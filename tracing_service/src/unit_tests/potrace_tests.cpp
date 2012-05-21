#include <boost/test/unit_test.hpp>

#include <vectorization/SimpleBWRecognizer.h>
#include <vectorization/PotraceImage.h>
#include <vectorization/PathDecomposer.h>
#include <vectorization/PolygonBuilder.h>

#include <utils/Collection.h>

#include <unit_tests/RasterImageStub.h>

#include <iostream>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Vectorization;
using namespace ImTrcr::UnitTests;
using namespace ImTrcr::Utils;
using namespace std;

void ToTheRight(PotracePath& path) {
    path.Augment(1, 0);
}

void ToTheLeft(PotracePath& path) {
    path.Augment(-1, 0);
}

void Upwards(PotracePath& path) {
    path.Augment(0, -1);
}

void Downwards(PotracePath& path) {
    path.Augment(0, 1);
}

BOOST_AUTO_TEST_SUITE(potrace_tests)

BOOST_AUTO_TEST_CASE(simple_black_white_recognizer_test) {
    SimpleBWRecognizer r;

    BOOST_CHECK(r.GetPotraceColor(ArgbQuad::Black()) == PixelColor::Black);
    BOOST_CHECK(r.GetPotraceColor(ArgbQuad::White()) == PixelColor::White);

    BOOST_CHECK(r.GetPotraceColor(ArgbQuad(155, 155, 155, 155)) == PixelColor::White);
    BOOST_CHECK(r.GetPotraceColor(ArgbQuad(100, 100, 100, 100)) == PixelColor::Black);
}

BOOST_AUTO_TEST_CASE(potrace_image_ctor_test) {
    vector<image_size_t> xs;
    vector<image_size_t> ys;

    xs.push_back(4); ys.push_back(0);
    xs.push_back(3); ys.push_back(1);
    xs.push_back(4); ys.push_back(1);
    xs.push_back(3); ys.push_back(2);
    xs.push_back(4); ys.push_back(2);
    xs.push_back(5); ys.push_back(2);
    xs.push_back(4); ys.push_back(3);
    xs.push_back(5); ys.push_back(3);

    RasterImageStub rasterImg(10, 10);
    ArgbQuad black = ArgbQuad(0, 0, 0);

    for (int i = 0; i < xs.size(); ++i) {
        rasterImg.SetColor(xs[i], ys[i], black);
    }

    SimpleBWRecognizer r;

    PotraceImage potraceImg(r, rasterImg);

    for (int i = 0; i < xs.size(); ++i) {
        BOOST_CHECK(potraceImg.RB(xs[i], ys[i]) == PixelColor::Black);
    }
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

BOOST_AUTO_TEST_CASE(potrace_image_invert_pixels_test) {
    RasterImageStub rasterImg(10, 10);
    vector<Point2> pointsToInvert;

    for (image_size_t x = 2; x < 5; ++x) {
        for (image_size_t y = 3; y < 5; ++y) {
            rasterImg.SetColor(x, y, ArgbQuad::Black());
            pointsToInvert.push_back(Point2(x, y));
        }
    }

    rasterImg.SetColor(3, 4, ArgbQuad::White());

    SimpleBWRecognizer r;

    PotraceImage potraceImg(r, rasterImg);

    potraceImg.InvertPixels(pointsToInvert);

    for (image_size_t x = 2; x < 5; ++x) {
        for (image_size_t y = 3; y < 5; ++y) {
            if (x == 3 && y == 4) {
                BOOST_CHECK(potraceImg.RB(x, y) == PixelColor::Black);
            }
            else {
                BOOST_CHECK(potraceImg.RB(x, y) == PixelColor::White);
            }
        }
    }
}

BOOST_AUTO_TEST_CASE(potrace_path_augment_not_closed_test) {
    PotracePath p;
    p.AddPoint(10, 11);
    p.Augment(1, 1);

    const vector<Point2>& points = p.GetPoints();

    BOOST_ASSERT(points.size() == 2);
    BOOST_CHECK(points[0].x == 10);
    BOOST_CHECK(points[0].y == 11);
    BOOST_CHECK(points[1].x == 11);
    BOOST_CHECK(points[1].y == 12);
}

BOOST_AUTO_TEST_CASE(potrace_path_augment_closed_test) {
    PotracePath p;
    p.AddPoint(10, 11);
    p.AddPoint(11, 11);
    p.AddPoint(11, 12);
    p.AddPoint(10, 12);
    p.Augment(0, -1);

    const vector<Point2>& points = p.GetPoints();

    BOOST_CHECK(points.size() == 4);
    BOOST_CHECK(p.IsClosed());
}

BOOST_AUTO_TEST_CASE(potrace_path_is_edge_in_path_test) {
    PotracePath p;

    p.AddPoint(0, 1);
    p.AddPoint(1, 1);
    p.AddPoint(2, 1);
    p.AddPoint(2, 2);
    p.AddPoint(3, 2);
    p.AddPoint(3, 1);
    p.AddPoint(3, 0);
    p.AddPoint(2, 0);

    BOOST_CHECK(p.IsEdgeInPath(2, 0, 3, 0));
    BOOST_CHECK(p.IsEdgeInPath(3, 0, 2, 0));
    BOOST_CHECK(p.IsEdgeInPath(1, 1, 2, 1));
    BOOST_CHECK(p.IsEdgeInPath(0, 1, 1, 1));
    BOOST_CHECK(!p.IsEdgeInPath(1, 1, 1, 2));
}

BOOST_AUTO_TEST_CASE(potrace_path_get_interior_points_simple_test) {
    PotracePath p;

    p.AddPoint(3, 1);
    Downwards(p);
    ToTheLeft(p);
    for (int i = 0; i < 4; ++i) { Downwards(p); }
    ToTheRight(p);
    Downwards(p);
    for (int i = 0; i < 2; ++i) { ToTheRight(p); }
    for (int i = 0; i < 2; ++i) { Upwards(p); }
    ToTheRight(p);
    for (int i = 0; i < 4; ++i) { Upwards(p); }
    for (int i = 0; i < 3; ++i) { ToTheLeft(p); }

    BOOST_ASSERT(p.IsClosed());

    vector<Point2> interiorPoints = p.GetInteriorPoints();

    BOOST_CHECK(interiorPoints.size() == 20);
    
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 1)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 1)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(5, 1)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(2, 2)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 2)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 2)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(5, 2)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(2, 3)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 3)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 3)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(5, 3)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(2, 4)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 4)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 4)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(5, 4)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(2, 5)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 5)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 5)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 6)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 6)));
}

