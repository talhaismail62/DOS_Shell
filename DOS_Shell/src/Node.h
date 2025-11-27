#pragma once
#include <iostream>
#include <String>
#include <vector>
using namespace std;

struct Node {
	string name;
	vector<Node> directories;
	vector<string> files;
};