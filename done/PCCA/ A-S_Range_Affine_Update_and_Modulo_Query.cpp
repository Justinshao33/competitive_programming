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

const int B = 1000, MOD = 1e5 + 3;

struct info {
    int a, b;
    info() {
        a = 1;
        b = 0;
    }
    info(int _a, int _b) : a(_a), b(_b) {}
    info operator+ (const info &oth) {
        info ret;
        ret.a = a * oth.a % MOD;
        ret.b = a * oth.b + b;
        ret.b %= MOD;
        return ret;
    } 
};

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
    int n, q; cin >> n >> q;
    vector<int> a(n), bel(n), inv(MOD);
    rep (i, 0, n) {
        cin >> a[i];
        bel[i] = i / B;
    }
    rep (i, 1, MOD) inv[i] = fpow(i, MOD - 2);
    vector cnt(B, vector<int>(MOD, 0));
    vector<info> tag(B, info(1, 0));
    rep (i, 0, n) cnt[bel[i]][a[i]]++;
    while (q--) {
        int t, l, r; cin >> t >> l >> r;
        l--, r--;
        auto push = [&](int id) -> void {
            rep (i, id * B, min(n, id * B + B)) {
                cnt[id][a[i]]--;
                a[i] = (a[i] * tag[id].a + tag[id].b) % MOD;
                cnt[id][a[i]]++;
            }
            tag[id] = info(1, 0);
        };
        if (t == 1) {
            int c, d; cin >> c >> d;
            if (bel[l] == bel[r]) {
                push(bel[l]);
                rep (i, l, r + 1) {
                    cnt[bel[i]][a[i]]--;
                    a[i] = (a[i] * c + d) % MOD;
                    cnt[bel[i]][a[i]]++;
                }
                continue;
            }
            for (int i = bel[l] + 1; i < bel[r]; i++) {
                tag[i] = info(c, d) + tag[i];
            }
            push(bel[l]);
            rep (i, l, bel[l] * B + B) {
                cnt[bel[l]][a[i]]--;
                a[i] = (a[i] * c + d) % MOD;
                cnt[bel[l]][a[i]]++;
            }
            push(bel[r]);
            rep (i, bel[r] * B, r + 1) {
                cnt[bel[r]][a[i]]--;
                a[i] = (a[i] * c + d) % MOD;
                cnt[bel[r]][a[i]]++;
            }
        } else {
            int x; cin >> x;
            push(bel[l]);
            push(bel[r]);
            int ans = 0;
            if (bel[l] == bel[r]) {
                for (int i = l; i <= r; i++) {
                    ans += a[i] == x;
                }
                cout << ans << '\n';
                continue;
            }
            rep (i, l, bel[l] * B + B) {
                ans += a[i] == x;
            }
            rep (i, bel[r] * B, r + 1) {
                ans += a[i] == x;
            }
            for (int i = bel[l] + 1; i < bel[r]; i++) {
                int X = x - tag[i].b + MOD;
                if (X >= MOD) X -= MOD;
                X = X * inv[tag[i].a] % MOD;
                ans += cnt[i][X];
            }
            cout << ans << '\n';
        }
    }
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    // std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}