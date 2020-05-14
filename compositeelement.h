/**
    \file CompositeElement.h
    \brief Header for CompositeElement class
*/

#ifndef COMPOSITEELEMENT_H
#define COMPOSITEELEMENT_H

#include "valuation.h"
#include "element.h"

#include <map>
#include <functional>
using namespace std;

///@brief Class CompositeElement that composes of Elements and implements the interface Element
///@return Return a pointer to cloned Element
class CompositeElement : public Element {

private:
    shared_ptr<Element> oprnd1;
    shared_ptr<Element> oprnd2;
	function<int(int,int)> op_fun;
    char op_ch;

public:
    ///@brief Constructor for the composite class Composite Element
    ///@param Shared_ptr of type Class Element, Shared_ptr of type Class Element, function handler, char (variable for function).
	CompositeElement(const Element&, const Element&, const function<int(int,int)>, char);

	///@brief Copy Constructor for the composite class CompositeElement
    ///@param Object from Class CompositeElement
	CompositeElement(const CompositeElement&);

    ///@brief Copy Assignment operator for the composite class CompositeElement
    ///@param Object from Class CompositeElement
    CompositeElement operator=(const CompositeElement&) noexcept;

    ///@brief Destructor for the composite class CompositeElement
	~CompositeElement();

	CompositeElement();

    ///@brief Clone CompositeElement object
    ///@return Return a pointer to cloned Element
	Element* clone() const override;

    ///@brief Construct string of CompositeElement object
    ///@return Return a CompositeElement as string '(+oprnd1 -> tostring + op_ch + oprnd->toString+)
    string toString() const override;

    ///@brief Evaluate the character as an integer based on the key-value pairs in dictionary.
    ///@return Return an integer
    ///@throws An exception is thrown, if the key is not found in the Valuation dictionary
	int evaluate(const Valuation&) override;

};

#endif
