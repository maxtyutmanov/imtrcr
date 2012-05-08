#include <vectorization/SimpleBWRecognizer.h>

namespace ImTrcr {
namespace Vectorization {

    PixelColor::Enum SimpleBWRecognizer::GetPotraceColor(Imaging::ArgbQuad actualColor) const {
        const int maxSum = 255 + 255 + 255 + 255;
        int actualSum = actualColor.alpha + actualColor.blue + actualColor.green + actualColor.red;

        double coeff = (double)actualSum / maxSum;

        if (coeff > 0.5) {
            return PixelColor::White;
        }
        else {
            return PixelColor::Black;
        }
    }

}
}