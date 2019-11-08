#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <bits/stdc++.h>

#include "vertex.h"
#include "init_vectors.h"
#include "filter.h"
#include "remove_vertex.h"

using namespace std;

struct State {
	V current;
	vector<V> vertices;
	vector<V> chosen;
};

bool operator== (const State &state1, const State &state2) {
	// Two states are equal if the current vertex, the vertices left and the vertices chosen are the same.
	return state1.current == state2.current && state1.vertices == state2.vertices && state1.chosen == state2.chosen;	
}

template<> struct std::hash<vector<V>> {
	// Defines the hash function for the type vector<V>.
	size_t operator() (const vector<V> &vertices) const noexcept {
		size_t seed = vertices.size();
		for(int i = 0; i < (int)vertices.size(); i++) {
			seed += vertices[i] * 37;
		}
		return hash<size_t>{}(seed);
	}
};

template<> struct std::hash<State> {
	// Defines the hash function for the type State.
	size_t operator() (const State &state) const noexcept {
		size_t h1 = hash<V>()(state.current);
		size_t h2 = hash<vector<V>>()(state.vertices);
		size_t h3 = hash<vector<V>>()(state.chosen);
		return h1 ^ h2 ^ h3;
	}
};

void insert(vector<V> &vertices, V vertex) {
	// Insert the vertex at the right position in the already sorted list of vertices.
	// This is done because the hash function takes into account order, but the list
	// with the same elements added in a different order should get the same hash value.
	vector<V>::iterator it = lower_bound(vertices.begin(), vertices.end(), vertex, greater<V>()); 
	vertices.insert(it, vertex); 
}

vector<V> create_next_vertices (vector<V> &vertices, vector<vector<V>> &neighbors, V current) {
	vector<V> next_vertices(vertices);	
	remove_vertex(next_vertices, current);

	// Create the list of the next vertices by removing the current and all of its neighbors.
	for (int i = 0; i < (int)neighbors[current].size(); i++) {
		remove_vertex(next_vertices, neighbors[current][i]);
	}
	return next_vertices;
}

bool DFS_sequential_search (vector<V> vertices, vector<V> &chosen, vector<vector<V>> &neighbors, unordered_set<State> &states, const int &BIN_GOAL) {
	// Stop if we achieved our goal of placing the amount of bins.
	if ((int)chosen.size() >= BIN_GOAL) {
		return true;
	}

	// Explore the tree by starting from every possible vertex still left.
	for (int i = 0; i < (int)vertices.size(); i++) {
		V current = vertices[i];
		insert(chosen, current);
		vector<V> next_vertices = create_next_vertices(vertices, neighbors, current);

		// Only continue the DFS if the current state is not already explored.
		State state = {current, next_vertices, chosen};
		if (states.find(state) == states.end()) {
			states.insert(state);

			if (DFS_sequential_search(next_vertices, chosen, neighbors, states, BIN_GOAL)) {
				return true;
			}
		} 

		remove_vertex(chosen, current);
	}		
	return false;
}

void swap (V *vertex1, V *vertex2) {
	// Swap the two vertices, used in the bubble sort.
	V temp = *vertex1;
	*vertex1 = *vertex2;
	*vertex2 = temp;
}

void bubble_sort (vector<V> &vertices, const vector<vector<V>> &neighbors) {
	// Sort the vertices according to their degree, smallest to highest.
	for (int i = 0; i < (int)vertices.size() - 1; i++) {
		for (int j = 0; j < (int)vertices.size() - i - 1; j++) {
			if (neighbors[vertices[j]].size() > neighbors[vertices[j+1]].size()) {
				swap(&vertices[j], &vertices[j+1]);
			}
		}
	}
}

int main () {

	int E_SIZE, V_SIZE, BIN_GOAL;
	cin >> E_SIZE >> V_SIZE >> BIN_GOAL;

	vector<V> vertices;
   	vector<vector<V>> neighbors(V_SIZE);

	vector<V> chosen;
	unordered_set<State> states;

	init_vectors(vertices, neighbors, V_SIZE, E_SIZE);

	// Filter out all vertices which will not be in the solution anyways.
	filter(vertices, neighbors);

	// If there are less vertices left than our bin goal, well then it is impossible to place them.
	if ((int)vertices.size() < BIN_GOAL) {
		cout << "impossible" << endl;
		return 0;
	}

	// Sort the vertices from low degree to high degree for higher chances of finding the 'possible' tree.
	bubble_sort(vertices, neighbors);

	// Run DFS.
	bool result = DFS_sequential_search(vertices, chosen, neighbors, states, BIN_GOAL);

	cout << (result ? "possible" : "impossible") << endl;

	return 0;
}
