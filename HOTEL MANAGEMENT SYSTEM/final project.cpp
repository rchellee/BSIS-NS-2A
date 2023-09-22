#include <windows.h>          //This is the windows header file
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<direct.h>
#include <conio.h>
#include<time.h>
#define max 200
using namespace std;
COORD coord = {0, 0};

//MARK:- Interface Functions Here =>

//**********************************************************
// THIS CLASS CONTAINS FUNCTIONS RELATED TO DRAW BOX ETC.
//**********************************************************

class shape
{
        public :
                        void line_hor(int, int, int, char) ;
                        void line_ver(int, int, int, char) ;
                        void box(int,int,int,int,char) ;
} ;

//**********************************************************
// FUNCTION TO DRAW HORIZONTAL LINE
//**********************************************************
void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}


void shape :: line_hor(int column1, int column2, int row, char c)
{
        for ( column1; column1<=column2; column1++ )
        {
                gotoxy(column1,row) ;
                cout <<c ;
        }
}

//**********************************************************
// FUNCTION TO DRAW VERTICAL LINE
//**********************************************************


void shape :: line_ver(int row1, int row2, int column, char c)
{
        for ( row1; row1<=row2; row1++ )
        {
                gotoxy(column,row1) ;
            cout <<c ;
        }
}

//**********************************************************
// FUNCTION TO DRAW BOX LINE
//**********************************************************

void shape :: box(int column1, int row1, int column2, int row2, char c)
{
        char ch=218 ;
        char c1, c2, c3, c4 ;
        char l1=196, l2=179 ;
        if (c == ch)
        {
                c1=218 ;
                c2=191 ;
                c3=192 ;
                c4=217 ;
                l1 = 196 ;
                l2 = 179 ;
        }
        else
        {
                c1=c ;
                c2=c ;
                c3=c ;
                c4=c ;
                l1 = c ;
                l2 = c ;
        }
        gotoxy(column1,row1) ;
        cout<<c1 ;
        gotoxy(column2,row1) ;
        cout <<c2 ;
        gotoxy(column1,row2) ;
        cout <<c3 ;
        gotoxy(column2,row2) ;
        cout <<c4 ;
        column1++ ;
        column2-- ;
        line_hor(column1,column2,row1,l1) ;
        line_hor(column1,column2,row2,l1) ;
        column1-- ;
        column2++ ;
        row1++ ;
        row2-- ;
        line_ver(row1,row2,column1,l2) ;
        line_ver(row1,row2,column2,l2) ;
}

void intro() {
    //system("color B5");
	cout<<"\n\t            ";
	SetColor(0);
	gotoxy(48,3);
	cout<<"C++ Project On Hotel Management System";
	gotoxy(1,6);
	cout<<"made by:";
    shape s ;
    SetColor(5);
                s.box(2,8,116,15,219) ;
                s.box(1,7,117,16,218) ;
	SetColor(0);
    gotoxy(42,10);
	cout<<"R i t c h e l l e    T .    R u e r a s ";
	gotoxy(42,11);
	cout<<"M o n i q u e    K y l e    C a b i g t i n g ";
	gotoxy(42,12);
	cout<<"A p r i l    J o y    D e a n g ";
    gotoxy(50,14);
	cout<<"B S I S - N S - 1 A B";

}

void head() {
	system ("cls");
	system("color B5");
    shape s ;

                s.box(2,1,116,7,219) ;
                s.box(1,0,117,8,218) ;
                gotoxy(52,3);
	cout<<"W E L C O M E";
    gotoxy(57,4);
	cout<<"T O";
    gotoxy(47,5);
	cout<<"D  E  L  U  X  E    H  O  T  E  L";
}

void load() {
    gotoxy(50,28);
    SetColor(0);
    cout<<"Please wait while loading";
    cout<<endl;
    system ("color B5");
    SetColor(13);
    char b=219;

    for (int i=0;i<=119;i++)
        {
            cout<<b;
    for (int j=0;j<=1e7;j++); //You can also use sleep function instead of for loop
 }
}

class hotel {
	private:
			int room_no;
			char name[30];
			char names[30];
			char wifi;
			char breakfast;
			int guest;
			char address[50];
			char phone[15];
			int days;
			float fare;

