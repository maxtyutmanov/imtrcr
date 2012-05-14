#include <boost/test/unit_test.hpp>

#include <imaging/SvgSerializer.h>
#include <imaging/PathSerializer.h>
#include <imaging/Path.h>

using namespace std;
using namespace ImTrcr::Imaging;
using namespace ImTrcr::Imaging::Primitives;

BOOST_AUTO_TEST_SUITE(svg_serializer_tests)

BOOST_AUTO_TEST_CASE(path_serializer_bezier_test) {
    PathSerializer s;

    PathCommand moveTo = PathCommand::MoveToCommand(10, 10.2);
    PathCommand bezier = PathCommand::QuadraticBezierToCommand(20.123, 20, 30.345, 30.1);
    PathCommand close = PathCommand::ClosePathCommand();
    
    s.MoveTo(moveTo);
    s.QuadraticBezier(bezier);
    s.ClosePath();

    const string expected = "M 10.00 10.20 Q 20.12 20.00 30.34 30.10 Z";
    string actual = s.GetResult();

    BOOST_CHECK(expected == actual);
}

BOOST_AUTO_TEST_CASE(svg_serializer_bezier_test) {
    SvgSerializer s;

    VectorImage* img = new VectorImage();

    PathCommand moveTo = PathCommand::MoveToCommand(10, 10.2);
    PathCommand bezier = PathCommand::QuadraticBezierToCommand(20.123, 20, 30.345, 30.1);
    PathCommand close = PathCommand::ClosePathCommand();
    Path* path = new Path(ArgbQuad(0, 0, 0));
    path->AddCommand(moveTo);
    path->AddCommand(bezier);
    path->AddCommand(close);
    img->AddPrimitive(path);

    moveTo = PathCommand::MoveToCommand(100, 100.2);
    bezier = PathCommand::QuadraticBezierToCommand(200.123, 200, 300.345, 300.1);
    close = PathCommand::ClosePathCommand();
    path = new Path(ArgbQuad(0, 0, 0));
    path->AddCommand(moveTo);
    path->AddCommand(bezier);
    path->AddCommand(close);
    img->AddPrimitive(path);

    TiXmlDocument* doc = s.Serialize(*img);
    TiXmlElement* root = doc->RootElement();

    BOOST_ASSERT(root != NULL);
    BOOST_CHECK(strcmp(root->Value(), "svg") == 0);

    TiXmlElement* firstChild = root->FirstChildElement();

    BOOST_ASSERT(firstChild != NULL);
    BOOST_CHECK(strcmp(firstChild->Value(), "path") == 0);
    BOOST_ASSERT(firstChild->Attribute("d") != NULL);
    BOOST_CHECK(strcmp(firstChild->Attribute("d"), "M 10.00 10.20 Q 20.12 20.00 30.34 30.10 Z") == 0);

    TiXmlElement* secondChild = firstChild->NextSiblingElement();

    BOOST_ASSERT(secondChild != NULL);
    BOOST_CHECK(strcmp(secondChild->Value(), "path") == 0);
    BOOST_ASSERT(secondChild->Attribute("d") != NULL);
    BOOST_CHECK(strcmp(secondChild->Attribute("d"), "M 100.00 100.20 Q 200.12 200.00 300.35 300.10 Z") == 0);

    BOOST_CHECK(secondChild->NextSiblingElement() == NULL);

    delete img;
    delete doc;
}

BOOST_AUTO_TEST_SUITE_END();