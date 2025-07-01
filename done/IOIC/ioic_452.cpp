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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct Treap{
    Treap *l, *r;
    int key, pri, size;
    int mx, v;
    Treap(int k, int val) : l(nullptr), r(nullptr), key(k), pri(get_rand(1, IINF)), size(1), mx(val), v(val) {}
    void pull();
} *root[MAXN];

inline int Max(Treap *root) {
    return root == nullptr ? 0 : root->mx;
}

inline int size(Treap *root){
    return root == nullptr ? 0 : root->size;
}

void Treap::pull(){
    size = 1;
    int tmp = max(Max(l), Max(r));
    if(l != nullptr) size += l->size;
    if(r != nullptr) size += r->size;
    mx = max(v, tmp);
}

Treap *merge(Treap *a, Treap *b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(a->pri < b->pri){
        a->r = merge(a->r, b);
        a->pull();
        return a;
    }
    else{
        b->l = merge(a, b->l);
        b->pull();
        return b;
    }
}

void split(Treap *root, Treap *&a, Treap *&b, int k){
    if(root == nullptr){
        a = b = nullptr;
        return;
    }
    if(root->key < k){
        a = root;
        split(root->r, a->r, b, k);
        a->pull();
    }
    else{
        b = root;
        split(root->l, a, b->l, k);
        b->pull();
    }
}

void insert(Treap *&root, int k, int val){
    Treap *a, *b, *c;
    split(root, a, b, k);
    split(b, b, c, k + 1);
    if (b != nullptr) {
        b->v = max(b->v, val);
        b->mx = b->v;
        root = merge(a, merge(b, c));
        return;
    }
    root = merge(merge(a, new Treap(k, val)), merge(b, c));
}

inline int get_ans(Treap *&root, int k){
    Treap *l, *r;
    split(root, l, r, k + 1);
    int ret = Max(l);
    root = merge(l, r);
    return ret;
}

void Union(Treap *&a, Treap *&b) {
    if (b == nullptr) return;
    Union(a, b->l);
    Union(a, b->r);
    insert(a, b->key, b->v);
    b = nullptr;
}

void solve() {
    int n, q; cin >> n >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int id, x, y; cin >> id >> x >> y;
            id--;
            insert(root[id], x, y);
        } else if (t == 2) {
            int a, b; cin >> a >> b;
            a--, b--;
            if (size(root[a]) < size(root[b])) {
                Union(root[b], root[a]);
                swap(root[b], root[a]);
            } else {
                Union(root[a], root[b]);
            }
        } else {
            int id, k; cin >> id >> k;
            id--;
            int ans = get_ans(root[id], k);
            if (ans == 0) ans--;
            cout << ans << '\n';
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