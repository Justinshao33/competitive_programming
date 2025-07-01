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

void solve(){
    int n; ll k; cin >> n >> k;
    vector<ll> a(n + 1);
    rep(i, 1, n + 1) cin >> a[i];

    auto check = [&](ll p) -> pll {
        pll dp = {0, -LINF}, opt = {0, 0};
        rep(i, 1, n + 1){
            pll g = dp, go = opt;
            if(chmax(g.S, dp.F - a[i])){
                go.S = opt.F;
            }
            if(chmax(g.F, dp.S + a[i] - p)){
                go.F = opt.S + 1;
            }
            swap(dp, g);
            swap(go, opt);
        }
        return {dp.F, opt.F};
    };

    auto tmp = check(0);
    k = min(k, tmp.S);

    ll l = 0, r = *max_element(all(a)) + 5;
    while(r - l > 1){
        ll mid = l + r >> 1;
        auto cur = check(mid);
        if(cur.S <= k) r = mid;
        else l = mid;
    }
    tmp = check(r);
    cout << tmp.F + r * k << '\n';
}
 
int main(){
    ZTMYACANESOCUTE;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}
