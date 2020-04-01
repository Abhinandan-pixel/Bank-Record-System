#include <iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
class acc
{
private:
    char acc_no[20];
    char fname[10];
    char lname[10];
    float total_bal;
public:
    void read_data();
    void show_data();
    void write_rec();
    void read_rec();
    void sear_rec();
    void edit_rec();
    void del_rec();
};
void acc::read_data()
{
    cout<<"Enter Account number:";
    cin>>acc_no;
    cout<<"Enter First name:";
    cin>>fname;
    cout<<"Enter last name:";
    cin>>lname;
    cout<<"Enter Balance:";
    cin>>total_bal;
    cout<<endl;
}
void acc::show_data()
{
    cout<<"Account number: "<<acc_no<<endl;
    cout<<"First name: "<<fname<<endl;
    cout<<"last name: "<<lname<<endl;
    cout<<"Current balance: "<<total_bal<<endl;
    cout<<"-----------------------------------"<<endl;
}
void acc::write_rec()
{
    ofstream outfile("record.bank",ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char*>(this),sizeof(*this));
    outfile.close();

}
void acc::read_rec()
{ifstream infile("record.bank",ios::binary);
if(infile.is_open())
{

  cout<<"\n****Data from file****"<<endl;
  while(!infile.eof())
  {

        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
      {
          show_data();
      }
  }
  infile.close();
}
else
{
    cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
}
}
 void acc::sear_rec()
 {  ifstream infile("record.bank",ios::binary);
     if(infile.is_open())
     {  infile.seekg(0,ios::end);
         int n;
         int coun=infile.tellg()/sizeof(*this);
         cout<<"There are "<<coun<<" records"<<endl;
         cout<<"Enter the record number to search : ";
         cin>>n;
         infile.seekg((n-1)*sizeof(*this));
         infile.read(reinterpret_cast<char *>(this),sizeof(*this));
         show_data();

     }
     else
     {
         cout<<"Error in opening in file ";
         return;
     }
 }
 void acc::edit_rec()
 {
     fstream iofile;
     iofile.open("record.bank",ios::in|ios::binary);
     if(!iofile)
     {
         cout<<"Error in opening the file";
         return;
     }
         int coun;
         int n;
         iofile.seekg(0,ios::end);
         coun=iofile.tellg()/sizeof(*this);
         cout<<"There are "<<coun<<" records "<<endl;
         cout<<"Enter record to be edited ";
         cin>>n;
         iofile.seekg((n-1)*sizeof(*this));
         iofile.read(reinterpret_cast<char *>(this),sizeof(*this));
         cout<<"Record "<<n<<" has following data "<<endl;
         show_data();
         iofile.close();
         iofile.open("record.bank",ios::out|ios::in|ios::binary);
         iofile.seekp((n-1)*sizeof(*this));
         cout<<"Enter data to modify "<<endl;
         read_data();
         iofile.write(reinterpret_cast<char *>(this),sizeof(*this));

}
void acc::del_rec()
{
    ifstream infile;
    infile.open("record.bank",ios::binary);
    if(!infile)
    {
        cout<<"Error in opening the file";
        return;
    }
    int coun;
    int n;
    infile.seekg(0,ios::end);
    coun=infile.tellg()/sizeof(*this);
    cout<<"There are "<<coun<<" records "<<endl;
    cout<<"Enter the record number to delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank",ios::out|ios::binary);
    infile.seekg(0);
    for(int i=0;i<coun;i++)
    {
        infile.read(reinterpret_cast<char *>(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char *>(this),sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
   rename("tmpfile.bank", "record.bank");
}

int main()
{
    acc A;
    int choice;
    cout<<"***Account Information System***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add record to file";
        cout<<"\n\t2-->Show record from file";
        cout<<"\n\t3-->Search Record from file";
        cout<<"\n\t4-->Update Record";
        cout<<"\n\t5-->Delete Record";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            A.write_rec();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.sear_rec();
            break;
        case 4:
            A.edit_rec();
            break;
        case 5:
            A.del_rec();
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"\nEnter correct choice";
            exit(0);
        }
    }
    system("pause");
    return 0;


}
