#include <iostream>
#include <string>
#include <cmath>
#include <complex>
using namespace std;


class Error {
public:
	virtual void print() = 0;
};

class ENotExistsIndex : public Error {
public:
	string ENEI;
	ENotExistsIndex() :ENEI("Invalid index!\n") {}
	void print() {
		cout << ENEI << endl;
	}
};

class EDivisionByZero : public Error {
public:
	string ENEI;
	EDivisionByZero() :ENEI("Division by zero!\n") {}
	void print() {
		cout << ENEI << endl;
	}
};

class ESize : public Error {
public:
	string ENEI;
	ESize() :ENEI("Sizes are't equal!") {}
	void print() {
		cout << ENEI << endl;
	}
};

class ESizeLessThan2 : public Error {
public:
	string ENEI;
	ESizeLessThan2() :ENEI("Sizes less than 2") {}
	void print() {
		cout << ENEI << endl;
	}
};


template <typename T>

class CTVector
{
private:
	size_t size;
	T* _array;
	T eps;
public:

	CTVector()
	{
		size = 1;
		eps = 0;
		_array = new T[size];
	}

	CTVector(const size_t d)
	{
		size = d;
		_array = new T[size];
		eps = 0;
	}

	CTVector(const size_t d, const T* ar, const T epsilon)
	{
		size = d;
		_array = new T[size];
		eps = epsilon;

		for (size_t i = 0; i < size; ++i)
		{
			_array[i] = ar[i];
		}

	}


	CTVector(const CTVector& source)
	{
		size = source.size;
		eps = source.eps;
		_array = new T[size];
		for (size_t i = 0; i < size; ++i)
		{
			_array[i] = source[i];
		}
	}

	~CTVector()
	{
		delete[] _array;
	}

	friend ostream& operator<<(ostream& os, CTVector& v)
	{
		for (size_t i = 0; i < v.size; ++i)
		{
			if (i == 0)
			{
				os << '(' << v[0] << ',';
			}

			else if (i < v.size - 1)
			{
				os << v[i] << ',';
			}

			else if (i == v.size - 1)
			{
				os << v[i] << ')';
			}
		}

		os << endl;

		return os;
	}

	void set_eps(const T e)
	{
		eps = e;
	}

