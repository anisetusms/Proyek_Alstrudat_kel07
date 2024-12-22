#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 50

typedef struct {
    int id_penumpang;
    char nama_penumpang[50];
    char jenis_antrian[20];
    char waktu_kedatangan[20];
    char status[20];
} Penumpang;

typedef struct {
    Penumpang data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

// Fungsi inisialisasi queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}