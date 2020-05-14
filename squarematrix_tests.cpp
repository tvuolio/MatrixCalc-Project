#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#include "valuation.h"
#include "intelement.h"
#include "varelement.h"
#include "element.h"
#include "symbolicmatrix.h"
#include "concretematrix.h"
#include "compositeelement.h"
#include "catch.hpp"

/*Test cases for the Valuation class
*/
TEST_CASE("Valuation tests" "[Valuation]") {
	Valuation valuation;
	valuation['a'] = 1;
	CHECK(valuation.at('a') == 1);
}

/*Test cases for the Class ConcreteSquareMatrix and SymbolicSquarematrix
Each of the operations as well as the constructors are tested. The output is converted as string to get a easily interpretable comparison.
*/

TEST_CASE("Empty Constructor (Symbolic)", "[SymbolicSquareMatrix"){

        SymbolicSquareMatrix empty;
		CHECK(empty.toString() == "[]");

}

TEST_CASE("Test symbolic operator * and *=", "[SymbolicSquareMatrix]"){
		SymbolicSquareMatrix a("[[a,b][c,d]]");
		SymbolicSquareMatrix b("[[1,2][3,4]]");
		SymbolicSquareMatrix c;
		c = a*b;
		CHECK(c.toString() == "[[((a*1)+(b*3)),((a*2)+(b*4))][((c*1)+(d*3)),((c*2)+(d*4))]]");
		a*=b;
		CHECK(a.toString() == "[[((a*1)+(b*3)),((a*2)+(b*4))][((c*1)+(d*3)),((c*2)+(d*4))]]");

}

TEST_CASE("Test symbolic operator + and +=", "[SymbolicSquareMatrix]"){
		SymbolicSquareMatrix a("[[a,b][c,d]]");
		SymbolicSquareMatrix b("[[1,2][3,4]]");
		SymbolicSquareMatrix c;
		c = a+b;
		CHECK(c.toString() == "[[(a+1),(b+2)][(c+3),(d+4)]]");
		a+=b;
		CHECK(a.toString() == "[[(a+1),(b+2)][(c+3),(d+4)]]");

}

TEST_CASE("Test symbolic operator - and -=", "[SymbolicSquareMatrix]"){

		SymbolicSquareMatrix a("[[a,b][c,d]]");
		SymbolicSquareMatrix b("[[1,2][3,4]]");
		SymbolicSquareMatrix c;
		c = a-b;
		CHECK(c.toString() == "[[(a-1),(b-2)][(c-3),(d-4)]]");
		a-=b;
		CHECK(a.toString() == "[[(a-1),(b-2)][(c-3),(d-4)]]");

}



TEST_CASE("Test Valuation and * operation (Symbolic)", "[SymbolicSquareMatrix"){

        Valuation valuation;
        valuation['x'] = 1;
        valuation['y'] = 2;
        VariableElement a('x');
        VariableElement b('x');

        SymbolicSquareMatrix matti1("[[1,2,3][1,2,3][1,2,3]]");
        SymbolicSquareMatrix matti2("[[x,2,3][1,y,3][1,2,3]]");
        SymbolicSquareMatrix matti3;

        matti3 = matti1 * matti2;

        ConcreteSquareMatrix matti4;
        matti4 = matti3.evaluate(valuation);

        REQUIRE(matti4.toString() == "[[6,12,18][6,12,18][6,12,18]]");
}

TEST_CASE("Test Valuation and + operation (Symbolic)", "[SymbolicSquareMatrix"){

        Valuation valuation;
        valuation['x'] = 1;
        valuation['y'] = 2;
        VariableElement a('x');
        VariableElement b('x');

        SymbolicSquareMatrix matti1("[[1,2,3][1,2,3][1,2,3]]");
        SymbolicSquareMatrix matti2("[[x,2,3][1,y,3][1,2,3]]");
        SymbolicSquareMatrix matti3;

        matti3 = matti1 + matti2;

        ConcreteSquareMatrix matti4;
        matti4 = matti3.evaluate(valuation);

        REQUIRE(matti4.toString() == "[[2,4,6][2,4,6][2,4,6]]");
}


