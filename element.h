/**
    \file element.h
    \brief Header for interface Element
*/

#ifndef ELEMENT_H
#define ELEMENT_H

#include "valuation.h"

#include <vector>
#include <iostream>
#include <memory>
#include <map>


using namespace std;


class Element {

public:
    virtual ~Element();
    virtual int evaluate(const Valuation&) = 0;
    virtual string toString() const{return "";};
    virtual Element* clone() const = 0;
    friend bool operator==(const Element&, const Element&);
    friend std::ostream& operator<<(std::ostream& os, Element& e);
};

#endif
