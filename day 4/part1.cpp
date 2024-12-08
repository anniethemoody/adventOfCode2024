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

bool determineDirection (vector<vector<char> >& list, int& row, int& col, int directionIndex)
{
    bool invalid = true;
    switch(directionIndex)
        {
            case 0:
                if(row - 1 >= 0)
                {   row--;
                    invalid = false;
                }
                break;
            case 1:
                if(row - 1>= 0 && col - 1 >= 0)
                {
                    row--;
                    col--;
                    invalid = false;
                }
                break;
            case 2:
                if(col - 1 >= 0)
                {
                    col--;
                    invalid = false;
                }
                break;
            case 3:
                if(row + 1 < list.size() && col - 1 >= 0)
                {
                    row++;
                    col--;
                    invalid = false;
                }
                break;
            case 4:
                if(row + 1 < list.size())
                {
                    row++;
                    invalid = false;
                }
                break;
            case 5:
                if(row + 1 < list.size() && col + 1 < list[row].size())
                {
                    row++;
                    col++;
                    invalid = false;
                }
                break;
            case 6:
                if(col + 1 < list[row].size())
                {
                    col++;
                    invalid = false;
                }
                break;
            case 7:
                if(row - 1 >= 0 && col + 1 < list[row].size())
                {
                    row--;
                    col++;
                    invalid = false;
                }
                break;
            default:
                cout << "Invalid choice." << endl;
        }

        return invalid;
}

void findOccurancesXMASPerDirection(vector<vector<char> >& list, int row, int col, int directionIndex, int& numOfOccurances, int& xmasIndex)
{
    //base case
    if(xmasIndex == 4)
    {
        numOfOccurances++;
        return;
    }

    if (list[row][col] == XMAS[xmasIndex])
    {
        xmasIndex++;
        if (determineDirection(list, row, col, directionIndex) && xmasIndex != 4)
        {
            return;
        }
    }

    else
    {
        xmasIndex = 0;
        return;
    }

    findOccurancesXMASPerDirection(list, row, col, directionIndex, numOfOccurances, xmasIndex);
    return;
}

void findOccurancesXMASForOnePosition(vector<vector<char> >& list, int row, int col, int directionIndex, int& numOfOccurances, int& xmasIndex)
{
    //base case
    if(directionIndex == 8)
    {
        directionIndex = 0;
        return;
    }

    if(list[row][col] == XMAS[0])
    {
        findOccurancesXMASPerDirection(list, row, col, directionIndex, numOfOccurances, xmasIndex); 
        directionIndex++;
        xmasIndex = 0;
        findOccurancesXMASForOnePosition(list, row, col, directionIndex, numOfOccurances, xmasIndex);
    }
    return;
}

void findOccurancesXMAS(vector<vector<char> >& list, int row, int col, int directionIndex, int& numOfOccurances, int& xmasIndex)
{   
    if(row + 1 > list.size())
    {
        return;
    }

    findOccurancesXMASForOnePosition(list, row, col, directionIndex, numOfOccurances, xmasIndex);

    //shift to next character
    if(col + 1 < list[row].size())
    {
        col++;
    }
    else
    {
        row++;
        col = 0;
    }
    directionIndex = 0;

    findOccurancesXMAS(list, row, col, directionIndex, numOfOccurances, xmasIndex);

    return;
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

    //find occurances of XMAS in all direction (horizontal, vertical, diagonal, written backwards)
    int row, col, directionIndex, numOfOccurances, xmasIndex = 0;
    findOccurancesXMAS(list, row, col, directionIndex, numOfOccurances, xmasIndex);

    cout << "Total number of occurances of \"XMAS\" is: " << numOfOccurances << endl;
    
    inputFile.close();
    return 0;
}