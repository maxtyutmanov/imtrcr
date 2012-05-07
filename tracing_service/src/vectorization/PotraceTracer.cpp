#pragma once

#include "vectorization/PotraceTracer.h"
#include <imaging/Path.h>

using namespace ImTrcr::Imaging;
using namespace ImTrcr::Imaging::Primitives;

namespace ImTrcr {
namespace Vectorization {

    Imaging::VectorImage* PotraceTracer::Trace(const Imaging::RasterImage& rasterImage) {
        VectorImage* vectorImage = new VectorImage();

        PathCommand moveTo = PathCommand::MoveToCommand(10, 10.2);
        PathCommand bezier = PathCommand::QuadraticBezierToCommand(20.123, 20, 30.345, 30.1);
        PathCommand close = PathCommand::ClosePathCommand();
        Path* path = new Path(ArgbQuad(0, 0, 0));
        path->AddCommand(moveTo);
        path->AddCommand(bezier);
        path->AddCommand(close);
        vectorImage->AddPrimitive(path);

        moveTo = PathCommand::MoveToCommand(100, 100.2);
        bezier = PathCommand::QuadraticBezierToCommand(200.123, 200, 300.345, 300.1);
        close = PathCommand::ClosePathCommand();
        path = new Path(ArgbQuad(0, 0, 0));
        path->AddCommand(moveTo);
        path->AddCommand(bezier);
        path->AddCommand(close);
        vectorImage->AddPrimitive(path);

        return vectorImage;
    }
}
}
