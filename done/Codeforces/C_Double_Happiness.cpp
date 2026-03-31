#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
 
#define rep(a, b, c) for (int a = b; a < c; a++)
 
const int C = 3e8 + 5;

bitset<C> isp; 
int prime[C / 30 * 2], ptr;

inline void sieve() {
    rep (i, 2, C) {
        if (!isp[i]) {
            prime[ptr++] = i;
        }
        rep (j, 0, ptr) {
            if (i * prime[j] >= C) break;
            isp[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

void solve() {
    sieve();
    int l, r; cin >> l >> r;
    int ans = l <= 2 && r >= 2;
    while (l < 3 || l % 4 != 1) l++;
    for (; l <= r; l += 4) ans += !isp[l];
    cout << ans << '\n';
}
 
signed main() {
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}