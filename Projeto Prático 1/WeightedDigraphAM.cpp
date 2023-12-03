#include <iostream>
#include <cstdlib> // atoi
#include <vector>
#include <list>
#include <iomanip> // setw
#include <limits>
using namespace std;

//implementação de um grafo ponderado e direcionado utilizando matriz de adjacência

const float inf = std::numeric_limits<float>::infinity();

typedef unsigned int Vertex;

typedef float Weight;

class Edge
{
public:
	Weight weight;
	Edge() : weight(inf) {}
	Edge(Weight _weight) : weight(_weight) {}
};

class WeightedDigraphAM
{
private:
	unsigned int num_vertices;
	unsigned int num_edges;
	Edge **adj;

public:
	WeightedDigraphAM(unsigned int);
	~WeightedDigraphAM();
	void add_edge(Vertex, Vertex, Weight);
	list<Vertex> get_adj(Vertex);
	Weight get_weight_edge(Vertex, Vertex);
	void remove_edge(Vertex, Vertex);
	unsigned int get_num_vertices();
	unsigned int get_num_edges();
};

unsigned int WeightedDigraphAM::get_num_vertices()
{
	return num_vertices;
}

unsigned int WeightedDigraphAM::get_num_edges()
{
	return num_edges;
}

WeightedDigraphAM::WeightedDigraphAM(unsigned int _num_vertices) : num_vertices(_num_vertices),
															   num_edges(0)
{
	const unsigned int LINHAS = num_vertices;
	const unsigned int COLUNAS = num_vertices;
	adj = new Edge *[LINHAS];
	for (unsigned int i = 0; i < LINHAS; ++i)
	{
		adj[i] = new Edge[COLUNAS];
	}
}

void WeightedDigraphAM::remove_edge(Vertex u, Vertex v)
{
	Edge edge{inf};
	adj[u][v] = edge;
	num_edges--;
}

WeightedDigraphAM::~WeightedDigraphAM()
{
	const unsigned int LINHAS = num_vertices;
	for (unsigned int i = 0; i < LINHAS; ++i)
	{
		delete[] adj[i];
	}
	delete[] adj;
}

void WeightedDigraphAM::add_edge(Vertex u, Vertex v, Weight weight)
{
	if (adj[u][v].weight == inf)
	{
		Edge edge{weight};
		adj[u][v] = edge;
		num_edges++;
	}
}

std::list<Vertex> WeightedDigraphAM::get_adj(Vertex u)
{
	std::list<Vertex> values;
	for (unsigned int v = 0; v < num_vertices; ++v)
	{
		if (adj[u][v].weight != inf)
		{
			values.push_back(v);
		}
	}
	return values;
}

Weight WeightedDigraphAM::get_weight_edge(Vertex u, Vertex v)
{
	return adj[u][v].weight;
}

void display_matadj_graph(WeightedDigraphAM &g)
{
	int k = 0;

	for (unsigned int i = 0; i < g.get_num_vertices(); i++)
	{
		cout << std::setw(k) << g.get_weight_edge(i, 0) << " ";
		for (unsigned int j = 1; j < g.get_num_vertices(); j++)
		{
			cout << std::setw(k + 2) << g.get_weight_edge(i, j) << " ";
		}
		cout << endl;
	}
}

int main()
{
	unsigned int num_vertices;
	unsigned int num_edges;

	cin >> num_vertices;
	cin >> num_edges;

	cout << "num_vertices: " << num_vertices << endl;
	cout << "num_edges: " << num_edges << endl;

	WeightedDigraphAM g{num_vertices};

	Vertex u = 0;
	Vertex v = 0;

	Weight weight = inf;

	for (unsigned int i = 0; i < num_edges; ++i)
	{
		cin >> u >> v >> weight;
		g.add_edge(u, v, weight);
	}

	display_matadj_graph(g);

	cout<< "removendo..."  <<endl;

	g.remove_edge(1, 2);

	display_matadj_graph(g);

	return 0;
}