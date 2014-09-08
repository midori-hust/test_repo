///  DNS Query program on Linu

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

char dns_servers[10][100];
#define T_A 1 
#define T_NS 2
#define T_CNAME 5
#define T_SOA 6
#define T_PTR 12
#define T_MX 15

//function prototypes
void ngethostbyname(unsigned char*);
void ChangetoDnsNameFormat(unsigned char*,unsigned char*);
unsigned char* ReadName(unsigned char*,unsigned char*,int*);
void get_dns_servers();

//the  struct for DNS header
 struct dns_header{

  unsigned short id; 
  unsigned char rd :1;  
  unsigned char tc :1;
  unsigned char aa :1;
  unsigned char opcode :4;
  unsigned char qr :1;

  unsigned char rcode :4;
  unsigned char cd :1;
  unsigned char ad :1;
  unsigned char z :1;
  unsigned char ra :1;

  unsigned short q_count;
  unsigned short ans_count;
  unsigned short auth_count;
  unsigned short add_count;
};


// struct for the query
 struct question{
  unsigned short qtype;
  unsigned short qclass;
};




//Resource Record
 struct r_data{
  unsigned short type;
  unsigned short _class;
  unsigned int ttl;
  unsigned short data_len;
};


//these two struct will help
 struct res_record{
  unsigned char *name;
  unsigned char *rdata;
  struct r_data *resource;
 };



typedef  struct {
  unsigned char *name;
  struct question *ques;
}query;



int main()
{
  unsigned char hostname[100];

  //get the DNS servers 
  get_dns_servers();
  printf("\n    Chuong Trinh Mo Phong May Chu Phan Giai Ten Mien Don Gian. \n");
  //get the hostname
  printf("\n-->Enter  HostName to Lookup  :   ");
  //gets((char*)hostname);
  scanf("%s",(char*)hostname);

  //now get the ip of this hostname
  ngethostbyname(hostname);

  return 0;


}


