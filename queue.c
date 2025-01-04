#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

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

int isValidTime(const char *time) {
    if (strlen(time) != 5 || time[2] != ':') return 0;
    if (!(time[0] >= '0' && time[0] <= '2' && time[1] >= '0' && time[1] <= '9') ||
        !(time[3] >= '0' && time[3] <= '5' && time[4] >= '0' && time[4] <= '9')) return 0;
    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int minute = (time[3] - '0') * 10 + (time[4] - '0');
    return (hour >= 0 && hour <= 24 && minute >= 0 && minute <= 59);
}

void addQueue(Queue *q, Penumpang p) {
    if (isFull(q)) {
        printf("Antrian penuh!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = p;
    printf("Penumpang %s berhasil ditambahkan ke antrian.\n", p.nama_penumpang);
}

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

Penumpang peek(Queue *q) {
    Penumpang p;
    if (isEmpty(q)) {
        printf("Antrian kosong!\n");
        return p;
    }
    return q->data[q->front];
}

void peekAll(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong!\n");
        return;
    }
    int i = q->front;
    while (1) {
        printf("ID: %d, Nama: %s, Jenis Antrian: %s, Waktu: %s, Status: %s\n",
               q->data[i].id_penumpang, q->data[i].nama_penumpang,
               q->data[i].jenis_antrian, q->data[i].waktu_kedatangan,
               q->data[i].status);
        if (i == q->rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
}