#include <bits/stdc++.h>
#define N 1000010
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int fa[N], ch[N][2], val[N], s[N], st[N], tag[N];

inline bool isroot(int x) { //判断x是否为splay的根节点
	return ch[fa[x]][0] != x and ch[fa[x]][1] != x;
}
inline void push_up(int x) {
	s[x] = s[ch[x][0]] ^ s[ch[x][1]] ^ val[x];
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
	int y = fa[x], z = fa[y], chk = (ch[y][1] == x);
	ch[y][chk] = ch[x][chk ^ 1];
	if (ch[x][chk ^ 1])
		fa[ch[x][chk ^ 1]] = y;
	ch[x][chk ^ 1] = y;
	if (!isroot(y)) ch[z][ch[z][1] == y] = x;
	fa[x] = z; fa[y] = x;
	push_up(y), push_up(x);
}
inline void splay(int x) {
	int y = x, z, top = 0;
	st[++top] = y;
	while (!isroot(y)) st[++top] = y = fa[y];
	while (top) push_down(st[top--]);
	while (!isroot(x)) {
		y = fa[x], z = fa[y];
		if (!isroot(y)) 
			rotate((ch[y][1] == x) ^ (ch[z][1] == y) ? x : y);
		rotate(x);
	}
	push_up(x);
}
inline void access(int x) {
	for (int y = 0; x; x = fa[y = x])
		splay(x), ch[x][1] = y, push_up(x);
}
inline void makeroot(int x) {
	access(x); splay(x);
	tag[x] ^= 1; push_down(x);
}
inline int findroot(int x) {
	access(x); splay(x);
	while (ch[x][0]) x = ch[x][0];
	return x;
}
inline void split(int x, int y) {
	makeroot(x);
	access(y); splay(y);
}
inline void link(int x, int y) {
	makeroot(x);
	if (findroot(y) != x) fa[x] = y;
}
inline void cut(int x, int y) {
	makeroot(x);
	if (findroot(y) == x and fa[x] == y and !ch[x][0]) {
		fa[x] = ch[y][0] = 0;
		push_up(y);
	}
}

int main() {
	int n = read(), m = read();
	for (int i = 1; i <= n; i++) val[i] = read();
	while (m--) {
		int type = read(), x = read(), y = read();
		if (type == 0) 
			split(x, y), printf("%d\n", s[y]);
		else if (type == 1) 
			link(x, y);
		else if (type == 2) 
			cut(x, y);
		else splay(x), val[x] = y;
	}
	// system("pause");
}
