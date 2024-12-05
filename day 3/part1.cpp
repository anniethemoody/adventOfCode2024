#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

ifstream openFile(string fileName)
{
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cerr << "Error opening the file!";
        return ifstream();
    }

    return inputFile;
}

string storeFileAsString(ifstream& inputFile)
{
    string line;
    string fileAsString;
    while (getline(inputFile, line)) {
        fileAsString += line;
    }

    return fileAsString;
}

int calculateTotalMultiplications(string file)
{
    int totalMultiplication = 0;

    regex mul("mul\\((\\d{1,3}),(\\d{1,3})\\)");

    auto matchesBegin = sregex_iterator(file.begin(), file.end(), mul);
    auto matchesEnd = sregex_iterator();

    for (auto it = matchesBegin; it != matchesEnd; ++it)
    {
        smatch match = *it;
        int firstNumber = stoi(match[1].str());
        int secondNumber = stoi(match[2].str());
        totalMultiplication += firstNumber  * secondNumber; 
    }

    return totalMultiplication;
}

int main()
{
    //open file
    ifstream inputFile = openFile("input.txt");
    if (!inputFile) {
        return 1;
    }

    //store file into a string
    string file = storeFileAsString(inputFile);

    //calculate result from the restored file
    int totalMultiplication = calculateTotalMultiplications(file);
    cout << "Total multiplications: " << totalMultiplication << endl;

    inputFile.close();
    return 0;
}