#ifndef SOAP_SERVICE_ILOGGER_H
#define SOAP_SERVICE_ILOGGER_H

#include <string>

namespace ImTrcr {
namespace SoapService {

    class ILogger {
    public:
        virtual void LogMessage(const std::string& msg) const = 0;
    };

}
}

#endif