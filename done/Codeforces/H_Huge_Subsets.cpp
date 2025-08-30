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

#define i128 __int128

void print(i128 x) {
    string s = "";
    while (x > 0) {
        s += char(x % 10 + '0');
        x /= 10;
    }
    reverse(all(s));
    cout << s << ' ';
} 

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    rep (i, 0, n) cin >> a[i];
    int G = 0;
    rep (i, 0, n - 1) G = gcd(G, abs(a[i] - a[i + 1]));
    rep (i, 1, n) {
        i128 v = i128(a[0]) * i;
        if (G == 0) print(v);
        else cout << gcd(i64(v % G), G) << ' ';
    }
    i128 sum = 0;
    rep (i, 0, n) sum += a[i];
    print(sum);
    cout << '\n';
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}