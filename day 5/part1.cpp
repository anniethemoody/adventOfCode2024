#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>

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

void storeFileToLists(ifstream& inputFile, unordered_map<int, vector<int> > & pageOrderingRules_hashmap, vector<vector<int> >& update_list)
{
    string line;
    while (getline(inputFile, line) && !line.empty())
    {
        stringstream ss(line);
        string firstNum, secondNum;
        getline(ss, firstNum, '|');
        getline(ss, secondNum);

        pageOrderingRules_hashmap[stoi(firstNum)].push_back(stoi(secondNum));
    }

    while (getline(inputFile, line))
    {
        vector<int> lineArray;

        stringstream ss(line);
        string num;
        while (getline(ss, num, ','))
        {
            lineArray.push_back(stoi(num));
        }
        if (!ss.eof()) {
            lineArray.push_back(stoi(num));
        }
        
        update_list.push_back(lineArray);
    }
}

bool checkRulesForEachLine(unordered_map<int, vector<int> > pageOrderingRules_hashmap, vector<int> row)
{
    for (const auto& col : row)
    {
        auto key = pageOrderingRules_hashmap.find(col);
        int startIndex = distance(row.begin(), find(row.begin(), row.end(), col)) + 1;

        if(key != pageOrderingRules_hashmap.end() && startIndex < row.size())
        {
            vector<int> value = key->second;

            for (int i = startIndex; i < row.size(); ++i)
            {
                auto it = find(value.begin(), value.end(), row[i]);
                if(it == value.end())
                {
                    return false;
                }
            }
        }
        else if (startIndex == row.size())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

int calculateCorrectUpdates(unordered_map<int, vector<int> > pageOrderingRules_hashmap, vector<vector<int> >& update_list)
{
    int sumOfMiddleNumberOfCorrectUpdates = 0;

    for (const auto& row : update_list)
    {
        if (checkRulesForEachLine(pageOrderingRules_hashmap, row))
        {
            int middleIndex = row.size()/2;
            sumOfMiddleNumberOfCorrectUpdates += row[middleIndex];
        }
    }

    return sumOfMiddleNumberOfCorrectUpdates;
}

int main()
{
    //open file
    ifstream inputFile = openFile("input.txt");
    if (!inputFile) {
        return 1;
    }

    //store file into hashmap
    unordered_map<int, vector<int> > pageOrderingRules_hashmap;
    vector<vector<int> > update_list;
    storeFileToLists(inputFile, pageOrderingRules_hashmap, update_list);

    int sumOfMiddleNumberOfCorrectUpdates = calculateCorrectUpdates(pageOrderingRules_hashmap, update_list);

    cout << "Total number of occurances of the middle page number from the correctly-ordered updates is: " 
    << sumOfMiddleNumberOfCorrectUpdates << endl;
    
    inputFile.close();
    return 0;
}