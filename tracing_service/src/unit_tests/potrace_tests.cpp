#include <boost/test/unit_test.hpp>

#include <vectorization/SimpleBWRecognizer.h>
#include <vectorization/PotraceImage.h>
#include <vectorization/PathDecomposer.h>

#include <unit_tests/RasterImageStub.h>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Vectorization;
using namespace ImTrcr::UnitTests;

BOOST_AUTO_TEST_SUITE(potrace_tests)

BOOST_AUTO_TEST_CASE(simple_black_white_recognizer_test) {
    SimpleBWRecognizer r;

    BOOST_CHECK(r.GetPotraceColor(ArgbQuad::Black()) == PixelColor::Black);
    BOOST_CHECK(r.GetPotraceColor(ArgbQuad::White()) == PixelColor::White);

    BOOST_CHECK(r.GetPotraceColor(ArgbQuad(155, 155, 155, 155)) == PixelColor::White);
    BOOST_CHECK(r.GetPotraceColor(ArgbQuad(100, 100, 100, 100)) == PixelColor::Black);
}

BOOST_AUTO_TEST_CASE(potrace_image_size_test) {
    RasterImageStub rasterImg(10, 10);
    SimpleBWRecognizer r;
    PotraceImage potraceImg(r, rasterImg);

    BOOST_CHECK(potraceImg.GetH() == 10);
    BOOST_CHECK(potraceImg.GetW() == 10);
}

BOOST_AUTO_TEST_CASE(potrace_image_inner_pixel_test) {
    RasterImageStub rasterImg(10, 10);
    rasterImg.SetColor(3, 3, ArgbQuad::Black());
    
    SimpleBWRecognizer r;
    PotraceImage potraceImg(r, rasterImg);

    //* * * * * 0
    //* * * * * 1
    //* * * * * 2
    //* * * # * 3
    //* * * * * 4
    //0 1 2 3 4 potrace image's coordinate grid nodes are located at pixel's corners

    BOOST_CHECK(potraceImg.RB(3, 3) == PixelColor::Black);
    BOOST_CHECK(potraceImg.LB(4, 3) == PixelColor::Black);
    BOOST_CHECK(potraceImg.RT(3, 4) == PixelColor::Black);
    BOOST_CHECK(potraceImg.LT(4, 4) == PixelColor::Black);
    BOOST_CHECK(potraceImg.LB(4, 4) == PixelColor::White);
    BOOST_CHECK(potraceImg.RT(4, 4) == PixelColor::White);
    BOOST_CHECK(potraceImg.RB(4, 4) == PixelColor::White);
}

BOOST_AUTO_TEST_CASE(potrace_image_boundary_pixels_test) {
    RasterImageStub rasterImg(10, 10);
    rasterImg.SetColor(0, 0, ArgbQuad::Black());
    
    SimpleBWRecognizer r;

    PotraceImage potraceImg(r, rasterImg);

    BOOST_CHECK(potraceImg.LT(0, 0) == PixelColor::White);
    BOOST_CHECK(potraceImg.LB(0, 0) == PixelColor::White);
    BOOST_CHECK(potraceImg.RT(0, 0) == PixelColor::White);
    BOOST_CHECK(potraceImg.RB(0, 0) == PixelColor::Black);
    BOOST_CHECK(potraceImg.LT(1, 1) == PixelColor::Black);
}

BOOST_AUTO_TEST_CASE(path_decomposer_test) {
    
}

BOOST_AUTO_TEST_SUITE_END();