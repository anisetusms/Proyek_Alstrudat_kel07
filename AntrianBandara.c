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

// Fungsi cek apakah queue kosong
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Fungsi cek apakah queue penuh
int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// Fungsi cek apakah ID penumpang sudah ada di queue
int isIdExists(Queue *q, int id) {
    if (isEmpty(q)) return 0;
    int i = q->front;
    while (1) {
        if (q->data[i].id_penumpang == id) return 1;
        if (i == q->rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    return 0;
}


// Fungsi menambahkan penumpang ke queue
void addQueue(Queue *q, Penumpang p) {
    if (isFull(q)) {
        printf("Antrian penuh!\n");
        return;
    }
    if (isIdExists(q, p.id_penumpang)) {
        printf("ID Penumpang %d sudah ada di antrian!\n", p.id_penumpang);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = p;
    printf("Penumpang %s berhasil ditambahkan ke antrian.\n", p.nama_penumpang);
}

// Fungsi menghapus penumpang dari queue
Penumpang delQueue(Queue *q) {
    Penumpang p;
    if (isEmpty(q)) {
        printf("Antrian kosong!\n");
        return p;
    }
    p = q->data[q->front];
    if (q->front == q->rear) {
        initQueue(q);
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }
    return p;
}

// Fungsi melihat penumpang terdepan di queue
Penumpang peek(Queue *q) {
    Penumpang p;
    if (isEmpty(q)) {
        printf("Antrian kosong!\n");
        return p;
    }
    return q->data[q->front];
}