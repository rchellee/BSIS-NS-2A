/***************************************/
/*     HUFFMAN ENCODING PROGRAM        */
/* CREATED BYRITCHELLE T. RUERAS       */
/*              &&                     */
/*       MONIQUE KYLE CABIGTING        */
/*          26 JANUARY 2023            */
/***************************************/
#include <iostream>
#include <string>
#include <limits>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <windows.h>
#include <cstdio>
using namespace std;
#define EMPTY_STRING ""

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
    gotoxy(0,27);cout<<"Please wait while loading"<<endl;
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
	gotoxy(28,1);cout<<"F I L E  C O M P R E S S   U S I N G   H U F F M A N    A L G O R I T H M";
	gotoxy(1,4);cout<<"made by:";
    shape s ;
    SetColor(8);//set text color
        s.box(2,6,116,13,219) ;//box shape
        SetColor(0);
        s.box(1,5,117,14,218) ;
	SetColor(5);//set text color to black
    gotoxy(45,8);cout<<"R i t c h e l l e    T .    R u e r a s ";
	gotoxy(42,10);cout<<"M o n i q u e    K y l e    C a b i g t i n g ";
	gotoxy(50,12);cout<<"B S I S - N S - 2 A B";
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
    gotoxy(18,3);cout<<"C O M P R E S S   &  D E C O M P R E S S   F I L E   U S I N G   H U F F M A N   C O D I N G";
}

//structure used to define a node
struct Huffman_Node
{
    char ch;
    int freq;
    Huffman_Node *left, *right;
};

//function used to create a new node
Huffman_Node* new_node(char ch, int freq, Huffman_Node* left, Huffman_Node* right)
{
    Huffman_Node* node = new Huffman_Node();
    node->ch = ch;//assign the character 'c' to the character of the node (eventually a leaf)
    node->freq = freq;//assign frequency
    node->left = left;
    node->right = right;

    return node;
}

struct compress
{
    bool operator()(const Huffman_Node* lt, const Huffman_Node* rt) const
    {
        return lt->freq > rt->freq;
    }
};

bool isLeaf(Huffman_Node* root) {
    return root->left == nullptr && root->right == nullptr;
}

int chars [256];
void init (){
int i;
for (i=0;i<256;i++)
    chars [i]=0;
}

void encode(Huffman_Node* root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) {
        return;
    }
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}
void decode(Huffman_Node* root, int &index, string str, string &decodedString)
{
    if (root == nullptr) {
        return;
    }
    if (isLeaf(root))
    {
        decodedString += root->ch;
        return;
    }

    index++;

    if (str[index] == '0') {
        decode(root->left, index, str, decodedString);
    }
    else {
        decode(root->right, index, str, decodedString);
    }
}

