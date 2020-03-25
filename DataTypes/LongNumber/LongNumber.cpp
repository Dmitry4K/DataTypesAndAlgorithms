#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include"LongNumber.h"


const unsigned long long DEFAULT_BASE_FOR_LONG_NUMBER = 1000000;

class LongNumber {
private:
	long long Base = DEFAULT_BASE_FOR_LONG_NUMBER;
	std::vector<long long> Container;
public:
	LongNumber();
	LongNumber(const std::string& str);
	LongNumber(long long a);
	void Clear();
	void Print(std::ostream& out) const;
	friend int Cmp(const LongNumber& a, const LongNumber& b);
	friend bool operator>(const LongNumber& a, const LongNumber& b);
	friend bool operator<(const LongNumber& a, const LongNumber& b);
	friend bool operator>=(const LongNumber& a, const LongNumber& b);
	friend bool operator<=(const LongNumber& a, const LongNumber& b);
	friend bool operator==(const LongNumber& a, const LongNumber& b);
	friend bool operator!=(const LongNumber& a, const LongNumber& b);

	friend LongNumber Sum(const LongNumber& a, const LongNumber& b);//a > 0 , b > 0
	friend LongNumber Sub(const LongNumber& a, const LongNumber& b);// a - b > 0
	friend LongNumber Mult(const LongNumber& a, const LongNumber& b);
	friend LongNumber Div(const LongNumber& a, const LongNumber& b);
	friend LongNumber SmallDiv(const LongNumber& a, const int& b);
	friend LongNumber SmallMult(const LongNumber& a, const int& b);
	friend std::ostream& operator<< (std::ostream& out, const LongNumber& a);
	friend LongNumber Exp(const LongNumber& a, const LongNumber&);
	friend LongNumber SmallExp(const LongNumber& a, const LongNumber& b);
};
LongNumber SmallMult(const LongNumber& a, const int& b);
LongNumber Exp(const LongNumber& a, const LongNumber&);
LongNumber SmallDiv(const LongNumber& a, const int& b);
int Cmp(const LongNumber& a, const LongNumber& b);
LongNumber Sum(const LongNumber& a, const LongNumber& b);
LongNumber Sub(const LongNumber& a, const LongNumber& b);
LongNumber Mult(const LongNumber& a, const LongNumber& b);
LongNumber Div(const LongNumber& a, const LongNumber& b);
std::ostream& operator<< (std::ostream& out, const LongNumber& a);

std::ostream& operator<< (std::ostream& out, const LongNumber& a) {
	a.Print(out);
	return out;
}

LongNumber::LongNumber() {}
LongNumber::LongNumber(const std::string& s) {
	int k = (int)std::log10(Base);
	for (int i = (int)s.length(); i > 0; i -= k)
		if (i < k)
			Container.push_back(atoi(s.substr(0, i).c_str()));
		else
			Container.push_back(atoi(s.substr(i - k, k).c_str()));

	while (Container.size() > 1 && Container.back() == 0)
		Container.pop_back();
}
void LongNumber::Print(std::ostream& out) const{
	out << (Container.empty() ? 0 : Container.back());
	int k = (int)log10(Base);
	for (int i = (int)Container.size() - 2; i >= 0; --i)
		out <<std::setw(k)<<std::setfill('0') <<Container[i];
}
LongNumber::LongNumber(long long a) {
	if (a == 0) {
		Container.push_back(0);
	}
	while (a > 0) {
		Container.push_back(a % Base);
		a /= Base;
	}
}
void LongNumber::Clear() {
	while (Container.size() > 1 && Container[Container.size() - 1] == 0)
		Container.pop_back();
}

int Cmp(const LongNumber& a, const LongNumber& b) {
	if (a.Container.size() != b.Container.size()) {
		return a.Container.size() > b.Container.size() ? 1 : -1;
	}
	for (int i = a.Container.size() - 1; i >= 0; --i) {
		if (a.Container[i] != b.Container[i]) {
			return a.Container[i] > b.Container[i] ? 1 : -1;
		}
	}
	return 0;
}

bool operator>(const LongNumber& a, const LongNumber& b) {
	return Cmp(a, b) == 1 ? true : false;
}
bool operator<(const LongNumber& a, const LongNumber& b) {
	return Cmp(a, b) == -1 ? true : false;
}
bool operator>=(const LongNumber& a, const LongNumber& b) {
	return Cmp(a, b) >=0  ? true : false;
}
bool operator<=(const LongNumber& a, const LongNumber& b) {
	return Cmp(a, b) <= 0 ? true : false;
}
bool operator==(const LongNumber& a, const LongNumber& b) {
	return Cmp(a, b) == 0 ? true : false;
}
bool operator!=(const LongNumber& a, const LongNumber& b) {
	return Cmp(a, b) != 0 ? true : false;
}

