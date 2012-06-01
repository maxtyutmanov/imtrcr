#ifndef UTILS_STRING_H
#define UTILS_STRING_H

#include <string>

namespace ImTrcr {
namespace Utils {

    class StringUtils {
    public:
        static void TrimEnd(std::string& str);
        static bool TryParseInt(const std::string& str, int& result);
    };

}
}

#endif