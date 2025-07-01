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
 
const int MAXN = 3e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct info {
    int y, l, r, val;
};

int tree[MAXN << 2], tag[MAXN << 2];

void upd(int pos, int val) {
    tree[pos] += val;
    tag[pos] += val;
}

void push(int pos) {
    if (tag[pos]) {
        upd(lpos, tag[pos]);
        upd(rpos, tag[pos]);
        tag[pos] = 0;
    }
}

void mod(int pos, int l, int r, int ml, int mr, int val) {
    if (ml > mr) return;
    if (ml <= l && mr >= r) {
        upd(pos, val);
        return;
    }
    push(pos);
    int mid = l + r >> 1;
    if (ml <= mid) mod(lpos, l, mid, ml, mr, val);
    if (mr > mid) mod(rpos, mid + 1, r, ml, mr, val);
    tree[pos] = max(tree[lpos], tree[rpos]);
}

int query(int pos, int l, int r) {
    if (l == r) return l;
    push(pos);
    int mid = l + r >> 1;
    if (tree[lpos] == tree[1]) return query(lpos, l, mid);
    else return query(rpos, mid + 1, r); 
}

void solve() {
    int n; cin >> n;
    vector<info> rec;
    vector<int> dic;
    const int MAXR = 1e9;
    dic.pb(MAXR);
    rep (i, 0, n) {
        int l, r; cin >> l >> r;
        /*
        1: 0 <= L < l && l < R < r
        2: l < L < r && r < R <= 1e9
        同一個線段產生的兩個矩形不會互相重疊，可以直接計算最大矩形重疊
        */
        rec.pb({0, l + 1, r - 1, 1});
        rec.pb({max(0, l - 1), l + 1, r - 1, -1});
        rec.pb({l + 1, r + 1, MAXR, 1});
        rec.pb({r - 1, r + 1, MAXR, -1});
        dic.pb(l + 1);
        dic.pb(r - 1);
        dic.pb(r + 1);
    } 
    sort(all(dic));
    dic.erase(unique(all(dic)), dic.end());
    sort(all(rec), [](info a, info b) {
        if (a.y != b.y) return a.y < b.y;
        return a.val > b.val;
    });
    int m = dic.size();
    int ans = 0, L = 0, R = 1;
    for (auto &[y, l, r, val] : rec) {
        l = lower_bound(all(dic), l) - dic.begin() + 1;
        r = lower_bound(all(dic), r) - dic.begin() + 1;
        mod(1, 1, m, l, r, val);
        if (ans < tree[1]) {
            ans = tree[1];
            L = y;
            R = dic[query(1, 1, m) - 1];
        } else if (ans == tree[1] && l == y) {
            R = min(R, dic[query(1, 1, m) - 1]);
        }
    }
    cout << L << ' ' << R << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}