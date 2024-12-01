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

int calculateTotalSimilarityScore(vector<int> list1, vector<int> list2)
{
    int totalSimilarityScore = 0;

    while (!list1.empty())
    {
        int topNumList1 = list1.front();
        int occuranceOfTopNumList2 = count(list2.begin(), list2.end(),topNumList1);

        int similarityScore = topNumList1 * occuranceOfTopNumList2;
        totalSimilarityScore += similarityScore;

        list1.erase(find(list1.begin(), list1.end(), topNumList1));
    }

    return totalSimilarityScore;
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

    //calculate total similarity score
    int totalSimilarityScore = calculateTotalSimilarityScore(list1, list2);
    cout << "Total similarity score: " << totalSimilarityScore << endl;

    inputFile.close();
    return 0;
}