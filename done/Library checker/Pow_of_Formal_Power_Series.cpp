#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

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

using u32 = unsigned int;
using u64 = unsigned long long;
template <class T>
constexpr T power(T a, u64 b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <u32 P>
struct ModInt {
    u32 v;
    const static ModInt G;
    
    constexpr ModInt &norm(u32 x) {
        v = x < P ? x : x - P;
        return *this;
    }
    constexpr ModInt(i64 x = 0) { norm(x % P + P); }
    constexpr ModInt inv() const { return power(*this, P - 2); }
    constexpr ModInt operator-() const { return ModInt() - *this; }
    constexpr ModInt operator+(const ModInt &r) const { return ModInt().norm(v + r.v); }
    constexpr ModInt operator-(const ModInt &r) const { return ModInt().norm(v + P - r.v); }
    constexpr ModInt operator*(const ModInt &r) const { return ModInt().norm(u64(v) * r.v % P); }
    constexpr ModInt operator/(const ModInt &r) const { return *this * r.inv(); }
    constexpr ModInt &operator+=(const ModInt &r) { return *this = *this + r; }
    constexpr ModInt &operator-=(const ModInt &r) { return *this = *this - r; }
    constexpr ModInt &operator*=(const ModInt &r) { return *this = *this * r; }
    constexpr ModInt &operator/=(const ModInt &r) { return *this = *this / r; }
    constexpr bool operator==(const ModInt &r) const { return v == r.v; }
    constexpr bool operator!=(const ModInt &r) const { return v != r.v; }
    explicit constexpr operator bool() const { return v != 0; }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &r) {
        return os << r.v;
    }
};
using mint = ModInt<998244353>;
template <> const mint mint::G = mint(3);

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <class mint>
void nft(bool type, std::vector<mint> &a) {
    int n = int(a.size()), s = 0;
    while ((1 << s) < n) {
        s++;
    }
    assert(1 << s == n);
    static std::vector<mint> ep, iep;
    while (int(ep.size()) <= s) {
        ep.push_back(power(mint::G, mint(-1).v / (1 << int(ep.size()))));
        iep.push_back(ep.back().inv());
    }
    std::vector<mint> b(n);
    for (int i = 1; i <= s; i++) {
        int w = 1 << (s - i);
        mint base = type ? iep[i] : ep[i], now = 1;
        for (int y = 0; y < n / 2; y += w) {
            for (int x = 0; x < w; x++) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | w];
                b[y | x] = l + r;
                b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        std::swap(a, b);
    }
}
template <class mint>
std::vector<mint> multiply(const std::vector<mint> &a, const std::vector<mint> &b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (std::min(n, m) <= 8) {
        std::vector<mint> ans(n + m - 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i + j] += a[i] * b[j];
            }
        }
        return ans;
    }
    int lg = 0;
    while ((1 << lg) < n + m - 1) {
        lg++;
    }
    int z = 1 << lg;
    auto a2 = a, b2 = b;
    a2.resize(z);
    b2.resize(z);
    nft(false, a2);
    nft(false, b2);
    for (int i = 0; i < z; i++) {
        a2[i] *= b2[i];
    }
    nft(true, a2);
    a2.resize(n + m - 1);
    mint iz = mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) {
        a2[i] *= iz;
    }
    return a2;
}