TEST_CASE("Test Valuation and - operation (Symbolic)", "[SymbolicSquareMatrix"){

        Valuation valuation;
        valuation['x'] = 1;
        valuation['y'] = 2;
        VariableElement a('x');
        VariableElement b('x');

        SymbolicSquareMatrix matti1("[[1,2,3][1,2,3][1,2,3]]");
        SymbolicSquareMatrix matti2("[[x,2,3][1,y,3][1,2,3]]");
        SymbolicSquareMatrix matti3;

        matti3 = matti1 - matti2;

        ConcreteSquareMatrix matti4;
        matti4 = matti3.evaluate(valuation);

        REQUIRE(matti4.toString() == "[[0,0,0][0,0,0][0,0,0]]");
}



TEST_CASE("Test Valuation (Symbolic)", "[Concrete SquareMatrix"){

        Valuation valuation{};

        SymbolicSquareMatrix matrix("[[x,7,8][6,8,9][6,8,9]]");
        valuation['x'] = 500;
        ConcreteSquareMatrix matrix2;

        matrix2 = matrix.evaluate(valuation);

        REQUIRE(matrix2.toString() == "[[500,7,8][6,8,9][6,8,9]]" );

}
TEST_CASE("Test << operator (Symbolic)", "[SymbolicSquareMatrix"){

        ostringstream os;
        SymbolicSquareMatrix matrix("[[1,x,8][6,8,9][6,8,9]]");

        os << matrix;

        REQUIRE(os.str() == "[[1,x,8][6,8,9][6,8,9]]" );

}

TEST_CASE("Test << operator (Concrete)", "[ConcreteSquareMatrix"){

        ostringstream os;
        ConcreteSquareMatrix matrix("[[1,7,8][6,8,9][6,8,9]]");

        os << matrix;

        REQUIRE(os.str() == "[[1,7,8][6,8,9][6,8,9]]" );

}


TEST_CASE("Test for matrix equality (symbolic)", "[SymbolicSquareMatrix]"){

    SymbolicSquareMatrix matti1("[[A,7,8][6,8,9][6,8,9]]");
    SymbolicSquareMatrix matti2("[[A,7,8][6,8,9][6,8,9]]");

    CHECK( matti1 == matti2);

}


TEST_CASE("Test for copy assignment operator (symbolic)", "[SymbolicSquareMatrix]"){

        SymbolicSquareMatrix matti1("[[5,x,8][6,8,9][6,8,9]]");
        SymbolicSquareMatrix matti2 = matti1;
        REQUIRE( matti2.toString() == "[[5,x,8][6,8,9][6,8,9]]" );

}

TEST_CASE("Test for copy constructor (symbolic)", "[SymbolicSquareMatrix]"){
        SymbolicSquareMatrix matti1("[[5,7,8][x,8,9][6,8,9]]");
        SymbolicSquareMatrix matti2(matti1);
        REQUIRE( matti2.toString() == "[[5,7,8][x,8,9][6,8,9]]" );

}
TEST_CASE("Test for transpose (symbolic)", "[SymbolicSquareMatrix]"){

    SymbolicSquareMatrix matti1("[[5,7,8][x,8,9][6,8,9]]");
    SymbolicSquareMatrix matti_t;
    matti_t = matti1.transpose();
    REQUIRE( matti_t.toString() == "[[5,x,6][7,8,8][8,9,9]]");

}


TEST_CASE("Test for print() -function (Symbolic)", "[tostring]") {

    ostringstream os;
	SymbolicSquareMatrix matti1("[[A,7,8][6,8,9][6,8,9]]");
    matti1.print(os);
	REQUIRE( os.str() == "[[A,7,8][6,8,9][6,8,9]]\n");

}

TEST_CASE("Test for toString() -function (Symbolic)", "[tostring]") {
	SymbolicSquareMatrix matti1("[[A,7,8][6,x,9][6,8,9]]");
	REQUIRE(matti1.toString() == "[[A,7,8][6,x,9][6,8,9]]");
}


