#include "Node.h"
#include "DATO.h"
#include<iostream>
#include<tuple>
#include <stack> 
#define SAFE_DELETE(p) { if (p) { delete (p); (p)=nullptr; } } ((void)0)  
using namespace std;

class AVL {
public:
    Node* root;
    int i, j;
    int i0, j0;
    AVL() {
        root = nullptr;
    }
    Node* InsertNode(DATO* key, Node* parent);
    void orderTree(Node* p);
    int HeightOfNode(Node* p);
    int CheckBalanceTree(Node* p);
    Node* CheckIfNeedRotation(Node* p);
    Node* LeftToLeftColumnRotation(Node* p);
    Node* LeftToRightRotation(Node* p);
    Node* RightToRightRotation(Node* p);
    Node* RightToLeftRotation(Node* p);
    Node* Predecessor(Node* p);
    Node* Successor(Node* p);
    Node* FirstOfRow(int i);
    int Sum_I_J(Node* p, int i, int _j0, int _j,int result);
    int sumRectangle(Node * p ,Node* columnRow, int _i0, int _i, int _j0, int _j, int result);
    template <class T> tuple<bool, Node*> findNode(int i, int j, T oper);
    template <class T> void deleteNode(Node* p, T oper, bool deleteDATO);
    void insert(Node * p , DATO*  dato, bool left);
    template <class T, class B> void deleteAllRow(AVL*& p, int i, T oper, B byColumn);
    void showRow(Node* initial, int i);
    template <class T> void cleanTree(T oper, bool deleteDATO);
    ~AVL() {};
};
/**
* Iterative function in charge of searching for a specific node, so that
* it can be used to validate if a node already exists, in addition to its
* later use in the insertion and deletion routines.
*/
template<class T>
inline tuple<bool, Node*> AVL::findNode(int i, int j, T oper)
{
    Node* p = root;
    Node* last = root;
    while (p != nullptr)
    {
        if (p->_data->getColumn() == j && p->_data->getRow() == i) {
            last = p;
            break;
        }
        last = p;
        p = oper(p, i, j);
    }
    return tuple<bool, Node*>{
        p == nullptr ? false : true,
            last
    };
}
/**
 * Function in charge of eliminating a specific node from the AVL
 * tree with the row-column or column-row order relationship.
 */
template<class T>
inline void AVL::deleteNode(Node * p, T oper, bool deleteDATO)
{
    Node* q = p->parent;
    Node* last = root;
    if (p->leftChild == nullptr && p->rightChild == nullptr ) {
            if (root == p) {
                root = nullptr;
            }
          
            if (deleteDATO  ) {
                delete p->_data;
                p->_data = nullptr;
            }
            if (q) {
                q->leftChild == p ? q->leftChild = nullptr : q->rightChild = nullptr;
                SAFE_DELETE(p);
                orderTree(q);
                q = nullptr;
            }
            else {
                SAFE_DELETE(p);
            }
          
    }
    else {
        j = p->_data->getColumn();
        i = p->_data->getRow();
        while (true)
        {
            if (p->_data->getRow() == i && p->_data->getColumn() == j) {
                if (p->leftChild == nullptr && p->rightChild == nullptr) {
                    if (root == p) {
                        root = nullptr;
                    }
                    q = p->parent;
                    break;
                }
                if (deleteDATO==true  && p->_data && q!=p) {
                    delete p->_data;
                    p->_data = nullptr;
                }
                if (HeightOfNode(p->leftChild) > HeightOfNode(p->rightChild)) {
                    q = Predecessor(p->leftChild);
                    p->_data = q->_data;
                }
                else {
                    q = Successor(p->rightChild);
                    p->_data = q->_data;
                }
                j = q->_data->getColumn();
                i = q->_data->getRow();
                p = q;
            }
            else {
                p = oper(q, i, j);
            }
        }
    }
    if (q ) {
        q->leftChild == p ? q->leftChild = nullptr : q->rightChild = nullptr; 
        SAFE_DELETE(p);
        orderTree(q);
    }
}
/**
 * Function in charge of eliminating all the nodes of row i.
 */
template<class T, class B>
inline void AVL::deleteAllRow(AVL*& c, int i, T oper, B byColumn) {
    Node* p = root;
    Node* q;
    tuple<bool, Node*> result;
    while (p) {
        if (p->_data->getRow() == i) {
            if (p->leftChild == nullptr && p->rightChild == nullptr) {
                result = c->findNode(p->_data->getRow(), p->_data->getColumn(), byColumn);
                c->deleteNode(get<1>(result), byColumn, false);
                q = p->parent; 
                if (q) {
                    q->leftChild == p ? q->leftChild = nullptr : q->rightChild = nullptr;
                }
                delete p->_data;
                p->_data = nullptr;
                SAFE_DELETE(p);
                orderTree(q);
                break; 
            }
            else {
                result = c->findNode(p->_data->getRow(), p->_data->getColumn(), byColumn);
                c->deleteNode(get<1>(result), byColumn, true);
                if (HeightOfNode(p->leftChild) > HeightOfNode(p->rightChild)) {
                    q = Predecessor(p->leftChild);
                    p->_data = q->_data;
                }
                else {
                    q = Successor(p->rightChild);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
                    p->_data = q->_data;
                }
                deleteNode(q, oper, false );
            }
        }
        else {
            p->_data->getRow() > i ? p = p->leftChild : p = p->rightChild;
        }
        if (p == nullptr) {
            break;
        }
    }
}
/**
* Function responsible for freeing dynamic memory, going through
* all the nodes of the AVL tree and deleting them.
*/
template<class T>
inline void AVL::cleanTree(T oper ,bool deleteDATO)
{
    Node* p = root;
    while (p) {
        deleteNode(p, oper, deleteDATO);
        p = root;
    }
}
