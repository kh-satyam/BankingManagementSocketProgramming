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
  struct admin a1;
  printf("Admin Users Data\n");
  while(read(fd,&a1,sizeof(struct admin))>0){
    printf("%d %s %s\n",a1.id,a1.pwd,a1.name);
  }
  return 0;
}
