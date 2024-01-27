#include <iostream>
#include <vector>
#include <list>
#include <limits>

using namespace std;

const float inf = std::numeric_limits<float>::infinity();

typedef unsigned int Vertex;
typedef float Weight;

class Edge
{
public:
    Vertex vertex1;
    Vertex vertex2;
    Weight weight;
    Edge() {}
    Edge(Vertex vertex1, Vertex vertex2, Weight weight) : vertex1(vertex1), vertex2(vertex2), weight(weight){};
};

class NeuronEdge
{
public:
    Vertex vertex1;
    Vertex vertex2;
    Weight weight;
    bool vertex1_isSick;
    bool vertex2_isSick;
    NeuronEdge() {}
    NeuronEdge(Vertex vertex1, Vertex vertex2, Weight weight, bool vertex1_isSick, bool vertex2_isSick) : vertex1(vertex1), vertex2(vertex2), weight(weight), vertex1_isSick(vertex1_isSick), vertex2_isSick(vertex2_isSick){};
};

class NeuronBlock
{
public:
    Vertex vertex;
    Weight weight;
    float distance;
    NeuronBlock *pi;
    vector<NeuronEdge> neuronEdges;

    NeuronBlock() : distance(0), pi(nullptr) {}
    NeuronBlock(Vertex vertex) : vertex(vertex), weight(0.0f), distance(0), pi(nullptr){};
    NeuronBlock(Vertex vertex, Weight weight) : vertex(vertex), weight(weight), distance(0), pi(nullptr){};
};

template <typename T>
class WeightedGraphAL
{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    vector<Edge> edges;
    list<T> *adj;

public:
    vector<NeuronBlock> vertices;
    WeightedGraphAL(unsigned int);
    ~WeightedGraphAL();
    void add_edge(Vertex, Vertex, Weight);
    bool vertex_already_exists(Vertex u, Vertex v);
    void remove_edge(Vertex, Vertex);
    unsigned int get_num_vertices() { return num_vertices; }
    unsigned int get_num_edges() { return num_edges; }
    list<T> get_adj(Vertex v) { return adj[v]; }
    vector<Edge> return_edges() { return edges; }
    vector<NeuronBlock> return_vertices() { return vertices; }
    NeuronBlock getNB(Vertex u)
    {
        return vertices[u];
    }
};

class MinPQ
{
private:
    vector<pair<int, float>> A;
    int heapSize;

public:
    MinPQ(vector<float> &vetor) : heapSize(vetor.size())
    {
        A.resize(vetor.size());
        for (unsigned int i = 0; i < vetor.size(); i++)
        {
            A[i].first = i;
            A[i].second = vetor[i];
        }

        buildMinHeap();
    }
    vector<pair<int, float>> getA()
    {
        return A;
    }
    int returnHeapSize()
    {
        return heapSize;
    }

    int parent(int i)
    {
        return (i) / 2;
    }
    int left(int i)
    {
        return 2 * i;
    }
    int right(int i)
    {
        return 2 * i + 1;
    }
    void minHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heapSize && A[l].second < A[i].second)
            smallest = l;
        if (r < heapSize && A[r].second < A[smallest].second)
            smallest = r;

        if (smallest != i)
        {
            swap(A[i], A[smallest]);
            minHeapify(smallest);
        }
    }

    void buildMinHeap()
    {
        for (int i = (heapSize) / 2; i >= 0; --i)
        {
            minHeapify(i);
        }
    }

    int heapExtractMin()
    {
        int min_val = A[0].first;
        heapSize--;
        A.erase(A.begin());
        minHeapify(0);
        return min_val;
    }

    void heapDecreaseKey(int i, float &key)
    {
        if (key > A[i].second)
        {
            return;
        }
        for (int j = 0; j < heapSize; j++)
        {
            if (A[j].first == i)
            {
                A[j].second = key;
                i = j;
                break;
            }
        }
        while (i > 0 && A[parent(i)].second > A[i].second)
        {
            swap(A[i], A[parent(i)]);
            i = parent(i);
        }
    }
};

