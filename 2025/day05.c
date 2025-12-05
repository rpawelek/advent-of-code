#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

int compare_ranges(const void *a, const void *b) {
    const Range *range_a = (const Range*)a;
    const Range *range_b = (const Range*)b;

    if (range_a->start < range_b->start) return -1;
    if (range_a->start > range_b->start) return 1;
    return 0;
}

int main(void) {
    Range ranges[1024];
    int rcount = 0;
    long long a = 0, b = 0;
    long long fresh_amount = 0;

    printf("Paste your input: ");
    while (scanf("%lld-%lld", &a, &b) == 2) {
       ranges[rcount].start = a;
       ranges[rcount].end = b;
       ++rcount;
    }

    // while (scanf("%lld", &a) == 1) {
    //     if (is_in_range(a, ranges, rcount)) {
    //         ++fresh_amount;
    //     }
    // }

    qsort(ranges, rcount, sizeof(Range), compare_ranges);

    long long current_start = ranges[0].start;
    long long current_end = ranges[0].end;

    for (int i = 1; i < rcount; ++i) {
        if (ranges[i].start <= current_end + 1) {
            current_end = ranges[i].end > current_end ? ranges[i].end : current_end;
        } else {
            fresh_amount += (current_end - current_start + 1);

            current_start = ranges[i].start;
            current_end = ranges[i].end;
        }
    }
    fresh_amount += (current_end - current_start + 1);

    printf("Amount of fresh ingredients: %lld\n", fresh_amount);

    return 0;
}
