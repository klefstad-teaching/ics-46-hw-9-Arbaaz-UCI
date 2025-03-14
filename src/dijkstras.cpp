#include "dijkstras.h"
#include <algorithm>
using namespace std;

struct Node {
    int vertex;
    int dist;
    Node(int v, int d) : vertex(v), dist(d) {}
};

struct NodeGreater {
    bool operator()(const Node& a, const Node& b) const {
        return a.dist > b.dist;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    previous.resize(n, -1);
    priority_queue<Node, vector<Node>, NodeGreater> pq;
    distance[source] = 0;
    pq.push(Node(source, 0));
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u]) continue;
        visited[u] = true;
        for (auto& edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            if (!visited[v] && distance[u] != INF && distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    if (destination < 0 || destination >= (int)distances.size() || distances[destination] == INF) {
        return {};
    }
    vector<int> path;
    int cur = destination;
    while (cur != -1) {
        path.push_back(cur);
        cur = previous[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i + 1 < v.size()) cout << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
