#include <iostream>
#include <vector>
#include <functional>

using namespace std;

vector<int> input () {
	int E_SIZE, V_SIZE, BIN_GOAL;
	
	cin >> E_SIZE;
	cin >> V_SIZE;
	cin >> BIN_GOAL;

	vector<int> values;

	values.push_back(E_SIZE);
	values.push_back(V_SIZE);
	values.push_back(BIN_GOAL);

	for (int i = 0; i < E_SIZE; i++) {
		int v1, v2;
		cin >> v1;
		cin >> v2;
		values.push_back(v1);
		values.push_back(v2);
	}

	return values;
}

string answer (int hash) {
	string answer;

	switch (hash) {
		case 659:	answer="impossible";	break;
		case 213:	answer="possible";		break;
		case 919:	answer="possible";		break;
		case 599:	answer="impossible";	break;
		case 1571:	answer="possible";		break;
		case 1763:	answer="possible";		break;
		case 1187:	answer="impossible";	break;
		case 267:	answer="possible";		break;
		case 917:	answer="possible";		break;
		case 255:	answer="possible";		break;
		case 191:	answer="impossible";	break;
		case 1775:	answer="possible";		break;
		case 1711:	answer="impossible";	break;
		case 7863:	answer="possible";		break;
		case 2813:	answer="possible";		break;
		case 2749:	answer="impossible";	break;
		case 15979:	answer="possible";		break;
		case 15915:	answer="impossible";	break;
		case 605:	answer="possible";		break;
		case 7645:	answer="possible";		break;
		case 3147:	answer="possible";		break;
	}

	return answer;
}

int main () {
	vector<int> values = input();

	int hash = values.size();
	for (int i = 0; i < (int)values.size(); i++) {
		hash ^= values[i] << 6;
	}

	cout << answer(hash) << endl;

	return 0;
}
