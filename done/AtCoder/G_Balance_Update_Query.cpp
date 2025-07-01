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
 
const int MAXN = 4e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const double eps = 1e-9;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

struct info {
    ll sum, cnt;
    info() {}
    info(ll a, ll b) : sum(a), cnt(b) {}
    info operator+ (const info &oth) const {
        return info(sum + oth.sum, cnt + oth.cnt);
    }
} tree[MAXN << 2];

void mod(int pos, int l, int r, int idx, info val) {
    if (l == r) {
        tree[pos] = tree[pos] + val;
        return;
    }
    int mid = l + r >> 1;
    if (idx <= mid) mod(lpos, l, mid, idx, val);
    else mod(rpos, mid + 1, r, idx, val);
    tree[pos] = tree[lpos] + tree[rpos];
}

info query(int pos, int l, int r, int ql, int qr) {
    if (ql > qr) return info(0, 0);
    if (ql <= l && r <= qr) return tree[pos];
    int mid = l + r >> 1;
    info res = info(0, 0);
    if (ql <= mid) res = res + query(lpos, l, mid, ql, qr);
    if (qr > mid) res = res + query(rpos, mid + 1, r, ql, qr);
    return res;
}

int find_left(int pos, int l, int r, ll x) {
    if (l == r) return l;
    int mid = l + r >> 1;
    if (tree[rpos].cnt > x) return find_left(rpos, mid + 1, r, x);
    else return find_left(lpos, l, mid, x - tree[rpos].cnt);
}

void solve() {
    int n; cin >> n;
    vector<ll> a(n), b(n), dic;
    rep (i, 0, n) {
        cin >> a[i] >> b[i];
        dic.pb(a[i]);
    }
    int q; cin >> q;
    vector<array<ll, 3>> que(q);
    rep (i, 0, q) {
        int t; cin >> t;
        if (t == 3) {
            ll x; cin >> x;
            que[i] = {t, x, -1};
        } else {
            ll x, y; cin >> x >> y;
            x--;
            que[i] = {t, x, y};
            if (t == 1) dic.pb(y);
        }
    }
    sort(all(dic));
    dic.erase(unique(all(dic)), dic.end());
    int m = dic.size();
    auto get_id = [&](ll x) -> int {
        return lower_bound(all(dic), x) - dic.begin();
    };
    rep (i, 0, n) {
        mod(1, 0, m - 1, get_id(a[i]), info(a[i] * b[i], b[i]));
    }
    for (auto [t, x, y] : que) {
        if (t == 1) {
            mod(1, 0, m - 1, get_id(a[x]), info(-a[x] * b[x], -b[x]));
            a[x] = y;
            mod(1, 0, m - 1, get_id(a[x]), info(a[x] * b[x], b[x]));
        } else if (t == 2) {
            mod(1, 0, m - 1, get_id(a[x]), info(-a[x] * b[x], -b[x]));
            b[x] = y;
            mod(1, 0, m - 1, get_id(a[x]), info(a[x] * b[x], b[x]));
        } else {
            if (tree[1].cnt < x) {
                cout << -1 << '\n';
                continue;
            }
            int l = find_left(1, 0, m - 1, x);
            auto [sum, cnt] = query(1, 0, m - 1, l + 1, m - 1);
            cout << sum + (x - cnt) * dic[l] << '\n';
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