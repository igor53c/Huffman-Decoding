// Huffman Decoding.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

typedef struct node {

	int freq;
	char data;
	node* left;
	node* right;

} node;

struct deref :public binary_function<node*, node*, bool> {
	bool operator()(const node* a, const node* b)const {
		return a->freq > b->freq;
	}
};

typedef priority_queue<node*, vector<node*>, deref> spq;

node* huffman_hidden(string s) {

	spq pq;
	vector<int>count(256, 0);

	for (int i = 0; i < s.length(); i++) {
		count[s[i]]++;
	}

	for (int i = 0; i < 256; i++) {

		node* n_node = new node;
		n_node->left = nullptr;
		n_node->right = nullptr;
		n_node->data = (char)i;
		n_node->freq = count[i];

		if (count[i] != 0)
			pq.push(n_node);

	}

	while (pq.size() != 1) {

		node* left = pq.top();
		pq.pop();
		node* right = pq.top();
		pq.pop();
		node* comb = new node;
		comb->freq = left->freq + right->freq;
		comb->data = '\0';
		comb->left = left;
		comb->right = right;
		pq.push(comb);

	}

	return pq.top();

}

void print_codes_hidden(node* root, string code, map<char, string>& mp) {

	if (root == nullptr)
		return;
	if (root->data != '\0') {
		mp[root->data] = code;
	}

	print_codes_hidden(root->left, code + '0', mp);
	print_codes_hidden(root->right, code + '1', mp);

}

void decode_huff(node* root, string s) {

	string output;

	node* head = root;

	for (char ch : s)
	{
		switch (ch)
		{
		case '0':
		{
			if (root->left->data != NULL)
			{
				output += root->left->data;
				root = head;
			}
			else
			{
				root = root->left;
			}
		}
			break;
		case '1':
		{
			if (root->right->data != NULL)
			{
				output += root->right->data;
				root = head;
			}
			else
			{
				root = root->right;
			}
		}
			break;
		}
	}

	cout << output << endl;
}

int main() {

	string s;
	std::cin >> s;

	node* tree = huffman_hidden(s);
	string code;

	map<char, string> mp;
	print_codes_hidden(tree, code, mp);

	string coded;

	for (char & i : s) {
		coded += mp[i];
	}

	decode_huff(tree, coded);

	return 0;
}