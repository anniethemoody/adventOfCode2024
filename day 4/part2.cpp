#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

const string XMAS = "XMAS";
const string DIRECTION[8] = {"N","NW","W","SW","S","SE","E","NE"};

ifstream openFile(string fileName)
{
    ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        cerr << "Error opening the file!";
        return ifstream();
    }

    return inputFile;
}

void storeFileToLists(ifstream& inputFile, vector<vector<char> >& list)
{
    string line;
    while (getline(inputFile, line))
    {
        vector<char> lineArray;
        for (size_t i = 0; i < line.size(); ++i)
        {
            lineArray.push_back(line[i]);
        }
        list.push_back(lineArray);
    }
}

int findOccurancesX_MASPerA(vector<vector<char> >& list, int row, int col)
{
    int numOfOccurances = 0;
    if (((list[row - 1][col - 1] == 'S' && list[row + 1][col + 1] == 'M') ||
    (list[row - 1][col - 1] == 'M' && list[row + 1][col + 1] == 'S')) &&
    ((list[row - 1][col + 1] == 'S' && list[row + 1][col - 1] == 'M') ||
    (list[row - 1][col + 1] == 'M' && list[row + 1][col - 1] == 'S')))
    {
        numOfOccurances++;
    }
    return numOfOccurances;
}

int findOccurancesX_MAS(vector<vector<char> >& list)
{
    int numOfOccurances = 0;
    //find position of A
    for (int row = 1; row < list.size()-1; ++row)
    {
        for (int col = 1; col < list[row].size()-1; ++col)
        {
            if(list[row][col] == 'A')
            {
                numOfOccurances += findOccurancesX_MASPerA(list, row, col);
            }
        }
    }
    return numOfOccurances;
}

int main()
{
    //open file
    ifstream inputFile = openFile("input.txt");
    if (!inputFile) {
        return 1;
    }

    //store into 2d vector
    vector<vector<char> > list;
    storeFileToLists(inputFile, list);

    //find occurances of X-MAS
    int numOfOccurances = findOccurancesX_MAS(list);

    cout << "Total number of occurances of \"X-MAS\" is: " << numOfOccurances << endl;
    
    inputFile.close();
    return 0;
}