/**
    \file CompositeElement.cpp
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
#include "compositeelement.h"

/// @brief Constructor for the CompositeElement class
/// @param The objects, the function and the operator by making use of which the object is constructed
CompositeElement::CompositeElement(const Element& e1, const Element& e2, const function<int(int,int)> f, char oper){

    oprnd1 = shared_ptr<Element>(e1.clone());
    oprnd2 = shared_ptr<Element>(e2.clone());
    op_ch = oper;
    op_fun = f;

}

/// @brief Method clone for the CompositeElement class
/// @return Returns a new CompositeElements (new pointers to oprnd1 and oprnd2, as well as the assosiated function and operator character
Element* CompositeElement::clone() const{
    return new CompositeElement(*oprnd1, *oprnd2, op_fun, op_ch);
}

/// @brief Copy constructor for the CompositeElement class
/// @param An object from class CompositeElement
CompositeElement::CompositeElement(const CompositeElement& c){

        oprnd1 = shared_ptr<Element>(c.oprnd1 -> clone());
        oprnd2 = shared_ptr<Element>(c.oprnd2 -> clone());
        op_ch = c.op_ch;
        op_fun = c.op_fun;

}

/// @brief Copy assignment operator for the CompositeElement class
/// @return This object with deep copied pointers
CompositeElement CompositeElement::operator=(const CompositeElement& c) noexcept{

        oprnd1 = shared_ptr<Element>(c.oprnd1 -> clone());
        oprnd2 = shared_ptr<Element>(c.oprnd2 -> clone());
        op_ch = c.op_ch;
        op_fun = c.op_fun;
        return *this;

}
/// @brief Default constructor for class CompositeElement
CompositeElement::CompositeElement(){
}

/// @brief Destructor of CompositeElement object
CompositeElement::~CompositeElement(){
}

/// @brief toString method to CompositeElement class
/// @return Returns the operands and the op_ch as a string
string CompositeElement::toString() const{

    stringstream ss;
    ss << "(";
    ss << oprnd1->toString();
    ss << op_ch;
    ss << oprnd2->toString();
    ss << ")";
    return ss.str();
}

/// @brief Method Valuate for the class CompositeElement
/// @return The value that is computed based on the defined function ("+", "-" or "*"), operand values as well as the valuation object map valus.
int CompositeElement::evaluate(const Valuation& valuation){

    return op_fun(oprnd1->evaluate(valuation),oprnd2->evaluate(valuation));

}
