#include <utils/String.h>

using namespace std;

namespace ImTrcr {
namespace Utils {

    void StringUtils::TrimEnd(string& str) {
        while (str.length() > 0 && str[str.length() - 1] == ' ') {
            str.erase(str.length() - 1, 1);
        }
    }

}
}
