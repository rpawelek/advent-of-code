#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 2048
#define MAX_DIGITS 20

int main(void) {
    unsigned long start = 0, end = 0;
    unsigned long sum = 0;

    char buf[MAX_INPUT_LENGTH] = {};
    char* current_pos = NULL;
    int chars_read = 0;

    printf("Paste your input: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        perror("Error reading input");
        return 1;
    }
    buf[strcspn(buf, "\n")] = '\0';

    current_pos = buf;
    while (sscanf(current_pos, "%lu-%lu,%n", &start, &end, &chars_read) == 2) {
        for (int d = 1; d <= MAX_DIGITS / 2; ++d) {
            unsigned long power_of_10 = 1;
            for (int i = 0; i < d; ++i) {
                power_of_10 *= 10;
            }

            unsigned long divisor_A = power_of_10 + 1;
            unsigned long min_A = power_of_10 / 10;
            unsigned long range_A = (start + power_of_10) / divisor_A;
            unsigned long start_A = (range_A > min_A) ? range_A : min_A;

            for (unsigned long A = start_A; ; ++A) {
                unsigned long max_A = power_of_10 - 1;

                if (A > max_A) break;

                unsigned long current_invalid_id = A * divisor_A;
                if (current_invalid_id > end) break;
                sum += current_invalid_id;
            }
        }

        current_pos += chars_read;
    }

    printf("Sum of all invalid IDs: %lu\n", sum);

    return 0;
}
