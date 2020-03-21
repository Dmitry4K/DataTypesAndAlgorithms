#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include"LongNumber.h"


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
}
void LongNumber::Print(std::ostream& out) const{
	out << (Container.empty() ? 0 : Container.back());
//	out.width((int)log10(Base));
	for (int i = (int)Container.size() - 2; i >= 0; --i)
		out <<std::setw((int)log10(Base))<<std::setfill('0') <<Container[i];
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

	/*
	int n = b.Container.size();
	int m = a.Container.size() - b.Container.size();//*/
	//нормализаци€
	int d = (int)(a.Base / (b.Container.back() + 1));
	LongNumber u = SmallMult(a, d);
	LongNumber v = SmallMult(b, d);
	//std::cout << "Start u: " << u << " and v: " << v;
	//std::cout << " d: " << d << std::endl;
	int n = v.Container.size();
	int m = u.Container.size() - v.Container.size();
	
	LongNumber Q;
	if (n == 1) {
		Q = SmallDiv(a, b.Container.back());
		return Q;
	}
	if (u.Container.size() == n+m) {
		u.Container.push_back(0);
		//std::cout << "u is uped!\n";
	}
	Q.Container.resize(m + 1);
	//начальна€ установка
	int j = m;
	while (j >= 0) {
		int q = ((u.Container[j + n] * u.Base + u.Container[j + n - 1]) / v.Container[n - 1]);
		int r = ((u.Container[j + n] * u.Base + u.Container[j + n - 1]) % v.Container[n - 1]);
		//вычислить q

		//std::cout << "q: " << q << ' ';
		do	{
			if (q == u.Base || q * v.Container[n - 2] > u.Base* r + u.Container[j + n - 2]){
				--q;
				//std::cout << q << ' ';
				r += v.Container[n - 1];
			}
			else{
				break;
			}
		} while (r < u.Base);
		//умножить и вычесть
		//LongNumber t;
		//t.Container = std::vector<long long>(n);
		//std::copy(u.Container.begin() + j, u.Container.begin() + j + n, t.Container.begin());
		LongNumber k = SmallMult(v, q*std::pow(a.Base, j));
		//компенсировать сложение
		if (u < k) {
			u = Sub(u, k);
			--q;
			//std::cout << q << ' ';
			u = Sub(u, v);
		}
		else {
			u = Sub(u, k);
			for (int i = u.Container.size(); i < n + m; ++i)
				u.Container.push_back(0);
		}
		//std::copy(t.Container.begin(), t.Container.end(), u.Container.begin() + j);
		
		//std::cout << q << ' ' << std::endl <<"u: "<< u <<" k: "<< k<< std::endl;
		Q.Container[j] = q;
		--j;
	}
	while (Q.Container.size() > 1 && Q.Container.back() == 0)
		Q.Container.pop_back();
	return Q;
	/*
	//начальна€ инициализаци€ u/v a/b
	//int n = v.arr.Count;
	int n = b.Container.size();//длина делител€
	//int m = u.arr.Count - v.arr.Count; 
	int m = a.Container.size() - b.Container.size();//разница длин делител€ и делимого
	//int[] tempArray = new int[m + 1];
	//tempArray[m] = 1;
	//q = new BigInteger(tempArray, true);
	LongNumber q(1); //результат вычислени€
	//Ќормализаци€
	//int d = (myBase / (v.arr[n - 1] + 1));
	int d = (a.Base / (b.Container[n - 1] + 1));
	u = u.Multiply(d);
	v = v.Multiply(d);
	if (u.arr.Count == n + m)//аккуратна€ проверка на d==1
	{
		u.arr.Add(0);
	}
	//Ќачальна€ установка j
	int j = m;
	//÷икл по j
	while (j >= 0)
	{
		//¬ычислить временное q
		long cur = (long)(u.arr[j + n]) * (long)(myBase)+u.arr[j + n - 1];
		int tempq = (int)(cur / v.arr[n - 1]);//нормализаци€ помогает не выпрыгнуть за границу типа
		int tempr = (int)(cur % v.arr[n - 1]);
		do
		{
		if (tempq == myBase || (long)tempq * (long)v.arr[n - 2] > (long)myBase* (long)tempr + u.arr[j + n - 2])
		{
			tempq--;
			tempr += v.arr[n - 1];
		}
		else
		{
			break;
		}
		} while (tempr < myBase); 
		//”множить и вычесть 
		BigInteger u2 = new BigInteger(u.arr.GetRange(j, n + 1), true); u2 = u2.Substract(v.Multiply(tempq)); bool flag = false; if (!u2.sign)//если отрицательные { flag = true; List bn = new List();
		for (int i = 0; i <= n; i++) { bn.Add(0); } bn.Add(1); u2.ChangeSign(true); u2 = new BigInteger(bn, true).Substract(u2);
	} 
	//ѕроверка остатка q.arr[j] = tempq; if (flag) { // омпенсировать сложение q.arr[j]--; u2 = u2.Add(v); if(u2.arr.Count>n+j)
	u2.arr.RemoveAt(n + j);

	//мен€ем u, так как все вычислени€ происход€т с его разр€дами
	for (int h = j; h < j + n; h++) {
		if (h - j >= u2.arr.Count)
		{
			u.arr[h] = 0;
		}
		else
		{
			u.arr[h] = u2.arr[h - j];
		}
	}
	j--;
	}
	q.arr = q.normalize(q.arr);
	//ƒенормализаци€
	int unusedR = 0;
	r = new BigInteger(u.arr.GetRange(0, n), true).Divide(d, out unusedR);
	return 0;
	//*/
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
