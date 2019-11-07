#include <iostream>
#include <vector>
#include <bits/stdc++.h> 

#include "init_vectors.h"

#define COLORS 5

using namespace std;

typedef int V;

vector<V> results;

ostream &operator << (ostream &out, vector<V> vertices) {
	cerr << "[";
	for (int i = 0; i < (int)vertices.size(); i++) {
		cerr << vertices[i]+1;
		if (i != (int)vertices.size()-1) {
			cerr << ",";
		}
	}
	cerr << "]";
	return out;
}

void remove_vertex (vector<V> &vertices, const V vertex) {
	// Remove vertex from the vertices list by its id not by index.
	vertices.erase(remove(vertices.begin(), vertices.end(), vertex), vertices.end());
}

int highest (const vector<V> &colors) {
	int counts[COLORS];

	// Initialize all counts to 0.
	for (int i = 0; i < COLORS; i++) {
		counts[i] = 0;
	}

	// Increase all the corresponding color counts for all vertex colors.
	for (int i = 0; i < (int)colors.size(); i++) {
		counts[colors[i]]++;
	}

	int color_max = -1;
	// Get the biggest color count.
	int max = -1;
	for (int i = 0; i < COLORS; i++) {
		if (counts[i] > max) {
			max = counts[i];
			color_max = i;
		}
	}

	results.clear();
	for (int i = 0; i < (int)colors.size(); i++) {
		if (colors[i] == color_max) {
			results.push_back(i+1);
		}
	}

	return max;
}

int choose_color (const V &current, const vector<V> &colors, const vector<vector<V>> &neighbors) {
	bool legal_color[COLORS];

	// Initialize all the colors to legal.
	for (int i = 0; i < COLORS; i++) {
		legal_color[i] = true;
	}

	// Set the color to illegal if one of the neighbors has this color.
	for (int i = 0; i < (int)neighbors[current].size(); i++) {
		int color_neighbor = colors[neighbors[current][i]];
		legal_color[color_neighbor] = false;
	}

	// Take the FIRST legal color (so lower index colors have priority).
	for (int i = 0; i < COLORS; i++) {
		if (legal_color[i]) {
			return i;
		}
	}
	return -1;
}

int color (vector<V> vertices, const vector<vector<V>> &neighbors, const int &V_SIZE) {
	vector<V> colors(V_SIZE);
	for (int i = 0; i < V_SIZE; i++) {
		colors[i] = -1;
	}

	// Choose a color for a random vertex until all vertices are colored.
	while (vertices.size() > 0) {
		V current = vertices[rand() % vertices.size()];	
		colors[current] = choose_color(current, colors, neighbors);
		remove_vertex(vertices, current);
	}
	return highest(colors);
}

bool search (const vector<V> &vertices, const vector<vector<V>> &neighbors, const int &V_SIZE, const int &BIN_GOAL) {
	const int MAX = 10000;
	int result, count = 0;

	// Search for a coloring which satisfies the BIN_GOAL until the limit is reached.
	// If the limit is reached stop and return false else return true.
	do {
		result = color (vertices, neighbors, V_SIZE);
		count++;
	} while (result < BIN_GOAL && count < MAX);

	return result >= BIN_GOAL;
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
	srand(time(0));

	int E_SIZE, V_SIZE, BIN_GOAL;
	cin >> E_SIZE >> V_SIZE >> BIN_GOAL;

	vector<V> vertices;
   	vector<vector<V>> neighbors(V_SIZE);

	vector<V> chosen;

	init_vectors(vertices, neighbors, V_SIZE, E_SIZE);

	// Filter out all vertices which will not be in the solution anyways.
	filter(vertices, neighbors);

	// If there are less vertices left than our bin goal, well then it is impossible to place them.
	if ((int)vertices.size() < BIN_GOAL) {
		cout << "impossible" << endl;
		return 0;
	}

	// Search for a solution.
	bool result = search(vertices, neighbors, V_SIZE, BIN_GOAL);

	cout << (result ? "possible" : "impossible") << endl;
	cerr << results << endl;

	return 0;
}
