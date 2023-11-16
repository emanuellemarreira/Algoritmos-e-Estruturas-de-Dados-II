#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

typedef unsigned int vertex;

int main(int argc, char const *argv[]){
    int value = 0;
    vector<int> values;
    for(int i = 1; i < argc; ++i){ //pego os valores de entrada do terminal que vao estar numa linha só
        value = atoi(argv[i]);//pegar valor e converter pra int 
        values.push_back(value);
    }
     
    unsigned int num_vertices = values[0];
    unsigned int num_edges = values[1];
    Grafo<Edge> g{num_vertices};
    for(int i = 2; i <= num_edges*2; i += 2){//começa do 2 pra ler só as conexoes
        vertex u = values[i]; 
        vertex v = values[i+1]; //ler em pares 
        g.add_edge(u, v);
    }
    display_graph(g);
    cout << endl;
    return 0;
}