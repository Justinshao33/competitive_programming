#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }
 
void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> pt;
    rep (i, 0, n) {
        int x, y; cin >> x >> y;
        pt.push_back({x, y, -1});
    }
    rep (i, 0, m) {
        int x, y; cin >> x >> y;
        pt.push_back({x, y, i});
    }
    vector<int> dis(m, IINF);
    rep (k, 0, 8) {
        sort(all(pt));
        map<int, int> Yaxis;
        for (auto [x, y, t] : pt) {
            if (t == -1) {
                auto it = Yaxis.lower_bound(y);
                while (it != Yaxis.end()) {
                    // X - x + Y - y < X - px + Y - py
                    // px + py < x + y
                    if (x + y > it->fi + it->se) {
                        it = Yaxis.erase(it);
                    } else {
                        break;
                    }
                }
                Yaxis[y] = x;
            } else {
                auto it = Yaxis.upper_bound(y);
                if (it != Yaxis.begin()) {
                    it = prev(it);    
                    chmin(dis[t], abs(x - it->se) + abs(y - it->fi));
                }
            }
        }
        for (auto &[x, y, t] : pt) {
            if (k & 1) {
                x = -x;
            } else {
                swap(x, y);
            }
        }
    }
    cout << *max_element(all(dis)) << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}
