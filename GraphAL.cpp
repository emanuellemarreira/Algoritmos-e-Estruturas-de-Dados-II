#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef unsigned int Vertex;
class ItemVertex{
public: 
    unsigned int value;
    ItemVertex(){}
    ItemVertex(unsigned int value): value(value){};
};

template<typename T>
class Graph{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    list<T> *adj; //pra alocar dinamicamente
public:
    Graph(unsigned int);
    ~Graph();
    void add_edge(Vertex, Vertex);
    void remove_edge(Vertex, Vertex);
    list<T> get_adj(Vertex v){ return adj[v]; }
    unsigned int get_num_vertices(){return num_vertices;}
    unsigned int get_num_edges(){return num_edges;}
};

template<typename T>
Graph<T>::Graph(unsigned int num_vertices): num_vertices(num_vertices){
    adj = new list<ItemVertex>[num_vertices];
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
void Graph<T>::add_edge(Vertex u, Vertex v){
    ItemVertex item_Vertex_v{v};
    adj[u].push_back(item_Vertex_v);
    ItemVertex item_Vertex_u{u};
    adj[v].push_back(item_Vertex_u);//como nao é direcionado tem que fazer esse vice-versa
    num_edges++;
}

template<typename T>
void Graph<T>::remove_edge(Vertex u, Vertex v){
    ItemVertex item_Vertex_v{v};
    ItemVertex item_Vertex_u{u};
    list<ItemVertex> &lista_u = adj[u];
    for( auto itr = lista_u.begin(); itr!= lista_u.end(); ++itr){
        if(itr->value == item_Vertex_v.value){
            itr = lista_u.erase( itr );
        }
    }
    list<ItemVertex> &lista_v = adj[v];
    for( auto itr2 = lista_v.begin(); itr2!= lista_v.end(); ++itr2){
        if(itr2->value == item_Vertex_u.value){
            itr2 = lista_v.erase( itr2 );
        }
    }
    num_edges--;
}

template <typename T>
void input_graph(Graph<T> &g, unsigned int num_edges){
    Vertex u = 0;
    Vertex v = 0;
    for(unsigned int i = 0; i<num_edges; ++i){
        cin >> u >> v;
        g.add_edge(u, v);
    }
}
template <typename T>
void display_list(list<T> &lst) {
	for (auto item_Vertex : lst) {
		cout << item_Vertex.value << ", ";
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
    Graph<ItemVertex> g{num_vertices};
    input_graph(g, num_edges);
    display_graph(g);
    //g.remove_edge(2,3);
    //cout<<"removendo..."<<endl;
    //display_graph(g);
    return 0;
}