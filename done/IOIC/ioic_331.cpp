#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,popcnt,sse4,abm")
#include<bits/stdc++.h>
using namespace std;
 
const int MOD = 1e9 + 7;
const int BUF_SZ = 1 << 15;

char buf[BUF_SZ];
int pos;
int len;
char next_char() {
	if (pos == len) {
		pos = 0;
		len = (int)fread(buf, 1, BUF_SZ, stdin);
		if (!len) { return EOF; }
	}
	return buf[pos++];
}

int in() {
	int x;
	char ch;
	int sgn = 1;
	while (!isdigit(ch = next_char())) {
		if (ch == '-') { sgn *= -1; }
	}
	x = ch - '0';
	while (isdigit(ch = next_char())) { x = x * 10 + (ch - '0'); }
	return x * sgn;
}

char c[3] = {'M', 'M'}, c2[3] = {'T', 'T'};

const short b = 6, d = 15, e = 120;

inline void solve() {
    int n = in();
    short ans = 0;
    while (n--) {
        int a = in();
        if (a == b || a == d || a == e) ans ^= 2;
        else ans ^= (a & 1 ^ (a < 15 || a > 120));

    }
    printf("%s\n", (ans ? c : c2));
}
 
int main() {
    short T = in();
    while (T--) {
        solve();
    }
}