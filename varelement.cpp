/**
    \file VariableElement.cpp
    \brief Code for VariableElement class
*/
#include <sstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "varelement.h"
#include "element.h"
#include "valuation.h"

/// @brief Construct an VariableElement object with a whitespace
VariableElement::VariableElement() {
	this -> val = ' ';
}

/// @brief Construct an VariableElement object with value v
/// @param v Value for the constructed VariableElement object, an integer
VariableElement::VariableElement(char v) {
	this -> val = v;
}

/// @brief A destroyer to class VariableElement
VariableElement::~VariableElement() {
}

/// @brief toString method to VariableElement class
/// @return Returns the value as a string
string VariableElement::toString() const{

    stringstream val_string;
    val_string << val;
    return val_string.str();

}

/// @brief Getter for VariableElement object
/// @return Returns the value of the object, an integer
char VariableElement::getVal() const {
	return val;
}

/// @brief Setter for VariableElement object
/// @param v Value to be set for the object, an integer
/// @return Return void
void VariableElement::setVal(char v) {
	this -> val = v;
}

///@brief Setter for VariableElement object
///@return Return a pointer to cloned VariableElement
Element* VariableElement::clone() const {
	return new VariableElement(*this);
}

///@brief Evaluate the character as an integer based on the key-value pairs in dictionary.
///@return Return an integer
///@throws An exception is thrown, if the key is not found in the Valuation dictionary
int VariableElement::evaluate(const Valuation& valuation) {

        return valuation.at(val);

}

/// @brief Print operator suitable to be used with cout <<
/// @details
/// uses the getVal() -method to fetch the value of an object,
/// convert to string and output in an ostream object
/// @return Returns an ostream object
std::ostream& operator<<(std::ostream& os, const VariableElement& val) {
	os << val.getVal();
	return os;
}
/*
/// @brief == operator for VariableElement
/// @return true if VariableElements are equal, false otherwise
bool operator==(const VariableElement& a, const VariableElement& b){
	if(a.getVal() == b.getVal())
		return true;
	else
		return false;
}*/
