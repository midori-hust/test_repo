#include <stdio.h>
#include <math.h>

int main() {
  float a, b, c, delta;
  float root1, root2;

  printf("Solve the equation ax^2 + bx + c = 0\n");

  printf("a = ");
  scanf("%f", &a);
  printf("b = ");
  scanf("%f", &b);
  printf("c = ");
  scanf("%f", &c);

  delta = b * b - 4 * a * c;

  if(delta < 0) {
    printf("There is no root of this equation\n");
    return 0;
  }
  else {
    root1 = (-b + sqrt(delta)) / (2 * a);
    root2 = (-b - sqrt(delta)) / (2 * a);
  }

  if(root1 == root2)
    printf("root 1 = root 2 = %f\n", root1);
  else
    printf("root 1 = %f\nroot 2 = %f\n", root1, root2);

  return 0;
}
