#include <bits/stdc++.h>
#define int long long 
#define N 1000010
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m;
int tot, head[N];
struct Edge { int to, nxt, dis; } edge[N];
inline void add(int u, int v, int w) {
	edge[++tot].to = v; edge[tot].nxt = head[u]; head[u] = tot; edge[tot].dis = w;
}

struct LinearBasis {
	int a[64];
	inline void insert(int x) {
		for (int i = 62; i >= 0; i--) {
			if (x & (1ll << i)) {
				if (!a[i]) { a[i] = x; return ; }
				else x ^= a[i]; 
			}
		}
	}
	inline int query(int res) {
		for (int i = 62; i >= 0; i--) {
			if ((res ^ a[i]) > res) 
				res ^= a[i];
		}
		return res;
	}
} line;

int ans[N]; bool vis[N];
inline void dfs(int u, int res) {
	ans[u] = res; vis[u] = true;
	for (int e = head[u]; e; e = edge[e].nxt) {
		int v = edge[e].to;
		if (!vis[v]) dfs(v, res ^ edge[e].dis);
		else line.insert(res ^ edge[e].dis ^ ans[v]);
	}
}

signed main() {
	int n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read(), w = read();
		add(u, v, w); add(v, u, w);
	}
	dfs(1, 0);
	printf("%lld", line.query(ans[n]));
	// system("pause");
}
