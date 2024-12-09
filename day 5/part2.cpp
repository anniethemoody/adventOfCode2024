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

vector<int> reorderIncorrectUpdates(unordered_map<int, vector<int> > pageOrderingRules_hashmap, vector<int> row)
{
    vector<int> newRow(row.size(),0);
    
    //copy old hashmap to a new hashmap
    unordered_map<int, vector<int> > newHashMap = pageOrderingRules_hashmap;

    //get rid off numbers that are not in the row in the new hashmap
    for (auto it = newHashMap.begin(); it != newHashMap.end();)
    {
        int key = it->first;
        vector<int>& values = it->second;

        //delete key & values if key is not in current update(row)
        auto it_key = find(row.begin(), row.end(), key);
        if (it_key == row.end())
        {
            it = newHashMap.erase(it);
            continue;
        }

        //delete element in values if they are not in current update(row)
        vector<int> copyValues = values;
        for(int element: copyValues)
        {
            auto it_element = find(row.begin(), row.end(), element);
            if (it_element == row.end())
            {
                values.erase(remove(values.begin(), values.end(), element), values.end());
            }
        }
        ++it;
    }

    //order them based on descending order of size of each key
    for (auto it = newHashMap.begin(); it != newHashMap.end(); ++it)
    {
        int key = it->first;
        vector<int>& values = it->second;

        newRow[row.size() - (values.size()+1)] = key;
    }

    return newRow;
}

vector<int> checkRulesForEachLine(unordered_map<int, vector<int> > pageOrderingRules_hashmap, vector<int> row)
{
    vector<int> newRow(row.size(),0);
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
                    newRow = reorderIncorrectUpdates(pageOrderingRules_hashmap, row);
                    return newRow;
                }
            }
        }
        else if (startIndex == row.size())
        {
            return newRow;
        }
        else
        {
            newRow = reorderIncorrectUpdates(pageOrderingRules_hashmap, row);
            return newRow;
        }
    }
}

int calculateCorrectUpdates(unordered_map<int, vector<int> > pageOrderingRules_hashmap, vector<vector<int> >& update_list)
{
    int sumOfMiddleNumberOfCorrectUpdates = 0;

    for (const auto& row : update_list)
    {
        vector<int> newRow = checkRulesForEachLine(pageOrderingRules_hashmap, row);
        if (newRow.size() != 0)
        {
            int middleIndex = newRow.size()/2;
            sumOfMiddleNumberOfCorrectUpdates += newRow[middleIndex];
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

    cout << "Total number of occurances of the middle page number from the incorrectly-ordered updates is: " 
    << sumOfMiddleNumberOfCorrectUpdates << endl;
    
    inputFile.close();
    return 0;
}