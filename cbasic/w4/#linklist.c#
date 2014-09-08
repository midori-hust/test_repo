#include "linklist.h"

//Tao moi 1 phan tu moi
node *newNode(elementType data)
{
  node* new;
  new = (node*)malloc(sizeof(node));
  new->element = data;
  new->next = NULL;
  return new;
}

//Chen 1 phan tu vao dau danh sach
void insertTop(node* new_item)
{
  if(root == NULL) root = new_item;
  else
    {
      new_item->next = root;
      root = new_item;
    }
}

//Chen 1 phan tu vao sau phan tu tro boi cur torng danh sach
void insert(node* new_item)
{
  if(root == NULL) root = cur = new_item;
  else
    {
      new_item->next = cur->next;
      cur->next = new_item;
      cur = new_item; //Hoac cur=cur->next;
    }
}

//Hien thi danh sach ra man hinh
void displayList()
{
  node* cur;
  for(cur = root; cur != NULL; cur = cur->next)
    {
      //Hien thi cur->element ra man hinh
      //(Cai nay phai biet duoc kieu cua element thi moi printf duoc)
      printf("%d\n", cur->element);
    }
}


//Xoa phan tu ngay sau phan tu cur trong danh sach
void deleteNode()
{

  prev = getPrev(root, cur);
  if(root != cur)
    {
      root = root->next;
      free(cur);
    }
  else
    {
      //prev = cur;
      //cur = prev->next;
      prev->next = cur->next;
      free(cur);  
    }
}

//Lay prev trong danh sach
node *getPrev()
{

  if((cur == root) || (root == NULL))
    {
      prev=NULL;
      return prev;
    }
  for(prev = root; prev != NULL; prev = prev->next)
    if(prev->next = cur) break;
  return prev;
}
