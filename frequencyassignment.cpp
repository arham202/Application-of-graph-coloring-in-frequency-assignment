#include <bits/stdc++.h>
using namespace std;

#define V 6

void printConfiguration(int colorArray[]) {
    cout << "The assigned colors are as follows: " << endl;
    for (int i = 0; i < V; i++)
        cout << "Vertex: " << i+1 << " Color: " << colorArray[i] << endl;
}

bool isSafe(vector<vector<int>>& graph, int colorArray[], int vertex, int c) {
    for (int i = 0; i < V; i++)
        if (graph[vertex][i] && colorArray[i] == c)
            return false;
    return true;
}

bool graphColoringAlgorithm(vector<vector<int>>& graph, int m, int vertex, int colorArray[]) {
    if (vertex == V) {
        if (isSafe(graph, colorArray, vertex - 1, colorArray[vertex - 1])) {
            printConfiguration(colorArray);
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
    vector<vector<int>> distances = {
        {0, 85, 175, 200, 50, 100},
        {85, 0, 125, 175, 100, 160},
        {175, 125, 0, 100, 200, 250},
        {200, 175, 100, 0, 210, 220},
        {50, 100, 200, 210, 0, 100},
        {100, 160, 250, 220, 100, 0}
    };

    vector<vector<int>> graph(6, vector<int>(6, 0));
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (i != j && distances[i][j] <= 150) {
                graph[i][j] = 1;
            }
        }
    }

    int colorArray[V];
    for (int i = 0; i < V; i++)
        colorArray[i] = 0;

    for (int i = 1; i <= V; i++)
        if (graphColoringAlgorithm(graph, i, 0, colorArray)) {
            cout << "Minimum number of channels needed: " << i << endl;
            break;
        }

    return 0;
}
