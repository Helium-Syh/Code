#include <bits/stdc++.h>
#define int long long 
#define N 20010
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	return x * f;
}
int n, Q, ans, a[N], b[N], rt[N];
vector<int>v[N];
struct Peresitant_Segment_Tree {
	int ls[N << 5], rs[N << 5], sum[N << 5], pre[N << 5], suf[N << 5], tot;
	#define ls(p) ls[p]
	#define rs(p) rs[p]
	inline void build(int &p, int l, int r) {
		p = ++tot;
		if(l == r) return ;
		int mid = (l + r) >> 1;
		build(ls(p), l, mid);
		build(rs(p), mid + 1, r);
	}
	inline void push_up(int p) {
		sum[p] = sum[ls(p)] + sum[rs(p)];
		suf[p] = max(suf[rs(p)], suf[ls(p)] + sum[rs(p)]);
		pre[p] = max(pre[ls(p)], pre[rs(p)] + sum[ls(p)]);
	}
	inline void update(int &p, int pr, int l, int r, int x, int k) {
		p = ++tot; ls[p] = ls[pr]; rs[p] = rs[pr];
		sum[p] = sum[pr]; pre[p] = pre[pr]; suf[p] = suf[pr];
		if(l == r) {
			sum[p] = k;
			pre[p] = suf[p] = max(k, 0ll);
			return ;
		}
		int mid = (l + r) >> 1;
		if(x <= mid) update(ls(p), ls(pr), l, mid, x, k);
		else update(rs(p), rs(pr), mid + 1, r, x, k);
		push_up(p);
	}
	inline int query_sum(int p, int l, int r, int nl, int nr) {
		if(nl <= l and r <= nr) return sum[p];
		if(nl > r or nr < l) return 0;
		int mid = (l + r) >> 1, res = 0;
		if(nl <= mid) res += query_sum(ls(p), l, mid, nl, nr);
		if(nr > mid) res += query_sum(rs(p), mid + 1, r, nl, nr);
		return res;
	}
	inline int query_pre(int p, int l, int r, int nl, int nr) {
		if(nl <= l and r <= nr) return pre[p];
		if(nl > r or nr < l) return 0;
		int mid = (l + r) >> 1;
		return max(query_pre(ls(p), l, mid, nl, nr), query_sum(ls(p), l, mid, nl, nr) + query_pre(rs(p), mid + 1, r, nl, nr));
	}
	inline int query_suf(int p, int l, int r, int nl, int nr) {
		if(nl <= l and r <= nr) return suf[p];
		if(nl > r or nr < l) return 0;
		int mid = (l + r) >> 1;
		return max(query_suf(rs(p), mid + 1, r, nl, nr), query_suf(ls(p), l, mid, nl, nr) + query_sum(rs(p), mid + 1, r, nl, nr));
	}
} tree;
int las;	
signed main() {
	n = read();
	for(int i = 1; i <= n; i++) a[i] = read(), b[i] = a[i];
	sort(b + 1, b + n + 1);
	int tot = unique(b + 1, b + n + 1) - b - 1;
	for(int i = 1; i <= n; i++) {
		a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
		v[a[i]].push_back(i);
	}
	tree.build(rt[1], 1, n);
	for(int i = 1; i <= n; i++) tree.update(rt[1], rt[1], 1, n, i, 1);  
	for(int i = 2; i <= tot; i++) {
		rt[i] = rt[i - 1];
		for(int j = 0; j < v[i - 1].size(); j++) 
			tree.update(rt[i], rt[i], 1, n, v[i - 1][j], -1);
	}	
	Q = read(); 
	while(Q--) {
		int q[4], a = read(), e = read(), c = read(), d = read();
		q[0] = (a + las) % n + 1, q[1] = (e + las) % n + 1, q[2]= (c + las) % n + 1, q[3] = (d + las) % n + 1;
		sort(q, q + 4); 
		int l = 1, r = tot, mid, cnt;
		while(l <= r) {
			mid = (l + r) >> 1; cnt = 0; 
			cnt = tree.query_sum(rt[mid], 1, n, q[1], q[2]); 
			cnt += tree.query_suf(rt[mid], 1, n, q[0], q[1] - 1) + tree.query_pre(rt[mid], 1, n, q[2] + 1, q[3]);
			if(cnt >= 0) 
				l = mid + 1, ans = mid;
			else 
				r = mid - 1;
		}
		printf("%lld\n", las = b[ans]);
	} 
}
