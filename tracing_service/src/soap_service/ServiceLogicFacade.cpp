#include <soap_service/ServiceLogicFacade.h>
#include <soap_service/StatusCodes.h>

#include <imaging/RasterImage.h>
#include <imaging/VectorImage.h>
#include <imaging/WinBMP.h>
#include <imaging/InvalidBmpStreamException.h>

#include <utils/Memory.h>
#include <utils/base64.h>

#include <assert.h>
#include <sstream>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Vectorization;
using namespace ImTrcr::Utils;
using namespace std;

namespace ImTrcr {
namespace SoapService {

    ServiceLogicFacade::ServiceLogicFacade(Imaging::ISvgSerializer* svgSerializer, Vectorization::ITracer* tracer) {
        assert(svgSerializer != NULL);
        assert(tracer != NULL);

        this->svgSerializer = svgSerializer;
        this->tracer = tracer;
    }

    ServiceLogicFacade::~ServiceLogicFacade() {
        MemoryUtils::SafeFree(&svgSerializer);
        MemoryUtils::SafeFree(&tracer);
    }

    int ServiceLogicFacade::Trace(struct soap* soap, _ns2__Trace* request, _ns2__TraceResponse* response) const {
        
        RasterImage* rasterImage = NULL;
        VectorImage* vectorImage = NULL;
        TiXmlDocument* svgXmlDocument = NULL;

        try {

            //decode image data from base64
            string decodedImgData;

            bool encodingSuccessful = Base64::Decode(request->imageData, decodedImgData);

            if (!encodingSuccessful) {
                response->statusCode = StatusCodes::DECODING_ERROR;
                goto CLEANUP;
            }

            istringstream sourceImageStream(decodedImgData);

            //create RasterImage instance

            try {
                rasterImage = WinBMP::FromStream(sourceImageStream);
            }
            catch (const ImTrcr::Imaging::InvalidBmpStreamException& ex) {
                response->statusCode = StatusCodes::WRONG_FORMAT_ERROR;
                goto CLEANUP;
            }
            catch (...) {
                response->statusCode = StatusCodes::WRONG_FORMAT_ERROR;
                goto CLEANUP;
            }

            //trace RasterImage instance to VectorImage instance
            try {
                vectorImage = tracer->Trace(*rasterImage);
            }
            catch (...) {
                response->statusCode = StatusCodes::TRACING_ERROR;
                goto CLEANUP;
            }

            //serialize VectorImage to SVG XML and put it into response object
            svgXmlDocument = svgSerializer->Serialize(*vectorImage);

            TiXmlPrinter printer;
            printer.SetStreamPrinting();
            svgXmlDocument->Accept(&printer);
            response->svgXml = printer.CStr();
            response->statusCode = StatusCodes::OK;
            goto CLEANUP;
        }
        catch (...) {
            response->statusCode = StatusCodes::UNKNOWN_ERROR;
            goto CLEANUP;
        }

    CLEANUP:
        MemoryUtils::SafeFree(&rasterImage);
        MemoryUtils::SafeFree(&vectorImage);
        MemoryUtils::SafeFree(&svgXmlDocument);

        return SOAP_OK;
    }
}
}