void ngethostbyname(unsigned char *host)
{
  unsigned char buf[65536];
  unsigned  char *qname,*reader;
  int i,j,stop,s;

  struct sockaddr_in a;
  //the replies from the DNS server
  struct res_record  answers[20],auth[20],addit[20];

  struct sockaddr_in dest;
  struct dns_header  *dns = NULL;
  struct question    *qinfo = NULL;
  //udp packet for dns queries
  s=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

  dest.sin_family = AF_INET;
  dest.sin_port = htons(53);
  // dns server
  dest.sin_addr.s_addr = inet_addr(dns_servers[0]);
  //set the dns struct to standard queries
  dns=(struct dns_header*)&buf;

  dns->id=(unsigned short)htons(getpid());
  dns->qr = 0;      //This is a query
  dns->opcode = 0;  //This is a standard query
  dns->aa = 0;      //Not Authoritative
  dns->tc = 0;      //This message is not truncated
  dns->rd = 1;      //Recursion Desired
  dns->ra = 0;      //Recursion not available! hey we dont have it (lol)
  dns->z  = 0;
  dns->ad = 0;
  dns->cd = 0;
  dns->rcode = 0;
  dns->q_count = htons(1);   //we have only 1 question
  dns->ans_count  = 0;
  dns->auth_count = 0;
  dns->add_count  = 0;

  //point to the query portion
  qname = (unsigned char*)&buf[sizeof(struct dns_header)];

  ChangetoDnsNameFormat(qname,host);
  qinfo = (struct question *)&buf[sizeof(struct dns_header)+strlen((const char*)qname)+1];
  qinfo->qtype = htons(1);
  qinfo->qclass = htons(1);

  printf("\n +/Sending Packet........");
  if(sendto(s,(char*)buf,sizeof(struct dns_header) + (strlen((const char*)qname)+1) + sizeof(struct question),0,(struct sockaddr*)&dest,sizeof(dest)) == 0)
    {
      printf("\nError Sending Socket ");
    }
  printf("\n +/Sent ");
  i=sizeof dest;
  printf("\n +/Receiving anwser .......");

  if(recvfrom (s,(char*)buf,65536,0,(struct sockaddr*)&dest,&i) == 0)
    {
      printf("\nFailed . error Code .");
      
    }


  printf("\n +/Received.");
  dns=(struct dns_header*)buf;
  reader = &buf[sizeof(struct dns_header) + (strlen((const char*)qname)+1) + sizeof(struct question)];
  printf("\nThe response contains  : ");
  printf("\n   -->%d Questions             ",ntohs(dns->q_count));
  printf("\n   -->%d Anwsers               ",ntohs(dns->ans_count));
  printf("\n   -->%d Authoritative Server  ",ntohs(dns->auth_count));
  printf("\n   -->%d Additional records\n  ",ntohs(dns->add_count));


  //reading answers
  stop=0;

  for(i = 0;i<ntohs(dns->ans_count);i++)
    {
      answers[i].name=ReadName(reader,buf,&stop);
      reader = reader + stop;

      answers[i].resource = (struct r_data*)(reader);
      reader = reader  +  sizeof(struct r_data);

      if(ntohs(answers[i].resource->type)==1)
	{
	  answers[i].rdata=(unsigned char*)malloc(ntohs(answers[i].resource->data_len));
	  for(j=0;j<ntohs(answers[i].resource->data_len);j++)
	    answers[i].rdata[j]=reader[j];
	  answers[i].rdata[ntohs(answers[i].resource->data_len)]='\0';
	  reader = reader + ntohs(answers[i].resource->data_len);
	}else 
	{
	  answers[i].rdata=ReadName(reader,buf,&stop);
	  reader=reader+stop;
	}

    }
  //read authorities

  for(i=0;i<ntohs(dns->auth_count);i++)
    {
      auth[i].name = ReadName(reader,buf,&stop);
      reader  = reader + stop;

      auth[i].resource = (struct r_data*)(reader);
      reader += sizeof(struct r_data);

      auth[i].rdata = ReadName(reader,buf,&stop);
      reader += stop;
    }


  //read addtional
  for(i=0;i<ntohs(dns->add_count);i++)
    {
      addit[i].name = ReadName(reader,buf,&stop);
      reader  += stop;

      addit[i].resource = (struct r_data*)(reader);
      reader += sizeof(struct r_data);
      if(ntohs(addit[i].resource->type)==1)
	{
	  addit[i].rdata = (unsigned char*)malloc(ntohs(addit[i].resource->data_len));
	  for(j=0;j<ntohs(addit[i].resource->data_len);j++)
	    addit[i].rdata[j]=reader[j];

	  addit[i].rdata[ntohs(addit[i].resource->data_len)]='\0';
	  reader+=ntohs(addit[i].resource->data_len);
	}else
	{
	  addit[i].rdata=ReadName(reader,buf,&stop);
	  reader+=stop;
	}
    }

  //printf answers
  for(i=0;i<ntohs(dns->ans_count);i++)
    {
      printf("\n+++++++++++ Print  Answers ++++++++++++");
      printf("\n+-----> Name  : %s",answers[i].name);
      //IPV4 address
      if(ntohs(answers[i].resource->type)==1)
	{
	  long *p;
	  p=(long*)answers[i].rdata;
	  a.sin_addr.s_addr=(*p);
	  printf("\n+-----> Has IPv4 address  : %s ",inet_ntoa(a.sin_addr));

	}
      if(ntohs(answers[i].resource->type=5))
	printf("\n+-----> Has alias name  : %s",answers[i].rdata);
      printf("\n+++++++++++++++++++++++++++++++++++++++");
      printf("\n\n\n");
    }

 
 //print authorities 
  for(i=0;i<ntohs(dns->auth_count);i++)
    {
      printf("\n++++++++ Print  Authorities  +++++++++");
      printf("\n+-----> Name  :  %s",auth[i].name);

      if(ntohs(auth[i].resource->type)==2)
	printf("\n+-----> Has authorities name server  :  %s",auth[i].name);
      printf("\n+++++++++++++++++++++++++++++++++++++");
      printf("\n\n\n");
    }
 
  
//print addtional resource records
  for(i=0;i<ntohs(dns->add_count);i++)
    {
      printf("\n++++++++Print addtional resource records++++++++++");
      printf("\n+----->Name   :  %s",addit[i].name);

      if(ntohs(addit[i].resource->type)==1)
	{
	  long *p;
	  p=(long*)addit[i].rdata;
	  a.sin_addr.s_addr=(*p);
	  printf("\n+----->Has IPv4 address  :  %s",inet_ntoa(a.sin_addr));
	}
      printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++");
      printf("\n\n\n");
    }
 
  return;
}

unsigned char* ReadName(unsigned char* reader,unsigned char* buffer,int* count)
{
  unsigned char*name;
  unsigned int p=0,jumped=0,offset;
  int i,j;
  *count=1;
  name=(unsigned char*)malloc(256);
  name[0]='\0';

  while(*reader!=0)
    {
      if(*reader>=192)
	{
	  offset=(*reader)*256+*(reader+1)-49152;
	  reader=buffer+offset-1;
	  jumped=1;
	}else
	name[p++]=*reader;
      
      reader=reader+1;

      if(jumped==0)
	*count=*count+1;
    }

  name[p]='\0';
  if(jumped==1)
    *count=*count+1;

  for(i=0;i<(int)p;i++)
    {
      p=name[i];
      for(j=0;j<(int)p;j++)
	{
	  name[i]=name[i+1];
	  i++;
	}
      name[i]='.';
    }
  name[i-1]='\0';
  return name;

}


void get_dns_servers()
{
  strcpy(dns_servers[0],"208.67.222.222");
  strcpy(dns_servers[1],"208.67.222.220");
}



void ChangetoDnsNameFormat(unsigned char* dns,unsigned char* host)
{
  int lock=0,i;
  strcat((char*)host,".");
  for(i=0;i<(int)strlen((char*)host);i++)
    {
      if(host[i]=='.')
	{
	  *dns++=i-lock;
	  for(;lock<i;lock++)
	    {
	      *dns++=host[lock];
	    }
	  lock++;
	}

    }
  *dns++='\0';
}
