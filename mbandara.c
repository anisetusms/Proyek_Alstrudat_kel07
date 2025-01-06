#include "bandara.h"

int main() {
    Queue checkInQueue, boardingQueue;
    initQueue(&checkInQueue);
    initQueue(&boardingQueue);

    int choice;
    do {
        printf("\n=== Sistem Antrian Bandara ===\n");
        printf("1. Tambah ke Antrian Check-in\n");
        printf("2. Layani Penumpang Check-in\n");
        printf("3. Layani Penumpang di Gerbang Keberangkatan\n");
        printf("4. Lihat Semua Antrian Check-in\n");
        printf("5. Lihat Semua Antrian Gerbang Keberangkatan\n");
        printf("6. Statistik Antrian\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Passenger p;
                printf("Masukkan ID Penumpang: ");
                scanf("%s", p.id_penumpang);
                printf("Masukkan Nama Penumpang: ");
                getchar(); // untuk membersihkan newline dari input sebelumnya
                fgets(p.nama_penumpang, sizeof(p.nama_penumpang), stdin);
                p.nama_penumpang[strcspn(p.nama_penumpang, "\n")] = '\0'; // Hapus newline
                printf("Masukkan Nomor Penerbangan: ");
                scanf("%s", p.nomor_penerbangan);
                printf("Masukkan Waktu Kedatangan (HH:MM): ");
                scanf("%s", p.waktu_kedatangan);
                strcpy(p.status, "Menunggu");
                addQueue(&checkInQueue, p);
                break;
            }
            case 2: {
                if (!isEmpty(&checkInQueue)) {
                    Passenger served = delQueue(&checkInQueue);
                    strcpy(served.status, "Check-in Selesai");
                    char log_message[128];
                    snprintf(log_message, sizeof(log_message), "Penumpang ID: %s dilayani di Check-in", served.id_penumpang);
                    logActivity(log_message, &served);  // Log activity dengan data lengkap penumpang
                    addQueue(&boardingQueue, served);  // Pindah ke boarding queue
                } else {
                    printf("Tidak ada penumpang yang dapat dilayani.\n");
                }
                break;
            }
            case 3: {
                if (!isEmpty(&boardingQueue)) {
                    Passenger served = delQueue(&boardingQueue);
                    strcpy(served.status, "Boarding Selesai");
                    char log_message[128];
                    snprintf(log_message, sizeof(log_message), "Penumpang ID: %s dilayani di Boarding", served.id_penumpang);
                    logActivity(log_message, &served);  // Log activity dengan data lengkap penumpang
                } else {
                    printf("Tidak ada penumpang yang dapat dilayani di boarding.\n");
                }
                break;
            }
            case 4:
                printQueue(&checkInQueue);
                break;
            case 5:
                printQueue(&boardingQueue);
                break;
            case 6:
                printStatistics(&checkInQueue, "Check-in");
                printStatistics(&boardingQueue, "Boarding");
                break;
            case 0:
                printf("Terima kasih! Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
