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
    data_t* queue_array[QUEUE_SIZE];
} queue_t;

queue_t* init_queue(int size)
{
    queue_t* queue = malloc(sizeof(queue_t));
    queue->front = -1;
    queue->rear = -1;
    queue->size = size;

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
    void* dt;

    if (is_queue_empty(queue))
    {
        queue->front = 0;
        queue->rear = 0;

        if (type == INT)
        {
            dt = malloc(sizeof(int));
        }
        else if (type == FLOAT)
        {
            dt = malloc(sizeof(float));
        }
        else if (type == CHAR)
        {
            dt = malloc(sizeof(char));
        }
        else
        {
            printf("Invalid type !!!\n");
            return -1;
        }

        queue->queue_array[queue->front] = malloc(sizeof(data_t));
        queue->queue_array[queue->front]->type = type;
        queue->queue_array[queue->front]->data = dt;
    }
    else if (((queue->rear + QUEUE_SIZE + 1) % QUEUE_SIZE) == queue->front)
    {
        printf("Queue is full !!!\n");
        return -1;
    }
    else
    {
        if (type == INT)
        {
            dt = malloc(sizeof(int));
        }
        else if (type == FLOAT)
        {
            dt = malloc(sizeof(float));
        }
        else if (type == CHAR)
        {
            dt = malloc(sizeof(char));
        }
        else
        {
            printf("Invalid type !!!\n");
            return -1;
        }

        queue->queue_array[queue->front] = malloc(sizeof(data_t));
        queue->queue_array[queue->front]->type = type;
        queue->rear = (queue->rear + 1) % QUEUE_SIZE;
        queue->queue_array[queue->rear] = dt;
    }

    printf("Sucessfully insert new data to queue !!!\n");
    return 0;
}

data_t* dequeue(queue_t* queue)
{
    data_t* dt = malloc(sizeof(data_t));

    if (is_queue_empty(queue))
    {
        printf("Queue is empty !!!\n");
        return NULL;
    }
    else if (queue->front == queue->rear) // In case there is only 1 data
    {
        // dt->data = queue->queue_array[queue->front]->data;
        // dt->type = queue->queue_array[queue->front]->type;

        dt = queue->queue_array[queue->front];

        // free(queue->queue_array[queue->front]->data);
        free(queue->queue_array[queue->front]);

        queue->front = -1;
        queue->rear = -1;

    }
    else // more than 1 data on the queue
    {
        dt->data = queue->queue_array[queue->front]->data;
        dt->type = queue->queue_array[queue->front]->type;

        // free(queue->queue_array[queue->front]->data);
        free(queue->queue_array[queue->front]);

        queue->front = (queue->front + 1) % QUEUE_SIZE;
    }

    return dt;
}

int main()
{
    queue_t* q = init_queue(QUEUE_SIZE);

    int test[] = {1,2,3,4,5};

    enqueue(q, &test[0], INT);
    enqueue(q, &test[1], INT);
    enqueue(q, &test[2], INT);
    enqueue(q, &test[3], INT);
    enqueue(q, &test[4], INT);

    for (int i = 0; i < (q->rear - q->front + 1); i++)
    {
        printf("q->rear: %d\n", q->rear);
        printf("q->front: %d\n", q->front);
        data_t* dat;
        dat = dequeue(q);

        if (dat->type == INT)
        {
            // dat->data = (int*)dat->data;
            printf("%d\n", *(int*)dat->data);
        }
    }
}

