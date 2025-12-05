#include <stdio.h>
#include <stdbool.h>

typedef struct {
    long long start;
    long long end;
} Range;

bool is_in_range(long long number, const Range ranges[], int rcount) {
    for (int i = 0; i < rcount; ++i) {
        if (number >= ranges[i].start && number <= ranges[i].end) {
            return true;
        }
    }

    return false;
}

int main(void) {
    Range ranges[1024];
    int rcount = 0;
    long long a = 0, b = 0;
    int fresh_amount = 0;

    printf("Paste your input: ");
    while (scanf("%lld-%lld", &a, &b) == 2) {
       ranges[rcount].start = a;
       ranges[rcount].end = b;
       ++rcount;
    }

    while (scanf("%lld", &a) == 1) {
        if (is_in_range(a, ranges, rcount)) {
            ++fresh_amount;
        }
    }

    printf("Amount of fresh ingredients: %d\n", fresh_amount);

    return 0;
}
