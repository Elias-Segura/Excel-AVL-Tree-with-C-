#include "AVL.h"

/**
 * Function responsible for returning the node with the data inserted into the AVL tree.
 */
Node* AVL::InsertNode(DATO* key, Node* parent) {
    Node* t;
    t = new Node;
    t->_data = key;
    t->parent = parent;
    t->leftChild = nullptr;
    t->rightChild = nullptr;
    t->height = 1;
    return t;
}


/**
 * Function corresponding to the balance factor, in charge of checking and returning
 * the height difference of the left subtree and that of the right subtree.
 */
int AVL::CheckBalanceTree(Node* p) {
    int heightLeft = 0, heightRight = 0;
    if (p->leftChild)
    {
        heightLeft = p->leftChild->height;
    }
    if (p->rightChild)
    {
        heightRight = p->rightChild->height;
    }
    return heightLeft - heightRight;
}

/**
 * Function in charge of checking if the rotation of the nodes within the tree is necessary,
 * likewise it verifies what type of rotation to apply, whether it is left to left rotation,
 * left to right rotation, right to right rotation and right to left rotation.
 */
Node* AVL::CheckIfNeedRotation(Node* p) {
    if (CheckBalanceTree(p) == 2 && CheckBalanceTree(p->leftChild) == 1) {
        return LeftToLeftColumnRotation(p);
    }
    else if (CheckBalanceTree(p) == 2 && CheckBalanceTree(p->leftChild) == -1) {
        return LeftToRightRotation(p);
    }
    else if (CheckBalanceTree(p) == -2 && CheckBalanceTree(p->rightChild) == -1) {
        return RightToRightRotation(p);
    }
    else if (CheckBalanceTree(p) == -2 && CheckBalanceTree(p->rightChild) == 1) {
        return RightToLeftRotation(p);
    }
    else if (CheckBalanceTree(p) == 2 && CheckBalanceTree(p->leftChild) == 0) {
        return LeftToLeftColumnRotation(p);
    }
    else if (CheckBalanceTree(p) == -2 && CheckBalanceTree(p->rightChild) == 0) {
        return RightToRightRotation(p);
    }
    return p;
}

/**
* Iterative function in charge of ordering the tree, specifically accommodating the root
* of the AVL tree after the execution of the insert and delete routines.
*/
void AVL::orderTree(Node* p)
{
    Node* last = p;
    while (p) {
        p->height = HeightOfNode(p);
        p = CheckIfNeedRotation(p);
        last = p;
        if (p->parent == nullptr) {
            last = p;
        }
        p = p->parent;
    }
    root->parent = nullptr;
    root = last;
}

/**
 * Function in charge of finding and returning the height of the left subtree
 * and also the height of the right subtree.
 */
int AVL::HeightOfNode(Node* p) {
    int heightLeft = 0, heightRight = 0;
    if (p == nullptr) {
        return 0;
    }
    if (p->leftChild)
    {
        heightLeft = p->leftChild->height;
    }
    if (p->rightChild)
    {
        heightRight = p->rightChild->height;
    }
    return heightLeft > heightRight ? heightLeft + 1 : heightRight + 1;
}

/**
 * Iterative function in charge of performing the rotation
 * from left to left (LL) in the AVL binary tree.
 */
Node* AVL::LeftToLeftColumnRotation(Node* p) {

    Node* pl = p->leftChild;
    Node* plr = pl->rightChild;
    pl->rightChild = p;
    p->leftChild = plr;
    p->height = HeightOfNode(p);
    pl->height = HeightOfNode(pl);
    if (p->parent) {
        if (p->parent->leftChild == p) {
            p->parent->leftChild = pl;
        }
        else {
            p->parent->rightChild = pl;
        }
    }
    pl->parent = p->parent;
    p->parent = pl;
    if (p->leftChild) {
        p->leftChild->parent = p;
    }
    if (root == p) {
        root = pl;
    }
    return pl;
}

/**
 * Iterative function responsible for performing the double rotation
 * from left to right (LR) in the AVL binary tree.
 */
Node* AVL::LeftToRightRotation(Node* p) {

    Node* pl = p->leftChild;
    Node* plr = pl->rightChild;

    pl->rightChild = plr->leftChild;
    p->leftChild = plr->rightChild;
    plr->leftChild = pl;
    plr->rightChild = p;

    pl->height = HeightOfNode(pl);
    p->height = HeightOfNode(p);
    plr->height = HeightOfNode(plr);

    if (p->parent) {
        if (p->parent->leftChild == p) {
            p->parent->leftChild = plr;
        }
        else {
            p->parent->rightChild = plr;
        }
    }
    plr->parent = p->parent;
    plr->leftChild->parent = plr;
    plr->rightChild->parent = plr;
    if (p->leftChild) {
        p->leftChild->parent = p;
    }
    if (pl->rightChild) {
        pl->rightChild->parent = pl;
    }
    if (p == root) {
        root = plr;
        plr->parent = nullptr;
    }
    return plr;
}

/**
 * Iterative function in charge of performing the rotation
 * from right to right (RR) in the AVL binary tree.
 */
Node* AVL::RightToRightRotation(Node* p) {

    Node* pr = p->rightChild;
    Node* prl = pr->leftChild;
    pr->leftChild = p;
    p->rightChild = prl;
    p->height = HeightOfNode(p);
    pr->height = HeightOfNode(pr);

    if (p->parent) {
        if (p->parent->leftChild == p) {
            p->parent->leftChild = pr;
        }
        else {
            p->parent->rightChild = pr;
        }
    }
    pr->parent = p->parent;
    p->parent = pr;
    if (p->rightChild) {
        p->rightChild->parent = p;
    }
    if (root == p) {
        root = pr;
        root->parent = nullptr;
    }
    return pr;
}

