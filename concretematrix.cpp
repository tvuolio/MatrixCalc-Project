#include <sstream>
#include <iostream>
#include <string>
#include <memory>

using namespace std;
#include "intelement.h"
#include "concretematrix.h"
#include "valuation.h"
#include "compositeelement.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"


///@brief Parameterized constructor for the ConcreteSquareMatrix class
///@details
/// Construct an object ConcreteSquareMatrix. The matrix form is assessed with isConcreteSquareMatrix. If the isConcreteSquareMatrix returns false, then an exception is thrown.
///@param matrix (string)
///@throws std::invalid_argument if the matrix is ill-defined

ConcreteSquareMatrix::ConcreteSquareMatrix(const string& matrix){

    int val=0, i=0, len;
    char c = ']';

    stringstream val_string("");
    //if the matrix is not correctly defined throw an exception
    if (!isSquareMatrix(matrix)){

        throw invalid_argument("Matrix is not a square matrix");

    }

    len = matrix.size();

    vector<shared_ptr<IntElement>> row;
    //Iterate through each of the characters in the string
    while(i < len-1){
        //add each of the digit or "-" to stringstream. It is already known that the matrix is correctly defined.
        if (isdigit(matrix.at(i)) || matrix.at(i) == '-'){

            while (isdigit(matrix.at(i)) || matrix.at(i) == '-'){

                val_string << matrix.at(i);
                i++;

            }

            val_string >> val;

            val_string.str(string());
            val_string.clear();
            row.push_back(std::shared_ptr<IntElement>(new IntElement(val)));

            val = 0;


        }
        //if the character ']' is reached in the string, add the row of elements to matrix
        if (matrix.at(i) == c){

            elements.push_back(row);

            row.clear();

        }

        i++;
    }

    //elements = mat;

}


///@brief non-Parameterized constructor for the ConcreteSquareMatrix class
///@details
/// Construct an object ConcreteSquareMatrix. The values to be setted are drawn from class IntElement (= 0)

ConcreteSquareMatrix::ConcreteSquareMatrix(){


   // cout << "Matrix created" << endl;
}

///@brief Destructor of the ConcreteSquareMatrix class
///@details
/// Destroy the object ConcreteSquareMatrix
ConcreteSquareMatrix::~ConcreteSquareMatrix(){

}
///@brief Method print for a ConcreteSquareMatrix
///@details
/// Print a given matrix to a string of a form [[e11,...,e1n][en1, ... ,enn]]
///@param os from class iostream

void ConcreteSquareMatrix::print(std::ostream& os){

    int i, j;
    int n = elements.size();
    os << "[";
    //Iterate each of the matrix elements
    for (i = 0; i < n; i++){
        os << "[";
        for (j = 0; j < n; j++){
            if (j == n-1){
                os << *elements[i][j] << "";
            }else{
                os << *elements[i][j] << ",";
            }
        }
        os << "]";
    }
    os << "]" << endl;
}

///@brief Operator += for matrices
///@details
/// Calculate the sum of each element e and the current value
///@param matrix object from class ConcreteSquareMatrix
///@return pointer to the val
///@throws std::invalid_argument if the matrix dimensions do not agree

ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& matrix){
        //Throw exception if the matrix dimensions do not agree
        if (n != matrix.n){
            throw invalid_argument("Matrix dimensions do not agree!");
        }
        int j, i;
        //Iterate through each of the elements in the matrix
        for (i = 0 ; i < matrix.n; i++){
            for (j = 0 ; j < matrix.n ; j++){
               *elements[i][j] += *matrix.elements[i][j];
            }
        }
        return *this;

}


///@brief Operator -= for matrices
///@details
/// Calculate the subtraction of each element e and the current value
///@param matrix object from class ConcreteSquareMatrix
///@return pointer to the val
///@throws std::invalid_argument if the matrix dimensions do not agree

ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix& matrix){
        //Throw exception if the matrix dimensions do not agree
        if (n != matrix.n){
            throw invalid_argument("Matrix dimensions do not agree!");
        }

        int j, i;
        //Iterate through each of the elements in the matrix
        for (i = 0 ; i < matrix.n; i++){
            for (j = 0 ; j < matrix.n ; j++){
               *elements[i][j] -= *matrix.elements[i][j];
            }
        }
        return *this;

}

