#include <vectorization/PathDecomposer.h>

using namespace ImTrcr::Imaging;

namespace ImTrcr {
namespace Vectorization {

    void PathDecomposer::FindClosedPaths(TracingContext& ctx) {
        ctx.paths.clear();

        image_size_t height = ctx.potraceImg.GetH();
        image_size_t width = ctx.potraceImg.GetW();
        
        for (image_size_t y = 0; y < height; ++y) {
            for (image_size_t x = 0; x < width; ++x) {
                if (ctx.potraceImg.RB(x, y) == PixelColor::Black) {
                    PotracePath path;
                    path.AddPoint(x, y);
                    path.AddPoint(x, y + 1);    //going to the bottom edge of pixel
                    AugmentPath(ctx.potraceImg, path);
                    DeleteBlackRegion(ctx.potraceImg, path);

                    ctx.paths.push_back(path);
                }
            }
        }
    }

    void PathDecomposer::AugmentPath(const PotraceImage& img, PotracePath& path) {
        //given current and previous point, find a next point. Don't go back

        //if the next point is the starting point of path, we're done
    }

    void PathDecomposer::DeleteBlackRegion(PotraceImage& img, const PotracePath& path) {
        //TODO: implementation
    }

}
}