#include "stdio.h"
#include "stdlib.h"

#define QUEUE_SIZE 100

/*
Operation:
    - Enqueue O(1)
        + Insert new elements to rear position
    + Dequeue O(1)
    + IsEmpty O(1)
*/

typedef enum {
    INT,
    FLOAT,
    CHAR
} data_type;

typedef struct data
{
    void* data;
    data_type type;
} data_t;

typedef struct queue
{
    int front;
    int rear;
    int size;
    data_t** queue_array; // instead of <data_t* queue_array[QUEUE_SIZE]> -> for dynamic change size (based on user purpose not HARD CODE)
} queue_t;

queue_t* init_queue(int size)
{
    queue_t* queue = malloc(sizeof(queue_t));
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;
    queue->queue_array = (data_t**)(malloc(size * sizeof(data_t*)));

    return queue;
}

int is_queue_empty(const queue_t* queue)
{
    if (queue->front == -1 && queue->rear == -1)
    {
        return 1; // queue is empty
    }

    return 0; // queue is NOT empty
}

int enqueue(queue_t* queue, void* data, data_type type)
{
    if (((queue->rear + queue->size + 1) % queue->size) == queue->front)
    {
        printf("Queue is full !!!\n");
        return -1;
    }

    data_t* new_data = malloc(sizeof(data_t));
    new_data->type = type;

    if (type == INT)
    {
        new_data->data = malloc(sizeof(int));
        *(int*)new_data->data = *(int*)data;
    }
    else if (type == FLOAT)
    {
        new_data->data = malloc(sizeof(float));
        *(float*)new_data->data = *(float*)data;
    }
    else if (type == CHAR)
    {
        new_data->data = malloc(sizeof(char));
        *(char*)new_data->data = *(char*)data;
    }
    else
    {
        printf("Invalid type !!!\n");

        free(new_data->data);
        new_data->data = NULL;
        free(new_data);
        new_data = NULL;

        return -1;
    }

    if (is_queue_empty(queue))
    {
        queue->front = queue->rear = 0;
    }
    else
    {
        queue->rear = (queue->rear + 1) % queue->size;
    }

    queue->queue_array[queue->rear] = new_data;

    printf("Sucessfully insert new data to queue !!!\n");
    return 0;
}

data_t* dequeue(queue_t* queue)
{
    if (is_queue_empty(queue))
    {
        printf("Queue is empty !!!\n");
        return NULL;
    }

    data_t* dt = queue->queue_array[queue->front];

    if (queue->front == queue->rear) // In case there is only 1 data
    {
        queue->front = -1;
        queue->rear = -1;

    }
    else // more than 1 data on the queue
    {
        queue->front = (queue->front + 1) % queue->size;
    }

    return dt;
}

void destroy_queue(queue_t* queue)
{
    free(queue->queue_array);
    free(queue);
}

int main()
{
    queue_t* q = init_queue(4);

    int test[] = {1,2,3,4,5};
    char a = 'V';
    float f = 19.9;

    enqueue(q, &test[0], INT);
    enqueue(q, &test[1], INT);
    enqueue(q, &a, CHAR);
    enqueue(q, &f, FLOAT);
    enqueue(q, &test[4], INT);
    enqueue(q, &test[2], INT);
    enqueue(q, &test[3], INT);

    while (!is_queue_empty(q))
    {
        data_t* dat;

        dat = dequeue(q);

        if (dat->type == INT)
        {
            // dat->data = (int*)dat->data;
            printf("%d\n", *(int*)dat->data);
        }
        else if (dat->type == FLOAT)
        {
            printf("%.2f\n", *(float*)dat->data);
        }
        else if (dat->type == CHAR)
        {
            printf("%c\n", *(char*)dat->data);
        }
        else
        {
            printf("Invalid type !!!\n");
        }

        free(dat->data);
        free(dat);
    }

    destroy_queue(q);
    return 0;
}

