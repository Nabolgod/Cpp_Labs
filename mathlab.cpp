#include <iostream>
#include <string>

using namespace std;

class MathObject {
public:
	MathObject __add__(MathObject other) {};

	MathObject __sub__(MathObject other) {};

	MathObject __mul__(MathObject other) {};

	MathObject __mul__(int other) {};

	void __str__(int other) {}
};

class Matrix : public MathObject {
public:
	Matrix __add__(Matrix other) {
		return Matrix();
	}

	Matrix __sub__(Matrix other) {
		return Matrix();
	}

	Matrix __mul__(Matrix other) {
		return Matrix();
	}

	Matrix __mul__(int other) {
		return Matrix();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

class Polynomial : public MathObject {
public:
	Polynomial __add__(Matrix other) {
		return Polynomial();
	}

	Polynomial __sub__(Matrix other) {
		return Polynomial();
	}

	Polynomial __mul__(Matrix other) {
		return Polynomial();
	}

	Polynomial __mul__(int other) {
		return Polynomial();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

class Vector : public MathObject {
public:
	Vector __add__(Vector other) {
		return Vector();
	}

	Vector __sub__(Vector other) {
		return Vector();
	}

	Vector __mul__(Vector other) {
		return Vector();
	}

	Vector __mul__(int other) {
		return Vector();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

class Fraction : public MathObject {
public:
	Fraction __add__(Fraction other) {
		return Fraction();
	}

	Fraction __sub__(Fraction other) {
		return Fraction();
	}

	Fraction __mul__(Fraction other) {
		return Fraction();
	}

	Fraction __mul__(int other) {
		return Fraction();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

class СomplexNumber : public MathObject {
public:
	СomplexNumber __add__(СomplexNumber other) {
		return СomplexNumber();
	}

	СomplexNumber __sub__(СomplexNumber other) {
		return СomplexNumber();
	}

	СomplexNumber __mul__(СomplexNumber other) {
		return СomplexNumber();
	}

	СomplexNumber __mul__(int other) {
		return СomplexNumber();
	}

	void __str__(int other) {
		cout << "" << endl;
	}
};

int main() {

	
	return 0;
}