	bool operator == (const CTVector& v) const
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			if (abs(_array[i] - v[i]) > eps)
			{
				return false;
			}
		}
		return true;
	}

	CTVector operator + (const CTVector& v) const
	{
		CTVector obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] + v[i];
		}
		return obj;
	}

	CTVector<complex<T>> operator + (const CTVector<complex<T>>& v) const
	{
		CTVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] + v[i];
		}
		return obj;
	}

	CTVector& operator += (const CTVector& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array[i] = _array[i] + v[i];
		}
		return *this;
	}

	CTVector<complex<T>>& operator += (const CTVector<complex<T>>& v) const
	{
		CTVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] + v[i];
		}
		return obj;
	}

	CTVector operator - (const CTVector& v) const
	{
		CTVector obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] - v[i];
		}
		return obj;
	}

	CTVector<complex<T>> operator - (const CTVector<complex<T>>& v) const
	{
		CTVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] - v[i];
		}
		return obj;
	}

	CTVector& operator -= (const CTVector& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array[i] = _array[i] - v[i];
		}
		return *this;
	}

	CTVector<complex<T>> operator -= (const CTVector<complex<T>>& v) const
	{
		CTVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] - v[i];
		}
		return obj;
	}

	T operator * (const CTVector& v) const
	{
		T multiplication = 0;
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array[i] * v[i];
		}
		return multiplication;
	}

	complex<T> operator * (const CTVector<complex<T>>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array[i] * v[i];
		}
		return multiplication;
	}

	CTVector operator * (const T s)
	{
		CTVector<T> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] * s;
		}
		return obj;

	}

	CTVector<complex<T>> operator * (const complex<T> s)
	{
		CTVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] * s;
		}
		return obj;

	}

	friend CTVector operator * (const T s, const CTVector& v)
	{
		CTVector<T> obj(v.size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj._array[i] = v[i] * s;
		}
		return obj;

	}

	friend CTVector<complex<T>> operator * (const complex<T> s, const CTVector& v)
	{
		CTVector<complex<T>> obj(v.size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj._array[i] = v[i] * s;
		}
		return obj;

	}

	CTVector operator / (const T s) const
	{
		CTVector obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] / s;
		}
		return obj;
	}

	CTVector<complex<T>> operator / (const complex<T> s) const
	{
		CTVector<complex<T>> obj(size);
		if (s.real() == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] / s;
		}
		return obj;
	}

	T operator [] (const size_t i) const
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return _array[i];
	}

	T& operator [] (const size_t i)
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return _array[i];
	}

	size_t get_size() const
	{
		return size;
	}

	CTVector operator =(const CTVector& v)
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			_array[i] = v[i];
		}
		return *this;
	}

	CTVector UnitPerpendicular()
	{
		{
			if (size % 2 == 0)
			{
				if (size == 2)
				{
					T* vector = new T[2];
					vector[0] = _array[1] * -1;
					vector[1] = _array[0];

					T x = vector[0] / pow((pow(vector[0], 2) + pow(vector[1], 2)), 0.5);
					T y = vector[1] / pow((pow(vector[0], 2) + pow(vector[1], 2)), 0.5);
					vector[0] = x;
					vector[1] = y;

					return CTVector(size, vector, 0);
				}
				else
				{
					T* vector = new T[size];
					vector[0] = 0;
					vector[size - 1] = 0;
					for (size_t i = 1; i < size - 1; ++i)
					{
						if (i % 2 != 0)
						{
							vector[i] = -1 * _array[i + 1];
						}

						else
						{
							vector[i] = _array[i - 1];
						}
					}



					T summ = 0;
					for (size_t j = 1; j < size - 1; ++j)
					{
						summ += pow(vector[j], 2);
					}


					for (size_t i = 1; i < size - 1; ++i)
					{
						vector[i] = vector[i] / pow(summ, 0.5);
					}

					return CTVector(size, vector, 0);
				}
			}
			if (size % 2 != 0)
			{
				if (size < 2) throw  ESizeLessThan2();
				else
				{
					T* vector = new T[size];
					vector[0] = 0;
					for (size_t i = 1; i < size; ++i)
					{
						if (i % 2 != 0)
						{
							vector[i] = _array[i + 1];
						}

						else
						{
							vector[i] = -1 * _array[i - 1];
						}
					}

					T summ = 0;
					for (size_t j = 1; j < size; ++j)
					{
						summ += pow(vector[j], 2);
					}


					for (size_t i = 1; i < size; ++i)
					{
						vector[i] = vector[i] / pow(summ, 0.5);
					}

					return CTVector(size, vector, 0);
				}
			}
		}
	}

};

template <typename T>

class CTVector<complex<T>>
{
private:
	size_t size;
	complex<T>* _array;
	T eps;
public:

	CTVector()
	{
		size = 1;
		eps = 0;
		_array = new complex<T>[size];
	}

	CTVector(const size_t d)
	{
		size = d;
		_array = new complex<T>[size];
		eps = 0;
	}

	CTVector(const size_t d, const complex<T>* ar, const T epsilon)
	{
		size = d;
		_array = new complex<T>[size];
		eps = epsilon;

		for (size_t i = 0; i < size; ++i)
		{
			_array[i] = ar[i];
		}

	}


	CTVector(const CTVector<complex<T>>& source)
	{
		size = source.size;
		eps = source.eps;
		_array = new complex<T>[size];
		for (size_t i = 0; i < size; ++i)
		{
			_array[i] = source[i];
		}
	}

	~CTVector()
	{
		delete[] _array;
	}

	friend ostream& operator<<(ostream& os, const CTVector<complex<T>>& v)
	{
		for (size_t i = 0; i < v.size; ++i)
		{
			if (i == 0)
			{
				os << '(' << v[0] << ',';
			}

			else if (i < v.size - 1)
			{
				os << v[i] << ',';
			}

			else if (i == v.size - 1)
			{
				os << v[i] << ')';
			}
		}

		os << endl;

		return os;
	}

