#include <vector>

#include "vertex.h"
#include "remove_vertex.h"

using namespace std;

// Remove all the references to vertex inside of the neighbors from other vertices.
void remove_edges (const V &vertex, vector<vector<V>> &neighbors) {
	for (int i = 0; i < (int)neighbors.size(); i++) {
		remove_vertex(neighbors[i], vertex);
	}
}

// Determine whether vertices1 is a subset of vertices2.
bool subset (const vector<V> &vertices1, const vector<V> &vertices2) {
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

// Here we filter out vertices based on the following criteria:
// if the neighbors of the current vertex are a subset of the 
// neighbors of a neighbor of the current vertex then remove this
// neighbor from the vertices left. This can be done since we 
// know that it is always more beneficial to choose the current
// vertex instead of this particular neighbor. 
void filter (vector<V> &vertices, vector<vector<V>> &neighbors) {
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
