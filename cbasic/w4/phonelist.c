#include "phonelist.h"

//Tao moi 1 phan tu moi
AddressList *newAddress(char *name, int tel, char *email)
{
  AddressList* new;
  new = (AddressList*)malloc(sizeof(AddressList));
  strcpy((new->addr).name,name);
  new->addr.tel = tel;
  strcpy(new->addr.email,email);
  new->next = NULL;
  return new;
}

//Chen 1 phan tu vao dau danh sach
void insertTop(AddressList* new_item)
{
  if(root == NULL) root = new_item;
  else
    {
      new_item->next = root;
      root = new_item;
    }
}

//Chen 1 phan tu vao sau phan tu tro boi cur torng danh sach
void insert(AddressList* new_item)
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
  AddressList* cur1;
  for(cur1 = root; cur1 != NULL; cur1 = cur1->next)
    {
      //Hien thi cur->element ra man hinh
      //(Cai nay phai biet duoc kieu cua element thi moi printf duoc)
      printf("\n");
      printf("%s\t%d\t%s\n", cur1->addr.name, cur1->addr.tel, cur1->addr.email);
    }
}

void delete()
{
  char name[MAXLENGTH];

  printf("Nhap ten nguoi ban muon xoa: "); scanf("%s", name);
  deleteNumber(name);
}

//Xoa phan tu ngay sau phan tu cur trong danh sach
void deleteNumber(char *name)
{
  AddressList* cur1;
  AddressList* temp;

  if(strcmp(root->addr.name, name) != 0)
    {
      printf("Pending...\n");
      for(cur1 = root; cur1 != NULL; cur1 = cur1->next)
	{
	  temp = cur1->next;
	  if(strcmp(temp->addr.name, name) == 0) 
	    {
	      cur1->next = temp->next;
	      free(temp);
	      break;
	    }
	}
    }
  else
    {
      temp = root;
      root = root->next;
      free(temp);
    }
  printf("Da xoa xong!\n");
}
