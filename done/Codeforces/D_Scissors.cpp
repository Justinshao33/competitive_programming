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

struct zvalue {
    vector<int> z;
    int operator[] (const int &x) const {
        return z[x];
    }
    zvalue(string s) {
        int n = s.size();
        z.resize(n);
        z[0] = 0;
        int l = 1, r = 0;
        rep (i, 1, n) {
            z[i] = min(z[i - l], max<int>(0, r - i));
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
    }
};

void out(int x, int y) {
    cout << "Yes\n";
    cout << x + 1 << ' ' << y + 1 << '\n';
}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    string s, t; cin >> s >> t; 
    vector<int> z, z2;
    {
        string ss = t + "#" + s;
        z = zvalue(ss).z;
        reverse(all(t));
        reverse(all(s));
        ss = t + "#" + s;
        z2 = zvalue(ss).z;
    }
    rep (i, 0, n) {
        if (z[i + m + 1] == m) {
            int r = min(max(i + m - 1, 2 * k - 1), n - 1);
            return out(r - k - k + 1, r - k + 1);
        }
    }
    vector<int> L(m + 1, n), R(m + 1, -1);
    L[0] = 0, R[0] = n - k;
    vector<vector<pii>> eve(m + 1);
    rep (i, m + 1, n + 1 + m) {
        chmin(L[z[i]], i - 1 - m);
        if (n - (i - 1 - m) - 1 - z2[i] + 1 <= n - k) {
            eve[z2[i]].push_back({n - (i - 1 - m) - 1, 1});
            if (n - (i - 1 - m) - (n - k) - 1 >= 0) eve[n - (i - 1 - m) - (n - k) - 1].push_back({n - (i - 1 - m) - 1, -1});
        }
    }
    multiset<int> mst;
    for (int i = m; i >= 0; --i) {
        if (i + 1 <= m) chmin(L[i], L[i + 1]);
        for (auto [x, t] : eve[i]) {
            if (t == 1) {
                mst.insert(x);
            } else {
                mst.extract(x);
            }
        }
        if (!mst.empty()) R[i] = *mst.rbegin();
    }
    rep (i, 0, min(k, m) + 1) {
        if (m - i > k) continue;
        if (L[i] == n || R[m - i] == -1) continue;
        if (L[i] - (k - i) >= 0 && L[i] + i <= R[m - i] - (m - i) + 1) {
            cout << "Yes\n";
            cout << L[i] - (k - i) + 1 << ' ' << R[m - i] - (m - i) + 1 + 1 << '\n'; 
            return;
        }
    }
    cout << "No\n";
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}