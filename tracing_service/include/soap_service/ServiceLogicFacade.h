#ifndef SOAP_SERVICE_SERVICE_LOGIC_FACADE_H
#define SOAP_SERVICE_SERVICE_LOGIC_FACADE_H

#include <imaging/ISvgSerializer.h>

#include <vectorization/ITracer.h>

#include <soap_service/soapH.h>

namespace ImTrcr {
namespace SoapService {

    //Forms abstraction layer above logic for handling SOAP requests to tracing service
    class ServiceLogicFacade {
    public:
        ServiceLogicFacade(Imaging::ISvgSerializer* svgSerializer, Vectorization::ITracer* tracer);
        virtual ~ServiceLogicFacade();

        int Trace(struct soap* soap, _ns2__Trace* request, _ns2__TraceResponse* response) const;
    private:
        Imaging::ISvgSerializer* svgSerializer;
        Vectorization::ITracer* tracer;
    };

}
}

#endif