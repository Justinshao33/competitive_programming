#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.fi + p2.fi, p1.se + p2.se); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.fi - p2.fi, p1.se - p2.se); }

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
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

void solve() {
    int n, k, b; cin >> n >> k >> b;
    if (k % 2 == 1) {
        cout << "No\n";
    } else if (n == 1) {
        if (k == 1) cout << "No\n";
        else cout << "Yes\n0\n";
    } else if (n == 2) {
        if (k == 2) {
            if (b == 0) {
                cout << "No\n";
            } else {
                cout << "Yes\n";
                cout << "1\n1 2\n";
            }
        } else {
            cout << "No\n";
        }
    } else if (k == 0) {
        if (b == 0) {
            cout << "Yes\n";
            cout << n << '\n';
            rep (i, 1, n + 1) cout << i << ' ' << i % n + 1 << '\n';
        } else {
            cout << "No\n";
        }
    } else if (b == 0) {
        if (n == 3) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            cout << n + k / 2 << '\n';
            rep (i, 1, n + 1) cout << i << ' ' << i % n + 1 << '\n';
            rep (i, 1, n / 2 + 1) {
                if (k > 0) {
                    cout << i << ' ' << n / 2 + i << '\n';
                    k -= 2;
                }
            }
            assert(k == 0);
        }
    } else if (b == n - 1) {
        cout << "Yes\n";
        cout << n - 1 << '\n';
        rep (i, 2, n + 1) {
            if (k > 0) {
                cout << 1 << ' ' << i << '\n';
                if (i & 1 ^ 1) k -= 2;
            } else {
                cout << i - 1 << ' ' << i << '\n';
            }
        }
        assert(k == 0);
    } else if (b == n - 2) {
        cout << "No\n";
    } else if (n == 4 && k == 4 && b == 1) {
        cout << "No\n";
    } else if (n - b - b == 2 && k == n) {
        cout << "Yes\n";
        int C = n - b;
        vector<pii> edge;
        rep (i, 1, C + 1) edge.push_back({i, i % C + 1});
        edge.push_back({1, C + 1});
        rep (i, C + 2, n + 1) edge.push_back({i - C + 1, i});
        if (n != 4) edge.push_back({2, C});
        cout << ssize(edge) << '\n';
        for (const auto &[x, y] : edge) cout << x << ' ' << y << '\n';
    } else {
        cout << "Yes\n";
        int C = n - b;
        vector<pii> edge;
        int cnt = 0;
        rep (i, 1, C + 1) edge.push_back({i, i % C + 1});
        vector<int> deg(n + 1, 0);
        for (int i = C + 1, ptr = 1; i <= n; i++) {
            if (k > 0) {
                if (ptr > C) {
                    edge.push_back({i, 1});
                    deg[1]++;
                    if (cnt & 1) k -= 2;
                    cnt++;
                } else {
                    edge.push_back({i, ptr});
                    deg[ptr]++;
                    ptr++;
                    k -= 2;
                }
            } else {
                edge.push_back({i - 1, i});
            }
        }
        if (k > 0) {
            vector<int> cyc;
            rep (i, 1, C + 1) if (deg[i] % 2 == 0) {
                cyc.push_back(i);
            } 
            for (int i = 0, ptr = (ssize(cyc) + 1) / 2; i < ssize(cyc) / 2; i++) {
                if (k > 0) {
                    edge.push_back({cyc[i], cyc[ptr]});
                    k -= 2;
                    ptr++;
                }
            }
        }
        cout << ssize(edge) << '\n';
        for (const auto &[x, y] : edge) cout << x << ' ' << y << '\n';
        assert(k == 0);
    }
}

int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }
}