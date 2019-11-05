#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <bits/stdc++.h> 

using namespace std;

typedef int V;

int pruned = 0, total = 0;

struct State {
	V current;
	vector<V> vertices;
	vector<V> chosen;
};

ostream &operator << (ostream &out, vector<V> vertices) {
	// Print a vector with vertices, this is just for debugging purposes.
	cerr << "[";
	for (int i = 0; i < (int)vertices.size(); i++) {
		cerr << vertices[i];
		if (i != (int)vertices.size()-1) {
			cerr << ",";
		}
	}
	cerr << "]";
	return out;
}

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

void init_vectors (vector<V> &vertices, vector<vector<V>> &neighbors, const int &V_SIZE, const int &E_SIZE) {

	// Initialize vertices list.
	for (int i = 0; i < V_SIZE; i++) {
		vertices.push_back(i);
	}

	// Add neighbors to vertices.
	for (int i = 0; i < E_SIZE; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		neighbors[v1-1].push_back(v2-1);
		neighbors[v2-1].push_back(v1-1);
	}
}

void insert(vector<V> &vertices, V vertex) {
	// Insert the vertex at the right position in the already sorted list of vertices.
	// This is done because the hash function takes into account order, but the list
	// with the same elements added in a different order should get the same hash value.
	vector<V>::iterator it = lower_bound(vertices.begin(), vertices.end(), vertex, greater<V>()); 
	vertices.insert(it, vertex); 
}

void remove_vertex (vector<V> &vertices, V vertex) {
	// Remove the vertex from the vertices list by value not by index.
	vertices.erase(remove(vertices.begin(), vertices.end(), vertex), vertices.end());
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

		total++;
		// Only continue the DFS if the current state is not already explored.
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

void remove_edges (const V &vertex, vector<vector<V>> &neighbors) {
	// Remove all the references to vertex inside of the neighbors from other vertices.
	for (int i = 0; i < (int)neighbors.size(); i++) {
		remove_vertex(neighbors[i], vertex);
	}
}

bool subset (const vector<V> &vertices1, const vector<V> &vertices2) {
	// Determine whether vertices1 is a subset of vertices2.
	for (int i = 0; i < (int)vertices1.size(); i++) {
		bool found = false;;

		for (int j = 0; !found && j < (int)vertices2.size(); j++) {
			if (vertices1[i] == vertices2[j]) {
				found = true;
			}
		}
		if (!found) {
			return false;
		}
	}
	return true;
}

void filter (vector<V> &vertices, vector<vector<V>> &neighbors) {
	// Here we filter out vertices based on the following criteria:
	// if the neighbors of the current vertex are a subset of the 
	// neighbors of a neighbor of the current vertex then remove this
	// neighbor from the vertices left. This can be done since we 
	// know that it is always more beneficial to choose the current
	// vertex instead of this particular neighbor. 
	bool found;

	do {
		found = false;

		for (int i = 0; i < (int)vertices.size() && !found; i++) {
			V current = vertices[i];

			for (int j = 0; j < (int)neighbors[current].size(); j++) {
				V neighbor = neighbors[current][j];
				remove_vertex(neighbors[current], neighbor);

				if (subset(neighbors[current], neighbors[neighbor])) {
					remove_edges(neighbor, neighbors);	
					remove_vertex(vertices, neighbor);

					found = true;
				} else {
					neighbors[current].push_back(neighbor);
				}
			}
		}
	} while (found);
}

int main () {

	int E_SIZE, V_SIZE, BIN_GOAL;
	cin >> E_SIZE >> V_SIZE >> BIN_GOAL;

	vector<V> vertices;
   	vector<vector<V>> neighbors(V_SIZE);

	vector<V> chosen;
	unordered_set<State> states;

	init_vectors(vertices, neighbors, V_SIZE, E_SIZE);

	int old_size = vertices.size();
	// Filter out all vertices which will not be in the solution anyways.
	filter(vertices, neighbors);
	cerr << "Removed " << old_size - vertices.size() << " of total " << old_size << " vertices. "; 

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
	cerr << "Pruned " << pruned << " of total " << total << " amount of trees." << endl;

	return 0;
}
