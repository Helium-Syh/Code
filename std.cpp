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
int fa[N], ch[N][2], tag[N], sum[N], siz[N], st[N];
inline bool isroot(int x) {
	return ch[fa[x]][0] != x and ch[fa[x]][1] != x;
}
inline void push_up(int x) {
	sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + 1 + siz[x];
}
inline void push_down(int x) {
	if (tag[x]) {
		swap(ch[x][0], ch[x][1]);
		tag[ch[x][0]] ^= 1; 
		tag[ch[x][1]] ^= 1;
		tag[x] = 0;
	}
}
inline void rotate(int x) {
	int y = fa[x], z = fa[y], chk = ch[fa[x]][1] == x;
	ch[y][chk] = ch[x][chk ^ 1];
	if (ch[x][chk ^ 1]) 
		fa[ch[x][chk ^ 1]] = y;
	ch[x][chk ^ 1] = y;
	if (!isroot(y)) 
		ch[z][ch[z][1] == y] = x;
	fa[x] = z; fa[y] = x;
	push_up(y); push_up(x);
}
inline void splay(int x) {
	int y = x, z, top = 0;
	st[++top] = y;
	while (!isroot(y)) st[++top] = (y = fa[y]);
	while (top) push_down(st[top--]);
	while (!isroot(x)) {
		y = fa[x], z = fa[y];
		if (!isroot(y))
			rotate((ch[z][1] == y) ^ (ch[z][1] == y) ? x : y);
		rotate(x);
	}
	push_up(x);
}
inline void access(int x) {
	for (int y = 0; x; y = x, x = fa[y = x]) {
		splay(x), siz[x] += sum[ch[x][1]] - sum[y];
		ch[x][1] = y, push_up(x);
	}
}
inline void makeroot(int x) {
	access(x); splay(x);
	tag[x] ^= 1; push_down(x);
}
inline void split(int x, int y) {
	makeroot(x); 
	access(y); splay(y);
}
inline void link(int x, int y) {
	makeroot(x);
	makeroot(y);
	fa[x] = y;
	siz[y] += sum[x];
	push_up(y);
}
signed main() {
	int n = read(), q = read();
	for (int i = 1; i <= n; i++) sum[i] = 1;
	while (q--) {
		char ch[2]; scanf("%s", ch);
		int x = read(), y = read();
		if (ch[0] == 'A') 
			link(x, y);
		else 
			split(x, y), printf("%lld\n", sum[x] * (sum[y] - sum[x]));
	}
	system("pause");
}