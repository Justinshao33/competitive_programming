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
 
ll fpow(ll x, ll exp, ll mod){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct info {
    ll mx, mxcnt, smx, mi, micnt, smi, sum, addtag = 0;
    void update(int, ll, int);
} tree[MAXN << 2];

ll a[MAXN];

void info::update(int t, ll val, int len) {
    if (t == 0) {
        if (mx <= val) return;
        sum += (val - mx) * mxcnt;
        if (mi == mx) {
            mi = val;
        } else if (smi == mx) {
            smi = val;
        }
        mx = val;
    } else if (t == 1) {
        if (mi >= val) return;
        sum += (val - mi) * micnt;
        if (mx == mi) {
            mx = val;
        } else if (smx == mi) {
            smx = val;
        }
        mi = val;
    } else {
        sum += val * len;
        mx += val;
        smx = max(-LINF, smx + val);
        mi += val;
        smi = min(LINF, smi + val);
        addtag += val;
    }
}

void push(int pos, int l, int r) {
    if (tree[pos].addtag) {
        int mid = l + r >> 1;
        tree[lpos].update(2, tree[pos].addtag, mid - l + 1);
        tree[rpos].update(2, tree[pos].addtag, r - mid);
        tree[pos].addtag = 0;
    }

    ll v = tree[pos].mx;
    tree[lpos].update(0, v, 0);
    tree[rpos].update(0, v, 0);

    v = tree[pos].mi;
    tree[lpos].update(1, v, 0);
    tree[rpos].update(1, v, 0);
}

void pull(int pos) {
    ll smx = (tree[lpos].mx == tree[rpos].mx) ? -LINF : min(tree[lpos].mx, tree[rpos].mx),
       smi = (tree[lpos].mi == tree[rpos].mi) ? LINF : max(tree[lpos].mi, tree[rpos].mi);
    smx = max({smx, tree[lpos].smx, tree[rpos].smx});
    smi = min({smi, tree[lpos].smi, tree[rpos].smi});
    tree[pos] = {
        max(tree[lpos].mx, tree[rpos].mx),
        tree[lpos].mxcnt * (tree[lpos].mx >= tree[rpos].mx) + tree[rpos].mxcnt * (tree[lpos].mx <= tree[rpos].mx),
        smx,
        min(tree[lpos].mi, tree[rpos].mi),
        tree[lpos].micnt * (tree[lpos].mi <= tree[rpos].mi) + tree[rpos].micnt * (tree[lpos].mi >= tree[rpos].mi),
        smi,
        tree[lpos].sum + tree[rpos].sum,
        tree[pos].addtag
    };
}

void build(int pos, int l, int r) {
    if (l == r) {
        tree[pos] = {a[l], 1, -LINF, a[l], 1, LINF, a[l], 0};
        return;
    }
    int mid = l + r >> 1;
    build(lpos, l, mid);
    build(rpos, mid + 1, r);
    pull(pos);
}

void mod(int pos, int l, int r, int ml, int mr, ll val, int t) {
    if (ml <= l && mr >= r) {
        if ((t == 0 && val > tree[pos].smx) || (t == 1 && val < tree[pos].smi) || t == 2) {
            tree[pos].update(t, val, r - l + 1);
            return;
        }
    }
    push(pos, l, r);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val, t);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val, t);
    pull(pos);
}

ll query(int pos, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) return tree[pos].sum;
    push(pos, l, r);
    int mid = l + r >> 1;
    ll res = 0;
    if (ql <= mid) res += query(lpos, l, mid, ql, qr);
    if (qr > mid) res += query(rpos, mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n, q; cin >> n >> q;
    rep (i, 1, n + 1) cin >> a[i];
    build(1, 1, n);
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        l++;
        if (t < 3) {
            ll b; cin >> b;
            mod(1, 1, n, l, r, b, t);
        } else {
            cout << query(1, 1, n, l, r) << '\n';
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