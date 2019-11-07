#include <iostream>
#include <vector>

#include "vertex.h"

using namespace std;

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
