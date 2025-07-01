#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0)
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define debug(x) cerr << #x << " = " << x << '\n';
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

pii operator + (const pii &p1, const pii &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pii operator - (const pii &p1, const pii &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }
pll operator + (const pll &p1, const pll &p2) { return make_pair(p1.F + p2.F, p1.S + p2.S); }
pll operator - (const pll &p1, const pll &p2) { return make_pair(p1.F - p2.F, p1.S - p2.S); }

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
    int n, m, k; cin >> n >> m >> k;
    map<int, set<int>> row, col;
    pii s, t; cin >> s.F >> s.S >> t.F >> t.S;
    rep (i, 0, k) {
        int x, y; cin >> x >> y;
        row[x].insert(y);
        col[y].insert(x);
    }
    map<pii, int> mp;
    queue<pii> q;
    q.push(s);
    mp[s] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        auto it = row[x].lower_bound(y);
        if (it != row[x].end()) {
            if (*it != y + 1 && mp.find({x, *it - 1}) == mp.end()) {
                mp[{x, *it - 1}] = mp[{x, y}] + 1;
                q.push({x, *it - 1});
            }
        }
        if (!row[x].empty() && it != row[x].begin()) {
            --it;
            if (*it != y - 1 && mp.find({x, *it + 1}) == mp.end()) {
                mp[{x, *it + 1}] = mp[{x, y}] + 1;
                q.push({x, *it + 1});
            }
        }
        it = col[y].lower_bound(x);
        if (it != col[y].end()) {
            if (*it != y + 1 && mp.find({*it - 1, y}) == mp.end()) {
                mp[{*it - 1, y}] = mp[{x, y}] + 1;
                q.push({*it - 1, y});
            }
        }
        if (!col[y].empty() && it != col[y].begin()) {
            it--;
            if (*it != y - 1 && mp.find({*it + 1, y}) == mp.end()) {
                mp[{*it + 1, y}] = mp[{x, y}] + 1;
                q.push({*it + 1, y});
            }
        }
    }
    if (mp.find(t) == mp.end()) cout << -1 << '\n';
    else cout << mp[t] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}