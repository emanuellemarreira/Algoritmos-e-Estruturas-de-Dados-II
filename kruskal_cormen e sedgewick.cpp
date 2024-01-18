#include <iostream>
#include <vector>
#include <list>
#include <algorithm> //pro sort, TEMPORARIOOOOOOOOOOOOOOOOOOOOOOOOO
using namespace std;

// Implementação de um grafo ponderado
// utilizando lista de adjacência

typedef unsigned int Vertex;
typedef float Weight;

class Edge{
    public:
        Vertex vertex1; //faz conexoes uv
        Vertex vertex2;
        Weight weight;
        Edge() {}
        Edge(Vertex vertex1, Vertex vertex2, Weight weight) : vertex1(vertex1), vertex2(vertex2),weight(weight){};
};

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
    vector<VertexWeightPair> vertices;
    vector<Edge> edges;
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
    vector<VertexWeightPair> return_vertices(){ return vertices; }
    vector<Edge> return_edges(){ return edges; }
    void get_vertices()
    {
        for (auto item : vertices)
        {
            cout << "("<< item.vertex << " , " << item.weight<<")";
        }
        cout << endl;
    }
    void get_edges(){
        for (auto item : edges){
            cout << "("<< item.vertex1 << " , " << item.vertex2<<" , "<< item.weight<<" ) ";
        }
    }
};

template <typename T>
class UnionFind
{
private:
    vector<Vertex> id;
    unsigned int count; // numero de componentes
public:
    UnionFind(int N) : id(N), count(N)
    {
        // for(unsigned int i = 0; i < N; i++){
        //   id[i] = i;  //todo identificador do conjunto no início é ele mesmo
        //}
    }

    void makeSet(WeightedGraphAL<VertexWeightPair> &g) //tem o argumento T v
    {
        ///id[v] = v;
        for(unsigned int i = 0; i < g.get_num_vertices(); i++){
            id[i] = i;  //todo identificador do conjunto no início é ele mesmo
        }
    }

    // quick find
    Vertex find(Vertex p)
    {
        return id[p];
    }
    void unionf(Vertex p, Vertex q)
    {
        Vertex pID = find(p);
        Vertex qID = find(q);
        if (pID == qID)
        {
            return; // ja estao no mesmo componente
        }
        for (unsigned int i = 0; i < id.size(); i++)
        {
            if (id[i] == pID)
            {
                id[i] = qID;
            }
        }
        count--;
    }
    bool connected(Vertex p, Vertex q)
    {
        return find(p) == find(q); // se id sao iguais sao do mesmo conjunto logo estao conectados
    }

    static bool compareByWeight(const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    }

    vector<Edge> Kruskal(WeightedGraphAL<VertexWeightPair> &g)
    {
        vector<Edge> A;
        vector<Edge> vector_edges = g.return_edges();
        //for(auto v : vector_vertices){
        makeSet(g); //fazendo o makeset pra todos como era no construtor, era pra enviar v por v
        //}
        sort(vector_edges.begin(), vector_edges.end(), compareByWeight);
        //for (auto item : vector_edges){
           // cout << "("<< item.vertex1 << " , " << item.vertex2<<" , "<< item.weight<<" ) ";
        //}
        for (auto item : vector_edges){
            //cout << "fora = " << item.vertex1 <<", "<< item.vertex2 << " / "<<id[item.vertex1] << ", " << id[item.vertex2] << ": " <<connected(item.vertex1, item.vertex2)<<endl;
            if (find(item.vertex1) != find(item.vertex2)){
                A.push_back(item);
                unionf(item.vertex1, item.vertex2);
                //cout << "dentro = " << item.vertex1 <<", "<< item.vertex2 << " / "<<id[item.vertex1] << ", " << id[item.vertex2] << ": " <<connected(item.vertex1, item.vertex2)<<endl;
            }
        }
        return A;
    }
};


template <typename T>
WeightedGraphAL<T>::WeightedGraphAL(unsigned int num_vertices) : num_vertices(num_vertices)
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
    int flag1 = 0, flag2 = 0;
    int flag3 = 0, flag4 = 0;
    if (vertex_already_exists(u, v) == false)
    {
        adj[u].push_back(item_Vertex_v);
        flag3 = 1;
    }
    if (vertex_already_exists(v, u) == false)
    {
        adj[v].push_back(item_Vertex_u);
        flag4 = 1;
    }

    if(flag3 == 1 && flag4 == 1){
        Edge uv{u, v, weight};
        edges.push_back(uv);
    }

    for (auto itr = vertices.begin(); itr != vertices.end(); ++itr)
    {
        if (itr->vertex == item_Vertex_v.vertex)
        {
            flag1 = 1;
        }
        if (itr->vertex == item_Vertex_u.vertex)
        {
            flag2 = 1;
        }
    }
    if (flag1 == 0)
    {
        vertices.push_back(item_Vertex_v);
    }
    if (flag2 == 0)
    {
        vertices.push_back(item_Vertex_u);
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
    for (auto itr = vertices.begin(); itr != vertices.end(); ++itr)
    {
        if (get_adj(item_Vertex_v.vertex).empty())
        {
            itr = vertices.erase(itr);
        }
        if (get_adj(item_Vertex_u.vertex).empty())
        {
            itr = vertices.erase(itr);
        }
    }

    for (auto itr2 = edges.begin(); itr2 != edges.end(); ++itr2)
    {
        if (itr2->vertex1 == item_Vertex_u.vertex || itr2->vertex1 == item_Vertex_v.vertex)
        {
            itr2 = edges.erase(itr2);
        }
    }
    for (auto itr2 = edges.begin(); itr2 != edges.end(); ++itr2)
    {
        if (itr2->vertex2 == item_Vertex_u.vertex || itr2->vertex2 == item_Vertex_v.vertex)
        {
            itr2 = edges.erase(itr2);
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
    //display_WeightedGraphAL(g);
    //g.get_edges();
    UnionFind<VertexWeightPair> uf(num_vertices);
    vector<Edge> result = uf.Kruskal(g);
    for (auto item : result) {
        cout << "(" << item.vertex1 << " , " << item.vertex2 << " , " << item.weight << " ) " << endl;
    }
    return 0;
}