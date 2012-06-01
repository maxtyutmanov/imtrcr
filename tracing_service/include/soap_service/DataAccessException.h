#ifndef SOAP_SERVICE_DATA_ACCESS_EXCEPTION_H
#define SOAP_SERVICE_DATA_ACCESS_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace ImTrcr {
namespace SoapService {

    class DataAccessException : public std::runtime_error {
    public:
        DataAccessException(const std::string& message)
            : std::runtime_error(message) {}
    };

}
}

#endif