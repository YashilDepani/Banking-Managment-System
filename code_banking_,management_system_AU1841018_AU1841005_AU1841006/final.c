#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<unistd.h>
#include<windows.h>
/**********************************
 Declaration of function prototypes
**********************************/
void account_number();
void rectangle();
void gotoxy(int x, int y);
void start_screen();
void password_login(int n);
void menu1();
void admin_menu();
void search_account();
void modify_account();
void delete_account();
void loan_application();
void user_menu();
void create_account();
void loan_app_no();
void user_login_menu(long int n);
void transaction(long int n,long int p,char ch,double m);
void deposite(long int n);
void withdraw(long int n);
void transfer(long int n);
void simple_interest(long int n);
void account_summary(long int n);
void loan(long int n);
void loan_application_status(long int n);
void graph(long int n);
void mini_statement(long int n);


/********************************
 Structure to define user account
 *******************************/
 
struct account
{
	long int acc_no,adhar_card;
	char password[20], name[20], address[50], occupation[20];
	double balance;
}acc;

/**************************************
 Structure to store transaction details
 *************************************/
 
struct trans
{
    long int sender,recipient;
    char status;
    double amount;
    char dt[11];
}t;

/************************************
 Structure for calculation of simple interest
*************************************/

struct interest
{
	float principal,principal1,min;
	int time;
}intrst;

/******************************
 Structure for loan application
 *****************************/

struct loan
{
 	int status,check_admin_loan,check_user_loan;
 	long int acc_no;
 	char app_no[6];
 	double amount,income;
}l;

/********************************
Function to assign account number
********************************/


void account_number()
{
	FILE *fp;
	fp=fopen("user_accounts.txt","r");
	fseek(fp,0L,2);
	long n=ftell(fp);
	acc.acc_no=1000000+(n/sizeof(acc));
}

/*****************************************
Function to assign loan application number
*****************************************/

void loan_app_no()
{
	int num=0;
	FILE *fp;
	fp=fopen("loan.txt","r");
	fseek(fp,0L,2);
	l.app_no[0]='a';
	l.app_no[1]='#';
	l.app_no[2]='0';
	l.app_no[3]='0';
	l.app_no[4]='1';
	l.app_no[5]='\0';
	long n=ftell(fp);
	n=n/sizeof(l);
	int i;
	for(i=2;i<=4;i++)
	{
		num=num*10;
		num+=(l.app_no[i]-48);
	}
	num+=n;
	i=4;
	while(num!=0)
	{
		l.app_no[i]=(num%10)+48;
		num=num/10;
		i--;
	}
	fclose(fp);
}


/*************************
Gotoxy function defination
*************************/


void gotoxy(int x, int y)
{
	COORD coord;                                       //declaration for goto function
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
	
}

/*************************
function for border formation
*************************/

void rectangle()
{
  int i,left=18,right=95,top=4,bottom=25,j;
  for(i=left; i<=right; i++)
	{
		gotoxy(i,top);
		printf("%c",178);
		gotoxy(i,bottom);
		printf("%c",178);			
	} 
  for(i=top; i<=bottom; i++)
	{
		gotoxy(left,i);
		printf("%c",178);
		gotoxy(right,i);
		printf("%c",178);
	}  
}


/*******************************
Function to display start screen
*******************************/


void start_screen()
{                                                       //forming rectangle
   int i,left=28,right=60,top=9,bottom=16,j;
   char ch;

	system("color 1E");
	
	gotoxy(39,11);
    printf("A PROJECT");
	gotoxy(42,12);
	printf("ON");
	gotoxy(32,13);
    printf("BANKING MANAGMENT SYSTEM");	

	for(i=left; i<=right; i++)
	{
		gotoxy(i,top);
		printf("%c",196);
		Sleep(10);
		gotoxy(i,bottom);
		printf("%c",196);
		Sleep(10);	
			
	}
	for(i=0; i<=14; i++)
	{
		gotoxy(i+28,11-i);
		printf("%c",249);
		Sleep(10);
	}
	for(i=0; i<=10; i++)
	{
		gotoxy(39+i,0);
		printf("%c",249);
		Sleep(10);
	}
	for(i=0; i<=11; i++)
	{
		gotoxy(60-i,11-i);
		printf("%c",249);
	}
	for(i=left+3; i<+right-3; i++)
	{
		gotoxy(i,14);
		printf("%c",196);
		Sleep(20);
	}
	for(i=right; i<=44; i++)
	{
		gotoxy(i,j);
		printf("%c",249);
	}
	
	for(i=top; i<=bottom; i++)
	{
		gotoxy(left,i);
		printf("%c",182);
		Sleep(20);
		gotoxy(right,i);
		printf("%c",182);
		Sleep(20);
	}	
	gotoxy(41,3);
	printf("Welcome");
	gotoxy(43,4);
	printf("To");
	gotoxy(41,6);
	printf("BJP Bank");
	gotoxy(42,8);
	printf("$ $ $");
	
	gotoxy(0,19);
	printf("Press any-key to contiue\n");
	ch=getch();
	//system("cls");
	menu1();
}

