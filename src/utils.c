#include "../include/include.h"

Point new_point(int x, int y)
{
    Point res;
    res.x = x;
    res.y = y;
    return res;
}

void new_finish_point(int x, int y, Finish_point *res)
{
    res->x = x;
    res->y = y;
    res->next = NULL;
}

void add_point(Matrix *matrix, int x, int y, Type type)
{
    if (type == start)
        matrix->start = new_point(x, y);
    else
    {
        Finish_point *res = malloc(sizeof(Finish_point));
        if (matrix->finish == NULL)
        {
            new_finish_point(x, y, res);
            matrix->finish = res;
        }
        else
        {
            Finish_point *temp = matrix->finish;
            while (temp->next != NULL) temp = temp->next;
            new_finish_point(x, y, res);
            temp->next = res;
        }
    }
}

void push(Queue *main, Queue *new)
{
    if (main == NULL)
    {
        main = new;
        return;
    }
    Queue *last = main;
    while (last->next != NULL) last = last->next;
    last->next = new;
    last->next->next = NULL;
}

Queue *pop(Queue *queue)
{
    Queue *prev = queue;
    if (queue != NULL) queue = queue->next;
    free(prev);
    return queue;
}

void queue_free(Queue *queue)
{
    Queue *temp;
    while (queue != NULL)
    {
        temp = queue;
        queue = queue->next;
        free(temp);
    }
}

void matrix_free(Matrix *matrix)
{
    for (int y = 0; y < matrix->map_height; y++) free(matrix->map[y]);
    free(matrix->map);

    Finish_point *temp = NULL;
    while (matrix->finish)
    {
        temp = matrix->finish;
        matrix->finish = matrix->finish->next;
        free(temp);
    }
}
