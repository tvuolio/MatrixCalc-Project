/**
    \file intelement.cpp
    \brief Implementation for the IntElement class
*/

#include <string>
#include <iostream>
#include <sstream>
#include <ostream>
#include <map>

#include "intelement.h"
#include "valuation.h"
using namespace std;


///@brief Parameterized constructor for the IntElement class
///@details
/// Construct an object IntElement
///@param value of the object

IntElement::IntElement(int v){

    this->val = v;

}

///@brief Non-parameterized constructor for the IntElement class
///@details
/// Construct an object IntElement and assign 0 as the value

IntElement::IntElement(){
    this->val = 0;
    //cout << "Element created" << endl;
}

///@brief Destructor of the IntElement class
///@details
/// Destruct the object IntElement
IntElement::~IntElement(){
    //cout << "Element destroyed" << endl;
}

int IntElement::evaluate(const Valuation& valuation){

        return val;
}

string IntElement::toString() const{

    stringstream val_string;
    val_string << val;
    return val_string.str();

}

Element* IntElement::clone() const{
    return new IntElement(*this);
}

///@brief Operator += for individual matrix elements
///@details
/// Calculate the sum of element e and the current value
///@param e object intElement
///@return pointer to the val

IntElement& IntElement::operator+=(const IntElement& e){
    this->val += e.getVal();
    return *this;
}

///@brief Operator -= for individual matrix elements
///@details
/// Calculate the subtraction of element e and the current value
///@param e object intElement
///@return pointer to the val
IntElement& IntElement::operator-=(const IntElement& e){
    this->val -= e.getVal();
    return *this;
}

///@brief Operator *= for individual matrix elements
///@details
/// Calculate the product of element e and the current value
///@param e object intElement
///@return pointer to the val

IntElement& IntElement::operator*=(const IntElement& e){
    this->val *= e.getVal();
    return *this;
}
///@brief Operator + for individual matrix elements
///@details
/// Calculate the sum of elements i1 and i2
///@param i1 object intElement of matrix1
///@param i2 object intElement of matrix2
///@return sum object that is constructed from the IntElement class

IntElement operator+(const IntElement& i1, const IntElement& i2){
    int sum0;
    sum0 = i1.getVal() + i2.getVal();
    IntElement sum(sum0);
    return sum;
}

///@brief Operator - for individual matrix elements
///@details
/// Calculate the subtraction of element elements i1 and i2
///@param i1 object intElement of matrix1
///@param i2 object intElement of matrix2
///@return sub object that is constructed from the IntElement class
IntElement operator-(const IntElement& i1, const IntElement& i2){

    int sub0;

    sub0 = i1.getVal() - i2.getVal();

    IntElement sub(sub0);
    return sub;

}

///@brief Operator * for individual matrix elements
///@details
/// Calculate the product of element elements i1 and i2
///@param i1 object intElement of matrix1
///@param i2 object intElement of matrix2
///@return prod object that is constructed from the IntElement class
IntElement operator*(const IntElement& i1, const IntElement& i2){

    int prod0;

    prod0 = i1.getVal() * i2.getVal();

    IntElement prod(prod0);
    return prod;

}

///@brief Operator << for individual matrix elements
///@details
/// Print the matrix element
///@param os object from iostream
///@param i1 object intElement of matrix
///@return output stream for printing
std::ostream& operator<<(std::ostream& os, const IntElement& i1){

    os << i1.getVal();
    return os;

}

/*
///@brief Operator == for individual matrix elements
///@details
/// Print the matrix element
///@param e1 object IntElement of a SquareMatrix
///@param e2 object IntElement of a SquareMatrix
///@return Boolean, which indicates are the elements similar
bool operator==(const IntElement& e1, const IntElement& e2){

    if (e1.getVal() == e2.getVal()){

        return true;

    }else{
        return false;
    }

}
*/
///@brief Operator != for individual matrix elements
///@details
/// Print the matrix element
///@param e1 object IntElement of a SquareMatrix
///@param e2 object IntElement of a SquareMatrix
///@return Boolean, which indicates are the elements non-similar
bool operator!=(const IntElement& e1, const IntElement& e2){

    if (e1.getVal() != e2.getVal()){

        return true;

    }else{
        return false;
    }

}


///@brief get-method for the value of a object
///@details
/// get the value of the element of a matrix object
///@return value of the IntElement
int IntElement::getVal() const{
    return val;
}
///@brief set-method for the value of a object
///@details
/// set a value of the element of a matrix object
///@param v integer value
void IntElement::setVal(int v){
    val = v;
}