/*******************************
Function for password login and validation
*******************************/


void password_login(int n)
{
	char ch='n';
	long int username1;
	int flag=0,check1=0;
	do
	{
		system("cls");
		rectangle();
		gotoxy(20,6);
		printf("%c Username:",15);
		scanf("%ld",&username1);
		int i;
		char password1[20],pswrd1;
		gotoxy(20,8);
		printf("%c Password:",15);
	
		for(i=0; i<20; i++)
		{
			pswrd1=getch();
			password1[i]=pswrd1;
			if(pswrd1!=13&&pswrd1!=8)
			printf("*");
			if(pswrd1==13)
			break;
			if(pswrd1==8)
			{
				printf("\b");
				printf(" ");
				printf("\b");
				--i ;
				i--;
			}
		}
		password1[i]='\0';
		gotoxy(0,0);
		//printf("%s",acc.password)
		if(n==1)
		{
			FILE *fp;
			fp=fopen("user_accounts.txt","a+");
			while(fread(&acc,sizeof(struct account),1,fp))
			{
				ch='n';
				if(acc.acc_no==username1)
				{
					//flag=1;
					//	gotoxy(0,0);
					//	printf("%s",acc.password);
					if(strcmp(acc.password,password1)==0)
					{
						gotoxy(20,10);
						printf("Access Granted");
						check1=1;
						break;
					}
				}
			}
			if(check1==0)
			{
				gotoxy(20,10);
				printf("Access denied");
				gotoxy(20,11);
				printf("Do you want to retry(y/n)???");
				ch=getch();			
			}
		}
		if(n==2)
		{
			if(username1==12345678)
				{
					flag=1;                                     /****************************
					                                                 admin login
					                                             **************************/
					if(strcmp("admin",password1)==0)
					{
						gotoxy(20,10);
						printf("Access Granted");
						check1=1;
						break;
					}
				}
			if(check1==0)
			{
				gotoxy(20,10);
				printf("Access denied");
				gotoxy(20,11);
				printf("Do you want to retry  (y/n)???");
				ch=getch();			
			}
		}
	}while(ch=='y');
	if(check1==1)
	{
		char con;
		gotoxy(0,27);
		printf("Press Enter to continue...");
		while(con!=13)
		con=getch();
		if(n==1)
		user_login_menu(username1);
		if(n==2)	
		admin_menu();
	}
	if(check1==0)
	{
		system("cls");
		if(n==1)
			user_menu();
		if(n==2)
			menu1();
	}	
}


/*******************************
Function to input type of user
*******************************/


void menu1()
{
  int n;
  menu:    
  system("cls");
  rectangle();  
  gotoxy(20,6);                                       
  printf("1.%c Admin login",15);
  gotoxy(20,8);
  printf("2.%c Other user",15);
  gotoxy(20,10);
  printf("3.%c back to main menu",15);
  //back();
  gotoxy(0,27);
  printf("enter your option:.....");
  scanf("%d",&n);
  
  switch(n)
  	{
  		case 1:
  			{
			 password_login(2);
  			 break;
  			}
  		case 2:
  			{
			 user_menu();
  			 break;
  			}
  		case 3:
  			{
  				system("cls");
				  main();
  				break;
			  }
  		default:
  			{
  				gotoxy(0,0);
			 printf("enter valid option  \n");
  			goto menu;
  			break;
  			}
  	}  
}


/*******************************
         ADMIN Menu
*******************************/


void admin_menu()
{
	system("cls");
	rectangle();
	gotoxy(0,0);
    printf("welcome to BJP bank");
    gotoxy(20,6);
    printf("1.%c search account",15);
    gotoxy(20,8);
	printf("2.%c modify account",15);
	gotoxy(20,10);
	printf("3.%c delete account",15);
	gotoxy(20,12);
	FILE *fp;
	fp=fopen("loan.txt","r");
	int flag=0;
	while(fread(&l,sizeof(struct loan),1,fp))
	{
		if(l.check_admin_loan==1)
		flag++;
	}
	if(flag==0)
		printf("4.%c Loan applicatins",15);
	else
		printf("4.%c Loan applicatins(%d new)",15,flag);
	gotoxy(20,14);
	printf("5.%c logout",15);
	gotoxy(0,27);
	printf("enter your choice....");
	int choice;
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1:search_account();
				break;
		case 2:modify_account();
				break;
		case 3:delete_account();
				break;	
		case 4:loan_application();
				break;		
		case 5:menu1();
				break;			
	}
	
}


