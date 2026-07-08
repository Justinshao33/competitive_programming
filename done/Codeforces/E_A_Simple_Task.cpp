#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
using pld = pair<ld, ld>;
#define fi first
#define se second

#ifdef LOCAL
#define ZTMYACANESOCUTE // freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 2e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    map<int, char> odt;
    rep (i, 1, n + 1) odt[i] = s[i - 1] - 'a';
    odt[n + 1] = ' ';
    // initialize edges odt[1] and odt[n + 1] 1-base
    auto split = [&](const int &x) -> void {
        const auto it = prev(odt.upper_bound(x));
        odt[x] = it->second;
    };
    auto merge = [&](const int &l, const int &r, int t) -> void {
        split(l), split(r + 1);
        auto itl = odt.lower_bound(l), itr = odt.lower_bound(r + 1);
        vector<int> cnt(26, 0);
        for (; itl != itr; itl = odt.erase(itl)) {
            // do something
            cnt[itl->se] += next(itl)->fi - itl->fi;
        }
        // assign value to odt[l]
        int ptr = l;
        if (t == 1) {
            rep (i, 0, 26) if (cnt[i]) {
                odt[ptr] = i;
                ptr += cnt[i];
            }
        } else {
            for (int i = 25; i >= 0; --i) if (cnt[i]) {
                odt[ptr] = i;
                ptr += cnt[i];
            }
        } 
    };
    while (q--) {
        int l, r, t; cin >> l >> r >> t;
        merge(l, r, t);
    }
    for (auto it = odt.begin(); it->fi != n + 1; it = odt.erase(it)) {
        int cnt = next(it)->fi - it->fi;
        cout << string(cnt, 'a' + it->se);
    }
    cout << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}