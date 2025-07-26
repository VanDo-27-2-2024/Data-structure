# QUEUE
### Implementaiton based on this https://www.youtube.com/watch?v=okr-XE8yTO8


## Operation
![alt text](image.png)

## Circualr-array based implementation vs Array based implementation
<img src="image-1.png" alt="Queue Operation" width="600"/>

## How to run the example
    gcc -o queue circular_array_based.c

## Memory leak testing with Valgrind tool
    valgrind --leak-check=full ./queue.out

![alt text](image-2.png)
