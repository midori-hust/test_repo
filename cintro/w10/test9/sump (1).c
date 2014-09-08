#include <stdio.h>
#include <malloc.h>
typedef struct _Pow{
    int so_mu;
    float he_so;
    struct _Pow* next;
    
}Pow;

void printPow(Pow* p);
void insertPow(Pow** p,int so_mu, float he_so);
void sumPow(Pow* p1,Pow* p2,Pow* p);

main(){
    Pow* p1 = NULL;
    Pow* p2 = NULL;
    Pow* p=NULL;
    int so_mu;
    float he_so;
    printf("\n---------------NHAP DU LIEU--------------");
    printf("\nDa thuc 1: \n");
    while(1){
        scanf("%d%f",&so_mu,&he_so);
        if(he_so == 0) break;
        else insertPow(&p1,so_mu,he_so);
    }
    printPow(p1);
    printf("\nNhap da thuc 2:\n");
    while(1){
        scanf("%d%f", &so_mu, &he_so);
        if(he_so == 0) break;
        else insertPow(&p2,so_mu,he_so);
        
    }
    printPow(p2);
    sumPow(p1,p2,p);
    printPow(p);
    
}
void printPow(Pow* p){
    Pow *pp;
    pp=p;
    while(pp!=NULL){
        printf("\n(%d,%.1f)",pp->so_mu ,pp->he_so);
        pp=pp->next;
        }
    printf("\n");
}

void insertPow(Pow** p, int so_mu,float he_so){
    Pow* temp_node;
    temp_node=(Pow*)malloc(sizeof(Pow));
    if(temp_node == NULL) printf("\nNot enough memory!");
    temp_node->he_so=he_so;
    temp_node->so_mu=so_mu;
    temp_node->next= *p;
    *p=temp_node;
}

void sumPow(Pow* p1, Pow* p2, Pow* p){
    Pow* pp1;
    Pow* pp2;
    pp1=p1;
    pp2=p2;
    while((pp1!=NULL)&&(pp2!=NULL)){
        if(pp1->so_mu == pp2->so_mu){
            insertPow(&p,pp1->so_mu,pp1->he_so);
            pp1=pp1->next;
            pp2=pp2->next;
            continue;
        }

        if(pp1->so_mu < pp2->so_mu){
            insertPow(&p,pp1->so_mu,pp2->he_so);
            pp1=pp1->next;
            continue;
            
        }

        if(pp1->so_mu > pp2->so_mu){ // Not neccessary for the last case
            insertPow(&p,pp2->so_mu,pp2->he_so);
            pp2=pp2->next;
            continue;
        }
    }
    if(pp1 == NULL){
        while(pp2!=NULL){
            insertPow(&p,pp2->so_mu,pp2->he_so);
            pp2=pp2->next;
            
        }
    }
    
    if(pp2==NULL){
        while(pp1!=NULL){
            insertPow(&p,pp1->so_mu,pp1->he_so);
            pp1=pp1->next;

        }
        
    }
}
