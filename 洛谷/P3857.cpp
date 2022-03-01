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
	int a[52], cnt;
	inline void insert(int x) {
		for (int i = 51; i >= 0; i--) {
			if (x & (1ll << i)) {
				if (!a[i]) { a[i] = x; cnt++; return ; }
				else x ^= a[i];
			}
		}
	}
} line;
char s[52];
signed main() { 
	int n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		scanf("%s", s + 1); int num = 0;
		for (int j = 1; j <= n; j++) 
			num += (1ll << j) * (s[j] == 'O');
		// printf("num");
		line.insert(num);
	}
	printf("%lld\n", (1ll << line.cnt) % 2008);
	// system("pause");
}
