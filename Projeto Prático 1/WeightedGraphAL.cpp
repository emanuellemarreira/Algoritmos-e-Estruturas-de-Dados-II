#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Implementação de um grafo ponderado
// utilizando lista de adjacência

typedef unsigned int Vertex;
typedef float Weight;

class VertexWeightPair
{
public:
    Vertex vertex;
    Weight weight;
    VertexWeightPair() {}
    VertexWeightPair(Vertex vertex) : vertex(vertex), weight(0.0f){};
    VertexWeightPair(Vertex vertex, Weight weight) : vertex(vertex), weight(weight){};
};

template <typename T>
class WeightedGraphAL
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj;

public:
    WeightedGraphAL(unsigned int);
    ~WeightedGraphAL();
    void add_edge(Vertex, Vertex, Weight);
    bool vertex_already_exists(Vertex u, Vertex v);
    void remove_edge(Vertex, Vertex);
    unsigned int get_num_vertices() { return num_vertices; }
    unsigned int get_num_edges() { return num_edges; }
    list<T> get_adj(Vertex v) { return adj[v]; }
};

template <typename T>
WeightedGraphAL<T>::WeightedGraphAL(unsigned int num_vertices) : num_vertices(num_vertices), num_edges(0)
{
    adj = new list<VertexWeightPair>[num_vertices];
}
template <typename T>
WeightedGraphAL<T>::~WeightedGraphAL()
{
    for (unsigned int u = 0; u < num_vertices; ++u)
    {
        adj[u].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_edges = 0;
    num_vertices = 0;
}

template <typename T>
void WeightedGraphAL<T>::add_edge(Vertex u, Vertex v, Weight weight)
{
    VertexWeightPair item_Vertex_v{v, weight};
    VertexWeightPair item_Vertex_u{u, weight};
    if (vertex_already_exists(u, v) == false)
    {
        adj[u].push_back(item_Vertex_v);
    }
    if (vertex_already_exists(v, u) == false)
    {
        adj[v].push_back(item_Vertex_u);
    }
    num_edges++;
}

template <typename T>
bool WeightedGraphAL<T>::vertex_already_exists(Vertex u, Vertex v)
{
    VertexWeightPair item_Vertex_u{u};
    VertexWeightPair item_Vertex_v{v};
    list<VertexWeightPair> &lista_u = adj[u];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->vertex == item_Vertex_v.vertex)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void WeightedGraphAL<T>::remove_edge(Vertex u, Vertex v)
{
    VertexWeightPair item_Vertex_v{v};
    VertexWeightPair item_Vertex_u{u};
    list<VertexWeightPair> &lista_u = adj[u];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->vertex == item_Vertex_v.vertex)
        {
            itr = lista_u.erase(itr);
        }
    }
    list<VertexWeightPair> &lista_v = adj[v];
    for (auto itr2 = lista_v.begin(); itr2 != lista_v.end(); ++itr2)
    {
        if (itr2->vertex == item_Vertex_u.vertex)
        {
            itr2 = lista_v.erase(itr2);
        }
    }
    num_edges--;
}

template <typename T>
void input_WeightedGraphAL(WeightedGraphAL<T> &g, unsigned int num_edges)
{
    Vertex u = 0;
    Vertex v = 0;
    Weight weight = 0;
    for (unsigned int i = 0; i < num_edges; ++i)
    {
        cin >> u >> v >> weight;
        g.add_edge(u, v, weight);
    }
}
template <typename T>
void display_list(list<T> &lst)
{
    for (auto item_Vertex : lst)
    {
        cout << "(" << item_Vertex.vertex << ", " << item_Vertex.weight << "), ";
    }
    cout << endl;
}
template <typename T>
void display_WeightedGraphAL(WeightedGraphAL<T> &g)
{
    for (unsigned int v = 0; v < g.get_num_vertices(); v++)
    {
        cout << v << ": ";
        list<T> lst = g.get_adj(v);
        display_list(lst);
    }
}
int main()
{
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    WeightedGraphAL<VertexWeightPair> g{num_vertices};
    input_WeightedGraphAL(g, num_edges);
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;
    display_WeightedGraphAL(g);
    return 0;
}