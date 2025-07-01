#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rep(X, a, b) for(int X = a; X < b; ++X)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pld pair<ld, ld>
#define ld long double
#define F first
#define S second

#ifdef LOCAL
#define ZTMYACANESOCUTE freopen("in.txt", "r", stdin);
#define debug(...) {cerr << #__VA_ARGS__ << " = "; dbg(__VA_ARGS__);}
#else
#define ZTMYACANESOCUTE ios_base::sync_with_stdio(0), cin.tie(0);
#define debug(...) 6;
#endif

void dbg() { cerr << '\n'; }
template<typename T, typename ...U>
void dbg(T t, U ...u) { cerr << t << ' '; dbg(u...); }

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
 
ll fpow(ll x, ll exp, ll mod = LLONG_MAX){ ll res = 1; while(exp){ if(exp & 1) res = res * x % mod; x = x * x % mod; exp >>= 1;} return res; }

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

// need atcoder_modint
namespace atcoder_convolution {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
constexpr int bsf_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

// Compile time primitive root
// @param m must be prime
// @return primitive root (and minimum in now)
constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (long long)(i)*i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        divs[cnt++] = x;
    }
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (atcoder_modint::internal::pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
template <int m> constexpr int primitive_root = primitive_root_constexpr(m);

template <class mint,
          int g = internal::primitive_root<mint::mod()>,
          atcoder_modint::internal::is_static_modint_t<mint>* = nullptr>
struct fft_info {
    static constexpr int rank2 = bsf_constexpr(mint::mod() - 1);
    array<mint, rank2 + 1> root;   // root[i]^(2^i) == 1
    array<mint, rank2 + 1> iroot;  // root[i] * iroot[i] == 1

    array<mint, max(0, rank2 - 2 + 1)> rate2;
    array<mint, max(0, rank2 - 2 + 1)> irate2;

    array<mint, max(0, rank2 - 3 + 1)> rate3;
    array<mint, max(0, rank2 - 3 + 1)> irate3;

    fft_info() {
        root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
        iroot[rank2] = root[rank2].inv();
        for (int i = rank2 - 1; i >= 0; i--) {
            root[i] = root[i + 1] * root[i + 1];
            iroot[i] = iroot[i + 1] * iroot[i + 1];
        }

        {
            mint prod = 1, iprod = 1;
            for (int i = 0; i <= rank2 - 2; i++) {
                rate2[i] = root[i + 2] * prod;
                irate2[i] = iroot[i + 2] * iprod;
                prod *= iroot[i + 2];
                iprod *= root[i + 2];
            }
        }
        {
            mint prod = 1, iprod = 1;
            for (int i = 0; i <= rank2 - 3; i++) {
                rate3[i] = root[i + 3] * prod;
                irate3[i] = iroot[i + 3] * iprod;
                prod *= iroot[i + 3];
                iprod *= root[i + 3];
            }
        }
    }
};

template <class mint, atcoder_modint::internal::is_static_modint_t<mint>* = nullptr>
void butterfly(vector<mint>& a) {
    int n = int(a.size());
    int h = internal::ceil_pow2(n);

    static const fft_info<mint> info;

    int len = 0;  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
    while (len < h) {
        if (h - len == 1) {
            int p = 1 << (h - len - 1);
            mint rot = 1;
            for (int s = 0; s < (1 << len); s++) {
                int offset = s << (h - len);
                for (int i = 0; i < p; i++) {
                    auto l = a[i + offset];
                    auto r = a[i + offset + p] * rot;
                    a[i + offset] = l + r;
                    a[i + offset + p] = l - r;
                }
                if (s + 1 != (1 << len))
                    rot *= info.rate2[bsf(~(unsigned int)(s))];
            }
            len++;
        } else {
            // 4-base
            int p = 1 << (h - len - 2);
            mint rot = 1, imag = info.root[2];
            for (int s = 0; s < (1 << len); s++) {
                mint rot2 = rot * rot;
                mint rot3 = rot2 * rot;
                int offset = s << (h - len);
                for (int i = 0; i < p; i++) {
                    auto mod2 = 1ULL * mint::mod() * mint::mod();
                    auto a0 = 1ULL * a[i + offset].val();
                    auto a1 = 1ULL * a[i + offset + p].val() * rot.val();
                    auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();
                    auto a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();
                    auto a1na3imag =
                        1ULL * mint(a1 + mod2 - a3).val() * imag.val();
                    auto na2 = mod2 - a2;
                    a[i + offset] = a0 + a2 + a1 + a3;
                    a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
                    a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
                    a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
                }
                if (s + 1 != (1 << len))
                    rot *= info.rate3[bsf(~(unsigned int)(s))];
            }
            len += 2;
        }
    }
}

template <class mint, atcoder_modint::internal::is_static_modint_t<mint>* = nullptr>
void butterfly_inv(vector<mint>& a) {
    int n = int(a.size());
    int h = internal::ceil_pow2(n);

    static const fft_info<mint> info;

    int len = h;  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
    while (len) {
        if (len == 1) {
            int p = 1 << (h - len);
            mint irot = 1;
            for (int s = 0; s < (1 << (len - 1)); s++) {
                int offset = s << (h - len + 1);
                for (int i = 0; i < p; i++) {
                    auto l = a[i + offset];
                    auto r = a[i + offset + p];
                    a[i + offset] = l + r;
                    a[i + offset + p] =
                        (unsigned long long)(mint::mod() + l.val() - r.val()) *
                        irot.val();
                    ;
                }
                if (s + 1 != (1 << (len - 1)))
                    irot *= info.irate2[bsf(~(unsigned int)(s))];
            }
            len--;
        } else {
            // 4-base
            int p = 1 << (h - len);
            mint irot = 1, iimag = info.iroot[2];
            for (int s = 0; s < (1 << (len - 2)); s++) {
                mint irot2 = irot * irot;
                mint irot3 = irot2 * irot;
                int offset = s << (h - len + 2);
                for (int i = 0; i < p; i++) {
                    auto a0 = 1ULL * a[i + offset + 0 * p].val();
                    auto a1 = 1ULL * a[i + offset + 1 * p].val();
                    auto a2 = 1ULL * a[i + offset + 2 * p].val();
                    auto a3 = 1ULL * a[i + offset + 3 * p].val();

                    auto a2na3iimag =
                        1ULL *
                        mint((mint::mod() + a2 - a3) * iimag.val()).val();

                    a[i + offset] = a0 + a1 + a2 + a3;
                    a[i + offset + 1 * p] =
                        (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();
                    a[i + offset + 2 * p] =
                        (a0 + a1 + (mint::mod() - a2) + (mint::mod() - a3)) *
                        irot2.val();
                    a[i + offset + 3 * p] =
                        (a0 + (mint::mod() - a1) + (mint::mod() - a2na3iimag)) *
                        irot3.val();
                }
                if (s + 1 != (1 << (len - 2)))
                    irot *= info.irate3[bsf(~(unsigned int)(s))];
            }
            len -= 2;
        }
    }
}

template <class mint, atcoder_modint::internal::is_static_modint_t<mint>* = nullptr>
vector<mint> convolution_naive(const vector<mint>& a,
                                    const vector<mint>& b) {
    int n = int(a.size()), m = int(b.size());
    vector<mint> ans(n + m - 1);
    if (n < m) {
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                ans[i + j] += a[i] * b[j];
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i + j] += a[i] * b[j];
            }
        }
    }
    return ans;
}