BOOST_AUTO_TEST_CASE(potrace_path_get_interior_points_concave_test) {
    PotracePath p;

    p.AddPoint(3, 1);
    Downwards(p);
    ToTheLeft(p);
    for (int i = 0; i < 4; ++i) { Downwards(p); }
    ToTheRight(p);
    Downwards(p);
    for (int i = 0; i < 2; ++i) { ToTheRight(p); }
    for (int i = 0; i < 2; ++i) { Upwards(p); }
    ToTheRight(p);
    for (int i = 0; i < 4; ++i) { Upwards(p); }
    ToTheLeft(p);
    for (int i = 0; i < 2; ++i) { Downwards(p); }
    ToTheLeft(p);
    for (int i = 0; i < 2; ++i) { Upwards(p); }
    ToTheLeft(p);

    BOOST_ASSERT(p.IsClosed());

    vector<Point2> interiorPoints = p.GetInteriorPoints();

    BOOST_CHECK(interiorPoints.size() == 18);
    
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 1)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(5, 1)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(2, 2)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 2)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(5, 2)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(2, 3)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 3)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 3)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(5, 3)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(2, 4)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 4)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 4)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(5, 4)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(2, 5)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 5)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 5)));

    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(3, 6)));
    BOOST_CHECK(CollectionUtils::Contains(interiorPoints, Point2(4, 6)));
}

