#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    int employeeID;
    char fullName[31];
    char bornPlace[31];
    char bornDate[11];
    char position[51];
} Employee;

typedef struct node
{
    Employee employee;
    struct node *next;
} Node;

Node *head = NULL;

// function for validate employee id
bool validateEmployeeID(int id)
{
    if (id >= 10000 && id <= 99999)
    {
        return true;
    }
    return false;
}

// function for validate length of string
bool validateStringLength(const char *str, int maxLength)
{
    if (strlen(str) <= maxLength)
    {
        return true;
    }

    return false;
}

// Function to clear input buffer
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// bubble sort for linked list
void bubblSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// push employee to linked list
void push(Employee employee)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->employee = employee;

    if (head == NULL)
    {
        head = node;
    }
    else
    {
        node->next = head;
        head = node;
    }
}

// delete employee from linked list by employee id
void pop(int employeeId)
{
    if (head == NULL)
        return;

    // find employee id in linked list
    Node *current = head;
    while (current != NULL)
    {
        Employee employee = current->employee;

        if (employee.employeeID == employeeId) {
            if (current == head) {
                Node *temp = current;
                head = current->next;

                free(temp);
            } else {
                // find node before current node
                Node *before = head;
                while (before != NULL)
                {
                    if (before->next == current) break;
                    before = before->next;
                }
                
                before->next = current->next;
                free(current);
            }

            break;
        }

        current = current->next;
    }
}

void resetLinkedList()
{
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;

        free(temp);
    }
}

// show linked list
void display()
{
    Node *start = head;
    int arrayLength = 0;

    if (start == NULL)
    {
        printf("Database is empty\n");
    }
    else
    {
        // get size of linked list
        while (start != NULL)
        {
            arrayLength += 1;
            start = start->next;
        }

        int employeeIds[arrayLength];
        start = head;
        for (int i = 0; i < arrayLength; i++)
        {
            Employee employee = start->employee;
            employeeIds[i] = employee.employeeID;

            start = start->next;
        }

        bubblSort(employeeIds, arrayLength);

        puts("===========================");
        for (int i = 0; i < arrayLength; i++)
        {
            start = head;
            while (start != NULL)
            {
                Employee employee = start->employee;

                if (employee.employeeID == employeeIds[i])
                {
                    printf("Employee ID: %d\n", employee.employeeID);
                    printf("Nama Lengkap: %s\n", employee.fullName);
                    printf("Tempat Lahir: %s\n", employee.bornPlace);
                    printf("Tanggal Lahir: %s\n", employee.bornDate);
                    printf("Jabatan: %s\n", employee.position);

                    break;
                }

                start = start->next;
            }

            puts("===========================");
        }
    }
}

int main()
{
    bool exit = false;
    int choice = 0;
    int employeeId;
    int employeeCount;

    do
    {
        puts("1. Push data karyawan");
        puts("2. Menampilkan data karyawan");
        puts("3. Hapus data karyawan berdasarkan employee id");
        puts("4. Hapus semua data karyawan");
        puts("5. Keluar program");
        printf("Silahkan pilih menu : \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Masukkan jumlah employee yang akan dimasukkan : \n");
            scanf("%d", &employeeCount);

            // validate data can be input only 5
            if (employeeCount > 5)
            {
                puts("Maksimal jumlah data yang dapat diinput adalah 5");
                break;
            }

            for (int i = 0; i < employeeCount; i++)
            {
                Employee employee;

                printf("Masukkan employee id untuk karyawan %d : \n", i + 1);
                scanf("%d", &employee.employeeID);

                while (getchar() != '\n')
                    ;

                // check employee id
                if (validateEmployeeID(employee.employeeID))
                {
                    puts("Invalid employee id");
                    break;
                }

                printf("Masukkan nama lengkap untuk karyawan %d : \n", i + 1);
                // scanf("%[^\n]%*c", &employee.fullName);
                fgets(employee.fullName, sizeof(employee.fullName), stdin);
                employee.fullName[strcspn(employee.fullName, "\n")] = '\0';
                clear_input_buffer();

                if (!validateStringLength(employee.fullName, 30))
                {
                    puts("Nama karyawan terlalu panjang");
                    break;
                }

                printf("Masukkan tempat lahir untuk karyawan %d : \n", i + 1);
                // scanf("%[^\n]%*c", &employee.bornPlace);
                fgets(employee.bornPlace, sizeof(employee.bornPlace), stdin);
                employee.bornPlace[strcspn(employee.bornPlace, "\n")] = '\0';
                clear_input_buffer();

                if (!validateStringLength(employee.bornPlace, 30))
                {
                    puts("Tempat lahir terlalu panjang");
                    break;
                }

                printf("Masukkan tanggal lahir (yyyy-mm-dd) untuk karyawan %d : \n", i + 1);
                // scanf("%10s", &employee.bornPlace);
                fgets(employee.bornDate, sizeof(employee.bornDate), stdin);
                employee.bornDate[strcspn(employee.bornDate, "\n")] = '\0';
                clear_input_buffer();

                printf("Masukkan jabatan untuk karyawan %d : \n", i + 1);
                // scanf("%[^\n]%*c", &employee.position);
                fgets(employee.position, sizeof(employee.position), stdin);
                employee.position[strcspn(employee.position, "\n")] = '\0';
                clear_input_buffer();

                if (!validateStringLength(employee.position, 50))
                {
                    puts("Jabatan terlalu panjang");
                    break;
                }

                push(employee);
            }

            break;

        case 2:
            display();
            break;

        case 3:
            printf("Masukkan id emplyee : \n");
            scanf("%d", &employeeId);

            if (validateEmployeeID(employeeId))
            {
                puts("Invalid employee id");
                break;
            }

            pop(employeeId);

            break;

        case 4:
            resetLinkedList();
            break;

        default:
            exit = true;
            break;
        }

    } while (!exit);

    return 0;
}