#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include <unistd.h>
using namespace std;
#define rep(X, a, b) for(int X = a; X < b; ++X)

#define GU p1 == p2 && (p2 = (p1 = buf) + read(0, buf, BUF_SIZE), p1 == p2) ? -1 : *p1++
 
const int BUF_SIZE = 1 << 16;
static char buf[BUF_SIZE], vi[10], *p1 = buf, *p2 = buf;
static int p3;
inline int in() {int re = 0; char c = GU; while (c == ' ' || c == '\n') {c = GU;} while (c >= '0' && c <= '9') {re = (re << 3) + (re << 1) + (c ^ '0'), c = GU;} return re;}
inline void out(int x) {char str[10]; int p = 0; do {str[p++] = '0' ^ (x % 10); x /= 10;} while (x); for (--p; p >= 0; p--) {vi[p3++] = str[p];} write(1, vi, p3);}

constexpr int N = 20, mask = (1 << 30) - 1;

int sum[1 << N][N], xo[1 << N][N], f[1 << N];

int main() {
    int n; n = in();
    rep (i, 0, n) f[i] = in();
    rep (bit, 0, n) {
        rep (i, 0, N) {
            if (i) sum[bit][i] = sum[bit][i - 1];
            if (bit & (1 << i)) sum[bit][i] = (sum[bit][i] + sum[bit ^ (1 << i)][i]) & mask;
        }
        f[bit] = (f[bit] + sum[bit][19]) & mask;
        xo[bit][0] ^= f[bit];
        rep (i, 0, N) {
            if (i) xo[bit][i] = xo[bit][i - 1];
            if (bit & (1 << i)) xo[bit][i] ^= xo[bit ^ (1 << i)][i];
        }
        rep (i, 0, N) {
            sum[bit][i] = (sum[bit][i] + xo[bit][19]) & mask;
        }
    }
    out(f[n - 1]);
}