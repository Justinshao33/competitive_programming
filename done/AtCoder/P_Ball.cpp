#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;
using i64 = long long;

#define all(a) begin(a), end(a)
#define rep(a, b, c) for (int a = b; a < c; a++)

bool chmin(auto& a, auto b) { return (b < a and (a = b, true)); }
bool chmax(auto& a, auto b) { return (a < b and (a = b, true)); }

using u32 = unsigned int;
using u64 = unsigned long long;
#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder_modint {

namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename conditional<is_same<T, __int128_t>::value ||
                                  is_same<T, __int128>::value,
                              true_type,
                              false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename conditional<is_same<T, __uint128_t>::value ||
                                  is_same<T, unsigned __int128>::value,
                              true_type,
                              false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral = typename conditional<is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              true_type,
                                              false_type>::type;

template <class T>
using is_signed_int = typename conditional<(is_integral<T>::value &&
                                                 is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                true_type,
                                                false_type>::type;

template <class T>
using is_unsigned_int =
    typename conditional<(is_integral<T>::value &&
                               is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              true_type,
                              false_type>::type;

template <class T>
using to_unsigned = typename conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename conditional<is_signed<T>::value,
                              make_unsigned<T>,
                              common_type<T>>::type>::type;

#else

template <class T> using is_integral = typename is_integral<T>;

template <class T>
using is_signed_int =
    typename conditional<is_integral<T>::value && is_signed<T>::value,
                              true_type,
                              false_type>::type;

template <class T>
using is_unsigned_int =
    typename conditional<is_integral<T>::value &&
                                  is_unsigned<T>::value,
                              true_type,
                              false_type>::type;

template <class T>
using to_unsigned = typename conditional<is_signed_int<T>::value,
                                              make_unsigned<T>,
                                              common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = enable_if_t<is_unsigned_int<T>::value>;

template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

// @param m `1 <= m`
// @return x mod m
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}

// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr long long bases[3] = {2, 7, 61};
    for (long long a : bases) {
        long long t = d;
        long long y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};

    // Contracts:
    // [1] s - m0 * a = 0 (mod b)
    // [2] t - m1 * a = 0 (mod b)
    // [3] s * |m1| + t * |m0| <= b
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

        // [3]:
        // (s - t * u) * |m1| + t * |m0 - m1 * u|
        // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
        // = s * |m1| + t * |m0| <= b

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    // by [3]: |m0| <= b/g
    // by g != b: |m0| < b/g
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
struct barrett {
    unsigned int _m;
    unsigned long long im;

    // @param m `1 <= m < 2^31`
    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

    // @return m
    unsigned int umod() const { return _m; }

    // @param a `0 <= a < m`
    // @param b `0 <= b < m`
    // @return `a * b % m`
    unsigned int mul(unsigned int a, unsigned int b) const {
        // [1] m = 1
        // a = b = im = 0, so okay

        // [2] m >= 2
        // im = ceil(2^64 / m)
        // -> im * m = 2^64 + r (0 <= r < m)
        // let z = a*b = c*m + d (0 <= c, d < m)
        // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
        // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2
        // ((ab * im) >> 64) == c or c + 1
        unsigned long long z = a;
        z *= b;
#ifdef _MSC_VER
        unsigned long long x;
        _umul128(z, im, &x);
#else
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
        unsigned int v = (unsigned int)(z - x * _m);
        if (_m <= v) v += _m;
        return v;
    }
};

struct modint_base {};
struct static_modint_base : modint_base {};

template <class T> using is_modint = is_base_of<modint_base, T>;
template <class T> using is_modint_t = enable_if_t<is_modint<T>::value>;

}  // namespace internal

template <int m, enable_if_t<(1 <= m)>* = nullptr>
struct static_modint : internal::static_modint_base {
    using mint = static_modint;

  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    static_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    static_modint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    static_modint(T v) {
        _v = (unsigned int)(v % umod());
    }

