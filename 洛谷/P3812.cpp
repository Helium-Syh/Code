#include <bits/stdc++.h>
#define int long long 
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}
struct LinearBasis {
	int a[52];
	inline void insert(int x) {
		for (int i = 51; i >= 0; i--) {
			if (x & (1ll << i)) {
				if (!a[i]) { a[i] = x; return ; }
				else x ^= a[i];
			}
		}
	}
	inline int query() {
		int ans = 0;
		for (int i = 51; i >= 0; i--) 
			ans = max(ans, ans ^ a[i]);
		return ans;
	}
} line;
signed main() {
	int n = read();
	for (int i = 1; i <= n; i++) 
		line.insert(read());
	printf("%lld\n", line.query());
	// system("pause");
}
