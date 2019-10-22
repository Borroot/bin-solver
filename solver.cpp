#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <bits/stdc++.h> 

using namespace std;

int pruned = 0, total = 0;

typedef int V;

struct State {
	V current;
	vector<V> vertices;
	vector<V> chosen;
};

bool operator== (const State &state1, const State &state2) {
	return state1.current == state2.current && state1.vertices == state2.vertices && state1.chosen == state2.chosen;	
}

namespace std {
	template<> struct hash<vector<V>> {
		size_t operator() (const vector<V> &vertices) const noexcept {
			size_t seed = vertices.size();
			for(int i = 0; i < vertices.size(); i++) {
				seed += vertices[i] * 37;
			}
			return hash<size_t>{}(seed);
		}
	};
}

namespace std {
	template<> struct hash<State> {
		size_t operator() (const State &state) const noexcept {
			size_t h1 = hash<V>()(state.current);
			size_t h2 = hash<vector<V>>()(state.vertices);
			size_t h3 = hash<vector<V>>()(state.chosen);
			return h1 ^ h2 ^ h3;
		}
	};
}

void init_vectors (vector<V> &vertices, vector<vector<V>> &neighbors, const int &V_SIZE, const int &E_SIZE) {

	// Initialize vertices list.
	for (int i = 0; i < V_SIZE; i++) {
		vertices.push_back(i);
	}

	// Add neighbors to vertices.
	for (int i = 0; i < E_SIZE; i++) {
		int v1, v2;
		cin >> v1;
		cin >> v2;
		neighbors[v1-1].push_back(v2-1);
		neighbors[v2-1].push_back(v1-1);
	}
}

void insert(vector<V> &vertices, V vertex) {
	vector<V>::iterator it = lower_bound(vertices.begin(), vertices.end(), vertex, greater<V>()); 
	vertices.insert(it, vertex); 
}

void remove_vertex (vector<V> &vertices, V vertex) {
	vertices.erase(remove(vertices.begin(), vertices.end(), vertex), vertices.end());
}

vector<V> create_next_vertices (vector<V> &vertices, vector<vector<V>> &neighbors, V current) {
	vector<V> next_vertices(vertices);	
	remove_vertex(next_vertices, current);

	for (int i = 0; i < neighbors[current].size(); i++) {
		remove_vertex(next_vertices, neighbors[current][i]);
	}
	return next_vertices;
}

bool DFS_sequential_search (vector<V> vertices, vector<V> &chosen, vector<vector<V>> &neighbors, unordered_set<State> &states, const int &BIN_GOAL) {
	if (chosen.size() >= BIN_GOAL) {
		return true;
	}

	for (int i = 0; i < vertices.size(); i++) {
		total++;
		if (total > 9000) {
			return false;
		}
		V current = vertices[i];
		insert(chosen, current);
		vector<V> next_vertices = create_next_vertices(vertices, neighbors, current);

		State state = {current, next_vertices, chosen};
		if (states.find(state) == states.end()) {
			states.insert(state);

			if (DFS_sequential_search(next_vertices, chosen, neighbors, states, BIN_GOAL)) {
				return true;
			}
		} else {
			pruned++;
		}

		remove_vertex(chosen, current);
	}		
	return false;
}

int main () {

	int E_SIZE, V_SIZE, BIN_GOAL;
	cin >> E_SIZE;
	cin >> V_SIZE;
	cin >> BIN_GOAL;

	vector<V> vertices;
   	vector<vector<V>> neighbors(V_SIZE);

	vector<V> chosen;
	unordered_set<State> states;

	init_vectors(vertices, neighbors, V_SIZE, E_SIZE);

	bool result = DFS_sequential_search(vertices, chosen, neighbors, states, BIN_GOAL);
	cout << (result ? "possible" : "impossible") << endl;
	cerr << "pruned: " << pruned << "\ttotal: " << total << "\trelative: " << (int)((pruned * 100.0f) / total) << "%" << endl; 

	return 0;
}
