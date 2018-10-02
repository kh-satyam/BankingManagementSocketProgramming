#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<error.h>
#include<errno.h>
#include<stdlib.h>
#include<signal.h>
#define MAX 50
struct normal_account{
  char acc_name[MAX];
  char acc_pwd[MAX];
  int acc_num;
  float bal;
};
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
struct admin{
  int id;
  char pwd[MAX];
  char name[MAX];
};
int count=0;
int count2=0;
void myhandler(int s){
  if(s==SIGCHLD){
    printf("client exits\n");
    count--;
    printf("%d clients are live\n",count);
  }
}
int sfd;
int cfd;
int nfd;
int jfd1;
int jfd2;
int afd;
int acc_num;
char pwd[MAX];
int jacc_num;
char jpwd[MAX];
void adminLogin();
void adminManage();
void adminViewNormalAccountDetails();
void adminViewJointAccountDetails();
void adminDeleteNormalAccount();
void adminDeleteJointAccount();
void loginmenu();
void normalCreate();
void normalLogin();
void normalManage();
void normalAccDetails();
void normalChangePassword();
void normalWithdrawMoney();
void normalDepositMoney();
void normalViewAccountBalance();
void jointCreate();
void jointLogin();
void jointManage();
void jointAccountDetails();
void jointAccountChangePassword();
void jointAccountWithdrawMoney();
void jointAccountDepositMoney();
void normalAccDetails(){
  struct normal_account n1;
  printf("Your account details are as follows:\n");
  lseek(nfd,0,SEEK_SET);
  while(read(nfd,&n1,sizeof(struct normal_account))>0){
    printf("%d %d %s %s\n",acc_num,n1.acc_num,n1.acc_pwd,pwd);
    if(acc_num==n1.acc_num){
      if(strcmp(pwd,n1.acc_pwd)==0){
        printf("pass match\n");
      }
      write(cfd,&n1,sizeof(struct normal_account));
      printf("details send\n");
      break;
    }
  }
  normalManage();
}
void normalChangePassword(){
  printf("normal change password\n");
  char npwd[MAX];
  read(cfd,npwd,MAX);
  lseek(nfd,0,SEEK_SET);
  struct normal_account n1;
  while(read(nfd,&n1,sizeof(struct normal_account))>0){
    if(acc_num==n1.acc_num){
      printf("account found\n");
      strcpy(n1.acc_pwd,npwd);
      break;
    }
  }
  lseek(nfd,-1*sizeof(struct normal_account),SEEK_CUR);
  write(nfd,&n1,sizeof(struct normal_account));
  printf("password changed\n");
  normalManage();
}
void normalWithdrawMoney(){
  printf("normalWithdrawMoney\n");
  float amt;
  read(cfd,&amt,sizeof(amt));
  lseek(nfd,0,SEEK_SET);
  struct normal_account n1;
  while(read(nfd,&n1,sizeof(struct normal_account))>0){
    if(acc_num==n1.acc_num){
      printf("account found\n");
      n1.bal=n1.bal-amt;
      break;
    }
  }
  lseek(nfd,-1*sizeof(struct normal_account),SEEK_CUR);
  write(nfd,&n1,sizeof(struct normal_account));
  printf("Amount withdrawn\n");
  normalManage();
}
void normalDepositMoney(){
  printf("normalDepositMoney\n");
  float amt;
  read(cfd,&amt,sizeof(amt));
  lseek(nfd,0,SEEK_SET);
  struct normal_account n1;
  while(read(nfd,&n1,sizeof(struct normal_account))>0){
    if(acc_num==n1.acc_num){
      printf("account found\n");
      n1.bal=n1.bal+amt;
      break;
    }
  }
  lseek(nfd,-1*sizeof(struct normal_account),SEEK_CUR);
  write(nfd,&n1,sizeof(struct normal_account));
  printf("Amount Deposited\n");
  normalManage();
}
void normalViewAccountBalance(){
  float amt;
  printf("Your account balance details are as follows:\n");
  lseek(nfd,0,SEEK_SET);
  struct normal_account n1;
  while(read(nfd,&n1,sizeof(struct normal_account))>0){
    printf("%d %d %s %s\n",acc_num,n1.acc_num,n1.acc_pwd,pwd);
    if(acc_num==n1.acc_num){
      if(strcmp(pwd,n1.acc_pwd)==0){
        printf("pass match\n");
      }
      amt=n1.bal;
      write(cfd,&amt,sizeof(float));
      printf("details send\n");
      break;
    }
  }
  normalManage();
}
void normalManage(){
  /*printf("Welcome to Your Account Management portal\n");
	printf("1.View Account Holder Details\n");
	printf("2.Change Password\n");
	printf("3.Withdraw Money\n");
	printf("4.Deposit Money\n");
	printf("5.View Balance\n");
	printf("6.Logout\n");*/
  printf("normalManage\n");
  int res;
  read(cfd,&res,sizeof(int));
  switch(res){
    case 1:
      printf("Your Account Details are: ");
      normalAccDetails();
    case 2:
  		printf("Password change menu:\n");
			normalChangePassword();
  		break;
    case 3:
			printf("Withdraw money menu:\n");
      normalWithdrawMoney();
  		break;
    case 4:
  		printf("Deposit money menu:\n");
  		normalDepositMoney();
  		break;
    case 5:
      printf("View Account Balance menu:\n");
      normalViewAccountBalance();
      break;
    default:
      loginmenu();
  }
}
void normalLogin(){
  /*printf("Enter your account number\n");
  printf("Enter your password\n");*/
  read(cfd,&acc_num,sizeof(int));
  read(cfd,pwd,MAX);
  printf("Client details:%d %s\n",acc_num,pwd);
  int res=0;
  struct normal_account n1;
  lseek(nfd,0,SEEK_SET);
  while(read(nfd,&n1,sizeof(struct normal_account))>0){
    if(acc_num==n1.acc_num && strcmp(pwd,n1.acc_pwd)==0){
      res=1;
      break;
    }
  }
  write(cfd,&res,sizeof(int));
  if(res==0){
    printf("Invalid details\n");
    loginmenu();
  }else{
    printf("Login verified\n");
    normalManage();
  }
}
void normalCreate(){
  printf("normalCreate\n");
  struct normal_account n1;
  read(cfd,&n1,sizeof(struct normal_account));
  lseek(nfd,0,SEEK_END);
  write(nfd,&n1,sizeof(struct normal_account));
  printf("normal account created\n");
  loginmenu();
}
void jointAccountDetails(){
  printf("JointAccount Details");
  int offset=sizeof(struct joint_account)*count2;
  lseek(jfd1,offset,SEEK_SET);
  struct flock lock;
  lock.l_type=F_RDLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start=offset;
  lock.l_len=sizeof(struct joint_account);
  printf("Trying to acquire read lock on data\n");
  int r=fcntl(jfd1,F_SETLKW,&lock);
  printf("Read lock acquired\n");
  struct joint_account j1;
  read(jfd1,&j1,sizeof(struct joint_account));
  printf("details are %s %s %s %d %f\n",j1.acc_name1,j1.acc_name2,j1.acc_pwd,j1.acc_num,j1.bal);
  write(cfd,&j1,sizeof(struct joint_account));
  char c;
  read(cfd,&c,1);
  lock.l_type=F_UNLCK;
  printf("releasing read lock\n");
  fcntl(jfd1,F_SETLK,&lock);
  printf("lock released\n");
  jointManage();
}
void jointAccountChangePassword(){
  printf("joint change password\n");
  char tpwd[MAX];
  read(cfd,tpwd,MAX);
  int offset=sizeof(struct joint_account)*count2;
  lseek(jfd1,offset,SEEK_SET);
  struct flock lock;
  lock.l_type=F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start=offset;
  lock.l_len=sizeof(struct joint_account);
  printf("Trying to acquire write lock on data\n");
  int r=fcntl(jfd1,F_SETLKW,&lock);
  printf("write lock acquired\n");
  struct joint_account j1;
  read(jfd1,&j1,sizeof(struct joint_account));
  printf("details are %s %s %s %d %f\n",j1.acc_name1,j1.acc_name2,j1.acc_pwd,j1.acc_num,j1.bal);
  strcpy(j1.acc_pwd,tpwd);
  lseek(jfd1,-1*sizeof(struct joint_account),SEEK_CUR);
  write(jfd1,&j1,sizeof(struct joint_account));
  char m[MAX];
  strcpy(m,"Password Changed successfully\n");
  write(cfd,m,MAX);
  char c;
  read(cfd,&c,1);
  lock.l_type=F_UNLCK;
  printf("releasing write lock\n");
  fcntl(jfd1,F_SETLK,&lock);
  printf("lock released\n");
  jointManage();
}
void jointAccountWithdrawMoney(){
  printf("joint Withdraw Money\n");
  float kamt;
  read(cfd,&kamt,sizeof(float));
  int offset=sizeof(struct joint_account)*count2;
  lseek(jfd1,offset,SEEK_SET);
  struct flock lock;
  lock.l_type=F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start=offset;
  lock.l_len=sizeof(struct joint_account);
  printf("Trying to acquire write lock on data\n");
  int r=fcntl(jfd1,F_SETLKW,&lock);
  printf("write lock acquired\n");
  struct joint_account j1;
  read(jfd1,&j1,sizeof(struct joint_account));
  printf("details are %s %s %s %d %f\n",j1.acc_name1,j1.acc_name2,j1.acc_pwd,j1.acc_num,j1.bal);
  j1.bal=j1.bal-kamt;
  lseek(jfd1,-1*sizeof(struct joint_account),SEEK_CUR);
  write(jfd1,&j1,sizeof(struct joint_account));
  char m[MAX];
  strcpy(m,"Amount Withdrawn successfully\n");
  write(cfd,m,MAX);
  char c;
  read(cfd,&c,1);
  lock.l_type=F_UNLCK;
  printf("releasing write lock\n");
  fcntl(jfd1,F_SETLK,&lock);
  printf("lock released\n");
  jointManage();
}
void jointAccountDepositMoney(){
  printf("joint Deposite Money\n");
  float kamt;
  read(cfd,&kamt,sizeof(float));
  int offset=sizeof(struct joint_account)*count2;
  lseek(jfd1,offset,SEEK_SET);
  struct flock lock;
  lock.l_type=F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start=offset;
  lock.l_len=sizeof(struct joint_account);
  printf("Trying to acquire write lock on data\n");
  int r=fcntl(jfd1,F_SETLKW,&lock);
  printf("write lock acquired\n");
  struct joint_account j1;
  read(jfd1,&j1,sizeof(struct joint_account));
  printf("details are %s %s %s %d %f\n",j1.acc_name1,j1.acc_name2,j1.acc_pwd,j1.acc_num,j1.bal);
  j1.bal=j1.bal+kamt;
  lseek(jfd1,-1*sizeof(struct joint_account),SEEK_CUR);
  write(jfd1,&j1,sizeof(struct joint_account));
  char m[MAX];
  strcpy(m,"Amount Deposited Successfully\n");
  write(cfd,m,MAX);
  char c;
  read(cfd,&c,1);
  lock.l_type=F_UNLCK;
  printf("releasing write lock\n");
  fcntl(jfd1,F_SETLK,&lock);
  printf("lock released\n");
  jointManage();
}
void jointManage(){
  printf("jointManage\n");
  /*printf("Welcome to Joint Account Management Portal\n");
  printf("1.View Account Holder Details\n");
	printf("2.Change Password\n");
	printf("3.Withdraw Money\n");
	printf("4.Deposit Money\n");
	printf("5.View Balance\n");
	printf("6.Logout\n");*/
  int res;
  read(cfd,&res,sizeof(res));
  switch(res){
    case 1:
      printf("Joint Account Details\n");
      jointAccountDetails();
    case 2:
      printf("Change Joint Account Password\n");
      jointAccountChangePassword();
      break;
    case 3:
      printf("Withdraw Money\n");
      jointAccountWithdrawMoney();
      break;
    case 4:
      printf("Deposit Money\n");
      jointAccountDepositMoney();
      break;
    default:
      loginmenu();
  }
}
void jointLogin(){
  printf("joint Login menu\n");
  read(cfd,&jacc_num,sizeof(int));
  read(cfd,jpwd,MAX);
  printf("Joint details are:%d %s\n",jacc_num,jpwd);
  lseek(jfd2,0,SEEK_SET);
  int res=0;
  struct joint_account_d j1;
  lseek(jfd2,0,SEEK_SET);
  count2=0;
  while(read(jfd2,&j1,sizeof(struct joint_account_d))>0){
    //printf("%d %d %s %s\n",j1.acc_num,jacc_num,j1.acc_pwd,jpwd);
    if(j1.acc_num==jacc_num && strcmp(j1.acc_pwd,jpwd)==0){
      printf("Acc verified\n");
      res=1;
      break;
    }
    count2++;
  }
  write(cfd,&res,sizeof(int));
  if(res==0){
    printf("Invalid details\n");
    loginmenu();
  }else{
    printf("login successfull\n");
    printf("record number:%d\n",count2);
    jointManage();
  }
}
void jointCreate(){
  printf("joint create\n");
  struct joint_account t1;
  struct joint_account_d t2;
  read(cfd,&t1,sizeof(struct joint_account));
  read(cfd,&t2,sizeof(struct joint_account_d));
  lseek(jfd1,0,SEEK_END);
  write(jfd1,&t1,sizeof(struct joint_account));
  lseek(jfd2,0,SEEK_END);
  write(jfd2,&t2,sizeof(struct joint_account_d));
  printf("account created\n");
  loginmenu();
}
void adminViewNormalAccountDetails(){
  printf("adminViewNormalAccountDetails\n");
  int anum;
  read(cfd,&anum,sizeof(int));
  struct normal_account n1;
  lseek(nfd,0,SEEK_SET);
  int res=0;
  while(read(nfd,&n1,sizeof(n1))>0){
    if(n1.acc_num==anum){
      printf("account found\n");
      res=1;
      break;
    }
  }
  write(cfd,&res,sizeof(int));
  if(res==1){
      write(cfd,&n1,sizeof(struct normal_account));
  }
  adminManage();
}
void adminViewJointAccountDetails(){
  printf("JointAccount Details\n");
  int id;
  read(cfd,&id,sizeof(int));
  printf("Account details:%d\n",id);
  int res=0;
  struct joint_account_d t1;
  lseek(jfd2,0,SEEK_SET);
  int counter=0;
  while(read(jfd2,&t1,sizeof(struct joint_account_d))>0){
    //printf("%d %d %s %s\n",j1.acc_num,jacc_num,j1.acc_pwd,jpwd);
    if(t1.acc_num==id){
      printf("Acc verified\n");
      res=1;
      break;
    }
    counter++;
  }
  write(cfd,&res,sizeof(int));
  if(res==0){
    printf("account not found\n");
  }else{
    int offset=sizeof(struct joint_account)*counter;
    lseek(jfd1,offset,SEEK_SET);
    struct flock lock;
    lock.l_type=F_RDLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=offset;
    lock.l_len=sizeof(struct joint_account);
    printf("Trying to acquire read lock on data\n");
    int r=fcntl(jfd1,F_SETLKW,&lock);
    printf("Read lock acquired\n");
    struct joint_account t2;
    read(jfd1,&t2,sizeof(struct joint_account));
    printf("details are %s %s %s %d %f\n",t2.acc_name1,t2.acc_name2,t2.acc_pwd,t2.acc_num,t2.bal);
    write(cfd,&t2,sizeof(struct joint_account));
    char c;
    read(cfd,&c,1);
    lock.l_type=F_UNLCK;
    printf("releasing read lock\n");
    fcntl(jfd1,F_SETLK,&lock);
    printf("lock released\n");
  }
  adminManage();
}
void adminDeleteNormalAccount(){
  printf("adminDeleteNormalAccount\n");
  int tacc;
  read(cfd,&tacc,sizeof(int));
  lseek(nfd,0,SEEK_SET);
  struct normal_account n1;
  while(read(nfd,&n1,sizeof(struct normal_account))>0){
    if(n1.acc_num==tacc){
      printf("account found\n");
      n1.acc_num=-1;
      break;
    }
  }
  lseek(nfd,-1*sizeof(struct normal_account),SEEK_CUR);
  write(nfd,&n1,sizeof(struct normal_account));
  printf("normal account deleted\n");
  adminManage();
}
void adminDeleteJointAccount(){
  printf("admin delete joint account\n");
  int tc;
  read(cfd,&tc,sizeof(int));

  struct joint_account_d t1;
  lseek(jfd2,0,SEEK_SET);
  int counter=0;
  while(read(jfd2,&t1,sizeof(struct joint_account_d))>0){
    //printf("%d %d %s %s\n",j1.acc_num,jacc_num,j1.acc_pwd,jpwd);
    if(t1.acc_num==tc){
      printf("Acc verified\n");
      break;
    }
    counter++;
  }
  int offset=sizeof(struct joint_account)*counter;
  int offset1=sizeof(struct joint_account_d)*counter;
  lseek(jfd1,offset,SEEK_SET);
  lseek(jfd2,offset1,SEEK_SET);
  struct flock lock;
  lock.l_type=F_WRLCK;
  lock.l_whence=SEEK_SET;
  lock.l_start=offset;
  lock.l_len=sizeof(struct joint_account);
  printf("Trying to acquire write lock on data\n");
  int r=fcntl(jfd1,F_SETLKW,&lock);
  printf("write lock acquired\n");
  struct joint_account t2;
  read(jfd1,&t2,sizeof(struct joint_account));
  read(jfd2,&t1,sizeof(struct joint_account_d));
  printf("details are %s %s %s %d %f\n",t2.acc_name1,t2.acc_name2,t2.acc_pwd,t2.acc_num,t2.bal);
  printf("log details :%d %s\n",t1.acc_num,t1.acc_pwd);
  t2.acc_num=-1;
  t1.acc_num=-1;
  lseek(jfd1,-1*sizeof(struct joint_account),SEEK_CUR);
  lseek(jfd2,-1*sizeof(struct joint_account_d),SEEK_CUR);
  write(jfd1,&t2,sizeof(struct joint_account));
  write(jfd2,&t1,sizeof(struct joint_account_d));
  char *tarr="Message deleted";
  char tarr1[MAX];
  strcpy(tarr1,tarr);
  write(cfd,tarr1,MAX);
  char c;
  read(cfd,&c,1);
  lock.l_type=F_UNLCK;
  printf("releasing read lock\n");
  fcntl(jfd1,F_SETLK,&lock);
  printf("lock released\n");
  adminManage();

}
void adminManage(){
  printf("adminManage\n");
  /*printf("Admin Management Portal\n");
  printf("1.View NormalAccount Details\n");
  printf("2.View JointAccount Details\n");
  printf("3.Delete Normal Account\n");
  printf("4.Delete Joint Account\n");*/
  int option;
  read(cfd,&option,sizeof(int));
  switch(option){
    case 1:
      printf("adminViewNormalAccountDetails\n");
      adminViewNormalAccountDetails();
      break;
    case 2:
      printf("adminViewJointAccountDetails\n");
      adminViewJointAccountDetails();
      break;
    case 3:
      printf("adminDeleteNormalAccount\n");
      adminDeleteNormalAccount();
      break;
    case 4:
      printf("adminDeleteJointAccount\n");
      adminDeleteJointAccount();
      break;
    default:
      loginmenu();
  }
  loginmenu();
}

