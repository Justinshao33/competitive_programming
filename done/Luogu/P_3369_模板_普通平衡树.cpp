#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
// #pragma GCC optimize("O3,unroll-loops")
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

struct Treap{
    Treap *l, *r;
    int key, size;
    Treap(int k) : l(nullptr), r(nullptr), key(k), size(1) {}
    void pull();
    void push() {};
};
inline int SZ(Treap *p){
    return p == nullptr ? 0 : p->size;
}
void Treap::pull() {
    size = 1 + SZ(l) + SZ(r);
}
Treap *merge(Treap *a, Treap *b){
    if (!a || !b) return a ? a : b;
    if (rand() % (SZ(a) + SZ(b)) < SZ(a)) {
        return a->push(), a->r = merge(a->r, b), a->pull(), a;
    }
    return b->push(), b->l = merge(a, b->l), b->pull(), b;
}
// <= k, > k
void split(Treap *p, Treap *&a, Treap *&b, int k) { // by key
    if (!p) return a = b = nullptr, void();
    p->push();
    if (p->key <= k) {
        a = p, split(p->r, a->r, b, k), a->pull();
    } else {
        b = p, split(p->l, a, b->l, k), b->pull();
    }
}
// k, n - k
void split2(Treap *p, Treap *&a, Treap *&b, int k) { // by size
    if (!p) return a = b = nullptr, void();
    p->push();
    if (SZ(p->l) + 1 <= k) {
        a = p, split2(p->r, a->r, b, k - SZ(p->l) - 1);
    } else {
        b = p, split2(p->l, a, b->l, k);
    }
    p->pull();
}
void insert(Treap *&p, int k) {
    Treap *l, *r;
    p->push(), split(p, l, r, k);
    p = merge(merge(l, new Treap(k)), r);
    p->pull();
}
bool erase(Treap *&p, int k) {
    if (!p) return false;
    if (p->key == k) {
        Treap *t = p;
        p->push(), p = merge(p->l, p->r);
        delete t;
        return true;
    } 
    Treap *&t = k < p->key ? p->l : p->r;
    return erase(t, k) ? p->pull(), true : false;
}
int Rank(Treap *p, int k) { // # of key < k
    if (!p) return 0;
    if (p->key < k) return SZ(p->l) + 1 + Rank(p->r, k);
    return Rank(p->l, k);
}
Treap *kth(Treap *p, int k) { // 1-base
    if (k <= SZ(p->l)) return kth(p->l, k);
    if (k == SZ(p->l) + 1) return p;
    return kth(p->r, k - SZ(p->l) - 1);
}
// pref: kth(Rank(x)), succ: kth(Rank(x+1)+1)
tuple<Treap*, Treap*, Treap*> interval(Treap *&o, int l, int r) { // 1-based
    Treap *a, *b, *c; // b: [l, r]
    split2(o, a, b, l - 1), split2(b, b, c, r - l + 1);
    return make_tuple(a, b, c);
}

void solve() {
    int q; cin >> q;
    Treap *rt = nullptr;
    while (q--) {
        int t, x; cin >> t >> x;
        if (t == 1) {
            insert(rt, x);
        } else if (t == 2) {
            erase(rt, x);
        } else if (t == 3) {
            cout << Rank(rt, x) + 1 << '\n';
        } else if (t == 4) {
            cout << kth(rt, x)->key << '\n';
        } else if (t == 5) {
            int rk = Rank(rt, x);
            cout << kth(rt, rk)->key << '\n';
        } else {
            int rk = Rank(rt, x + 1);
            cout << kth(rt, rk + 1)->key << '\n';
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