#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#define MAX 50
struct normal_account{
  char acc_name[MAX];
  char acc_pwd[MAX];
  int acc_num;
  float bal;
};
int main(){
  int fd=open("n_acc_d",O_CREAT|O_RDWR,S_IRWXU);
  struct normal_account a1;
  printf("Normal Users Data\n");
  while(read(fd,&a1,sizeof(struct normal_account))>0){
    printf("%s %s %d %f\n",a1.acc_name,a1.acc_pwd,a1.acc_num,a1.bal);
  }
  return 0;
}
