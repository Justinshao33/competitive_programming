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
 
const int MAXN = 1e6 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow (ll x, ll exp, ll mod = LLONG_MAX) { if (x == 0) return 0; ll res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

template <typename T>
struct FenwickTree{
    vector<T> BIT;
    FenwickTree(int n) : BIT(n + 1, 0) {}

    void mod(int x, T val) {
        while(x < BIT.size()){
            BIT[x] += val;
            x += x & -x;
        }
    }

    T query(int x) {
        T res = 0;
        while (x > 0) {
            res += BIT[x];
            x -= x & -x;
        }
        return res;
    }

    T query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n, q; cin >> n >> q;
    map<int, ll> odt;
    odt[1] = 1, odt[n + 1] = -1;
    FenwickTree<ll> bit(n);
    vector<ll> add(n + 1, 0);
    auto split = [&](const int &x) -> void {
        const auto it = prev(odt.upper_bound(x));
        odt[x] = it->second;
    };
    while (q--) {
        string s; cin >> s;
        if (s[0] == 'C') {
            int l, r, c; cin >> l >> r >> c;
            split(l);
            split(r + 1);
            auto itl = odt.lower_bound(l), itr = odt.lower_bound(r + 1);
            for (; itl != itr; itl = odt.erase(itl)) {
                int L = itl->first, R = next(itl)->first;
                bit.mod(L, add[itl->second]);               
                bit.mod(R, -add[itl->second]);
            }
            odt[l] = c;
            bit.mod(l, -add[c]);
            bit.mod(r + 1, add[c]);
        } else if (s[0] == 'A') {
            int c, x; cin >> c >> x;
            add[c] += x;
        } else {
            int x; cin >> x;
            split(x);
            cout << bit.query(x) + add[odt[x]] << '\n';
        }
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