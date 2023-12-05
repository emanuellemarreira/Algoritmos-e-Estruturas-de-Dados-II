#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <iomanip>
#include <limits>
using namespace std;

// implementação de um grafo ponderado e direcionado utilizando matriz de adjacência

const float inf = std::numeric_limits<float>::infinity();

template <typename T>
class Edge
{
public:
	T weight;
	Edge() : weight(inf) {}
	Edge(T _weight) : weight(_weight) {}
};

template <typename T>
class WeightedDigraphAM
{
private:
	unsigned int num_vertices;
	unsigned int num_edges;
	Edge<T> **adj;

public:
	WeightedDigraphAM(unsigned int);
	~WeightedDigraphAM();
	void add_edge(unsigned int, unsigned int, T);
	list<unsigned int> get_adj(unsigned int);
	T get_weight_edge(unsigned int, unsigned int);
	void remove_edge(unsigned int, unsigned int);
	unsigned int get_num_vertices();
	unsigned int get_num_edges();
};

template <typename T>
unsigned int WeightedDigraphAM<T>::get_num_vertices()
{
	return num_vertices;
}

template <typename T>
unsigned int WeightedDigraphAM<T>::get_num_edges()
{
	return num_edges;
}

template <typename T>
WeightedDigraphAM<T>::WeightedDigraphAM(unsigned int _num_vertices) : num_vertices(_num_vertices),
																	  num_edges(0)
{
	const unsigned int LINHAS = num_vertices;
	const unsigned int COLUNAS = num_vertices;
	adj = new Edge<T> *[LINHAS];
	for (unsigned int i = 0; i < LINHAS; ++i)
	{
		adj[i] = new Edge<T>[COLUNAS];
	}
}

template <typename T>
void WeightedDigraphAM<T>::remove_edge(unsigned int u, unsigned int v)
{
	Edge<T> edge{inf};
	adj[u][v] = edge;
	num_edges--;
}

template <typename T>
WeightedDigraphAM<T>::~WeightedDigraphAM()
{
	const unsigned int LINHAS = num_vertices;
	for (unsigned int i = 0; i < LINHAS; ++i)
	{
		delete[] adj[i];
	}
	delete[] adj;
}

template <typename T>
void WeightedDigraphAM<T>::add_edge(unsigned int u, unsigned int v, T weight)
{
	if (adj[u][v].weight == inf)
	{
		Edge<T> edge{weight};
		adj[u][v] = edge;
		num_edges++;
	}
}

template <typename T>
std::list<unsigned int> WeightedDigraphAM<T>::get_adj(unsigned int u)
{
	std::list<unsigned int> values;
	for (unsigned int v = 0; v < num_vertices; ++v)
	{
		if (adj[u][v].weight != inf)
		{
			values.push_back(v);
		}
	}
	return values;
}

template <typename T>
T WeightedDigraphAM<T>::get_weight_edge(unsigned int u, unsigned int v)
{
	return adj[u][v].weight;
}

template <typename T>
void display_matadj_graph(WeightedDigraphAM<T> &g)
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

	WeightedDigraphAM<float> g{num_vertices};

	unsigned int u = 0;
	unsigned int v = 0;

	float weight = inf;

	for (unsigned int i = 0; i < num_edges; ++i)
	{
		cin >> u >> v >> weight;
		g.add_edge(u, v, weight);
	}

	display_matadj_graph(g);

	return 0;
}