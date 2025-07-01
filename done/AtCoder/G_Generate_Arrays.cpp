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
    int n; cin >> n;
    vector<int> a(n), id(n);
    rep (i, 0, n) {
        cin >> a[i], a[i]--;
        id[a[i]] = i;
    }
    int q; cin >> q;
    vector<set<int>> val(q + 1), pos(q + 1);
    rep (i, 0, n) {
        val[0].insert(a[i]);
        pos[0].insert(id[a[i]]);
    }
    rep (i, 1, q + 1) {
        int t, s, x; cin >> t >> s >> x;
        auto work = [&](int st, int v, int p) -> void {
            val[i].insert(v);
            pos[i].insert(p);
            val[st].erase(v);
            pos[st].erase(p);
        };
        if (t == 1) {
            if (2 * x >= (int)pos[s].size()) {
                int cur = pos[s].size();
                if (cur > x) {
                    auto it = prev(pos[s].end());
                    while (cur > x) {
                        auto nxt = prev(it);
                        work(s, a[*it], *it);
                        it = nxt;
                        cur--;
                    }
                }
            } else {
                int cur = 0;
                auto it = pos[s].begin();
                while (cur < x) {
                    auto nxt = next(it);
                    work(s, a[*it], *it);
                    it = nxt;
                    cur++;
                }
                swap(val[s], val[i]);
                swap(pos[s], pos[i]);
            }
        } else {
            x--;
            auto L = val[s].upper_bound(x), R = L;
            while (L != val[s].begin() && R != val[s].end()) L--, R++;
            if (L == val[s].begin()) {
                auto it = val[s].upper_bound(x);
                if (it != val[s].begin()) {
                    it = prev(it);
                    while (it != val[s].begin()) {
                        auto nxt = prev(it);
                        work(s, *it, id[*it]);
                        it = nxt;
                    }
                    work(s, *it, id[*it]);
                }
                swap(val[s], val[i]);
                swap(pos[s], pos[i]);
            } else {
                auto it = val[s].upper_bound(x);
                while (it != val[s].end()) {
                    auto nxt = next(it);
                    work(s, *it, id[*it]);
                    it = nxt;
                }
            }
        }
        cout << val[i].size() << '\n';
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