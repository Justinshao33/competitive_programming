#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;

int n, a[15][15], ans = 0, sum = 0;
bool qu[15][15];

bool check(int x, int y) {
    
    return true;
}
 
map<int, int> mp;

void f(int i) {
    if (i == n) return;
    f(i + 1);
    for (int j = 0; j < n; j++) {
        if (check(i, j)) {
            qu[i][j] = true;
            sum += a[i][j];
            ans = max(ans, sum);
            // cout << i << ' ' << j << ' ' << sum << '\n';
            f(i + 1);
            qu[i][j] = false;
            sum -= a[i][j];
        }    
    }
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    f(0);
    cout << ans << '\n';
}

signed main() {
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}