	public:
			void main_menu();		//to display the main menu
			void manageRooms();
			void viewr();          //view all rooms
			void checkIn();				//to book a room
			void display(); 		//to display the customer record
			void rooms();			//to display allotted rooms
			void edit();			//to edit the customer record
			int check(int);	     	//to check room status
			void modify();		//to modify the record
			void checkOut(int);   //to delete the record
			void guestSummaryReport();
			void searchRoom(int);
			int status;
};

void hotel::viewr()
{

shape s ;
                SetColor(5);
                s.box(2,10,40,14,219) ;
                s.box(1,9,41,15,218) ;
    cout<<endl;
		SetColor(0) ;
		gotoxy(5,11) ;
		cout<<"**********************************";
		gotoxy(5,12);
		cout<<"********  Lists Of Rooms  ********";
		gotoxy(5,13);
		cout<<"**********************************";

cout<<"\n\n\n";
ifstream fin("allrooms.dat",ios::in);
while(!fin.eof())
    {
fin.read((char*)this,sizeof(hotel));
SetColor(0);
cout<<endl;
cout<<"\n\tROOM TYPE : "<<names<<endl;
cout<<"\tROOM NO. : "<<room_no<<endl;
    }
    gotoxy(0,0);
    SetColor(8);
cout<<"Press any key to continue.....!!";
getch();

fin.close();

}

void hotel::searchRoom(int r)
{
int flag;
  system("cls");
  head();
ifstream fin("allrooms.dat",ios::in);

while(!fin.eof())
    {
        fin.read((char*)this,sizeof(hotel));
if(room_no==r)
{
 shape s ;
 SetColor(5) ;
                s.box(40,9,84,24,219) ;
                s.box(39,8,85,25,218) ;

                gotoxy(53,24);cout<<"    DELUXE HOTEL  ";
                gotoxy(45,27);cout<<"C++ Project On Hotel Management System";
		cout<<endl;
		SetColor(0) ;
		gotoxy(44,11) ;
		cout<<"************************************";
		gotoxy(44,12);
		cout<<"**********  Room Details  **********";
		gotoxy(44,13);
		cout<<"************************************";

cout<<"\n\n";

SetColor(0) ;
cout<<endl;
cout<<"\n\t\t\t\t\t\tROOM TYPE : "<<names<<endl;
cout<<"\t\t\t\t\t\tROOM NO. : "<<room_no<<endl;
cout<<"\t\t\t\t\t\tFREE WIFI : "<<wifi<<endl;
cout<<"\t\t\t\t\t\tFREE BREAKFAST : "<<breakfast<<endl;
cout<<"\t\t\t\t\t\tGUEST (s) per ROOM : "<<guest<<endl;
cout<<"\t\t\t\t\t\tROOM PRICE : "<<(max*room_no)<<endl;
flag=1;
    }


}
 gotoxy (0,0);
  SetColor(8);
cout<<"Press any key to continue...";
getch();
fin.close();
}

void hotel::modify()
{
system("cls");
head();
                shape s ;

                s.box(40,9,84,24,219) ;
                s.box(39,8,85,25,218) ;
                                SetColor(0) ;
                gotoxy(53,24);cout<<"    DELUXE HOTEL  ";
                gotoxy(45,27);cout<<"C++ Project On Hotel Management System";
		cout<<endl;
		SetColor(0) ;
		gotoxy(57,10) ;
		cout<<"*************";
		gotoxy(57,11);
		cout<<"* ADD ROOMS *";
		gotoxy(57,12);
		cout<<"*************";
int r, flag;
int i=0;
ofstream fout("allrooms.dat",ios::app);
SetColorAndBackground(14,0);
gotoxy(41,14) ;
cout<<"Enter New Rooms :"<<endl;
gotoxy(44,16) ;
cout<<"Enter Room No. : ";
cin>>r;
room_no=r;
gotoxy(44,17) ;
cout<<"Enter Room Name : ";
cin>>names;
gotoxy(44,18) ;
cout<<"Free Wifi(Y/N) : ";
cin>>wifi;
gotoxy(44,19) ;
cout<<"Free Breakfast (Y/N) : ";
cin>>breakfast;
gotoxy(44,20) ;
cout<<"Enter guest(s) per room : ";
cin>>guest;
fout.write((char*)this,sizeof(hotel));
gotoxy(51,22) ;
status=0;
cout<<"Record is modified....!!";
gotoxy(50,28);

cout<<"Press any key to continue.....!!";

	getch();
	fout.close();
load();
}

