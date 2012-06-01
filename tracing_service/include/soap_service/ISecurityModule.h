#ifndef SOAP_SERVICE_ISECURITY_MODULE_H
#define SOAP_SERVICE_ISECURITY_MODULE_H

#include <string>

namespace ImTrcr {
namespace SoapService {

    class ISecurityModule {
    public:
        virtual bool CheckSystemID(const std::string& systemID) const = 0;
    };

}
}

#endif