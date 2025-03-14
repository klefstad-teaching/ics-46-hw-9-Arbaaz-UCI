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
    vector<string> res;
    for (int i = 0; i < (int)word.size(); i++) {
        string removed = word.substr(0,i) + word.substr(i+1);
        if (dict.count(removed)) res.push_back(removed);
    }
    for (int i = 0; i < (int)word.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            if (word[i] == c) continue;
            string replaced = word;
            replaced[i] = c;
            if (dict.count(replaced)) res.push_back(replaced);
        }
    }
    for (int i = 0; i <= (int)word.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            string inserted = word.substr(0,i) + c + word.substr(i);
            if (dict.count(inserted)) res.push_back(inserted);
        }
    }
    sort(res.begin(), res.end());
    res.erase(unique(res.begin(), res.end()), res.end());
    return res;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if (!word_list.count(end_word)) return {};
    set<string> dict = word_list;
    if (!dict.count(begin_word)) dict.insert(begin_word);
    queue<vector<string>> q;
    q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();
        string last = path.back();
        vector<string> nbrs = generate_neighbors(last, dict);
        for (auto &w : nbrs) {
            if (!visited.count(w)) {
                visited.insert(w);
                vector<string> newp = path;
                newp.push_back(w);
                if (w == end_word) return newp;
                q.push(newp);
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
    vector<string> r = generate_word_ladder("cat", "dog", word_list);
    if (r.empty()) cout << "No word ladder found." << endl;
    else print_word_ladder(r);
}
