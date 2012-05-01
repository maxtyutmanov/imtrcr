#ifndef IMAGING_FILE_NOT_FOUND_EXCEPTION_H
#define IMAGING_FILE_NOT_FOUND_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace ImTrcr {
namespace Imaging {

    class FileNotFoundException : public std::runtime_error {
    public:
        FileNotFoundException(const std::wstring& filePath)
            : std::runtime_error("File with specified path cannot be found"), filePath(filePath) {}

        std::wstring GetFilePath() const {
            return filePath;
        }
        
        virtual ~FileNotFoundException() throw() {}
    private:
        std::wstring filePath;
    };

}
}

#endif