BOOST_AUTO_TEST_CASE(path_decomposer_test) {
    ArgbQuad black = ArgbQuad(0, 0, 0);
    RasterImageStub rasterImg(10, 10);
    rasterImg.SetColor(4, 0, black);
    rasterImg.SetColor(3, 1, black);
    rasterImg.SetColor(4, 1, black);
    rasterImg.SetColor(3, 2, black);
    rasterImg.SetColor(4, 2, black);
    rasterImg.SetColor(5, 2, black);
    rasterImg.SetColor(4, 3, black);
    rasterImg.SetColor(5, 3, black);

    //0 1 2 3 4 5 6 7 8 9 0
    // * * * * # * * * * * 
    // * * * # # * * * * * 
    // * * * # # # * * * * 
    // * * * * # # * * * * 
    // * * * * * * * * * * 
    // * * * * * * * * * * 
    // * * * * * * * * * * 
    // * * * * * * * * * * 
    // * * * * * * * * * * 
    // * * * * * * * * * * 

    SimpleBWRecognizer r;

    VectorImage vectorImg;
    PotraceImage potraceImg(r, rasterImg);

    TracingContext ctx(vectorImg, potraceImg);
    
    PathDecomposer d;
    d.FindClosedPaths(ctx);

    BOOST_ASSERT(ctx.paths.size() == 1);
    BOOST_ASSERT(ctx.paths[0].IsClosed());

    const vector<Point2>& points = ctx.paths[0].GetPoints();

    BOOST_ASSERT(points.size() == 14);

    BOOST_CHECK(points[0] == Point2(4, 0));
    BOOST_CHECK(points[1] == Point2(4, 1));
    BOOST_CHECK(points[2] == Point2(3, 1));
    BOOST_CHECK(points[3] == Point2(3, 2));
    BOOST_CHECK(points[4] == Point2(3, 3));
    BOOST_CHECK(points[5] == Point2(4, 3));
    BOOST_CHECK(points[6] == Point2(4, 4));
    BOOST_CHECK(points[7] == Point2(5, 4));
    BOOST_CHECK(points[8] == Point2(6, 4));
    BOOST_CHECK(points[9] == Point2(6, 3));
    BOOST_CHECK(points[10] == Point2(6, 2));
    BOOST_CHECK(points[11] == Point2(5, 2));
    BOOST_CHECK(points[12] == Point2(5, 1));
    BOOST_CHECK(points[13] == Point2(5, 0));

}

BOOST_AUTO_TEST_CASE(potrace_path_every_two_point_path_is_straight_test) {
    PotracePath p;

    p.AddPoint(3, 1);
    Downwards(p);
    ToTheLeft(p);
    for (int i = 0; i < 4; ++i) { Downwards(p); }
    ToTheRight(p);
    Downwards(p);
    ToTheRight(p);
    Downwards(p);
    for (int i = 0; i < 2; ++i) { ToTheRight(p); }
    Upwards(p);
    ToTheRight(p);
    for (int i = 0; i < 4; ++i) { Upwards(p); }
    ToTheLeft(p);
    Upwards(p);
    ToTheLeft(p);
    Upwards(p);
    for (int i = 0; i < 2; ++i) { ToTheLeft(p); }

    const int pointsCount = p.GetPoints().size();

    for (int i = 0; i < pointsCount - 1; ++i) {
        BOOST_CHECK(p.IsStraight(i, i + 1));
    }
}

BOOST_AUTO_TEST_CASE(potrace_path_every_three_point_path_is_straight_test) {
    PotracePath p;

    p.AddPoint(3, 1);
    Downwards(p);
    ToTheLeft(p);
    for (int i = 0; i < 4; ++i) { Downwards(p); }
    ToTheRight(p);
    Downwards(p);
    ToTheRight(p);
    Downwards(p);
    for (int i = 0; i < 2; ++i) { ToTheRight(p); }
    Upwards(p);
    ToTheRight(p);
    for (int i = 0; i < 4; ++i) { Upwards(p); }
    ToTheLeft(p);
    Upwards(p);
    ToTheLeft(p);
    Upwards(p);
    for (int i = 0; i < 2; ++i) { ToTheLeft(p); }

    BOOST_CHECK(p.IsStraight(0, 2));
    BOOST_CHECK(p.IsStraight(23, 1));
}

