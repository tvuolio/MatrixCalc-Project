/**
    \file VariableElement.h
    \brief Header for Valuation map defined as a class.
*/

#ifndef VALUATION_H
#define VALUATION_H
#include <map>


using namespace std;

///@Brief The Valuation map object of which properties are inherited from std::map.

class Valuation : public map<char,int>{


public:
	Valuation(){};
    ~Valuation(){};


};

#endif
