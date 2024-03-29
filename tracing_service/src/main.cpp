#include <fstream>
#include <iostream>
#include <sstream>

#include <vectorization/PotraceTracer.h>
#include <vectorization/SimpleBWRecognizer.h>

#include <imaging/SvgSerializer.h>
#include <imaging/WinBMP.h>
#include <imaging/VectorImage.h>
#include <imaging/InvalidBmpStreamException.h>

#include <utils/base64.h>
#include <utils/Memory.h>
#include <utils/String.h>

#include <soap_service/soapH.h>
#include <soap_service/StatusCodes.h>
#include <soap_service/ServiceLogicFacade.h>
#include <soap_service/ImTrcrSoapBinding.nsmap>
#include <soap_service/SecurityModule.h>
#include <soap_service/DbLogger.h>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Vectorization;
using namespace ImTrcr::Utils;
using namespace ImTrcr::SoapService;
using namespace std;

ServiceLogicFacade* serviceLogic = NULL;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Two args are required: 1) port 2) path to sqlite3 database" << endl;
        return -1;
    }

    int portNumber;

    if (!StringUtils::TryParseInt(argv[1], portNumber)) {
        cerr << "Wrong port number" << endl;
        return -1;
    }

    ISecurityModule* sm = new SecurityModule(argv[2]);
    ILogger* logger = new DbLogger(argv[2]);

    serviceLogic = new ServiceLogicFacade(new SvgSerializer(), new PotraceTracer(new SimpleBWRecognizer()), sm, logger);

    struct soap soap;

    int master, slave;  //sockets

    soap_init(&soap);

    master = soap_bind(&soap, NULL, portNumber, 100);

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

    MemoryUtils::SafeFree(&serviceLogic);

    return 0;
}

int __ns1__Trace(struct soap* soap, _ns2__Trace* request, _ns2__TraceResponse* response) {
    return serviceLogic->Trace(soap, request, response);
}