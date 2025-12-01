#include <stdio.h>

int main(void) {
    int password = 0;
    int dial = 50;

    char buf[64] = {};
    char direction = '\0';
    int steps = 0;
    int result = 0;

    printf("Paste your input: ");
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if (buf[0] == '\n' || buf[0] == '\r')
            break;

        if (sscanf(buf, " %c%d", &direction, &steps) != 2) {
            printf("Invalid input format\n");
            return 1;
        }

        int passes = 0;
        if (direction == 'L') {
            for (int i = 1; i <= steps; ++i) {
                dial = (dial - 1 + 100) % 100;
                if (dial == 0) ++passes;
            }
        } else if (direction == 'R') {
            for (int i = 1; i <= steps; ++i) {
                dial = (dial + 1) % 100;
                if (dial == 0) ++passes;
            }
        } else {
            printf("Invalid direction\n");
            return 1;
        }

        password += passes;
    }

    printf("Password: %d\n", password);
    return 0;
}
