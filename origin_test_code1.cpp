
// Autor : Nemonet TYP
// Title: Supermarket Billing System project in C++
// PROJECT FOR C/C++ PROGRAMMING TUTORIAL
// source: https://github.com/The-Young-Programmer/C-CPP-Programming/blob/main/Projects/C%2B%2B%20Projects/Basic/Supermarket%20Billing%20System/main.cpp


#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
using namespace std;
//global variable declaration
int k=7,r=0,flag=0;
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
struct date
{
    int mm,dd,yy;
};

ofstream fout;
ifstream fin;

class item
{
    int itemno;
    char name[25];
    date d;
public:
    void add()
    {
        cout<<"

	Item No: ";
        cin>>itemno;
        cout<<"

	Name of the item: ";
        cin>>name;
//gets(name);
        cout<<"

	Manufacturing Date(dd-mm-yy): ";
        cin>>d.mm>>d.dd>>d.yy;
    }
    void show()
    {
        cout<<"
	Item No: ";
        cout<<itemno;
        cout<<"

	Name of the item: ";
        cout<<name;
        cout<<"

	Date : ";
        cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
    }
    void report()
    {
        gotoxy(3,k);
        cout<<itemno;
        gotoxy(13,k);
        puts(name);
    }
    int retno()
    {
        return(itemno);

    }

};

class amount: public item
{
    float price,qty,tax,gross,dis,netamt;
public:
    void add();
    void show();
    void report();
    void calculate();
    void pay();
    float retnetamt()
    {
        return(netamt);
    }
} amt;

void amount::add()
{
    item::add();
    cout<<"

	Price: ";
    cin>>price;
    cout<<"

	Quantity: ";
    cin>>qty;
    cout<<"

	Tax percent: ";
    cin>>tax;
    cout<<"

	Discount percent: ";
    cin>>dis;
    calculate();
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::calculate()
{
    gross=price+(price*(tax/100));
    netamt=qty*(gross-(gross*(dis/100)));
}
void amount::show()
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    item::show();
    cout<<"

	Net amount: ";
    cout<<netamt;
    fin.close();
}

void amount::report()
{
    item::report();
    gotoxy(23,k);
    cout<<price;
    gotoxy(33,k);
    cout<<qty;
    gotoxy(44,k);
    cout<<tax;
    gotoxy(52,k);
    cout<<dis;
    gotoxy(64,k);
    cout<<netamt;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        getch();
        k=7;
        system("cls");
        gotoxy(30,3);
        cout<<" ITEM DETAILS ";
        gotoxy(3,5);
        cout<<"NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";
        gotoxy(44,5);
        cout<<"TAX";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(64,5);
        cout<<"NET AMOUNT";
    }
}

void amount::pay()
{
    show();
    cout<<"


		*********************************************";
    cout<<"
		                 DETAILS                  ";
    cout<<"
		*********************************************";
    cout<<"

		PRICE                     :"<<price;
    cout<<"

		QUANTITY                  :"<<qty;
    cout<<"
		TAX PERCENTAGE              :"<<tax;
    cout<<"
		DISCOUNT PERCENTAGE         :"<<dis;
    cout<<"


		NET AMOUNT              :Rs."<<netamt;
    cout<<"
		*********************************************";
}

int main()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout<<setprecision(2);
    fstream tmp("temp.dat",ios::binary|ios::out);
menu:
    system("cls");
    gotoxy(25,2);
    cout<<"Super Market Billing ";
    gotoxy(25,3);
    cout<<"===========================

";
    cout<<"
		1.Bill Report

";
    cout<<"		2.Add/Remove/Edit Item

";
    cout<<"		3.Show Item Details

";
    cout<<"		4.Exit

