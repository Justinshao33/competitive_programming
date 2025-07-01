#include <stdio.h>

int T, a, n, ans;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ans = 0;
        while (n--) {
            scanf("%d", &a);
            if (a == 6 || a == 15 || a == 120) ans ^= 2;
            else if (a <= 120 && a >= 15) ans ^= (a & 1);
            else ans ^= (a & 1 ^ 1);
        }
        printf("%s", (ans ? "MM\n" : "TT\n"));
    }
}