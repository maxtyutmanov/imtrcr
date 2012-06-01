#ifndef UNIT_TESTS_SECURITY_MODULE_MOCK_H
#define UNIT_TESTS_SECURITY_MODULE_MOCK_H

#include <soap_service/ISecurityModule.h>

namespace ImTrcr {
namespace UnitTests {

    class SecurityModuleMock : public SoapService::ISecurityModule {
    public:
        virtual bool CheckSystemID(const std::string& systemID) const {
            return true;
        }
    };

}
}

#endif