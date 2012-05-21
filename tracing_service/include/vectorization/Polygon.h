#ifndef VECTORIZATION_POLYGON_H
#define VECTORIZATION_POLYGON_H

#include <vectorization/PotracePath.h>
#include <vector>

namespace ImTrcr {
namespace Vectorization {

    class Polygon {
    public:
        Polygon() {};

        template <typename TCollection>
        Polygon(const TCollection& c) 
            : verticesIndices(c.begin(), c.end()) { }

        void AddVertex(int vertexIndex);
        const std::vector<int>& GetVerticesIndices() const;
        int GetVertexCount() const;
    private:
        std::vector<int> verticesIndices;
    };

}
}

#endif