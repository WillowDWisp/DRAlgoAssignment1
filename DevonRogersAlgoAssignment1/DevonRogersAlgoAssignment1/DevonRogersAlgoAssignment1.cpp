// DevonRogersAlgoAssignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>  
#include <vector>
#include <string>
#include <sstream>

#include <chrono> //this file is used to measure/record the time taken by the sorting function



using namespace std;
//this struct is the backbone of the whole program; it forms the nodes of the linked list that product data is stored in
struct nodeType {
    int id;
    string name;
    float price;
    char category;

    nodeType *link;
};

//initialize various nodes that are used throughout the program
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

    if (tempArray.size() < 3) {
        throw invalid_argument("");
    }

    //this removes a trailing space i was having problems with at the start of the product names. function based off of this code: https://stackoverflow.com/a/39546561 
    if (tempArray[1][0] == ' ') {
        for (int i = 0;i < tempArray[1].size() - 1;i++)
        {
            tempArray[1][i] = tempArray[1][i + 1]; //move all element to the left except first one
        }
        tempArray[1].pop_back();
    }

    while (tempArray[0].size() > 5) {
        tempArray.pop_back();
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
//this function allows the user to insert new products
void insertNode() {
    int answer = 0;
    cout << "How would you like to add a new product?\n1. One attribute at a time.\n2. All attributes at once.\n3. From a file.\n4. Cancel.\n";
    cin >> answer;
    if (answer == 2) {
        cout << "Please enter the details for the new product in the following format, including the commas, and replacing the square brackets with the corresponding attribute: [ID], [Name], [Price], [Category]\n";
        string newProduct;
        cin >> newProduct;

        try {
            insertNode(newProduct); 
        }
        catch (invalid_argument) {
            cout << "Invalid formatting!\n";
            return;
        }



        
        //WARNING: this line is very volatile , and *will* crash the program if the input is formatted wrong.
        //I tried adding default values for when something went wrong, but ended up making things worse

        cout << "Product added!\n";

    }
    else if (answer == 1) {
        newNode = new nodeType;
        string tempArray;


        //yes i did just adapt the code from the other insertNode function

        cout << "Please enter the product's ID. ";
        cin >> tempArray;
        while (tempArray.size() > 5) {
            tempArray.pop_back();
        }
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
                try {
                    insertNode(strDat);
                }
                catch (invalid_argument) { //if a line is incorrectly formatted, catch that and skip it
                    cout << "Invalid line detected, skipping.\n";
                }

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
    if (tolower(cat) == 'b') {
        return "Books";
    }
    if (tolower(cat) == 'c') {
        return "Clothing";
    }
    if (tolower(cat) == 'h') {
        return "Home & Kitchen";
    }
    if (tolower(cat) == 'e') {
        return "Electronics";
    }
    //no custom categories, sorry!
    return "Other";
}

//this function allows the user to search for products automatically
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
//this function updates product details
void updateProduct(bool encore = false) {
    bool found = false;
    if (encore == true) {
        found = true;
    }

    if (encore == false) {
        cout << "Please enter the ID of the product you wish to update. If there are multiple with the same ID, only the first one will be affected.\n";
        cout << "If you would like to go back to the previous menu, enter \"Cancel\"\n";
        string answer;
        cin >> answer;
        if (tolower(answer[0]) == 'c') {
            return;
        }
        int searchID = std::stoi(answer);

        current = first;
        while (current != NULL) {
            if (searchID == current->id) {
                found = true;
                break;
            }
            else {
                current = current->link;
            }
        }
    }

    if (found == true) {
        if (encore == false) {
            cout << "Product found! ";
        }
        cout << "What would you like to modify?\n1. ID\n2. Name\n3. Price\n4. Category\n5. Cancel\n";

        int modifyNum;
        cin >> modifyNum;
        if (modifyNum <= 0 || modifyNum > 4) {
            return;
        }
        cout << "Please enter the new ";
        if (modifyNum == 1) {
            cout << "ID: ";
            cin >> current->id;
            
        }
        else if (modifyNum == 2) {
            cout << "name: ";
            string junk;
            std::getline(cin, junk);
            std::getline(cin, current->name);
        }
        else if (modifyNum == 3) {
            cout << "price: ";
            cin >> current->price;
        }
        else if (modifyNum == 4) {
            cout << "category: ";
            string junk;
            std::getline(cin, junk);
            std::getline(cin, junk);
            current->category = junk[0];
        }
        cout << "Would you like to modify this product further? Y/N\n";
        char encoreAns;
        cin >> encoreAns;
        if (tolower(encoreAns) == 'y') {
            updateProduct(true);
        }
        else { return; }
    }
    else {
        cout << "No product found!\n";
    }
}
//this function cleanly removes a product from the list
void deleteProduct() {
    cout << "Please enter the ID of the product you wish to delete. If there are multiple with the same ID, only the first one will be deleted, unless the last product is a duplicate, then that one will be affected.\n";
    cout << "If you would like to go back to the main menu, enter \"Cancel\"\n";
    string answer;
    cin >> answer;
    if (tolower(answer[0]) == 'c') {
        return;
    }
    int searchID = std::stoi(answer);
    bool found = false;
    //if the product the user wants to delete is the last one, it's faster to do this for printing, although you still need to iterate through for current to be set properly
    bool isLast = false;
    //if the product the user wants to delete is the first one, special handling must be used, otherwise it will be missed
    bool isFirst = false;
    if (searchID == last->id) {
        isLast = true;
    }

    current = first;
    while (current->link != NULL) {
        if (searchID == first->id) {
            isFirst = true;
            found = true;
            break;
        }   

        if (searchID == current->link->id) {
            found = true;
            break;
        }
        else {
            current = current->link;
        }
    }

    if (found == true) {
        cout << "Product found:\n";
        if (isLast) {
            cout << last->id << ", " << last->name << ", " << last->price << ", " << handleCat(last->category) << endl;
        }
        else if (isFirst) {
            cout << first->id << ", " << first->name << ", " << first->price << ", " << handleCat(first->category) << endl;
        }
        else {
            cout << current->link->id << ", " << current->link->name << ", " << current->link->price << ", " << handleCat(current->link->category) << endl;
        }

        cout << "Would you like to delete this product? Y/N\n";

        string reply;

        bool unanswered = true;
        while (unanswered) {
            cin >> reply;
            if (tolower(reply[0]) == 'y') {

                nodeType* temp;
                if (isFirst) {
                    //if the given product is the first product, have temp be equal to first, then move first down the list by one
                    temp = first;
                    first = first->link;
                }
                else {
                    temp = current->link;
                }

                if (!isFirst) {
                    //if the given product is the last product, set current's link to NULL and set last to be current
                    if (temp->link == NULL) {
                        current->link = NULL;
                        last = current;
                    }
                    else {
                        //if the given product is not the first or last product, remove it as normal.
                        current->link = temp->link;

                    }
                }


                delete temp; //this line removes the deleted product from memory, freeing up the space for other uses
                cout << "Product deleted!\n";
                unanswered = false;
            }
            else if (tolower(reply[0]) == 'n') {
                cout << "Would you like to delete a different product? Y/N\n";
                string ans;
                cin >> ans;
                if (tolower(ans[0]) == 'y') {
                    unanswered = false;
                    deleteProduct();
                }
                else {
                    unanswered = false;
                    break;
                }
            }
            else {
                cout << "Invalid command, please try again.\n";
            }
        }

    }
    else {
        cout << "No product with that ID could be found.\n";
    }
}

//this function swaps the values of the node at "current" and the node at "current->link". it is called swapPointers because I originally tried to sort the list by only moving the pointers, which did not work.
void swapPointers() {
    nodeType* tempNode = new nodeType;
    
    tempNode->link = current;

    tempNode->id = current->id;
    tempNode->name = current->name;
    tempNode->price = current->price;
    tempNode->category = current->category;

    current->id = current->link->id;
    current->name = current->link->name;
    current->price = current->link->price;
    current->category = current->link->category;

    current->link->id = tempNode->id;
    current->link->name = tempNode->name;
    current->link->price = tempNode->price;
    current->link->category = tempNode->category;


}

//this function sorts the list of products. it can sort by price in ascending and descending order
    //sorts via bubble sort; code adapted from here: https://www.geeksforgeeks.org/bubble-sort/
    //the code I used for timing the sorting algorithm came from here: https://www.geeksforgeeks.org/chrono-in-c/
void sortProducts() {
    cout << "How would you like the products ordered?\n1. Ascending order\n2. Descending order\n3. Cancel\n";
    int initAns = 0;
    cin >> initAns;
    int listLength = 0;
    //if the user doesn't enter 1 or 2, there's no point wasting time doing everything else this function does
    if (initAns != 1 && initAns != 2) {
        return;
    }
    
    current = first;
    while (current != NULL) {
        listLength++;
        //cout << listLength << endl;
        current = current->link;

    }
    

    current = first;

    int debugCounter = 0;

    cout << "Sorting...\n";

    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    //if the user wants the list sorted in ascending order, use the first option
    if (initAns == 1) {
        for (int i = 0; i < listLength - 1; i++) {
            current = first;
            bool swapped = false;
            for (int j = 0; j < listLength - i - 1; j++) {
                if (current->price > current->link->price) {
                    
                    swapPointers();

                    swapped = true;
                }
                current = current->link;
            }

            //if nothing gets swapped by the inner loop, break the loop to cut down on time
            if (swapped == false) {
                break;
            }
        }
    } //else use the second option
    else {
        for (int i = 0; i < listLength - 1; i++) {
            current = first;
            bool swapped = false;
            for (int j = 0; j < listLength - i - 1; j++) {
                //cout << i << "," << j << endl;
                if (current->price < current->link->price) {
                    swapPointers();
                    
                    swapped = true;
                }
                current = current->link;

            }

            //if nothing gets swapped by the inner loop, break the loop to cut down on time
            if (swapped == false) {
                break;
            }
        }
    }
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    cout << "Sorted! Time taken: " << elapsed_seconds.count() << "s\n";
}


//prints all data from the given line
void printData() {

    current = first;

    while (current != NULL) {
        cout << current->id << ", " << current->name << ", " << current->price << ", " << handleCat(current->category) << endl;
        current = current->link;
    }
}


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
            try {
                insertNode(strDat);
            }
            catch (invalid_argument) {//while this shouldn't happen, it's better to be safe than sorry
                cout << "Invalid line detected, skipping.\n";

            }
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
        updateProduct();
        break;
    case 4:
        deleteProduct();
        break;
    case 5:
        searchProducts();
        break;
    case 6:
        sortProducts();
        break;
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
