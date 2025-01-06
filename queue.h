#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE_SIZE 50

typedef struct {
    char id_penumpang[20]; // ID penumpang berupa alphanumeric
    char nama_penumpang[50];
    char jenis_antrian[20];
    char waktu_kedatangan[20];
    char status[20];
} Penumpang;

typedef struct {
    Penumpang data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

// Deklarasi fungsi
void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
int isIdExists(Queue *q, const char *id);
int isValidId(const char *id);
int isValidTime(const char *time);
void addQueue(Queue *q, Penumpang p);
Penumpang delQueue(Queue *q);
Penumpang peek(Queue *q);
void peekAll(Queue *q);

#endif
