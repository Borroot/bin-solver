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
ostream& operator<< (ostream &out, vector<T> vertices) {
	cout << "{";
	for (int i = 0; i < vertices.size(); i++) {
		cout << vertices[i];
		if (i != vertices.size() - 1) {
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

int main () {

	int E_SIZE, V_SIZE, B_SIZE;
	cin >> E_SIZE;
	cin >> V_SIZE;
	cin >> B_SIZE;

	vector<E> edges    = init_edges(E_SIZE);
	vector<V> vertices = init_vectors(V_SIZE);

	cout << edges;
	cout << vertices;

	return 0;
}