///@brief Operator *= for matrices
///@details
/// Calculate the product of each element e and the current value
///@param matrix object from class ConcreteSquareMatrix
///@return pointer to the val
///@throws std::invalid_argument if the matrix dimensions do not agree

ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix& matrix){
        int j, i,k;
        //Throw exception if the matrix dimensions do not agree
        if (n != matrix.n){
        throw invalid_argument("Matrix dimensions do not agree!");
        }

        ConcreteSquareMatrix matrix2(matrix);
        //Iterate through each of the elements in the matrix
        //k = row of the left-hand side matrix
        //j = column of the left-hand side matrix and the row of the right hand side matrix
        //i = column of the right hand side matrix
        //the sum is saved to the slot defined by the row of the left hand side matrix and the column of the right hand side matrix
        for (k = 0 ; k < matrix.n; k++){
            for (i = 0 ; i < matrix.n; i++){
                IntElement sum(0);
                for (j = 0 ; j < matrix.n ; j++){
                        sum = sum + *elements[k][j] * *matrix.elements[j][i];
                    }
                    *matrix2.elements[k][i] = sum;

                }
        }

        this -> elements = matrix2.elements;
        return *this;

}

///@brief Operator + for 2 matrices
///@details
/// Calculate the sum of each element e in two given square matrices
///@param matrix1 object from class ConcreteSquareMatrix
///@param matrix2 object from class ConcreteSquareMatrix
///@return matrix3 from class ConcreteSquareMatrix
///@throws std::invalid_argument if the matrix dimensions do not agree

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& matrix1, const ConcreteSquareMatrix& matrix2){

    ConcreteSquareMatrix matrix3;
    matrix3 = matrix1;
    matrix3 += matrix2;
    return matrix3;

}
///@brief Operator - for 2 matrices
///@details
/// Calculate the subtraction of each element e in two given square matrices
///@param matrix1 object from class ConcreteSquareMatrix
///@param matrix2 object from class ConcreteSquareMatrix
///@return matrix3 from class ConcreteSquareMatrix
///@throws std::invalid_argument if the matrix dimensions do not agree
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& matrix1, const ConcreteSquareMatrix& matrix2){

    ConcreteSquareMatrix matrix3;
    matrix3 = matrix1;
    matrix3 -= matrix2;
    return matrix3;


}
///@brief Operator * for 2 matrices
///@details
/// Calculate the product of each element e in two given square matrices
///@param matrix1 object from class ConcreteSquareMatrix
///@param matrix2 object from class ConcreteSquareMatrix
///@return matrix3 from class ConcreteSquareMatrix
///@throws std::invalid_argument if the matrix dimensions do not agree
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& matrix1, const ConcreteSquareMatrix& matrix2){

    ConcreteSquareMatrix matrix3;
    matrix3 = matrix1;
    matrix3 *= matrix2;
    return matrix3;


}
///@brief Copy assignment operator for class ConcreteSquareMatrix
///@details
/// Copies the matrix1 to matrix2, but instead of making a shallow copy, different memory addresses are allocated for matrix2
///@param matrix object from class ConcreteSquareMatrix
///@return If a self-assignment is made, then the method returns this matrix uncopied, otherwise copies the matrix to this.

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(const ConcreteSquareMatrix& matrix){
    int i,j;
    if (*this == matrix){
        return *this;
    }
    elements = matrix.elements;
    elements.clear();
    vector<shared_ptr<IntElement>> row;
    ///Allocate a new pointer that points to new matrices elements and push this pointer to attribute vector stack
    for (i  = 0; i < matrix.n; i++){
        for (j = 0; j < matrix.n; j++){
            IntElement val = *matrix.elements[i][j];
            row.push_back(std::shared_ptr<IntElement>(new IntElement(val)));
        }
        elements.push_back(row);
        row.clear();
    }

    this-> n = matrix.n;
    return *this;
}


///@brief Copy constructor for the ConcreteSquareMatrix class
///@details
/// Construct a copy object, but instead of making a shallow copy, different memory addresses are allocated for matrix2
///@param matrix object from class ConcreteSquareMatrix

ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix& matrix){
    int i,j;

    elements = matrix.elements;
    elements.clear();
    vector<shared_ptr<IntElement>> row;
    ///Allocate a new pointer that points to new matrices elements and push this pointer to attribute vector stack
    for (i  = 0; i < matrix.n; i++){
        for (j = 0; j < matrix.n; j++){
            IntElement val = *matrix.elements[i][j];
            row.push_back(std::shared_ptr<IntElement>(new IntElement(val)));
        }
        elements.push_back(row);
        row.clear();
    }

    this-> n = matrix.n;
}

