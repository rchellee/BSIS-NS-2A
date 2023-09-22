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

void SetColor(int ForgC){
  WORD wColor;

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
void gotoxy(int x,int y){
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void setFontStyle(int FontSize){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = FontSize;                  // Height
    cfi.FontFamily = FF_DONTCARE;

    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); // font style
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void SetColorAndBackground(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    return;
}
void ShowConsoleCursor(int showFlag)
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
    SetColor(8);//set text color to gray
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
    gotoxy(23,3);cout<<"W  E  L  C  O  M  E              T   O             C  A  R  A  '  S    B  A  N  K";
}

typedef struct account{
    string f_name, l_name;
    string acc_num;
    string birth;
    string contact;
    int balance;
    string p_code;
}ACC;
typedef struct record{
    ACC ar[MAX];// ARRAY OF STRUCTURES
    int last;
}REC;
class Account{
private:
    REC L;
    bool isFull();
    int locate(string n);
    int locPosition(string n);
    void pincode();
    void encrypt();
    int code;
    char pin[7];
public:
    void makenull();
    void add(ACC x);
    int display(string n);
    int checking(int n);
    void save();
    void retrieve();
    int insertcard();
    void removecard();
    void balance(int p);
    void withdraw( int n, int p);
    void deposit(int n, int p);
    void fund_t(int a, int n, int p);
    void ch_pin();
    int loc(string n);
};


int Account::locPosition(string n){
int i;
for (i=0;i<=L.last;i++){
    if (L.ar[i].acc_num>n)
        return (i);
}
return (i);//L.last+1
}

void Account::makenull(){
  L.last = -1;
}

void Account::add(ACC x){
int i,p;
if (isFull()){
    SetColor(0);
    gotoxy(52,10);cout <<"ATM List is full.\n";
    gotoxy(50,28);system("pause");
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

int Account::locate(string n){
int i;
for (i=0;i<=L.last;i++)
    if (L.ar[i].p_code==n)
        return(i);
return(-1);
}

int Account::loc(string n){
int i;
for (i=0;i<=L.last;i++)
    if (L.ar[i].acc_num==n)
        return(i);
return(-1);
}

bool Account::isFull(){
   return(L.last==MAX-1);
}

void Account::pincode(){
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

void Account::encrypt(){
int i=0;
while(pin[i]!='\0'){
    pin[i]=pin[i] + code;
    i++;
}
}

int Account::display(string n){
setFontStyle(20);
int p;
char op;
p=locate(n);
head();
shape s ;
SetColor(8);
s.box(42,10,80,14,219) ;
SetColor(0);
s.box(41,9,81,15,218) ;
SetColor(0);
	gotoxy(47,11) ;cout<<"******************************";
	gotoxy(47,12); cout<<"******** DISPLAY MODE ********";
	gotoxy(47,13); cout<<"******************************";
    s.box(35,16,85,27,218) ;
	SetColorAndBackground(14,0);
    gotoxy(37,17);cout <<"Account Name          :   "<< L.ar[p].f_name<<" "<<L.ar[p].l_name;
    gotoxy(37,19);cout <<"Account Number        :   "<<L.ar[p].acc_num;
    gotoxy(37,21);cout <<"Birthday(05-22-2001)  :   "<< L.ar[p].birth;//any format e.g 05-22-2001//May 22,2001
    gotoxy(37,23);cout <<"Contact Number        :   "<<L.ar[p].contact;
    gotoxy(37,25);cout <<"Enrypted Pin Code     :   "<<L.ar[p].p_code<<endl;
    SetColor(15);
    gotoxy(0,28);system("pause");
    load();
return(p);
}

int Account::insertcard(){
setFontStyle(20);
shape s ;
int p;
code = rand() % 99;
FILE *fp;
do{
    head();
    SetColor(8);
    s.box(33,21,86,25,219) ;
    SetColor(0);
    s.box(32,20,87,26,218) ;
    SetColor(5);
    gotoxy(38,23);cout<<"PLEASE INSERT YOUR ATM CARD...";
    fp=fopen("e:ATM.txt","r");
    SetColor(0);
    load();
    } while(!fp);
    fclose(fp);
    retrieve();
    start:
        head();
        SetColor(8);
        s.box(36,11,84,13,219) ;
        SetColor(0);
        s.box(35,10,85,14,218) ;
        SetColor(5);
        gotoxy(50,12);printf("Please enter PIN : ");
        pincode();
        encrypt();
        p=locate(pin);
        if(p==-1){
            SetColorAndBackground(14,0);
            gotoxy(40, 18);cout << "*Please enter valid Pin or ATM card is not inserted*";
	        gotoxy(0,28);system ("pause");
		    goto start;
        }
        else{
            load();
            display(pin);
        }
return(p);
}

void Account::removecard(){
FILE *fp;
shape s;
do{ head();
    SetColor(8);
    s.box(36,11,84,13,219) ;
    SetColor(0);
    s.box(35,10,85,14,218) ;
    SetColor(5);
    gotoxy(40,12);cout<<"Please remove your ATM card...";
    fp=fopen("e:ATM.txt","r");
    load();
} while(fp!=NULL);
fclose(fp);
   intro();
    SetColor(8);
    s.box(33,21,86,25,219) ;
    SetColor(0);
    s.box(32,20,87,26,218) ;
    SetColor(5);
    gotoxy(38,23);printf("THANK YOU FOR BANKING WITH OUR CARA'S BANK...\n\n\n\n");
}

void Account::balance(int p){
shape s;
setFontStyle(20);
head();
SetColor(8);
s.box(31,15,90,19,219) ;
SetColor(0);
s.box(30,14,91,20,218) ;
SetColor(5);
gotoxy(44,17) ;cout << "Your current balance is P"<< L.ar[p].balance<<endl;
SetColorAndBackground(14,0);
gotoxy(0,28);system("pause");
load();
}

void Account::withdraw(int n, int p){
    shape s;
    head();
    SetColor(0);
    s.box(25,14,95,20,218) ;
    SetColor(5);
if (L.ar[p].balance<5000){
    gotoxy(30,16) ;cout << "You cannot withdraw because your current balance is P"<< L.ar[p].balance<<endl;
    gotoxy(30,17) ;cout<<"Balance must be minimum of 5000php ";
}
else{
    if( L.ar[p].balance < n){
	gotoxy(30,17) ;cout << " Sorry we can't process your transaction you have only " << L.ar[p].balance<<"php";
	gotoxy(30,18) ;cout << "Please try again, Thank you";
	}
	else if(n <= L.ar[p].balance){
	L.ar[p].balance = L.ar[p].balance - n;
	gotoxy(30,17) ;cout <<  "You have withdrawn P" << n;
    gotoxy(30,18) ; cout<< " Your current balance is now " << L.ar[p].balance<<endl;
    save();

	}
}
SetColorAndBackground(14,0);
gotoxy(0,28);system("pause");
load();
}

void Account::deposit(int n, int p){
    shape s;
    head();
    SetColor(0);
    s.box(25,13,95,22,218) ;
    SetColor(5);
    L.ar[p].balance = L.ar[p].balance + n;
	gotoxy(47,17);cout <<  "You have deposit "<< n ;
    gotoxy(45,19); cout << "Your current balance is now P" << L.ar[p].balance<<endl;
    save();
SetColorAndBackground(14,0);
gotoxy(0,28);system("pause");
load();
}

void Account::fund_t(int a, int n, int p){
    shape s;
    head();
if (L.ar[p].balance<5000 || p==-1){
    SetColor(0);
    s.box(30,12,100,17,218) ;
    SetColor(5);
    gotoxy(32,15);cout<<"ERROR... account number is invalid or insufficient balance"<<endl;
}
else if ( L.ar[p].balance < a){
	SetColor(0);
    s.box(30,12,100,19,218) ;
    SetColor(5);
    gotoxy(32,15);cout << "Sorry we can't process your transaction since you have only " << L.ar[p].balance<<"php";
	gotoxy(44,17);cout << "Please try again, Thank you";
    load();
	}

else{
    L.ar[p].balance = L.ar[p].balance - a;
    save();
    L.ar[n].balance = L.ar[n].balance + a;
    SetColor(0);
    s.box(30,13,95,19,218) ;
    SetColor(5);
    gotoxy(39,15);cout <<  "You have transfer P" << a <<" to "<< L.ar[n].f_name<<" "<<L.ar[n].l_name<<endl;
    gotoxy(39, 17);cout<<"Your current balance is now P" << L.ar[p].balance<<endl;
    save();
    }
SetColorAndBackground(14,0);
gotoxy(0,28);system("pause");
load();
}

void Account::ch_pin(){
int p;
int index =0;
char ch;
shape s;
PIN:
head();
    SetColor(8);
    s.box(36,11,84,17,219) ;
    SetColor(0);
    s.box(35,10,85,18,218) ;
    SetColor(5);
    gotoxy(41,12);cout << "Please enter your old PIN: ";
    pincode();
    encrypt();
    p=locate(pin);
    if(p==-1){
        gotoxy(47,25);cout << "Wrong pincode...";
        gotoxy(47, 26);cout<<"Please enter valid Pin";
        SetColorAndBackground(14,0);
    gotoxy(0,28);system("pause");
        goto PIN;
        }
    else{
	    gotoxy(41,14);cout << "Please enter your NEW pin: ";
        pincode();
        encrypt();
        gotoxy(41,15);printf("Encrypted Pin Code : %s\n",pin);
        L.ar[p].p_code=pin;
        save();
        load();
}
SetColorAndBackground(14,0);
gotoxy(0,28);system("pause");}

int main(){
    Account ac;//object
    ACC acc;
    REC rec;
    ac.makenull();
    shape s;
    int pointer = 0, amount, depo, p, f;
	intro();
	load();
    p = ac.insertcard();
    setFontStyle(20);
    char Menu[][38] =  {"  B A L A N C E   I N Q U I R Y ", "       W I T H D R A W          ", "        D E P O S I T           ", "  F U N D   T R A N S F E R     ", "  C H A N G E  P I N C O D E    ", "            E X I T             "};
    string num;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(1){
        head();
        ShowConsoleCursor(0);//SET CURSOR OFF
        gotoxy(52,10);printf( "MAIN MENU\n\n");
        gotoxy(35, 18);printf("USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU");

        for(int i=0; i<6; ++i){
            //This will highlight the choice in the menu
            if(i==pointer){
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 10);
                printf("%s\n", Menu[i]);
            }else{
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 15); // set color of the text to white
                printf("%s\n",Menu[i]);
            }
             SetConsoleTextAttribute(hConsole, 15);
        }
        //This will check the key stroke that is being pressed in keyboard
        while(1){
            if(GetAsyncKeyState(VK_UP) != 0){
                --pointer;

                if(pointer == -1){
                    pointer = 5;
                    }
                break;
            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                ++pointer;
                if(pointer == 6){
                    pointer = 0;
                }

                break;
            }else if(ch=getch() == ENTER){
                switch(pointer){
                    case 0:
                    {
                        ShowConsoleCursor(1);//SET CURSON ON
                        ac.balance(p);
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        withdraw:
                        head();
                        SetColor(0);
                        s.box(30,14,86,20,218) ;
                        SetColor(5);
                        gotoxy(35,17);cout<< "Enter the amount you'd like to withdraw? ";
	                    cin >> amount;
                        if (amount <  100){
                        SetColor(0);
                        s.box(35,22,75,26,218) ;
                        SetColor(5);
		                gotoxy(40, 24);cout << "Please enter 100php and above";
                        SetColorAndBackground(14,0);
                        gotoxy(0,28);system("pause");
		                goto withdraw;
	                        }
                        else
                            ac.withdraw(amount,p);
                        break;
                    }
                    case 2:
                    {
                        ShowConsoleCursor(1);
                        dep :
                        head();
                        SetColor(0);
                        s.box(30,14,91,20,218) ;
                        SetColor(5);
		                gotoxy(40,17);cout<< "Enter the amount you'd like to deposit:  ";
	                    cin >> depo;
                        if (depo <  100){
                        SetColor(0);
                        s.box(30,22,75,26,218) ;
                        SetColor(5);
		                gotoxy(38,24);cout << "Please enter 100php and above";
                        SetColorAndBackground(14,0);
                        gotoxy(0,28);system("pause");
		                goto dep;
	                        }
                        else
                            ac.deposit(depo,p);
                        break;
                    }
                    case 3:
                    {
                        ShowConsoleCursor(1);
                        fund:
                        head();
                        SetColor(0);
                        s.box(25,14,110,21,218) ;
                        SetColor(5);
		                gotoxy(30,17);cout<<"Enter the account number of the person you want to transfer your fund: "; cin>>num;
                        f = ac.loc(num);
                        if(f==-1){
                            SetColor(0);
                            s.box(30,23,71,26,218) ;
                            SetColor(5);
		                    gotoxy(38,24);cout<<"Account number invalid!!!";
                            SetColorAndBackground(14,0);
                            gotoxy(0,28);system("pause");
                            goto fund;
                        }
                        gotoxy(35,18);cout<< "Enter the amount you'd like to transfer:  ";cin>>amount;
                        if (amount <  100){
                            SetColor(0);
                            s.box(30,23,75,26,218) ;
                            SetColor(5);
		                    gotoxy(38,24);
		                    cout << "Please enter 100php and above";
                            SetColorAndBackground(14,0);
                            gotoxy(0,28);system("pause");
		                    goto fund;
	                        }
                        else
		                    ac.fund_t(amount, f, p);
                        break;
                    }
                    case 4:
                    {
                        ShowConsoleCursor(1);
                        ac.ch_pin();
                        break;
                    }
                    case 5:
                    {
                        ShowConsoleCursor(1);
                        ac.removecard();
                        exit(0);
                    }
                }
                break;
            }
        }

    }
}
void Account::save(){
fstream fp;
fp.open("e:ATM.txt",ios::out);
for (int i = 0;i<=L.last;i++){
   fp << L.ar[i].f_name<<" "<<L.ar[i].l_name<<endl<<L.ar[i].acc_num<<" "<<L.ar[i].birth<<" "<<L.ar[i].contact<<" "<<L.ar[i].balance<<" "<<L.ar[i].p_code<<endl;
}
fp.close();
}

void Account::retrieve(){
fstream fp;
ACC r;
fp.open("e:ATM.txt",ios::in);
while (true){
    fp >>r.f_name >>r.l_name>>r.acc_num>>r.birth>>r.contact>>r.balance>>r.p_code;
    if (!fp.eof())
       add(r);
    else
       break;
}
fp.close();
}
