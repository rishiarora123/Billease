#include <iostream>    //for c++ print options
#include<windows.h>
#include<mysql.h>      // for my sql
#include<string.h>     // for string
#include <sstream>     // stringstream
#include<stdio.h>      // for c outputs
#include <iomanip>     // for set width
#include <time.h>      // for date and time
using namespace std;
int add();
static int no=0,total_product=0, d_name=1,total_price=0;
static string pname;
static MYSQL* conn;
int pass();
int n();
void sql_work();
void connectsql();
int bill();
int price();
int passs();
int prdata();
int getsqldata();
int allprint();
void print();
void print();
void deletedatabase();
void pr(int n);
struct pr{
    int srno;
    char name[50];
    char price[10];
}p[50];
struct data{
    int srno;
    char name[30],price_str[10];
    int price;
}d[30];
int main(){
    int choice;
    again:
    string name;
    cout<<"Please Enter your First name: ";
    cin>>pname;
    if(pname=="ri"){
        int password;
        cout<<"Enter the password:";
        cin>>password;
        if(password==123){
            passs();
            goto again;
        }
        else{
            goto again;
        }
    }
    total_price=0;
    cout<<"\n\n Hello "<<pname<<" , I am your assistant today so choose your no. according To your need.....\n\n";
    system("pause");
    system("cls");
    again2:
    printf("==========================================================================\n");
    printf("1.Price check\n2.Print Bill\n3.Admin mode\n4.Exit\n");
    printf("--------------------------------------------------------------------------\n");
    printf("Enter your Choice:");
    scanf("%d",&choice);
    printf("==========================================================================\n\n");
    switch(choice){
        case 1:
        price();
        system("pause");
        system("cls");
        goto again2;
        case 2:
        allprint();
        bill();
        total_product=0;
        system("cls");
        goto again;
        case 3:
        pass();
        system("cls");
        goto again;
        case 4:
        break;
    }
    return 0;
}
void deletedatabase(){
     connectsql();
     if(conn){
        int qstate = 0;
        for(int i=0;i<=1000;i++){
            qstate = 0;
            stringstream ss;
            ss<<"DROP TABLE `bill"<<i<<"`";
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
        }
     }
}
void connectsql(){
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "", "ddd", 3306, NULL, 0);
}
void sql_work(){
    connectsql();
    string dummy;
    if(conn){
        int qstate = 0;
        for(d_name;d_name<=d_name;d_name){
            stringstream ss;
            ss<<"CREATE TABLE `ddd`.`bill"<<d_name<<"` ( `Serial no` INT(3) NOT NULL AUTO_INCREMENT , `pname` TEXT NOT NULL ,`srno` INT(3) NOT NULL ,  `name` TEXT(20) NOT NULL ,  `price` INT(5) NOT NULL , `Time` TEXT(25) NOT NULL ,    PRIMARY KEY  (`Serial no`)) ENGINE = InnoDB";
            string query = ss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
            break;
        }

        for(int i=1;i<=total_product+1;i++){
          if(total_product+1==i){
              stringstream ss;
              ss << "INSERT INTO bill"<<d_name<<"(name,price) VALUES('Total','" <<total_price<<"')";
              string query = ss.str();
              const char* q = query.c_str();
              qstate = mysql_query(conn, q);
              break;
          }
          time_t my_time = time(NULL);
          stringstream ss;
          string name=d[i].name;
          int srno=d[i].srno,price=d[i].price;
          if(i==1){
            stringstream sss;
            sss << "INSERT INTO bill"<<d_name<<"(pname,srno,name,price,Time) VALUES('" <<pname<<"','"<< srno << "','" << name << "','" << price<<"','"<< ctime(&my_time) <<"')";
            string query = sss.str();
            const char* q = query.c_str();
            qstate = mysql_query(conn, q);
          }
          else{
                ss << "INSERT INTO bill"<<d_name<<"(srno,name,price) VALUES('" << srno << "','" << name << "','" << price <<"')";
                string query = ss.str();
                const char* q = query.c_str();
                qstate = mysql_query(conn, q);
          }
          system("cls");
          cout<<"\n\nThe bill was send to labour please wait to call by owner\n\n";

          if(qstate != 0)
             cout << "Insert Error" << mysql_error(conn) << endl;
        }
        system("pause");
    }
    else{
        cout << "Connection Error" << endl;
    }
    d_name++;
    //system("pause");
    //system("cls");
}
int passs(){
        system("cls");
        int aaa;
        re:
        cout<<"1.Add items details\n2.delete all database bill\n\nEnter Choice:";
        cin>>aaa;
        if(aaa==1){
            add();
            return 0;
        }
        if(aaa==2){
            deletedatabase();
            cout<<"All tables deleted successful\n please reboot this program.......\n ";
            system("pause");
            system("cls");
        }
        else{
            cout<<"wrong choice pls try again \n";
            goto re;
        }
}
int pass(){
    char un[]="ri",pass[]="123";
    char un2[10],pass2[10],wr=0;
    retry:
    if(wr==3){
        printf("------You try maximum time retry after some time-------\n\n\n");
        return 0;
    }
    printf("Enter username:");
    scanf("%s",&un2);
    printf("Enter password:");
    scanf("%s",&pass2);
    if(strcmp(un2,un)==0 && strcmp(pass2,pass)==0){
        passs();
    }
    else{
        printf(":::::::::::You Entered Wrong Details::::::::::::\n\n");
        printf("--------------------RETRY-----------------------\n\n");
        wr++;
        goto retry;
    }
    return 0;
}
int add(){
    char name[100],data[1024],*value,add[50];
    int srno,price,j,i,m;
    n();
    allprint();
    printf("The last serial no. is %d\n\n",no);
    no++;
    printf("--------------------------------------------------------------------------\n");

    printf("how many items data you enter:");
    scanf("%d",&m);
    FILE *fp=fopen("2project.csv","a");
    for(j=0;j<m;j++){
     value=strtok(data,",");
     srno=no;
     no++;
     printf("\n\n**************************************************************************\n");
     printf("Enter Name:");
     scanf("%s",&name);
     printf("Enter price:");
     scanf("%d",&price);
     fprintf(fp,"%d,%s,%d,\n",srno,name,price);
     printf("**************************************************************************\n");
     printf("------------------------this data is copy successful----------------------\n");
     printf("**************************************************************************\n");
    }
    fclose(fp);
}
int prdata(){
    int i,m=0;
    char data[1024],cmp[50];
    FILE *fp=fopen("2project.csv","r");
    fgets(data,1024,fp);
    for(i=0;i<50;i++){
       m++;
       if(i==0){
         strcpy(cmp,data);
         printf("%s",data);
       }
       else{
        fgets(data,1024,fp);
        if(strcmp(cmp,data)==0){
          no=m-2;
          return 0;
        }
        printf("%s\n",data);
        strcpy(cmp,data);
       }
    }
    fclose(fp);
}
int n(){
    int i,m=0;
    char data[1024],cmp[50];
    FILE *fp=fopen("2project.csv","r");
    fgets(data,1024,fp);
    for(i=0;i<50;i++){
       m++;
       if(i==0){
         strcpy(cmp,data);
       }
       else{
        fgets(data,1024,fp);
        if(strcmp(cmp,data)==0){
          no=m-2;
          return 0;
        }
        strcpy(cmp,data);
       }
    }
    fclose(fp);
}
int price(){
    n();
    char *value,data[1024];
    int j,a,k,row=1,temp;
    FILE *fp=fopen("2project.csv","r");
    printf("Enter the serial no. of item:");
    scanf("%d",&a);
    printf("==========================================================================\n");
    for(j=0;j<=no;j++){
        fgets(data,1024,fp);
        value=strtok(data,",");
        if(row==1){
             row++;
             continue;
        }
        temp=atoi(value);
        if(a==temp){
           value=strtok(NULL,",");
           printf("Name of item:\t");
           printf("%s\t\t",value);
           value=strtok(NULL,",");
           printf("Price:\t");
           printf("%s",value);
        }
        row++;
    }
    fclose(fp);
    printf("\n==========================================================================\n\n");
    return 0;
}
void pr(int n){
    int k,temp,len;
    printf("\n\n  --------------------------------------------------------------------------------------------------------------\n");
    printf("  |  Serial no.\t\t\t\t| Item name       \t\t\t\t    \t\tPrice  |\n");
    printf("  --------------------------------------------------------------------------------------------------------------\n");
    for(k=1;k<=n;k++){
      for(int i=1;i<=500;i++){
          len++;
          if(d[k].name[i]=='\0'){
                break;
          }
      }
      temp=atoi(d[k].price_str);
      printf("  |  %d",k);
      printf("\t\t\t\t\t|%s\t",d[k].name);
      if(len<7){
         printf("\t\t\t\t\t\t\t");
         cout<<setw(5)<<temp;
         cout<<"  |\n";
         printf("  --------------------------------------------------------------------------------------------------------------\n");
         len=0;
         total_price=total_price+temp;
         continue;
       }
       if(len>=7 && len<15){
         printf("\t\t\t\t\t\t");
         cout<<setw(5)<<temp;
         cout<<"  |\n";
         printf("  --------------------------------------------------------------------------------------------------------------\n");
         len=0;
         total_price=total_price+temp;
         continue;
       }
       if(len>=15 && len<23){
         printf("\t\t\t\t\t");
         cout<<setw(5)<<temp;
         cout<<"  |\n";
         printf("  --------------------------------------------------------------------------------------------------------------\n");
         len=0;
         total_price=total_price+temp;
         continue;
       }
       if(len>=23){
         printf("\t\t\t\t");
         cout<<setw(5)<<temp;
         cout<<"  |\n";
         printf("  --------------------------------------------------------------------------------------------------------------\n");
         total_price=total_price+temp;
         len=0;
         continue;
       }
    }
    printf("  --------------------------------------------------------------------------------------------------------------\n");
    printf("  ---------------\t\t\t| Total\t\t\t\t\t\t \t\t");
    cout<<setw(5)<<total_price<<"  |\n";
    printf("  --------------------------------------------------------------------------------------------------------------\n\n");
    printf("\n*************************************************Thanks for visiting********************************************\n\n\n\n\n\n\n\n\n");
}
int bill(){
    char *value,data[1024],name[20],price[10];

    int i,j,a,k,noo=0,row=1,temp,temp_price,total=0;

    n();
    printf("\n**************************************************Press 0 for exit******************************************************\n\n");
    for(i=1;i<100;i++){
        noo++;
        FILE *fp=fopen("2project.csv","r");
        printf("Enter the serial no. of item:");
        scanf("%d",&a);
        if(a==0){
            pr(noo-1);
            system("pause");
            sql_work();
            break;
        }
        for(j=0;j<=no;j++){
           fgets(data,1024,fp);
           value=strtok(data,",");
           if(row==1){
                row++;
                continue;
           }
           temp=atoi(value);
           if(a==temp){
              total_product++;
              d[i].srno=temp;
              value=strtok(NULL,",");
              strcpy(d[i].name,value);
              value=strtok(NULL,",");
              strcpy(d[i].price_str,value);
              temp_price=atoi(value);
              d[i].price=temp_price;
           }
           row++;
        }
        row=1;
        fclose(fp);
    }
    return 0;
}
void print(){
    int k,total=0,temp,len=0;
    printf("\n\n  --------------------------------------------------------------------------------------------------------------\n");
    printf("  |  Serial no.\t\t\t\t| Item name       \t\t\t\t    \t\tPrice  |\n");
    printf("  --------------------------------------------------------------------------------------------------------------\n");

    for(k=1;k<=no;k++){
      for(int i=1;i<=500;i++){
          len++;
          if(p[k].name[i]=='\0'){
                break;
          }
      }


      temp=atoi(p[k].price);
      printf("  |  %d",k);
      printf("\t\t\t\t\t|%s\t",p[k].name);
      if(len<7){
         printf("\t\t\t\t\t\t\t");
         cout<<setw(5)<<temp;
         cout<<"  |\n";
         printf("  --------------------------------------------------------------------------------------------------------------\n");

         len=0;
         continue;
      }
      if(len>=7 && len<15){
         printf("\t\t\t\t\t\t");
         cout<<setw(5)<<temp;
         cout<<"  |\n";
         printf("  --------------------------------------------------------------------------------------------------------------\n");
         len=0;
         continue;
      }
      if(len>=15 && len<23){
         printf("\t\t\t\t\t");
         cout<<setw(5)<<temp;
         cout<<"  |\n";
         printf("  --------------------------------------------------------------------------------------------------------------\n");
         len=0;
         continue;
      }
      if(len>=23){
         printf("\t\t\t\t");
         cout<<setw(5)<<temp;
         cout<<"  |\n";
         printf("  --------------------------------------------------------------------------------------------------------------\n");
         len=0;
         continue;
      }
    }
}
int allprint(){
    int i,j,row=0,srno;
    char *value,data[1024];
    FILE *fp=fopen("2project.csv","r");
    n();
    for(i=0;i<=no+1;i++){
        fgets(data,1024,fp);
        if(row==0){
            row++;
            continue;
        }
        if(i==no+1){
            print();
            break;
        }
        value=strtok(data,",");
        srno=atoi("value");
        p[i].srno=srno;
        value=strtok(NULL,",");
        strcpy(p[i].name,value);
        value=strtok(NULL,",");
        strcpy(p[i].price,value);
    }
    return 0;
}
