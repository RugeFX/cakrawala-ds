#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
using namespace std;

class Graph
{
private:
    // jumlah vertex
    int V;
    // matrix adjacency menggunakan vector 2 dimensi yang isinya int 0 / 1
    vector<vector<int>> adjMatrix;
    // list adjacency menggunakan vector dari list yang isinya int sesuai dengan hubungan antar vertex
    vector<list<int>> adjList;

public:
    Graph(int vertices)
    {
        V = vertices;
        // nentuin ukuran matrix dan list, matrix diisi sama 0 semua karena belum ada isinya
        adjMatrix.resize(V, vector<int>(V, 0));
        adjList.resize(V);
    }

    void addEdge(int src, int dest)
    {
        // tambahin hubungan antar vertex di matrix, index src ke dest dan dest ke src dijadiin 1
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1;

        // tambahin hubungan di list, tinggal push relasinya ke list
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
        // vector buat nentuin vertex yang sudah dikunjungi
        vector<bool> visited(V, false);
        // queue buat ngejalanin BFS
        queue<int> q;
        // vertex awal otomatis udah dikunjungi
        visited[startVertex] = true;
        // push vertex awal ke queue
        q.push(startVertex);

        while (!q.empty())
        {
            // ambil vertex paling depan dari queue
            int currentVertex = q.front();
            cout << currentVertex << " ";
            // pop vertex dari queue
            q.pop();
            // loop semua vertex yang terhubung sama current
            for (auto neighbor : adjList[currentVertex])
            {
                // kalo belum dikunjungin, bikin visited trus push ke queue
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
        // vector buat nentuin vertex yang sudah dikunjungi
        vector<bool> visited(V, false);
        // panggil fungsi rekursif untuk ngejalanin DFS
        DFSRecursive(startVertex, visited);
        cout << endl;
    }

    void DFSRecursive(int vertex, vector<bool> &visited)
    {
        // buat visited true untuk vertex yang lagi dikunjungi
        visited[vertex] = true;
        cout << vertex << " ";
        // loop semua vertex yang terhubung sama vertex
        for (auto neighbor : adjList[vertex])
        {
            // kalo belum dikunjungin, recursiion lagi
            if (!visited[neighbor])
            {
                DFSRecursive(neighbor, visited);
            }
        }
    }

    bool isConnected()
    {
        // vector buat nentuin vertex yang sudah dikunjungi
        vector<bool> visited(V, false);
        queue<int> q;
        // vertex awal otomatis udah dikunjungi
        visited[0] = true;
        // push vertex awal ke queue
        q.push(0);

        while (!q.empty())
        {
            // ambil vertex paling depan dari queue
            int currentVertex = q.front();
            // pop vertex dari queue
            q.pop();
            // loop semua vertex yang terhubung sama current
            for (auto neighbor : adjList[currentVertex])
            {
                // kalo belum dikunjungin, bikin visited trus push ke queue
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        // loop semua vertex, kalo ada yang belum dikunjungin, berarti graph ga connected
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