TEST_CASE("Test << operation (symbolic)", "[SymbolicSquareMatrix"){

        ostringstream os;
        SymbolicSquareMatrix matrix("[[A,7,8][6,8,9][6,8,9]]");

        os << matrix;

        REQUIRE(os.str() == "[[A,7,8][6,8,9][6,8,9]]" );

}



TEST_CASE("Test for move constructor (symbolic)", "[SymbolicSquareMatrix"){

        SymbolicSquareMatrix matti1("[[A,7,8][6,8,9][6,8,9]]");
        SymbolicSquareMatrix matti3(std::move(matti1));

        REQUIRE(matti3.toString() == "[[A,7,8][6,8,9][6,8,9]]");

}

TEST_CASE("Test for move assignment operator (symbolic)", "[SymbolicSquareMatrix"){

        SymbolicSquareMatrix matti1("[[A,7,8][6,8,9][6,8,9]]");
        SymbolicSquareMatrix matti3;
        matti3 = std::move(matti1);

        REQUIRE(matti3.toString() == "[[A,7,8][6,8,9][6,8,9]]");

}




TEST_CASE("Test for move constructor", "[Concrete SquareMatrix"){

        ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
        ConcreteSquareMatrix matti2("[[5,7,8][6,8,9][6,8,9]]");
        ConcreteSquareMatrix matti3(std::move(matti1));

        REQUIRE(matti3.toString() == "[[5,7,8][6,8,9][6,8,9]]");

}

TEST_CASE("Test for move assignment operator", "[ConcreteSquareMatrix"){

        ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
        ConcreteSquareMatrix matti3 = std::move(matti1);
        REQUIRE(matti3.toString() == "[[5,7,8][6,8,9][6,8,9]]");

}




TEST_CASE("Test for copy assignment operator", "[ConcreteSquareMatrix]"){

        ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
        ConcreteSquareMatrix matti2 = matti1;
        REQUIRE( matti2.toString() == "[[5,7,8][6,8,9][6,8,9]]" );

}

TEST_CASE("Test for copy constructor", "[ConcreteSquareMatrix]"){
        ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
        ConcreteSquareMatrix matti2(matti1);
        REQUIRE( matti2.toString() == "[[5,7,8][6,8,9][6,8,9]]" );

}
TEST_CASE("Test for transpose", "[ConcreteSquareMatrix]"){

    ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
    ConcreteSquareMatrix matti_t;
    matti_t = matti1.transpose();
    REQUIRE( matti_t.toString() == "[[5,6,6][7,8,8][8,9,9]]");

}

TEST_CASE("Test for matrix inequality", "[ConcreteSquareMatrix]"){

    ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
    ConcreteSquareMatrix matti2("[[6,7,8][6,8,9][6,8,9]]");

    CHECK_FALSE(matti1 == matti2);

}

TEST_CASE("Test for matrix equality", "[ConcreteSquareMatrix]"){

    ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
    ConcreteSquareMatrix matti2("[[5,7,8][6,8,9][6,8,9]]");

    CHECK( matti1 == matti2);

}


TEST_CASE("Negative test for - operator", "[!throws]") {

	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2][1,2]]");

    CHECK_THROWS(matti1-matti2);

}

TEST_CASE("Negative test for + operator", "[!throws]") {

	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2][1,2]]");

    CHECK_THROWS(matti1+matti2);

}

TEST_CASE("Negative test for * operator", "[!throws]") {

	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2][1,2]]");

    CHECK_THROWS(matti1*matti2);

}

TEST_CASE("Negative test for += operator", "[!throws]") {

	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2][1,2]]");

    CHECK_THROWS(matti1+=matti2);

}

TEST_CASE("Negative test for -= operator", "[!throws]") {

	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2][1,2]]");

    CHECK_THROWS(matti1-=matti2);

}


TEST_CASE("Negative test for *= operator", "[!throws]") {

	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2][1,2]]");

    CHECK_THROWS(matti1*=matti2);

}

TEST_CASE("Test for ConcreteSquareMatrix(string)", "[ConcreteSquareMatrix(string)]") {
	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	REQUIRE(matti1.toString() == "[[5,7,8][6,8,9][6,8,9]]");
}

