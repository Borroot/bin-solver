#include <iostream>
#include <vector>

using namespace std;

struct V {
	int label;
	vector<int> neighbors;
};

bool operator== (V vector1, V vector2) {
	return vector1.label == vector2.label;
}

//template <typename T>
//ostream& operator<< (ostream &out, vector<T> graph) {
	//cout << "{";
	//for (int i = 0; i < graph.size(); i++) {
		//cout << graph[i];
		//if (i != graph.size() - 1) {
			//cout << ", ";
		//}
	//}
	//cout << "}" << endl;
	//return out;
//}

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

vector<V> copy (vector<V> original) {
	vector<V> copy;

	for (int i = 0; i < original.size(); i++) {
		copy.push_back(original[i]);
	}
	return copy;
}

void remove_neighbors (vector<V> &vertices, vector<int> &to_be_removed) {
	for (int i = 0; i < to_be_removed.size(); i++) {
		for (int j = 0; j < vertices.size(); j++) {
			if (to_be_removed[i] == vertices[j].label) {
				vertices.erase(vertices.begin() + j);
			}
		}
	}
}

bool DFS_sequential_search (vector<V> &vertices_left, int bins_placed, const int &B_SIZE) {
	if (bins_placed >= B_SIZE) {
		return true;
	}
		
	bins_placed++;
	for (int i = 0; i < vertices_left.size(); i++) {
		V current = vertices_left[i];

		vertices_left.erase(vertices_left.begin() + i);

		vector<V> vertices_left_copy = copy(vertices_left);
		remove_neighbors(vertices_left, current.neighbors);

		if (DFS_sequential_search(vertices_left, bins_placed, B_SIZE)) {
			return true;
		}

		vertices_left = vertices_left_copy;
		vertices_left.insert(vertices_left.begin() + i, current);
	}		
	bins_placed--;

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
