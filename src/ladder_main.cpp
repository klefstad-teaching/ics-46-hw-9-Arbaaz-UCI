#include "ladder.h"
using namespace std;

int main()
{
    string startWord, endWord;
    cin >> startWord >> endWord;
    if (startWord == endWord) {
        cout << "No word ladder found." << endl;
        return 0;
    }
    set<string> word_list;
    load_words(word_list, "words.txt");
    vector<string> ladder = generate_word_ladder(startWord, endWord, word_list);
    print_word_ladder(ladder);
    return 0;
}