template <class mint, atcoder_modint::internal::is_static_modint_t<mint>* = nullptr>
vector<mint> convolution_fft(vector<mint> a, vector<mint> b) {
    int n = int(a.size()), m = int(b.size());
    int z = 1 << internal::ceil_pow2(n + m - 1);
    a.resize(z);
    internal::butterfly(a);
    b.resize(z);
    internal::butterfly(b);
    for (int i = 0; i < z; i++) {
        a[i] *= b[i];
    }
    internal::butterfly_inv(a);
    a.resize(n + m - 1);
    mint iz = mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
    return a;
}

}  // namespace internal

template <class mint, atcoder_modint::internal::is_static_modint_t<mint>* = nullptr>
vector<mint> convolution(vector<mint>&& a, vector<mint>&& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (min(n, m) <= 60) return atcoder_convolution::internal::convolution_naive(a, b);
    return internal::convolution_fft(a, b);
}

template <class mint, atcoder_modint::internal::is_static_modint_t<mint>* = nullptr>
vector<mint> convolution(const vector<mint>& a,
                              const vector<mint>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (min(n, m) <= 60) return atcoder_convolution::internal::convolution_naive(a, b);
    return internal::convolution_fft(a, b);
}

template <unsigned int mod = 998244353,
          class T,
          enable_if_t<atcoder_modint::internal::is_integral<T>::value>* = nullptr>
