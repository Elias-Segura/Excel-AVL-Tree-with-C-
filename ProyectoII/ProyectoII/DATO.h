#pragma once
 
class DATO
{
private:
	int data;
	int row;
	int column;

public:
	DATO(int row, int col, int value);
	int getColumn();
	int getRow();
	int getData();
 
	void setData(int data);
 	bool operator == (DATO* key) {
		return key->getColumn() == this->column && key->getRow() == this->row;
	}
	bool operator < (DATO* key) {
		if (key->row == this->row) return key->column < this->column; 
		if (key->row < this->row) { return true; }
		return false;
	}
	bool operator > (DATO* key) {
		if (key->column == this->column) return key->row < this->row;
		if (key->column < this->column) { return true; }
		return false;
	}
   ~DATO()
	{

	}
};

 