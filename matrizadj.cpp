#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

typedef unsigned int vertex;
typedef unsigned int weight;

class Edge{
public:
    weight weight;
    Edge(weight _weight) : weight(_weight) {}
};

class Graph{
private:
    unsigned int num_vertices;
    unsigned int num_edges;
    Edge **adj;
public:
    Graph(unsigned int);
    ~Graph();
};

Graph::Graph(unsigned int num_vertices): num_vertices(_num_vertices)
                                         num_edges(0) {
    const unsigned int LINHAS = num_vertices;
    const unsigned int COLUNAS = num_vertices;
    adj = new Edge*[LINHAS];
    for( int i = 0 ; i < LINHAS; ++i ){
        adj[i] = new Edge[COLUNAS]{0};//vetor do tamanho colunas e instancia no construtor com zero
    }
}

Graph::add_edge(vertex u, vertex v){
    Edge edge{1};
    adj[u][v] = edge;
    adj[v][u] = edge;
    num_vertices++;
}

Graph::~Graph(): {
    const unsigned int LINHAS = num_vertices;
    for(int i = 1; i < argc; ++i){ //pego os valores de entrada do terminal que vao estar numa linha só
        value = atoi(argv[i]);//pegar valor e converter pra int 
        values.push_back(value);
    }
     
    unsigned int num_vertices = values[0];
    unsigned int num_edges = values[1];
    Graph<Edge> g{num_vertices};
    for(int i = 2; i <= num_edges*2; i += 2){//começa do 2 pra ler só as conexoes
        vertex u = values[i]; 
        vertex v = values[i+1]; //ler em pares 
        g.add_edge(u, v);
    }
    display_graph(g);
    cout << endl;
    return 0;
}