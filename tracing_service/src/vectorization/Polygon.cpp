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

    const Point2& Polygon::operator[](size_t index) const {
        if (index < 0 || index >= GetVertexCount()) {
            throw logic_error("Index of vertex is out of range");
        }

        return path->GetPoints()[verticesIndices[index]];
    }

    bool Polygon::IsInverted() const {
        return path->IsInverted();
    }
}
}