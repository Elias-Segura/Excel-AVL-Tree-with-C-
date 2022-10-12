#include "DATO.h"

 
DATO::DATO(int row, int col, int value)
{
	this->row = row; 
	this->column = col;
	this->data = value;

}

int DATO::getColumn() {
	return this->column;
};
int DATO::getRow() {
	return this->row;
};
int DATO::getData() {
	return this->data;
}
 
void DATO::setData(int data) {
	this->data = data;
}

 

 