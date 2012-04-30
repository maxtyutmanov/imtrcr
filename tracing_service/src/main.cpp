#include "vectorization/PotraceTracer.h"
#include "imaging/WinBMP.h"
#include "imaging/VectorImage.h"
#include <fstream>
#include <iostream>

#include "soap_service/soapH.h"
#include "soap_service/ImTrcrSoapBinding.nsmap"

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Vectorization;
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

        for (int i = 1; ;++i) {
            slave = soap_accept(&soap);

            if (slave < 0) {
                soap_print_fault(&soap, stderr);
                break;
            }

            fprintf(stderr, "%d: accepted connection from IP=%d.%d.%d.%d socket=%d", i,
                (soap.ip >> 24), (soap.ip >> 16) & 0xFF, (soap.ip >> 8) & 0xFF, soap.ip & 0xFF, slave);

            if (soap_serve(&soap) != SOAP_OK) {
                soap_print_fault(&soap, stderr);
            }

            fprintf(stderr, "request served\n");

            soap_destroy(&soap);
            soap_end(&soap);
        }
    }

    soap_done(&soap);

    return 0;
}

int __cdecl __ns1__Trace(struct soap* soap, _ns2__Trace* request, _ns2__TraceResponse* response) {
    return 0;
}