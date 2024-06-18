#include <stdio.h>

void main()
{
    /*
     * internship = 1
     * full time = 2
     * contract = 3 
     */

    int categoryEmployee;
    int payPerHour;
    int overtimePay;
    printf("Choose employee category (1=intern, 2=full time, 3=contract) : ");
    scanf("%d", &categoryEmployee);

    // validate input
    checkCategory(categoryEmployee, &payPerHour, &overtimePay);

    int workHours;
    printf("Insert total work hours : ");
    scanf("%d", &workHours);

    // count salary
    int salary;
    if (workHours > 40) {
        salary = payPerHour * 40;
        salary += overtimePay * (workHours - 40);
    } else {
        salary = payPerHour * workHours;
    }

    printf("Salary must be paid is %d", salary);
}

void checkCategory(int categoryEmployee, int* payPerHour, int* overtimePay)
{
    switch (categoryEmployee)
        {
        case 1:
            *payPerHour = 5000;
            *overtimePay = *payPerHour + (*payPerHour * 0.5);
            break;
        
        case 2:
            *payPerHour = 100000;
            *overtimePay = *payPerHour + (*payPerHour * 0.5);
            break;

        case 3:
            *payPerHour = 125000;
            break;

        default:
            goto exit;
        }

    return;

    exit:
        printf("Wrong input");
        exit(1);
}