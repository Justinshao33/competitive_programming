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

const int C = 1e6 + 5;

int mo[C], lp[C], phi[C], isp[C]; 
vector<int> prime;

void sieve() {
    mo[1] = phi[1] = 1;
    rep (i, 1, C) lp[i] = 1;
    rep (i, 2, C) {
        if (lp[i] == 1) {
            lp[i] = i;
            prime.pb(i);
            isp[i] = 1;
            mo[i] = -1;
            phi[i] = i - 1;
        }
        for (int p : prime) {
            if (i * p >= C) break;
            lp[i * p] = p;
            if (i % p == 0) {
                phi[p * i] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
            mo[i * p] = mo[i] * mo[p];
        }
    }
}

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    vector<vector<int>> div(m + 1);
    rep (i, 1, m + 1) for (int j = i; j <= m; j += i) div[j].pb(i);
    auto calc = [&]() -> vector<int> {
        vector<int> v(m + 1), val(n, 0);
        rep (i, 0, n) v[a[i]]++;
        vector<int> f(m + 1, 0);
        rep (i, 1, m + 1) for (int j = i; j <= m; j += i) {
            f[i] += v[j];
        }
        rep (i, 0, n) {
            if (a[i] == 0) continue;
            for (int d : div[a[i]]) {
                val[i] += mo[d] * f[d];
            }
        }
        return val;
    };
    auto val = calc();
    vector<int> ans(4, -1);
    ans[0] = max_element(all(val)) - val.begin();
    if (val[ans[0]] == 0) {
        cout << 0 << '\n';
        return;
    }
    rep (i, 0, n) if (i != ans[0] && gcd(a[i], a[ans[0]]) == 1) {
        if (ans[1] == -1 || val[ans[1]] > val[i]) ans[1] = i; 
    }
    a[ans[0]] = a[ans[1]] = 0;
    val = calc();
    ans[2] = max_element(all(val)) - val.begin();
    if (val[ans[2]] == 0) {
        cout << 0 << '\n';
        return;
    }
    rep (i, 0, n) if (a[i] != 0 && i != ans[2] && gcd(a[i], a[ans[2]]) == 1) {
        ans[3] = i;
        break;
    }
    rep (i, 0, 4) cout << ans[i] + 1 << " \n" [i == 3];
}

 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    cin >> T;
    sieve();
    while (T--) {
        solve();
    }
}