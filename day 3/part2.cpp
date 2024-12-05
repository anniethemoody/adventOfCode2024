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

    bool enabled = true;

    regex mul("(do\\(\\)|don't\\(\\)|mul\\((\\d{1,3}),(\\d{1,3})\\))");

    smatch match;
    string::const_iterator searchStart(file.cbegin());

    while (regex_search(searchStart, file.cend(), match, mul))
    {
        string fullMatch = match[0].str();

        if(fullMatch == "do()")
        {
            enabled = true; 
        }
        
        else if (fullMatch == "don't()") 
        {
            enabled = false; 
        }

        else if (match[2].matched && match[3].matched)
        {
            if (enabled) 
            {
                int firstNumber = stoi(match[2].str());
                int secondNumber = stoi(match[3].str());
                totalMultiplication += firstNumber * secondNumber; 
            }
        }

        searchStart = match.suffix().first;
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