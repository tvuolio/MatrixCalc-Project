/**
    \file element.cpp
    \brief Implementation file for the interface class Element

*/

#include <iostream>
#include <sstream>
#include "element.h"

///@brief Destructor for the interface Element
Element::~Element(){
}
/// @brief << operator for interface class Element
/// @details
/// uses the getVal() -method to fetch the value of an object,
/// convert to string and output in an ostream object
/// @return Returns an ostream object
std::ostream& operator<<(std::ostream& os, Element& e){
                os << e.toString();
                return os;
};

bool operator==(const Element& e1, const Element& e2){
    if ( e1.toString() == e2.toString()){

        return true;

    }else{
        return false;
    }

}
