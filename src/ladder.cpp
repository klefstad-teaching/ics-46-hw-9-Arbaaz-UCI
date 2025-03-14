#include "ladder.h"
#include <algorithm>
using namespace std;

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg << " (\"" << word1 << "\" -> \"" << word2 << "\")" << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d)
{
    if (abs((int)str1.size() - (int)str2.size()) > d) {
        return false;
    }
    if (str1.size() == str2.size()) {
        int diffCount = 0;
        for (size_t i = 0; i < str1.size(); ++i) {
            if (str1[i] != str2[i]) {
                diffCount++;
                if (diffCount > d) return false;
            }
        }
        return diffCount == d;
    } else {
        const string& s1 = (str1.size() < str2.size()) ? str1 : str2;
        const string& s2 = (str1.size() < str2.size()) ? str2 : str1;
        int i = 0, j = 0;
        int mismatch = 0;
        while (i < (int)s1.size() && j < (int)s2.size()) {
            if (s1[i] != s2[j]) {
                mismatch++;
                if (mismatch > d) return false;
                j++;
            } else {
                i++;
                j++;
            }
        }
        if (j < (int)s2.size()) mismatch++;
        return mismatch == d;
    }
}

bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        const string& last_word = ladder.back();
        for (const auto& w : word_list) {
            if (!visited.count(w) && is_adjacent(last_word, w)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(w);
                if (w == end_word) {
                    return new_ladder;
                }
                visited.insert(w);
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream in(file_name);
    if (!in.is_open()) {
        cerr << "Could not open dictionary file: " << file_name << endl;
        return;
    }
    string w;
    while (in >> w) {
        word_list.insert(w);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder)
{
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> r = generate_word_ladder("cat", "dog", word_list);
    if (!r.empty()) {
        cout << "size = " << r.size() << endl;
        print_word_ladder(r);
    } else {
        cout << "no ladder found." << endl;
    }
}