/****************************
Function to search an account
****************************/


void search_account()
{
	FILE *fp;
	char con=0;
	fp=fopen("user_accounts.txt","r");
	system("cls");
	rectangle();

	long int n;
	gotoxy(20,6);
	printf("%c enter account number u want to search: ",15);
	scanf("%ld",&n);
	while(fread(&acc,sizeof(struct account),1,fp)==1)
	{
		if(n==acc.acc_no)
		{
		
			gotoxy(20,8);
			printf("%c user's account number is %ld",15,acc.acc_no);
			gotoxy(20,10);
			printf("%c user's current balacne is  %.2lf\n",15,acc.balance);
			gotoxy(20,12);
			printf("%c user's name is  %s",15,acc.name);
			gotoxy(20,14);
			printf("%c user's address is %s",15,acc.address);
			gotoxy(20,16);
			printf("%c new password is %s",15,acc.password);
			gotoxy(20,18);
			printf("%c new occupation is %s",15,acc.occupation);
	break;
		}
	}
	
	gotoxy(0,27);
	fflush(stdin);
	printf("press enter to continue...");
	while(con!=13)
	con=getch();
	admin_menu();
}

/****************************
Function to modify an account
****************************/

void modify_account()
{
	FILE *fp;
	fp=fopen("user_accounts.txt","r+");
	long int n;
	char another='y';
	char con;
	system("cls");
	rectangle();
	while(another=='y')
	{
		gotoxy(20,6);
		printf("%c enter account number of the account you want to modify: ",15);
		scanf("%ld",&n);	
		rewind(fp);
		while(fread(&acc,sizeof(struct account),1,fp)==1)
		{
			if(n==acc.acc_no)
			{
				
				gotoxy(20,8);
				printf("%c enter new name : ",15);
				scanf("%s",acc.name);
				gotoxy(20,10);
				printf("enter new password: ");
				int i;
				char pswrd2;
				
				for(i=0; i<20; i++)
				{
					pswrd2=getch();
					acc.password[i]=pswrd2;
					if(pswrd2!=13 && pswrd2!=8)
					printf("*");
					if(pswrd2==13)
					break;
					if(pswrd2==8)
					{
						printf("\b");
						printf(" ");
						printf("\b");
						--i ;
						i--;
					}
				}
				
				gotoxy(20,12);
				printf("%c enter new address: ",15);
				scanf("%s",acc.address);
				fflush(stdin);
				gotoxy(20,14);
				printf("%c enter new occupation: ",15);
				scanf("%s",acc.occupation);
				fseek(fp,-sizeof(struct account),1);
				fwrite(&acc,sizeof(struct account),1,fp);
				break;
			}	
		}
			
		gotoxy(20,20);	
		printf("do you want to modify other account (y/n)...");
		fflush(stdin);
		another=getche();
		
		}
		fclose(fp);
		gotoxy(0,27);
		printf("please close the console for better functioning of the programme");
		//printf("press enter to continue...");
		while(con!=13)
		con=getch();
		admin_menu();		
}
	
/****************************
Function to delete an account
****************************/
	
void delete_account()
{
	FILE *fp,*fp1;
	fp=fopen("user_accounts.txt","r");
	fp1=fopen("temp.txt","w");
	long int n;
	char con;
	system("cls");
	rectangle();
	gotoxy(20,6);
	printf("%c enter account number of the account you want to delete: ",15);
	scanf("%ld",&n);
	rewind(fp);
	while(fread(&acc,sizeof(struct account),1,fp)==1)
	{
		if(n!=acc.acc_no)
		{
			fwrite(&acc,sizeof(struct account),1,fp1);
		}
	}
	gotoxy(20,8);
	printf("%c account of account number %d has been deleted successfully:  ",15,n);
	
	remove("user_accounts.txt");
	rename("temp.txt","user_accounts.txt");
	
	fclose(fp);
	fclose(fp1);
	
	gotoxy(0,27);
	printf("press enter to continue...");
	while(con!=13)
	con=getch();
	
	admin_menu();
		
		
}
	
/*******************************
       Loan application
*******************************/

