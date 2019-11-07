#include <vector>
#include <bits/stdc++.h>

#include "vertex.h"

using namespace std;

void remove_vertex (vector<V> &vertices, V vertex) {
	vertices.erase(remove(vertices.begin(), vertices.end(), vertex), vertices.end());
}
