#include "../include/include.h"

int directions[2][4] = {{0, -1, 1, 0}, {-1, 0, 0, 1}};

char *my_getline(char *res, int fd, Matrix *matrix)
{
    char c;
    int i = 0, r;
    while ((r = read(fd, &c, 1)) >= 0)
    {
        if (c == '\n' || r == 0)
        {
            if (matrix->map_width != -1 && i != matrix->map_width)
                matrix->error = 1;
            break;
        }
        res[i++] = c;
    }
    if (i == 0)
        matrix->error = 1;
    else
        res[i] = '\0';
    return res;
}

void get_size(char *line, Matrix *matrix)
{
    int height = atoi(line);
    while (*line != 'x') line++;
    int width = atoi(++line);
    matrix->map_height = height;
    matrix->map_width = width;
    while (isdigit(*line)) line++;
    for (int i = 0; i < 5; i++) matrix->chars[i] = *line++;
}

void get_points(Matrix *matrix)
{
    for (int y = 0; y < matrix->map_height; y++)
        for (int x = 0; x < matrix->map_width; x++)
        {
            if (!(x == 0 || x == matrix->map_width - 1 || y == 0 ||
                  y == matrix->map_height - 1))
                continue;
            if (matrix->map[y][x].cell == matrix->chars[3])
                add_point(matrix, x, y, start);
            if (matrix->map[y][x].cell == matrix->chars[4])
                add_point(matrix, x, y, finish);
        }
    if (matrix->start.x == -1 || !matrix->finish) matrix->error = 1;
}

int is_possible(int y, int x, Matrix matrix)
{
    return (y > -1 && y < matrix.map_height && x < matrix.map_width && x > -1);
}

void print(Matrix matrix)
{
    printf("%dx%d%s\n", matrix.map_height, matrix.map_width, matrix.chars);
    for (int y = 0; y < matrix.map_height; y++)
    {
        for (int x = 0; x < matrix.map_width; x++)
            printf("%c", matrix.map[y][x].cell);
        printf("\n");
    }
    printf("%d STEPS!", matrix.steps);
}

Point shortest_finish(Matrix *matrix)
{
    Point p;
    matrix->steps = -1;
    Finish_point *temp = matrix->finish;
    while (temp != NULL)
    {
        if (matrix->steps == -1 ||
            matrix->steps > matrix->map[temp->y][temp->x].visited)
        {
            p.x = temp->x;
            p.y = temp->y;
            matrix->steps = matrix->map[p.y][p.x].visited;
        }
        temp = temp->next;
    }
    return p;
}

void road(Matrix *matrix)
{
    Point p = shortest_finish(matrix);
    while (matrix->map[p.y][p.x].visited != 0)
    {
        for (int i = 0; i < 4; i++)
        {
            int way_x = p.x + directions[0][i];
            int way_y = p.y + directions[1][i];
            if (is_possible(way_y, way_x, *matrix) &&
                matrix->map[p.y][p.x].visited - 1 ==
                    matrix->map[way_y][way_x].visited)
            {
                if (matrix->map[way_y][way_x].cell != matrix->chars[3])
                    matrix->map[way_y][way_x].cell = matrix->chars[2];
                p.y = way_y;
                p.x = way_x;
                break;
            }
        }
    }
}

void update(Matrix *matrix, Queue *queue, Queue *new, int col, int row,
            int distance)
{
    matrix->map[col][row].visited = distance;
    new = queue;
    while (new->next != NULL) new = new->next;
    new->next = malloc(sizeof(Queue));
    new->next->distance = distance;
    new->next->point.x = row;
    new->next->point.y = col;
    new->next->next = NULL;
}

int finished(Queue curr, Matrix matrix)
{
    Finish_point *temp = matrix.finish;
    while (temp != NULL)
    {
        if (curr.point.x == temp->x && curr.point.y == temp->y) return 1;
        temp = temp->next;
    }
    return 0;
}

void algorithm(Matrix matrix)
{
    if (matrix.start.x == -1 || matrix.finish == NULL) return;
    Queue *queue = malloc(sizeof(Queue));
    Queue *new = NULL;
    queue->distance = 0;
    queue->point = matrix.start;
    queue->next = NULL;
    while (queue)
    {
        Queue *curr = queue;
        if (finished(*curr, matrix)) break;
        for (int i = 0; i < 4; i++)
        {
            int row = curr->point.x + directions[0][i];
            int col = curr->point.y + directions[1][i];
            if (is_possible(col, row, matrix) &&
                (matrix.map[col][row].cell == matrix.chars[1] ||
                 matrix.map[col][row].cell == matrix.chars[4]) &&
                matrix.map[col][row].visited == 0)
                update(&matrix, queue, new, col, row, curr->distance + 1);
        }
        queue = pop(queue);
    }
    queue_free(queue);
}

void parse_map(Matrix *matrix, char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *row = (char *)malloc(500);
    get_size(my_getline(row, fd, matrix), matrix);
    if (matrix->error) return;
    matrix->map = (Map **)malloc(matrix->map_height * sizeof(Map *));
    for (int y = 0; y < matrix->map_height; y++)
    {
        matrix->map[y] = (Map *)calloc(matrix->map_width, sizeof(Map));
        row = my_getline(row, fd, matrix);
        for (size_t i = 0; i < strlen(row); i++)
            matrix->map[y][i].cell = row[i];
        if (matrix->error) return;
    }
    matrix->start.x = -1;
    get_points(matrix);
    if (matrix->error) return;
    algorithm(*matrix);
    road(matrix);
    free(row);
}