void loan_application()
{
	system("cls");
	char app_no[6];
	FILE *fp;
	FILE *fp2;
	fp=fopen("loan.txt","r+");
	fp2=fopen("user_accounts.txt","r+");
	rectangle();
	int i=5;
	
	while(fread(&l,sizeof(struct loan),1,fp))
	{
		if(l.status==0)
		{
			i++;
			gotoxy(20,i);
			puts(l.app_no);
		}
	}
	
	gotoxy(0,27);
	printf("Enter the application number to open:");
	for(i=0;i<5;i++)
	{
		app_no[i]=getch();
		printf("%c",app_no[i]);
	}
	
	app_no[5]='\0';
	fseek(fp,0L,0);
	system("cls");
	rectangle();
	
	while(fread(&l,sizeof(struct loan),1,fp))
	{
		if(strcmp(l.app_no,app_no)==0)
		{
			gotoxy(20,6);
			printf("Account Number:%ld",l.acc_no);
			gotoxy(20,8);
			printf("Ammount of loan:%lf",l.amount);
			gotoxy(20,10);
			printf("Monthly income:%lf",l.income);
			break;			
		}
	}
	
	gotoxy(20,12);
	printf("1.%c Sanction Loan",15);
	gotoxy(20,14);
	printf("2.%c Reject Loan",15);
	gotoxy(20,16);
	printf("3.%c Return to main menu",15);
	int menu;
	gotoxy(0,27);
	printf("Enter your choice");
	
	scanf("%d",&menu);
	switch(menu)
	{
		case 1:{
					l.status=1;
					l.check_admin_loan=0;
					l.check_user_loan=1;
					fseek(fp,-sizeof(struct loan),1);
    				fwrite(&l,sizeof(struct loan),1,fp);
    				while(fread(&acc,sizeof(struct account),1,fp2))
    				{
    					if(acc.acc_no==l.acc_no)
    					{
    						acc.balance+=l.amount;
    						break;
						}
					}
					transaction(l.acc_no,l.acc_no,'D',l.amount);
					fseek(fp2,-sizeof(struct account),1);
    				fwrite(&acc,sizeof(struct account),1,fp2);
					break;
				}
				
		case 2:{
					l.status=-1;
					l.check_admin_loan=0;
					l.check_user_loan=1;
					fseek(fp,-sizeof(struct loan),1);
    				fwrite(&l,sizeof(struct loan),1,fp);
					break;
				}
				
		case 3:{
					l.check_admin_loan=0;
					fseek(fp,-sizeof(struct loan),1);
    				fwrite(&l,sizeof(struct loan),1,fp);
    				admin_menu;
					break;
				}
				
	}
	
	fclose(fp);
	fclose(fp2);
	char con;
	printf("press enter to continue...");
	while(con!=13)
	con=getch();
	
	admin_menu();
}



/*******************************
         USER Menu
*******************************/


void user_menu()
{
	system("cls");
	int menu;
	
	rectangle();
	
	gotoxy(20,6);
	printf("1.%c Create account",15);
	gotoxy(20,8);
	printf("2.%c Login",15);
	gotoxy(20,10);
	printf("3.%c back",15);
	gotoxy(0,27);
	printf("Enter your option:.....");
	 // after main menu
	scanf("%d",&menu);
	
	switch(menu)
	{
		case 1:create_account();
			   break;
		case 2:password_login(1);
			   break;
		case 3:menu1();
			   break;
	}
}


/*******************************
Function to create a new account
*******************************/


void create_account()
{
	char con=0;
	system("cls");
	
	rectangle();
	
	FILE *acc_file;
	acc_file = fopen("user_accounts.txt","a");
	
	fflush(stdin);
	gotoxy(20,6);
	printf("%c Enter your name:",15);
	gets(acc.name);
	fflush(stdin);
	gotoxy(20,8);
	printf("%c Enter your address:",15);
	gets(acc.address);
	fflush(stdin);
	gotoxy(20,10);
    printf("%c Enter your adhar card no.:",15);
	scanf("%ld",&acc.adhar_card);
	fflush(stdin);	
	gotoxy(20,12);
	printf("%c Enter your occupation:",15);
	gets(acc.occupation);
	fflush(stdin);	
	gotoxy(20,14);
	printf( "Enter your password:");
	//printf("\t\t\t");
	int i;
	char pswrd;
	for(i=0; i<20; i++)
		{
			pswrd=getch();
			acc.password[i]=pswrd;
			if(pswrd!=13&&pswrd!=8)
			printf("*");
			if(pswrd==13)
			break;
			if(pswrd==8)
			{
				printf("\b");
				printf(" ");
				printf("\b");
				--i ;
				i--;
			}
		}
	acc.password[i]='\0';
	fflush(stdin);
	account_number();	
	acc.balance=0;
	fwrite(&acc,sizeof(struct account),1,acc_file);
	gotoxy(20,16);
	printf("Congratulations!!!Your account has been created.");
	gotoxy(20,17);
	printf("Your account number is %ld.",acc.acc_no);
	gotoxy(20,18);
	printf("Use this *%ld* account number as your",acc.acc_no);
	gotoxy(20,19);
	printf("username to login your account.");
	fclose(acc_file);
	gotoxy(0,27);
	printf("Press enter to continue:...");
	while(con!=13)
	con=getch();
	user_menu();
}


