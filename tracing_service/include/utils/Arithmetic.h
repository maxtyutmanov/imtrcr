#ifndef UTILS_ARITHMETIC_H
#define UTILS_ARITHMETIC_H

namespace ImTrcr {
namespace Utils {

    class ArithmeticUtils {
    public:
        template <typename TVal>
        static TVal CyclicInc(TVal val, TVal period) {
            TVal result = val + 1;

            if (result < period) {
                return result;
            }
            else {
                return result - period;
            }
        }

        template <typename TVal>
        static TVal CyclicDec(TVal val, TVal period) {
            TVal result = val - 1;

            if (result >= 0) {
                return result;
            }
            else {
                return result + period;
            }
        }
    };

}
}

#endif