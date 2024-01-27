#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef unsigned int Vertex;
typedef float Weight;

class Edge {
public:
    Vertex vertex1;
    Vertex vertex2;
    Weight weight;
    Edge() {}
    Edge(Vertex vertex1, Vertex vertex2, Weight weight) : vertex1(vertex1), vertex2(vertex2), weight(weight) {};
};

class VertexWeightPair {
public:
    Vertex vertex;
    Weight weight;
    VertexWeightPair() {}
    VertexWeightPair(Vertex vertex) : vertex(vertex), weight(0.0f) {};
    VertexWeightPair(Vertex vertex, Weight weight) : vertex(vertex), weight(weight) {};
};

template <typename T>
class WeightedGraphAL {
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
    vector<VertexWeightPair> return_vertices() { return vertices; }
    vector<Edge> return_edges() { return edges; }
    void get_vertices() {
        for (auto item : vertices) {
            cout << "(" << item.vertex << " , " << item.weight << ")";
        }
        cout << endl;
    }
    void get_edges() {
        for (auto item : edges) {
            cout << "(" << item.vertex1 << " , " << item.vertex2 << " , " << item.weight << " ) ";
        }
    }
};

void selectionSort(vector<Edge> &vetor);

class UnionFind {
private:
    vector<Vertex> id;

public:
    UnionFind(int N) : id(N + 1) {}  // +1 para lidar com os vértices a partir do 1
    void makeSet(WeightedGraphAL<VertexWeightPair> &g) {
        for (unsigned int i = 1; i <= g.get_num_vertices(); i++) {
            id[i] = i;
        }
    }

    Vertex findSet(Vertex p) {
        return id[p];
    }

    void unionf(Vertex p, Vertex q) {
        Vertex pID = findSet(p);
        Vertex qID = findSet(q);
        if (pID == qID) {
            return;
        }
        for (unsigned int i = 1; i <= id.size(); i++) {
            if (id[i] == pID) {
                id[i] = qID;
            }
        }
    }

    vector<Edge> Kruskal(WeightedGraphAL<VertexWeightPair> &g) {
        vector<Edge> A;
        vector<Edge> vector_edges = g.return_edges();
        makeSet(g);
        selectionSort(vector_edges);
        for (auto item : vector_edges) {
            if (findSet(item.vertex1) != findSet(item.vertex2)) {
                A.push_back(item);
                unionf(item.vertex1, item.vertex2);
            }
        }
        return A;
    }
};

void selectionSort(vector<Edge> &vetor) {
    for (unsigned int i = 0; i < vetor.size(); i++) {
        int min = i;
        for (unsigned int j = i; j < vetor.size(); j++) {
            if (vetor[j].weight < vetor[min].weight) {
                min = j;
            }
        }
        Edge tmp = vetor[i];
        vetor[i] = vetor[min];
        vetor[min] = tmp;
    }
}

template <typename T>
WeightedGraphAL<T>::WeightedGraphAL(unsigned int num_vertices) : num_vertices(num_vertices) {
    adj = new list<VertexWeightPair>[num_vertices + 1];  // +1 para lidar com os vértices a partir do 1
}

template <typename T>
WeightedGraphAL<T>::~WeightedGraphAL() {
    for (unsigned int u = 1; u <= num_vertices; ++u) {
        adj[u].clear();
    }
    delete[] adj;
    adj = nullptr;
    num_edges = 0;
    num_vertices = 0;
}