LongNumber Sum(const LongNumber& a, const LongNumber& b) {
	long long transfer = 0;
	long long Size = std::max(a.Container.size(), b.Container.size());
	long long S = 0;
	LongNumber C;
	for (int i = 0; i < Size; ++i) {
		if (i >= (int)a.Container.size()) {
			S = b.Container[i] + transfer;
			C.Container.push_back(S % a.Base);
			transfer = S / a.Base;
		}
		else if (i >= (int)b.Container.size()) {
			S = a.Container[i] + transfer;
			C.Container.push_back(S % a.Base);
			transfer = S / a.Base;
		}
		else{
			S = a.Container[i] + b.Container[i] + transfer;
			C.Container.push_back(S % a.Base);
			transfer = S / a.Base;
		}
	}
	if (transfer != 0) {
		C.Container.push_back(transfer);
	}
	return C;
}


LongNumber Sub(const LongNumber& a, const LongNumber& b) {
	if (a < b)
		return Sub(b, a);
	LongNumber C;
	long long transfer = 0;
	long long S;
	for (int i = 0; i < (int)a.Container.size(); ++i) {
		if (i >= (int)b.Container.size()) {
			S = a.Container[i] - transfer;
		}
		else {
			S = a.Container[i] - b.Container[i] - transfer;
		}
		transfer = 0;
		if (S < 0) {
			S += a.Base;
			transfer = 1;
		}
		C.Container.push_back(S);
	}
	C.Clear();
	return C;
}
LongNumber Mult(const LongNumber& a, const LongNumber& b) {
	LongNumber C;
	C.Container.resize(a.Container.size() + b.Container.size());
	for (size_t i = 0; i < a.Container.size(); ++i)
		for (int j = 0, carry = 0; j < (int)b.Container.size() || carry; ++j) {
			long long cur = C.Container[i + j] + a.Container[i] * 1ll * (j < (int)b.Container.size() ? b.Container[j] : 0) + carry;
			C.Container[i + j] = int(cur % a.Base);
			carry = int(cur / a.Base);
		}
	while (C.Container.size() > 1 && C.Container.back() == 0)
		C.Container.pop_back();
	return C;
}
LongNumber Div(const LongNumber& a, const LongNumber& b) {
	LongNumber Res, cv = LongNumber(0);
	Res.Container.resize(a.Container.size());
	for (int i = (int)a.Container.size() - 1; i >= 0; --i) {
		cv.Container.insert(cv.Container.begin(), a.Container[i]);
		if (!cv.Container.back())
			cv.Container.pop_back();
		int x = 0, l = 0, r = a.Base;
		while (l <= r) {
			int m = (l + r) / 2;
			LongNumber cur = SmallMult(b, m);
			if (cur <= cv) {
				x = m;
				l = m + 1;
			}
			else {
				r = m - 1;
			}
		}
		Res.Container[i] = x;
		cv = Sub(cv, SmallMult(b, x));
	}

	while (Res.Container.size() > 1 && Res.Container.back() == 0)
		Res.Container.pop_back();
	return Res;
}
LongNumber SmallDiv(const LongNumber& a, const int& b) {
	LongNumber c;
	c.Container.resize(a.Container.size());
	int carry = 0;
	for (int i = (int)a.Container.size() - 1; i >= 0; --i) {
		long long cur = a.Container[i] + carry * 1ll * a.Base;
		c.Container[i] = int(cur / b);
		carry = int(cur % b);
	}
	while (c.Container.size() > 1 && c.Container.back() == 0)
		c.Container.pop_back();
	return c;
}
LongNumber SmallMult(const LongNumber& a, const int& b) {
	int carry = 0;
	LongNumber C;
	C.Container = std::vector<long long>(a.Container);
	for (size_t i = 0; i < C.Container.size() || carry; ++i) {
		if (i == C.Container.size())
			C.Container.push_back(0);
		long long cur = carry + C.Container[i] * 1ll * b;
		C.Container[i] = int(cur % C.Base);
		carry = int(cur / C.Base);
	}
	while (C.Container.size() > 1 && C.Container.back() == 0)
		C.Container.pop_back();
	return C;
}

LongNumber Exp(const LongNumber& a, const LongNumber& B) {
	if (a == 1) {
		return 1;
	}
	if (B == 0) {
		return 1;
	}
	if (B == 1) {
		return a;
	}
	if (B == 2) {
		return Mult(a, a);
	}
	LongNumber R = SmallDiv(B, 2);
	LongNumber L = Sub(B, R);
	return Mult(Exp(a, L), Exp(a, R));
}

LongNumber SmallExp(const LongNumber& a, const LongNumber& b) {
	LongNumber Res(1);
	LongNumber B(b);
	LongNumber A(a);
	while (B > 0) {
		if (B.Container.back() % 2)
			Res = Mult(Res, A);
		A = Mult(A, A);
		B = SmallDiv(B, 2);
	}
	return Res;
}
