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
    int n; cin >> n;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i], a[i]--;
    vector pre(n, vector<ll>(B + 1, 0));
    vector cnt(B + 1, vector<ll>(B + 1, 0)); // same pair
    vector<int> bel(n);
    rep (i, 0, n) bel[i] = i / B;
    rep (i, 0, n) pre[a[i]][bel[i]]++;
    rep (i, 0, n) rep (j, 1, B + 1) pre[i][j] += pre[i][j - 1];
    {
        vector<ll> val(n, 0);
        rep (i, 0, B + 1) {
            rep (j, i, B + 1) {
                if (j) cnt[i][j] = cnt[i][j - 1];
                rep (k, j * B, min(n, (j + 1) * B)) {
                    cnt[i][j] += val[a[k]];
                    val[a[k]]++;
                }
            }
            rep (j, 0, n) val[j] = 0;
        }
    }
    
    auto get = [&](int x, int l, int r) -> ll {
        if (l > r) return 0;
        return pre[x][r] - (l - 1 < 0 ? 0 : pre[x][l - 1]);
    };
    
    vector Ldif(B + 2, vector<ll>(B + 2, 0));
    vector Rdif(B + 2, vector<ll>(B + 2, 0));

    auto mod = [&](int p, int x, int v) -> void {
        int bl = p / B;
        if (v < 0) {
            { // pre
                for (int cur = bl; cur <= B; cur++) {
                    pre[x][cur] += v;
                }
            }
            { // cnt
                // cnt[i][j]{i <= bl <= j} := cnt[i][j] + calc(i, bl) + calc(bl + 1, j);
                rep (i, 0, bl + 1) {
                    Rdif[i][bl] += v * get(x, i, bl);
                }
                rep (j, bl + 1, B + 1) {
                    Ldif[bl][j] += v * get(x, bl + 1, j);
                }
            }
        } else {
            { // cnt
                // cnt[i][j]{i <= bl <= j} := cnt[i][j] + calc(i, bl) + calc(bl + 1, j);
                rep (i, 0, bl + 1) {
                    Rdif[i][bl] += v * get(x, i, bl);
                }
                rep (j, bl + 1, B + 1) {
                    Ldif[bl][j] += v * get(x, bl + 1, j);
                }
            }
            { // pre
                for (int cur = bl; cur <= B; cur++) {
                    pre[x][cur] += v;
                }
            }
        }
    };
    
    vector<ll> val(n, 0);
    auto que = [&](int l, int r) -> ll {
        ll L = bel[l], R = bel[r], res = 1LL * (r - l + 1) * ((r - l + 1) - 1) / 2;
        if (L == R) {
            for (int cur = l; cur <= r; cur++) {
                res -= val[a[cur]];
                val[a[cur]]++;
            }
            for (int cur = l; cur <= r; cur++) {
                val[a[cur]] = 0;
            }
            return res;
        }
        res -= cnt[L + 1][R - 1];
        for (int cur = L + 1; cur <= R - 1; cur++) {
            res -= Rdif[L + 1][cur];
            res -= Ldif[cur][R - 1];
        }
        for (int cur = l; bel[cur] == L; cur++) {
            res -= val[a[cur]];
            res -= get(a[cur], L + 1, R - 1);
            val[a[cur]]++;
        }
        for (int cur = R * B; cur <= r; cur++) {
            res -= val[a[cur]];
            res -= get(a[cur], L + 1, R - 1);
            val[a[cur]]++;
        }
        for (int cur = l; bel[cur] == L; cur++) {
            val[a[cur]] = 0;   
        }
        for (int cur = R * B; cur <= r; cur++) {
            val[a[cur]] = 0;
        }
        return res;
    };
    
    int q; cin >> q;
    ll last = 0;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            ll p, x; cin >> p >> x;
            p = (p + last) % n, x = (x + last) % n;
            mod(p, a[p], -1);
            a[p] = x;
            mod(p, a[p], 1);
        } else {
            ll l, r; cin >> l >> r;
            l = (l + last) % n, r = (r + last) % n;
            if (l > r) swap(l, r);
            ll ans = que(l, r);            
            cout << ans << ' ';
            last = ans;
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