";
    cout<<"		Please Enter Required Option: ";
    int ch,ff;
    float gtotal;
    cin>>ch;
    switch(ch)
    {
    case 1:
ss:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Details";
        gotoxy(25,3);
        cout<<"================

";
        cout<<"
		1.All Items

";
        cout<<"		2.Back to Main menu

";
        cout<<"		Please Enter Required Option: ";
        int cho;
        cin>>cho;
        if(cho==1)
        {
            system("cls");
            gotoxy(30,3);
            cout<<" BILL DETAILS ";
            gotoxy(3,5);
            cout<<"ITEM NO";
            gotoxy(13,5);
            cout<<"NAME";
            gotoxy(23,5);
            cout<<"PRICE";
            gotoxy(33,5);
            cout<<"QUANTITY";
            gotoxy(44,5);
            cout<<"TAX %";
            gotoxy(52,5);
            cout<<"DISCOUNT %";
            gotoxy(64,5);
            cout<<"NET AMOUNT";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"

File Not Found...";
                goto menu;
            }
            fin.seekg(0);
            gtotal=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report();
                    gtotal+=amt.retnetamt();
                    ff=0;
                }
                if(ff!=0) gtotal=0;
            }
            gotoxy(17,k);
            cout<<"


			Grand Total="<<gtotal;
            getch();
            fin.close();
        }
        if(cho==2)
        {
            goto menu;
        }
        goto ss;
    case 2:
db:
        system("cls");
        gotoxy(25,2);
        cout<<"Bill Editor";
        gotoxy(25,3);
        cout<<"=================

";
        cout<<"
		1.Add Item Details

";
        cout<<"		2.Edit Item Details

";
        cout<<"		3.Delete Item Details

";
        cout<<"		4.Back to Main Menu ";
        int apc;
        cin>>apc;
        switch(apc)
        {
        case 1:
            fout.open("itemstore.dat",ios::binary|ios::app);
            amt.add();
            cout<<"
		Item Added Successfully!";
            getch();
            goto db;

        case 2:
            int ino;
            flag=0;
            cout<<"

	Enter Item Number to be Edited :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            fout.open("itemstore.dat",ios::binary|ios::app);
            if(!fin)
            {
                cout<<"

File Not Found...";
                goto menu;
            }
            fin.seekg(0);
            r=0;
            while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    int x=amt.item::retno();
                    if(x==ino)
                    {
                        flag=1;
                        fout.seekp(r*sizeof(amt));
                        system("cls");
                        cout<<"
		Current Details are
";
                        amt.show();
                        cout<<"

		Enter New Details
";
                        amt.add();
                        cout<<"
		Item Details editted";
                    }
                }
                r++;
            }
            if(flag==0)
            {
                cout<<"
		Item No does not exist...Please Retry!";
                getch();
                goto db;
            }
            fin.close();
            getch();
            goto db;

        case 3:
            flag=0;
            cout<<"

	Enter Item Number to be deleted :";
            cin>>ino;
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"

File Not Found...";
                goto menu;
            }
//fstream tmp("temp.dat",ios::binary|ios::out);
            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.item::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
                goto db;
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
                cout<<"
		Item Succesfully Deleted";
            else if (flag==0)
                cout<<"
		Item does not Exist! Please Retry";
            getch();
            goto db;
        case 4:
            goto menu;
        default:
            cout<<"

		Wrong Choice!!! Retry";
            getch();
            goto db;
        }
    case 3:
        system("cls");
        flag=0;
        int ino;
        cout<<"

		Enter Item Number :";
        cin>>ino;
        fin.open("itemstore.dat",ios::binary);
        if(!fin)
        {
            cout<<"

File Not Found...
Program Terminated!";
            goto menu;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.item::retno();
            if(x==ino)
            {
                amt.pay();
                flag=1;
                break;
            }
        }
        if(flag==0)
            cout<<"
		Item does not exist....Please Retry!";
        getch();
        fin.close();
        goto menu;
    case 4:
        system("cls");
        gotoxy(20,20);
        cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        if((yn=='Y')||(yn=='y'))
        {
            gotoxy(12,20);
            system("cls");
            cout<<"************************** THANKS **************************************";
            getch();
            exit(0);
        }
        else if((yn=='N')||(yn=='n'))
            goto menu;
        else
        {
            goto menu;
        }
    default:
        cout<<"

		Wrong Choice....Please Retry!";
        getch();
        goto menu;
    }
    return 0;
}
