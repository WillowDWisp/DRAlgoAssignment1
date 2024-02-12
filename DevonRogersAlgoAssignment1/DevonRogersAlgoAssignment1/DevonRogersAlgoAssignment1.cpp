// DevonRogersAlgoAssignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>  
#include <vector>
#include <string>
#include <sstream>


using namespace std;

//template <typename T>;

/*start of massive debug comment*/

struct nodeType {
    int id;
    string name;
    float price;
    char category;

    nodeType *link;
};

nodeType* first, * last, * newNode;
nodeType* current;



void insertNode(string line) {
    newNode = new nodeType;

    vector<string> tempArray;

    std::istringstream iss(line);
    string s;
    while (std::getline(iss, s, ',')) {
        tempArray.push_back(s);

    }

    //this removes a trailing space i was having problems with at the start of the product names. function based off of this code: https://stackoverflow.com/a/39546561 
    for (int i = 0;i < tempArray[1].size() - 1;i++)
    {
        tempArray[1][i] = tempArray[1][i + 1]; //move all element to the left except first one
    }
    tempArray[1].pop_back();

    newNode->id = std::stoi(tempArray[0]);
    newNode->name = tempArray[1];
    newNode->price = stof(tempArray[2]);
    newNode->category = tempArray[3][1];

    newNode->link = NULL;

    //from page 274/275 of the Malik C++ textbook
    if (first == NULL) {
        first = newNode;
        last = newNode;
    }
    else {
        last->link = newNode;
        last = newNode;
    }

}

void insertNode() {

}

//the list of product data stores the categories as characters to save space. this function turns that data back into categories
string handleCat(char cat) {
    if (cat == 'B') {
        return "Books";
    }    
    if (cat == 'C') {
        return "Clothing";
    }    
    if (cat == 'H') {
        return "Home & Kitchen";
    }    
    if (cat == 'E') {
        return "Electronics";
    }
    return "uh oh";
}

//advances the position of 'current'
void advanceCurrent() {
    current = current->link;
}

//returns current to the beginning of the list
void resetCurrent() {
    current = first;
}

//prints all data from the given line
void printData() {

    current = first;

    while (current != NULL) {
        cout << current->id << ", " << current->name << ", " << current->price << ", " << handleCat(current->category) << endl;
        current = current->link;
    }
}

/*end of massive debug comment*/

void loadData() {
    first = NULL;
    last = NULL;

    //string used to pass the data from the text file to the linked list
    string strDat;
    //reads from product_data.txt
    ifstream ProductData("product_data.txt");

    if (ProductData.ifstream::is_open()) {
        while (getline(ProductData, strDat)) {
            // runs insertNode for each line in the text file
            insertNode(strDat);

        }
    }
    else {
        cout << "File not found";
    }

    ProductData.ifstream::close();
    current = first;
}

int main()
{
    loadData();



    printData();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
