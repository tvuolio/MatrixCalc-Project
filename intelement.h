/**
    \file intelement.h
    \brief Header for IntElement class
*/

#ifndef INTELEMENT_H
#define INTELEMENT_H



#include "element.h"
#include "valuation.h"

#include <map>

using namespace std;



class IntElement : public Element {

private:
	int val;

public:

	IntElement();
	IntElement(int v);
	~IntElement();

	int evaluate(const Valuation&) override;

    string toString() const override;

	int getVal() const;
	void setVal(int v);
	Element* clone() const override;

	friend IntElement operator+(const IntElement&, const IntElement&);
	friend IntElement operator-(const IntElement&, const IntElement&);
	friend IntElement operator*(const IntElement&, const IntElement&);
	friend std::ostream& operator<<(std::ostream&, const IntElement&);

	IntElement& operator+=(const IntElement&);
	IntElement& operator-=(const IntElement&);
	IntElement& operator*=(const IntElement&);
	//bool operator==(const IntElement&, const IntElement&);
	friend bool operator!=(const IntElement& a, const IntElement& b);

};

#endif
