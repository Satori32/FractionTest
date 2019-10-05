#include <iostream>
#include <cstdint>
#include <numeric>
#include <limits>
#include <algorithm>

//cant use for minus field.
//std::gcd need C++17.

#define CONSTEXPR /**/constexpr/**/

class Fraction {
protected:
	template<class T>
	CONSTEXPR T Abs(const T& In) const {
		return In > 0 ? In : -In;
	}
	template<class T>
	CONSTEXPR T Gcd(T A,T B) const {
		if (A < B) {
			T AA = A;
			A = B;
			B = AA;
		}
		T R = A%B;
		while (R) {
			A = B;
			B = R;
			R = A % B;
		}
		return B;
	}
public:
	CONSTEXPR Fraction(){}
	CONSTEXPR Fraction(std::intmax_t N):Denominator(1),Numerator(N){}
	CONSTEXPR Fraction(std::intmax_t Bunnsi,std::uintmax_t Bunnbo):Numerator(Bunnsi),Denominator(Bunnbo){}

	CONSTEXPR operator double() const {
		return (Numerator / (double)Denominator) ;
	}
	CONSTEXPR std::intmax_t& GetNumerator() {
		return Numerator;
	}
	CONSTEXPR std::intmax_t GetNumerator() const {
		return Numerator;

	}	std::uintmax_t& GetDenominator(){
		return Denominator;
	}
	CONSTEXPR std::uintmax_t GetDenominator() const {
		return Denominator;
	}
	CONSTEXPR bool Set(const std::intmax_t& N,const std::uintmax_t& D){
		Denominator = D;
		Numerator = N;
		return true;

	}
	CONSTEXPR bool Denomi() {
		std::intmax_t D = Gcd<std::uintmax_t>(Abs(Numerator), Denominator);

		while (D != 1) {
			Numerator /= D;
			Denominator /= D;
			D =  Gcd<std::uintmax_t>(Abs(Numerator), Denominator);
		}
		return true;
	}

	CONSTEXPR double ToDouble() const{
		return *this;
	}
	CONSTEXPR Fraction operator +(const Fraction& In)const {		
		std::uintmax_t Mul= GetDenominator()* In.GetDenominator();
		Fraction A{static_cast<std::intmax_t>(GetNumerator() * (Mul/GetDenominator())),Mul};
		Fraction B{static_cast<std::intmax_t>(In.GetNumerator() * (Mul/In.GetDenominator())),Mul};
		Fraction T{ A.GetNumerator() + B.GetNumerator(),Mul };
		T.Denomi();
		return T;

	}
	CONSTEXPR Fraction operator -(const Fraction& In)const {
		std::uintmax_t Mul= GetDenominator()* In.GetDenominator();
		Fraction A{static_cast<std::intmax_t>(GetNumerator() * (Mul/GetDenominator())),Mul};
		Fraction B{static_cast<std::intmax_t>(In.GetNumerator() * (Mul/In.GetDenominator())),Mul};
		Fraction T{ A.GetNumerator() - B.GetNumerator(),Mul };
		T.Denomi();		
		return T;
	}
	CONSTEXPR Fraction operator *(const Fraction& In)const {
		Fraction T(GetNumerator() * In.GetNumerator(), GetDenominator() * In.GetDenominator());
		T.Denomi();
		return T;
	
	}

	CONSTEXPR Fraction operator /(const Fraction& In)const {
		int S = In.GetNumerator() > 0 ? 1 : -1;
		Fraction T(GetNumerator() * In.GetDenominator()*S,GetDenominator() * Abs(In.GetNumerator()));


		T.Denomi();
		return T;
	
	}


public:

protected:
	std::uintmax_t Denominator = 1;//•ª•ê
	std::intmax_t Numerator = 0;//•ªŽq
};


template<class Char>
std::basic_ostream<Char>& operator <<(std::basic_ostream<Char>& os, const Fraction& F) {
	os << F.GetNumerator() << '/' << F.GetDenominator();
	return os;
}
/** /
int main() {

	constexpr std::size_t L = 100;
	for (std::uintmax_t i = 1; i < L; i++) {
		for (std::intmax_t j = 0; j < L; j++) {
			Fraction F(j, i);	
			std::cout <<F<<'='<<static_cast<double>(F)<< std::endl;
		}
	}

	return 0;

}
/**/
int main() {
	CONSTEXPR Fraction A = 10;
	CONSTEXPR Fraction AA = 100;
	CONSTEXPR Fraction B(-1, 10);

	CONSTEXPR Fraction C = A + B;
	CONSTEXPR Fraction D = B - A;
	CONSTEXPR Fraction E = A * B;
	CONSTEXPR Fraction F = A / B;

	CONSTEXPR Fraction CC = AA + A;
	CONSTEXPR Fraction DD = AA - A;
	CONSTEXPR Fraction EE = AA * A;
	CONSTEXPR Fraction FF = AA / A;

	std::cout << C.GetNumerator() << '/' << C.GetDenominator() <<'='<<C<<'='<<static_cast<double>(C)<<std::endl;
	std::cout << D.GetNumerator() << '/' << D.GetDenominator() <<'='<<D<<'='<<static_cast<double>(D)<<std::endl;
	std::cout << E.GetNumerator() << '/' << E.GetDenominator() <<'='<<E<<'='<<static_cast<double>(E)<<std::endl;
	std::cout << F.GetNumerator() << '/' << F.GetDenominator() <<'='<<F<<'='<<static_cast<double>(F)<<std::endl;

	std::cout << CC.GetNumerator() << '/' << CC.GetDenominator() <<'='<<CC<< std::endl;
	std::cout << DD.GetNumerator() << '/' << DD.GetDenominator() <<'='<<DD<< std::endl;
	std::cout << EE.GetNumerator() << '/' << EE.GetDenominator() <<'='<<EE<< std::endl;
	std::cout << FF.GetNumerator() << '/' << FF.GetDenominator() <<'='<<FF<< std::endl;
	return 0;
}
/**/