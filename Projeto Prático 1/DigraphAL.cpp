#include <iostream>
#include <vector>
#include <list>
using namespace std;

// Implementação de um Grafo direcionado
// utilizando lista de adjacência

typedef unsigned int Vertex;
class ItemVertex
{
public:
    unsigned int value;
    ItemVertex() {}
    ItemVertex(unsigned int value) : value(value){};
};

template <typename T>
class DigraphAL
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj;

public:
    DigraphAL(unsigned int);
    ~DigraphAL();
    void add_edge(Vertex, Vertex);
    void remove_edge(Vertex, Vertex);
    bool vertex_already_exists(Vertex u, Vertex v);
    list<T> get_adj(Vertex v) { return adj[v]; }
    unsigned int get_num_vertices() { return num_vertices; }
    unsigned int get_num_edges() { return num_edges; }
};

template <typename T>
DigraphAL<T>::DigraphAL(unsigned int num_vertices) : num_vertices(num_vertices), num_edges(0)
{
    adj = new list<ItemVertex>[num_vertices];
}

template <typename T>
DigraphAL<T>::~DigraphAL()
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
void DigraphAL<T>::add_edge(Vertex u, Vertex v)
{
    ItemVertex item_Vertex_v{v};
    ItemVertex item_Vertex_u{u};
    if (vertex_already_exists(u, v) == false && u!=v)
    {
        adj[u].push_back(item_Vertex_v);
        num_edges++;
    }    
}

template <typename T>
void DigraphAL<T>::remove_edge(Vertex u, Vertex v)
{
    ItemVertex item_Vertex_v{v};
    ItemVertex item_Vertex_u{u};
    list<ItemVertex> &lista_u = adj[u];

    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->value == item_Vertex_v.value)
        {
            itr = lista_u.erase(itr);
        }
    }

    num_edges--;
}
template <typename T>
bool DigraphAL<T>::vertex_already_exists(Vertex u, Vertex v)
{
    ItemVertex item_Vertex_u{u};
    ItemVertex item_Vertex_v{v};
    
    list<ItemVertex> &lista_u = adj[u];

    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->value == item_Vertex_v.value)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void input_GraphAL(DigraphAL<T> &g, unsigned int num_edges)
{
    Vertex u = 0;
    Vertex v = 0;
    for (unsigned int i = 0; i < num_edges; ++i)
    {
        cin >> u >> v;
        g.add_edge(u, v);
    }
}

template <typename T>
void display_list(list<T> &lst)
{
    for (auto item_Vertex : lst)
    {
        cout << item_Vertex.value << ", ";
    }
    cout << endl;
}

template <typename T>
void display_GraphAL(DigraphAL<T> &g)
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
    DigraphAL<ItemVertex> g{num_vertices};
    input_GraphAL(g, num_edges);
    cout << "num_vertices: " << g.get_num_vertices() << endl;
    cout << "num_edges: " << g.get_num_edges() << endl;
    display_GraphAL(g);
    return 0;
}