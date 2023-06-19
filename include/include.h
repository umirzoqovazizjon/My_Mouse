#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

typedef struct _struct_point
{
    int x;
    int y;
} Point;

typedef struct _finish_point
{
    int x;
    int y;
    struct _finish_point *next;
} Finish_point;

typedef struct _struct_queue
{
    Point point;
    int distance;
    struct _struct_queue *next;
} Queue;

typedef struct _struct_map
{
    char cell;
    int visited;
} Map;

typedef struct _struct_matrix
{
    int map_height;
    int map_width;
    Point start;
    Finish_point *finish;
    Map **map;
    int steps;
    int error;
    char chars[5];
} Matrix;

typedef enum type
{
    start,
    finish
} Type;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void algorithm(Matrix);
int finished(Queue, Matrix);
void get_points(Matrix *);
void get_size(char *, Matrix *);
int is_possible(int, int, Matrix);
char *my_getline(char *, int, Matrix *);
void parse_map(Matrix *, char *);
void print(Matrix);
void road(Matrix *);
Point shortest_finish(Matrix *);
void update(Matrix *, Queue *, Queue *, int, int, int);

#endif  // !FUNCTIONS_H

#ifndef UTILS_H
#define UTILS_H

void add_point(Matrix *, int, int, Type);
void matrix_free(Matrix *);
void new_finish_point(int, int, Finish_point *);
Point new_point(int, int);
Queue *pop(Queue *);
void push(Queue *, Queue *);
void queue_free(Queue *);

#endif  // !UTILS_H