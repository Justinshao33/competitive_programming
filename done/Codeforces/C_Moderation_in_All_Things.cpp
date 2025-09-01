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

using pii = pair<int, int>;

const int INF = 1e18 + 5;

#define fi first
#define se second

struct Treap {
    Treap *l, *r, *fa;
    int size, val, sum;
    pii seg;
    Treap(int L, int R) : l(nullptr), r(nullptr), fa(nullptr), size(1), val(R - L + 1), sum(R - L + 1), seg(pii(L, R)) {}
    void pull();
    void push() {};
};
inline int SZ(Treap *p) {
    return p == nullptr ? 0 : p->size;
}
inline int SUM(Treap *p) {
    return p == nullptr ? 0 : p->sum;
}
void Treap::pull() {
    fa = nullptr;
    size = 1 + SZ(l) + SZ(r);
    sum = val + SUM(l) + SUM(r);
    if (l) l->fa = this;
    if (r) r->fa = this;
}
Treap *merge(Treap *a, Treap *b) {
    if (!a || !b) return a ? a : b;
    if (rand() % (SZ(a) + SZ(b)) < SZ(a)) {
        return a->push(), a->r = merge(a->r, b), a->pull(), a;
    }
    return b->push(), b->l = merge(a, b->l), b->pull(), b;
}
// k, n - k
void split2(Treap *p, Treap *&a, Treap *&b, int k) { // by size
    if (!p) return a = b = nullptr, void();
    p->push();
    if (SZ(p->l) + 1 <= k) {
        a = p, split2(p->r, a->r, b, k - SZ(p->l) - 1);
    } else {
        b = p, split2(p->l, a, b->l, k);
    }
    p->pull();
}
int kth(Treap *p, int k) { // 1-base
    if (k <= SUM(p->l)) return kth(p->l, k);
    if (k <= SUM(p->l) + p->val) return p->seg.first + k - SUM(p->l) - 1;
    return kth(p->r, k - SUM(p->l) - p->val);
}
tuple<Treap*, Treap*, Treap*> interval(Treap *&o, int l, int r) { // 1-based
    Treap *a, *b, *c; // b: [l, r]
    split2(o, a, b, l - 1), split2(b, b, c, r - l + 1);
    return make_tuple(a, b, c);
}

void print(Treap *p) {
    if (!p) return;
    print(p->l);
    cout << '[' << p->seg.first << ',' << p->seg.second << "] ";
    print(p->r);
}

// need record fa
int get_pos(Treap *p) {
    if (!p) return 0;
    int sz = SZ(p->l) + 1;
    while (p->fa) {
        if (p->fa->r == p) {
            sz += SZ(p->fa->l) + 1;
        }
        p = p->fa;
    }
    return sz;
}

void solve() {
    int q; cin >> q;
    Treap *rt = nullptr;
    int num = 1;
    map<pii, Treap*> node;
    node[{0, 0}] = new Treap(0, 0);
    rt = merge(rt, node[{0, 0}]);
    while (q--) {
        int p, x; cin >> p >> x;
        if (x > 0) {
            auto [seg, nd] = *prev(node.lower_bound(pii(p, INF)));
            int pos = get_pos(nd);
            auto [a, b, c] = interval(rt, pos, pos);
            delete b;
            node.erase(seg);
            node[{seg.fi, p}] = new Treap(seg.fi, p);
            if (p + 1 <= seg.se) node[{p + 1, seg.se}] = new Treap(p + 1, seg.se);
            node[{num, num + x - 1}] = new Treap(num, num + x - 1);
            rt = merge(merge(a, node[{seg.fi, p}]), node[{num, num + x - 1}]);
            if (p + 1 <= seg.se) rt = merge(rt, node[{p + 1, seg.se}]);
            rt = merge(rt, c);
            num += x;
        } else {
            x = -x;
            Treap *nd = prev(node.lower_bound(pii(p, INF)))->second;
            int pos = get_pos(nd);
            bool f = 0;
            if (nd->seg.se == p) pos++, f = 1;
            else p++;
            {
                auto [a, b, c] = interval(rt, pos, pos);
                if (f) p = b->seg.fi;
                node.erase(b->seg);
                if (b->seg.fi != p) {
                    node[{b->seg.fi, p - 1}] = new Treap(b->seg.fi, p - 1);
                    a = merge(a, node[{b->seg.fi, p - 1}]);
                    pos++;
                }
                int len = b->seg.se - p + 1;
                if (len - x > 0) {
                    node[{p + x, b->seg.se}] = new Treap(p + x, b->seg.se);
                    rt = merge(merge(a, node[{p + x, b->seg.se}]), c);
                } else {
                    rt = merge(a, c);
                }
                x = max<int>(0, x - len);
                delete b;
            }
            while (x > 0) {
                auto [a, b, c] = interval(rt, pos, pos);
                node.erase(b->seg);
                if (b->val <= x) {
                    rt = merge(a, c);
                    x -= b->val;
                } else {
                    auto [L, R] = b->seg;
                    node[{L + x, R}] = new Treap(L + x, R);
                    rt = merge(merge(a, node[{L + x, R}]), c);
                    x = max<int>(0, x - b->val);
                }
                delete b;
            }
        }
        cout << kth(rt, (SUM(rt) + 1) / 2) << '\n';
    }
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