vector<T> convolution(const vector<T>& a, const vector<T>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using mint = atcoder_modint::static_modint<mod>;
    vector<mint> a2(n), b2(m);
    for (int i = 0; i < n; i++) {
        a2[i] = mint(a[i]);
    }
    for (int i = 0; i < m; i++) {
        b2[i] = mint(b[i]);
    }
    auto c2 = convolution(move(a2), move(b2));
    vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        c[i] = c2[i].val();
    }
    return c;
}

vector<long long> convolution_ll(const vector<long long>& a,
                                      const vector<long long>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    static constexpr unsigned long long MOD1 = 754974721;  // 2^24
    static constexpr unsigned long long MOD2 = 167772161;  // 2^25
    static constexpr unsigned long long MOD3 = 469762049;  // 2^26
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

    static constexpr unsigned long long i1 =
        atcoder_modint::internal::inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr unsigned long long i2 =
        atcoder_modint::internal::inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr unsigned long long i3 =
        atcoder_modint::internal::inv_gcd(MOD1 * MOD2, MOD3).second;

    auto c1 = convolution<MOD1>(a, b);
    auto c2 = convolution<MOD2>(a, b);
    auto c3 = convolution<MOD3>(a, b);

    vector<long long> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        unsigned long long x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;
        // B = 2^63, -B <= x, r(real value) < B
        // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
        // r = c1[i] (mod MOD1)
        // focus on MOD1
        // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
        // r = x,
        //     x - M' + (0 or 2B),
        //     x - 2M' + (0, 2B or 4B),
        //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
        // (r - x) = 0, (0)
        //           - M' + (0 or 2B), (1)
        //           -2M' + (0 or 2B or 4B), (2)
        //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
        // we checked that
        //   ((1) mod MOD1) mod 5 = 2
        //   ((2) mod MOD1) mod 5 = 3
        //   ((3) mod MOD1) mod 5 = 4
        long long diff =
            c1[i] - atcoder_modint::internal::safe_mod((long long)(x), (long long)(MOD1));
        if (diff < 0) diff += MOD1;
        static constexpr unsigned long long offset[5] = {
            0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = x;
    }

    return c;
}

}  // namespace atcoder_convolution

using mint = atcoder_modint::modint998244353;
using namespace atcoder_convolution;

