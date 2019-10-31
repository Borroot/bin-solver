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
		cin >> v1;
		cin >> v2;
		neighbors[v1-1].push_back(v2-1);
		neighbors[v2-1].push_back(v1-1);
	}
}

void remove_vertex (vector<V> &vertices, const V vertex) {
	vertices.erase(remove(vertices.begin(), vertices.end(), vertex), vertices.end());
}

int highest (const vector<V> &colors) {
	vector<int> counts(COLORS);
	for (int i = 0; i < (int)colors.size(); i++) {
		counts[colors[i]]++;
	}

	int max = -1;
	for (int i = 0; i < (int)counts.size(); i++) {
		if (counts[i] > max) {
			max = counts[i];
		}
	}
	return max;
}

int choose_color (const V &current, const vector<V> &colors, const vector<vector<V>> &neighbors) {
	bool legal_color[COLORS];
	for (int i = 0; i < COLORS; i++) {
		legal_color[i] = true;
	}

	for (int i = 0; i < (int)neighbors[current].size(); i++) {
		legal_color[colors[neighbors[current][i]]] = false;
	}

	for (int i = 0; i < COLORS; i++) {
		if (legal_color[i]) {
			return i;
		}
	}
	return COLORS - 1;
}

int color (vector<V> vertices, const vector<vector<V>> &neighbors, const int &V_SIZE) {
	vector<V> colors(V_SIZE);

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

	do {
		result = color (vertices, neighbors, V_SIZE);
		count++;
	} while (result < BIN_GOAL && count < MAX);

	return result >= BIN_GOAL;
}

int main () {
	srand(time(0));

	int E_SIZE, V_SIZE, BIN_GOAL;
	cin >> E_SIZE;
	cin >> V_SIZE;
	cin >> BIN_GOAL;

	vector<V> vertices;
   	vector<vector<V>> neighbors(V_SIZE);

	init_vectors(vertices, neighbors, V_SIZE, E_SIZE);
	bool result = search(vertices, neighbors, V_SIZE, BIN_GOAL);

	cout << (result ? "possible" : "impossible") << endl;

	return 0;
}
