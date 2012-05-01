#include <utils/base64.h>
#include <sstream>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <cctype>

using namespace std;
using namespace boost::archive::iterators;

namespace ImTrcr {
namespace Utils {

    const char Base64::b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const byte Base64::reverse_table[] = {
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
        64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
        64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
    };

    bool Base64::Decode(const string& encoded, string& decoded) {
        decoded.clear();
        int bits_collected = 0;
        unsigned int accumulator = 0;
        const string::const_iterator last = encoded.end();

        for (string::const_iterator it = encoded.begin(); it != last; ++it) {
            const int c = *it;
            
            if (isspace(c) || c == '=') {
                // Skip whitespace and padding. Be liberal in what you accept.
                continue;
            }

            if ((c > 127) || (c < 0) || (reverse_table[c] > 63)) {
                return false;
            }

            accumulator = (accumulator << 6) | reverse_table[c];
            bits_collected += 6;

            if (bits_collected >= 8) {
                bits_collected -= 8;
                decoded += (char)((accumulator >> bits_collected) & 0xffu);
            }
        }

        return true;
    }

}
}