#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
        }
        curr->isEndOfWord = true;
    }

    bool search(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }
        return curr->isEndOfWord;
    }

    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }
        return true;
    }

    void suggest(string partial) {
        TrieNode* curr = root;
        for (char c : partial) {
            if (curr->children.find(c) == curr->children.end()) {
                return;
            }
            curr = curr->children[c];
        }
        dfs(curr, partial);
    }

    void dfs(TrieNode* node, string prefix) {
        if (node->isEndOfWord) {
            cout << prefix << endl;
        }
        for (auto child : node->children) {
            dfs(child.second, prefix + child.first);
        }
    }
};

int main() {
    Trie dict;

    //Уважаемый ментор, запишите ваши слова сюда.
    ifstream file("dictionary.txt");
    if (file.is_open()) {
        string word;
        while (getline(file, word)) {
            dict.insert(word);
        }
        file.close();
    }
    else {
        cout << "Failed to open file." << endl;
        return 0;
    }

    string partial = "";
    while (true) {
        cout << "Enter a partial word: ";
        cin >> partial;

        if (dict.search(partial)) {
            cout << "Found word: " << partial << endl;
        }
        else {
            cout << "Suggested words:" << endl;
            dict.suggest(partial);

            string input;
            cin >> input;
            if (dict.search(input)) {
                cout << "Found word: " << input << endl;
            }
            else {
                cout << "Word not found." << endl;
            }
            partial = input;
        }
    }

    return 0;
}
