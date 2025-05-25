#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;
    Node** table;
} HashTable;

// hash function menggunakan division method; sumber http://www.cse.yorku.ca/~oz/hash.html
unsigned int hashFunction(const char* key, int tableSize) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % tableSize;
}

HashTable* createHashTable(int size) {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if (ht == NULL) {
        perror("Gagal mengalokasikan memori untuk HashTable");
        exit(EXIT_FAILURE);
    }
    ht->size = size;
    ht->table = (Node**)calloc(size, sizeof(Node*));
    if (ht->table == NULL) {
        perror("Gagal mengalokasikan memori untuk array tabel");
        free(ht);
        exit(EXIT_FAILURE);
    }
    return ht;
}

void insertValue(HashTable* ht, const char* value) {
    unsigned int index = hashFunction(value, ht->size);

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Gagal mengalokasikan memori untuk Node baru");
        exit(EXIT_FAILURE);
    }

    newNode->value = (char*)malloc(strlen(value) + 1);
    if (newNode->value == NULL) {
        perror("Gagal mengalokasikan memori untuk nama ilmiah");
        free(newNode);
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->value, value);

    newNode->next = NULL;

    // lakukan pengecekan apakah index sudah terisi apa belum, apabila terjadi collision simpan value ke node selanjutnya
    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        newNode->next = ht->table[index];
        ht->table[index] = newNode;
        printf("Kolisi terdeteksi untuk '%s'. Ditambahkan ke rantai di indeks %u.\n", value, index);
    }
}

char* searchValue(HashTable* ht, const char* value) {
    unsigned int index = hashFunction(value, ht->size);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (strcmp(current->value, value) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void printHashTable(HashTable* ht) {
    printf("\n--- Isi Hash Table ---\n");
    for (int i = 0; i < ht->size; i++) {
        printf("Indeks %d:", i);
        Node* current = ht->table[i];
        if (current == NULL) {
            printf(" Kosong\n");
        } else {
            while (current != NULL) {
                printf(" --> [%s]", current->value);
                current = current->next;
            }
            printf("\n");
        }
    }
    printf("----------------------\n");
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < ht->size; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* temp = current;
            free(temp->value);
            current = current->next;
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
    printf("\nHash Table telah dibebaskan dari memori.\n");
}

int main() {
    int table_size = 101;
    HashTable* hashTable = createHashTable(table_size);

    printf("--- Menyisipkan Data ---\n");
    insertValue(hashTable, "Canis familiaris");
    insertValue(hashTable, "Dicerorhinus Sumatrensis");
    insertValue(hashTable, "Periplaneta Americana");
    insertValue(hashTable, "Columba Livia");
    insertValue(hashTable, "Elephas Maximus");
    insertValue(hashTable, "Loligo Pealii");
    insertValue(hashTable, "Mabouya Multifasciata");

    printHashTable(hashTable);

    printf("\n--- Mencari Nama Ilmiah Hewan ---\n");
    printf("Lakukan pencarian untuk data 'Columba Livia'\n");
    char* foundScientificName = searchValue(hashTable, "Columba Livia");
    if (foundScientificName) {
        printf("Ditemukan: '%s'\n", foundScientificName);
    } else {
        printf("'%s' tidak ditemukan.\n", "Columba Livia");
    }

    printf("Lakukan pencarian untuk data 'Panthera Tigris'\n");
    foundScientificName = searchValue(hashTable, "Panthera Tigris");
    if (foundScientificName) {
        printf("Ditemukan: '%s'\n", foundScientificName);
    } else {
        printf("'%s' tidak ditemukan.\n", "Panthera Tigris");
    }

    freeHashTable(hashTable);

    return 0;
}