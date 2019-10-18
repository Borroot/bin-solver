#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct V {
	int label;
	vector<int> neighbors;
};

bool operator== (V vector, int label) {
	return vector.label == label;
}

vector<V> init_vectors (const int V_SIZE, const int E_SIZE) {
	vector<V> vertices;

	// Initialize vertices list.
	for (int i = 0; i < V_SIZE; i++) {
		vertices.push_back({i+1, {}});
	}

	// Add neighbors to vertices.
	for (int i = 0; i < E_SIZE; i++) {
		int v1, v2;
		cin >> v1;
		cin >> v2;
		vertices[v1-1].neighbors.push_back(v2);
		vertices[v2-1].neighbors.push_back(v1);
	}

	return vertices;
}

void remove_by_label (vector<V> &vertices, int label) {
	vertices.erase(remove(vertices.begin(), vertices.end(), label), vertices.end());
}

vector<V> create_next_vertices (vector<V> &vertices, V current) {
	vector<V> next_vertices(vertices);	
	remove_by_label(next_vertices, current.label);

	for (int i = 0; i < current.neighbors.size(); i++) {
		remove_by_label(next_vertices, current.neighbors[i]);
	}

	return next_vertices;
}

bool DFS_sequential_search (vector<V> vertices, int bins_placed, const int &B_SIZE) {
	if (bins_placed >= B_SIZE) {
		return true;
	}
		
	bins_placed++;
	for (int i = 0; i < vertices.size(); i++) {
		V current = vertices[i];
		vector<V> next_vertices = create_next_vertices(vertices, current);

		if (DFS_sequential_search(next_vertices, bins_placed, B_SIZE)) {
			return true;
		}
	}		
	return false;
}

int main () {

	int E_SIZE, V_SIZE, B_SIZE;
	cin >> E_SIZE;
	cin >> V_SIZE;
	cin >> B_SIZE;

	vector<V> vertices = init_vectors(V_SIZE, E_SIZE);

	bool result = DFS_sequential_search(vertices, 0, B_SIZE);
	cout << (result ? "possible" : "impossible") << endl;

	return 0;
}
