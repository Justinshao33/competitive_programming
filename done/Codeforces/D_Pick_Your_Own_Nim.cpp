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
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    rep (i, 0, n) cin >> a[i];
    int m; cin >> m;
    vector<pll> stone; // val, col
    int tot = 0;
    rep (i, 0, m) {
        int k; cin >> k;
        rep (j, 0, k) {
            ll b; cin >> b;
            stone.pb({b, i});
        }
        tot += k;
    }
    /*
    M1 = linear matroid
    M2 = color matroid
    y<-s if I+y   satisfies M1
    y->t if I+y   satisfies M2
    x<-y if I-x+y satisfies M2
    x->y if I-x+y satisfies M1
    */
    set<int> I, nI;
    rep (i, 0, tot) nI.insert(i);
    vector<ll> basis_a(60, -1);
    rep (i, 0, n) {
        for (int j = 59; j >= 0; --j) if (a[i] >> j & 1) {
            if (basis_a[j] == -1) {
                basis_a[j] = a[i];
                break;
            }
            a[i] ^= basis_a[j];
        }
        if (a[i] == 0) {
            cout << -1 << '\n';
            return;
        }
    }
    while (true) {
        vector<vector<int>> adj(tot + 2);
        int s = tot, t = s + 1;
        auto M1 = [&]() -> void {
            {
                auto basis = basis_a;
                for (int i : I) {
                    ll val = stone[i].fi;
                    for (int j = 59; j >= 0; --j) if (val >> j & 1) {
                        if (basis[j] == -1) {
                            basis[j] = val;
                            break;
                        }
                        val ^= basis[j];
                    }
                    assert(val != 0);
                }
                for (int i : nI) {
                    ll val = stone[i].fi;
                    for (int j = 59; j >= 0; --j) if (val >> j & 1) {
                        if (basis[j] == -1) {
                            adj[s].pb(i);
                            break;
                        }
                        val ^= basis[j];
                    }
                }
            }
            {
                for (int i : I) {
                    auto basis = basis_a;
                    for (int ii : I) if (ii != i) {
                        ll val = stone[ii].fi;
                        for (int j = 59; j >= 0; --j) if (val >> j & 1) {
                            if (basis[j] == -1) {
                                basis[j] = val;
                                break;
                            }
                            val ^= basis[j];
                        }
                    }
                    for (int j : nI) {
                        ll val = stone[j].fi;
                        for (int k = 59; k >= 0; --k) if (val >> k & 1) {
                            if (basis[k] == -1) {
                                adj[i].pb(j);
                                break;
                            }
                            val ^= basis[k];
                        }
                    }
                }
            }
        };
        auto M2 = [&]() -> void {
            vector<bool> col(m, 0);
            for (int i : I) {
                assert(col[stone[i].se] == false);
                col[stone[i].se] = 1;
            }
            for (int j : nI) {
                if (!col[stone[j].se]) adj[j].pb(t);
                for (int i : I) {
                    if (!col[stone[j].se] || (stone[i].se == stone[j].se)) {
                        adj[j].pb(i);
                    }
                }
            }
        };
        auto augment = [&]() -> bool {
            vector<int> vis(tot + 2, 0), who(tot + 2, -1);
            queue<int> q;
            vis[s] = 1;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (!vis[v]) {
                        who[v] = u;
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
            if (!vis[t]) return false;
            int sz = I.size();
            for (int cur = who[t];; cur = who[cur]) {
                if (cur == -1 || cur == s) break;
                if (I.find(cur) != I.end()) {
                    nI.insert(cur);
                    I.erase(cur);
                } else {
                    I.insert(cur);
                    nI.erase(cur);
                }
            }
            assert(I.size() == sz + 1);
            return true;
        };
        M1();
        M2();
        if (!augment()) break;
    }
    if (I.size() != m) {
        cout << -1 << '\n';
    } else {
        for (int x : I) {
            cout << stone[x].fi << '\n';
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