/**
    \file symbolicmatrix.cpp
    \brief Implementation for the SymbolicSquareMatrix class
*/
#include <sstream>
#include <iostream>
#include <string>
#include <memory>
#include <map>

using namespace std;
#include "intelement.h"
#include "varelement.h"
#include "symbolicmatrix.h"
#include "concretematrix.h"
#include "valuation.h"
#include "compositeelement.h"

int sum(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
///@brief Parameterized constructor for the SymbolicSquareMatrix class
///@details
/// Construct an object SymbolicSquareMatrix. The matrix form is assessed with isSquareMatrix. If the isSquareMatrix returns false, then an exception is thrown.
///@param matrix (string)
///@throws std::invalid_argument if the matrix is ill-defined

SymbolicSquareMatrix::SymbolicSquareMatrix(const string& matrix){

    int val, i=0, len;
    char c = ']';
    char val_char = ' ';

    stringstream val_string("");
    if (!isSquareMatrix(matrix)){

        throw invalid_argument("Matrix is not a square matrix");

    }

    len = matrix.size();
    vector<shared_ptr<Element>> row;
    //Iterate through each of the characters in the string
    while(i < len-1){
        //add each of the digit or "-" to stringstream. It is already known that the matrix is correctly defined.
        if (isdigit(matrix.at(i)) || matrix.at(i) == '-' || isalpha(matrix.at(i))){
            while (isdigit(matrix.at(i)) || matrix.at(i) == '-' || isalpha(matrix.at(i))){
                if (isdigit(matrix.at(i)) || matrix.at(i) == '-'){

                    val_string << matrix.at(i);

                }else{
                    val_char = matrix.at(i);
                }

                i++;
            }
            if (isalpha(val_char)){

                row.push_back(std::shared_ptr<Element>(new VariableElement(val_char)));
                val_char = ' ';

            }else{

                val_string >> val;
                val_string.str(string());
                val_string.clear();
                row.push_back(std::shared_ptr<Element>(new IntElement(val)));
                val = 0;
            }
        }
        //if the character ']' is reached in the string, add the row of elements to matrix
        if (matrix.at(i) == c){

            elements.push_back(row);

            row.clear();

        }
        i++;
    }
}

///@brief Destructor of the SymbolicSquareMatrix class
///@details
/// Destroy the object SymbolicSquareMatrix
SymbolicSquareMatrix::~SymbolicSquareMatrix(){
}

///@brief Method evaluate for the SymbolicSquareMatrix class
///@details
/// Create an object ConcreteSquareMatrix from a specific SymbolicSquareMatrix object. Use the valuation defined in the "Valuation" class.
///@param Valuation map object.
///@return A matrix from class ConcreteSquareMatrix
ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& valuation){

    int i,j, e;

    SymbolicSquareMatrix m;
    m.elements = elements;
    m.n = n;
    elements.clear();
    vector<shared_ptr<Element>> row;

    for (i = 0 ; i < n ; i++ ){
        for (j = 0; j < n ; j++){

            e = m.elements[i][j]->evaluate(valuation);
            row.push_back(std::shared_ptr<Element>(new IntElement(e)));

        }
        elements.push_back(row);
        row.clear();
    }


    ConcreteSquareMatrix m2(this -> toString());
    return m2;
}

///@brief Operator + for 2 matrices
///@details
/// Calculate the sum of each element e in two given square matrices
///@param matrix1 object from class SymbolicSquareMatrix
///@param matrix2 object from class SymbolicSquareMatrix
///@return matrix3 from class SymbolicSquareMatrix
SymbolicSquareMatrix operator+(const SymbolicSquareMatrix& matrix1, const SymbolicSquareMatrix& matrix2){

    SymbolicSquareMatrix matrix3;
    matrix3 = matrix1;
    matrix3 += matrix2;
    return matrix3;

}

///@brief Operator - for 2 matrices
///@details
/// Calculate the subtraction of each element e in two given square matrices
///@param matrix1 object from class SymbolicSquareMatrix
///@param matrix2 object from class SymbolicSquareMatrix
///@return matrix3 from class SymbolicSquareMatrix
///@throws std::invalid_argument if the matrix dimensions do not agree
SymbolicSquareMatrix operator-(const SymbolicSquareMatrix& matrix1, const SymbolicSquareMatrix& matrix2){

    SymbolicSquareMatrix matrix3;
    matrix3 = matrix1;
    matrix3 -= matrix2;
    return matrix3;


}