void adminLogin(){
  int admin_acc;
  char admin_pwd[MAX];
  read(cfd,&admin_acc,sizeof(int));
  read(cfd,admin_pwd,MAX);
  printf("Admin details:%d %s\n",admin_acc,admin_pwd);
  int res=0;
  struct admin a1;
  lseek(afd,0,SEEK_SET);
  while(read(afd,&a1,sizeof(struct admin))>0){
    if(admin_acc==a1.id && strcmp(admin_pwd,a1.pwd)==0){
      res=1;
      printf("data verified\n");
      break;
    }
  }
  write(cfd,&res,sizeof(int));
  if(res==0){
    printf("Invalid details\n");
    loginmenu();
  }else{
    printf("Login verified\n");
    adminManage();
  }
}
void loginmenu(){
  printf("loginmenu\n");
  int option;
  /*printf("Choose on of the following options:\n");
	printf("1.Login(Singer User Accout)\n");
	printf("2.Login(Joint Acocunt Holder)\n");
	printf("3.Admin Login\n");
	printf("Create Account(Single User)\n");
	printf("Create Account(Joint Account)\n");*/
  read(cfd,&option,sizeof(int));
  switch (option) {
    case 1:
      printf("normalLogin\n");
      normalLogin();
      break;
    case 2:
      printf("jointLogin\n");
      jointLogin();
    case 3:
      printf("adminLogin\n");
      adminLogin();
    case 4:
      printf("create normal account\n");
      normalCreate();
      break;
    case 5:
      printf("create joint Account\n");
      jointCreate();
      break;
    default:
      close(cfd);
      exit(1);
  }
}
int main(int argc,char *argv[]){
  signal(SIGCHLD,myhandler);
  nfd=open("n_acc_d",O_CREAT|O_RDWR,S_IRWXU);//normal user data
  jfd1=open("j_acc_d1",O_CREAT|O_RDWR,S_IRWXU);//joint user data
  jfd2=open("j_acc_d2",O_CREAT|O_RDWR,S_IRWXU);//joint user login data
  afd=open("a_acc_d",O_CREAT|O_RDWR,S_IRWXU);//admin data
  if(nfd==-1){
    printf("Error in opening normal user data\n");
    printf("%s",strerror(errno));
  }
  if(jfd1==-1){
    printf("Error in opening joint user data1\n");
    printf("%s",strerror(errno));
  }
  if(jfd2==-1){
    printf("Error in opening joint user data2\n");
    printf("%s",strerror(errno));
  }
  if(afd==-1){
    printf("Error in opening admin data\n");
    printf("%s",strerror(errno));
  }
  struct sockaddr_in serv,cli;
  socklen_t cli_size=sizeof(struct sockaddr_in);
  sfd=socket(AF_UNIX,SOCK_STREAM,0);
  if(sfd==-1){
    printf("Error in creating socket\n");
    printf("%s",strerror(errno));
    return 0;
  }
  int port=atoi(argv[1]);
  //port=8051;
  printf("Server on port:%d %s\n",port,argv[1]);
  printf("socket call successfull\n");
  serv.sin_family=AF_UNIX;
  serv.sin_addr.s_addr=htonl(INADDR_ANY);
  serv.sin_port=htons(port);
  if(bind(sfd,(struct sockaddr*)&serv,sizeof(serv))==-1){
    printf("Error in bind\n%s\n",strerror(errno));return 0;
  }
  printf("bind successfull\n");

  if(listen(sfd,5)==-1){
    printf("Error in listen call\n%s",strerror(errno));
  }
  printf("socket created successfully\n");
  while(1){
    if((cfd=accept(sfd,(struct sockaddr *)&cli,&cli_size))==-1){
      printf("Error in accepting conection from client\n%s\n",strerror(errno));
    }
    printf("Currently connected clients:%d\n",++count);
    if(fork()==0){
      close(sfd);
      loginmenu();
    }else{
      close(cfd);
    }
  }
  return 0;
}
