#include <iostream>
#include <vector>
using namespace std;

void printConfiguration(int colorArray[], int V) {
    cout << "\nThe assigned colors are as follows:" << endl;
    for (int i = 0; i < V; i++)
        cout << "Vertex: " << i + 1 << " Color: " << colorArray[i] << endl;
}

bool isSafe(vector<vector<int>>& graph, int colorArray[], int vertex, int c) {
    for (int i = 0; i < graph.size(); i++)
        if (graph[vertex][i] && colorArray[i] == c)
            return false;
    return true;
}

bool graphColoringAlgorithm(vector<vector<int>>& graph, int m, int vertex, int colorArray[]) {
    if (vertex == graph.size()) {
        if (isSafe(graph, colorArray, vertex - 1, colorArray[vertex - 1])) {
            printConfiguration(colorArray, graph.size());
            return true;
        }
        return false;
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(graph, colorArray, vertex, c)) {
            colorArray[vertex] = c;
            if (graphColoringAlgorithm(graph, m, vertex + 1, colorArray))
                return true;

            colorArray[vertex] = 0;
        }
    }
    return false;
}

int main() {
    // Take user input for the number of vertices
    int V;
    cout<<endl;
    cout << "Enter the number of vertices: ";
    cin >> V;

    int th;
    cout << "Enter the threshold distance: ";
    cin >> th;
    cout<<endl;

    // Take user input for distances matrix
    vector<vector<int>> distances(V, vector<int>(V, 0));
    cout << "Enter the distances matrix (" << V << "x" << V << "):" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if(i == j){
                distances[i][j] = 0;
            } else{
                cout << "Distance from Vertex " << i + 1 << " to " << j + 1 << ": ";
                cin >> distances[i][j];
            }
        }
    }

    // Print the distance matrix table
    cout << "\nDistance Matrix:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cout << distances[i][j] << "\t";
        }
        cout << endl;
    }

    // Generate the graph based on distances
    vector<vector<int>> graph(V, vector<int>(V, 0));
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && distances[i][j] <= th) {
                graph[i][j] = 1;
            }
        }
    }

    int colorArray[V];
    for (int i = 0; i < V; i++)
        colorArray[i] = 0;

    for (int i = 1; i <= V; i++)
        if (graphColoringAlgorithm(graph, i, 0, colorArray)) {
            cout << "\nMinimum number of channels needed: " << i << endl;
            break;
        }

    return 0;
}
