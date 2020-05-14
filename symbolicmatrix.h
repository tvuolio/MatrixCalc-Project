/**
    \file symbolicmatrix.h
    \brief Header for SymbolicSquareMatrix class
*/

#ifndef SYMBOLICMATRIX_H
#define SYMBOLICMATRIX_H
#include <vector>
#include <memory>
#include "element.h"
#include "concretematrix.h"
#include "valuation.h"

#include <map>
using namespace std;



class SymbolicSquareMatrix {

private:
	int n = 0;
	vector<vector<shared_ptr<Element>>> elements;

public:
	SymbolicSquareMatrix();
	~SymbolicSquareMatrix();
	SymbolicSquareMatrix(const string&);

	SymbolicSquareMatrix(const SymbolicSquareMatrix&);
	SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix&);

	SymbolicSquareMatrix(SymbolicSquareMatrix&&);
	SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&&) noexcept;

	void print(std::ostream&);
	string toString() const;

    ConcreteSquareMatrix evaluate(const Valuation&);

    bool isSquareMatrix(const string& matrix);

	friend std::ostream& operator<<(std::ostream&, const SymbolicSquareMatrix&);
	SymbolicSquareMatrix transpose();

	SymbolicSquareMatrix& operator+=(const SymbolicSquareMatrix&);

	SymbolicSquareMatrix& operator-=(const SymbolicSquareMatrix&);

	SymbolicSquareMatrix& operator*=(const SymbolicSquareMatrix&);

	friend SymbolicSquareMatrix operator-(const SymbolicSquareMatrix&, const SymbolicSquareMatrix&);
	friend SymbolicSquareMatrix operator+(const SymbolicSquareMatrix&, const SymbolicSquareMatrix&);
	friend SymbolicSquareMatrix operator*(const SymbolicSquareMatrix&, const SymbolicSquareMatrix&);
	friend bool operator==(const SymbolicSquareMatrix&, const SymbolicSquareMatrix&);

};

#endif