template <class D>
struct Poly {
    std::vector<D> v;
    Poly(const std::vector<D> &v_ = {}) : v(v_) { shrink(); }
    void shrink() {
        while (v.size() && !v.back()) {
            v.pop_back();
        }
    }
    int size() const { return int(v.size()); }
    D freq(int p) const { return (p < size()) ? v[p] : D(0); }
    Poly operator+(const Poly &r) const {
        auto n = std::max(size(), r.size());
        std::vector<D> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = freq(i) + r.freq(i);
        }
        return res;
    }
    Poly operator-(const Poly &r) const {
        int n = std::max(size(), r.size());
        std::vector<D> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = freq(i) - r.freq(i);
        }
        return res;
    }
    Poly operator*(const Poly &r) const { return {multiply(v, r.v)}; }
    Poly operator*(const D &r) const {
        int n = size();
        std::vector<D> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = v[i] * r;
        }
        return res;
    }
    Poly operator/(const D &r) const { return *this * r.inv(); }
    Poly operator/(const Poly &r) const {
        if (size() < r.size()) return {{}};
        int n = size() - r.size() + 1;
        return (rev().pre(n) * r.rev().inv(n)).pre(n).rev();
    }
    Poly operator%(const Poly &r) const { return *this - *this / r * r; }
    Poly operator<<(int s) const {
        std::vector<D> res(size() + s);
        for (int i = 0; i < size(); i++) {
            res[i + s] = v[i];
        }
        return res;
    }
    Poly operator>>(int s) const {
        if (size() <= s) {
            return Poly();
        }
        std::vector<D> res(size() - s);
        for (int i = 0; i < size() - s; i++) {
            res[i] = v[i + s];
        }
        return res;
    }
    Poly &operator+=(const Poly &r) { return *this = *this + r; }
    Poly &operator-=(const Poly &r) { return *this = *this - r; }
    Poly &operator*=(const Poly &r) { return *this = *this * r; }
    Poly &operator*=(const D &r) { return *this = *this * r; }
    Poly &operator/=(const Poly &r) { return *this = *this / r; }
    Poly &operator/=(const D &r) { return *this = *this / r; }
    Poly &operator%=(const Poly &r) { return *this = *this % r; }
    Poly &operator<<=(const size_t &n) { return *this = *this << n; }
    Poly &operator>>=(const size_t &n) { return *this = *this >> n; }
    Poly pre(int le) const {
        return {{v.begin(), v.begin() + std::min(size(), le)}};
    }
    Poly rev(int n = -1) const {
        std::vector<D> res = v;
        if (n != -1) {
            res.resize(n);
        }
        std::reverse(res.begin(), res.end());
        return res;
    }
    Poly diff() const {
        std::vector<D> res(std::max(0, size() - 1));
        for (int i = 1; i < size(); i++) {
            res[i - 1] = freq(i) * i;
        }
        return res;
    }
    Poly inte() const {
        std::vector<D> res(size() + 1);
        for (int i = 0; i < size(); i++) {
            res[i + 1] = freq(i) / (i + 1);
        }
        return res;
    }
    // f * f.inv() = 1 + g(x)x^m
    Poly inv(int m) const {
        Poly res = Poly({D(1) / freq(0)});
        for (int i = 1; i < m; i *= 2) {
            res = (res * D(2) - res * res * pre(2 * i)).pre(2 * i);
        }
        return res.pre(m);
    }
    Poly exp(int n) const {
        assert(freq(0) == 0);
        Poly f({1}), g({1});
        for (int i = 1; i < n; i *= 2) {
            g = (g * 2 - f * g * g).pre(i);
            Poly q = diff().pre(i - 1);
            Poly w = (q + g * (f.diff() - f * q)).pre(2 * i - 1);
            f = (f + f * (*this - w.inte()).pre(2 * i)).pre(2 * i);
        }
        return f.pre(n);
    }
    Poly log(int n) const {
        assert(freq(0) == 1);
        auto f = pre(n);
        return (f.diff() * f.inv(n - 1)).pre(n - 1).inte();
    }
    Poly pow(int n, i64 k) const {
        int m = 0;
        while (m < n && freq(m) == 0) m++;
        Poly f(vector<D>(n, 0));
        if (k && m && (k >= n || k * m >= n)) return f;
        f.v.resize(n);
        if (m == n) return f.v[0] = 1, f;
        int le = m * k;
        Poly g({v.begin() + m, v.end()});
        D base = power<D>(g.freq(0), k), inv = g.freq(0).inv();
        g = ((g * inv).log(n - m) * D(k)).exp(n - m);
        for (int i = le; i < n; i++) f.v[i] = g.freq(i - le) * base;
        return f;
    }
    Poly sqrt(int n) const {
        assert(freq(0) == 1);
        Poly f = pre(n + 1);
        Poly g({1});
        for (int i = 1; i < n; i *= 2) {
            g = (g + f.pre(2 * i) * g.inv(2 * i)) / 2;
        }
        return g.pre(n + 1);
    }
    Poly modpower(u64 n, const Poly &mod) {
        Poly x = *this, res = {{1}};
        for (; n; n /= 2, x = x * x % mod) {
            if (n & 1) {
                res = res * x % mod;
            }
        }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const Poly &p) {
        if (p.size() == 0) {
            return os << "0";
        }
        for (auto i = 0; i < p.size(); i++) {
            if (p.v[i]) {
                os << p.v[i] << "x^" << i;
                if (i != p.size() - 1) {
                    os << "+";
                }
            }
        }
        return os;
    }
};
template <class mint>
struct MultiEval {
    using NP = MultiEval *;
    NP l, r;
    int sz;
    Poly<mint> mul;
    std::vector<mint> que;
    MultiEval(const std::vector<mint> &que_, int off, int sz_) : sz(sz_) {
        if (sz <= 100) {
            que = {que_.begin() + off, que_.begin() + off + sz};
            mul = {{1}};
            for (auto x : que) {
                mul *= {{-x, 1}};
            }
            return;
        }
        l = new MultiEval(que_, off, sz / 2);
        r = new MultiEval(que_, off + sz / 2, sz - sz / 2);
        mul = l->mul * r->mul;
    }
    MultiEval(const std::vector<mint> &que_) : MultiEval(que_, 0, int(que_.size())) {}
    void query(const Poly<mint> &pol_, std::vector<mint> &res) const {
        if (sz <= 100) {
            for (auto x : que) {
                mint sm = 0, base = 1;
                for (int i = 0; i < pol_.size(); i++) {
                    sm += base * pol_.freq(i);
                    base *= x;
                }
                res.push_back(sm);
            }
            return;
        }
        auto pol = pol_ % mul;
        l->query(pol, res);
        r->query(pol, res);
    }
    std::vector<mint> query(const Poly<mint> &pol) const {
        std::vector<mint> res;
        query(pol, res);
        return res;
    }
};
template <class mint>
Poly<mint> berlekampMassey(const std::vector<mint> &s) {
    int n = int(s.size());
    std::vector<mint> b = {mint(-1)}, c = {mint(-1)};
    mint y = mint(1);
    for (int ed = 1; ed <= n; ed++) {
        int l = int(c.size()), m = int(b.size());
        mint x = 0;
        for (int i = 0; i < l; i++) {
            x += c[i] * s[ed - l + i];
        }
        b.push_back(0);
        m++;
        if (!x) {
            continue;
        }
        mint freq = x / y;
        if (l < m) {
            // use b
            auto tmp = c;
            c.insert(begin(c), m - l, mint(0));
            for (int i = 0; i < m; i++) {
                c[m - 1 - i] -= freq * b[m - 1 - i];
            }
            b = tmp;
            y = x;
        } else {
            // use c
            for (int i = 0; i < m; i++) {
                c[l - 1 - i] -= freq * b[m - 1 - i];
            }
        }
    }
    return c;
}
template <class E, class mint = decltype(E().f)>
mint sparseDet(const std::vector<std::vector<E>> &g) {
    int n = int(g.size());
    if (n == 0) {
        return 1;
    }
    auto randV = [&]() {
        std::vector<mint> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = mint(std::uniform_int_distribution<i64>(1, mint(-1).v)(rng));  // need rng
        }
        return res;
    };
    std::vector<mint> c = randV(), l = randV(), r = randV();
    // l * mat * r
    std::vector<mint> buf(2 * n);
    for (int fe = 0; fe < 2 * n; fe++) {
        for (int i = 0; i < n; i++) {
            buf[fe] += l[i] * r[i];
        }
        for (int i = 0; i < n; i++) {
            r[i] *= c[i];
        }
        std::vector<mint> tmp(n);
        for (int i = 0; i < n; i++) {
            for (auto e : g[i]) {
                tmp[i] += r[e.to] * e.f;
            }
        }
        r = tmp;
    }
    auto u = berlekampMassey(buf);
    if (u.size() != n + 1) {
        return sparseDet(g);
    }
    auto acdet = u.freq(0) * mint(-1);
    if (n % 2) {
        acdet *= mint(-1);
    }
    if (!acdet) {
        return 0;
    }
    mint cdet = 1;
    for (int i = 0; i < n; i++) {
        cdet *= c[i];
    }
    return acdet / cdet;
}

void solve() {
    int n; i64 m; cin >> n >> m;
    vector<mint> a(n);
    rep (i, 0, n) cin >> a[i].v;
    Poly<mint> p(a);
    p = p.pow(n, m);
    rep (i, 0, n) cout << p.freq(i) << " \n" [i == n - 1];
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