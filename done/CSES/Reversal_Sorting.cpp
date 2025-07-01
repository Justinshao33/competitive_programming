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

struct Treap {
    int val, mi;
    Treap *l, *r;
    int size, pri, tag;
    Treap(int inp) : val(inp), mi(inp), l(nullptr), r(nullptr), size(1), pri(rand()), tag(0) {}
    void pull();
};
 
inline int Min(Treap *&p) {
    return p == nullptr ? IINF : p->mi;
}
 
inline int sz(Treap *&p) {
    return p == nullptr ? 0 : p->size;
}
 
void Treap::pull() {
    size = sz(l) + sz(r) + 1;
    mi = min({val, Min(l), Min(r)});
}
 
void push(Treap *p) {
    if (p->l) p->l->tag ^= p->tag;
    if (p->r) p->r->tag ^= p->tag;
    if (p->tag) {
        p->tag = 0;
        swap(p->l, p->r);
    }
}
 
Treap *merge(Treap *a, Treap *b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    push(a);
    push(b);
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
    push(root);
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

int query(Treap *p, int k) {
    if (p == nullptr) return 0;
    push(p);
    if (p->val == k) return sz(p->l) + 1;
    if (Min(p->l) == k) return query(p->l, k);
    else return sz(p->l) + query(p->r, k) + 1;
}

void solve() {
    int n; cin >> n;
    Treap *root = nullptr;
    rep (i, 0, n) {
        int a; cin >> a;
        root = merge(root, new Treap(a));
    }
    vector<pii> ope;
    rep (i, 1, n + 1) {
        Treap *a, *b, *c = nullptr;
        split(root, a, b, i - 1);
        int pos = query(b, i) + i - 1;
        // cerr << pos << '\n';
        if (pos != i) {
            ope.pb({i, pos});
            split(b, b, c, pos - i + 1);
            b->tag ^= 1;
        }
        root = merge(a, merge(b, c));
    }
    cout << ope.size() << '\n';
    for (auto [a, b] : ope) cout << a << ' ' << b << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}