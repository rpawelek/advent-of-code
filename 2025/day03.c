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

        int stack[512];
        int top = 0;
        int max_remove_amount = n - 12;

        for (int i = 0; i < n; ++i) {
            while (top > 0 && stack[top - 1] < digits[i] && max_remove_amount > 0) {
                top--;
                max_remove_amount--;
            }

            stack[top++] = digits[i];
        }

        top = 12;
        long val = 0;
        for (int i = 0; i < 12; ++i) {
            val = val * 10 + stack[i];
        }

        sum += val;
    }

    printf("Total output joltage: %ld\n", sum);

    return 0;
}