BOOST_AUTO_TEST_CASE(potrace_path_long_straight_path_test) {
    PotracePath p;

    p.AddPoint(0, 0);
    for (int i = 0; i < 6; ++i) { ToTheRight(p); }
    Upwards(p);
    for (int i = 0; i < 5; ++i) { ToTheRight(p); }

    BOOST_CHECK(p.IsStraight(0, p.GetPoints().size() - 1));
}

BOOST_AUTO_TEST_CASE(potrace_path_long_non_straight_path_all_directions_test) {
    PotracePath p;

    p.AddPoint(0, 0);

    Upwards(p);
    for (int i = 0; i < 4; ++i) { ToTheRight(p); }
    Downwards(p);
    ToTheLeft(p);

    BOOST_CHECK(!p.IsStraight(0, p.GetPoints().size() - 1));
}

BOOST_AUTO_TEST_CASE(potrace_path_long_non_straight_path_that_doesnt_use_all_directions) {
    PotracePath p;

    p.AddPoint(0, 0);

    for (int i = 0; i < 2; ++i) { ToTheRight(p); }
    Upwards(p);
    for (int i = 0; i < 3; ++i) { ToTheRight(p); }
    Upwards(p);
    for (int i = 0; i < 4; ++i) { ToTheRight(p); }
    Downwards(p);

    BOOST_CHECK(!p.IsStraight(0, p.GetPoints().size() - 1));
}

BOOST_AUTO_TEST_CASE(potrace_path_long_non_straight_path_that_doesnt_use_all_directions_2) {
    PotracePath p;

    p.AddPoint(0, 0);
    for (int i = 0; i < 2; ++i) { ToTheRight(p); }
    for (int i = 0; i < 2; ++i) { Downwards(p); }
    for (int i = 0; i < 2; ++i) { ToTheRight(p); }

    BOOST_CHECK(!p.IsStraight(0, p.GetPoints().size() - 1));
}

BOOST_AUTO_TEST_CASE(potrace_path_is_possible_segment_true) {
    PotracePath p;

    p.AddPoint(0, 0);
    for (int i = 0; i < 6; ++i) { ToTheRight(p); }
    Upwards(p);
    for (int i = 0; i < 5; ++i) { ToTheRight(p); }

    BOOST_ASSERT(p.IsStraight(0, p.GetPoints().size() - 1));

    BOOST_CHECK(p.IsPossibleSegment(1, p.GetPoints().size() - 2));
}

BOOST_AUTO_TEST_CASE(polygon_builder_test) {
    RasterImageStub rasterImg(10, 10);
    SimpleBWRecognizer r;
    PotraceImage potraceImg(r, rasterImg);
    VectorImage vectorImg;

    TracingContext ctx(vectorImg, potraceImg);

    PotracePath p;

    p.AddPoint(3, 1);
    Downwards(p);
    ToTheLeft(p);
    for (int i = 0; i < 4; ++i) { Downwards(p); }
    ToTheRight(p);
    Downwards(p);
    ToTheRight(p);
    Downwards(p);
    for (int i = 0; i < 2; ++i) { ToTheRight(p); }
    Upwards(p);
    ToTheRight(p);
    for (int i = 0; i < 4; ++i) { Upwards(p); }
    ToTheLeft(p);
    Upwards(p);
    ToTheLeft(p);
    Upwards(p);
    for (int i = 0; i < 2; ++i) { ToTheLeft(p); }

    ctx.paths.push_back(p);

    PolygonBuilder polygonBuilder;
    polygonBuilder.Polygonize(ctx);

    const vector<Polygon>& polygons = ctx.polygons;

    BOOST_ASSERT(polygons.size() == 1);

    Polygon pol = polygons[0];

    vector<int> ind = pol.GetVerticesIndices();

    BOOST_ASSERT(ind.size() == 8);

    BOOST_CHECK(ind[0] == 0);
    BOOST_CHECK(ind[1] == 1);
    BOOST_CHECK(ind[2] == 5);
    BOOST_CHECK(ind[3] == 9);
    BOOST_CHECK(ind[4] == 11);
    BOOST_CHECK(ind[5] == 13);
    BOOST_CHECK(ind[6] == 17);
    BOOST_CHECK(ind[7] == 21);
}

BOOST_AUTO_TEST_SUITE_END();