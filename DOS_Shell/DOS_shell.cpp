#include "src/Node.h"
using namespace std;

vector<string> tokenization(string line) {

	vector<string> tokens;

	string temp = "";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ' ') {
			tokens.push_back(temp);
			temp = "";
		}
		else {
			temp += line[i];
		}
	}

	tokens.push_back(temp);

	return tokens;
}

string tolower(string s) {

	for (int i = 0; i < s.size(); i++) {
		s[i] = tolower(s[i]);
	}

	return s;
}

bool isquit(vector<string> tokens) {
	if (tokens.size() == 1) {
		string temp = tolower(tokens[0]);
		if (temp == "exit")
			return true;
	}
	return false;
}

int main() {

	while (true) {
		string line;
		
		cout << "DOS> ";
		getline(cin, line);

		vector<string> tokens = tokenization(line);

		if (isquit(tokens))
			break;
	}

	return 0;
}