void hotel::manageRooms()
{
int opt,rno,i,flag=0,r;
char ch;
do
{
system("cls");
head();
                shape s ;

                s.box(40,9,84,24,219) ;
                s.box(39,8,85,25,218) ;
                                SetColor(0) ;
                gotoxy(53,24);cout<<"    DELUXE HOTEL  ";
                gotoxy(45,27);cout<<"C++ Project On Hotel Management System";
		cout<<endl;
		SetColor(0) ;
		gotoxy(32,9) ;
		cout<<"\n\t\t\t\t\t\t\t****************";
		cout<<"\n\t\t\t\t\t\t\t* MANAGE ROOMS *";
		cout<<"\n\t\t\t\t\t\t\t****************";
		cout<<endl;
		SetColorAndBackground(14,0);
gotoxy(44,14) ;
cout<<"1. ADD Rooms";
gotoxy(44,16) ;
cout<<"2. Search Rooms";
gotoxy(44,18) ;
cout<<"3. Back to Main Menu";
gotoxy(44,21) ;
cout<<"Enter Option: ";
cin>>opt;


//switch statement
switch(opt)
{
case 1:
modify();
break;
case 2:
     gotoxy(1,27);
  SetColorAndBackground(14,0);
    cout<<"Enter room no: " ;
cin>>r;
searchRoom(r);
break;
case 3:
//nothing to do
break;
default:
 gotoxy(1,27);
cout<<"Please enter correct option";
load();

break;
}
}while(opt!=3);
getch();
}

void hotel::checkIn() {
	system ("cls");
	head();
                shape s ;

                s.box(40,9,84,24,219) ;
                s.box(39,8,85,25,218) ;
                                SetColor(0) ;
                gotoxy(53,24);cout<<"    DELUXE HOTEL  ";
                gotoxy(45,27);cout<<"C++ Project On Hotel Management System";
		cout<<endl;
		SetColor(0) ;
		gotoxy(57,10) ;
		cout<<"************";
		gotoxy(57,11);
		cout<<"* CHECK IN *";
		gotoxy(57,12);
		cout<<"************";
	int r,flag;
	ofstream fout("Record.dat",ios::app);
SetColorAndBackground(14,0);
gotoxy(44,14) ;
	cout<<"Enter Customer Details";
gotoxy(44,15) ;
	cout<<" Room no: ";
	cin>>r;
	flag=check(r);
	if(flag)
    {
        gotoxy(45,19) ;
		cout<<"Sorry..!!!Room is already booked";
    }
	else {
		room_no=r;
		gotoxy(44,16) ;
		cout<<" Name: ";
		cin>>name;
		gotoxy(44,17) ;
		cout<<" Address: ";
		cin>>address;
		gotoxy(44,18) ;
		cout<<" Phone No: ";
		cin>>phone;
		gotoxy(44,19) ;
		cout<<" No of Days to Checkout: ";
		cin>>days;
		fare=days*(r*max);						//900 is currently set as the
											//default price per day
		fout.write((char*)this,sizeof(hotel));
		gotoxy(44,22) ;
		cout<<"Room is booked...!!!";
	}

	    gotoxy(50,28);
	cout<<"Press any key to continue.....!!";
	getch();
	fout.close();
	load();
}
int hotel::check(int r) {
	int flag=0;
	ifstream fin("Record.dat",ios::in);
	while(!fin.eof()) {
		fin.read((char*)this,sizeof(hotel));
		if(room_no==r) {
			flag=1;
			break;
		}
	}
	fin.close();
	return(flag);
}
//FUNCTION TO DISPLAY ALL ROOMS OCCUPIED


void hotel::rooms()
{

  system("cls");
  system("color B5");
  head();
  int choice;
ifstream fin("Record.dat",ios::app);
                shape s ;
                SetColor(5);
                s.box(50,10,98,14,219) ;
                s.box(49,9,99,15,218) ;
    cout<<endl;
		SetColor(0) ;
		gotoxy(55,11) ;
		cout<<"***********************************";
		gotoxy(55,12);
		cout<<"***** Lists Of Rooms Allotted *****";
		gotoxy(55,13);
		cout<<"***********************************";

cout<<"\n\n\n\n";
while(!fin.eof())
{
SetColor(0);
fin.read((char*)this,sizeof(hotel));
cout<<"\n\n\n\t\t\t\t\t\t\t\t\tROOM NO. : "<<room_no<<endl;
}
viewr();
gotoxy(0,0);
cout<<"Press any key to continue.....!! ";
getch();
fin.close();
    }

