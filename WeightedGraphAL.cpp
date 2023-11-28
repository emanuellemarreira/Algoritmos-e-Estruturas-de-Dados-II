#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef unsigned int vertex;
typedef unsigned int weight;

class VertexWeightPair{
public: 
    vertex vertice;
    weight peso;
    VertexWeightPair(){}
    VertexWeightPair(vertex vertice, weight peso): vertice(vertice), peso(peso){};

};

template<typename T>
class Graph{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj; 
public:
    Graph(unsigned int);
    ~Graph();
    void add_edge(vertex, vertex, weight);
    void remove_edge(vertex, vertex);
    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
    list<T> get_adj(vertex v){ return adj[v]; }
};

template<typename T>
Graph<T>::Graph(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<VertexWeightPair>[num_vertices];
}
template<typename T>
Graph<T>::~Graph(){
    for (unsigned int u = 0; u < num_vertices; ++u){
        adj[u].clear(); //pega uma lista que ta na posicao i e apaga usando clear pq adj é uma list
    }
    delete[] adj; //como adj é uma list
    adj = nullptr;
    num_edges =0;
    num_vertices = 0;
    //cout << "\nbye graph\n";
}

template<typename T>
void Graph<T>::add_edge(vertex u, vertex v, weight peso){
    VertexWeightPair item_vertex_v{v, peso};
    adj[u].push_back(item_vertex_v);
    VertexWeightPair item_vertex_u{u, peso};
    adj[v].push_back(item_vertex_u);//como nao é direcionado tem que fazer esse vice-versa
    num_edges++;
}

template<typename T>
void Graph<T>::remove_edge(vertex u, vertex v){
    VertexWeightPair item_vertex_v{v};
    VertexWeightPair item_vertex_u{u};
    list<VertexWeightPair> &lista_u = adj[u];
    for( auto itr = lista_u.begin(); itr!= lista_u.end(); ++itr){
        if(itr->vertice == item_vertex_v.vertice){
            itr = lista_u.erase( itr );
        }
    }
    list<VertexWeightPair> &lista_v = adj[v];
    for( auto itr2 = lista_v.begin(); itr2!= lista_v.end(); ++itr2){
        if(itr2->vertice == item_vertex_u.vertice){
            itr2 = lista_v.erase( itr2 );
        }
    }
    num_edges--;
}

template <typename T>
void input_graph(Graph<T> &g, unsigned int num_edges){
    vertex u = 0;
    vertex v = 0;
    weight peso = 0;
    for(unsigned int i = 0; i < num_edges; ++i){
        cin >> u >> v >> peso;
        g.add_edge(u, v, peso);
    }
}
template <typename T>
void display_list(list<T> &lst) {
	for (auto item_vertex : lst) {
		cout << "(" << item_vertex.vertice << ", " << item_vertex.peso << "),";
	}
	cout << endl;
}
template <typename T>
void display_graph(Graph<T> &g){
    for(unsigned int v = 0; v < g.get_num_vertices(); v++){
        cout << "v[" << v << "]: ";
		list<T> lst = g.get_adj(v);
		display_list( lst );
    }
}
int main(){
    unsigned int num_vertices = 0;
    unsigned int num_edges = 0;
    cin>> num_vertices >> num_edges;
    cout << "num_vertices: "<< num_vertices <<endl;
    cout << "num_edges: "<< num_edges <<endl;
    Graph<VertexWeightPair> g{num_vertices};
    input_graph(g, num_edges);
    display_graph(g);
    //g.remove_edge(2,3);
    //cout<<"removendo..."<<endl;
    //display_graph(g);
    return 0;
}