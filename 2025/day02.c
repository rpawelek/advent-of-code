#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LENGTH 2048
#define MAX_DIGITS 20

unsigned long calculate_power_of_10(int L) {
    unsigned long p = 1;
    for (int i = 0; i < L; ++i) {
        p *= 10;
    }
    return p;
}

unsigned long calculate_d_prime(int total_len, int sub_len) {
    unsigned long D_prime = 0;
    unsigned long term_prime = 1;
    unsigned long P_prime = calculate_power_of_10(sub_len);
    int total_repetitions = total_len / sub_len;

    for (int r = 0; r < total_repetitions; ++r) {
        D_prime += term_prime;
        term_prime *= P_prime;
    }
    return D_prime;
}

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
            unsigned long power_of_10 = calculate_power_of_10(d);

            unsigned long min_A = power_of_10 / 10;
            unsigned long max_A = power_of_10 - 1;

            for (int k = 2; d * k <= MAX_DIGITS; ++k) {
                unsigned long multiplier = 0;
                unsigned long term = 1;
                for (int i = 0; i < k; ++i) {
                    multiplier += term;
                    term *= power_of_10;
                }

                unsigned long range_A = (start + multiplier - 1) / multiplier;
                unsigned long start_A = (range_A > min_A) ? range_A : min_A;

                for (unsigned long a = start_A; a <= max_A; ++a) {
                    int is_primitive = 1;
                    for (int d_prime = 1; d_prime < d; ++d_prime) {
                        if (d % d_prime == 0) {
                            unsigned long D_prime = calculate_d_prime(d, d_prime);
                            if (D_prime > 0 && a % D_prime == 0) {
                                is_primitive = 0;
                                break;
                            }
                        }
                    }

                    unsigned long current_invalid_id = multiplier * a;

                    if (current_invalid_id > end) break;
                    if (is_primitive) sum += current_invalid_id;
                }
            }
        }

        current_pos += chars_read;
    }

    printf("Sum of all invalid IDs: %lu\n", sum);

    return 0;
}
