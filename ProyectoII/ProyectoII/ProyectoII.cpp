#include <iostream>
#include "DATO.h"
#include "Node.h"
#include "AVL.h"
#include <string>
#include <sstream>
#include <fstream>
#include <codecvt>
using namespace std;
void Inorder(Node* p);
int validateNumber(string msj);
bool check_number(string str);
char findDelimiter(string str);

/**
* The byRow struct corresponds to the use of operator overloading for the row-column tree,
* basically its purpose is to overload the operators =, < to use it in the order
* of traversal of the respective tree.
*/
struct byRow
{
    Node* operator()(Node* p, int i, int j)
    {
        Node* result;
        if (i == p->_data->getRow()) { j < p->_data->getColumn() ? result = p->leftChild : result = p->rightChild; }
        else if (i < p->_data->getRow()) { result = p->leftChild; }
        else { result = p->rightChild; }
        return result;
    }
};

/**
* The byColumn struct corresponds to the use of operator overloading for the column-row tree,
* basically its purpose is to overload the operators =, < to use it in the order
* of traversal of the respective tree.
*/
struct byColumn
{
    Node* operator()(Node* p, int i, int j)
    {
        Node* result;
        if (j == p->_data->getColumn()) { i < p->_data->getRow() ? result = p->leftChild : result = p->rightChild; }
        else if (j < p->_data->getColumn()) { result = p->leftChild; }
        else { result = p->rightChild; }
        return result;
    }
};