///@brief Operator * for 2 matrices
///@details
/// Calculate the product of each element e in two given square matrices
///@param matrix1 object from class SymbolicSquareMatrix
///@param matrix2 object from class SymbolicSquareMatrix
///@return matrix3 from class SymbolicSquareMatrix
SymbolicSquareMatrix operator*(const SymbolicSquareMatrix& matrix1, const SymbolicSquareMatrix& matrix2){

    SymbolicSquareMatrix matrix3;
    matrix3 = matrix1;
    matrix3 *= matrix2;
    return matrix3;


}

///@brief function sum for two integers.
///@details
/// Calculate the sum of two integers. The function is associated for each of the CompositeElements in the operator +=.
///@param integer
///@param integer
///@return sum of two integers
int sum(int a, int b){
    return a + b;
}

///@brief function subtract for two integers.
///@details
/// Calculate the subtract of two integers. The function is associated for each of the CompositeElements in the operator -=.
///@param integer
///@param integer
///@return subtract of two integers
int sub(int a, int b){
    return a - b;
}

///@brief function product for two integers.
///@details
/// Calculate the product of two integers. The function is associated for each of the CompositeElements in the operator *=.
///@param integer
///@param integer
///@return product of two integers

int mul(int a, int b){
    return a * b;
}

///@brief Operator += for this matrix and an other matrix
///@details
/// Calculate the sum of each element e in two given square matrices
///@param matrix1 object from class SymbolicSquareMatrix
///@return This matrix from class SymbolicSquareMatrix
///@throws std::invalid_argument if the matrices dimensions do not agree
SymbolicSquareMatrix& SymbolicSquareMatrix::operator+=(const SymbolicSquareMatrix& matrix){
        //Throw exception if the matrix dimensions do not agree

        if (n != matrix.n){
            throw invalid_argument("Matrix dimensions do not agree!");
        }
        int j, i;

        SymbolicSquareMatrix m;
        m.elements = elements;
        m.n = n;

        elements.clear();
        vector<shared_ptr<Element>> row;


        //Iterate through each of the elements in the matrix
        for (i = 0 ; i < matrix.n; i++){
            for (j = 0 ; j < matrix.n ; j++){

                    row.push_back(std::shared_ptr<Element>(new CompositeElement(*m.elements[i][j],*matrix.elements[i][j], sum, '+' )));

            }

            elements.push_back(row);
            row.clear();

        }
        return *this;

}

///@brief Operator -= for this matrix and an other matrix
///@details
/// Calculate the subtract of each element e in two given square matrices
///@param matrix1 object from class SymbolicSquareMatrix
///@return This matrix from class SymbolicSquareMatrix
///@throws std::invalid_argument if the matrices dimensions do not agree
SymbolicSquareMatrix& SymbolicSquareMatrix::operator-=(const SymbolicSquareMatrix& matrix){
        //Throw exception if the matrix dimensions do not agree

        if (n != matrix.n){
            throw invalid_argument("Matrix dimensions do not agree!");
        }
        int j, i;

        SymbolicSquareMatrix m;
        m.elements = elements;
        m.n = n;

        elements.clear();
        vector<shared_ptr<Element>> row;


        //Iterate through each of the elements in the matrix
        for (i = 0 ; i < matrix.n; i++){
            for (j = 0 ; j < matrix.n ; j++){

                    row.push_back(std::shared_ptr<Element>(new CompositeElement(*m.elements[i][j],*matrix.elements[i][j], sub, '-' )));

            }

            elements.push_back(row);
            row.clear();

        }
        return *this;
}

