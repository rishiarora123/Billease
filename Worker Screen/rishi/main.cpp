#include <iostream>   // c++ library
#include <mysql.h>   // for my sql
#include <sstream>   // for stringstream
#include <unistd.h>  // for sleep
#include <string.h>   // for string
#include <iomanip>    // for setw()


using namespace std;
struct billdata{
    int bsrno,srno,price;
    string pname,name,time;
}b[1000][100];
void print(int i,int brow);
int main()
{
    MYSQL* conn;
    int qstate = 0,j=0,roww=0;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn= mysql_real_connect(conn,"192.168.137.160","","","ddd",3306,NULL ,0);
    if(conn){
      for(int i=0;i<=100000;i++){
        stringstream ss;
        ss<<"SELECT `Serial no`, `pname` , `srno`, `name`, `price` , `Time` FROM `bill"<<i<<"`  WHERE 1";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(!qstate){
            j++;
            res = mysql_store_result(conn);
            while(row=mysql_fetch_row(res)){
                int bsrno=atoi(row[0]);
                b[i][roww].bsrno=bsrno;
                b[i][roww].pname=row[1];
                int srno=atoi(row[2]);
                b[i][roww].srno=srno;
                b[i][roww].name=row[3];
                int price=atoi(row[4]);
                b[i][roww].price=price;
                b[i][roww].time=row[5];
                roww++;
            }
            print(i,roww);
            roww=0;
        }
        if(i!=j){
            i--;
        }
        sleep(5);
      }
    }
    return 0;
}
void print(int i,int brow){
     for(int j=0;j<=brow-1;j++){
            if(j==0){
                    cout<<"---------------------------------------------------------------------------------------------------------\n";
                    cout<<"\tName of customer:"<<b[i][j].pname<<"\t\t\t\tTime and Date : "<<b[i][j].time;
                    cout<<"---------------------------------------------------------------------------------------------------------\n";
                    cout<<"|   Serial no.\t|\tProduct serial no.\t|\t\tName of product\t\t|\tPrice\t|\n";
                    cout<<"---------------------------------------------------------------------------------------------------------\n";
                    cout<<"|\t"<<b[i][j].bsrno<<"\t|\t\t"<<b[i][j].srno<<"\t\t|\t"<<setw(20)<<b[i][j].name<<"\t\t|\t"<<b[i][j].price<<"\t|\n";
            }
            if(j==brow-1){
                    cout<<"---------------------------------------------------------------------------------------------------------\n";
                    cout<<"|\t\t\t\t\t\t\t"<<setw(20)<<b[i][j].name<<"\t\t|\t"<<b[i][j].price<<"\t|\n";
                    cout<<"---------------------------------------------------------------------------------------------------------\n";

            }
            if(j!=0 && j!=brow-1){
                cout<<"|\t"<<b[i][j].bsrno<<"\t|\t\t"<<b[i][j].srno<<"\t\t|\t"<<setw(20)<<b[i][j].name<<"\t\t|\t"<<b[i][j].price<<"\t|\n";
            }
     }
     cout<<"\n\n\n";
}
