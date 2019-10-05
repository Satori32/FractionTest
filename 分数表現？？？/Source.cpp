#include <iostream>
#include <cstdint>
#include <numeric>
#include <limits>
#include <algorithm>

//cant use for minus field.

class Fraction {
public:
	Fraction(){}
	Fraction(std::intmax_t N):Denominator(1),Numerator(N){}
	Fraction(std::intmax_t Bunnsi,std::uintmax_t Bunnbo):Numerator(Bunnsi),Denominator(Bunnbo){}

	operator double() const {
		return (Numerator / (double)Denominator) ;
	}
	std::intmax_t& GetNumerator() {
		return Numerator;
	}
	std::intmax_t GetNumerator() const {
		return Numerator;

	}	std::uintmax_t& GetDenominator(){
		return Denominator;
	}
	std::uintmax_t GetDenominator() const {
		return Denominator;
	}
	bool Set(const std::intmax_t& N,const std::uintmax_t& D){
		Denominator = D;
		Numerator = N;
		return true;

	}
	bool Denomi() {
		std::intmax_t D = std::gcd(std::abs(Numerator), Denominator);

		while (D != 1) {
			Numerator /= D;
			Denominator /= D;
			D = std::gcd(std::abs(Numerator), Denominator);
		}
		return true;
	}

	double ToDouble() {
		return *this;
	}
	Fraction operator +(const Fraction& In)const {		
		std::uintmax_t Mul= GetDenominator()* In.GetDenominator();
		Fraction A{static_cast<std::intmax_t>(GetNumerator() * (Mul/GetDenominator())),Mul};
		Fraction B{static_cast<std::intmax_t>(In.GetNumerator() * (Mul/In.GetDenominator())),Mul};
		Fraction T{ A.GetNumerator() + B.GetNumerator(),Mul };
		T.Denomi();
		return T;

	}
	Fraction operator -(const Fraction& In)const {
		std::uintmax_t Mul= GetDenominator()* In.GetDenominator();
		Fraction A{static_cast<std::intmax_t>(GetNumerator() * (Mul/GetDenominator())),Mul};
		Fraction B{static_cast<std::intmax_t>(In.GetNumerator() * (Mul/In.GetDenominator())),Mul};
		Fraction T{ A.GetNumerator() - B.GetNumerator(),Mul };
		T.Denomi();		
		return T;
	}
	Fraction operator *(const Fraction& In)const {
		Fraction T(GetNumerator() * In.GetNumerator(), GetDenominator() * In.GetDenominator());
		T.Denomi();
		return T;
	
	}

	Fraction operator /(const Fraction& In)const {
		Fraction T(GetNumerator() * In.GetDenominator()*(In.GetNumerator()>0?1:-1), GetDenominator() * std::abs(In.GetNumerator()));


		T.Denomi();
		return T;
	
	}

protected:
	std::uintmax_t Denominator = 1;//•ª•ê
	std::intmax_t Numerator = 0;//•ªŽq
};

int main() {
	Fraction A = 10;
	Fraction AA = 100;
	Fraction B(-1, 10);

	Fraction C = A + B;
	Fraction D = B - A;
	Fraction E = A * B;
	Fraction F = A / B;

	Fraction CC = AA + A;
	Fraction DD = AA - A;
	Fraction EE = AA * A;
	Fraction FF = AA / A;

	std::cout << C.GetNumerator() << '/' << C.GetDenominator() <<'='<<C<< std::endl;
	std::cout << D.GetNumerator() << '/' << D.GetDenominator() <<'='<<D<< std::endl;
	std::cout << E.GetNumerator() << '/' << E.GetDenominator() <<'='<<E<< std::endl;
	std::cout << F.GetNumerator() << '/' << F.GetDenominator() <<'='<<F<< std::endl;

	std::cout << CC.GetNumerator() << '/' << CC.GetDenominator() <<'='<<CC<< std::endl;
	std::cout << DD.GetNumerator() << '/' << DD.GetDenominator() <<'='<<DD<< std::endl;
	std::cout << EE.GetNumerator() << '/' << EE.GetDenominator() <<'='<<EE<< std::endl;
	std::cout << FF.GetNumerator() << '/' << FF.GetDenominator() <<'='<<FF<< std::endl;
	return 0;
}