///@brief Operator *= for this matrix and an other matrix
///@details
/// Calculate the product of each element e in two given square matrices
///@param matrix1 object from class SymbolicSquareMatrix
///@return This matrix from class SymbolicSquareMatrix
///@throws std::invalid_argument if the matrices dimensions do not agree
SymbolicSquareMatrix& SymbolicSquareMatrix::operator*=(const SymbolicSquareMatrix& matrix){
        //Throw exception if the matrix dimensions do not agree

        if (n != matrix.n){
            throw invalid_argument("Matrix dimensions do not agree!");
        }
        int j=0, i=0, k=0;
        SymbolicSquareMatrix m;
        m.elements = elements;
        m.n = n;
        elements.clear();
        vector<shared_ptr<Element>> row;
        //Iterate through each of the elements in the matrix
		CompositeElement c(*m.elements[i][k],*matrix.elements[k][j], mul, '*');

        for (i = 0; i < matrix.n ; i++){
            for (j = 0 ; j < matrix.n; j++){
				k = 0;
				//Temporary object that is used to chain the compositeElement into multiple compositeElements
				CompositeElement c_tmp(*m.elements[i][k],*matrix.elements[k][j], mul, '*' );
				c = c_tmp;
                for (k = 1 ; k < matrix.n ; k++){
                    //A CompositeElement is chained such that a new compositeElement is composed based on the current CompositeElement and the Matrix Elements with sum operator
					CompositeElement c_next(*m.elements[i][k],*matrix.elements[k][j], mul, '*' );
                    //This results that each of the compositeElements are constructed as follows:
                    //Iteration k = 0, CompositeElement0 = Element*Element
                    //Iteration k = 1, CompositeElement1 = CompositeElement0 + Element*Element
                    //Iteration k = 2, CompositeElement2 = CompositeElement1 + Element*Element
                    //The CompositeElement2 represents the final CompositeElement in case of a 3x3 matrix.
					CompositeElement c_tmp(c,c_next,sum,'+');
					c = c_tmp;
                }
				row.push_back(std::shared_ptr<Element>(new CompositeElement(c)));
            }
            elements.push_back(row);
            row.clear();
        }
        return *this;

}



///@brief non-Parameterized constructor for the SymbolicSquareMatrix class
///@details
/// Construct an object SymbolicSquareMatrix.

SymbolicSquareMatrix::SymbolicSquareMatrix(){
}


///@brief Method print for a SymbolicSquareMatrix
///@details
/// Print a given matrix to a string of a form [[e11,...,e1n][en1, ... ,enn]]
///@param os from class iostream

void SymbolicSquareMatrix::print(std::ostream& os){

    int i, j;
    int n = elements.size();

    os << "[";
    //Iterate each of the matrix elements
    for (i = 0; i < n; i++){
        os << "[";
        for (j = 0; j < n; j++){
            if (j == n-1){
                os << elements[i][j]->toString() << "";
            }else{
                os << elements[i][j]->toString() << ",";
            }
        }
        os << "]";

    }
    os << "]" << endl;
}

///@brief Method toString for a SymbolicSquareMatrix
///@details
/// Convert a given matrix to a string of a form [[e11,...,e1n][en1, ... ,enn]]
///@return matrix as a string

string SymbolicSquareMatrix::toString() const{

    ostringstream os;
    string strmatrix;

    int i, j;
    int n = elements.size();
    os << "[";
    //Iterate each of the matrix elements
    for (i = 0; i < n; i++){
        os << "[";
        for (j = 0; j < n; j++){
            if (j == n-1){
                os << elements[i][j] -> toString() << "";
            }else{
                os << elements[i][j] -> toString()  << ",";
            }
        }
        os << "]";
    }
    os << "]";
	strmatrix = os.str();
	return strmatrix;
}


///@brief Operator transpose for printing a SymbolicSquareMatrix
///@details
/// Print a given matrix in a transponed form.
///@return a transponed matrix
SymbolicSquareMatrix SymbolicSquareMatrix::transpose(){

    vector<shared_ptr<Element>> row;
    SymbolicSquareMatrix m;
    m.elements = elements;
    m.n = n;
    elements.clear();
    char val_char;
    int i,j,value;
    for( i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            stringstream str_stream(m.elements[j][i] -> toString());
            stringstream str_stream2(m.elements[j][i] -> toString());
            str_stream >> val_char;
            str_stream2 >> value;

            if(isalpha(val_char)){
                row.push_back(std::shared_ptr<Element>(new VariableElement(val_char)));
            }else{
                row.push_back(std::shared_ptr<Element>(new IntElement(value)));
            }
        }
        elements.push_back(row);
        row.clear();
    }
    return *this;

}

