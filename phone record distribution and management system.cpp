

#include <iostream>
using namespace std;
#include<vector>

#include<fstream>
#include<limits>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>


class phone
{

    char ctry_code[4];
    char phno[11];
    char iso_code[4];

    public:

    void create_phrec()
    {
        cout<<"\n NEW PHONE RECORD \n";
        cout<<"\n\n Enter the phone number: ";
        cin>>phno;
        cout<<"\n\n Enter the country code: ";
        cin>>ctry_code;
        cout<<"\n\n Enter the ISO code: ";
        cin>>iso_code;
        cout<<"\n\n\n Phone record has been created. \n";

        cout << ctry_code << phno << " " << iso_code << endl;

    }

    void show_phrec()
    {
        cout<<"\nPhone number :  +";
        puts(ctry_code);
        cout<<" ";
        cout<<phno;

        cout<<"\nISO code : ";
        puts(iso_code);

    }

    void modify_phrec()
    {
        cout<<"\n Phone number : "<<phno;
        cout<<"\nModify country code : ";
        cin>>ctry_code;
        cout<<"\nModify ISO code : ";
        cin>>iso_code;

    }

    char* retphno()
    {
        return phno;
    }

    void report()
    {cout<<"+"<<ctry_code<<setw(30)<<phno<<setw(30)<<iso_code<<endl;}


};


class customer
{
    char bill_no[7];
    char name[20];
    char sex[10];
    char custphno[11];
    int token;

    public:
    void create_cust()
    {
        system("CLS");

        cout<<"\nNEW CUSTOMER ENTRY \n";
        cout<<"\nEnter the customers bill number :  ";
        cin>>bill_no;
        cout<<"\n\nEnter the name of the customer : ";
        cin>>name;
        cout<<"\n\nEnter the sex of the customer : ";
        cin>>sex;
        token=0;
        custphno[0]='\0';
        cout<<"\n\n Customer record has been created. ";

    }

    void show_cust()
    {
        cout<<"\nBill no. : "<<bill_no;
        cout<<"\nCustomer Name : ";
        puts(name);
        cout<<"\nSex : ";
        puts(sex);
        cout<<"\n Issued phone number : "<<token;
        if(token==1)
            cout<<"\nPhone No : "<<custphno;
    }

    void modify_cust()
    {
        cout<<"\nBill no. : "<<bill_no;
        cout<<"\nModify customer name : ";
        cin>>name;
        cout<<"\nModify sex : ";
        cin>>sex;

    }

    char* retbill_no()
    {
        return bill_no;
    }

