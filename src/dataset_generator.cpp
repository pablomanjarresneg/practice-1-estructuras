//
// Created by Pablo Manjarres on 21/03/26.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;

void generateDataset(const string& fileName, const string& outputFile)
{
    ifstream in(fileName);

    if (!in.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    vector<string> words;
    string word;

    while (getline(in, word))
    {
        if (!word.empty())
        {
            words.push_back(word);
        }
    }
    in.close();

    //Shuffle using a Mersenne Twister engine (seeded randomly)
    mt19937 rng(random_device{}());
    shuffle(words.begin(), words.end(), rng);

    ofstream out(outputFile);
    for (const auto& w : words)
    {
        out << w << endl;
    }
    cout << "dataset.txt created with" << words.size() << " words." << endl;
}

int main()
{
    generateDataset("words_alpha.txt", "dataset.txt");
    return 0;
}