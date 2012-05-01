#ifndef IMAGING_INVALID_BMP_STREAM_EXCEPTION_H
#define IMAGING_INVALID_BMP_STREAM_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace ImTrcr {
namespace Imaging {

    class InvalidBmpStreamException : public std::runtime_error {
    public: 
        InvalidBmpStreamException(const std::string& message) 
            : std::runtime_error(message) {}
            
        virtual ~InvalidBmpStreamException() throw() {}
    };

}
}

#endif
