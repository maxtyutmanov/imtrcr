#ifndef SOAP_SERVICE_SECURITY_MODULE_H
#define SOAP_SERVICE_SECURITY_MODULE_H

#include <soap_service/ISecurityModule.h>

namespace ImTrcr {
namespace SoapService {

    class SecurityModule : public ISecurityModule {
    public:
        SecurityModule(const std::string& dbPath);
        virtual bool CheckSystemID(const std::string& systemID) const;
    private:
        std::string dbPath;
    };

}
}

#endif