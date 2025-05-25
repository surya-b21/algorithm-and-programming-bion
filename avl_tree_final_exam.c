#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    char nama[50];
    int lama_pengerjaan;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

Node* createNode(int id, const char* nama, int lama) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memori gagal dialokasikan!\n");
        exit(EXIT_FAILURE);
    }
    node->id = id;
    strcpy(node->nama, nama);
    node->lama_pengerjaan = lama;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insertBuildingType(Node* node, int id, const char* nama, int lama) {
    if (node == NULL) return createNode(id, nama, lama);

    if (lama < node->lama_pengerjaan) node->left = insertBuildingType(node->left, id, nama, lama);
    else if (lama > node->lama_pengerjaan) node->right = insertBuildingType(node->right, id, nama, lama);
    else {
        if (id == node->id) {
            printf("Peringatan: Tipe bangunan dengan ID %d dan lama pengerjaan %d sudah ada.\n", id, lama);
            return node;
        } else {
            node->right = insertBuildingType(node->right, id, nama, lama);
        }
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && lama < node->left->lama_pengerjaan) return rightRotate(node);

    if (balance < -1 && lama > node->right->lama_pengerjaan) return leftRotate(node);

    if (balance > 1 && lama > node->left->lama_pengerjaan) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && lama < node->right->lama_pengerjaan) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void showBuildingType(Node* root) {
    if (root != NULL) {
        showBuildingType(root->left);
        printf("Nama: %s, \t Lama Pengerjaan: %3d hari\n", root->nama, root->lama_pengerjaan);
        showBuildingType(root->right);
    }
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* finishBuildingType(Node* root, int lama_pengerjaan_to_delete) {
    if (root == NULL) return root;

    if (lama_pengerjaan_to_delete < root->lama_pengerjaan) root->left = finishBuildingType(root->left, lama_pengerjaan_to_delete);
    else if (lama_pengerjaan_to_delete > root->lama_pengerjaan) root->right = finishBuildingType(root->right, lama_pengerjaan_to_delete);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);

            root->id = temp->id;
            strcpy(root->nama, temp->nama);
            root->lama_pengerjaan = temp->lama_pengerjaan;

            root->right = finishBuildingType(root->right, temp->lama_pengerjaan);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int next_id = 1;

    printf("--- Menambahkan Tipe Bangunan ---\n");
    root = insertBuildingType(root, next_id++, "Rumah Tipe 36", 120);
    root = insertBuildingType(root, next_id++, "Ruko 2 Lantai", 180);
    root = insertBuildingType(root, next_id++, "Apartemen Studio", 90);
    root = insertBuildingType(root, next_id++, "Gudang Kecil", 60);
    root = insertBuildingType(root, next_id++, "Rumah Tipe 45", 150);
    root = insertBuildingType(root, next_id++, "Kios Komersial", 75);
    root = insertBuildingType(root, next_id++, "Rumah Tipe 70", 200);
    root = insertBuildingType(root, next_id++, "Apartemen 2BR", 130);

    printf("\n--- Menampilkan daftar proyek bangunan yang sedang dalam pengerjaan ---\n");
    showBuildingType(root);

    printf("\n--- Menghapus tipe bangunan yang telah selesai dibangun --- \n");
    
    printf("Menghapus 'Gudang Kecil' (Lama Pengerjaan: 60 hari)\n");
    root = finishBuildingType(root, 60);
    printf("Menghapus 'Kios Komersial' (Lama Pengerjaan: 75 hari)\n");
    root = finishBuildingType(root, 75);

    printf("\n--- Menampilkan daftar proyek bangunan setelah penghapusan ---\n");
    showBuildingType(root);

    freeTree(root);

    return 0;
}