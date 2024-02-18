#include <iostream>
#include <vector>
#include <list>
#include <limits>

const float inf = std::numeric_limits<float>::infinity();

using namespace std;

class Vertex
{
public:
    int index;
    char col;
    int row;
    int cor;
    float d;
    Vertex *pi;

    Vertex(int idx, char c, int r, int cor, float d, Vertex *pi) : index(idx), col(c), row(r), cor(cor), d(d), pi(pi) {}
    Vertex(int index) : index(index) {}
};

template <typename T>
class Graph
{
public:
    vector<list<T>> adjacencyList;

    Graph(unsigned int size) : adjacencyList(size) {}

    void addEdge(Vertex &u, Vertex &v);
};

template <typename T>
class Queue
{
private:
    std::list<T> list;

public:
    Queue() {}
    void enqueue(T item) { list.push_back(item); }
    T dequeue()
    {
        T front = list.front();
        list.pop_front();
        return front;
    }
    bool isEmpty() { return list.empty(); }
};

template <typename T>
void Graph<T>::addEdge(Vertex &u, Vertex &v)
{
    adjacencyList[u.index].push_back(v);
}

template <typename T>
void createKnightGraph(Graph<T> &graph)
{

    int list1[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int list2[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int row = 1; row <= 8; ++row)
    {
        for (int col = 1; col <= 8; ++col)
        {
            int uIndex = (row - 1) * 8 + col;

            Vertex u(uIndex, 'A' + col - 1, row, 0, inf, nullptr);

            for (int i = 0; i < 8; i += 1)
            {
                int newRow = row + list1[i];
                int newCol = col + list2[i];

                if (newRow >= 1 && newRow <= 8 && newCol >= 1 && newCol <= 8)
                {
                    int vIndex = (newRow - 1) * 8 + newCol;
                    Vertex v(vIndex, 'A' + newCol - 1, newRow, 0, inf, nullptr);
                    graph.addEdge(u, v);
                }
            }
        }
    }
}

template <typename T>
float BFS(Graph<T> &graph, Vertex s, Vertex king)
{
    for (auto &lista : graph.adjacencyList)
    {
        for (auto &vertice : lista)
        {
            vertice.cor = 0;
            vertice.d = inf;
            vertice.pi = nullptr;
        }
    }
    s.cor = 1;
    s.d = 0;
    s.pi = nullptr;
    for (const Vertex &adjKing : graph.adjacencyList[king.index])
    {
        if (s.index == adjKing.index)
        {
            return s.d;
        }
    }
    Queue<Vertex> queue;
    queue.enqueue(s);
    while (!queue.isEmpty())
    {
        Vertex u = queue.dequeue();
        for (Vertex &v : graph.adjacencyList[u.index])
        {
            if (v.cor == 0)
            {
                v.cor = 1;
                v.d = u.d + 1;
                v.pi = &u;
                queue.enqueue(v);
                for (Vertex &adjKing : graph.adjacencyList[king.index])
                {
                    if (v.index == adjKing.index)
                    {
                        return v.d;
                    }
                }
            }
        }
        u.cor = 2;
    }
    return 0;
}

int getIndex(char letter, char number)
{
    int col = letter - 32;
    int row = number - '0';
    int index = (row - 1) * 8 + (col - 'A') + 1;
    return index;
}

int main()
{
    Graph<Vertex> Board(65);

    createKnightGraph(Board);

    int iterations;
    cin >> iterations;

    char input[20];
    vector<float> vectorShortestPaths;
    vector<vector<float>> allShortestPaths;

    for (int i = 0; i < iterations; i++)
    {
        int countShortestPath = 1;
        int shortestPath = 64;
        for (int i = 0; i < 10; i++)
        {
            cin >> input[i];
        }
        for (int i = 0; i < 8; i += 2)
        {
            int Knight = getIndex(input[i], input[i + 1]);
            int King = getIndex(input[8], input[9]);

            Vertex knight(Knight);
            Vertex king(King);
            float movements = BFS(Board, knight, king);
            if (movements < shortestPath)
            {
                shortestPath = movements;
                countShortestPath = 1;
            }
            if (movements == shortestPath)
            {
                countShortestPath += 1;
            }
        }
        for (int i = 1; i < countShortestPath; i += 1)
        {
            vectorShortestPaths.push_back(shortestPath);
        }
        allShortestPaths.push_back(vectorShortestPaths);
        vectorShortestPaths.clear();
    }
    for (auto &caminhos : allShortestPaths)
    {
        for (float caminho : caminhos)
        {
            cout << caminho << " ";
        }
        cout << endl;
    }
    return 0;
}
