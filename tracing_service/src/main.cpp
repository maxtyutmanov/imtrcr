#include <fstream>
#include <iostream>
#include <sstream>

#include <vectorization/PotraceTracer.h>

#include <imaging/SvgSerializer.h>
#include <imaging/WinBMP.h>
#include <imaging/VectorImage.h>
#include <imaging/InvalidBmpStreamException.h>

#include <utils/base64.h>

#include <soap_service/soapH.h>
#include <soap_service/ImTrcrSoapBinding.nsmap>
#include <soap_service/StatusCodes.h>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Vectorization;
using namespace ImTrcr::Utils;
using namespace std;

int main(int argc, char* argv[]) {
    struct soap soap;

    int master, slave;  //sockets

    soap_init(&soap);

    master = soap_bind(&soap, NULL, 55555, 100);

    if (master < 0) {
        soap_print_fault(&soap, stderr);
    }
    else {
        fprintf(stderr, "Socket connection successful: master socket = %d\n", master);

        //here's the main loop
        for (int i = 1; ;++i) {
            //accept connection
            slave = soap_accept(&soap); 

            if (slave < 0) {
                soap_print_fault(&soap, stderr);
                break;
            }

            //logging
            fprintf(stderr, "%d: accepted connection from IP=%d.%d.%d.%d socket=%d\n", i,
                (soap.ip >> 24), (soap.ip >> 16) & 0xFF, (soap.ip >> 8) & 0xFF, soap.ip & 0xFF, slave);

            //dispatch request to handler
            if (soap_serve(&soap) != SOAP_OK) {
                soap_print_fault(&soap, stderr);
            }

            fprintf(stderr, "request served\n");

            //dispose resources
            soap_destroy(&soap);
            soap_end(&soap);
        }
    }

    soap_done(&soap);

    return 0;
}

int __ns1__Trace(struct soap* soap, _ns2__Trace* request, _ns2__TraceResponse* response) {

    //decode image data from base64
    string decodedImgData;

    bool encodingSuccessful = Base64::Decode(request->imageData, decodedImgData);

    if (!encodingSuccessful) {
        response->statusCode = StatusCodes::DECODING_ERROR;
        return SOAP_ERR;
    }

    istringstream sourceImageStream(decodedImgData);

    //create RasterImage instance

    RasterImage* rasterImage = NULL;

    try {
        rasterImage = WinBMP::FromStream(sourceImageStream);
    }
    catch (const ImTrcr::Imaging::InvalidBmpStreamException& ex) {
        response->statusCode = StatusCodes::WRONG_FORMAT_ERROR;
        return SOAP_OK;
    }
    catch (...) {
        response->statusCode = StatusCodes::WRONG_FORMAT_ERROR;
        return SOAP_OK;
    }

    //trace RasterImage instance to VectorImage instance

    ITracer* tracer = new PotraceTracer();
    VectorImage* vectorImage = NULL;

    try {
        vectorImage = tracer->Trace(*rasterImage);
    }
    catch (...) {
        delete rasterImage;
        delete tracer;

        response->statusCode = StatusCodes::TRACING_ERROR;
        return SOAP_OK;
    }

    //serialize VectorImage to SVG XML and put it into response object
    ISvgSerializer* svgSerializer = new SvgSerializer();
    TiXmlDocument* svgXmlDocument = svgSerializer->Serialize(*vectorImage);

    TiXmlPrinter printer;
    printer.SetStreamPrinting();
    svgXmlDocument->Accept(&printer);
    response->svgXml = printer.CStr();

    delete rasterImage;
    delete tracer;
    delete vectorImage;
    delete svgSerializer;
    delete svgXmlDocument;

    response->statusCode = StatusCodes::OK;
    return SOAP_OK;
}
