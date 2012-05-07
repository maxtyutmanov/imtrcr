#ifndef UTILS_MEMORY_H
#define UTILS_MEMORY_H

namespace ImTrcr {
namespace Utils {

    class MemoryUtils {
    public:
        template <typename T>
        static void SafeFree(T** pptr) {
            if (*pptr != NULL) {
                delete *pptr;
                *pptr = NULL;
            }
        }
    };

}
}

#endif