/**
 * Iterative function responsible for performing the double rotation
 * from right to left (RL) in the AVL binary tree.
 */
Node* AVL::RightToLeftRotation(Node* p) {

    Node* pr = p->rightChild;
    Node* prl = pr->leftChild;

    pr->leftChild = prl->rightChild;
    p->rightChild = prl->leftChild;

    prl->rightChild = pr;
    prl->leftChild = p;

    pr->height = HeightOfNode(pr);
    p->height = HeightOfNode(p);
    prl->height = HeightOfNode(prl);
    if (p->parent) {
        if (p->parent->leftChild == p) {
            p->parent->leftChild = prl;
        }
        else {
            p->parent->rightChild = prl;
        }
    }
    prl->parent = p->parent;
    prl->leftChild->parent = prl;
    prl->rightChild->parent = prl;
    if (p->rightChild) {
        p->rightChild->parent = p;
    }
    if (pr->leftChild) {
        pr->leftChild->parent = pr;
    }
    if (root == p) {
        prl->parent = nullptr;
        root = prl;
    }
    return prl;
}

/**
 * Iterative function in charge of returning the predecessor node of another
 * node within the tree, this function is used later in the delete
 * methods.
 */
Node* AVL::Predecessor(Node* p) {
    while (p && p->rightChild != nullptr) {
        p = p->rightChild;
    }
    return p;
}

/**
 * Iterative function in charge of returning the successor node of another
 * node within the tree, this function is used later in the delete
 * methods.
 */
Node* AVL::Successor(Node* p) {
    while (p && p->leftChild != nullptr) {
        p = p->leftChild;
    }
    return p;
}

/**
 * Iterative function in charge of applying a search within the tree to find
 * the first cell of row i.
 */
Node* AVL::FirstOfRow(int i)
{
    Node* p = root;
    Node* last = nullptr;
    while (p) {
        if (p->_data->getRow() == i) {
            last = p;
            p = p->leftChild;
        }
        else
        {
            p->_data->getRow() > i ? p = p->leftChild : p = p->rightChild;
        }
    }
    return last;
}

/**
 * Iterative function in charge of traversing the tree and performing the sum of the rectangle (i0, j0) − (i1, j1)
 * using the function SUM_I_J.
 */
int AVL::Sum_I_J(Node* p, int i, int _j0, int _j , int result)
{
    if (p == nullptr) {
        return result;
    }
    if ((_j0 > _j)) {
        return result;
    }
    while (p) {
            if ((p->_data->getColumn() >= _j0 && p->_data->getColumn() <= _j) && i == p->_data->getRow()) {
                result += p->_data->getData();
                result = Sum_I_J(p, i, _j0, p->_data->getColumn() - 1, result);
                result = Sum_I_J(p, i, p->_data->getColumn() + 1, _j, result);
                p = nullptr;   
            }
            else if ((p->_data->getColumn() >= _j0 && p->_data->getColumn() <= _j)) {
                result = Sum_I_J(p->leftChild, i, _j0, _j, result);
                result = Sum_I_J(p->rightChild, i, _j0, _j, result);
                p = nullptr;
            }
            else {
                p->_data->getColumn() > _j0 ? p = p->leftChild : p = p->rightChild;
            }
    }
    return result;
}

/**
* Iterative function in charge of traversing the tree and performing the sum using the SUM_I_J function.
*/
int AVL::sumRectangle(Node* p, Node* columnRow, int _i0, int _i, int _j0, int _j, int result)
{
    if (p == nullptr) {
        return result;
    }
    if ((_i0 > _i)) {
        return result;
    }
    while (p) {
            if (p->_data->getRow() >= _i0 && p->_data->getRow() <= _i) {
                result  = Sum_I_J(columnRow, p->_data->getRow(), _j0, _j, result);
                result  = sumRectangle(p,columnRow, _i0, p->_data->getRow() - 1, _j0, _j, result);
                result  = sumRectangle(p,columnRow, p->_data->getRow() + 1,_i, _j0, _j, result);
                p = nullptr;
            }
            else {
                p->_data->getRow() > _i0 ? p = p->leftChild : p = p->rightChild;
            }
    }
    return result;
}

/**
 * function in charge of carrying out the insertion of the nodes in the tree
 * and whose order relationship can be by row column or column row, this
 * depends on the tree where the call is made.
 */
void AVL::insert(Node* p, DATO* dato, bool left)
{
    if (left) {
        p->leftChild = InsertNode(dato, p);
        orderTree(p->leftChild);
    }
    else {
        p->rightChild = InsertNode(dato, p);
        orderTree(p->rightChild);
    }
}

/**
* Function in charge of traversing the AVL tree and printing the
* row in order of the number of columns.
*/
void AVL::showRow(Node* initial, int i)
{
    stack<Node*> s;

    Node* p = initial;
    while (p) {
        if (p->_data->getRow() == i) {
            showRow(p->leftChild, i);
            cout << ",(" << p->_data->getRow() << "," << p->_data->getColumn() << ", " << p->_data->getData() << ") ," << flush;
            showRow(p->rightChild, i);
            break;
        }
        else
        {
            p->_data->getRow() > i ? p = p->leftChild : p = p->rightChild;
        }
    }
}