/**********************************
Function to display user login menu
**********************************/


void user_login_menu(long int n)
{
	int menu,flag=0;
	do
	{
		flag=0;
		system("cls");	
		rectangle();
		gotoxy(20,6);
		printf("1.%c Deposit Money",15);
		gotoxy(20,8);
		printf("2.%c Withdraw Money",15);
		gotoxy(20,10);
		printf("3.%c Transfer Money",15);
		gotoxy(20,12);
		printf("4.%c Deposit money for simple interest",15);
		gotoxy(20,14);
		printf("5.%c Check Account Summary",15);
		gotoxy(20,16);
		printf("6.%c Apply for loan",15);
		gotoxy(20,18);
		FILE *fp;
		fp=fopen("loan.txt","r");
		int flag=0;
		while(fread(&l,sizeof(struct loan),1,fp))
		{
			if(l.acc_no==n)
			{
				if(l.check_user_loan==1)
				flag++;
			}
		}
		printf("7.%c Check loan application status",15);
		gotoxy(20,20);
		printf("8.%c View mini Statment",15);
		gotoxy(20,22);
		printf("9.%c View graph of transaction",15);
		gotoxy(20,24);
		printf("10.%c Logout",15);
		gotoxy(0,27);
		printf("Enter your choice:.....");
		
		scanf("%d",&menu);
		switch(menu)
		{
			case 1:{
						deposite(n);
						break;
			       }
			case 2:{
						withdraw(n);
						break;
				   }
			case 3:{
						transfer(n);
						break;
				   }
		    case 4:{
						simple_interest(n);	   	
						break;
				   }       
			case 5:{
						account_summary(n);
						break;
				   }       
			case 6:{
						loan(n);
						break;
				   }
			case 7:{
						loan_application_status(n);
						break;
				   }	   
			case 8:{
						mini_statement(n);
						break;
				   } 
			case 9:{
						graph(n);
						break;
					}
			case 10:{
						user_menu();
						break;
					}
					      				   
		   default:{
						gotoxy(0,0);
						printf("Enter valid option...");
						Sleep(1000);
						flag=1;
						break;
				   }       
		}
	}while(flag==1);
}


/*****************************************
Function to record transcations in a file
*****************************************/


void transaction(long int sender, long int recipient,char ch,double m)
{
    char buff[20];
    struct tm *sTm;
    FILE *fp;
	fp = fopen("transections.txt","a");
	t.sender= sender;
	t.recipient=recipient;
	t.status=ch;
	t.amount=m;
	time_t now = time (0);
    sTm = gmtime (&now);
	strftime (buff, sizeof(buff), "%d/%m/%Y", sTm);
    strcpy(t.dt,buff);
	fwrite(&t,sizeof(struct trans),1,fp);
	getch();
	fclose(fp);
}


/*****************************************
Function to deposite money into an account
*****************************************/


void deposite(long int n)
{
	char con;
	double deposite;
	system("cls");
	rectangle();
	FILE *fp;
	fp=fopen("user_accounts.txt","r+");
	while(fread(&acc,sizeof(struct account),1,fp))
	{
		if(n==acc.acc_no)
		{
			gotoxy(20,6);
			printf("%c Current Account balance is : %.2lf",15,acc.balance);
			gotoxy(20,8);
			printf("Enter the amount to deposite:");
			scanf("%lf",&deposite);
			
			transaction(n,n,'D',deposite);
			acc.balance+=deposite;
			if(n==10)
			fseek(fp,0L,0);
			else
			fseek(fp,-sizeof(struct account),1);
			fwrite(&acc,sizeof(struct account),1,fp);
			gotoxy(20,10);
			printf("%c Account Balance after last transaction: %.2lf",15,acc.balance);
			gotoxy(20,12);
			break;
		}		
	}
	fclose(fp);
	gotoxy(0,27);
	printf("Press enter to continue...");
	
	while(con!=13)
	con=getch();
	user_login_menu(n);
}


