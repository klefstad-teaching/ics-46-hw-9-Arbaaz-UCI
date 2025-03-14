#include "ladder.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "Enter the start word: ";
    string startWord;
    cin >> startWord;
    cout << "Enter the end word: ";
    string endWord;
    cin >> endWord;
    if (startWord == endWord) {
        error(startWord, endWord, "Start and end words cannot be the same");
        return 0;
    }
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> ladder = generate_word_ladder(startWord, endWord, word_list);
    if (ladder.empty()) {
        cout << "No ladder found from \"" << startWord << "\" to \"" << endWord << "\"." << endl;
    } else {
        cout << "Found ladder:" << endl;
        print_word_ladder(ladder);
    }
    return 0;
}
