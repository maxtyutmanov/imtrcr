#include <utils/String.h>

using namespace std;

namespace ImTrcr {
namespace Utils {

    void StringUtils::TrimEnd(string& str) {
        while (str.length() > 0 && str[str.length() - 1] == ' ') {
            str.erase(str.length() - 1, 1);
        }
    }

    bool StringUtils::TryParseInt(const string& str, int& result) {
        char *end;
        long l;
        errno = 0;
        l = strtol(str.c_str(), &end, 10);
        if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
            return false;
        }
        if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
            return false;
        }
        if (*str.c_str() == '\0' || *end != '\0') {
            return false;
        }
        result = l;
        return true;
    }

}
}