/*****************************************
Function to withdraw money from an account
*****************************************/


void withdraw(long int n)
{
	char con;
	double withdraw;
	system("cls");
	rectangle();
	FILE *fp;
	fp=fopen("user_accounts.txt","r+");
	while(fread(&acc,sizeof(struct account),1,fp))
	{
		if(n==acc.acc_no)
		{
			gotoxy(20,6);
			printf("%c Current Account balance:%.2lf",15,acc.balance);			
			gotoxy(20,8);
			printf("%c Enter the amount to withdrawal:",15);
			scanf("%lf",&withdraw);
			if(withdraw > acc.balance)
			{
				gotoxy(20,10);
				printf("Account limit exceed");
				break;
			}
			else
			{
			transaction(n,n,'W',withdraw);	
			acc.balance-=withdraw;
			/*if(n==1000000)
			fseek(fp,0L,0);
			else*/
			fseek(fp,-sizeof(struct account),1);
    		fwrite(&acc,sizeof(struct account),1,fp);
			gotoxy(20,10);
			printf("Account Balance after last transaction: %.2lf",acc.balance);
			gotoxy(20,12);
			break;}
		}		
	}
	fclose(fp);
	gotoxy(0,27);
	printf("Press enter to continue...");
	
	while(con!=13)
	con=getch();
	user_login_menu(n);	
}


/*****************************************
Function to transfer money into an account
*****************************************/


void transfer(long int n)
{
	char con;
	double transfer;
	long int recipient;
	system("cls");
	rectangle();
	FILE *fp;
	fp=fopen("user_accounts.txt","r+");
	while(fread(&acc,sizeof(struct account),1,fp))
	{
		if(n==acc.acc_no)
		{
			gotoxy(20,6);
			printf("%c Current Account balance: %.2lf",15,acc.balance);			
			gotoxy(20,8);
			printf("%c Enter the amount to transfer:",15);
			scanf("%lf",&transfer);	
			if(transfer > acc.balance)
			{
				gotoxy(20,10);
				printf("Account limit exceed");
				break;
			}
			else
			{
				gotoxy(20,10);	
				printf("%c Enter the account number of the recipient:",15);
				scanf("%ld",&recipient);
			
				transaction(n,recipient,'T',transfer);	
				acc.balance-=transfer;
				/*if(n==1000000)
				fseek(fp,0L,0);
				else*/
				fseek(fp,-sizeof(struct account),1);
    			fwrite(&acc,sizeof(struct account),1,fp);
    			gotoxy(20,12);
				printf("%c Account Balance after last transaction:%.2lf",15,acc.balance);
				gotoxy(20,12);
			}
			break;
		}		
	}
	fseek(fp,0L,0);
	while(fread(&acc,sizeof(struct account),1,fp))
	{
		if(recipient==acc.acc_no)
		{		
			acc.balance+=transfer;
			if(recipient==10)
			fseek(fp,0L,0);
			else
			fseek(fp,-sizeof(struct account),1);
    		fwrite(&acc,sizeof(struct account),1,fp);
			break;
		}		
	}
	fclose(fp);
	gotoxy(0,27);
	printf("Press enter to continue...");
	while(con!=13)
	con=getch();
	user_login_menu(n);	
}


/*******************************
Function for simple interest
*******************************/


