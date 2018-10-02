#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#define MAX 50
struct admin{
  int id;
  char pwd[MAX];
  char name[MAX];
};
int main(){
  int fd=open("a_acc_d",O_CREAT|O_RDWR,S_IRWXU);
  printf("Enter admin Details\n");
  struct admin a1;
  printf("Enter admin id:");
  scanf("%d",&a1.id);
  printf("\n");
  printf("Enter admin password:");
  scanf("%s",a1.pwd);
  printf("\n");
  printf("Enter admin name:");
  scanf("%s",a1.name);
  printf("\n");
  printf("bytes skipped:%ld",lseek(fd,0,SEEK_END));
  write(fd,&a1,sizeof(struct admin));
  close(fd);
  return 0;
}