void hotel::display()
{

  system("cls");
  system("color B5");
  head();

ifstream fin("Record.dat",ios::in);
int r,flag;

shape s ;
	                SetColor(13);
                s.box(36,11,94,13,219) ;
                s.box(35,10,95,14,218) ;
                gotoxy(50,12);
                SetColor(0);
	  gotoxy(40,12); cout<<"Enter room no. for a particular customer's details: ";
	  cin>>r;

while(!fin.eof())
{

fin.read((char*)this,sizeof(hotel));
if(room_no==r)
{

system ("cls");
	head();
                shape s ;

                s.box(40,9,84,24,219) ;
                s.box(39,8,85,25,218) ;
                                SetColor(0) ;
                gotoxy(53,24);cout<<"    DELUXE HOTEL  ";
                gotoxy(45,27);cout<<"C++ Project On Hotel Management System";
		cout<<endl;
		SetColorAndBackground(14,0);
		gotoxy(48,11) ;
		cout<<"****************************";
		gotoxy(48,12);
		cout<<"**** CUSTOMER'S DETAILS ****";
		gotoxy(48,13);
		cout<<"****************************";

gotoxy(50,16) ;cout<<" Room no: "<<room_no;
gotoxy(50,17) ;cout<<" Name: "<<name;
gotoxy(50,18) ;cout<<" Address: "<<address;
gotoxy(50,19) ;cout<<" Phone no: "<<phone;
flag=1;

}
if(flag==0)
{
     system("cls");
       head();
    SetColor(13);
                s.box(36,11,94,13,219) ;
                s.box(35,10,95,14,218) ;
                gotoxy(48,12);
                SetColor(0);
  cout<<"Sorry Room no. not found or vacant....!!";

break;
}


}
gotoxy(50,28);
	     SetColor(8);
cout<<"Press any key to continue....!!";
getch();
fin.close();
load();
}

void hotel::guestSummaryReport()
{

  system("cls");
  system("color B5");
  head();
ifstream fin("Record.dat",ios::app);
                shape s ;
                SetColor(5);
                s.box(36,9,83,13,219) ;
                s.box(35,8,84,14,218) ;
                gotoxy(50,11);
                SetColor(0);
cout<<"List Of Rooms Allotted";
cout<<"\n\n\n";
while(!fin.eof())
{
SetColorAndBackground(14,0);
fin.read((char*)this,sizeof(hotel));
cout<<"\n\t\t\t\t\t\tROOM NO. : "<<room_no<<endl;
cout<<"\t\t\t\t\t\tCostumer's Name : "<<name<<endl;
cout<<"\t\t\t\t\t\tCostumer's Address : "<<address<<endl;
cout<<"\t\t\t\t\t\tPhone Number : "<<phone<<endl;
cout<<"\t\t\t\t\t\tNo. of days to checkout : "<<days<<endl;
}
gotoxy(0,0);
 SetColor(8);
cout<<"Press any key to exit...";
getch();
fin.close();
    }

