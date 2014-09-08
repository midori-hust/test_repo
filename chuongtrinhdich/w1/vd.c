#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char word[30]; //Tạo kiểu dữ liệu mới EleType
 
}EleType;

struct bst_node
{
    EleType data;
    int count;
    struct bst_node* left;
    struct bst_node* right;
}; //tạo kiểu cấu trúc cây nhị phân tìm kiếm, có thêm biến count để đếm tần số xuất hiện

struct bst_node* new_node(EleType data);
void free_node(struct bst_node* node);
struct bst_node **search(struct bst_node **root, EleType data);
void insert(struct bst_node** root, EleType data);
void delete(struct bst_node** node);
int inorderprint(struct bst_node *t);

main()
{
  struct bst_node *t=NULL;
  EleType item;
  char buff[30];
  
  FILE *fin;
  char filename1[]="input.txt";
  if ((fin = fopen(filename1,"r")) == NULL)
    {
      printf("Can not open %s!\n",filename1);
      return 0;
    }
  
  while (1)
    {
      fscanf(fin,"%s",buff);    //đọc từng từ từ file input.txt
      strcpy(item.word,buff);      //copy vào item.word
      if(feof(fin)) break;
      struct bst_node** node = search(&t,item);
      if (*node != NULL)
	((*node)->count)++; //nếu từ vừa đọc đã có trong cây nhị phân thì tăng biến count của node đó lên 1
      else
	insert(&t,item); //nếu chưa có trong cây nhị phân thì insert vào
    }
  inorderprint(t); //in BST ra màn hình theo thứ tự giữa và ghi vào file output.txt
  printf("\n");
  return 0;
}

struct bst_node *new_node(EleType data)  //tạo node mới
{
  struct bst_node* result = (struct bst_node *)malloc(sizeof(struct bst_node));
  result->data = data;
  result->count = 1;
  result->left = result->right = NULL;
  return result;
}

void free_node(struct bst_node *node) 
{
  free(node);
}

struct bst_node **search(struct bst_node **root, EleType data) //tìm kiếm data đã có trong cây chưa
{
  struct bst_node** node = root;
  while (*node != NULL) 
    {
      int compare_result = strcmp(data.word, (*node)->data.word);
      if (compare_result < 0)
	node = &(*node)->left;
      else if (compare_result > 0)
	node = &(*node)->right;
      else
	break;
    }
  return node;
}

void insert(struct bst_node **root, EleType data) 
{
  struct bst_node** node = search(root, data);
  if (*node == NULL) {
    *node = new_node(data);
  }
}

void delete(struct bst_node **node) 
{
    struct bst_node* old_node = *node;
    if ((*node)->left == NULL) {
        *node = (*node)->right;
        free(old_node);
    } else if ((*node)->right == NULL) {
        *node = (*node)->left;
        free_node(old_node);
    } else {
        struct bst_node** pred = &(*node)->left;
    while ((*pred)->right != NULL) {
        pred = &(*pred)->right;
    }

    /* Swap values */
    EleType temp = (*pred)->data;
    (*pred)->data = (*node)->data;
    (*node)->data = temp;

    delete(pred);
    }
}

int inorderprint(struct bst_node *t)
{
    FILE *fout;
    char filename2[]="output.txt";
    if ((fout = fopen(filename2,"w+")) == NULL)
    {
        printf("Can not open %s!\n",filename2);
        return 0;
    }
    if (t!=NULL)
    {
        
        inorderprint(t->left);
	printf("%s : %d\n",t->data.word,t->count);
	//  fprintf(fout,"%s : %d",t->data.word,t->count);
        inorderprint(t->right);

    }
    return 0;
}  