#include <iostream>
#include <fstream>

using namespace std;

class item {
public:
    int ino;
protected:
    char name[30];

    virtual void add_details() { }

public:
    void accept();
    void show();

    friend ofstream& operator<<(ofstream &ofs, const item &p);
    friend ifstream& operator>>(ifstream &ifs, item &p);

    int retno();
};

void item::accept() {
    cout << "Enter Item Number : ";
    cin >> ino;
}

void item::show() {
    cout << "\nItem Number is : " << ino;
    if (name == "")
        return;

    cout << "\nName: " << name;
}

ofstream &
operator<<(ofstream &ofs, const item &p) {
    ofs.write((char *)&p.ino, sizeof(p.ino));
    ofs.write((char *)p.name, sizeof(p.name));

    return ofs;
}

ifstream&
operator>>(ifstream &ifs, item &p) {
    ifs.read((char*)&p.ino, sizeof(p.ino));
    ifs.read((char*)p.name, sizeof(p.name));

    return ifs;
}

int
item::retno() {
    return ino;
}
```
This class `item` serves as a base for storing basic item information like number and name.

```cpp
class modern: public item {
public:
    int qnt;

protected:
    float prc;

public:

    void add_details_overload();
    void show_price_quantity();

    friend ofstream& operator<<(ofstream &ofs, const modern &p);
};

void
modern::add_details() {
    cout << "\nEnter Number of Quantity: ";
    cin >> qnt;
}

void 
modern::show_price_quantity() {
    cout << "\nPrice is : " << prc;
    cout << "\nQuatity is : " << qnt;

}
```
This derived class `modern` contains additional fields (`prc`, `qnt`) for item price and quantity.

### Main Menu and File Handling
```cpp
class fileHandler {
public:
    modern amt;

    void add();
    void edit(int);
    void delete_item(int);

    friend ofstream& operator<<(ofstream &ofs, const modern &p);
    friend ifstream& operator>>(ifstream &ifs,  modern &p);
};

void fileHandler::add() { ... }

void fileHandler::edit(int ino) { ... }

void fileHandler::delete_item(int ino) { ... }
```
These methods implement the functionalities to add, edit and delete items from a binary file.

### Main Program Logic
```cpp
int main() {
    ofstream fout;
    ifstream fin;

    cout << "Welcome to Modern Inventory Management System." << endl;
    int choice = 0, ino; 

    while (1) { 
        std::cout << "\nMAIN MENU\n1.Add Item Detail\n2.Edit Item Details\n3.Delete Item Detail\n4.View Item Details \n5.Exit" << endl;

        std::cin >> choice;
        
        switch (choice) {
            case 1:
                fout.open("inventory.dat", ios::binary | ios::app);
                modernHandler.add();
                cout << "Item Added Successfully!" << endl;
                getch();
                break;
                
            case 2: 
                // code to edit item details
                break;

            case 3:
                // code to delete an item 
                break;

            case 4: 
                // show the detail of a chosen index
                break;

            case 5:
                exit(0);
            default:
                cout << "Please Enter Valid Input Choice!" << endl;
                break;
        }
    }   
}
