/**
    \file concretematrix.h
    \brief Header file for the ConcreteSquareMatrix class
*/

#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H
#include "intelement.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

class ConcreteSquareMatrix{

    private:
        vector<vector<shared_ptr<IntElement>>> elements;

        int n = 0;

    public:
        ConcreteSquareMatrix(const string& matrix_str);
        ConcreteSquareMatrix();
        ~ConcreteSquareMatrix();
        ConcreteSquareMatrix(const ConcreteSquareMatrix& matrix);
        ConcreteSquareMatrix(ConcreteSquareMatrix&&);
        ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&& matrix) noexcept;

        ConcreteSquareMatrix transpose();
        ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix&);
        ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix&);
        ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix&);
        ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix&);
        string toString() const;

        friend std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix&);
        friend ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& matrix1, const ConcreteSquareMatrix& matrix2);
        friend ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& matrix1, const ConcreteSquareMatrix& matrix2);
        friend ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& matrix1, const ConcreteSquareMatrix& matrix2);
        friend bool operator==(const ConcreteSquareMatrix& matrix1, const ConcreteSquareMatrix& matrix2);

        void print(std::ostream&);

        bool isSquareMatrix(const string& matrix_str);

};

#endif // SQUAREMATRIX_H
