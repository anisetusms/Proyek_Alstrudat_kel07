#include "bandara.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// Fungsi untuk menginisialisasi antrian
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
    q->served_count = 0;
}

// Mengecek apakah antrian kosong
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Mengecek apakah antrian penuh
int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// Mengecek apakah ID penumpang sudah ada di antrian
int isDuplicate(Queue *q, const char *id_penumpang) {
    if (isEmpty(q)) return 0; // Antrian kosong, tidak ada duplikasi
    int i = q->front;
    while (1) {
        if (strcmp(q->data[i].id_penumpang, id_penumpang) == 0) {
            return 1; // ID duplikat ditemukan
        }
        if (i == q->rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    return 0; // Tidak ada duplikasi
}

// Menambahkan penumpang ke antrian dengan mengurutkan berdasarkan waktu kedatangan
void addQueue(Queue *q, Passenger p) {
    if (isFull(q)) {
        printf("Error: Antrian penuh!\n");
        return;
    }

    if (isDuplicate(q, p.id_penumpang)) {
        printf("Error: ID Penumpang %s sudah ada dalam antrian.\n", p.id_penumpang);
        return;
    }

    // Menambahkan penumpang dan menyortir berdasarkan waktu kedatangan
    if (isEmpty(q)) {
        q->front = q->rear = 0;
        q->data[q->rear] = p;
    } else {
        int i = q->rear;
        while (i != q->front - 1 && strcmp(p.waktu_kedatangan, q->data[(i + 1) % MAX_QUEUE_SIZE].waktu_kedatangan) < 0) {
            i = (i - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
        }
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        for (int j = q->rear; j != i; j = (j - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE) {
            q->data[j] = q->data[(j - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE];
        }
        q->data[i] = p;
    }

    printf("Sukses: Penumpang %s berhasil ditambahkan ke antrian.\n", p.nama_penumpang);

    // Log activity saat penumpang ditambahkan ke antrian
    logActivity("Penumpang ditambahkan ke antrian.", &p);
}

// Menghapus penumpang dari antrian
Passenger delQueue(Queue *q) {
    Passenger p = {"", "", "", "", ""};
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

    q->served_count++;
    printf("Penumpang %s dilayani.\n", p.nama_penumpang);

    // Log activity saat penumpang dilayani
    logActivity("Penumpang dilayani.", &p);

    return p;
}

// Melihat penumpang pertama di antrian
Passenger peek(Queue *q) {
    Passenger p = {"", "", "", "", ""};
    if (isEmpty(q)) {
        printf("Antrian kosong!\n");
    } else {
        p = q->data[q->front];
    }
    return p;
}

// Menampilkan semua penumpang di antrian, diurutkan berdasarkan waktu kedatangan
void peekAll(Queue *q, const char *status_filter) {
    if (isEmpty(q)) {
        printf("Antrian kosong!\n");
        return;
    }

    // Menyortir berdasarkan waktu kedatangan (ascending order)
    int size = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE + 1;
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            int idx_i = (q->front + i) % MAX_QUEUE_SIZE;
            int idx_j = (q->front + j) % MAX_QUEUE_SIZE;
            if (strcmp(q->data[idx_i].waktu_kedatangan, q->data[idx_j].waktu_kedatangan) > 0) {
                // Swap data[i] and data[j] if out of order
                Passenger temp = q->data[idx_i];
                q->data[idx_i] = q->data[idx_j];
                q->data[idx_j] = temp;
            }
        }
    }

    printHeader();
    int i = q->front;
    while (1) {
        if (strcmp(status_filter, "ALL") == 0 || strcmp(q->data[i].status, status_filter) == 0) {
            // Menampilkan semua data penumpang, termasuk No. Penerbangan, waktu, dan status
            printf("%-10s %-15s %-15s %-10s %-15s\n", q->data[i].id_penumpang, q->data[i].nama_penumpang, q->data[i].nomor_penerbangan, q->data[i].waktu_kedatangan, q->data[i].status);
        }
        if (i == q->rear) break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
}

// Menampilkan header tabel
void printHeader() {
    printf("=================================================================================\n");
    printf("ID        Nama            No. Penerbangan     Waktu      Status\n");
    printf("=================================================================================\n");
}

// Menampilkan antrian
void printQueue(Queue *q) {
    if (!isEmpty(q)) {
        peekAll(q, "ALL");
    } else {
        printf("Tidak ada penumpang dalam antrian.\n");
    }
}

// Menampilkan statistik antrian
void printStatistics(Queue *q, const char *queue_name) {
    // Mengecek apakah antrian kosong
    if (isEmpty(q)) {
        printf("Statistik %s:\n", queue_name);
        printf("Jumlah penumpang dalam antrian: 0\n");
        printf("Jumlah total penumpang yang telah dilayani: %d\n", q->served_count);
    } else {
        printf("Statistik %s:\n", queue_name);
        // Jumlah penumpang dalam antrian
        int total_in_queue = (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE + 1;
        printf("Jumlah penumpang dalam antrian: %d\n", total_in_queue);
        printf("Jumlah total penumpang yang telah dilayani: %d\n", q->served_count);
    }
}

// Menyimpan log aktivitas
void logActivity(const char *message, Passenger *p) {
    FILE *logFile = fopen("activity_log.txt", "a");
    if (!logFile) {
        perror("Gagal membuka file log");
        return;
    }

    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    // Menyimpan log dengan detail aktivitas dan data penumpang
    fprintf(logFile, "[%04d-%02d-%02d %02d:%02d:%02d] %s ID: %s, Nama: %s, No. Penerbangan: %s, Waktu Kedatangan: %s, Status: %s\n",
            local->tm_year + 1900, local->tm_mon + 1, local->tm_mday,
            local->tm_hour, local->tm_min, local->tm_sec,
            message, p->id_penumpang, p->nama_penumpang, p->nomor_penerbangan, p->waktu_kedatangan, p->status);

    fclose(logFile);
}
