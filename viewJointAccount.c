#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#define MAX 50
struct joint_account{
  char acc_name1[MAX];
  char acc_name2[MAX];
  char acc_pwd[MAX];
  int acc_num;
  float bal;
};
struct joint_account_d{
  char acc_pwd[MAX];
  int acc_num;
};
int main(){
  int fd1=open("j_acc_d1",O_CREAT|O_RDWR,S_IRWXU);
  int fd2=open("j_acc_d2",O_CREAT|O_RDWR,S_IRWXU);
  struct joint_account nc1;
  struct joint_account_d nc2;
  printf("Joint Account Users Data:\n");
  while(read(fd1,&nc1,sizeof(struct joint_account))>0){
    printf("%s %s %s %d %f\n",nc1.acc_name1,nc1.acc_name2,nc1.acc_pwd,nc1.acc_num,nc1.bal);
  }
  while(read(fd2,&nc2,sizeof(struct joint_account_d))>0){
    printf("%s %d\n",nc2.acc_pwd,nc2.acc_num);
  }
  close(fd1);
  close(fd2);
  return 0;
}