    char* retcustphno()
    {
        return custphno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {token=1;}

    void resettoken()
    {token=0;}

    void getcustphno(char t[])
    {
        strcpy(custphno,t);
    }

    void report()
    {cout<<"\t"<<bill_no<<setw(20)<<name<<setw(20)<<sex<<setw(20)<<token<<endl;}

};

fstream fp,fp1;
phone ph;
customer cust;


void new_ph()
{
    char ch;
    fp.open("phone.dat",ios::out|ios::app);
    do
    {
        system("CLS");
        ph.create_phrec();
        fp.write((char*)&ph,sizeof(phone));
        cout<<"\n\n Do you want to add more phone records?(y/n) : ";
        cin>>ch;

    }while(ch=='y'||ch=='Y');
    fp.close();
}

void new_cust()
{
    char ch;
    fp.open("customer.dat",ios::out|ios::app);
    do
    {
        cust.create_cust();
        fp.write((char*)&cust,sizeof(customer));
        cout<<"\n\n Do you want to add more customer records?(y/n) : ";
        cin>>ch;

    }while(ch=='y'||ch=='Y');
    fp.close();
}


void display_spphrec(char n[])
{
    cout<<"\nPHONE RECORD DETAILS\n";
    int flag=0;
    fp.open("phone.dat",ios::in);
    while(fp.read((char*)&ph,sizeof(phone)))
    {
        if(strcmpi(ph.retphno(),n)==0)
        {
            ph.show_phrec();
             flag=1;
        }
    }

    fp.close();
    if(flag==0)
        cout<<"\n\nThe phone record doesn't exist in our directory. ";
    getch();
}

void display_spcust(char n[])
{
    cout<<"\nCUSTOMER DETAILS\n";
    int flag=0;
    fp.open("customer.dat",ios::in);
    while(fp.read((char*)&cust,sizeof(customer)))
    {
        if((strcmpi(cust.retbill_no(),n)==0))
        {
            cust.show_cust();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
            cout<<"\n\nThe customer doesn't exist in our directory. ";
     getch();
}


void modify_phonerec()
{
    char n[11];
    int found=0;
    system("CLS");
    cout<<"\n\n\tMODIFY PHONE RECORD ";
    cout<<"\n\n\tEnter the phone number : ";
    cin>>n;
    fp.open("phone.dat",ios::in|ios::out);
    while(fp.read((char*)&ph,sizeof(phone)) && found==0)
    {
        if(strcmpi(ph.retphno(),n)==0)
        {
            ph.show_phrec();
            cout<<"\nEnter the new details of the phone number record : "<<endl;
            ph.modify_phrec();
            int pos=-1*sizeof(ph);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&ph,sizeof(phone));
                cout<<"\n\n\t Phone number record updated. ";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n The phone record doesn't exist in our directory.  ";
        getch();
}


void modify_customer()
{
    char n[7];
    int found=0;
    system("CLS");
    cout<<"\n\n\tMODIFY CUSTOMER RECORD ";
    cout<<"\n\n\tEnter the bill no. of the customer : ";
    cin>>n;
    fp.open("customer.dat",ios::in|ios::out);
    while(fp.read((char*)&cust,sizeof(customer)) && found==0)
    {
        if(strcmpi(cust.retbill_no(),n)==0)
        {
            cust.show_cust();
            cout<<"\nEnter the new details of the customer : "<<endl;
            cust.modify_cust();
            int pos=-1*sizeof(cust);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&cust,sizeof(customer));
            cout<<"\n\n\t Customer record updated.";
            found=1;
        }
    }

    fp.close();
    if(found==0)
        cout<<"\n\n The customer record doesn't exist in our directory. ";
    getch();
}


void delete_cust()
{
    char n[6];
    int flag=0;
    system("CLS");
        cout<<"\n\n\n\tDELETE CUSTOMER ";
        cout<<"\n\nEnter the bill no. of the customer you want to delete : ";
        cin>>n;
        fp.open("customer.dat",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&cust,sizeof(customer)))
    {
        if(strcmpi(cust.retbill_no(),n)!=0)
                 fp2.write((char*)&cust,sizeof(customer));
        else
               flag=1;
    }

    fp2.close();
    fp.close();

        remove("customer.dat");
        rename("Temp.dat","customer.dat");
        if(flag==1)
             cout<<"\n\n\tThe customer record has been deleted successfully. ";
        else
             cout<<"\n\nThe customer record doesn't exist in our directory. ";
        getch();

}


void delete_phrec()
{
    char n[10];
    system("CLS");
    cout<<"\n\n\n\tDELETE PHONE RECORD ";
    cout<<"\n\nEnter the phone number you want to delete : ";
    cin>>n;
    fp.open("phone.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&ph,sizeof(phone)))
    {
        if(strcmpi(ph.retphno(),n)!=0)
        {
            fp2.write((char*)&ph,sizeof(phone));
        }
    }

    fp2.close();
    fp.close();

        remove("phone.dat");
        rename("Temp.dat","phone.dat");
        cout<<"\n\n\tThe phone record has been deleted successfully. ";
        getch();
}


void displayall_cust()
{
    system("CLS");
         fp.open("customer.dat",ios::in);
         if(!fp)
         {
               cout<<"\n\nError, The file cannot be opened. \n";
               getch();
               return;
         }

    cout<<"\n\n*********************************************************************************************";
    cout<<"\n\n                                         CUSTOMER LIST                                       ";
    cout<<"\n\n*********************************************************************************************";
    cout<<"\n\n";

    cout<<"=====================================================================================================================\n";
    cout<<"\tBill no."<<setw(20)<<"Name"<<setw(20)<<"Sex"<<setw(20)<<"Phone number issued\n";
    cout<<"=====================================================================================================================\n";

    while(fp.read((char*)&cust,sizeof(customer)))
    {
        cust.report();
    }

    fp.close();
    getch();

}



void displayall_phrec()
{
    system("CLS");
    fp.open("phone.dat",ios::in);

    if(!fp)
    {
        cout<<"Error, The file cannot be opened. ";
               getch();
               return;
    }

    cout<<"\n\n*********************************************************************************************";
    cout<<"\n\n                                     PHONE NUMBER LIST                                       ";
    cout<<"\n\n*********************************************************************************************";
    cout<<"\n\n";

    cout<<"=========================================================================\n";
    cout<<"Country code"<<setw(30)<<"Phone number"<<setw(30)<<"ISO code\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&ph,sizeof(phone)))
    {
        ph.report();
    }
         fp.close();
         getch();
}


void phone_issue()
{
    char billno[6],phno[10];
    int found=0,flag=0;
    system("CLS");
    cout<<"\n\n PHONE NUMBER ISSUE";
    cout<<"\n\n\tEnter the customers bill no. : ";
    cin>>billno;

    fp.open("customer.dat",ios::in|ios::out);
    fp1.open("phone.dat",ios::in|ios::out);

        while(fp.read((char*)&cust,sizeof(customer)) && found==0)
        {
        if(strcmpi(cust.retbill_no(),billno)==0)
        {
            found=1;
            if(cust.rettoken()==0)
            {
                      cout<<"\n\n\tEnter the phone no. : ";
                      cin>>phno;
                while(fp1.read((char*)&ph,sizeof(phone))&& flag==0)
                {
                       if(strcmpi(ph.retphno(),phno)==0)
                    {
                        ph.show_phrec();
                        flag=1;
                        cust.addtoken();
                        cust.getcustphno(ph.retphno());
                               int pos=-1*sizeof(cust);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&cust,sizeof(customer));
                        cout<<"\n\n\t Phone number issued successfully ";
                    }
                    }
                  if(flag==0)
                        cout<<"\n\nThe phone record doesn't exist in our directory.\n";
            }
                  else
                       cout<<"\n\nYou still own a phone number\n.";

        }
    }
          if(found==0)
        cout<<"\n\nThe customer record doesn't exist in our directory.\n";
    getch();
      fp.close();
      fp1.close();
}


void return_phone()
{
    char billno[6],phno[10];
    int found=0,flag=0;
    system("CLS");
    cout<<"\n\n RETURN OWNERSHIP OF YOUR CURRENT PHONE NUMBER ";
    cout<<"\n\n\tEnter the customers bill no. : ";
    cin>>billno;
    fp.open("customer.dat",ios::in|ios::out);
    fp1.open("phone.dat",ios::in|ios::out);
    while(fp.read((char*)&cust,sizeof(customer)) && found==0)
       {
        if(strcmpi(cust.retbill_no(),billno)==0)
        {
            found=1;
            if(cust.rettoken()==1)
            {
            while(fp1.read((char*)&ph,sizeof(phone))&& flag==0)
            {
               if(strcmpi(ph.retphno(),cust.retcustphno())==0)
            {
                ph.show_phrec();
                flag=1;

                    cust.resettoken();
                    int pos=-1*sizeof(cust);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&cust,sizeof(customer));
                    cout<<"\n\n\t Phone number ownership returned successfully.";
            }
            }
          if(flag==0)
            cout<<"\n\nThe phone record does not exist. \n";
              }
         else
            cout<<"\n\nYou do not own this number. \n";
        }
       }
      if(found==0)
    cout<<"\n\nThe customer doesn't exist in our directory. \n";
    getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//        INTRODUCTION FUNCTION
//****************************************************************

void about_us()
{
    system("CLS");

    cout<<"\n                             *************************************************************************************************************"<<endl;
    cout<<"                                                         HULL PHONE RECORDS DISTRIBUTION AND MANAGEMENT SYSTEM                              "<<endl;
    cout<<"                             *************************************************************************************************************\n"<<endl;

    cout<<"***************************************************************"<<endl;
    cout<<"                             ABOUT US                           "<<endl;
    cout<<"***************************************************************"<<endl;
    cout<<"\n\n";

    cout<<"\n\nHull Phone Records management Pvt Ltd is one of the fastest-growing documents and Record Distribution and Management Company in the world. ";
    cout<<"\nThe company was established in the year of 2005 with a clear vision of creating an efficient";
    cout<<"\nrecord management system for various classes of people.";
    cout<<"\nEver since our inception, we have played a pivotal role in promoting the importance of contact";
    cout<<"\nand data management globally, thereby ushering in a new era in the field of contact storage-management.";
    cout<<"\n\n\nFOUNDERS :  SAHITYA.C\n";
    cout<<"            TEJAL.OM.A";
    cout<<"\n\n";

    cout<<"\n***************************************************************";
    cout<<"\n                       MISSION AND VISION                      ";
    cout<<"\n***************************************************************"<<endl;
    cout<<"\n1.To spread the importance and need of record management.";
    cout<<"\n2.To provide an excellent document management services.";
    cout<<"\n3.To safely manage the growing volumes of records & documents.";
    cout<<"\n4.To make record management affordable for a layman.";
    cout<<"\n5.Valuing and offering the best services for our clientele.\n";
    cout<<"\n\n\nThank you for availing HULL PHONE RECORDS DISTRIBUTION AND MANAGEMENT SYSTEM 's services!\n";
    cout<<"\n\n\nHave a great day ahead.\n";

    getch();
}



//***************************************************************
//        ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
    system("CLS");
    int ch2;
    cout<<"\n\n\n\tADMINISTRATOR MENU";
    cout<<"\n\n\t1.CREATE CUSTOMER RECORD";
    cout<<"\n\n\t2.DISPLAY ALL CUSTOMERS RECORD";
    cout<<"\n\n\t3.DISPLAY SPECIFIC CUSTOMER RECORD ";
    cout<<"\n\n\t4.MODIFY CUSTOMER RECORD";
    cout<<"\n\n\t5.DELETE CUSTOMER RECORD";
    cout<<"\n\n\t6.CREATE PHONE RECORD ";
    cout<<"\n\n\t7.DISPLAY ALL PHONE RECORDS";
    cout<<"\n\n\t8.DISPLAY SPECIFIC PHONE RECORD ";
    cout<<"\n\n\t9.MODIFY PHONE RECORD ";
    cout<<"\n\n\t10.DELETE PHONE RECORD ";
    cout<<"\n\n\t11.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease enter your choice (1-11) ";
    cin>>ch2;

    switch(ch2)
    {
            case 1:
                system("CLS");
                new_cust();
                break;

            case 2:
                displayall_cust();
                break;

            case 3:
                char num[6];
                system("CLS");
                cout<<"\n\n\tPlease enter the bill no. : ";
                cin>>num;
                display_spcust(num);
                break;

            case 4:
                modify_customer();
                break;

            case 5:
                delete_cust();
                break;

            case 6:
                system("CLS");
                new_ph();
                break;

            case 7:
                displayall_phrec();
                break;

            case 8: {
                char num[10];
                system("CLS");
                cout<<"\n\n\tPlease enter the phone number : ";
                cin>>num;
                display_spphrec(num);
                break;
                }

            case 9:
                modify_phonerec();
                break;

            case 10:
                delete_phrec();
                break;

            case 11:
                return;

            default:cout<<"\a";
       }
       admin_menu();
}


//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
    char ch;
    do
    {
        system("CLS");
        cout<<"\n\n\n                MAIN MENU";
        cout<<"\n\n              1. PHONE NUMBER ISSUE";
        cout<<"\n\n              2. RETURN OWNERSHIP OF PHONE NUMBER";
        cout<<"\n\n              3. ADMINISTRATOR MENU";
        cout<<"\n\n              4. ABOUT US";
        cout<<"\n\n              5. EXIT";
          cout<<"\n\n\tPlease Select Your Option (1-5) ";
          ch=getche();
          switch(ch)
          {
            case '1':
                system("CLS");
                phone_issue();
                break;

            case '2':
                return_phone();
                break;

            case '3':
                admin_menu();
                break;

            case '4':
                about_us();
                break;

            case '5':
                exit(0);

            default :
                cout<<"\a";

        }
        }while(ch!='5');
}

