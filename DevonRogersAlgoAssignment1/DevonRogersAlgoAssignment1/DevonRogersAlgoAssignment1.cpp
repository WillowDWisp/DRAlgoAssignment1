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
    if (tempArray[1][0] == ' ') {
        for (int i = 0;i < tempArray[1].size() - 1;i++)
        {
            tempArray[1][i] = tempArray[1][i + 1]; //move all element to the left except first one
        }
        tempArray[1].pop_back();
    }


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
    int answer = 0;
    cout << "How would you like to add a new product?\n1. One attribute at a time.\n2. All attributes at once.\n3. From a file.\n4. Cancel.\n";
    cin >> answer;
    if (answer == 2) {
        cout << "Please enter the details for the new product in the following format, replacing the square brackets with the corresponding attribute: [ID], [Name], [Price], [Category]\n";
        string newProduct;
        cin >> newProduct;

        //COME BACK TO THIS LATER, SINCE IT'LL BREAK IF THE USER INSERTS SOMETHING INVALID
        insertNode(newProduct);
        cout << "Product added!\n";
    }
    else if (answer == 1) {
        int newId;
        string newName;
        float newPrice;
        char newCat;

        newNode = new nodeType;
        string tempArray;


        //yes i did just adapt the code from the other insertNode function

        cout << "Please enter the product's ID. ";
        cin >> tempArray;
        newNode->id = std::stoi(tempArray);

        cout << "Please enter the product's name. ";
        std::getline(cin, tempArray);
        std::getline(cin, tempArray);
        //this removes a trailing space i was having problems with at the start of the product names. function based off of this code: https://stackoverflow.com/a/39546561 
        //this problem probably won't come up in this situation but better safe than sorry
        if (tempArray[0] == ' ') {
            for (int i = 0;i < tempArray.size() - 1;i++)
            {
                tempArray[i] = tempArray[i + 1]; //move all element to the left except first one
            }
            tempArray.pop_back();
        }
        newNode->name = tempArray;

        cout << "Please enter the product's price. ";
        cin >> tempArray;
        newNode->price = stof(tempArray);

        cout << "Please enter the product's category. ";
        std::getline(cin, tempArray);
        std::getline(cin, tempArray);
        newNode->category = tempArray[0];

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

        cout << "Product added!\n";

    }
    //if the user inserts 3 (or anything else) it returns them to the previous menu
    else if (answer == 3) {
        //string used to pass the data from the text file to the linked list
        string strDat;
        //string that hopefully contains the name of the file the user wants to load
        string userFile;
        cout << "Please enter the name of the file you would like to add products from. Please make sure the file is formatted correctly.\n";
        cin >> userFile;
        //reads from product_data.txt
        ifstream ProductData(userFile);

        if (ProductData.ifstream::is_open()) {
            while (getline(ProductData, strDat)) {
                // runs insertNode for each line in the text file
                insertNode(strDat);

            }
            cout << "Product(s) added!\n";
        }
        else {
            cout << "File not found.";
        }

        ProductData.ifstream::close();
    }
    
    else {
        return;
    }
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
    return "Other";
}

void searchProducts() {
    cout << "How would you like to search?\n1. By ID\n2. By Name\n3. Cancel\n";
    int answer;
    cin >> answer;
    if (answer == 1) {
        cout << "Please enter the ID of the product you wish to view. If the ID is not unique, only the first instance will be returned.\n";
        int searchID;
        cin >> searchID;
        current = first;
        while (current != NULL) {
            if (searchID == current->id) {
                cout << current->id << ", " << current->name << ", " << current->price << ", " << handleCat(current->category) << endl;
                break;
            }
            else {
                current = current->link;
            }
        }
    }
    else if (answer == 2) {
        cout << "Please enter the name of the product(s) you wish to view. All valid products will be returned.\n";
        string searchName;
        std::getline(cin, searchName);
        std::getline(cin, searchName);
        current = first;
        while (current != NULL) {
            if (searchName.size() > current->name.size()) {
                current = current->link;
                continue;
            }

            for (int i = 0; i < searchName.size();i++) {
                if (tolower(searchName[i]) != tolower(current->name[i])) {
                    current = current->link;
                    break;
                }
                else if (i == searchName.size() - 1) {
                    cout << current->id << ", " << current->name << ", " << current->price << ", " << handleCat(current->category) << endl;
                    current = current->link;
                }
            }



        }
    }
    else {
        return;
    }
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



bool running = true;

void displayCommands() {
    cout << "1. Display products\n2. Insert product\n3. Update product details\n4. Delete product\n5. Search products\n6. Sort products\n7. Quit\n";

}

void runtimeLoop() {
    cout << "To view the commands again, enter 0.\nWhat would you like to do? ";
    int answer;
    cin >> answer;
    switch (answer) {
    case 0:
        displayCommands();
        break;
    case 1:
        printData();
        break;
    case 2:
        insertNode();
        break;
    case 3:
    case 4:
    case 5:
        searchProducts();
        break;
    case 6:
    case 7:
        cout << "Have a good day!";
        running = false;
        break;

    default:
        cout << "Invalid command. Please try again.";
        break;
    }
}

int main()
{
    loadData();
    displayCommands();
    while (running) {
        runtimeLoop();
    }


    //printData();

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