///@brief Copy assignment operator for class SymbolicSquareMatrix
///@details
/// Copies the matrix1 to matrix2, but instead of making a shallow copy, different memory addresses are allocated for matrix2
///@param matrix object from class SymbolicSquareMatrix
///@
///@return If a self-assignment is made, then the method returns this matrix uncopied, otherwise copies the matrix to this.
///@throws std::invalid_argument if the matrices dimensions do not agree
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix& matrix){
    int i,j;
    if (*this == matrix)
        return *this;
    elements.clear();
    char val_char;
    int value;
    vector<shared_ptr<Element>> row;
    ///Allocate a new pointer that points to new matrices elements and push this pointer to attribute vector stack
    for (i  = 0; i < matrix.n; i++){
        for (j = 0; j < matrix.n; j++){
            stringstream str_stream(matrix.elements[i][j] -> toString());
            stringstream str_stream2(matrix.elements[i][j] -> toString());
            str_stream >> val_char;
            str_stream2 >> value;

            if(isalpha(val_char)){
                row.push_back(std::shared_ptr<Element>(new VariableElement(val_char)));
            }
            else{
                row.push_back(std::shared_ptr<Element>(new IntElement(value)));
            }
        }
        elements.push_back(row);
        row.clear();
    }

    this-> n = matrix.n;
    return *this;
}


///@brief Copy constructor for the SymbolicSquareMatrix class
///@details
/// Construct a copy object, but instead of making a shallow copy, different memory addresses are allocated for matrix2
///@param matrix object from class SymbolicSquareMatrix
SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& matrix){
    int i,j;
    elements = matrix.elements;
    elements.clear();
    char val_char;
    int value;
    vector<shared_ptr<Element>> row;
    ///Allocate a new pointer that points to new matrices elements and push this pointer to attribute vector stack
    for (i  = 0; i < matrix.n; i++){
        for (j = 0; j < matrix.n; j++){
            stringstream str_stream(matrix.elements[i][j] -> toString());
            stringstream str_stream2(matrix.elements[i][j] -> toString());
            str_stream >> val_char;
            str_stream2 >> value;

            if(isalpha(val_char)){
                row.push_back(std::shared_ptr<Element>(new VariableElement(val_char)));
            }
            else{
                row.push_back(std::shared_ptr<Element>(new IntElement(value)));
            }
        }
        elements.push_back(row);
        row.clear();
    }

    this-> n = matrix.n;

}


///@brief Operator == for 2 SymbolicSquareMatrices
///@details
/// Calculate the sum of each element e in two given square matrices
///@param matrix1 object from class SymbolicSquareMatrix
///@param matrix2 object from class SymbolicSquareMatrix
///@return bool (= True if the matrices are similar)
///@throws std::invalid_argument if the matrix dimensions do not agree

bool operator==(const SymbolicSquareMatrix& matrix1, const SymbolicSquareMatrix& matrix2){

    int i, j;
    //if the matrices dimensions do not agree, then return false
    if (matrix1.n != matrix2.n){
        return false;
    }
    //Iterate each of the matrix elements
    for (i = 0; i < matrix1.n; i++){
        for(j = 0; j < matrix1.n; j++){

            if (matrix1.elements[i][j]->toString() != matrix2.elements[i][j]->toString()){
                return false;
            }

        }

    }
    return true;

}

///@brief Operator << for printing a SymbolicSquareMatrix
///@details
/// Print a given matrix
///@param os from class iostream
///@return os from class iostream

std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& matrix){

    os << matrix.toString();
    return os;

}

///@brief Move constructor for the SymbolicSquareMatrix class
///@details
/// Moves the resources of a given matrix to this matrix. The matrix attributes are set to nullptr, whereas this matrix constitutes of the attributes of the given matrix.
///@param matrix object from class SquareMatrix

SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& matrix){
    cout << "Move Constructor called" << endl;
    n = std::move(matrix.n);
    elements = std::move(matrix.elements);

}

