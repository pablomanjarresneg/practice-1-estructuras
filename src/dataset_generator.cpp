#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <filesystem>

using namespace std;

static const int DATASET_SIZE = 100000;

void generateDataset(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile);
    if (!in.is_open()) {
        cerr << "Error opening file: " << inputFile << endl;
        return;
    }

    vector<string> words;
    string word;
    while (getline(in, word)) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }
    in.close();

    mt19937 rng(random_device{}());
    shuffle(words.begin(), words.end(), rng);

    int count = min(DATASET_SIZE, static_cast<int>(words.size()));

    ofstream out(outputFile);
    for (int i = 0; i < count; i++) {
        out << words[i] << "\n";
    }
    out.close();

    cout << "dataset.txt created with " << count << " words." << endl;
}

int main() {
    namespace fs = filesystem;

    fs::path input;
    if (fs::exists("data/words_alpha.txt")) {
        input = "data/words_alpha.txt";
    } else if (fs::exists("../data/words_alpha.txt")) {
        input = "../data/words_alpha.txt";
    } else {
        cerr << "Cannot find words_alpha.txt\n";
        return 1;
    }

    fs::path output = input.parent_path() / "dataset.txt";
    generateDataset(input.string(), output.string());
    return 0;
}
