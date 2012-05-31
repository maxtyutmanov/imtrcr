#include <boost/test/unit_test.hpp>

#include <vectorization/StraightLineEquation.h>

#include <utils/Arithmetic.h>

using namespace ImTrcr::Vectorization;
using namespace ImTrcr::Imaging;
using namespace ImTrcr::Utils;

BOOST_AUTO_TEST_SUITE(straight_line_equation_tests)

BOOST_AUTO_TEST_CASE(intersection_point_test) {
    StraightLineEquation l1(0, 2, 4, 2);
    StraightLineEquation l2(0, 0, 4, 4);
    StraightLineEquation l3(3, 0, 3, 100);

    Point2F foundPoint = StraightLineEquation::GetIntersectionPoint(l1, l2);

    BOOST_CHECK(ArithmeticUtils::RoughlyEq(foundPoint.GetX(), 2.0f));
    BOOST_CHECK(ArithmeticUtils::RoughlyEq(foundPoint.GetY(), 2.0f));

    foundPoint = StraightLineEquation::GetIntersectionPoint(l1, l3);

    BOOST_CHECK(ArithmeticUtils::RoughlyEq(foundPoint.GetX(), 3.0f));
    BOOST_CHECK(ArithmeticUtils::RoughlyEq(foundPoint.GetY(), 2.0f));

    foundPoint = StraightLineEquation::GetIntersectionPoint(l2, l3);

    BOOST_CHECK(ArithmeticUtils::RoughlyEq(foundPoint.GetX(), 3.0f));
    BOOST_CHECK(ArithmeticUtils::RoughlyEq(foundPoint.GetY(), 3.0f));
}

BOOST_AUTO_TEST_CASE(parallel_to_test_non_vertical_line) {
    StraightLineEquation l1(0, 0, 4, 4);

    Point2F p(2, 3);

    StraightLineEquation parallel = StraightLineEquation::ParallelTo(l1, p);

    BOOST_CHECK(ArithmeticUtils::RoughlyEq(parallel.GetA(), -1.0f));
    BOOST_CHECK(ArithmeticUtils::RoughlyEq(parallel.GetB(), 1.0f));
    BOOST_CHECK(ArithmeticUtils::RoughlyEq(parallel.GetC(), -1.0f));
}

BOOST_AUTO_TEST_CASE(parallel_to_test_vertical_line) {
    StraightLineEquation l1(3, 0, 3, 100);

    Point2F p(2, 3);

    StraightLineEquation parallel = StraightLineEquation::ParallelTo(l1, p);

    BOOST_CHECK(ArithmeticUtils::RoughlyEq(parallel.GetA(), 1.0f));
    BOOST_CHECK(ArithmeticUtils::RoughlyEq(parallel.GetB(), 0.0f));
    BOOST_CHECK(ArithmeticUtils::RoughlyEq(parallel.GetC(), -2.0f));
}

BOOST_AUTO_TEST_CASE(distance_between_lines) {
    StraightLineEquation l1(0, 3, 1, 5);
    StraightLineEquation l2(0, 7, 1, 9);

    float distance = StraightLineEquation::GetDistanceBetweenLines(l1, l2);

    BOOST_CHECK(ArithmeticUtils::RoughlyEq(distance, 1.789f, 0.1f));
}

BOOST_AUTO_TEST_CASE(distance_between_lines_horizontal) {
    StraightLineEquation l1(0, 3, 10, 3);
    StraightLineEquation l2(0, 5, 100, 5);

    float distance = StraightLineEquation::GetDistanceBetweenLines(l1, l2);

    BOOST_CHECK(ArithmeticUtils::RoughlyEq(distance, 2.0f));
}

BOOST_AUTO_TEST_CASE(distance_between_lines_vertical) {
    StraightLineEquation l1(3, 0, 3, 100);
    StraightLineEquation l2(5, 0, 5, 10);

    float distance = StraightLineEquation::GetDistanceBetweenLines(l1, l2);

    BOOST_CHECK(ArithmeticUtils::RoughlyEq(distance, 2.0f));
}

BOOST_AUTO_TEST_SUITE_END();