    unsigned int val() const { return _v; }

    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        if (prime) {
            assert(_v);
            return pow(umod() - 2);
        } else {
            auto eg = internal::inv_gcd(_v, m);
            assert(eg.first == 1);
            return eg.second;
        }
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
    static constexpr bool prime = internal::is_prime<m>;
};

template <int id> struct dynamic_modint : internal::modint_base {
    using mint = dynamic_modint;

  public:
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    dynamic_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        long long x = (long long)(v % (long long)(mod()));
        if (x < 0) x += mod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        _v = (unsigned int)(v % mod());
    }

    unsigned int val() const { return _v; }

    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v += mod() - rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        _v = bt.mul(_v, rhs._v);
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        auto eg = internal::inv_gcd(_v, mod());
        assert(eg.first == 1);
        return eg.second;
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

  private:
    unsigned int _v;
    static internal::barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id> internal::barrett dynamic_modint<id>::bt(998244353);

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;

namespace internal {

template <class T>
using is_static_modint = is_base_of<internal::static_modint_base, T>;

template <class T>
using is_static_modint_t = enable_if_t<is_static_modint<T>::value>;

template <class> struct is_dynamic_modint : public false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public true_type {};

template <class T>
using is_dynamic_modint_t = enable_if_t<is_dynamic_modint<T>::value>;

}  // namespace internal

}  // namespace atcoder_modint

using mint = atcoder_modint::modint998244353;

ostream& operator << (ostream &os, const mint &p) { os << p.val(); return os; }

mint G = mint(3);

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <class T>
constexpr T power(T a, u64 b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}


template <class mint>
void nft(bool type, std::vector<mint> &a) {
    int n = int(a.size()), s = 0;
    while ((1 << s) < n) {
        s++;
    }
    assert(1 << s == n);
    static std::vector<mint> ep, iep;
    while (int(ep.size()) <= s) {
        ep.push_back(power(G, mint(-1).val() / (1 << int(ep.size()))));
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
        while (v.size() > 1 && v.back() == 0) {
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
        Poly f(std::vector<D>(n, 0));
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
    Poly Getsqrt(int n) const {
        if (size() == 0) return {{0}};
        int z = QuadraticResidue(freq(0).v, 998244353);
        if (z == -1) return Poly{};
        Poly f = pre(n + 1);
        Poly g({z});
        for (int i = 1; i < n; i *= 2) {
            g = (g + f.pre(2 * i) * g.inv(2 * i)) / 2;
        }
        return g.pre(n + 1);
    }
    Poly sqrt(int n) const {
        int m = 0;
        while (m < n && freq(m) == 0) m++;
        if (m == n) return {{0}};
        if (m & 1) return Poly{};
        Poly s = Poly(std::vector<D>(v.begin() + m, v.end())).Getsqrt(n);
        if (s.size() == 0) return Poly{};
        std::vector<D> res(n);
        for (int i = 0; i + m / 2 < n; i++) res[i + m / 2] = s.freq(i);
        return Poly(res);
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

// need modint
vector<mint> fac, inv;

inline void init (int n) {
    fac.resize(n + 1);
    inv.resize(n + 1);
    fac[0] = inv[0] = 1;
    rep (i, 1, n + 1) fac[i] = fac[i - 1] * i;
    inv[n] = fac[n].inv();
    for (int i = n; i > 0; --i) inv[i - 1] = inv[i] * i;
}

inline mint Comb(int n, int k) {
    if (k > n || k < 0) return 0;
    return fac[n] * inv[k] * inv[n - k];
}

inline mint H(int n, int m) {
    return Comb(n + m - 1, m);
}

inline mint catalan(int n){
    return fac[2 * n] * inv[n + 1] * inv[n];
}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    init(n);
    vector<mint> p(n + 1), c(m);
    rep (i, 0, m) c[i] = i + 1;
    rep (i, 0, k + 1) p[n - i] = Comb(n, i);
    MultiEval ME(c);
    auto ans = ME.query(Poly(p));
    rep (i, 0, m) cout << ans[i].val() << '\n';
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