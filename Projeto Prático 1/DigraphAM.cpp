#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <iomanip>
using namespace std;

// implementação de grafo direcionado utilizando matriz de adjacência
typedef unsigned int Vertex;
typedef unsigned int Weight;

template <typename T>
class Edge
{
public:
    T weight;
    Edge() : weight(0) {}
    Edge(T _weight) : weight(_weight) {}
};

template <typename T>
class DigraphAM
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    Edge<T> **adj;

public:
    DigraphAM(unsigned int);
    ~DigraphAM();
    int add_edge(Vertex, Vertex);
    list<Vertex> get_adj(Vertex);
    T get_weight_edge(Vertex, Vertex);
    void remove_edge(Vertex, Vertex);
    unsigned int get_num_vertices();
    unsigned int get_num_edges();
};

template <typename T>
unsigned int DigraphAM<T>::get_num_vertices()
{
    return num_vertices;
}

template <typename T>
unsigned int DigraphAM<T>::get_num_edges()
{
    return num_edges;
}

template <typename T>
DigraphAM<T>::DigraphAM(unsigned int _num_vertices) : num_vertices(_num_vertices),
                                                  num_edges(0)
{
    const unsigned int LINHAS = num_vertices;
    const unsigned int COLUNAS = num_vertices;
    adj = new Edge<T> *[LINHAS];
    for (int i = 0; i < LINHAS; ++i)
    {
        adj[i] = new Edge<T>[COLUNAS];
    }
}

template <typename T>
void DigraphAM<T>::remove_edge(Vertex u, Vertex v)
{
    Edge<T> edge{0};
    adj[u][v] = edge;
    num_edges--;
}

template <typename T>
DigraphAM<T>::~DigraphAM()
{
    const unsigned int LINHAS = num_vertices;
    for (int i = 0; i < LINHAS; ++i)
    {
        delete[] adj[i];
    }
    delete[] adj;
}

template <typename T>
int DigraphAM<T>::add_edge(Vertex u, Vertex v)
{
    if (adj[u][v].weight == 0)
    {
        Edge<T> edge{1};
        adj[u][v] = edge;
        num_edges++;
        return 0;
    }
    return -1;
}

template <typename T>
std::list<Vertex> DigraphAM<T>::get_adj(Vertex u)
{
    std::list<Vertex> values;
    for (int v = 0; v < num_vertices; ++v)
    {
        if (adj[u][v].weight != 0)
        {
            values.push_back(v);
        }
    }
    return values;
}

template <typename T>
T DigraphAM<T>::get_weight_edge(Vertex u, Vertex v)
{
    return adj[u][v].weight;
}

template <typename T>
void display_matadj_graph(DigraphAM<T> &g)
{
    int k = 0;

    for (unsigned int i = 0; i < g.get_num_vertices(); i++)
    {
        cout << g.get_weight_edge(i, 0) << " ";
        for (unsigned int j = 1; j < g.get_num_vertices(); j++)
        {
            cout << g.get_weight_edge(i, j)<< " ";
        }
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    unsigned int num_vertices;
    unsigned int num_edges;

    cin >> num_vertices;
    cin >> num_edges;


    DigraphAM<Weight> g{num_vertices};

    for (unsigned int i = 0; i < num_edges; ++i)
    {
        Vertex u, v;
        cin >> u >> v;
        num_edges += g.add_edge(u, v);
    }
    cout << "num_vertices: " << num_vertices << endl;
    cout << "num_edges: " << num_edges << endl;
    display_matadj_graph(g);

    return 0;
}
