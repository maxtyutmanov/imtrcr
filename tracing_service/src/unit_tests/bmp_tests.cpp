//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ImTrcrTests
#include <boost/test/unit_test.hpp>
#include "imaging/WinBMP.h"
#include "imaging/PointOutOfBitmapException.h"
#include <sstream>
#include <string>
#include <fstream>

using namespace std;
using namespace ImTrcr::Imaging;

BOOST_AUTO_TEST_SUITE(bitmap_tests)

BOOST_AUTO_TEST_CASE(from_file_24bit) {
    ifstream input("24bit.bmp");

    WinBMP* bmp = WinBMP::FromStream(input);

    BOOST_CHECK(bmp->GetWidth() == 60);
    BOOST_CHECK(bmp->GetHeight() == 40);

    for (image_size_t x = 0; x < bmp->GetWidth(); ++x) {
        for (image_size_t y = 0; y < bmp->GetHeight(); ++y) {
            ArgbQuad px = bmp->GetColor(x, y);

            if (17 <= x && x <= 50 &&
                23 <= y && y <= 30) {

                BOOST_ASSERT(px.red == 0 && px.green == 0 && px.blue == 0);
            }
            else {
                BOOST_ASSERT(px.red == 255 && px.green == 255 && px.blue == 255);
            }
        }
    }

    delete bmp;
}

BOOST_AUTO_TEST_CASE(from_file_8bit) {
    ifstream input("8bit.bmp");

    WinBMP* bmp = WinBMP::FromStream(input);

    BOOST_CHECK(bmp->GetWidth() == 60);
    BOOST_CHECK(bmp->GetHeight() == 40);

    for (image_size_t x = 0; x < bmp->GetWidth(); ++x) {
        for (image_size_t y = 0; y < bmp->GetHeight(); ++y) {
            ArgbQuad px = bmp->GetColor(x, y);

            if (17 <= x && x <= 50 &&
                23 <= y && y <= 30) {

                BOOST_ASSERT(px.red == 0 && px.green == 0 && px.blue == 0);
            }
            else {
                BOOST_ASSERT(px.red == 255 && px.green == 255 && px.blue == 255);
            }
        }
    }

    delete bmp;
}

BOOST_AUTO_TEST_SUITE_END();
