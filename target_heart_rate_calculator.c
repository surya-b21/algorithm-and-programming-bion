#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> 

void main()
{
    char* birthDay[10];
    int age;

    printf("Please insert your birthday (DD/MM/YYYY): ");
    scanf("%s", &birthDay);

    convertBirthdayToAge(&birthDay, &age);
    int maxHeartRate = 220 - age;
    printf("Your maximum heart rate is %d\n", maxHeartRate);
    printf("Your target heart rate between %.2f to %.2f\n", maxHeartRate * 0.5, maxHeartRate * 0.8);
}

void convertBirthdayToAge(char* birthDay, int* age)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    char* token = strtok(birthDay, "/");
    int thirtyOneMonth[] = {1,3,5,7,8,10,12};

    int year, month, day, leapYear = 0, allowThirtyOneDay = 0;

    int index = 0;
    while (token != NULL)
    {
        switch (index)
        {
        case 0:
            day = atoi(token);
            break;
        
        case 1:
            month = atoi(token);
            // validate month between 1 to 12
            if (month <= 0 && month > 12) {
                printf("Invalid month");
                exit(1);
            }
            // find month allow day to 31
            for (int i = 0; thirtyOneMonth[i] < 7; i++ ) {
                if (month != thirtyOneMonth[i]) continue;

                allowThirtyOneDay = 1;
            }

            break;

        default:
            year = atoi(token);
            if (year % 4 == 0) {
                leapYear = 1;
            }
            break;
        }

        token = strtok(NULL, "/");
        index++;
    }

    // validate day
    if (
        (allowThirtyOneDay == 0 && day > 30) ||
        (month == 2 && ((leapYear == 0 && day > 28)))
    ) {
        printf("Invalid day");
        exit(1);
    } 
    
    *age = (tm.tm_year + 1900) - year;
    if ((tm.tm_mon + 1) < month) {
        *age -= 1;
    }
}