template <typename T>
void WeightedGraphAL<T>::add_edge(Vertex u, Vertex v, Weight weight) {
    VertexWeightPair item_Vertex_v{v, weight};
    VertexWeightPair item_Vertex_u{u, weight};
    int flag1 = 0, flag2 = 0;
    int flag3 = 0, flag4 = 0;
    if (vertex_already_exists(u, v) == false) {
        adj[u].push_back(item_Vertex_v);
        flag3 = 1;
    }
    if (vertex_already_exists(v, u) == false) {
        adj[v].push_back(item_Vertex_u);
        flag4 = 1;
    }

    if (flag3 == 1 && flag4 == 1) {
        Edge uv{u, v, weight};
        edges.push_back(uv);
    }

    for (auto itr = vertices.begin(); itr != vertices.end(); ++itr) {
        if (itr->vertex == item_Vertex_v.vertex) {
            flag1 = 1;
        }
        if (itr->vertex == item_Vertex_u.vertex) {
            flag2 = 1;
        }
    }
    if (flag1 == 0) {
        vertices.push_back(item_Vertex_v);
    }
    if (flag2 == 0) {
        vertices.push_back(item_Vertex_u);
    }
    num_edges++;
}

template <typename T>
bool WeightedGraphAL<T>::vertex_already_exists(Vertex u, Vertex v) {
    VertexWeightPair item_Vertex_u{u};
    VertexWeightPair item_Vertex_v{v};
    list<VertexWeightPair> &lista_u = adj[u];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr) {
        if (itr->vertex == item_Vertex_v.vertex) {
            return true;
        }
    }
    return false;
}

template <typename T>
void WeightedGraphAL<T>::remove_edge(Vertex u, Vertex v) {
    VertexWeightPair item_Vertex_v{v};
    VertexWeightPair item_Vertex_u{u};
    list<VertexWeightPair> &lista_u = adj[u];
    for (auto itr = lista_u.begin(); itr != lista_u.end(); ++itr) {
        if (itr->vertex == item_Vertex_v.vertex) {
            itr = lista_u.erase(itr);
        }
    }
    list<VertexWeightPair> &lista_v = adj[v];
    for (auto itr2 = lista_v.begin(); itr2 != lista_v.end(); ++itr2) {
        if (itr2->vertex == item_Vertex_u.vertex) {
            itr2 = lista_v.erase(itr2);
        }
    }
    for (auto itr = vertices.begin(); itr != vertices.end(); ++itr) {
        if (get_adj(item_Vertex_v.vertex).empty()) {
            itr = vertices.erase(itr);
        }
        if (get_adj(item_Vertex_u.vertex).empty()) {
            itr = vertices.erase(itr);
        }
    }

    for (auto itr2 = edges.begin(); itr2 != edges.end(); ++itr2) {
        if (itr2->vertex1 == item_Vertex_u.vertex || itr2->vertex1 == item_Vertex_v.vertex) {
            itr2 = edges.erase(itr2);
        }
    }
    for (auto itr2 = edges.begin(); itr2 != edges.end(); ++itr2) {
        if (itr2->vertex2 == item_Vertex_u.vertex || itr2->vertex2 == item_Vertex_v.vertex) {
            itr2 = edges.erase(itr2);
        }
    }
    num_edges--;
}

template <typename T>
void input_WeightedGraphAL(WeightedGraphAL<T> &g, unsigned int num_edges) {
    Vertex u = 0;
    Vertex v = 0;
    Weight weight = 0;
    for (unsigned int i = 0; i < num_edges; ++i) {
        cin >> u >> v >> weight;
        g.add_edge(u, v, weight);
    }
}

template <typename T>
void display_list(list<T> &lst) {
    for (auto item_Vertex : lst) {
        cout << "(" << item_Vertex.vertex << ", " << item_Vertex.weight << "), ";
    }
    cout << endl;
}

template <typename T>
void display_WeightedGraphAL(WeightedGraphAL<T> &g) {
    for (unsigned int v = 1; v <= g.get_num_vertices(); v++) {
        cout << v << ": ";
        list<T> lst = g.get_adj(v);
        display_list(lst);
    }
}

int main() {
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin >> num_vertices >> num_edges;
    WeightedGraphAL<VertexWeightPair> g{num_vertices};
    input_WeightedGraphAL(g, num_edges);
    display_WeightedGraphAL(g);

    UnionFind uf(num_vertices);
    vector<Edge> result = uf.Kruskal(g);
    for (auto item : result) {
        cout << "(" << item.vertex1 << " , " << item.vertex2 << " , " << item.weight << " ) " << endl;
    }
    return 0;
}
