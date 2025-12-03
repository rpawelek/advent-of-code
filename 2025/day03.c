#include <ctype.h>
#include <stdio.h>

int main(void) {
    char buf[1024] = {};
    long sum = 0;

    printf("Paste your input: ");
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if (buf[0] == '\n' || buf[0] == '\r') break;

        int digits[512], n = 0;

        for (int i = 0; buf[i]; ++i) {
            if (isdigit((unsigned char)buf[i])) {
                digits[n++] = buf[i] - '0';
            }
        }

        int best = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int val = digits[i] * 10 + digits[j];
                if (val > best) best = val;
            }
        }

        sum += best;
    }

    printf("Total output joltage: %ld\n", sum);

    return 0;
}
