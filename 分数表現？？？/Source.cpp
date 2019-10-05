#include <iostream>
#include <cstdint>
#include <numeric>
#include <limits>

//cant use for minus field.

class Fraction {
public:
	Fraction(){}
	Fraction(std::uintmax_t N):Denominator(1),Numerator(N){}
	Fraction(std::uintmax_t Bunnsi,std::uintmax_t Bunnbo,bool IsMinus=false):Numerator(Bunnsi),Denominator(Bunnbo),SignF(IsMinus){}

	operator double() const {
		return SignF ? (Numerator / (double)Denominator) : -(Numerator / (double)Denominator);
	}

	std::uintmax_t GetNumerator() const {
		return Numerator;
	}
	std::uintmax_t GetDenominator() const {
		return Denominator;
	}

	bool Set(const std::uintmax_t& N,const std::uintmax_t& D,bool F){
		Denominator = D;
		Numerator = N;
		SignF =F;
		return true;

	}
	bool Set(const std::uintmax_t& N,const std::uintmax_t& D){
		Denominator = D;
		Numerator = N;
		return true;

	}
	bool Denomi() {
		std::uintmax_t D = std::gcd(Numerator, Denominator);

		while (D != 1) {
			Numerator /= D;
			Denominator /= D;
			D = std::gcd(Numerator, Denominator);
		}
		return true;
	}

	double ToDouble() {
		return *this;
	}
	Fraction operator +(const Fraction& In)const {		
		std::uintmax_t Mul= GetDenominator()* In.GetDenominator();
		Fraction A{(GetNumerator() * (Mul/GetDenominator())),Mul};
		Fraction B{(In.GetNumerator() * (Mul/In.GetDenominator())),Mul};
		Fraction T{ A.GetNumerator() + B.GetNumerator(),Mul };
		T.Denomi();
		return T;

	}
	Fraction operator -(const Fraction& In)const {
		std::uintmax_t Mul= GetDenominator()* In.GetDenominator();
		Fraction A{(GetNumerator() * (Mul/GetDenominator())),Mul};
		Fraction B{(In.GetNumerator() * (Mul/In.GetDenominator())),Mul};
		Fraction T{ A.GetNumerator() - B.GetNumerator(),Mul };
		if (T.GetNumerator() > GetNumerator()) {//this is bad of bad.
			T.Set(std::numeric_limits<std::uintmax_t>::max() - T.GetNumerator()+1, T.GetDenominator());
			T.SignF = true;
		}
		T.Denomi();		
		return T;
	}
	Fraction operator *(const Fraction& In)const {
		Fraction T(GetNumerator() * In.GetNumerator(), GetDenominator() * In.GetDenominator());

		if (In.SignF != SignF) {T.SignF = true;	}
		if (In.SignF == SignF) {T.SignF = false;}

		T.Denomi();
		return T;
	
	}

	Fraction operator /(const Fraction& In)const {
		Fraction T(GetNumerator() * In.GetDenominator(), GetDenominator() * In.GetNumerator());

		if (In.SignF != SignF) {T.SignF = true;	}
		if (In.SignF == SignF) {T.SignF = false;}
		
		T.Denomi();
		return T;
	
	}

protected:
	std::uintmax_t Denominator = 1;//分母
	std::uintmax_t Numerator = 0;//分子
	bool SignF = false;//マイナスか？
};

int main() {
	Fraction A = 10;
	Fraction AA = 100;
	Fraction B(1, 10);

	Fraction C = A + B;
	Fraction D = B - A;
	Fraction E = A * B;
	Fraction F = A / B;

	Fraction CC = AA + A;
	Fraction DD = AA - A;
	Fraction EE = AA * A;
	Fraction FF = AA / A;

	std::cout << C.GetNumerator() << '/' << C.GetDenominator() << std::endl;
	std::cout << D.GetNumerator() << '/' << D.GetDenominator() << std::endl;
	std::cout << E.GetNumerator() << '/' << E.GetDenominator() << std::endl;
	std::cout << F.GetNumerator() << '/' << F.GetDenominator() << std::endl;
	std::cout << CC.GetNumerator() << '/' << CC.GetDenominator() << std::endl;
	std::cout << DD.GetNumerator() << '/' << DD.GetDenominator() << std::endl;
	std::cout << EE.GetNumerator() << '/' << EE.GetDenominator() << std::endl;
	std::cout << FF.GetNumerator() << '/' << FF.GetDenominator() << std::endl;
	return 0;
}