TEST_CASE("Test for ConcreteSquareMatrix(matrix)", "[ConcreteSquareMatrix(matrix)]") {
	ConcreteSquareMatrix matti1("[[1,2,3][1,2,3][1,2,34]]");
	ConcreteSquareMatrix matti2(matti1);
	REQUIRE(matti2.toString() == "[[1,2,3][1,2,3][1,2,34]]");
}

TEST_CASE("Test for ConcreteSquareMatrix + operator", "[addmatrix]") {
	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2,3][1,2,3][1,2,34]]");
	ConcreteSquareMatrix c;
	c = matti1 + matti2;
	REQUIRE(c.toString() == "[[6,9,11][7,10,12][7,10,43]]");
}

TEST_CASE("Test for ConcreteSquareMatrix - operator", "[submatrix]") {
	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2,3][1,2,3][1,2,34]]");
	ConcreteSquareMatrix c;
	c = matti1 - matti2;
	REQUIRE(c.toString() == "[[4,5,5][5,6,6][5,6,-25]]");
}

TEST_CASE("Test for Matrix product", "[multiply]") {
	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
    ConcreteSquareMatrix matti2("[[1,2,3][1,2,3][1,2,34]]");
    ConcreteSquareMatrix a;
    a = matti1 * matti2;
	REQUIRE(a.toString() == "[[20,40,308][23,46,348][23,46,348]]");
}

TEST_CASE("Test for toString() -function", "[tostring]") {
	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	REQUIRE(matti1.toString() == "[[5,7,8][6,8,9][6,8,9]]");
}

TEST_CASE("Test for ConcreteSquareMatrix += operator", "[addmatrix]") {
	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2,3][1,2,3][1,2,34]]");
	matti1 += matti2;
	REQUIRE(matti1.toString() == "[[6,9,11][7,10,12][7,10,43]]");
}

TEST_CASE("Test for ConcreteSquareMatrix -= operator", "[submatrix]") {
	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
	ConcreteSquareMatrix matti2("[[1,2,3][1,2,3][1,2,34]]");
	ConcreteSquareMatrix c;
	matti1 -= matti2;
	REQUIRE(matti1.toString() == "[[4,5,5][5,6,6][5,6,-25]]");
}

TEST_CASE("Test for ConcreteSquareMatrix *= operator", "[mulmatrix]") {
	ConcreteSquareMatrix matti1("[[5,7,8][6,8,9][6,8,9]]");
    ConcreteSquareMatrix matti2("[[1,2,3][1,2,3][1,2,34]]");
	matti1 *= matti2;
	REQUIRE(matti1.toString() == "[[20,40,308][23,46,348][23,46,348]]");
}

TEST_CASE("Testing different kinds of matrices", "[ConcreteSquareMatrices]") {
    ConcreteSquareMatrix matti;
    //I do not see a point why the empty matrix should be accepted, as there would be no elements in the "Matrix".
	REQUIRE(matti.isSquareMatrix("[]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,2,3][1,2,3]]") == true);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,x,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,2,3]x[1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][1,2,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[[3A567, 4,5][34567, 4,5][34567, 4,5]]") == false);
	REQUIRE(matti.isSquareMatrix("[[4.557, 5][4,5]]") == false);
	REQUIRE(matti.isSquareMatrix("[[4, , 5][4,5,5][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[, 567, 1]") == false);
	REQUIRE(matti.isSquareMatrix("[[7,8,1,111,-5]4[7,8,1,111,5][-7,8,1,111,5][7,8,1,111,5][7,8,1,111,5]]") == false);
	REQUIRE(matti.isSquareMatrix("[][7,8,1,5,5][7,8,1,111,5][-7,8,1,111,5][7,8,1,111,5][7,8,1,111,5]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][-1,-2]]") == true);
	REQUIRE(matti.isSquareMatrix("[[x,2][-1,-2]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][4-4,-2]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][2]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][1,2][1,2]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,2,3][1,2,3]") == false);
	REQUIRE(matti.isSquareMatrix("[1,2,3][1,2,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[1,2,3][1,2,3][1,2,3]") == false);
	REQUIRE(matti.isSquareMatrix("1,2,3][1,2,3][1,2,3") == false);
	REQUIRE(matti.isSquareMatrix("1,2,3") == false);
	REQUIRE(matti.isSquareMatrix("kissa") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][-,-2]]") == false);
	REQUIRE(matti.isSquareMatrix("") == false);
}

