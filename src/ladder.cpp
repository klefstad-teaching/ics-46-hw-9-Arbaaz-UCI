#include "ladder.h"
#include <algorithm>
using namespace std;

void error(string w1, string w2, string msg)
{
    cerr << msg << endl;
}

bool edit_distance_within(const string& s1, const string& s2, int d)
{
    if (abs((int)s1.size() - (int)s2.size()) > d) return false;
    int i = 0, j = 0, mismatch = 0;
    while (i < (int)s1.size() && j < (int)s2.size()) {
        if (s1[i] != s2[j]) {
            mismatch++;
            if (mismatch > d) return false;
            if (s1.size() > s2.size()) i++;
            else if (s1.size() < s2.size()) j++;
            else { i++; j++; }
        } else {
            i++;
            j++;
        }
    }
    mismatch += (s1.size() - i) + (s2.size() - j);
    return mismatch <= d;
}

bool is_adjacent(const string& w1, const string& w2)
{
    return edit_distance_within(w1, w2, 1);
}

static vector<string> generate_neighbors(const string& word, const set<string>& dict)
{
    vector<string> result;
    for (int i = 0; i < (int)word.size(); i++) {
        string del = word.substr(0,i) + word.substr(i+1);
        if (dict.find(del) != dict.end()) result.push_back(del);
    }
    for (int i = 0; i < (int)word.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (word[i] == c) continue;
            string rep = word;
            rep[i] = c;
            if (dict.find(rep) != dict.end()) result.push_back(rep);
        }
    }
    for (int i = 0; i <= (int)word.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            string ins = word.substr(0,i) + c + word.substr(i);
            if (dict.find(ins) != dict.end()) result.push_back(ins);
        }
    }
    return result;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (word_list.find(end_word) == word_list.end()) return {};
    set<string> dict = word_list;
    if (dict.find(begin_word) == dict.end()) dict.insert(begin_word);
    queue<vector<string>> q;
    q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();
        string last = path.back();
        vector<string> neighbors = generate_neighbors(last, dict);
        for (auto &n : neighbors) {
            if (!visited.count(n)) {
                visited.insert(n);
                vector<string> new_path = path;
                new_path.push_back(n);
                if (n == end_word) return new_path;
                q.push(new_path);
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream in(file_name);
    if (!in.is_open()) {
        cerr << "Could not open file." << endl;
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
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (auto &w : ladder) cout << w << " ";
    cout << endl;
}

void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> r = generate_word_ladder("cat","dog",word_list);
    if (r.empty()) cout << "No word ladder found." << endl;
    else print_word_ladder(r);
}
