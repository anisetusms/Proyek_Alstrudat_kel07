#ifndef BANDARA_H
#define BANDARA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUEUE_SIZE 50

// Struktur Penumpang
typedef struct {
    char id_penumpang[20];
    char nama_penumpang[50];
    char nomor_penerbangan[10];
    char waktu_kedatangan[6]; // Format HH:MM
    char status[20];
} Passenger;

// Struktur Antrian
typedef struct {
    Passenger data[MAX_QUEUE_SIZE];
    int front, rear;
    int served_count;
} Queue;

// Fungsi-fungsi yang dideklarasikan
void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
int isDuplicate(Queue *q, const char *id_penumpang);
void addQueue(Queue *q, Passenger p);
Passenger delQueue(Queue *q);
Passenger peek(Queue *q);
void peekAll(Queue *q, const char *status_filter);
void logActivity(const char *message, Passenger *p);
void printHeader();
void printQueue(Queue *q);
void printStatistics(Queue *q, const char *queue_name);

#endif