void compressFile(string fileName)
{
fstream my_file, my_file2;
string text, textInput, str, newName;
my_file.open(fileName, ios::in);//open the file stream
SetColor(5);
cout << "\n\tWhat would you like to be the name of the compressed file? ";cin >> newName;
my_file2.open(newName, ios::out);//to save the encoded text
my_file2 << fileName + "\n";
while(!my_file.eof()){
    getline(my_file, textInput);
    text += textInput + "\n";
    }
if (text == EMPTY_STRING) {
    return;
    }
unordered_map<char, int> freq;
for (char ch: text) {
    freq[ch]++;
    }
//used to insert a node into the priority que
priority_queue<Huffman_Node*, vector<Huffman_Node*>, compress> pq;
for (auto pair: freq) {
    pq.push(new_node(pair.first, pair.second, nullptr, nullptr));
    }
while (pq.size() != 1){
    Huffman_Node* left = pq.top(); pq.pop();
    Huffman_Node* right = pq.top();    pq.pop();
    int sum = left->freq + right->freq;
    pq.push(new_node('\0', sum, left, right));
    }
Huffman_Node* root = pq.top();
unordered_map<char, string> huffmanCode;
encode(root, EMPTY_STRING, huffmanCode);
for (char ch: text) {
    str += huffmanCode[ch];
    }
my_file2 << str;
printf("\nEncoded:\n");
SetColor(0);cout<<str<<endl;
cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void decompressFile(string fileName){
shape s;
fstream my_file, my_file2, my_file3;
string fileName2, decFilename, encodedString, text, textInput, decodedString;
my_file.open(fileName, ios::in);
getline(my_file, fileName2);
my_file2.open(fileName2, ios::in);
while(!my_file2.eof()){
    getline(my_file2, textInput);
    text += textInput + "\n";
    }
if (text == EMPTY_STRING) {
    return;
    }
unordered_map<char, int> freq;
for (char ch: text) {
        freq[ch]++;
    }
priority_queue<Huffman_Node*, vector<Huffman_Node*>, compress> pq;
for (auto pair: freq) {
    pq.push(new_node(pair.first, pair.second, nullptr, nullptr));
    }
while (pq.size() != 1){
    Huffman_Node* left = pq.top(); pq.pop();
    Huffman_Node* right = pq.top();    pq.pop();
    int sum = left->freq + right->freq;
    pq.push(new_node('\0', sum, left, right));
    }
Huffman_Node* root = pq.top();
unordered_map<char, string> huffmanCode;
getline(my_file, encodedString);
if (isLeaf(root)){
    while (root->freq--) {
        decodedString += root->ch;
        }
    }
else {
    int index = -1;
    while (index < (int)encodedString.size() - 1) {
            decode(root, index, encodedString, decodedString);
        }
    }
load();
head();
SetColor(0);s.box(28,8,100,12,218) ;
SetColor(5);
gotoxy(30,10);cout << "What do you want to be the name of the new file? ";
cin >>decFilename;
my_file3.open(decFilename, ios::out);
my_file3 << decodedString;
SetColor(8);s.box(0,14,118,20,219) ;
SetColor(5);
gotoxy(2,15);printf("Decoded : ");
SetColorAndBackground(14,0);
gotoxy(2,16);cout<< decodedString;
my_file3.close();
cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

int main(){
shape s;
int compress;
char filename[20];//file name
FILE *input;//file name
int i, size = 0;
char *fn, ch;
intro();
load();
menu:
head();
/*get input details from user*/
gotoxy(48,12);cout << "Press[1] to Compress" << endl;
gotoxy(48,13);cout << "Press[2] to Decompress" << endl;
gotoxy(48,14);cout << "Press[3] to Exit" << endl;
gotoxy(52,10);printf( "MAIN MENU\n\n");
gotoxy(45,17);cout << "Select an option: ";scanf("%d", &compress);
while(1){
    switch(compress){
        case 1:{
            re:
            head();
            init();
            SetColor(0);
            s.box(30,14,86,20,218) ;
            SetColor(5);
            gotoxy(35,17);printf("Type the name of the file: ");
            SetColorAndBackground(14,0);
            scanf("\t%s", filename);
            input = fopen(filename, "r");
            if (input==NULL){
                gotoxy(35,18);printf ("File error.");
                SetColorAndBackground(14,0);
                gotoxy(0,28);system("pause");
                goto re;}
            else{
                load();
                head();
                SetColor(5);
		        gotoxy(2,7);printf("File Read:");
            while (!feof (input)){
                ch = fgetc (input);
                chars [ch]++;
                putchar (ch);
                size++;}
            SetColor(5);
            printf("\n----------------- C O D E  T A B L E ----------------");
            cout<<"\n-----------------------------------------------------";
            cout<<"\n\tCODE   \t\tCHAR \t\tFREQ";
            cout<<"\n-----------------------------------------------------";
            SetColor(5);
            for (i=0;i<256;i++)
                if (chars [i]>0)
                printf ("\n\t%d\t:\t%c\t:\t%d", i,i, chars [i]);
		    printf ("\n\n\t\t\tFile size: %d bits.\n", size-1);
                }
            compressFile(filename);//import the file into the program and update the huffman tree
            system("pause");
            goto menu;
        break;}
        case 2:{
            head();
            init();
            SetColor(0);
            s.box(30,14,86,20,218) ;
            SetColor(5);
            gotoxy(35,17);printf("Type the name of the file: ");
            SetColorAndBackground(14,0);
            scanf("\t%s", filename);
            input = fopen(filename, "r");
            decompressFile(filename);
            cout<<endl;
            SetColor(8);
            gotoxy(0,28);system("pause");
            goto menu;
        break;}
        case 3:{
            intro();
            load();
            SetColorAndBackground(14,0);
            gotoxy(41,19);printf("H  A  P  P  Y    C  O  D  I  N  G.....\n\n\n\n\n\n\n\n\n\n");
            exit(0);
        }
        }
    }
    return 0;
}

