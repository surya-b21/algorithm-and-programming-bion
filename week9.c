#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct book {
    char *kode;
    char *nama;
    char *jenis;
    int harga;
} Book;

const char database[] = "databuku.txt";

// read all saved book
void readSavedBooks(Book **books, FILE *fptr)
{
    if (access(database, F_OK) != 0) {
        // creating file if file doesn exist
        fptr = fopen(database, "w");
    } else {
        // read data from file, then insert it to array of struct
        fptr = fopen(database, "r");

        char *line = malloc(256 * sizeof(char));
        int index = 0;
        while (fgets(line, 256, fptr) != NULL) {
            // Remove newline character at the end of the line (if present)
            line[strcspn(line, "\n")] = '\0';

            Book row;
            char *s = strtok(line, "|");
            int i = 0;
            while (s != NULL) {
                switch (i)
                {
                case 0:
                    row.kode = s;
                    break;

                case 1:
                    row.nama = s;
                    break;

                case 2:
                    row.jenis = s;
                    break;

                case 3:
                    row.harga = atoi(s);
                    break;

                default:
                    break;
                }

                s = strtok(NULL, "|");
                i++;
            }

            books[index] = &row;

            index++;
        }
    }

    fclose(fptr);
}

void addNewBook(Book **books)
{
    Book newBook;
    
    char kode[20];
    fgets(kode, sizeof(kode), stdin);
    printf("Masukkan kode buku : "); 
    fgets(kode, sizeof(kode), stdin);
    kode[strcspn(kode, "\n")] = '\0';
    newBook.kode = kode;

    char nama[20];
    printf("Masukkan nama buku : "); 
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = '\0';
    newBook.nama = nama;

    char jenis[20];
    printf("Masukkan jenis buku : "); 
    fgets(jenis, sizeof(jenis), stdin);
    jenis[strcspn(jenis, "\n")] = '\0';
    newBook.jenis = jenis;

    int harga;
    printf("Masukkan harga buku : "); 
    scanf("%d", &harga);
    newBook.harga = harga;
    
    // find lastIndex of array;
    int index = 0;
    while (books[index]->kode != NULL) {
        index++;
    }

    books[index] = &newBook;
}

int main()
{
    FILE *fptr;
    Book **books = malloc(10 * sizeof(Book*));
    for (int i = 0; i < 10; i++) {
        books[i] = malloc(sizeof(Book));
    }

    readSavedBooks(books, fptr);
    int choice;
    do
    {
        printf("1. Input\n2. View History\n3. View Buku\n4. Delete History\n5. Delete Buku\n6. Exit\n");
        printf("Silahkan pilih menu : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addNewBook(books);
            break;

        default:
            puts("Invliad choice");
            exit(1);
        }
    } while (choice != 6);

    return 0;
}