void selectionSort(vector<NeuronEdge> &vetor);

class UnionFind
{
private:
    vector<Vertex> id;

public:
    UnionFind(int N) : id(N + 1) {}
    void makeSet(WeightedGraphAL<NeuronBlock> &g)
    {
        for (unsigned int i = 1; i <= g.get_num_vertices(); i++)
        {
            id[i] = i;
        }
    }

    Vertex findSet(Vertex p)
    {
        return id[p];
    }

    void unionf(Vertex p, Vertex q)
    {
        Vertex pID = findSet(p);
        Vertex qID = findSet(q);
        if (pID == qID)
        {
            return;
        }
        for (unsigned int i = 1; i <= id.size(); i++)
        {
            if (id[i] == pID)
            {
                id[i] = qID;
            }
        }
    }

    float Kruskal(WeightedGraphAL<NeuronBlock> &g, vector<NeuronEdge> &block)
    {
        vector<NeuronEdge> A;
        float cont = 0;
        makeSet(g);
        selectionSort(block);
        for (auto neuron : block)
        {
            if (findSet(neuron.vertex1) != findSet(neuron.vertex2))
            {
                A.push_back(neuron);
                unionf(neuron.vertex1, neuron.vertex2);
            }
        }
        for (auto ne : A)
        {
            if (ne.vertex1_isSick || ne.vertex2_isSick)
            {
                for (auto na : A)
                {
                    cont += na.weight;
                }
                break;
            }
        }
        return cont;
    }
};

void selectionSort(vector<NeuronEdge> &vetor)
{
    for (unsigned int i = 0; i < vetor.size(); i++)
    {
        int min = i;
        for (unsigned int j = i; j < vetor.size(); j++)
        {
            if (vetor[j].weight < vetor[min].weight)
            {
                min = j;
            }
        }
        NeuronEdge tmp = vetor[i];
        vetor[i] = vetor[min];
        vetor[min] = tmp;
    }
}

template <typename T>
WeightedGraphAL<T>::WeightedGraphAL(unsigned int num_vertices) : num_vertices(num_vertices)
{
    adj = new list<NeuronBlock>[num_vertices + 1]; 
}

