#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <streambuf>
#include <string>
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
#define ld long double
#define F first
#define S second

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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Treap {
    int val, mi;
    Treap *l, *r;
    int size, pri, rev, add;
    Treap(int inp) : val(inp), mi(inp), l(NULL), r(NULL), size(1), pri(rand()), rev(0), add(0) {}
    void pull();
    void update(int, int);
}*root = NULL;
 
inline int Min(Treap *p) {
    return p == NULL ? IINF : p->mi;
}
 
inline int sz(Treap *p) {
    return p == NULL ? 0 : p->size;
}
 
void Treap::pull() {
    size = sz(l) + sz(r) + 1;
    mi = min(val, min(Min(l), Min(r)));
}

void Treap::update(int re, int ad) {
    val += ad;
    add += ad;
    mi += ad;
    rev ^= re;
}

void push(Treap *p) {
    if (p->l) p->l->update(p->rev, p->add);
    if (p->r) p->r->update(p->rev, p->add);
    p->add = 0;
    if (p->rev) {
        p->rev = 0;
        swap(p->l, p->r);
    } 
}
 
Treap *merge(Treap *a, Treap *b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
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
    if (root == NULL) {
        a = b = NULL;
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

void ADD() {
    int x, y, D; cin >> x >> y >> D;
    Treap *a, *b, *c;
    split(root, a, b, x - 1);
    split(b, b, c, y - x + 1);
    b->update(0, D);
    root = merge(a, merge(b, c));
}

void REV() {
    int x, y; cin >> x >> y;
    Treap *a, *b, *c;
    split(root, a, b, x - 1);
    split(b, b, c, y - x + 1);
    b->update(1, 0);
    root = merge(a, merge(b, c));
}

void REVO() {
    int x, y, T; cin >> x >> y >> T;
    T %= y - x + 1;
    Treap *a, *b, *c, *d;
    split(root, a, b, x - 1);
    split(b, b, d, y - x + 1);
    split(b, b, c, y - x + 1 - T);
    root = merge(merge(a, c), merge(b, d));
}

void INS() {
    int x, y; cin >> x >> y;
    Treap *a, *b;
    split(root, a, b, x);
    root = merge(a, merge(new Treap(y), b));
}

void DEL() {
    int x; cin >> x;
    Treap *a, *b, *c;
    split(root, a, b, x - 1);
    split(b, b, c, 1);
    root = merge(a, c);
} 

int MIN() {
    int x, y; cin >> x >> y;
    Treap *a, *b, *c;
    split(root, a, b, x - 1);
    split(b, b, c, y - x + 1);
    int ans = b->mi;
    root = merge(a, merge(b, c));
    return ans;
}

void solve() {
    int n; cin >> n;
    rep (i, 0, n) {
        int a; cin >> a;
        root = merge(root, new Treap(a));
    }
    int q; cin >> q;
    while (q--) {
        string s; cin >> s;
        if (s == "ADD") ADD();
        if (s == "REVERSE") REV();
        if (s == "REVOLVE") REVO();
        if (s == "INSERT") INS();
        if (s == "DELETE") DEL();
        if (s == "MIN") cout << MIN() << '\n';
    }
}
 
int main() {
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}