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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Treap {
    Treap *l, *r;
    int size, pri;
    int val = 0;
    Treap(int v) : l(nullptr), r(nullptr), size(1), pri(rand()), val(v) {}
    void pull();
};

inline int sz(Treap *p) {
    return (p == nullptr ? 0 : p->size);
}

void Treap::pull() {
    size = sz(l) + 1 + sz(r);
}

Treap *merge(Treap *a, Treap *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (a->pri < b->pri) {
        a->r = merge(a->r, b);
        a->pull();
        return a;
    } else {
        b->l = merge(a, b->l);
        b->pull();
        return b;
    }
}
 
void split(Treap *root, Treap *&a, Treap *&b, int k) {
    if (root == nullptr) {
        a = b = nullptr;
        return;
    }
    if (sz(root->l) < k) {
        a = root;
        split(root->r, a->r, b, k - sz(root->l) - 1);
        a->pull();
    } else {
        b = root;
        split(root->l, a, b->l, k);
        b->pull();
    }
}

void solve() {
    int n; cin >> n;
    Treap *root = nullptr;
    rep (i, 1, n + 1) {
        int p; cin >> p;
        if (i == 1) {
            root = new Treap(i);
        } else {
            Treap *a, *b;
            split(root, a, b, p - 1);
            root = merge(a, merge(new Treap(i), b));
        }
    }
    function<void(Treap*)> dfs = [&](Treap *p) -> void {
        if (p == nullptr) return;
        dfs(p->l);
        cout << p->val << ' ';
        dfs(p->r);
    };
    dfs(root);
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}