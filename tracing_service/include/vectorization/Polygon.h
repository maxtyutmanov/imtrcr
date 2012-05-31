#ifndef VECTORIZATION_POLYGON_H
#define VECTORIZATION_POLYGON_H

#include <vectorization/PotracePath.h>
#include <vector>

namespace ImTrcr {
namespace Vectorization {

    class Polygon {
    public:
        //TODO: we shouldn't pass pointer to path object here. Passing pointer usually means
        //passing ownership of object, but it's not out case

        template <typename TCollection>
        Polygon(const PotracePath* path, const TCollection& c) 
            : path(path), verticesIndices(c.begin(), c.end()) { }

        void AddVertex(int vertexIndex);
        const std::vector<int>& GetVerticesIndices() const;
        int GetVertexCount() const;

        const Point2& operator[](size_t index) const;

        //is polygon white
        bool IsInverted() const;
        
    private:
        std::vector<int> verticesIndices;
        const PotracePath* path;
    };

}
}

#endif