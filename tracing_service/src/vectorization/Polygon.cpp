#include <vectorization/Polygon.h>

using namespace std;

namespace ImTrcr {
namespace Vectorization {

    void Polygon::AddVertex(int vertexIndex) {
        verticesIndices.push_back(vertexIndex);
    }

    const vector<int>& Polygon::GetVerticesIndices() const {
        return verticesIndices;
    }

    int Polygon::GetVertexCount() const {
        return verticesIndices.size();
    }
}
}