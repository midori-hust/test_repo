/* Cau 14: */
/* Mot tu dien "Anh-Viet" don gian co du lieu duoc luu tru trong file "data.txt"  */
/* voi dinh dang nhu sau: tu tieng Anh, roi den dau tab, sau do den tu tieng Viet. */
/* Vi du: school     truong hoc (khoang cach o giua tuong ung voi 1 dau tab) */
/* Gia su rang trong file nay, cac tu tieng Anh khong co dau space, cac tu tieng  */
/* Viet co the co dau space, do dai toi da cua tu tieng Anh va tieng Viet la 20  */
/* ky tu. Hay tao file "data.txt" voi it nhat 5 tu tieng Anh. Sau do doc noi dung  */
/* cua cac tu tieng Anh luu vao 1 mang, cac tu tieng Viet luu vao 1 mang. Hien  */
/* thi 2 mang nay ra man hinh. */

#include <stdio.h>

#define MAXLENGTH 100

/*int main()
{
  FILE *f;
  char filename[] = "data.txt";

  if((f = fopen(filename, "wt")) == NULL)
    {
      printf("Cannot open file %s!\n", filename);
      return 1;
    }

  int i;
  char a[MAXLENGTH], b[MAXLENGTH];
  for(i=0; i<6; i++)
    {
      printf("Hay viet cac tu tieng Anh va nghia cua no: ");
      gets(a);
      gets(b);
      fprintf(f, "%s\t%s\n", a, b);
    }

  fclose(f);
  return 0;

}*/

struct words
{
  char word[MAXLENGTH];
  char mean[MAXLENGTH];
};

int main()
{
  struct words wordi[MAXLENGTH];
  FILE *f;
  char filename[] = "data.txt";
  int i=0;
  
  if((f = fopen(filename, "r")) == NULL)
    {
      printf("Cannot open file %s!\n", filename);
      return 1;
    }
  while(!feof(f))
    {
      fscanf(f, "%s\t", wordi[i].word);
      fgets(wordi[i].mean,20,f);
      i++;
    }
  fclose(f);
  int j;
  printf("Danh sach cac tu trong tu dien:\n");
  for(j=0; j<i; j++)
    {
      printf("%s\t%s", wordi[j].word, wordi[j].mean);
    }
  return 0;
}