	void set_eps(const T e)
	{
		eps = e;
	}

	bool operator == (const CTVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			if (abs(_array[i] - v[i]) > eps)
			{
				return false;
			}
		}
		return true;
	}

	CTVector<complex<T>> operator + (const CTVector<complex<T>>& v) const
	{
		CTVector<complex<T>> obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] + v[i];
		}
		return obj;
	}

	CTVector<complex<T>> operator + (const CTVector<T>& v) const
	{
		CTVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] + v[i];
		}
		return obj;
	}

	CTVector<complex<T>>& operator += (const CTVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array[i] = _array[i] + v[i];
		}
		return *this;
	}

	CTVector<complex<T>>& operator += (const CTVector<T>& v) const
	{
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array[i] = _array[i] + v[i];
		}
		return *this;
	}

	CTVector<complex<T>> operator - (const CTVector<complex<T>>& v) const
	{
		CTVector<complex<T>> obj(size);
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] - v[i];
		}
		return obj;
	}

	CTVector<complex<T>> operator - (const CTVector<T>& v) const
	{
		CTVector<complex<T>> obj(size);
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] - v[i];
		}
		return obj;
	}

	CTVector<complex<T>>& operator -= (const CTVector<complex<T>>& v) const
	{
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array[i] = _array[i] - v[i];
		}
		return *this;
	}

	CTVector<complex<T>>& operator -= (const CTVector<T>& v) const
	{
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			this->_array[i] = _array[i] - v[i];
		}
		return *this;
	}

	complex<T> operator * (const CTVector<complex<T>>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.size)throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array[i] * v[i]; //a= [z1,z2,z3] b= [z4,z5,z6] multi += z1*z4
		}
		return multiplication;
	}

	complex<T> operator * (const CTVector<T>& v) const
	{
		complex<T> multiplication = 0;
		if (size != v.get_size())throw ESize();
		for (size_t i = 0; i < size; ++i)
		{
			multiplication += _array[i] * v[i];
		}
		return multiplication;
	}

	CTVector<complex<T>> operator * (const T s)
	{
		CTVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] * s;
		}
		return obj;

	}

	friend CTVector<complex<T>> operator * (const T s, const CTVector<complex<T>>& v)
	{
		CTVector<complex<T>> obj(size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj._array[i] = v._array[i] * s;
		}
		return obj;

	}

	friend CTVector<complex<T>> operator * (const complex<T> s, const CTVector<complex<T>>& v)
	{
		CTVector<complex<T>> obj(size);
		for (size_t i = 0; i < v.size; ++i)
		{
			obj._array[i] = v._array[i] * s;
		}
		return obj;

	}

	CTVector<complex<T>> operator * (const complex<T> s)
	{
		CTVector<complex<T>> obj(size);
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] * s;
		}
		return obj;

	}

	CTVector<complex<T>> operator / (const T s) const
	{
		CTVector<complex<T>> obj(size);
		if (s == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] / s;
		}
		return obj;
	}

	CTVector<complex<T>> operator / (const complex<T> s) const
	{
		CTVector<complex<T>> obj(size);
		if (s.real() == 0) throw EDivisionByZero();
		for (size_t i = 0; i < size; ++i)
		{
			obj._array[i] = _array[i] / s;
		}
		return obj;
	}

	complex<T> operator [] (const size_t i) const
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return _array[i];
	}

	complex<T>& operator [] (const size_t i)
	{
		if (i > size or i < 0) throw ENotExistsIndex();
		return _array[i];
	}


	size_t get_size() const
	{
		return size;
	}


	CTVector<complex<T>> operator =(const CTVector<complex<T>>& v)
	{
		if (size != v.size)throw ESize();

		for (size_t i = 0; i < size; ++i)
		{
			_array[i] = v._array[i];
		}
		return *this;
	}

	CTVector<complex<T>> UnitPerpendicular()
	{

		if (size % 2 == 0)
		{
			if (size == 2)
			{
				complex<T>* vector = new complex<T>[2];
				vector[0] = _array[1] * -1.0;
				vector[1] = _array[0];

				complex<T> x = vector[0] / pow((pow(vector[0], 2) + pow(vector[1], 2)), 0.5);
				complex<T> y = vector[1] / pow((pow(vector[0], 2) + pow(vector[1], 2)), 0.5);
				vector[0] = x;
				vector[1] = y;

				return CTVector<complex<T>>(size, vector, 0);
			}
			else
			{
				complex<T>* vector = new complex<T>[size];
				vector[0] = 0;
				vector[size - 1] = 0;
				for (size_t i = 1; i < size - 1; ++i)
				{
					if (i % 2 != 0)
					{
						vector[i] = -1.0 * _array[i + 1];
					}

					else
					{
						vector[i] = _array[i - 1];
					}
				}


				
				complex<T> summ = 0;
				for (size_t j = 1; j < size - 1; ++j)
				{
					summ += pow(vector[j], 2);
				}


				for (size_t i = 1; i < size - 1; ++i)
				{
					vector[i] = vector[i] / pow(summ, 0.5);
				}

				return CTVector<complex<T>>(size, vector, 0);
			}
		}
		if (size % 2 != 0)
		{
			if (size < 2) throw  ESizeLessThan2();
			else
			{
				complex<T>* vector = new complex<T>[size];
				vector[0] = 0;
				for (size_t i = 1; i < size; ++i)
				{
					if (i % 2 != 0)
					{
						vector[i] = _array[i + 1];
					}

					else
					{
						vector[i] = -1.0 * _array[i - 1];
					}
				}
				complex<T> summ = 0;
				for (size_t j = 1; j < size; ++j)
				{
					summ += pow(vector[j], 2);
				}


				for (size_t i = 1; i < size; ++i)
				{
					vector[i] = vector[i] / pow(summ, 0.5);
				}

				CTVector<complex<T>> obj(size, vector, 0);

				return obj;
			}

		}
	}
};


