#include <stdio.h>
#include <math.h>

void main(){
    float weight;
    float height;
    float bmi;

    printf("Masukkan tinggi badan (cm) : ");
    scanf("%f", &height);
    height = height / 100;

    printf("Masukkan berat badan (kg) : ");
    scanf("%f", &weight);

    bmi = weight  / pow(height, 2);

    if (bmi < 18.5) {
      printf("Underweight");
    } else if (18.5 <= bmi && bmi <= 24.9) {
      printf("Normal");
    } else if (25.0 <= bmi && bmi <= 29.9) {
      printf("Overweight");
    } else {
      printf("Obese");
    }
}