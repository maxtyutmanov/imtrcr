#include <boost/test/unit_test.hpp>

#include <utils/Graph.h>

using namespace ImTrcr::Utils;
using namespace std;

BOOST_AUTO_TEST_SUITE(graph_tests)

BOOST_AUTO_TEST_CASE(find_shortest_cycle_test) {
    TwoDimArray<bool> ajMx(7, 7, false);

    ajMx.At(0, 1) = true;
    ajMx.At(0, 2) = true;

    ajMx.At(1, 2) = true;

    ajMx.At(2, 3) = true;
    ajMx.At(2, 4) = true;

    ajMx.At(3, 4) = true;
    
    ajMx.At(4, 5) = true;
    ajMx.At(4, 6) = true;

    ajMx.At(5, 6) = true;

    ajMx.At(6, 0) = true;

    vector<int> shortestCycle;

    GraphUtils::FindShortestCycle(ajMx, shortestCycle);

    BOOST_ASSERT(shortestCycle.size() == 4);

    BOOST_CHECK(shortestCycle[0] == 0);
    BOOST_CHECK(shortestCycle[1] == 2);
    BOOST_CHECK(shortestCycle[2] == 4);
    BOOST_CHECK(shortestCycle[3] == 6);
}

BOOST_AUTO_TEST_SUITE_END();