///@brief Move assignment operator for the SymbolicSquareMatrix class
///@details
/// Moves the resources of a given matrix to this matrix. The matrix attributes are set to nullptr, whereas this matrix constitutes of the attributes of the given matrix.
///@param matrix object from class SymbolicSquareMatrix
///@return If a self-assignment is made, then the method returns this matrix unmoved, otherwise moves the resources.

SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix&& matrix) noexcept{

    cout << "Move Assignment operator called" << endl;

    if(*this == matrix){
        return *this;
    }


    n =  std::move(matrix.n);
    elements = std::move(matrix.elements);

    return *this;
}

///@brief Method isSquareMatrix for checking if the matrix is defined correctly
///@details
/// Test whether the matrix string given is of correct form [[e11,...,e1n][en1, ... ,enn]]. Prevents construction of SymbolicSquareMatrix, if returns false
///@return boolean (= False matrix is ill-defined)

bool SymbolicSquareMatrix::isSquareMatrix(const string& matrix){

    int i = 0,k = 0, num = 0, n_block = 0;
    char c;
    vector <int> block;
    bool flag = true;
    bool flag_c = true;
    int len = matrix.length();
    int len_c = 0;
    if (len < 4){
        return false;
    }
    //If the matrix does not begin with "[" and end with "]]" it is defined wrong
    if (matrix.at(i) != '[' || matrix.at(matrix.length()-1) != ']' || matrix.at(matrix.length()-2) != ']'){
        return false;
    }
    i = 1;
    len = matrix.length()-1;
    //Iterate through each of the characters in the string
    //During the iterations flag = true means that the character is digit and otherwise the flag is false
    while(i < len) {
        len_c = 0;
        if (isdigit(matrix.at(i)) || matrix.at(i) == '-' || isalpha(matrix.at(i))){
            //If the character is digit or "-", then move to next character
            while(isdigit(matrix.at(i)) || matrix.at(i) == '-' || isalpha(matrix.at(i))){
              c = matrix.at(i);
              if (isalpha(c)){
                len_c += 1;
                flag_c = true;
              }
              if (isalpha(matrix.at(i+1))){
                return false;
              }
              if (flag_c && isdigit(c)){
                    return false;
              }
              if (len_c > 1){
                    return false;
              }
              i++;
              flag = true;
              //if the minus is between numbers then the matrix is falsely defined
              if (flag && matrix.at(i) == '-'){
                return false;
              }
              }

            if (c == '-'){
                return false;
            }
            num++;
        }else{

            flag_c = false;
            //if the character is not a digit, then it must be either [, ], or ','
            if (matrix.at(i) != '[' && matrix.at(i) != ']' && matrix.at(i) != '-' && matrix.at(i) != ',' && isdigit(matrix.at(i)) && isalpha(matrix.at(i)) ){
                return false;
            }
            //',' can be only after a digit (flag = true)
            if (matrix.at(i) == ',' && !flag){

                return false;
                //If the characters after ',' are not either digit or minus, then the matrix is falsely defined
            } else if (matrix.at(i) == ',' && !isdigit(matrix.at(i+1)) && matrix.at(i+1) != '-' && isalpha(matrix.at(i))){

                return false;

            }
            //if the square bracket is open, then push k++ to stack
            if (matrix.at(i) == '['){
                k++;
                flag = false;
                //otherwise pop from stack and push the number of elements in a particular block in the block vector
            }else if (matrix.at(i) == ']'){
                k--;
                block.push_back(num);
                n_block++;
                num = 0;
                flag = false;
            }else if (matrix.at(i) == ','){
                flag = false;
            }
        i++;
        }
    }

    i = 0;
    //check if the numbers in the block and the number of blocks in the matrix are equal
    int mat_size = block.size();
    while (i < mat_size){

        if (block.at(i) == n_block){
            flag = true;
        }else{
            return false;
        }
        i++;
    }
    //set the matrix dimensions to n
    this-> n = block.at(0);
    //if the flag is true and the stack is empty (k=0) then the matrix is correctly defined
    if (flag && k == 0){
        return true;
    }else{
        return false;
    }
}




