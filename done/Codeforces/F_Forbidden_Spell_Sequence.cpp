#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

#define int i64
#define all(a) a.begin(), a.end()
#define rep(a, b, c) for (int a = b; a < c; a++)

#ifdef PEPPA
template <typename R>
concept I = ranges::range<R> && !std::same_as<ranges::range_value_t<R>, char>;
template <typename A, typename B>
std::ostream &operator<<(std::ostream &o, const std::pair<A, B> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}
template <I T>
std::ostream &operator<<(std::ostream &o, const T &v) {
    o << "{";
    int f = 0;
    for (auto &&i : v) o << (f++ ? " " : "") << i;
    return o << "}";
}
void debug__(int c, auto &&...a) {
    std::cerr << "\e[1;" << c << "m";
    (..., (std::cerr << a << " "));
    std::cerr << "\e[0m" << std::endl;
}
#define debug_(c, x...) debug__(c, __LINE__, "[" + std::string(#x) + "]", x)
#define debug(x...) debug_(93, x)
#else
#define debug(x...) void(0)
#endif

bool chmin(auto& a, auto b) { return (b < a and (a = b, true)); }
bool chmax(auto& a, auto b) { return (a < b and (a = b, true)); }

const int MOD = 1e9 + 7;

int fpow(int x, int e) {
    int res = 1;
    while (e > 0) {
        if (e & 1) res = res * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return res;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<int> ban;
    rep (i, 0, m) {
        int k; cin >> k;
        int res = 0;
        rep (j, 0, k) {
            char c; cin >> c;
            res |= 1 << (c - 'a');
        }
        ban.push_back(res);
    }
    vector<int> cnt(1 << 7, 0);
    int ans = 0;
    rep (bit, 1, 1 << 7) {
        cnt[bit] = fpow(__builtin_popcount(bit), n);
        for (int msk = (bit - 1) & bit; msk > 0; msk = (msk - 1) & bit) {
            cnt[bit] -= cnt[msk];
            cnt[bit] = (cnt[bit] + MOD) % MOD;
        }
        bool f = 0;
        rep (i, 0, m) if ((bit & ban[i]) == ban[i]) f = 1;
        if (!f) ans += cnt[bit];
    }
    cout << ans % MOD << '\n';

}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;

    while (t--) {
        solve();
    }

    return 0;
}