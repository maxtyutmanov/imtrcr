#ifndef UTILS_COLLECTION_H
#define UTILS_COLLECTION_H

namespace ImTrcr {
namespace Utils {

    class CollectionUtils {
    public:
        template <typename TCollection, typename TElement>
        static bool Contains(const TCollection& c, const TElement& el) {
            TCollection::const_iterator it;

            for (it = c.begin(); it != c.end(); ++it) {
                if (*it == el) {
                    return true;
                }
            }

            return false;
        }
    };

}
}

#endif