TEST_CASE("Testing different kinds of symbolic", "[SymbolicSquareMatrices]") {
    SymbolicSquareMatrix matti;
    //I do not see a point why the empty matrix should be accepted, as there would be no elements in the "Matrix".
	REQUIRE(matti.isSquareMatrix("[]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,2,3][1,2,3]]") == true);
	REQUIRE(matti.isSquareMatrix("[[A1,2,3][1,2,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1A,2,3][1,2,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,x,3][1,2,3]]") == true);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,2,3]x[1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][1,2,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[[3A567, 4,5][34567, 4,5][34567, 4,5]]") == false);
	REQUIRE(matti.isSquareMatrix("[[4.557, 5][4,5]]") == false);
	REQUIRE(matti.isSquareMatrix("[[4, , 5][4,5,5][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[, 567, 1]") == false);
	REQUIRE(matti.isSquareMatrix("[[7,8,1,111,-5]4[7,8,1,111,5][-7,8,1,111,5][7,8,1,111,5][7,8,1,111,5]]") == false);
	REQUIRE(matti.isSquareMatrix("[][7,8,1,5,5][7,8,1,111,5][-7,8,1,111,5][7,8,1,111,5][7,8,1,111,5]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][-1,-2]]") == true);
	REQUIRE(matti.isSquareMatrix("[[x,2][-1,-2]]") == true);
	REQUIRE(matti.isSquareMatrix("[[1,2][4-4,-2]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][2]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][1,2][1,2]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2,3][1,2,3][1,2,3]") == false);
	REQUIRE(matti.isSquareMatrix("[1,2,3][1,2,3][1,2,3]]") == false);
	REQUIRE(matti.isSquareMatrix("[1,2,3][1,2,3][1,2,3]") == false);
	REQUIRE(matti.isSquareMatrix("1,2,3][1,2,3][1,2,3") == false);
	REQUIRE(matti.isSquareMatrix("1,2,3") == false);
	REQUIRE(matti.isSquareMatrix("kissa") == false);
	REQUIRE(matti.isSquareMatrix("[[1,2][-,-2]]") == false);
	REQUIRE(matti.isSquareMatrix("") == false);
}



/*Test cases for methods in Class IntElement and VariableElement
The operations and the constructors are evaluated by using the getVal()-method in each of the test cases.
*/

int test_sum(int a, int b) {
	return a+b;
}

TEST_CASE("Tests for == operator", "[Element]"){


        std::shared_ptr<Element> a1 (new IntElement(1));
		std::shared_ptr<Element> a2 (new IntElement(2));
		std::shared_ptr<Element> a3 (new IntElement(1));
		std::shared_ptr<Element> b1 (new VariableElement('x'));
		std::shared_ptr<Element> b2 (new VariableElement('y'));
		std::shared_ptr<Element> b3 (new VariableElement('x'));
		std::shared_ptr<Element> c1 (new CompositeElement(*a1,*b1,test_sum,'+'));
		std::shared_ptr<Element> c2 (new CompositeElement(*a2,*b2,test_sum,'+'));
		std::shared_ptr<Element> c3 (new CompositeElement(*a3,*b3,test_sum,'+'));
		CHECK(*a1 == *a3);
		CHECK_FALSE(*a1 == *a2);
		CHECK(*b1 == *b3);
		CHECK_FALSE(*b1 == *b2);
		CHECK(*c1 == *c3);
		CHECK_FALSE(*c1 == *c2);
		CHECK_FALSE(*a1 == *b1);
		CHECK_FALSE(*a1 == *c1);
		CHECK_FALSE(*b1 == *c1);

}

TEST_CASE("Test for evaluation and clone of Element subclasses", "[CompositeElement]"){

        Valuation valuation;
		valuation['x'] = 10;
		IntElement a(1);
		VariableElement b('x');
		CompositeElement c(a,b, test_sum,'+');
		Element* ie = a.clone();
		Element* ve = b.clone();
		Element* ce = c.clone();
		CHECK(ie -> evaluate(valuation) == 1);
		CHECK(ve -> evaluate(valuation) == 10);
		CHECK(ce -> evaluate(valuation) == 11);
		delete ie;
		delete ve;
		delete ce;

}