///@brief Move constructor for the ConcreteSquareMatrix class
///@details
/// Moves the resources of a given matrix to this matrix. The matrix attributes are set to nullptr, whereas this matrix constitutes of the attributes of the given matrix.
///@param matrix object from class ConcreteSquareMatrix

ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix&& matrix){
    n = std::move(matrix.n);
    elements = std::move(matrix.elements);

}

///@brief Move assignment operator for the ConcreteSquareMatrix class
///@details
/// Moves the resources of a given matrix to this matrix. The matrix attributes are set to nullptr, whereas this matrix constitutes of the attributes of the given matrix.
///@param matrix object from class ConcreteSquareMatrix
///@return If a self-assignment is made, then the method returns this matrix unmoved, otherwise moves the resources.

ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(ConcreteSquareMatrix&& matrix) noexcept{
    if(*this == matrix){
        return *this;
    }


    n =  std::move(matrix.n);
    elements = std::move(matrix.elements);

    return *this;
}


///@brief Operator transpose for printing a matrix
///@details
/// Print a given matrix
///@return a transponed matrix

ConcreteSquareMatrix ConcreteSquareMatrix::transpose() {
    ConcreteSquareMatrix mat_trans;
    mat_trans.elements = elements;
    mat_trans.n = n;
    vector<shared_ptr<IntElement>> row;
    elements.clear();
    //Iterate each of the matrix elements and change the row elements to columns and vice versa
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            IntElement val = *mat_trans.elements[j][i];
            row.push_back(std::shared_ptr<IntElement>(new IntElement(val)));

        }
        elements.push_back(row);

        row.clear();

    }
    return *this;
}

///@brief Operator == for 2 matrices
///@details
/// Calculate the sum of each element e in two given square matrices
///@param matrix1 object from class ConcreteSquareMatrix
///@param matrix2 object from class ConcreteSquareMatrix
///@return bool (= True if the matrices are similar)
///@throws std::invalid_argument if the matrix dimensions do not agree

bool operator==(const ConcreteSquareMatrix& matrix1, const ConcreteSquareMatrix& matrix2){

    int i, j;
    //if the matrices dimensions do not agree, then return false
    if (matrix1.n != matrix2.n){
        return false;
    }
    //Iterate each of the matrix elements
    for (i = 0; i < matrix1.n; i++){
        for(j = 0; j < matrix1.n; j++){

            if (*matrix1.elements[i][j] != *matrix2.elements[i][j]){
                return false;
            }

        }

    }
    return true;

}

///@brief Method toString for a ConcreteSquareMatrix
///@details
/// Convert a given matrix to a string of a form [[e11,...,e1n][en1, ... ,enn]]
///@return matrix as a string

string ConcreteSquareMatrix::toString() const{

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
                os << *elements[i][j] << "";
            }else{
                os << *elements[i][j] << ",";
            }
        }
        os << "]";
    }
    os << "]";
	strmatrix = os.str();
	return strmatrix;
}

///@brief Operator << for printing a matrix
///@details
/// Print a given matrix
///@param os from class iostream
///@return os from class iostream

std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& matrix){

    os << matrix.toString();
    return os;

}

///@brief Method isConcreteSquareMatrix for squareMatrice strings
///@details
/// Test whether the matrix string given is of correct form [[e11,...,e1n][en1, ... ,enn]]. Prevents construction, if returns false
///@return boolean (= False matrix is ill-defined)

bool ConcreteSquareMatrix::isSquareMatrix(const string& matrix){

    int i = 0,k = 0, num = 0, n_block = 0;
    char c;
    vector <int> block;
    bool flag = true;
    int len = matrix.length();

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
        if (isdigit(matrix.at(i)) || matrix.at(i) == '-'){
            //If the character is digit or "-", then move to next character
            while(isdigit(matrix.at(i)) || matrix.at(i) == '-'){
              c = matrix.at(i);
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
            //if the character is not a digit, then it must be either [, ], or ','
            if (matrix.at(i) != '[' && matrix.at(i) != ']' && matrix.at(i) != '-' && matrix.at(i) != ',' && !isdigit(matrix.at(i))){
                return false;
            }
            //',' can be only after a digit (flag = true)
            if (matrix.at(i) == ',' && !flag){

                return false;
                //If the characters after ',' are not either digit or minus, then the matrix is falsely defined
            } else if (matrix.at(i) == ',' && !isdigit(matrix.at(i+1)) && matrix.at(i+1) != '-'){

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