void simple_interest(long int n)
{
	system("cls");
	rectangle();
	FILE *fp5;
	FILE *fp6;
	int t;
	char con;
	double deposite;
	float interest=0,amount,sum,temp;
	
	fp5=fopen("interest.txt","a+");
	fp6=fopen("user_accounts.txt","r+");
	
	time_t t1,t2;
	
	while(fread(&acc,sizeof(struct account),1,fp6))
	{
		if(n==acc.acc_no)
		{
		gotoxy(20,6);
		printf("****Our Bank Offers 10%% Rate of Interest per 5 min****");
		gotoxy(20,8);
		printf("1.%c Enter the amount for the interest:",15);
		gotoxy(20,10);
		printf("2.%c view the updated amount:",15);
		

		gotoxy(0,27);
		printf("enter your option.....:");
	
		scanf("%d",&t);		
		switch(t)
		{
		case 1:
			{
				system("cls");
				rectangle();
				gotoxy(20,6);
				printf("%c Enter the amount for deposition:  ",15);
				scanf("%f",&intrst.principal);
				intrst.principal1=intrst.principal;
				gotoxy(20,8);
				printf("%c for how much min you want to deposit the money:  ",15);
				scanf("%f",&intrst.min);
				intrst.time=time(&t1);
				fwrite(&intrst,sizeof(struct interest),1,fp5);
				gotoxy(20,10);
				printf("%c NOTE: Remember this amount for further reqiurments:",15);	
			break;
			}
		case 2:
			{
				system("cls");
				rectangle();
				gotoxy(20,6);
				printf("%c Enter the deposited amount for viewing the updated amount:",15);
				scanf("%f",&temp);
				
			
				while(fread(&intrst,sizeof(struct interest),1,fp5))
				{
					if(temp==intrst.principal)
					{
						sum=intrst.principal*(float)(time(&t1)-intrst.time);
						intrst.principal1+=sum/3000;
						
						if(intrst.principal1<=intrst.principal+intrst.principal/3000*(intrst.min*60))
						{
					
							intrst.time=t2;
							fseek(fp5,-sizeof(struct interest),1);
							fwrite(&intrst,sizeof(struct interest),1,fp5);
							gotoxy(20,8);
							printf("%c The updated amount is:%f",15,intrst.principal1);
							sleep(1);
							break;
						}
						else
						{
							intrst.principal1=intrst.principal;
							intrst.principal1+=intrst.principal/3000*(intrst.min*60);
							fseek(fp5,-sizeof(struct interest),1);
							fwrite(&intrst,sizeof(struct interest),1,fp5);
							//gotoxy(20,8);
							//printf("%c The updated amount is:%f",15,intrst.principal1);
							break;
						}
					}
				}
			break;
			}
		}
			if(intrst.principal1==intrst.principal+intrst.principal/3000*(intrst.min*60))
			{
				system("cls");
				rectangle();
				deposite=intrst.principal1;
				transaction(n,n,'D',deposite);
				acc.balance+=deposite;
				if(n==10)
				fseek(fp6,0L,0);
				else
				fseek(fp6,-sizeof(struct account),1);
				fwrite(&acc,sizeof(struct account),1,fp6);
				gotoxy(20,6);
				printf("%c......congratulations.....",15);
				gotoxy(20,8);
				printf("%c Your account has been updated with amount Rs.%.2f",15,intrst.principal1);
				gotoxy(20,10);
				printf("%c Now you use this money for any purpose",15);
			}
		}
	}
	fclose(fp5);
	fclose(fp6);
	gotoxy(0,27);
	printf("press enter to continue....");
	while(con!=13)
	con=getch();
	
	user_login_menu(n);
}


/*******************************
Function to view account summary
*******************************/


void account_summary(long int n)
{
	char con;
	FILE *fp;
	fp=fopen("user_accounts.txt","r+");
	system("cls");
	rectangle();
	while(fread(&acc,sizeof(struct account),1,fp))
	{
		if(n==acc.acc_no)
		{
			gotoxy(20,6);
			printf("%c Account number:%ld",15,acc.acc_no);
			gotoxy(20,8);
			printf("%c Account balance:%.2lf",15,acc.balance);
			gotoxy(20,10);
			//printf("%c back",15);
			//back(1);
			
			break;
		}		
	}
	fclose(fp);
	gotoxy(0,27);
	printf("Press enter to continue...");
	while(con!=13)
	con=getch();
	user_login_menu(n);		
}

/*************************
Function to apply for loan
*************************/

void loan(long int n)
{
	FILE *fp;
	fp=fopen("loan.txt","a");
	system("cls");
	l.acc_no=n;
	l.check_admin_loan=1;
	l.check_user_loan=0;
	l.status=0;
	rectangle();
	gotoxy(20,6);
	printf("Enter the amount of loan:");
	scanf("%lf",&l.amount);
	gotoxy(20,8);
	printf("Enter your monthly income:");
	scanf("%lf",&l.income);
	gotoxy(20,10);
	printf("NOTE: Monthly income should be greater then loan");
	loan_app_no();
	fwrite(&l,sizeof(struct loan),1,fp);
	gotoxy(20,10);
	printf("Your loan application has been generated");
	gotoxy(20,12);
	printf("Your loan application number is:");
	puts(l.app_no);
	fclose(fp);	
	char con;
	gotoxy(0,27);
	printf("Press enter to continue...");
	while(con!=13)
	con=getch();
	user_login_menu(n);	
}

/****************************************
Function to check loan application status
****************************************/

