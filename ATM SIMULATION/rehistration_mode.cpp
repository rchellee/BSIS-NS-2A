#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define MAX 50
using namespace std;

void gotoxy(int x,int y){
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void SetColor(int ForgC){
  WORD wColor;
  //This handle is needed to get the current background attribute
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
 //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
    //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void setFontStyle(int FontSize){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = FontSize;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // font style
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void SetColorAndBackground(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    return;
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

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

void load() {
    setFontStyle(20);
    gotoxy(0,28);cout<<"Please wait while loading"<<endl;
    SetColor(8);//set text color to Light Magenta
    char b=219;
    for (int i=0;i<=119;i++){
        cout<<b;
        for (int j=0;j<=1e7;j++); //You can also use sleep function instead of for loop
    }
}

void intro()
{
    system("cls");
    setFontStyle(20);
    system("color B8");//set background color
    SetColor(5);//set text color to black
	cout<<"\n\t            ";
	gotoxy(48,3);
	cout<<"C++ Project On ATM SIMULATION";
	gotoxy(1,6);
	cout<<"made by:";
    shape s ;
    SetColor(8);//set text color
        s.box(2,8,116,15,219) ;//box shape
        SetColor(0);
        s.box(1,7,117,16,218) ;
	SetColor(5);//set text color to black
    gotoxy(45,10);
	cout<<"R i t c h e l l e    T .    R u e r a s ";
	gotoxy(42,12);
	cout<<"M o n i q u e    K y l e    C a b i g t i n g ";
	gotoxy(50,14);
	cout<<"B S I S - N S - 2 A B";
}

void head()
{
	system ("cls");
    setFontStyle(20);//set font and screen size
    system("color B8");//set background color
    shape s ;//box shape
    SetColor(8);
    s.box(2,1,116,5,219) ;
    SetColor(0);
    s.box(1,0,117,6,218) ;
    SetColor(5);
    gotoxy(23,3);cout<<"W  E  L  C  O  M  E              T   O             C A R A ' s    B  A  N  K";
}

typedef struct account{
    string f_name, l_name, m_name;
    string acc_num;
    string birth;
    string contact;
    int deposit;
    string p_code;
}ACC;


typedef struct record{
    ACC ar[MAX];// ARRAY OF STRUCTURES
    int last;
}REC;

class BANK{
private:
    REC L;
    bool isEmpty();
    bool isFull();
    int locate(string n);
    int locPosition(string n);
public:
    void makenull();
    void add(ACC x);
    void display(string n);
    int check(string n);
    void account();
    void pincode();
    void save();
    void retrieve();
};

//Global Variable
char pin[7], num[6];
int code;

void encrypt(){
int i=0;
while(pin[i]!='\0'){
    pin[i]=pin[i] + code;
    i++;
    }
}

int menu();

int main(){
BANK user;//object user
ACC acc;
REC rec;
shape s;
user.makenull();
user.retrieve();
int p, i=0;
code = rand() % 99;
head();
SetColor(8);
s.box(36,11,84,13,219) ;
SetColor(0);
s.box(35,10,85,14,218) ;
SetColor(5);
gotoxy(40,12);cout<<"C R E A T I N G   B A N K   A C C O U N T";
load();

while(true){
    start:
    head();
    SetColor(8);//color of box
    s.box(40,7,84,11,219) ;
    SetColor(0);
	gotoxy(46,8) ;cout<<"***********************************";
	gotoxy(46,9); cout<<"******** REGISTRATION MODE ********";
	gotoxy(46,10); cout<<"***********************************";
	SetColor(0);
    s.box(27,12,95,27,218) ;
	SetColorAndBackground(14,0);
    gotoxy (29,13); cout<<"Enter First Name                      : ";cin>>acc.f_name;//to use space in string
    gotoxy (29,14); cout<<"Enter Last Name                       : ";cin>>acc.l_name;

    first:
    gotoxy (29,15);cout<<"Enter account number (5 digits)       : ";
    user.account();
    acc.acc_num=num;
    p=user.check(acc.acc_num);
    if(p>-1){
            SetColor(15);
        gotoxy (0, 28);cout<<"Sorry. Account number is unavailable"<<endl;
        getch();goto start;
    }
    gotoxy (29,16);cout<<"Enter the birth date(dd-mm-yyyy)      : ";cin>>acc.birth;
    gotoxy (29,17);cout<<"Enter contact number                  : ";cin>> acc.contact;

    second:
    gotoxy (29,18);cout<<"Enter initial deposit (min. of 5000)  : ";
    cin>> acc.deposit;
    if (acc.deposit<5000){
            SetColor(15);
    gotoxy (0,28);cout<< "INVALID INPUT, INITIAL DEPOSIT MUST BE MINIMUM OF 5000";
    getch();goto start;
    }
    gotoxy (29,19);cout<<"Enter 4-6 digits Pin Code             : ";
    user.pincode();
    encrypt();
    gotoxy (29,20);printf("Encrypted Pin Code                   :  %s\n",pin);
    SetColor(15);
    gotoxy(0,28);system("pause");
    acc.p_code=pin;
    load();
    user.add(acc);
    user.display(acc.acc_num);
    intro();
    SetColor(8);
    s.box(33,21,86,25,219) ;
    SetColor(0);
    s.box(32,20,87,26,218) ;
    SetColor(5);
    gotoxy(38,23);printf("THANK YOU FOR BANKING WITH OUR CARA'S BANK...\n\n\n\n");
    break;
    }

return (0);
}

int BANK::locPosition(string n){
int i;
for (i=0;i<=L.last;i++){
    if (L.ar[i].acc_num>n)
        return (i);
}
return (i);
}

void BANK::makenull(){
  L.last = -1;
}

int BANK::check(string n){
        int i;
    for(i=0;i<=L.last;i++)
        if (L.ar[i].acc_num == n)
            return (i);
    return(-1);
}


void BANK::pincode(){
int index =0;
char ch;
while((ch=getch())!=13 && index<5){
    if (index<0)
        index=0;
    if(ch==8){//backspace ascii is 8
        putch('\b');
        putch(' ');
        putch('\b');
        index--;
     continue;
    }
    if(isdigit(ch)){
     pin[index++]=ch;
     putch('*');
    }
}
if (index==5)
    pin[index++]=ch;
pin[index]='\0';
}

void BANK::account(){
int index =0;
char ch;
while((ch=getch())!=13 && index<5){
    if (index<0)
        index=0;
    if(ch==8){//backspace ascii is 8
        putch('\b');
        putch(' ');
        putch('\b');
        index--;
     continue;
    }
    if(isdigit(ch)){
     num[index++]=ch;
     putch(ch);
    }
}
if (index==4)
    num[index++]=ch;
num[index]='\0';
}

void BANK::add(ACC x){
int i,p;
if (isFull()){
    cout <<"ATM list is full.\n";
    system("pause");
}
else {
    p=locPosition(x.acc_num);
    for (i=L.last;i>=p;i--){
        L.ar[i+1]=L.ar[i];
    }
        L.ar[p] = x;

        L.last++;
 }
}

void BANK::display(string n){
int p;
char op;
shape s;
p=locate(n);
head();
SetColor(8);
s.box(42,10,80,14,219) ;
SetColor(0);
s.box(41,9,81,15,218) ;
SetColor(0);
gotoxy(47,11) ;cout<<"******************************";
gotoxy(47,12); cout<<"******** DISPLAY MODE ********";
gotoxy(47,13); cout<<"******************************";
SetColor(0);
s.box(35,16,85,25,218) ;
SetColorAndBackground(14,0);
gotoxy (37,17);cout<<"Account Name          : "<< L.ar[p].f_name<<" "<<L.ar[p].l_name;
gotoxy (37,18);cout<<"Account Number        : "<<L.ar[p].acc_num;
gotoxy (37,19);cout<<"Birthday(05-22-2001)  : "<< L.ar[p].birth;//any format e.g 05-22-2001//May 22,2001
gotoxy (37,20);cout<<"Contact Number        : "<<L.ar[p].contact;
gotoxy (37,21);cout<<"Initial Deposit       : "<<L.ar[p].deposit;
gotoxy (37,22);cout<<"Enrypted Pin Code     : "<<L.ar[p].p_code<<endl;
gotoxy (37,24);cout<<"Create ATM Bank account? (y/n): "; cin>>op;
if (op=='y'){
    save();
    load();
}
else{
    load();
    intro();
    exit (0);
}

}

int BANK::locate(string n){
int i;
for (i=0;i<=L.last;i++)
    if (L.ar[i].acc_num==n)
        return(i);
return(-1);
}

bool BANK::isEmpty(){
    return(L.last==-1);
}

bool BANK::isFull(){
   return(L.last==MAX-1);
}

void BANK::save(){
ACC acc;
fstream fp;
fp.open("e:ATM.txt",ios::out);
for (int i = 0;i<=L.last;i++){
   fp << L.ar[i].f_name<<" "<<L.ar[i].l_name<<endl<<L.ar[i].acc_num<<" "<<L.ar[i].birth<<" "<<L.ar[i].contact<<" "<<L.ar[i].deposit<<" "<<L.ar[i].p_code<<endl;
}
fp.close();
}

void BANK::retrieve(){
fstream fp;
ACC r;
fp.open("e:ATM.txt",ios::in);
while (true){
    fp >>r.f_name >>r.l_name>>r.acc_num>>r.birth>>r.contact>>r.deposit>>r.p_code;
    if (!fp.eof())
       add(r);
    else
       break;
}
fp.close();
}
