#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define N 210
using namespace std;
inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
	while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, sx, sy, K; int mp[N][N]; char ch[N];
int dp[N][N][N]; //dp[t][i][j] 在时间t位于i行j列答案最值
deque<int>q; int ans = -inf;

int main() {
	n = read(), m = read(), sx = read(), sy = read(), K = read();
	for (int i = 1; i <= n; i++) {
		scanf("%s", ch + 1);
		for (int j = 1; j <= m; j++) {
			if (ch[j] == 'x') mp[i][j] = 1;
			else mp[i][j] = 0;
		}
	}
	memset(dp, -31, sizeof(dp));
	dp[0][sx][sy] = 0; 
	for (int i = 1; i <= K; i++) {
		int s = read(), t = read(), d = read();
		int tim = t - s + 1;
		// cout << tim << " " << d << endl;
		while (!q.empty()) q.pop_back();
		if (d == 1) {
			for (int j = 1; j <= m; j++) {
				while (!q.empty()) q.pop_back();
				dp[i][n][j] = dp[i - 1][n][j];
				if (!mp[n][j]) q.push_back(n);
				for (int k = n - 1; k >= 1; k--) {
					if (mp[k][j]) {
						while (!q.empty()) q.pop_back();
						continue;
					}
					while (!q.empty() and q.front() - k > tim) q.pop_front();
					while (!q.empty() and dp[i - 1][q.back()][j] + q.back() - k <= dp[i - 1][k][j]) q.pop_back();
					q.push_back(k);
					dp[i][k][j] = dp[i - 1][q.front()][j] + q.front() - k;
				}
			}
		} else if (d == 2) {
			for (int j = 1; j <= m; j++) {
				while (!q.empty()) q.pop_back();
				dp[i][1][j] = dp[i - 1][1][j];
				if (!mp[1][j]) q.push_back(1);
				for (int k = 2; k <= n; k++) {
					if (mp[k][j]) {
						while (!q.empty()) q.pop_back();
						continue;
					}
					while (!q.empty() and k - q.front() > tim) q.pop_front();
					while (!q.empty() and dp[i - 1][q.back()][j] + k - q.back() <= dp[i - 1][k][j]) q.pop_back();
					q.push_back(k);
					dp[i][k][j] = dp[i - 1][q.front()][j] + k - q.front();
				}
			}
		} else if (d == 3) {
			for (int j = 1; j <= n; j++) {
				while (!q.empty()) q.pop_back();
				dp[i][j][m] = dp[i - 1][j][m];
				if (!mp[j][m]) q.push_back(m);
				for (int k = m - 1; k >= 1; k--) {
					if (mp[j][k]) {
						while (!q.empty()) q.pop_back();
						continue;
					}
					while (!q.empty() and q.front() - k > tim) q.pop_front();
					while (!q.empty() and dp[i - 1][j][q.back()] + q.back() - k <= dp[i - 1][j][k]) q.pop_back();
					q.push_back(k);
					dp[i][j][k] = dp[i - 1][j][q.front()] + q.front() - k;
				}
			}
		} else if (d == 4) {
			for (int j = 1; j <= n; j++) {
				while (!q.empty()) q.pop_back();
				dp[i][j][1] = dp[i - 1][j][1];
				if (!mp[j][1]) q.push_back(1);
				for (int k = 2; k <= m; k++) {
					if (mp[j][k]) {
						while (!q.empty()) q.pop_back();
						continue;
					}
					while (!q.empty() and k - q.front() > tim) q.pop_front();
					while (!q.empty() and dp[i - 1][j][q.back()] + k - q.back() <= dp[i - 1][j][k]) q.pop_back();
					q.push_back(k);
					dp[i][j][k] = dp[i - 1][j][q.front()] + k - q.front();
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) 
			ans = max(ans, dp[K][i][j]);
	printf("%d", ans);
	// system("pause");
}
