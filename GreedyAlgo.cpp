#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

class Graph
{
    int V;               // No. of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix with weights

public:
    Graph(int V);
    void addEdge(int v, int w, int weight);
    void greedyColoring();
};

Graph::Graph(int V)
{
    this->V = V;
    adjMatrix.resize(V, vector<int>(V, 0)); // Initialize adjacency matrix with zeros
}

void Graph::addEdge(int v, int w, int weight)
{
    if (weight <= 150) // Only connect edges with distances equal to or less than 150
    {
        adjMatrix[v][w] = weight;
        adjMatrix[w][v] = weight; // Since the graph is undirected
    }
}

void Graph::greedyColoring()
{
    vector<int> result(V, -1); // Color assignment for each vertex

    // Assign colors to the vertices
    for (int u = 0; u < V; u++)
    {
        vector<bool> availableColors(V, true);

        // Process all adjacent vertices and flag their colors as unavailable
        for (int v = 0; v < V; v++)
        {
            if (adjMatrix[u][v] > 0 && result[v] != -1)
            {
                availableColors[result[v]] = false;
            }
        }

        // Find the first available color
        auto colorIt = find(availableColors.begin(), availableColors.end(), true);
        if (colorIt != availableColors.end())
        {
            result[u] = distance(availableColors.begin(), colorIt);
        }
    }

    // Print the result
    for (int u = 0; u < V; u++)
    {
        cout << "Vertex " << u << " ---> Color " << result[u] + 1 << endl; // Adding 1 because colors start from 1
    }

    // Find the number of colors used
    int numColors = *max_element(result.begin(), result.end()) + 1;
    cout << "Number of colors used: " << numColors << endl;
}

int main()
{
    Graph g(6);

    g.addEdge(0, 1, 85);
    g.addEdge(0, 2, 175);
    g.addEdge(0, 3, 200);
    g.addEdge(0, 4, 50);
    g.addEdge(0, 5, 100);

    g.addEdge(1, 2, 125);
    g.addEdge(1, 3, 175);
    g.addEdge(1, 4, 100);
    g.addEdge(1, 5, 160);

    g.addEdge(2, 3, 100);
    g.addEdge(2, 4, 200);
    g.addEdge(2, 5, 250);

    g.addEdge(3, 4, 210);
    g.addEdge(3, 5, 220);

    g.addEdge(4, 5, 100);

    cout << "Coloring of the graph \n";
    g.greedyColoring();

    return 0;
}