int main()
{
	int fir_array[3] = { 1, 2, 3 };
	int sec_array[3] = { 4, 5, 6 };

	CTVector<int> first(3, fir_array, 0), second(3, sec_array, 0);
	CTVector<int> resultsum = first + second;
	cout << "sum: " << resultsum << endl;

	double first_array[3] = { 1.1, 2.2, 3.3 };
	double second_array[3] = { 4.4, 5.5, 6.6 };

	CTVector<double> f_v(3, first_array, 0.5), s_v(3, second_array, 0.5);
	CTVector<double> resultsubtraction = s_v - f_v;
	cout << "subtraction: " << resultsubtraction << endl;
	cout << "operator [] test: " << resultsubtraction[0] << endl;

	int resultmultiv = first * second;
	cout << "result of multiplication of vectors : " << resultmultiv << endl;

	CTVector<double> resultmultic = s_v * 5;
	cout << "result of multiplication : " << resultmultic << endl;

	complex<double>  z1(1, 2), z2(3, 4), z3(5, 6), z4(7, 8), z5(9, 10), z6(11, 12);
	complex<double> arr[3] = { z1, z2, z3 }, arr2[3] = { z4, z5, z6 };
	CTVector<complex<double>> complexv(3, arr, 0.5), complexv2(3, arr2, 0.5);
	cout << "complexv : " << complexv << endl;
	cout << "complexv2 : " << complexv2 << endl;

	complex<double> resultofmult = complexv * complexv2;
	cout << "test of multi : " << resultofmult << endl;
	complex<double> multi_of_double_and_complex = f_v * complexv;
	cout << "test multi_of_double_and_complex : " << multi_of_double_and_complex << endl;

	CTVector<complex<double>> plusresult = complexv + f_v;
	cout << "test of summ operation : " << plusresult << endl;


	CTVector<double> v = f_v.UnitPerpendicular();
	cout << "perp double test :" << v << endl;
	CTVector<complex<double>> asd = complexv.UnitPerpendicular();
	cout << "perp duoble copmlex test :" << asd << endl;


	return 0;
}
