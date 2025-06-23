#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
using namespace std;

class Graph
{
private:
    int V;
    vector<vector<int>> adjMatrix;
    vector<list<int>> adjList;

public:
    Graph(int vertices)
    {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
        adjList.resize(V);
    }

    void addEdge(int src, int dest)
    {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1;

        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void printAdjMatrix()
    {
        cout << "Adjacency Matrix:" << endl;
        cout << "  ";
        for (int i = 0; i < V; i++)
        {
            cout << i << " ";
        }
        cout << endl;

        for (int i = 0; i < V; i++)
        {
            cout << i << " ";
            for (int j = 0; j < V; j++)
            {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void printAdjList()
    {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < V; i++)
        {
            cout << i << " -> ";
            for (auto neighbor : adjList[i])
            {
                cout << neighbor << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void BFS(int startVertex)
    {
        cout << "BFS Traversal starting from vertex " << startVertex << ": ";
        vector<bool> visited(V, false);
        queue<int> q;
        visited[startVertex] = true;
        q.push(startVertex);
        while (!q.empty())
        {
            int currentVertex = q.front();
            cout << currentVertex << " ";
            q.pop();
            for (auto neighbor : adjList[currentVertex])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    void DFS(int startVertex)
    {
        cout << "DFS Traversal starting from vertex " << startVertex << ": ";
        vector<bool> visited(V, false);
        DFSRecursive(startVertex, visited);
        cout << endl;
    }

    void DFSRecursive(int vertex, vector<bool> &visited)
    {
        visited[vertex] = true;
        cout << vertex << " ";
        for (auto neighbor : adjList[vertex])
        {
            if (!visited[neighbor])
            {
                DFSRecursive(neighbor, visited);
            }
        }
    }

    bool isConnected()
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[0] = true;
        q.push(0);
        while (!q.empty())
        {
            int currentVertex = q.front();
            q.pop();
            for (auto neighbor : adjList[currentVertex])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                return false;
            }
        }
        return true;
    }

    int getVertices() const
    {
        return V;
    }
};

int main()
{
    cout << "=== Graph Implementation with Adjacency Matrix & List ===" << endl;
    cout << "Features: addEdge(), BFS, DFS (recursive & iterative)" << endl
         << endl;
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    g.printAdjMatrix();
    g.printAdjList();

    g.BFS(0);
    g.BFS(2);
    g.DFS(0);
    g.DFS(2);

    cout << "Is the graph connected? " << (g.isConnected() ? "Yes" : "No") << endl;

    cout << "\n=== Additional Test Cases ===" << endl;
    Graph g2(5);

    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(3, 4);

    cout << "\nDisconnected Graph:" << endl;
    g2.printAdjMatrix();
    g2.printAdjList();

    cout << "BFS from vertex 0: ";
    g2.BFS(0);

    cout << "DFS from vertex 0: ";
    g2.DFS(0);

    cout << "Is the graph connected? " << (g2.isConnected() ? "Yes" : "No") << endl;
    return 0;
}
