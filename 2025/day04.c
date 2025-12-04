#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_neighbors(char **grid, int row_count, int col_count, int r, int c) {
    int paper_rolls_count = 0;

    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nc >= 0 && nr < row_count && nc < col_count) {
            if (grid[nr][nc] == '@') paper_rolls_count++;
        }
    }

    return paper_rolls_count;
}

int main(void) {
    char **grid = NULL;
    char buf[1024] = {};

    int row_count = 0;
    int col_count = 0;

    printf("Paste your input: ");
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if (buf[0] == '\n' || buf[0] == '\r') break;

        size_t len = strlen(buf);
        if (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
            len--;
        } else if (len == 0) {
            continue;
        }

        if (row_count == 0) {
            col_count = (int)len;
        }

        grid = (char **)realloc(grid, (row_count + 1) * sizeof(char *));
        grid[row_count] = (char *)malloc((col_count + 1) * sizeof(char));
        strncpy(grid[row_count], buf, col_count);

        ++row_count;
    }

    int total_removed_count = 0;
    int rolls_removed_in_round = 0;
    int removable_cells[100][2];

    do {
        rolls_removed_in_round = 0;
        int removable_count = 0;

        for (int r = 0; r < row_count; ++r) {
            for (int c = 0; c < col_count; ++c) {
                if (grid[r][c] != '@') continue;

                int paper_rolls_count = check_neighbors(grid, row_count, col_count, r, c);
                if (paper_rolls_count < 4) {
                    removable_cells[removable_count][0] = r;
                    removable_cells[removable_count][1] = c;
                    removable_count++;
                }
            }
        }

        if (removable_count > 0) {
            rolls_removed_in_round = removable_count;
            total_removed_count += rolls_removed_in_round;

            for (int i = 0; i < removable_count; ++i) {
                int r = removable_cells[i][0];
                int c = removable_cells[i][1];
                grid[r][c] = 'x';
            }
        }
    } while (rolls_removed_in_round > 0);

    for (int r = 0; r < row_count; ++r) {
        free(grid[r]);
    }
    free(grid);
    grid = NULL;

    printf("Amount of paper rolls that can be removed: %d\n", total_removed_count);

    return 0;
}
