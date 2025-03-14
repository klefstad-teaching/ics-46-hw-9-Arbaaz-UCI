#include "dijkstras.h"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph-filename>" << endl;
        return 1;
    }
    string filename = argv[1];
    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const runtime_error& e) {
        cerr << "Error reading graph file: " << e.what() << endl;
        return 1;
    }
    int source = 0;
    if (G.numVertices <= source) {
        cerr << "Graph has no vertices; cannot run Dijkstra." << endl;
        return 1;
    }
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    for (int v = 0; v < G.numVertices; ++v) {
        vector<int> path = extract_shortest_path(distances, previous, v);
        if (!path.empty()) {
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) cout << " ";
            }
            cout << endl;
        } else {
            if (v == source) {
                cout << source << endl;
            } else {
                cout << "No path to vertex " << v << endl;
            }
        }
        cout << "Total cost is ";
        if (distances[v] == INF) {
            cout << "INF" << endl;
        } else {
            cout << distances[v] << endl;
        }
    }
    return 0;
}
