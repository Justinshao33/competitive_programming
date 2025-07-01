#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct Manacher {
    string s;
    vector<int> p; // radius of palindromes
    int operator[] (const int &x) const {
        return p[x];
    };
    Manacher(string _s) {
        s = "$";
        for (char &c : _s) s += string(1, c) + "$";
        int n = s.size();
        p.resize(n);
        p[0] = 0;
        int rmx = 0;
        rep (i, 1, n) {
            if (i > rmx + p[rmx]) {
                p[i] = 0;
                int l = i - p[i], r = i + p[i];
                while (l - 1 >= 0 && r + 1 < n && s[l - 1] == s[r + 1]) {
                    l--, r++, p[i]++;
                }
                rmx = i;
            } else {
                int j = rmx - (i - rmx);
                if (j - p[j] > rmx - p[rmx]) p[i] = p[j];
                else if (j - p[j] < rmx - p[rmx]) p[i] = j - (rmx - p[rmx]);
                else {
                    p[i] = p[j];
                    int l = i - p[i], r = i + p[i];
                    while (l - 1 >= 0 && r + 1 < n && s[l - 1] == s[r + 1]) {
                        l--, r++, p[i]++;
                    }
                    if (i + p[i] > rmx + p[rmx]) rmx = i;
                }
            }
        }
    }
};

void solve() {
    string s; cin >> s;
    auto ma = Manacher(s);
    deque<int> dq;
    // cout << ma.p;
    rep (i, 0, ssize(ma.p)) {
        while (!dq.empty() && dq.front() + ma[dq.front()] < i) dq.pop_front();  
        dq.pb(i);
        // cout << dq.front() << ' ';
        if (i & 1) cout << i - dq.front() + 1 << ' ';
        while (!dq.empty() && ma[dq.back()] < ma[i]) dq.pop_back();
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}