TEST_CASE("Test << operation for VariableElement", "[VariableElement]"){

        ostringstream os;
        VariableElement v('a');

        os << v;

        REQUIRE(os.str() == "a" );

}

TEST_CASE("Test for VariableElement() empty constructor","[VariableElement]") {
	VariableElement v;
	REQUIRE(v.getVal() == ' ');
}


TEST_CASE("Test for VariableElement().setVal()","[VariableElement]") {
	VariableElement v;
	v.setVal('a');
	REQUIRE(v.getVal() == 'a');
}




TEST_CASE("Element tests", "[Element]"){
    Valuation valuation;
    valuation['x'] = 10;
    IntElement a(1);
    VariableElement b('x');

    Element* ie = a.clone();
    Element* ve = b.clone();
    CHECK(ie -> evaluate(valuation) == 1);
    CHECK(ve -> evaluate(valuation) == 10);
    CHECK(a.toString() == "1");
    stringstream ss;
    ss << a;
    CHECK(ss.str() == "1");
    delete ie;
    delete ve;

}

TEST_CASE("Test for VariableElement toString()", "[VariableElement"){

    VariableElement a('c');

    CHECK(a.toString() == "c");

}


TEST_CASE("Test for VariableElement constructor", "[VariableElement"){

    VariableElement a('c');

    REQUIRE(a.getVal() == 'c');

}

TEST_CASE("Test for VariableElement equality", "[VariableElement]"){

    VariableElement a('x');
    VariableElement b('x');

    CHECK(a==b);



}

TEST_CASE("Test for evaluation of IntElement", "[IntElement]"){
		IntElement a(5);
		Valuation valuation;
		valuation['a']=1;
		CHECK(a.evaluate(valuation) == 5);
}

TEST_CASE("Tests for methods Clone() & toString()", "[IntElement]") {
		IntElement a(1);
		Element* d = a.clone();
		CHECK(d -> toString() == "1");
		delete d;
}

TEST_CASE("Operator << for IntElement", "[IntElement]") {
		IntElement a(10);
		stringstream ss;
		ss << a;
		CHECK(ss.str() == "10");
}

TEST_CASE("Test for intElement equality", "[intElement"){

    IntElement a(1);
    IntElement b(1);

    CHECK(a==b);

}

TEST_CASE("Test for intElement inequality", "[intElement"){

    IntElement a(1);
    IntElement b(2);

    CHECK(a!=b);

}

TEST_CASE("Test for IntElement()","[intelement]") {
	IntElement a;
	REQUIRE(a.getVal() == 0);
}


TEST_CASE("Test for IntElement(int)","[intelement(int)]") {
	IntElement a(3);
	REQUIRE(a.getVal() == 3);
}

TEST_CASE("Test for IntElement + operator", "[add]") {
	IntElement a(1);
	IntElement b(2);
	IntElement c;
	c = a + b;
	REQUIRE(c.getVal() == 3);
}

TEST_CASE("Test for IntElement - operator", "[subtract]") {
	IntElement a(1);
	IntElement b(2);
	IntElement c;
	c = a - b;
	REQUIRE(c.getVal() == -1);
}

TEST_CASE("Test for IntElement * operator", "[multiply]") {
	IntElement a(1);
	IntElement b(2);
	IntElement c;
	c = a * b;
	REQUIRE(c.getVal() == 2);
}

TEST_CASE("Test for IntElement += operator", "[add=]") {
	IntElement a(1);
	IntElement b(2);
	a += b;
	REQUIRE(a.getVal() == 3);
}

TEST_CASE("Test for IntElement -= operator", "[sub=]") {
	IntElement a(1);
	IntElement b(2);
	a -= b;
	REQUIRE(a.getVal() == -1);

}

TEST_CASE("Test for IntElement *= operator", "[mul=]") {
	IntElement a(1);
	IntElement b(2);
	a *= b;
	REQUIRE(a.getVal() == 2);
}
