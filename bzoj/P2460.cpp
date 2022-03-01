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
	int a[64];
	inline bool insert(int x) {
		for (int i = 63; i >= 0; i--) {
			if (x & (1ll << i)) {
				if (!a[i]) { a[i] = x; return true; }
				else x ^= a[i];
			}
		}
		return false;
	}
} line;
struct Stone { int num, magic; } a[1010];
inline bool cmp(Stone x, Stone y) { return x.magic > y.magic; }
signed main() {
	int n = read(), ans = 0;
	for (int i = 1; i <= n; i++) 
		a[i] = (Stone) {read(), read()};
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		if (line.insert(a[i].num))
			ans += a[i].magic;
	printf("%lld", ans);
	// system("pause");
}
