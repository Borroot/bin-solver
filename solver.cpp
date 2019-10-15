#include <iostream>
#include <vector>

using namespace std;

typedef int V;

struct E {
	V v1, v2;	
};

ostream& operator<< (ostream &out, E edge) {
	cout << "[" << edge.v1 << "," << edge.v2 << "]";
	return out;
}

template <typename T>
ostream& operator<< (ostream &out, vector<T> graph) {
	cout << "{";
	for (int i = 0; i < graph.size(); i++) {
		cout << graph[i];
		if (i != graph.size() - 1) {
			cout << ", ";
		}
	}
	cout << "}" << endl;
	return out;
}

vector<V> init_vectors (const int V_SIZE) {
	vector<V> vertices;
	for (int i = 0; i < V_SIZE; i++) {
		vertices.push_back(i+1);
	}
	return vertices;
}

vector<E> init_edges (const int E_SIZE) {
	vector<E> edges;
	for (int i = 0; i < E_SIZE; i++) {
		int v1, v2;
		cin >> v1;
		cin >> v2;
		E edge = {v1, v2};
		edges.push_back(edge);
	}
	return edges;
}

vector<V> copy (vector<V> original) {
	vector<V> copy;

	for (int i = 0; i < original.size(); i++) {
		copy.push_back(original[i]);
	}
	return copy;
}

vector<V> search_neighbors (vector<E> &edges, vector<V> &vertices_left, V vertex) {
	vector<V> neighbors;

	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].v1 == vertex) {
			neighbors.push_back(edges[i].v2);
		} else if (edges[i].v2 == vertex) {
			neighbors.push_back(edges[i].v1);
		}
	}
	return neighbors;
}

void remove_neighbors (vector<V> &vertices, vector<V> &to_be_removed) {
	for (int i = 0; i < to_be_removed.size(); i++) {
		for (int j = 0; j < vertices.size(); j++) {
			if (to_be_removed[i] == vertices[j]) {
				vertices.erase(vertices.begin() + j);
			}
		}
	}
}

bool DFS_sequential_search (vector<E> &edges, vector<V> &vertices_left, vector<V> &vertices_chosen, const int &B_SIZE) {
	if (vertices_chosen.size() >= B_SIZE) {
		return true;
	}
		
	for (int i = 0; i < vertices_left.size(); i++) {
		V current_vertex = vertices_left[i];

		vertices_left.erase(vertices_left.begin() + i);
		vertices_chosen.push_back(current_vertex);

		vector<V> neighbors = search_neighbors(edges, vertices_left, current_vertex);

		vector<V> vertices_left_copy = copy(vertices_left);
		remove_neighbors(vertices_left, neighbors);

		if (DFS_sequential_search(edges, vertices_left, vertices_chosen, B_SIZE)) {
			return true;
		}

		vertices_left = vertices_left_copy;
		
		vertices_chosen.pop_back();
		vertices_left.insert(vertices_left.begin() + i, current_vertex);
	}		

	return false;
}

int main () {

	int E_SIZE, V_SIZE, B_SIZE;
	cin >> E_SIZE;
	cin >> V_SIZE;
	cin >> B_SIZE;

	vector<E> edges    = init_edges(E_SIZE);
	vector<V> vertices = init_vectors(V_SIZE);

	vector<V> chosen = {};
	bool result = DFS_sequential_search(edges, vertices, chosen, B_SIZE);
	cout << (result ? "possible" : "impossible") << endl;

	return 0;
}