template <typename T>
WeightedGraphAL<T>::~WeightedGraphAL()
{
    for (unsigned int u = 1; u <= num_vertices; ++u)
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
    NeuronBlock item_Vertex_v{v, weight};
    NeuronBlock item_Vertex_u{u, weight};
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

    if (flag3 == 1 && flag4 == 1)
    {
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
    NeuronBlock item_Vertex_u{u};
    NeuronBlock item_Vertex_v{v};
    list<NeuronBlock> &lista_u = adj[u];
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
    NeuronBlock item_Vertex_v{v};
    NeuronBlock item_Vertex_u{u};
    list<NeuronBlock> &lista_u = adj[u];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr)
    {
        if (itr->vertex == item_Vertex_v.vertex)
        {
            itr = lista_u.erase(itr);
        }
    }
    list<NeuronBlock> &lista_v = adj[v];
    for (auto itr2 = lista_v.begin(); itr2 != lista_v.end(); ++itr2)
    {
        if (itr2->vertex == item_Vertex_u.vertex)
        {
            itr2 = lista_v.erase(itr2);
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
    for (unsigned int v = 1; v <= g.get_num_vertices(); v++)
    {
        cout << v << ": ";
        list<T> lst = g.get_adj(v);
        display_list(lst);
    }
}

void inputNeuronBlocks(WeightedGraphAL<NeuronBlock> &g)
{
    unsigned int numVerticesNeuronBlock = 0;
    unsigned int numEdgesNeuronBlock = 0;
    unsigned int numberOfSickNeurons = 0;
    vector<Vertex> sickNeurons;
    Vertex neurons = 0;
    Vertex u = 0, v = 0;
    Weight weight = 0;

    for (auto &item : g.vertices)
    {
        cin >> numVerticesNeuronBlock >> numEdgesNeuronBlock;
        cin >> numberOfSickNeurons;

        sickNeurons.clear();

        if (numberOfSickNeurons > 0)
        {
            for (unsigned int i = 0; i < numberOfSickNeurons && cin >> neurons; ++i)
            {
                sickNeurons.push_back(neurons);
            }
        }

        for (unsigned int i = 0; i < numEdgesNeuronBlock; ++i)
        {
            cin >> u >> v >> weight;

            NeuronEdge ne{u, v, weight, false, false};

            for (unsigned int i = 0; i < sickNeurons.size(); ++i)
            {
                if (sickNeurons[i] == u)
                {
                    ne.vertex1_isSick = true;
                    ne.vertex2_isSick = false;
                }
                else if (sickNeurons[i] == v)
                {
                    ne.vertex1_isSick = false;
                    ne.vertex2_isSick = true;
                }
                else if (sickNeurons[i] == u && sickNeurons[i] == v)
                {
                    ne.vertex1_isSick = true;
                    ne.vertex2_isSick = true;
                }
            }
            item.neuronEdges.push_back(ne);
        }
        sickNeurons.clear();
    }
}

void relax(Vertex u, Vertex v, WeightedGraphAL<NeuronBlock> &G, vector<float> &distance, vector<int> &predecessores, MinPQ &pq)
{
    for (auto &w : G.return_edges())
    {
        if ((w.vertex1 == u && w.vertex2 == v) || (w.vertex2 == u && w.vertex1 == v))
        {
            if (distance[v] > (distance[u] + w.weight))
            {
                distance[v] = distance[u] + w.weight;
                predecessores[v] = u;
                pq.heapDecreaseKey(v, distance[v]);
            }
        }
    }
}
vector<int> dijkstra(WeightedGraphAL<NeuronBlock> &G, NeuronBlock s)
{
    vector<float> distance;
    distance.resize(G.get_num_vertices() + 1);
    vector<int> predecessores;
    predecessores.resize(G.get_num_vertices() + 1);

    for (unsigned int i = 0; i <= G.get_num_vertices(); i++)
    {
        if (i == s.vertex)
        {
            distance[i] = 0;
            predecessores[i] = -1;
        }
        else
        {
            distance[i] = inf;
            predecessores[i] = -1;
        }
    }

    MinPQ Q(distance);

    while (!Q.getA().empty())
    {
        int u = Q.heapExtractMin();
        if (u != 0)
        {
            for (auto v : G.get_adj(u))
            {
                relax(u, v.vertex, G, distance, predecessores, Q);
            }
        }
        else
        {
            continue;
        }
    }

    return predecessores;
}

int main()
{
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    WeightedGraphAL<NeuronBlock> g{num_vertices};
    input_WeightedGraphAL(g, num_edges);
    unsigned int blocoEntrada;
    int blocoSaida;
    cin >> blocoEntrada >> blocoSaida;
    inputNeuronBlocks(g);
    vector<int> predecessor;
    vector<int> caminho;

    for (auto v : g.vertices)
    {
        if (v.vertex == blocoEntrada)
        {
            predecessor = dijkstra(g, v);
            break;
        }
    }

    while (blocoSaida != -1)
    {
        caminho.push_back(blocoSaida);
        blocoSaida = predecessor[blocoSaida];
    }

    UnionFind uf(num_vertices);
    float acumula = 0;

    for (auto y : caminho)
{
    for (auto x : g.vertices)
    {
        if (x.vertex == static_cast<Vertex>(y))
        {
            acumula += uf.Kruskal(g, x.neuronEdges);
        }
    }
}

    cout << acumula;

    return 0;
}