struct Poly {
    vector<mint> a;
    Poly(){}
    Poly(ll n): a(n){}
    Poly(const vector<mint>& a): a(a){}
    Poly(vector<mint>&& a): a(a){}
    mint& operator[](ll x){ return a[x]; }
    mint operator[](ll x) const { return a[x]; }
    auto begin(){ return a.begin(); }
    auto end(){ return a.end(); }
    auto begin() const { return a.cbegin(); }
    auto end() const { return a.cend(); }
    ll size() const { return a.size(); }
    Poly& resize(ll n){ a.resize(n); return *this; }
    Poly& resize(const Poly& f){ if(size() < f.size()) resize(f.size()); return *this; }
    Poly& operator+=(const Poly& f){
        resize(f);
        for(ll i = 0; i < f.size(); i++) a[i] += f[i];
        return *this;
    }
    Poly operator+(const Poly& f) const {
        if(size() < f.size()) return Poly(f) += *this;
        return Poly(*this) += f;
    }
    Poly& operator-=(const Poly& f){
        resize(f);
        for(ll i = 0; i < f.size(); i++) a[i] -= f[i];
        return *this;
    }
    Poly operator-(const Poly& f) const { return Poly(*this) -= f; }
    Poly operator-(int) const {
        Poly ans(size());
        for(ll i = 0; i < size(); i++) ans[i] = -a[i];
        return ans;
    }
    Poly operator*(const Poly& f) const { return convolution(a, f.a); }
    Poly& operator*=(const Poly& f){ a = convolution(move(a), vector(f.a)); return *this; }
    Poly inv(ll n = -1) const {
        if(n == -1) n = size();
        if(n == 0) return {};
        assert(size() && a[0] != 0);
        vector<mint> ans = {a[0].inv()};
        for(ll m = 1; m < n; m *= 2) {
            const mint M = mint(m * m * 4).inv();
            vector<mint> x(a.begin(), a.begin() + min(size(), m * 2)), y = ans;
            x.resize(m * 2); internal::butterfly(x);
            y.resize(m * 2); internal::butterfly(y);
            for(ll i = 0; i < m * 2; ++i) x[i] *= y[i];
            internal::butterfly_inv(x);
            for(ll i = 0; i < m; i++) x[i] = 0;
            for(ll i = m; i < m * 2; i++) x[i] *= M;
            internal::butterfly(x);
            for(ll i = 0; i < m * 2; ++i) x[i] *= -y[i];
            internal::butterfly_inv(x);
            ans.insert(ans.end(), x.begin() + m, x.end());
        }
        ans.resize(n);
        return ans;
    }
    Poly operator/=(const Poly& f){
        const ll n = size();
        *this *= f.inv(n);
        return resize(n);
    }
    Poly operator/(const Poly& f) const { return Poly(*this) /= f; }
    Poly div(const Poly& f) const {
        assert(f.size() && f.a.back() != 0);
        Poly x = *this, y = f;
        while(x.size() && !x.a.back().val()) x.a.pop_back();
        while(y.size() && !y.a.back().val()) y.a.pop_back();
        if(x.size() < f.size()) return {};
        const ll n = x.size() - y.size() + 1;
        reverse(x.begin(), x.end()); x.resize(n);
        reverse(y.begin(), y.end()); y.resize(n);
        x /= y;
        reverse(x.begin(), x.end());
        return x;
    }
    Poly operator%(const Poly& f) const {
        assert(f.size() && f.a.back() != 0);
        return (*this - f * div(f)).resize(f.size() - 1);
    }
    pair<Poly, Poly> divmod(const Poly& f) const {
        assert(f.size() && f.a.back() != 0);
        const Poly D = div(f);
        return {D, (*this - f * D).resize(f.size() - 1)};
    }
    Poly D(ll n = -1) const {
        if(n == -1) n = size();
        if(n == 0) return {};
        Poly ans(size() - 1);
        for(ll i = 1; i < size(); i++) ans[i - 1] = a[i] * mint::raw(i);
        return ans;
    }
    Poly integral() const {
        const ll n = size();
        Poly ans(n + 1);
        ans[0] = 1;
        for(ll i = 0; i < n; i++) ans[i + 1] = ans[i] * mint::raw(i + 1);
        ans[n] = ans[n].inv();
        for(ll i = n; i--; ){
            swap(ans[i], ans[i + 1]);
            ans[i + 1] *= ans[i] * a[i];
            ans[i] *= mint::raw(i + 1);
        }
        ans[0] = 0;
        return ans;
    }
    Poly log(ll n = -1) const {
        if(n == -1) n = size();
        if(n == 0) return {};
        assert(size() && a[0] == 1);
        return (D(n) * inv(n)).resize(n - 1).integral();
    }
    Poly exp(ll n = -1) const {
        if(n == -1) n = size();
        if(n == 0) return {};
        assert(a[0] == 0);
        if(size() == 1) return vector<mint>{1};
        vector<mint> b = {1, a[1]}, c = {1}, z1, z2 = {1, 1};
        for(ll m = 2; m < n; m *= 2) {
            const mint M = mint(m).inv(), M2 = mint(m * 2).inv();
            auto y = b;
            y.resize(m * 2); internal::butterfly(y);
            z1 = move(z2);
            vector<mint> z(m);
            for(ll i = 0; i < m; i++) z[i] = y[i] * z1[i];
            internal::butterfly_inv(z);
            for(ll i = 0; i < m / 2; i++) z[i] = 0;
            for(ll i = m / 2; i < m; i++) z[i] *= M * M;
            internal::butterfly(z);
            for(ll i = 0; i < m; i++) z[i] *= -z1[i];
            internal::butterfly_inv(z);
            c.insert(c.end(), z.begin() + m / 2, z.end());
            z2 = c; z2.resize(m * 2);
            internal::butterfly(z2);
            Poly x = vector<mint>(begin(), begin() + min(size(), m));
            x = x.D(); x.a.push_back(0);
            internal::butterfly(x.a);
            for(ll i = 0; i < m; i++) x[i] *= y[i] * M;
            internal::butterfly_inv(x.a);
            x -= Poly(b).D();
            x.resize(m * 2);
            for(ll i = 0; i < m - 1; i++){
                x[m + i] = x[i]; x[i] = 0;
            }
            internal::butterfly(x.a);
            for (ll i = 0; i < m * 2; i++) x[i] *= z2[i] * M2;
            internal::butterfly_inv(x.a);
            x = x.integral(); x.a.pop_back();
            for(ll i = m; i < min(size(), m * 2); i++) x[i] += a[i];
            for(ll i = 0; i < m; i++) x[i] = 0;
            for(ll i = m; i < m * 2; i++) x[i] *= M2;
            internal::butterfly(x.a);
            for(ll i = 0; i < m * 2; ++i) x[i] *= y[i];
            internal::butterfly_inv(x.a);
            b.insert(b.end(), x.begin() + m, x.end());
        }
        return Poly(move(b)).resize(n);
    }
    Poly pow(ll k, ll n = -1){
        if(n == -1) n = size();
        if(n == 0) return {};
        assert(k >= 0);
        if(k == 0){
            Poly ans(n);
            ans[0] = 1;
            return ans;
        }
        Poly ans = *this;
        ll cnt = 0;
        while(cnt < size() && ans[cnt] == 0) cnt++;
        if(cnt == size() || cnt * k >= n) return Poly(n);
        ans.a.erase(ans.a.begin(), ans.a.begin() + cnt);
        const mint c = ans[0], C = c.pow(k), D = c.inv(), K = k;
        for(mint& i : ans) i *= D;
        ans = ans.log(n - cnt * k);
        for(mint& i : ans) i *= K;
        ans = ans.exp();
        for(mint& i : ans) i *= C;
        ans.a.insert(ans.a.begin(), cnt * k, 0);
        return ans;
    }
};

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

const int CC = 5e5 + 5;

int lp[CC]; 
vector<int> prime;

void sieve() {
    rep (i, 1, CC) lp[i] = 1;
    rep (i, 2, CC) {
        if (lp[i] == 1) {
            prime.pb(i);
        }
        for (int p : prime) {
            if (i * p >= CC) break;
            lp[i * p] = p;
            if (i % p == 0) {
                break;
            }
        }
    }
}

void solve() {
    int n; cin >> n;
    init(n);
    sieve();
    Poly f(n + 1);
    f.a[1] = n;
    for (int p : prime) {
        if (p < 3 || p > n) continue;
        f.a[p] = fac[p - 1] * mint(2).inv() * n * p * inv[p];
    }
    f = f.exp();
    cout << (f.a[n] * fac[n] / n / n).val() << '\n';
}
 
int main() {
    ZTMYACANESOCUTE;
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}