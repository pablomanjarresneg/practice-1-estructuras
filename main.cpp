#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("data/dataset.txt");

    if (!in.is_open()) { cerr << "Error opening file" << endl; return 1; }

    vector<string> words;
    string word;

    while (getline(in,word))
    {
        if (!word.empty()) { words.push_back(word); }
    }
    in.close();

    cout << "Loaded " << words.size() << " words." << endl;
    cout << "\nFirst 20 words from dataset.txt:\n";

    for (size_t i = 0; i < words.size() && i < 20; i++)
    {
        cout << words[i] << endl;
    }
    return 0;
}