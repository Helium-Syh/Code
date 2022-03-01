#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define N 1000010
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}
int n, q, h[N], a[N];
vector<int> E[N];
int tot, head[N];
struct Edge { int to, nxt; } edge[N];
inline void add(int u, int v) {
	edge[++tot].to = v; edge[tot].nxt = head[u]; head[u] = tot;
}

int fa[N][21], siz[N], dep[N], dfn[N], dfncnt;
inline void dfs1(int u, int father) {
	fa[u][0] = father; dep[u] = dep[father] + 1; dfn[u] = ++dfncnt;
	for (int i = 1; i <= 20; i++) 
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int i = 0; i < E[u].size(); i++) {
		int v = E[u][i];
		if (v == father) continue;
		dfs1(v, u); siz[u] += siz[v];
	} siz[u] += 1;
}
inline int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 20; i >= 0; i--) {
		if (dep[fa[x][i]] >= dep[y])
			x = fa[x][i];
	}
	if (x == y) return x;
	for (int i = 20; i >= 0; i--) {
		if (fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	}
	return fa[x][0];
}

inline bool cmp(int x, int y) { return dfn[x] < dfn[y]; }

int s[N], top;
inline void ins(int x) {
    if (!top) { s[++top] = x; return ; }
    int ance = lca(x, s[top]); 
    while (top > 1 and dep[ance] < dep[s[top - 1]]) 
        add(s[top - 1], s[top]), --top;
    if (dep[ance] < dep[s[top]]) 
		add(ance, s[top--]);
    if (!top or s[top] != ance) 
		s[++top] = ance;
    s[++top] = x;
}

bool flag[N]; int id[N], dis[N];

inline void dfs2(int u) {
	if (flag[u]) id[u] = u, dis[u] = 0;
	else id[u] = 0, dis[u] = inf;
	for (int e = head[u]; e; e = edge[e].nxt) {
		int v = edge[e].to;
		dfs2(v);
		if (!id[u] or dep[id[v]] < dep[id[u]] or (dep[id[v]] == dep[id[u]] and id[u] > id[v]))
			id[u] = id[v], dis[u] = dep[id[u]] - dep[u];
	}
}
inline void dfs3(int u, int father) {
	if (father) {
		int len = dis[father] + dep[u] - dep[father];
		if (dis[u] > len or (len == dis[u] and id[father] < id[u])) 
			id[u] = id[father], dis[u] = len;
	}
	for (int e = head[u]; e; e = edge[e].nxt) {
		int v = edge[e].to;
		dfs3(v, u);
	}
}
inline int jump(int x, int len) {
	for (int i = 20; i >= 0; i--) {
		if (len >= (1 << i))
			len -= (1 << i), x = fa[x][i];
	}
	return x;
}
int ans[N];
inline void dfs4(int u) {
	int cnt = siz[u];
	for (int e = head[u]; e; e = edge[e].nxt) {
		int v = edge[e].to; dfs4(v);
		// cout << u << " " << v << " " << id[u] << " " << id[v] << endl;
		if (id[v] == id[u]) cnt -= siz[v];
		else {
			int len = dep[id[v]] - dep[u] + dis[u];
			if (len == 1) 
				cnt -= siz[v];
			else {
				int x;
				if (id[u] > id[v]) 
					x = jump(id[v], len / 2);
				else 
					x = jump(id[v], (len - 1) / 2);
				cnt -= siz[x];
				ans[id[v]] += siz[x] - siz[v];
			}
		}
	}
	ans[id[u]] += cnt;
}

inline void clear(int u) {
	for (int e = head[u]; e; e = edge[e].nxt) {
		int v = edge[e].to;
		clear(v);
	}
	head[u] = 0; flag[u] = false; ans[u] = 0;
}

int main() {
	n = read();
	for (int i = 1; i < n; i++) {
		int u = read(), v = read();
		E[u].push_back(v);
		E[v].push_back(u);
	}
	dfs1(1, 0); 
	// for (int i = 1; i <= n; i++) {
	// 	int u = read(), v = read();
	// 	printf("%d\n", lca(u, v));
	// }
	q = read();
	while (q--) {
		int m = read(); tot = 0;
		for (int i = 1; i <= m; i++)
			h[i] = a[i] = read(), flag[h[i]] = true;
		sort(a + 1, a + m + 1, cmp);
		if (a[1] != 1) s[++top] = 1;
		for (int i = 1; i <= m; i++)
			ins(a[i]);
		if (top) {
			while (--top)		
				add(s[top], s[top + 1]);
		}
		dfs2(1); dfs3(1, 0); dfs4(1);
		for (int i = 1; i <= m; i++)
			printf("%d ", ans[h[i]]);
		printf("\n");
		clear(1);
	}
	// system("pause");
}
