#ifndef UTILS_GRAPH_H
#define UTILS_GRAPH_H

#include <vector>

#include <utils/TwoDimArray.h>

namespace ImTrcr {
namespace Utils {

    class GraphUtils {
    public:
        static void FindShortestCycle(const TwoDimArray<bool>& adjacencyM, std::vector<int>& shortestCycle);

    private:
        static void GetVerticesListFromPrevList(const std::vector<int>& prevList, const int last, std::vector<int>& verticesList);
    };

}
}

#endif