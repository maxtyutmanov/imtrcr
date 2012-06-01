#ifndef UNIT_TESTS_LOGGER_MOCK_H
#define UNIT_TESTS_LOGGER_MOCK_H

#include <soap_service/ILogger.h>

namespace ImTrcr {
namespace UnitTests {

    class LoggerMock : public SoapService::ILogger {
    public:
        void LogMessage(const std::string& msg) const {
            //do nothing
        }
    };

}
}

#endif