void loan_application_status(long int n)
{
	FILE *fp;
	fp=fopen("loan.txt","r");
	system("cls");
	char app_no[6];
	rectangle();
	gotoxy(20,6);
	printf("Enter your loan application number:");
	int i;
	for(i=0;i<5;i++)
	{
		app_no[i]=getch();
		printf("%c",app_no[i]);
	}
	app_no[5]='\0';
	system("cls");
	rectangle();
	while(fread(&l,sizeof(struct loan),1,fp))
	{
		if(strcmp(l.app_no,app_no)==0)
		{
			gotoxy(20,6);
			printf("Loan application number:");
			puts(l.app_no);
			l.check_user_loan=0;
			gotoxy(20,8);
			if(l.status==0)
			{
				printf("Your loan application is in queue");
			}
			if(l.status==1)
			{
				printf("Congratulations!!!Your loan has been sanctioned.");
				gotoxy(20,9);
				printf("The ammount has been transferred to your account.");
			}
			if(l.status==-1)
			{
				printf("Your loan application has been rejected");
			}
			fseek(fp,-sizeof(struct loan),1);
    		fwrite(&l,sizeof(struct loan),1,fp);
    		break;
		}	
	}
	fclose(fp);	
	char con;
	gotoxy(0,27);
	printf("Press enter to continue...");
	while(con!=13)
	con=getch();
	user_login_menu(n);	
}

/************************************************
Function to view the mini statement of an account
************************************************/


void mini_statement(long int n)
{
	char con;
	int i=6;
	FILE *fp;
	fp=fopen("transections.txt","r");
	system("cls");
	rectangle();
	//fseek(fp,0L,0);
	while(fread(&t,sizeof(struct trans),1,fp))
	{
		if((n==t.sender)||(n==t.recipient))
		{
			if(t.status!='T')
			{
				gotoxy(20,i);
				printf("%c %s %c Account no::%7ld Amount:Rs%.2lf\n",15,t.dt,t.status,t.sender,t.amount);
			}
			else
			{
				gotoxy(20,i);
				printf("%c %s %c From:%7ld To:%7ld Amount:Rs%.2lf\n",15,t.dt,t.status,t.sender,t.recipient,t.amount);
			}
			i++;
		}
	}
	fclose(fp);
	gotoxy(0,27);
	printf("Press enter to continue...");
	while(con!=13)
	con=getch();
	user_login_menu(n);	
}

/************************************************
Function to view graph of transactions
************************************************/

void graph(long int n)
{
	system("cls");
	double amount=0,j,i;
	char con;
	gotoxy(0,1);
    printf("\t\t\t\t\tTHE TRANSACTION SUMMARY");
    gotoxy(0,2);
 	 for(i=0; i<=110; i++)
  	{
  		printf("%c",169);
  	}
  
  int scale=100;
  gotoxy(0,3);
  printf("       -1000    -800    -600     -400     -200      0      200      400      600      800      1000     1200");
  gotoxy(0,4);
  for(i=0; i<=110; i++)
  {
  	printf("%c",196);
  }
  
  for(i=5; i<26; i++)
  {
  	gotoxy(52,i);
  	printf("%c",219);
  }
	FILE *fp3;
	fp3=fopen("transections.txt","r");
	i=0;
	
		while(fread(&t,sizeof(struct trans),1,fp3))
		{
			if((n==t.sender) || (n==t.recipient))	
			{
			
				gotoxy(52,2*(i+3));
				if(t.status=='D')
				{
					amount=t.amount*9/200;
					for(j=0; j<=amount; j++)
					{
						printf("%c",178);
					}
					printf("%.2lf",t.amount);
					i++;
				}
				if(t.status=='W')
				{
					amount=-(t.amount*9/200);
					for(j=amount; j<0; j++)
					{
						gotoxy(52+j,2*(i+3));
						printf("%c",178);
					}
					gotoxy(52+amount-7,2*(i+3));
					printf("%.2lf",t.amount);
					i++;	
				}
				if(t.status=='T')
				{
					if(t.sender==n)
					{
						amount=-(t.amount*9/200);
						for(j=amount; j<0; j++)
						{
							gotoxy(52+j,2*(i+3));
							printf("%c",178);
						}
						gotoxy(52+amount-7,2*(i+3));
				    	printf("%.2lf",t.amount);
						i++;	
					}
					else
					{
						amount=t.amount*9/200;
						for(j=0; j<=amount; j++)
						{
							printf("%c",178);
						}
						printf("%.2lf",t.amount);
						i++;		
					}		
				}
			}
		}
	fclose(fp3);
	gotoxy(0,28);
	printf("Press enter to continue...");
	while(con!=13)
	con=getch();
	user_login_menu(n);	
}


/************************************************
              VOID MAIN FUNCTION
************************************************/


void main()
{
	start_screen();
}
