#include "../include/include.h"

int main(int argc, char **argv)
{
    Matrix matrix = {.error = 0, .map_width = -1};
    parse_map(&matrix, argv[argc - 1]);
    if (matrix.error)
    {
        fprintf(stderr, "MAP ERROR");
        return 1;
    }
    print(matrix);
    matrix_free(&matrix);
    return 0;
}