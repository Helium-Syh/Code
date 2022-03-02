#include <bits/stdc++.h>
#define int long long 
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

const int p = 10086;

struct LinearBasis {
	int a[32], rnk[32], cnt;
	inline void insert(int x) {
		for (int i = 30; i >= 0; i--) {
			if (x & (1ll << i)) {
				if (!a[i]) { a[i] = x; cnt++; return ;}
				else x ^= a[i];
			}
		}
	}
	inline int query(int x) {
		vector<int> v;
		for (int i = 0; i <= 30; i++)	
			if (a[i]) v.push_back(i);
		int res = 0;
		for (int i = 0; i < v.size(); i++) {
			if (x & (1 << v[i]))
				res |= (1 << i);
		}
		return res;
	}
} line;

inline int Quick_Pow(int a, int b) {
	int base = 1;
	while (b) {
		if (b & 1) base *= a, base %= p;
		a *= a, a %= p; b >>= 1;
	}
	return base;
}

signed main() {
	int n = read();
	for (int i = 1; i <= n; i++) 
		line.insert(read());
	int q = read();
	int rnk = line.query(q);
	printf("%lld", (1ll * rnk * Quick_Pow(2, n - line.cnt) + 1) % p);
	// system("pause");
}
