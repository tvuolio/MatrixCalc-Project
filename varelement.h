/**
    \file VariableElement.h
    \brief Header for VariableElement class
*/

#ifndef VARELEMENT_H
#define VARELEMENT_H




#include "valuation.h"
#include "element.h"

#include <map>

using namespace std;



class VariableElement : public Element {

private:

	char val;

public:
	VariableElement();
	VariableElement(char v);
	~VariableElement();
	char getVal() const;
	void setVal(char v);
	Element* clone() const override;

	int evaluate(const Valuation&) override;

	string toString() const override;

	friend std::ostream& operator<<(std::ostream&, const VariableElement&);
	//bool operator==(const VariableElement& a);

};

#endif
