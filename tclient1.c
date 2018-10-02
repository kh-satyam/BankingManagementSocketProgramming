#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include<error.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
int sd;
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
int acc_num;
char pwd[MAX];
int jacc_num;
char jpwd[MAX];
int count1=0;
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
	printf("Your Account details are as follows:\n");
	struct normal_account n1;
	read(sd,&n1,sizeof(n1));
	printf("Account Name:%s\n",n1.acc_name);
	printf("Account Password:%s\n",n1.acc_pwd);
	printf("Account number:%d\n",n1.acc_num);
	printf("Account balance:%f\n\n",n1.bal);
	int k;
	printf("Press any key to to go back to Management Portal\n");
  char c;
  read(0,&c,sizeof(char));
  //fflush(stdin);
  system("clear");
	normalManage();
}
void normalChangePassword(){
	printf("Enter new Password for your Account:");
	char npwd[MAX];
	scanf("%s",npwd);
	write(sd,npwd,MAX);
	printf("Password successfully changed\n\n");
  printf("Press any key to go back to Management Portal\n");
  char c;
  read(0,&read,sizeof(char));
  //fflush(stdin);
  system("clear");
	normalManage();
}
void normalWithdrawMoney(){
	printf("Enter amount to withdraw:");
	float amt;
	scanf("%f",&amt);
	write(sd,&amt,sizeof(float));
	printf("Amount Withdrawn\n\n");
  printf("Press any key to go back to Management Portal\n");
  char c;
  read(0,&read,sizeof(char));
  //fflush(stdin);
  system("clear");
	normalManage();
}
void normalDepositMoney(){
	printf("Enter amount to deposit:");
	float amt;
	scanf("%f",&amt);
	write(sd,&amt,sizeof(float));
	printf("Money Deposited\n\n");
  printf("Press any key to go back to Management Portal\n");
  char c;
  read(0,&read,sizeof(char));
  //fflush(stdin);
  system("clear");
	normalManage();
}
void normalViewAccountBalance(){
	printf("Your account balance details are as follows:\n");
	float amt;
	read(sd,&amt,sizeof(float));
	printf("Account balance:%f\n\n",amt);
  printf("Press any key to go back to Management Portal\n");
  char c;
  read(0,&read,sizeof(char));
  system("clear");
  //fflush(stdin);
	normalManage();
}
void normalManage(){
	printf("Welcome to Your Account Management portal\n");
	printf("1.View Account Holder Details\n");
	printf("2.Change Password\n");
	printf("3.Withdraw Money\n");
	printf("4.Deposit Money\n");
	printf("5.View Balance\n");
	printf("6.Logout\n\n");
  printf("Choose an option form above:\n");
	int response;
	scanf("%d",&response);
  fflush(stdin);
	write(sd,&response,sizeof(int));
  system("clear");
	switch(response){
		case 1:
			printf("Your Account Details are:\n");
			normalAccDetails();
			break;
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
	printf("Enter your account number:");
	scanf("%d",&acc_num);
	printf("Enter your password:");
	scanf("%s",pwd);
	write(sd,&acc_num,sizeof(int));
	write(sd,pwd,MAX);
	int res;
	read(sd,&res,sizeof(int));
  fflush(stdin);
	if(res==0){
		printf("Invalid Login Details\n\nPlease any key to continue\n");
    char c;
    read(0,&c,1);
    fflush(stdin);
    system("clear");
		loginmenu();
	}else{
		printf("Login successfull\n");
    system("clear");
		normalManage();
	}
}
void normalCreate(){
	printf("Normal Account Creation Menu:\n");
	printf("Enter Account number:");
	int n;
	scanf("%d",&n);
  fflush(stdin);
	printf("Enter Account name:");
	char name1[MAX];
	scanf("%s",name1);
  fflush(stdin);
	printf("Enter Account password:");
	char pwd1[MAX];
	scanf("%s",pwd1);
  fflush(stdin);
	printf("Enter starting balance:");
	float b;
	scanf("%f",&b);
  fflush(stdin);
	struct normal_account n1;
	n1.bal=b;
	n1.acc_num=n;
	strcpy(n1.acc_name,name1);
	strcpy(n1.acc_pwd,pwd1);
	write(sd,&n1,sizeof(struct normal_account));
	printf("Account created successfully\n\n");
  printf("Press any key to continue\n");
  char c;
  read(0,&c,1);
  fflush(stdin);
  system("clear");
	loginmenu();
}
void jointAccountDetails(){
  printf("Your Account details are:\n\n");
  struct joint_account j1;
  read(sd,&j1,sizeof(struct joint_account));
  printf("First Account Holder:%s\nSecond Account Holder:%s\nAccount password:%s\nAccount number:%d\nAccount balance:%f\n\n",j1.acc_name1,j1.acc_name2,j1.acc_pwd,j1.acc_num,j1.bal);
  char k;
  printf("Press any key to go back to Management portal\n");
  read(0,&k,1);
  fflush(stdin);
  write(sd,&k,1);
  system("clear");
  jointManage();
}
void jointAccountChangePassword(){
  printf("Joint Account Change Password\n");
  printf("Enter new Password\n");
  char tarr[MAX];
  scanf("%s",tarr);
  fflush(stdin);
  write(sd,tarr,MAX);
  char t[MAX];
  read(sd,t,MAX);
  fflush(stdin);
  printf("%s\n\n",t);
  char c;
  printf("Press any key to go back to Management portal\n");
  read(0,&c,1);
  fflush(stdin);
  write(sd,&c,1);
  system("clear");
  jointManage();
}
void jointAccountWithdrawMoney(){
  printf("Joint Account Withdraw Money\n");
  printf("Enter amount to withdraw\n");
  float kamt;
  scanf("%f",&kamt);
  fflush(stdin);
  write(sd,&kamt,sizeof(float));
  char t[MAX];
  read(sd,t,MAX);
  printf("%s\n\n",t);
  char c;
  printf("Press any key to go back to Management portal\n");
  read(0,&c,1);
  write(sd,&c,1);
  system("clear");
  jointManage();
}
void jointAccountDepositMoney(){
  printf("Joint Account Deposite Money\n");
  printf("Enter amount to deposit\n");
  float kamt;
  scanf("%f",&kamt);
  fflush(stdin);
  write(sd,&kamt,sizeof(float));
  char t[MAX];
  read(sd,t,MAX);
  printf("%s\n\n",t);
  char c;
  printf("Press any key to go back to Management portal\n");
  read(0,&c,1);
  write(sd,&c,1);
  system("clear");
  jointManage();
}
void jointManage(){
  printf("Welcome to Joint Account Management Portal\n");
  printf("1.View Account Holder Details\n");
	printf("2.Change Password\n");
	printf("3.Withdraw Money\n");
	printf("4.Deposit Money\n");
	//printf("5.View Balance\n");
	printf("5.Logout\n\n");
  printf("Choose one of the options:\n");
  int res;
  scanf("%d",&res);
  fflush(stdin);
  write(sd,&res,sizeof(int));
  system("clear");
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
      printf("Deposite Money\n");
      jointAccountDepositMoney();
      break;
    default:
      loginmenu();
  }
}
void jointLogin(){
  printf("Enter your account number\n");
  scanf("%d",&jacc_num);
  fflush(stdin);
  printf("Enter your account password\n");
  scanf("%s",jpwd);
  fflush(stdin);
  write(sd,&jacc_num,sizeof(int));
  write(sd,jpwd,MAX);
  int res;
  read(sd,&res,sizeof(int));
  if(res==1){
    printf("\n\nLogin successfull\n");
    system("clear");
    jointManage();
  }else{
    printf("\n\nInvalid details\n");
    printf("Press any key to go back\n");
    char c;
    read(0,&c,1);
    system("clear");
    loginmenu();
  }
}
void jointCreate(){
  printf("Create new joint Account\n");
  printf("Enter first account holder name\n");
  char n1[MAX];
  scanf("%s",n1);
  fflush(stdin);
  printf("Enter joint account holder name\n");
  char n2[MAX];
  scanf("%s",n2);
  fflush(stdin);
  printf("Enter account password\n");
  char n3[MAX];
  scanf("%s",n3);
  fflush(stdin);
  printf("Enter amount to deposit\n");
  float kamt;
  scanf("%f",&kamt);
  fflush(stdin);
  printf("Enter account number\n");
  int a;
  scanf("%d",&a);
  fflush(stdin);
  struct joint_account j1;
  struct joint_account_d j2;
  strcpy(j1.acc_name1,n1);
  strcpy(j1.acc_name2,n2);
  strcpy(j1.acc_pwd,n3);
  j1.acc_num=a;
  j1.bal=kamt;
  j2.acc_num=a;
  strcpy(j2.acc_pwd,n3);
  write(sd,&j1,sizeof(struct joint_account));
  write(sd,&j2,sizeof(struct joint_account_d));
  printf("Account Created Successfully\n");
  printf("\n\nPress any key to go back to Management portal\n");
  char c;
  read(0,&c,1);
  fflush(stdin);
  system("clear");
  loginmenu();
}
void adminViewNormalAccountDetails(){
  printf("Enter Account number:\n");
  int anum;
  scanf("%d",&anum);
  write(sd,&anum,sizeof(int));
  struct normal_account n1;
  int res=0;
  read(sd,&res,sizeof(int));
  if(res==0){
    printf("Account not found\n\n");
    printf("Press any key to go back\n");
    char c;
    read(0,&c,sizeof(char));
    system("clear");
    adminManage();
  }
  read(sd,&n1,sizeof(struct normal_account));
  printf("Account details are:\n");
  printf("Accound number:%d\n",n1.acc_num);
  printf("Account User Name:%s\n",n1.acc_name);
  printf("Account password:%s\n",n1.acc_pwd);
  printf("Account Balance:%f\n\n",n1.bal);
  printf("Press any key to go back\n");
  char c;
  read(0,&c,sizeof(char));
  system("clear");
  adminManage();
}
void adminViewJointAccountDetails(){
  printf("Enter account id:\n");
  int id;
  scanf("%d",&id);
  write(sd,&id,sizeof(int));
  int res=0;
  read(sd,&res,sizeof(int));
  if(res==0){
    printf("Account doesn't exist\n\n");
    printf("Press any key to go back\n");
    char c;
    read(0,&c,sizeof(char));
    system("clear");
    adminManage();
  }
  struct joint_account j1;
  read(sd,&j1,sizeof(struct joint_account));
  printf("\n\nFirst Account Holder:%s\nJoint Account Holder:%s\nAccount Password:%s\nAccount Number:%d\nAccount Balance:%f\n\n",j1.acc_name1,j1.acc_name2,j1.acc_pwd,j1.acc_num,j1.bal);
  char k;
  printf("Press any key to go back\n");
  read(0,&k,sizeof(char));
  fflush(stdin);
  write(sd,&k,1);
  system("clear");
  adminManage();
}
void adminDeleteNormalAccount(){
  printf("Enter account number to delete:\n");
  int tacc;
  scanf("%d",&tacc);
  write(sd,&tacc,sizeof(int));
  printf("normal account deleted\n\n");
  printf("Press any key to go back\n");
  char c;
  fflush(stdin);
  read(0,&c,sizeof(char));
  system("clear");
  adminManage();

}
void adminDeleteJointAccount(){
  printf("Enter account number to delete\n");
  int tc;
  scanf("%d",&tc);
  write(sd,&tc,sizeof(int));
  char msg[MAX];
  read(sd,msg,MAX);
  printf("%s\n\n",msg);
  printf("press any key to continue\n");
  char c;
  read(0,&c,sizeof(char));
  system("clear");
  adminManage();
}
void adminManage(){
  printf("Admin Management Portal\n");
  printf("1.View NormalAccount Details\n");
  printf("2.View JointAccount Details\n");
  printf("3.Delete Normal Account\n");
  printf("4.Delete Joint Account\n");
  printf("5.Exit()\n\n");
  printf("Choose an option\n");
  int option;
  scanf("%d",&option);
  write(sd,&option,sizeof(int));
  system("clear");
  switch(option){
    case 1:
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

  char c;
  read(0,&c,sizeof(char));
  loginmenu();
}

void adminLogin(){
  int id;
  char apwd[MAX];
  printf("Enter your admin id:");
	scanf("%d",&id);
	printf("Enter your password:");
	scanf("%s",apwd);
	write(sd,&id,sizeof(int));
	write(sd,apwd,MAX);
	int res;
	read(sd,&res,sizeof(int));
  fflush(stdin);
	if(res==0){
		printf("Invalid Login Details\n\nPlease any key to continue\n");
    char c;
    read(0,&c,1);
    fflush(stdin);
    system("clear");
		loginmenu();
	}else{
		printf("\nLogin successfull\n");
    system("clear");
		adminManage();
	}
}
void loginmenu(){
	printf("\n\nChoose on of the following options:\n");
	printf("1.Login(Singer User Accout)\n");
	printf("2.Login(Joint Acocunt Holder)\n");
	printf("3.Admin Login\n");
	printf("4.Create Account(Single User)\n");
	printf("5.Create Account(Joint Account)\n");
	printf("6.Exit\n\n");
	int option;
	printf("Enter your choice:");
	scanf("%d",&option);
  fflush(stdin);
	write(sd,&option,sizeof(int));
  system("clear");
	switch(option){
		case 1:
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
			close(sd);
			exit(1);
	}
}
int main(int argc,char *argv[]){
	struct sockaddr_in serv;
	//memset(&serv, '0', sizeof(serv));
	char buf[80];
	char *ip_addr="14.139.155.19";
	sd=socket(AF_UNIX,SOCK_STREAM,0);
	if(sd==-1)
  {
    printf("Error in creating socket:%d\n",sd);
    printf("%s",strerror(errno));
    return 0;
  }
	int port=atoi(argv[1]);
	//port=8050;
	printf("Server on port:%d %s\n\n",port,argv[1]);
	printf("socket call successfull\n\n");
	serv.sin_family= AF_UNIX;
	//serv.sin_addr.s_addr= inet_addr(ip_addr);
	serv.sin_port=htons(port);

	if(connect(sd, (struct sockaddr *)(&serv), sizeof(serv))==-1){
		printf("Error in connect\n%s\n",strerror(errno));return 0;
	}
	printf("Connection  Successfull\n\n\n");
  system("clear");
  printf("Banking Management System\n");
	loginmenu();
  close(sd);
  return 0;
}
