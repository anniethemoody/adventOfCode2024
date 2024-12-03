#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iterator>

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

void splitFileToLists(ifstream& inputFile, vector<vector<int> >& list)
{
    string line;
    while (getline(inputFile, line))
    {
        vector<int> lineArray;
        stringstream ss(line);

        int element;
        while (ss >> element) 
        {
            lineArray.push_back(element);
        }
        list.push_back(lineArray);
    }
}

bool checkReportSafety(vector<int> row)
{
    bool safe = true;

    //check 1st condition
    vector<int> rowIncreasing = row;
    vector<int> rowDecreasing = row;
    sort(rowIncreasing.begin(), rowIncreasing.end());
    sort(rowDecreasing.begin(), rowDecreasing.end(), greater<int>());
    if (row != rowIncreasing && row != rowDecreasing) 
    {
        safe = false;
    }

    //check 2nd condition
    else
    {
        for (auto col = row.begin(); col != row.end()-1; ++col)
        {
            int difference = abs(*col - *next(col));
            if(difference < 1 || difference > 3)
            {
                safe = false;
                break;
            }
        }
    }

    return safe;
}

int checkReportsSafety(vector<vector<int> >& list)
{
    int safeReports = 0;
    vector<vector<int> > toErase;

    for (const auto& row : list)
    {
        bool safe = checkReportSafety(row);

        if(safe)
        {
            safeReports++;
            toErase.push_back(row);
        }
    }

    for (const auto& rowToErase : toErase) 
    {
        list.erase(remove(list.begin(), list.end(), rowToErase), list.end());
    }

    return safeReports;
}

int checkReportsSafetyToleratesOneBadLevel(vector<vector<int> >& list)
{
    int safeReports = 0;

    for (const auto& row : list)
    {
        //erase one element until it is safe or reach the end of list
        for (auto col = row.begin(); col != row.end(); ++col)
        {
            vector<int> rowCopy = row;
            rowCopy.erase(rowCopy.begin()+distance(row.begin(), col));

            if(checkReportSafety(rowCopy))
            {
                safeReports++;
                break;
            }
        }
    }

    return safeReports;
}

int main()
{
    //open file
    ifstream inputFile = openFile("input.txt");
    if (!inputFile) {
        return 1;
    }

    //store file in a 2d list
    vector<vector<int> > list;
    splitFileToLists(inputFile, list);

    //check safety of each report (a report == a row from the 2d list), and remove the safe ones from the list
    int safeReportsBefore = checkReportsSafety(list);
    cout << "Total safe reports before new model was introduced: " << safeReportsBefore << endl;

    //check safety of each bad report with tolerating one bad level
    int safeReportsAfter = checkReportsSafetyToleratesOneBadLevel(list) + safeReportsBefore;
    cout << "Total safe reports after new model was introduced: " << safeReportsAfter << endl;

    inputFile.close();
    return 0;
}