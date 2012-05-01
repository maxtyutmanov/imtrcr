#pragma once

#include <utils/Common.h>
#include <string>

namespace ImTrcr {
namespace Utils {

    class Base64 {
    public:
        static bool Decode(const std::string& encoded, std::string& decoded);
    private:
        // base64 
        static const char b64_table[];
        static const byte reverse_table[];
    };

}
}