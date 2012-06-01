#include <vectorization/PathDecomposer.h>

#include <stdexcept>
#include <map>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Vectorization;
using namespace std;

namespace ImTrcr {
namespace Vectorization {

    PathDecomposer::PathDecomposer() {
        walkDirections[Directions::RIGHT].x = 1;
        walkDirections[Directions::RIGHT].y = 0;

        walkDirections[Directions::LEFT].x = -1;
        walkDirections[Directions::LEFT].y = 0;

        walkDirections[Directions::DOWNWARDS].x = 0;
        walkDirections[Directions::DOWNWARDS].y = 1;

        walkDirections[Directions::UPWARDS].x = 0;
        walkDirections[Directions::UPWARDS].y = -1;
    }

    void PathDecomposer::FindClosedPaths(TracingContext& ctx) {
        ctx.paths.clear();

        image_size_t height = ctx.potraceImg.GetH();
        image_size_t width = ctx.potraceImg.GetW();
        
        for (image_size_t y = 0; y < height; ++y) {
            for (image_size_t x = 0; x < width; ++x) {
                if (ctx.potraceImg.RB(x, y) == PixelColor::Black) {
                    PotracePath path(ctx.potraceImg.IsInvertedRB(x, y));
                    path.AddPoint(x, y);
                    path.AddPoint(x, y + 1);    //going to the bottom edge of the pixel
                    BuildPath(ctx.potraceImg, path);
                    vector<Point2> interiorPoints = path.GetInteriorPoints();
                    ctx.potraceImg.InvertPixels(interiorPoints);
                    
                    if (ctx.opts.despecklingPixels == 0 || interiorPoints.size() > ctx.opts.despecklingPixels) {
                       ctx.paths.push_back(path);
                    }
                }
            }
        }
    }

    void PathDecomposer::BuildPath(const PotraceImage& img, PotracePath& path) {
        //given the current and previous points, find a direction to go. 
        //Direction is a 2 dimensional vector

        while (!path.IsClosed()) {
            bool found = false;
            Point2 foundDirection;

            for (int i = 0; i < DIRECTIONS_COUNT; ++i) {
                if (IsDirectionAllowed(img, path, (Directions::Enum)i)) {
                    //TODO: implement turn policies

                    foundDirection = walkDirections[i];
                    found = true;
                    break;
                }
            }

            if (found) {
                path.Augment(foundDirection.x, foundDirection.y);
            }
            else {
                throw logic_error("Cannot augment path. Cannot find direction.");
            }
        }
    }

    bool PathDecomposer::IsDirectionAllowed(const PotraceImage& img, const PotracePath& path, const Directions::Enum direction) {
        Point2 directionVector = walkDirections[direction];

        //...check for back direction
        Point2 resultingEdge = Point2(path.CurX() + directionVector.x, path.CurY() + directionVector.y);

        //...check if new edge is already included in the current path
        if (path.IsEdgeInPath(path.CurX(), path.CurY(), path.CurX() + directionVector.x, path.CurY() + directionVector.y)) {
            return false;
        }

        //...check if the resulting edge has black pixel to the 
        //left and white pixel to the right of itself

        switch (direction) {
        case Directions::LEFT:
            return 
                img.LB(path.CurX(), path.CurY()) == PixelColor::Black && 
                img.LT(path.CurX(), path.CurY()) == PixelColor::White;
        case Directions::RIGHT:
            return
                img.RB(path.CurX(), path.CurY()) == PixelColor::White && 
                img.RT(path.CurX(), path.CurY()) == PixelColor::Black;
        case Directions::DOWNWARDS:
            return
                img.RB(path.CurX(), path.CurY()) == PixelColor::Black && 
                img.LB(path.CurX(), path.CurY()) == PixelColor::White;
        case Directions::UPWARDS:
            return
                img.LT(path.CurX(), path.CurY()) == PixelColor::Black && 
                img.RT(path.CurX(), path.CurY()) == PixelColor::White;
        default:
            throw logic_error("Unknown direction");
        }
    }

}
}
