#pragma once
#include "DATO.h"
class Node {
public:
    Node* leftChild;
    Node* rightChild;
    Node* parent; 
    DATO* _data;
    int height;

    ~Node() {};

};

