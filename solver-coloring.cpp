#include <iostream>
#include <vector>
#include <bits/stdc++.h> 

#define COLORS 5

using namespace std;

typedef int V;

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

	// Get the biggest color count.
	int max = -1;
	for (int i = 0; i < COLORS; i++) {
		if (counts[i] > max) {
			max = counts[i];
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

int main () {
	srand(time(0));

	int E_SIZE, V_SIZE, BIN_GOAL;
	cin >> E_SIZE >> V_SIZE >> BIN_GOAL;

	vector<V> vertices;
   	vector<vector<V>> neighbors(V_SIZE);

	init_vectors(vertices, neighbors, V_SIZE, E_SIZE);
	bool result = search(vertices, neighbors, V_SIZE, BIN_GOAL);

	cout << (result ? "possible" : "impossible") << endl;

	return 0;
}
