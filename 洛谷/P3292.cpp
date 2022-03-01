#include <bits/stdc++.h>
#define N 20010
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}
int n, q; long long g[N];
int tot, head[N];
struct Edge { int to, nxt; } edge[N << 1];
inline void add(int u, int v) {
	edge[++tot].to = v; edge[tot].nxt = head[u]; head[u] = tot;
}

struct LinearBasis {
	long long a[62];
	LinearBasis() { memset(a, 0, sizeof(a)); }
    inline void insert(long long x) {
        for (int i = 61; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (!a[i]) { a[i] = x; return ; }
				else x ^= a[i];
            }
		}
    }
	inline long long query() {
        long long res = 0;
        for (int i = 61; i >= 0; i--)
            if ((res ^ a[i]) > res) 
				res ^= a[i];
        return res;
    }
};

inline LinearBasis merge(LinearBasis x, LinearBasis y) {
	for (int i = 0; i <= 61; i++)
		if(y.a[i])
			x.insert(y.a[i]); 
	return x;
}

int fa[N][16], dep[N]; LinearBasis F[N][16];
inline void dfs1(int u, int father) {
	fa[u][0] = father; dep[u] = dep[father] + 1; 
	F[u][0].insert(g[u]);
	for (int i = 1; i <= 15; i++) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		F[u][i] = merge(F[u][i - 1], F[fa[u][i - 1]][i - 1]);
	}
	for (int e = head[u]; e; e = edge[e].nxt) {
		int v = edge[e].to;
		if (v == father) continue;
		dfs1(v, u);
	}
}

inline long long lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	LinearBasis tmp; 
	for (int i = 15; i >= 0; i--) {
		if (dep[fa[x][i]] >= dep[y])
			tmp = merge(tmp, F[x][i]), x = fa[x][i];
	}
	if (x == y) { tmp.insert(g[x]); return tmp.query(); }
	for (int i = 15; i >= 0; i--) {
		if (fa[x][i] != fa[y][i]) {
			tmp = merge(tmp, F[x][i]);
			tmp = merge(tmp, F[y][i]);
			x = fa[x][i], y = fa[y][i];
		}
	}
	tmp.insert(g[fa[x][0]]);
	tmp.insert(g[x]);
	tmp.insert(g[y]);
	return tmp.query();
}

signed main() {
	n = read(), q = read();
	for (int i = 1; i <= n; i++) scanf("%lld", &g[i]);
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		add(u, v); add(v, u);
	}
	dfs1(1, 0);
	while (q--) {
		int u = read(), v = read();
		printf("%lld\n", lca(u, v));
	}
	// system("pause");
}
