#include <stdio.h>

#define PI 3.1415

int main() {
  float r;

  printf("Please enter the radius of the circle: ");
  scanf("%f", &r);

  printf("P = %f\nS = %f\n", PI * 2 * r, PI * r * r);
  return 0;
}
