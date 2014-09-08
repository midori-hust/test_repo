#include<stdio.h>

void compress(char s[],char s1[], char s2[])		//nen
{
    FILE*f1;
    FILE*f2;
    char m[1024];
    int i,k;
    int j=0;
    f1=fopen(s1,"r");
    f2=fopen(s2,"w");
    while(fgets(m,1024,f1)!=NULL)
        {
            for(i=0;i<strlen(m);i++)
            {
                if(m[i]>='A'&&m[i]<='Z')
                {
                    k=(m[i]-'A'+s[j]-'a')%26;
                    m[i]='A'+k;
                    j++;
                }
                else if(m[i]>='a'&&m[i]<='z')
                {
                    k=(m[i]-'a'+s[j]-'a')%26;
                    m[i]='a'+k;
                    j++;
                }
                if(j==strlen(s)) j=0;
            }
            fprintf(f2,"%s",m);
        }
    fclose(f1);
    fclose(f2);
}
void decompress(char s[],char s1[], char s2[])		//giai nen
{
    FILE*f1;
    FILE*f2;
    char m[1024];
    int i,k;
    int j=0;
    f1=fopen(s1,"r");
    f2=fopen(s2,"w");
    while(fgets(m,1024,f1)!=NULL)
        {
            for(i=0;i<strlen(m);i++)
            {
                if(m[i]>='A'&&m[i]<='Z')
                {
                    k=(m[i]-'A'-(s[j]-'a'))%26;
                    if(k<0) k=26+k;
                    m[i]='A'+k;
                    j++;
                }
                else if(m[i]>='a'&&m[i]<='z')
                {
                    k=(m[i]-'a'-(s[j]-'a'))%26;
                    if(k<0) k=26+k;
                    m[i]='a'+k;
                    j++;
                }
                if(j==strlen(s)) j=0;
            }
            fprintf(f2,"%s",m);
        }
    fclose(f1);
    fclose(f2);
}
