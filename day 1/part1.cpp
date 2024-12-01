#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

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

void splitFileToLists(ifstream& inputFile, vector<int>& list1, vector<int>& list2)
{
    string line;
    while (getline(inputFile, line))
    {
        int num1, num2;
        stringstream ss(line);
        ss >> num1 >> num2;

        list1.push_back(num1);
        list2.push_back(num2);
    }
}

int calculateTotalDistance(vector<int> list1, vector<int> list2)
{
    int totalDistance = 0;

    while (!list1.empty() && !list2.empty())
    {
        int minNumList1 = *min_element(begin(list1), end(list1));
        int minNumList2 = *min_element(begin(list2), end(list2));

        int distance = abs(minNumList1 - minNumList2);
        totalDistance += distance;

        list1.erase(find(list1.begin(), list1.end(), minNumList1));
        list2.erase(find(list2.begin(), list2.end(), minNumList2));
    }

    return totalDistance;
}

int main()
{
    //open file
    ifstream inputFile = openFile("input.txt");
    if (!inputFile) {
        return 1;
    }

    //store file in 2 lists
    vector<int> list1, list2;
    splitFileToLists(inputFile, list1, list2);

    //calculate total distance
    int totalDistance = calculateTotalDistance(list1, list2);
    cout << "Total distance: " << totalDistance << endl;

    inputFile.close();
    return 0;
}