int main()
{
 
    ifstream file;
    AVL* rowColumn = new AVL;
    AVL* columnRow = new AVL;
    string op = "20";
    int row, column, value, i0, i, j0, j;
    tuple<bool, Node*> result;
    while (op != "8") {
        system("cls");
        cout << "0.Read csv" << endl;
        cout << "1.Insert (i,j)" << endl;
        cout << "2.Delete (i,j)" << endl;
        cout << "3.Show InOrder Tree" << endl;
        cout << "4.First of the row (i)" << endl;
        cout << "5.Show Row i" << endl;
        cout << "6.Sum rectangle" << endl;
        cout << "7.Search node(i,j)" << endl;
        cout << "9.Delete all nodes of row i" << endl;
        cout << "8.Close" << endl;

        if (op == "0")
        {
            std::wifstream wif(L"tree.csv");
            wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
            std::wstringstream wss;
            wss << wif.rdbuf();
            std::wstring line;
            row = 1;
            column = 1;
            string dato2 = "";
            char delimiter = '*';
            while (getline(wss, line))
            {
                std::string wstr_turned_to_str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(line);
                stringstream st(wstr_turned_to_str);
                if (delimiter == '*') {
                    delimiter = findDelimiter(st.str());
                }

                while (getline(st, dato2, delimiter))
                {
                    if (check_number(dato2))
                    {
                        value = stoi(dato2);
                        if (rowColumn->root == nullptr)
                        {
                            cout << "First time" << endl;
                            DATO* dato = new DATO(row, column, value);
                            rowColumn->root = rowColumn->InsertNode(dato, nullptr);
                            columnRow->root = columnRow->InsertNode(dato, nullptr);
                        }
                        else
                        {
                            result = rowColumn->findNode(row, column, byRow());
                            if (get<0>(result) == true)
                            { // already exists
                                cout << "Already exists" << endl;
                                get<1>(result)->_data->setData(value);
                            }
                            else
                            {
                                DATO* dato = new DATO(row, column, value);
                                rowColumn->insert(get<1>(result), dato, get<1>(result)->_data->operator < (dato));
                                result = columnRow->findNode(row, column, byColumn());
                                columnRow->insert(get<1>(result), dato, get<1>(result)->_data->operator > (dato));
                            }
                        }
                       
                    }
                    column++;
                }
                row++;
                column = 1;
            }

            file.close();

            op = "20";
            cin.ignore();
            cout << endl
                << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }

        if (op == "1") {
            row = validateNumber("Type number of row: ");
            column = validateNumber("Type number of column: ");
            value = validateNumber("Type a number: ");
            if (rowColumn->root == nullptr) {
                cout << "First time" << endl;
                DATO* dato = new DATO(row, column, value);

                rowColumn->root = rowColumn->InsertNode(dato, nullptr);
                columnRow->root = columnRow->InsertNode(dato, nullptr);
            }
            else {
                result = rowColumn->findNode(row, column, byRow());
                if (get<0>(result) == true) { //already exists
                    cout << "Already exists" << endl;
                    get<1>(result)->_data->setData(value);
                }
                else {
                    DATO* dato = new DATO(row, column, value);
                    rowColumn->insert(get<1>(result), dato, get<1>(result)->_data->operator < (dato));
                    result = columnRow->findNode(row, column, byColumn());
                    columnRow->insert(get<1>(result), dato, get<1>(result)->_data->operator > (dato));
                }
            }
            op = "20";
            cin.ignore();
            cout << endl << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }
        if (op == "2") {
            system("cls");
            row = validateNumber("Type number of row: ");
            column = validateNumber("Type number of column: ");

            result = rowColumn->findNode(row, column, byRow());
            if (get<0>(result) == true) { //already exists
                rowColumn->deleteNode(get<1>(result), byRow(), false);
                result = columnRow->findNode(row, column, byColumn());
                columnRow->deleteNode(get<1>(result), byColumn(), true);
            }
            op = "20";
            cin.ignore();
            cout << endl << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }
        if (op == "3") {
            if (rowColumn->root != nullptr) {
                std::cout << "Row - Column:" << rowColumn->root->_data->getRow() << " " << rowColumn->root->_data->getColumn() << endl;
                Inorder(rowColumn->root);
                std::cout << endl << "Column - Row:" << endl;
                Inorder(columnRow->root);
                cout << endl << endl;
            }
            op = "20";
            cin.ignore();
            cout << endl << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }
        if (op == "4") {
            system("cls");
            row = validateNumber("Type number of row: ");
            Node* result = rowColumn->FirstOfRow(row);
            if (result) {
                cout << "The first of the row" << row << " is : (" << result->_data->getRow() << "," << result->_data->getColumn() << ")" << endl;
            }
            else {
                cout << "Node not found" << endl;
            }
            op = "20";
            cin.ignore();
            cout << endl << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }
        if (op == "5") {
            system("cls");
            row = validateNumber("Type number of row: ");
            rowColumn->showRow(rowColumn->root, row);
            op = "20";
            cin.ignore();
            cout << endl << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }
        if (op == "6") {
            system("cls");
            i0 = validateNumber("Type number of initial row(i0): ");
            system("cls");
            i = validateNumber("Type number of end row(i): ");
            system("cls");
            j0 = validateNumber("Type number of initial column (j0): ");
            system("cls");
            j = validateNumber("Type number of end column (j): ");
            if (rowColumn->root) {
                int result = rowColumn->sumRectangle( rowColumn->root, columnRow->root, i0 <= i ? i0 : i, i >= i0 ? i : i0, j0 <= j ? j0 : j, j >= j0 ? j : j0 ,0);
                cout << endl << "The result of sum ( " << i0 << "," << j0 << ")" << " (" << i << "," << j << ") is: " << result << endl;
            }
            op = "20";
            cin.ignore();
            cout << endl << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }
        if (op == "7") {
            system("cls");
            row = validateNumber("Type number of row: ");
            column = validateNumber("Type number of column: ");
            result = rowColumn->findNode(row, column, byRow());
            if (get<0>(result) == true) {
                cout << "The value in position (" << row << "," << column << ") is: " << get<1>(result)->_data->getData() << endl;
            }
            else {
                cout << "Node not found" << endl;
            }
            op = "20";
            cin.ignore();
            cout << endl << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }

        if (op == "9") {
            system("cls");
            row = validateNumber("Type number of row: ");
            Node* result = rowColumn->FirstOfRow(row);
            if (result) {
                rowColumn->deleteAllRow(columnRow, row, byRow(), byColumn());
            }
            op = "20";
            cin.ignore();
            cout << endl << "Type enter to continue: " << endl;
            cin.get();
            continue;
        }
        cout << "Type an option: " << endl; cin >> op;
    }
    rowColumn->cleanTree(byRow(), false);
    columnRow->cleanTree(byColumn(), true);
    delete rowColumn;
    delete columnRow;
    return 0;
}

/**
* It is an iterative validation function that checks the value passed by parameter.
*/
bool check_number(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i]) == false) {
            return false;
        }
    }
    if (str.length() == 0) {
        return false;
    }
  
    return true;
}

/**
* Iterative function in charge of validating the number, making use of the check_number function.
*/
int validateNumber(string msj) {
    string num;
    cout << msj << endl;
    cin >> num;
    while (!check_number(num)) {
        cout << msj << endl;
        cin >> num;
    }
    return stoi(num);
}

/**
* Function in charge of searching the character with which the CSV file is delimited.
*/
char findDelimiter(string str) {
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
        {
            return str[i];
        }
    }
    return ' ';
}

/**
 * Method responsible for performing an inorder traversal of the entire tree.
 */
void Inorder(Node* p) {
    if (p != nullptr) {
        Inorder(p->leftChild);
        cout << ",(" << p->_data->getRow() << "," << p->_data->getColumn() << ", " << p->_data->getData() << ") ," << flush;
        Inorder(p->rightChild);
    }
}