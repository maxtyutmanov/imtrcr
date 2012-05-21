#include <utils/Graph.h>

#include <queue>
#include <stack>

using namespace std;

namespace ImTrcr {
namespace Utils {

    void GraphUtils::FindShortestCycle(const TwoDimArray<bool>& adjacencyM, std::vector<int>& shortestCycle) {
        const int verticesCount = adjacencyM.GetRowCount();
        
        //TODO: here we suppose that optimal cycle passes through the 0-th point. 
        //Generally it's NOT true

        //no big deal, it's just a BFS (breadth first search)

        //this vector will track vertices that we've already visited
        vector<bool> visited;
        visited.resize(verticesCount, false);
        

        //this vector will form linked list of indices (prev = index of _previous_ vertex of polygon)
        vector<int> prev;
        prev.resize(verticesCount, -1);
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int curPointIndex = q.front();
            visited[curPointIndex] = true;
            q.pop();

            //for each adjacent vertex that hasn't been visited yet
            for (int i = 0; i < verticesCount; ++i) {
                if (adjacencyM.At(curPointIndex, i)) {
                    if (i == 0) {
                        //cycle is closing up

                        GetVerticesListFromPrevList(prev, curPointIndex, shortestCycle);
                        return;
                    }
                    else if (!visited[i]) {
                        //yet another ajacent not visited vertex. Let's add it to the queue of vertices we've got to visit
                        q.push(i);
                        //...and mark it as visited
                        visited[i] = true;
                        //...add note to prev list
                        prev[i] = curPointIndex;
                    }
                }
            }
        }

        throw logic_error("Cannot find cycle in graph");
    }

    void GraphUtils::GetVerticesListFromPrevList(const vector<int>& prevList, const int last, vector<int>& verticesList) {
        //TODO: this copying can be optimized

        //temporary stack
        stack<int> s;
        int curIndex = last;
        while (curIndex != -1) {
            s.push(curIndex);
            curIndex = prevList[curIndex];
        }

        verticesList.clear();
        verticesList.reserve(s.size());

        while (!s.empty()) {
            verticesList.push_back(s.top());
            s.pop();
        }
    }
}
}