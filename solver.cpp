#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <bits/stdc++.h> 

using namespace std;

struct V {
	int label;
	vector<int> neighbors;
};

struct State {
	int current;
	vector<int> vertices;
	vector<int> chosen;
};

bool operator== (const V &vector, const int label) {
	return vector.label == label;
}

bool operator== (const State &state1, const State &state2) {
	return state1.current == state2.current && state1.vertices == state2.vertices && state1.chosen == state2.chosen;	
}

namespace std {
	template<> struct hash<vector<int>> {
		size_t operator() (const vector<int> &vec) const noexcept {
			size_t seed = vec.size();
			for(auto& i : vec) {
				seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
			}
			return seed;
		}
	};
}

namespace std {
	template<> struct hash<State> {
		size_t operator() (const State &state) const noexcept {
			size_t h1 = hash<int>()(state.current);
			size_t h2 = hash<vector<int>>()(state.vertices);
			size_t h3 = hash<vector<int>>()(state.chosen);
			return h1 ^ h2 ^ h3;
		}
	};
}

vector<V> init_vectors (const int &V_SIZE, const int &E_SIZE) {
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

vector<int> labels (vector<V> vertices) {
	vector<int> labels_vertices;

	for (int i = 0; i < vertices.size(); i++) {
		labels_vertices.push_back(vertices[i].label);
	}
	return labels_vertices;
}

State create_state (V &current, vector<V> &vertices, vector<int> &chosen) {
	State state = {current.label, labels(vertices), chosen}; 
	return state; 
}

void insert(vector<int> &vertices, int vertex) {
	vector<int>::iterator it = lower_bound(vertices.begin(), vertices.end(), vertex, greater<int>()); 
	vertices.insert(it, vertex); 
}

bool DFS_sequential_search (vector<V> vertices, vector<int> &chosen, unordered_set<State> &states, const int &BIN_GOAL) {
	if (chosen.size() >= BIN_GOAL) {
		return true;
	}
		
	for (int i = 0; i < vertices.size(); i++) {
		V current = vertices[i];
		insert(chosen, current.label);
		vector<V> next_vertices = create_next_vertices(vertices, current);

		State state = create_state(current, next_vertices, chosen);
		if (states.find(state) == states.end()) {
			states.insert(state);

			if (DFS_sequential_search(next_vertices, chosen, states, BIN_GOAL)) {
				return true;
			}
		} 
		chosen.pop_back();
	}		
	return false;
}

int main () {

	int E_SIZE, V_SIZE, BIN_GOAL;
	cin >> E_SIZE;
	cin >> V_SIZE;
	cin >> BIN_GOAL;

	vector<V> vertices = init_vectors(V_SIZE, E_SIZE);
	vector<int> chosen;
	unordered_set<State> states;

	bool result = DFS_sequential_search(vertices, chosen, states, BIN_GOAL);
	cout << (result ? "possible" : "impossible") << endl;

	return 0;
}