void hotel::main_menu()
{
    hotel h;
int i,j,opt,rno,r;
char ch;
char pname[100];


do
{
system("cls");
head();
                shape s ;
                s.box(40,9,84,24,219) ;
                s.box(39,8,85,25,218) ;
                                SetColor(0) ;
                gotoxy(53,24);cout<<"    DELUXE HOTEL  ";
                gotoxy(45,27);cout<<"C++ Project On Hotel Management System";
		cout<<endl;
		SetColor(0) ;
		gotoxy(32,9) ;
		cout<<"\n\t\t\t\t\t\t\t*************";
		cout<<"\n\t\t\t\t\t\t\t* MAIN MENU *";
		cout<<"\n\t\t\t\t\t\t\t*************";
SetColorAndBackground(14,0);
gotoxy(44,14) ;
cout<<"1. Manage Rooms";
gotoxy(44,15) ;
cout<<"2. Check-In Room";
gotoxy(44,16) ;
cout<<"3. Check Available Rooms";
gotoxy(44,17) ;
cout<<"4. Search Customer";
gotoxy(44,18) ;
cout<<"5. Check-Out Room";
gotoxy(44,19) ;
cout<<"6. Guest Summary Report";
gotoxy(44,20) ;
cout<<"7. Exit";
gotoxy(44,22) ;
cout<<"Enter Option: ";
cin>>opt;
switch(opt)
{
case 1:
manageRooms();
break;
case 2:
checkIn();
break;
case 3:
    rooms();
    break;

case 4:
display();
break;
case 5:
  gotoxy(1,27);
  SetColorAndBackground(14,0);
    cout<<"Enter room no: " ;
cin>>r;
    checkOut(r);
break;
case 6:
guestSummaryReport();
break;
case 7:
    load();
    system("cls");
    intro();
    SetColor(13);
    gotoxy(50,19);
cout<<"T H A N K   Y O U !";
    gotoxy(39,22);
cout<<" F O R    U S I N G    O U R   S O F T W A R E ";
break;
default:
  gotoxy(1,27);
cout<<"Please Enter correct option";
load();
break;
}
}while(opt!=7);

getch();
}

void hotel::checkOut(int r)
{
 system("cls");
  system("color B5");
  head();
  shape s ;
int flag=0;
char ch;
ifstream fin("Record.dat",ios::in);
ofstream fout("temp.dat",ios::out);

s.box(40,9,84,24,219) ;
                s.box(39,8,85,25,218) ;
                                SetColor(0) ;
                gotoxy(53,24);cout<<"    DELUXE HOTEL  ";
                gotoxy(45,27);cout<<"C++ Project On Hotel Management System";
		cout<<endl;

while(!fin.eof())
{

fin.read((char*)this,sizeof(hotel));
if(room_no==r)

{
    SetColorAndBackground(14,0);
		gotoxy(50,11) ;
		cout<<"**************************";
		gotoxy(50,12) ;
		cout<<"****  Check-Out Room  ****";
		gotoxy(50,13) ;
		cout<<"**************************";

gotoxy(44,15) ;
cout<<"Name: "<<name;
gotoxy(44,16) ;
cout<<"Address: "<<address;
gotoxy(44,17) ;
cout<<"Phone No: "<<phone;
gotoxy(44,18) ;
cout<<"No of Days to Checkout: "<< days;
gotoxy(44,19) ;
cout<<"Total payment: "<< fare;
gotoxy(42,21) ;
cout<<"Do you want to checkout this room(y/n): ";
cin>>ch;

if(ch=='n')

fout.write((char*)this,sizeof(hotel));
flag=1;

}

else
fout.write((char*)this,sizeof(hotel));

}

fin.close();
fout.close();

if(flag==0)
{
        gotoxy(42,17) ;
SetColorAndBackground(14,0);
cout<<"Sorry room no. not found or vacant...!!";
load();
}

else
{

remove("Record.dat");
rename("temp.dat","Record.dat");

}

}


int main()
{
    hotel h;
    system("color B5");
	cout<<"\n\n\n";
	intro();
	load();
	SetColor(0);
	    gotoxy(50,28);
	cout<<"Press any key to continue....!!";
	getch();
	system ("cls");
	 head();
	char id[5],pass[7];
	                shape s ;
	                SetColor(13);
                s.box(36,11,84,13,219) ;
                s.box(35,10,85,14,218) ;
                gotoxy(50,12);
                SetColor(0);
	cout<<"USERNAME => ";
	cin>>id;
	SetColor(13);
	s.box(36,18,84,20,219) ;
    s.box(35,17,85,21,218) ;
	gotoxy(50,19);
	SetColor(0);
	cout<<"PASSWORD => ";
	cin>>pass;
	load();
	cout<<"\t";
	if(strcmp(id,"admin")==0&&strcmp(pass,"******")==0)
		cout<<"\n\n\t\t\t  !!!Login Successfull!!!";
	else {
		cout<<"\n\n\t\t\t!!!INVALID CREDENTIALS!!!";
		getch();
		exit(-1);
	}
	system ("cls");
	h.main_menu();
	getch();

	return 0;
}
