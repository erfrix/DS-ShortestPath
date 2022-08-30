#include<iostream>
#include<vector>
#include<list>

using namespace std;

int V = 16; //Number of Vertecies
float FLOAT_MAX = 10000.0; //Infinity

//Prints the path using "parents"
void printPath(int currentVertex, int parents[]) {

    if (currentVertex == -1) {
        return;
    }
    printPath(parents[currentVertex], parents);
    cout << currentVertex << " ";
}

//Prints the solution
void printSolution(int s, float dist[], int parents[]) {
    cout << "\n";
    cout << s << " -> " << 15;
    cout << "\t Distance: " << dist[15];
    cout << "\t Path: ";
    printPath(15, parents);
    cout << endl;

    //Shortest Path For All Vertecies
    // for (int vertexIndex = 0; vertexIndex < V; vertexIndex++) 
    // {
    //     if (vertexIndex != s) {
    //         cout << "\n" << s << " -> ";
    //         cout << vertexIndex << "\t Distance: ";
    //         cout << dist[vertexIndex] << "\t Path: ";
    //         printPath(vertexIndex, parents);
    //     }
    // }

}

//Adds an edge to to adjecancy list - its a pair list u -> v with weight*multiply
void addEdge(list < pair < int, float > > * al, int u, int v, float w, int multiply) {
    al[u].push_back(make_pair(v, (w * multiply)));
}

//Finds nearest index in graph from a node
int nearest(float dist[], bool visited[]) {
    float shortestDist = FLOAT_MAX, nearestIndex = 0;

    for (int i = 0; i < V; i++)
        if (dist[i] <= shortestDist && visited[i] == false) {
            shortestDist = dist[i];
            nearestIndex = i;
        }

    return nearestIndex;
}

//Dijkstra Algorithm
void dijkstra(list < pair < int, float > > * al, int s) {
    float dist[V]; //Shortest Distance From Starting Node
    bool visited[V] = {}; // Visisted Nodes
    int parents[V]; //For Printing The Shortest Path

    for (int i = 0; i < V; i++) //Set all distances to INFINITY
        dist[i] = FLOAT_MAX;

    dist[s] = 0.0; //Distance to self is 0
    parents[s] = -1; //Starting node has no parents

    //Main Alogrithm - Dijikstra
    for (int i = 0; i < V - 1; i++) {
        int u = nearest(dist, visited);
        visited[u] = true;

        int vertexIndex = 0;
        for (list < pair < int, float > > ::iterator it = al[u].begin(); it != al[u].end(); it++)
            if (visited[it -> first] == false && dist[u] != FLOAT_MAX && dist[it -> first] > dist[u] + it -> second) {
                parents[it -> first] = u;
                dist[it -> first] = dist[u] + it -> second;
            }

    }

    printSolution(s, dist, parents);

}

int main() {
    list < pair < int, float > > * al = new list < pair < int, float > > [V];
    addEdge(al, 0, 1, 0.2, 1);
    addEdge(al, 0, 2, 0.2, 1);
    addEdge(al, 0, 3, 0.2, 3);
    addEdge(al, 1, 0, 0.2, 1);
    addEdge(al, 1, 2, 1.4, 2);
    addEdge(al, 1, 3, 1.3, 3);
    addEdge(al, 2, 0, 0.2, 1);
    addEdge(al, 2, 1, 1.4, 2);
    addEdge(al, 2, 3, 0.2, 2);
    addEdge(al, 2, 6, 2.4, 2);
    addEdge(al, 3, 0, 0.2, 3);
    addEdge(al, 3, 1, 1.3, 3);
    addEdge(al, 3, 2, 0.2, 2);
    addEdge(al, 3, 4, 1.9, 2);
    addEdge(al, 3, 5, 2.1, 3);
    addEdge(al, 4, 3, 1.9, 2);
    addEdge(al, 4, 5, 2, 1);
    addEdge(al, 5, 3, 2.1, 3);
    addEdge(al, 5, 4, 2, 1);
    addEdge(al, 5, 6, 1.9, 2);
    addEdge(al, 5, 7, 0.1, 3);
    addEdge(al, 6, 2, 2.4, 2);
    addEdge(al, 6, 5, 1.9, 2);
    addEdge(al, 6, 8, 3, 3);
    addEdge(al, 7, 5, 0.1, 3);
    addEdge(al, 7, 8, 0.1, 1);
    addEdge(al, 7, 9, 0.1, 2);
    addEdge(al, 7, 13, 3.5, 2);
    addEdge(al, 8, 6, 3, 3);
    addEdge(al, 8, 7, 0.1, 1);
    addEdge(al, 8, 14, 4.1, 2);
    addEdge(al, 9, 7, 0.1, 2);
    addEdge(al, 9, 10, 1.1, 1);
    addEdge(al, 9, 12, 2, 1);
    addEdge(al, 10, 9, 1.1, 1);
    addEdge(al, 10, 11, 1.8, 2);
    addEdge(al, 11, 10, 1.8, 2);
    addEdge(al, 11, 12, 0.6, 3);
    addEdge(al, 12, 9, 2, 1);
    addEdge(al, 12, 11, 0.6, 3);
    addEdge(al, 12, 13, 0.8, 3);
    addEdge(al, 12, 15, 0.2, 1);
    addEdge(al, 13, 7, 3.5, 2);
    addEdge(al, 13, 12, 0.8, 3);
    addEdge(al, 13, 14, 1.2, 3);
    addEdge(al, 14, 8, 4.1, 2);
    addEdge(al, 14, 13, 1.2, 3);
    addEdge(al, 15, 12, 0.2, 1);

    dijkstra(al, 0);
}