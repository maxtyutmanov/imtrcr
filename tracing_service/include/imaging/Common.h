#ifndef IMAGING_COMMON_H
#define IMAGING_COMMON_H

#include "utils/Common.h"

namespace ImTrcr {
namespace Imaging {

    //NOTE: this has to be signed, otherwise some loops in code would be broken!
    typedef signed int image_size_t;
}
}

#endif
