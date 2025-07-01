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

struct FenwickTree{
    vector<ll> BIT;
    FenwickTree(int n) : BIT(n + 1, 0) {}

    void mod(int x, ll val) {
        while(x <= BIT.size()){
            BIT[x] += val;
            x += x & -x;
        }
    }

    ll query(int x) {
        ll res = 0;
        while (x) {
            res += BIT[x];
            x -= x & -x;
        }
        return res;
    }

    ll rquery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

struct info {
    int l, r, k, id;
};

template<typename T>inline void read(T &x) {
    x = 0;
    static int p; p = 1;
    static char c; c = getchar();
    while (!isdigit(c)) { if (c == '-') p = -1; c = getchar();}
    while (isdigit(c)) { x = (x << 1) + (x << 3) + (c - 48); c = getchar();}
    x *= p;
}

int a[1 << 16];

void solve() {
    int n, q; read(n), read(q);
    vector<int> a(n + 1);
    vector<info> que;
    rep (i, 1, n + 1) {
        read(a[i]);
        que.pb({i, 1, a[i], -1});
    }
    int cnt = n + q - 1;
    vector<int> ans(q, -1);
    rep (i, 0, q) {
        int t; read(t);
        if (t == 1) {
            int l, r, k; read(l), read(r), read(k);
            que.pb({l, r, k, i});
        } else if (t == 2) {
            int c, v; read(c), read(v);
            que.pb({c, -1, a[c], -1});
            a[c] = v;
            que.pb({c, 1, a[c], -1});
            cnt++;
        } else {
            int x, v; read(x), read(v);
            ans[i] = 7122;
            cnt--;
        }
    }
    FenwickTree bit(n);
    vector<info> q1, q2;
    auto solve = [&](auto self, ll l, ll r, int ql, int qr) -> void {
        if (ql > qr || l > r) return;
        if (l == r) {
            rep (i, ql, qr + 1) if (que[i].id != -1) {
                ans[que[i].id] = l;
            }
            return;
        }
        ll mid = l + r >> 1;
        rep (i, ql, qr + 1) {
            if (que[i].id != -1) {
                int cur = bit.rquery(que[i].l, que[i].r);
                if (cur >= que[i].k) q1.pb(que[i]);
                else {
                    que[i].k -= cur;
                    q2.pb(que[i]);
                }
            } else {
                if (que[i].k <= mid) {
                    bit.mod(que[i].l, que[i].r);
                    q1.pb(que[i]);
                } else {
                    q2.pb(que[i]);
                }
            }
        }
        rep (i, ql, qr + 1) if (que[i].id == -1 && que[i].k <= mid) {
            bit.mod(que[i].l, -que[i].r);
        }
        int sz = q1.size();
        rep (i, 0, sz) que[ql + i] = q1[i];
        rep (i, 0, q2.size()) que[ql + sz + i] = q2[i];
        q1.clear();
        q2.clear();
        self(self, l, mid, ql, ql + sz - 1);
        self(self, mid + 1, r, ql + sz, qr);
    };
    solve(solve, 0, INT_MAX, 0, cnt);
    rep (i, 0, q) if (ans[i] != -1) cout << ans[i] << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    read(T);
    while (T--) {
        solve();
    }
}