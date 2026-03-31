#ifdef LOCAL
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;

#define int long long

using ll  = long long;
using ull = unsigned long long;
using ld = long double;
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
using pii = pair<int, int>;
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

template<class T> bool chmin(T &a, T b) { return (b < a && (a = b, true)); }
template<class T> bool chmax(T &a, T b) { return (a < b && (a = b, true)); }

#define lpos pos << 1
#define rpos pos << 1 | 1
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << "," << p.second << ')'; }
template<typename A> ostream& operator << (ostream &os, const vector<A> &p) { for(const auto &a : p) os << a << " "; os << '\n'; return os; }
 
const int MAXN = 5e5 + 5, MOD = 998244353, IINF = 1e9 + 7, MOD2 = 1000000007;
const ll LINF = 1e18L + 5;
const int B = 320;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// int get_rand(int l, int r){ return uniform_int_distribution<int>(l, r)(rng); }
 
int fpow (int x, int exp, int mod = LLONG_MAX) { if (x == 0) return 0; int res = 1; while (exp > 0) { if (exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1; } return res; }

struct info{
    int l, r, y, v;
};

vector<int> dic;
int tree[MAXN << 2], tag[MAXN << 2];
 
void pull(int pos, int l, int r) {
	if (tag[pos]) tree[pos] = dic[r + 1] - dic[l];
	else if(l < r) tree[pos] = tree[lpos] + tree[rpos];
    else tree[pos] = 0;
}
 
void mod(int pos, int l, int r, int ml, int mr, int val){
    if (ml <= l && mr >= r) {
        tag[pos] += val;
    }
    else{
        int mid = l + r >> 1;
        if(ml <= mid) mod(lpos, l, mid, ml, mr, val);
        if(mr > mid) mod(rpos, mid + 1, r, ml, mr, val);
    }
    pull(pos, l, r);
}


void solve() {
    int n, m; cin >> n >> m;
    // dic.push_back(m);
    int h, w; cin >> h >> w;
    int N; cin >> N;
    vector<info> rec;
    rep (i, 0, N) {
        int r, c; cin >> r >> c;
        int r2 = min(r, n - h + 1), c2 = min(c, m - w + 1);
        r = max<int>(1, r - h + 1), c = max<int>(1, c - w + 1);
        if (r <= r2 && c <= c2) {
            dic.push_back(c);
            dic.push_back(c2 + 1);
            rec.push_back({c, c2 + 1, r, 1});
            rec.push_back({c, c2 + 1, r2 + 1, -1});
        }
    }
    sort(all(dic));
    dic.erase(unique(all(dic)), dic.end());
    sort(all(rec), [](auto a, auto b) {
        return a.y < b.y;
    });
    int ans = (n - h + 1) * (m - w + 1), pre = 0;
    for (auto [l, r, y, v] : rec){
        ans -= 1LL * (y - pre) * tree[1];
        pre = y;
        l = lower_bound(all(dic), l) - dic.begin();
        r = lower_bound(all(dic), r) - dic.begin() - 1;
        mod(1, 0, ssize(dic) - 2, l, r, v);
    }
    cout << ans << '\n';
}
 
signed main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}