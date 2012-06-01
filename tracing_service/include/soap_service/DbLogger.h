#ifndef SOAP_SERVICE_LOGGER_H
#define SOAP_SERVICE_LOGGER_H

#include <soap_service/ILogger.h>

namespace ImTrcr {
namespace SoapService {

    class DbLogger : public ILogger {
    public:
        DbLogger(const std::string& dbPath);

        virtual void LogMessage(const std::string& msg) const;
    private:
        std::string dbPath;
    };

}
}

#endif