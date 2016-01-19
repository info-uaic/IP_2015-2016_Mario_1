#include <iostream>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <cstring>
#include <cstdlib>
#include <windows.h>
using namespace std;


char board[400][400];
int jump=0;
int x=0,y=58,xm=8,ym=80,dir=1,jump2=0,scor=0,km=0,v[4],bul=0;


//////////////////---OBJECTS-->//////////////////
void marioR(int y, int x)
{
	for (int i = x; i <= x + 7; i++)
		board[y][i] = (char)177;
	board[y + 1][x + 1]= (char)176;
	board[y + 1][x + 2]= (char)176;
	board[y + 1][x + 6]= (char)176;
	board[y + 1][x + 3]= (char)178;
	board[y + 1][x + 4]= (char)178;
	board[y + 1][x + 5]= (char)178;
	board[y + 2][x]= (char)176;
	board[y + 2][x+1]= (char)176;
	board[y + 2][x+2]= (char)176;
	board[y + 2][x+4]= (char)176;
	board[y + 2][x+3]= (char)178;
	board[y + 2][x+5]= (char)178;
	board[y + 2][x+6]= (char)178;
	board[y + 2][x+7]= (char)178;
	board[y + 3][x+2]= (char)178;
	board[y + 3][x+3]= (char)178;
	board[y + 3][x]= (char)176;
	board[y + 3][x+1]= (char)176;
	board[y + 3][x+4]= (char)176;
	board[y + 3][x+5]= (char)176;
	board[y + 3][x+6]= (char)176;
}

void marioL(int y, int x)
{
	for (int i = x; i <= x + 7; i++)
		board[y][i] = (char)177;
    board[y+1][x+1]=(char)176;
    board[y+1][x+5]=(char)176;
    board[y+1][x+6]=(char)176;
    board[y+1][x+2]=(char)178;
    board[y+1][x+3]=(char)178;
    board[y+1][x+4]=(char)178;
    board[y+2][x]=(char)178;
    board[y+2][x+1]=(char)178;
    board[y+2][x+2]=(char)178;
    board[y+2][x+4]=(char)178;
    board[y+2][x+3]=(char)176;
    board[y+2][x+5]=(char)176;
    board[y+2][x+6]=(char)176;
    board[y+2][x+7]=(char)176;
    board[y+3][x+1]=(char)176;
    board[y+3][x+2]=(char)176;
    board[y+3][x+3]=(char)176;
    board[y+3][x+6]=(char)176;
    board[y+3][x+7]=(char)176;
    board[y+3][x+4]=(char)178;
    board[y+3][x+5]=(char)178;
}

void block(int y, int x)
{
    int ok=0;
    for(int i=0;i<4;i++)
        for(int j=0;j<8;j+=2)
            if(ok==0){
                board[y+i][x+j]=(char)176;
                board[y+i][x+j+1]=(char)176;
                if(j<6)
                ok=1;}
            else{
                board[y+i][x+j]=(char)177;
                board[y+i][x+j+1]=(char)177;
                if(j<6)
                ok=0;}
}

void blockk(int y, int x)
{
    int ok=0;
    for(int i=0;i<4;i++)
        for(int j=0;j<8;j+=2)
            if(ok==0){
                board[y+i][x+j]=(char)177;
                board[y+i][x+j+1]=(char)177;
                if(j<6)
                ok=1;}
            else{
                board[y+i][x+j]=(char)177;
                board[y+i][x+j+1]=(char)177;
                if(j<6)
                ok=0;}
    for(int i=1;i<=2;i++)
        for(int j=2;j<6;j++)
            board[y+i][x+j]='?';
}

void coin(int y, int x)
{
    for(int i=2;i<=5;i++)
    {
        board[y][x+i]=(char)178;
        board[y+3][x+i]=(char)178;
    }
    for(int i=1;i<=2;i++)
        for(int j=0;j<=1;j++)
        {
            board[y+i][x+j]=(char)178;
            board[y+i][x+j+6]=(char)178;
            board[y+i][x+j+3]='!';
        }
}

void bullet(int y, int x)
{
    for(int i=0;i<4;i++)
    {
        board[y+1][x+2+i]=(char)176;
        board[y+2][x+2+i]=(char)176;
    }
}

void turtle(int y,int x)
{
    for(int i=y;i<y+4;i++)
        for(int j=x;j<x+8;j++)
            board[i][j]=(char)177;
    board[y][x]=NULL;
    board[y][x+1]=NULL;
    board[y][x+6]=NULL;
    board[y][x+7]=NULL;
    board[y+1][x]=NULL;
    board[y+1][x+7]=NULL;
    board[y+2][x+2]=(char)178;
    board[y+2][x+5]=(char)178;
}

void tube(int y, int x)
{
    for(int i=x;i<x+8;i++)
        board[y][i]=(char)178;
    for(int i=y+1;i<y+4;i++)
        for(int j=x+1;j<x+7;j++)
            board[i][j]=(char)177;
}

void castle(int y,int x)
{
    block(y,x);
    block(y,x+12);
    block(y,x+24);
    block(y+4,x+4);
    block(y+4,x+12);
    block(y+4,x+20);
    block(y+8,x+4);
    block(y+8,x+12);
    block(y+8,x+20);
}

struct turt{
    int yt,xt,d,f;
}t[5];

void create_board()
{
    for(int i=0;i<400;i++)
        for(int j=0;j<400;j++)
            board[i][j]=0;



    ///turtle///
    turtle(14*4,9*8);t[0].yt=14*4;t[0].xt=9*8;
    turtle(20*4,18*8);t[1].yt=20*4;t[1].xt=18*8;
    turtle(37*4,16*8);t[2].yt=37*4;t[2].xt=16*8;
    turtle(37*4,21*8);t[3].yt=37*4;t[3].xt=21*8;
    turtle(37*4,19*8);t[4].yt=37*4;t[4].xt=19*8;
    turtle(80,0);turtle(80,40);
    ///block///
    for(int i=0;i<50;i++)
    {
        block(21*4,i*8);
        block(38*4,i*8);
    }
    block(18*4,3*8);
    block(18*4,5*8);
    block(18*4,10*8);
    block(20*4,17*8);
    block(20*4,21*8);
    for(int i=10;i<15;i++)
        block((i+6)*4,26*8);
    block(18*4,24*8);
    block(18*4,25*8);
    for(int i=0;i<=9;i++)
        block(15*4,(7+i)*8);
    block(14*4,8*8);
    block(15*4,26*8);
    block(14*4,12*8);
    block(35*4,9*8);
    block(35*4,10*8);
    block(32*4,12*8);
    block(32*4,13*8);
    block(37*4,15*8);
    block(37*4,22*8);
    for(int i=0;i<=7;i++)
        block(29*4,(15+i)*8);
    //////////
    ///blockk///
    blockk(18*4,4*8);
    blockk(18*4,9*8);
    blockk(18*4,11*8);
    blockk(18*4,29*8);
    blockk(18*4,30*8);
    blockk(18*4,31*8);
    blockk(12*4,14*8);
    blockk(12*4,15*8);
    blockk(12*4,16*8);
    ////////////
    ///coin///
    for(int i=0;i<=1;i++)
        for(int j=0;j<=3;j++)
        {
            coin((26+i)*4,(17+j)*8);
            coin((35+i)*4,(5+j)*8);
        }
    //////////
    ///tube///
    tube(20*4,34*8);
    tube(37*4,1*8);
    //////////
    ///castle///
    castle(35*4,26*8);
    ////////////
}

void delet(int y,int x)
{
    for(int i=y;i<y+4;i++)
        for(int j=x;j<x+8;j++)
            board[i][j]=NULL;
}
//////////////////<--OBJECTS---//////////////////
//////////////////---PAGES--->//////////////////
void meniu();
void joc();


void next_level()
{
    km=1;
    system("cls");
        cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<49;i++)
        cout<<' ';
    cout<<"NEXT CHAPTER";
    for(int i=0;i<49;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"                ";
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"          ";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"           ";
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"          ";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    Sleep(2000);
    return;
}

void scorr()
{
    system("cls");
    cout<<"merge help";
    system("cls");
        cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<48;i++)
        cout<<' ';
    cout<<"TOP 3: ";
    for(int i=0;i<55;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    ////////////
    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    if(v[0]/100!=0){
        cout<<' '<<"#1:   "<<v[0];
        for(int i=0;i<100-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
    }
    else
    {
        if(v[0]/10!=0){
        cout<<' '<<"#1:   "<<v[0];
        for(int i=0;i<101-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
        }

    else
    {
        if(v[0]/10==0){
        cout<<' '<<"#1:   "<<v[0];
        for(int i=0;i<102-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
        }
    }
    }
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    //////////
    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    if(v[1]/100!=0){
        cout<<' '<<"#2:   "<<v[1];
        for(int i=0;i<100-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
    }
    else
    {
        if(v[1]/10!=0){
        cout<<' '<<"#2:   "<<v[1];
        for(int i=0;i<101-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
        }

    else
    {
        if(v[1]/10==0){
        cout<<' '<<"#2:   "<<v[1];
        for(int i=0;i<102-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
        }
    }
    }
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
 /////////////
    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    if(v[2]/100!=0){
        cout<<' '<<"#3:   "<<v[2];
        for(int i=0;i<100-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
    }
    else
    {
        if(v[2]/10!=0){
        cout<<' '<<"#3:   "<<v[2];
        for(int i=0;i<101-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
        }

    else
    {
        if(v[2]/10==0){
        cout<<' '<<"#3:   "<<v[2];
        for(int i=0;i<102-47;i++)
            cout<<' ';
        cout<<(char)186<<endl;
        }
    }
    }
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
//////////////
    cout<<(char)186;
    for(int i=0;i<48;i++)
        cout<<' ';
    cout<<"APASA ORICE";
    for(int i=0;i<51;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    int c=getch();
    joc();
    return;
}
void winner()
{
    system("cls");
        cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<49;i++)
        cout<<' ';
    cout<<"AI CASTIGAT!";
    for(int i=0;i<49;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"                ";
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"          ";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"           ";
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"          ";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    Sleep(2000);
    for(int i=0;i<3;i++)
        if(scor>v[i])
        {
            if(i==0)
            {
                v[2]=v[1];
                v[1]=v[0];
            }
            if(i==1)
            {
                v[2]=v[1];
            }
            v[i]=scor;
            break;
        }
    x=0,y=58,xm=8,ym=80,dir=1,jump2=0,scor=0,km=0,jump=0;
    ofstream fout("scor.in");
    fout<<v[0]<<endl<<v[1]<<endl<<v[2]<<endl;
    create_board();
    meniu();
    return;
}
void game_over()
{
    system("cls");
        cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<50;i++)
        cout<<' ';
    cout<<"GAME OVER!";
    for(int i=0;i<50;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"                ";
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"          ";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"           ";
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"          ";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    Sleep(2000);
    meniu();
    return;
}
bool valid(int a,int b,int d)
{
    if(board[a+1][b+3]=='!')
    {
        scor+=5;
        return true;
    }
    if(board[a][b]==NULL&&board[a+2][b+2]!=(char)178)
        return true;

    if(board[a+1][b+2]=='?'&&d==1)
    {
        delet(a,b);
        coin(a,b);
        return false;
    }
    if(board[a+2][b+2]==(char)178)
    {
        if(d==3){
        delet(a,b);
        scor+=20;

        for(int i=0;i<=4;i++)
            if(t[i].yt==a&&t[i].xt==b)
                t[i].f=0;
        return false;
        }
        else
            game_over();
    }
    if(board[a][b]==(char)178&&d==3)
    {
        if(km==0){
        next_level();}
        ym=144;
        xm=8;
        y=126;
        x=0;
    }
    return false;
}

bool validt(int a,int b, int d)
{
    if(a==ym+jump&&b==xm+jump)
        game_over();
    if(board[a+3][b]==NULL)
        return true;
    return false;
}

void turtles()
{
    for(int i=0;i<5;i++)
        if(t[i].f==1)
        delet(t[i].yt,t[i].xt);
    for(int i=0;i<5;i++)
    {
        if(t[i].f==1){
        if(t[i].d==1)
        {
            if(validt(t[i].yt,t[i].xt+8,2))
                t[i].xt+=8;
            else
                t[i].d=2;
        }
        else
        {
            if(validt(t[i].yt,t[i].xt-8,2))
                t[i].xt-=8;
            else
                t[i].d=1;
        }
        }
    }
    for(int i=0;i<5;i++)
        if(t[i].f==1)
        turtle(t[i].yt,t[i].xt);
    return;
}

struct bull{
    int yb,xb,d,f=0;
}b[10];

bool validb(int a,int c)
{
    if(c<x)
        return false;
        if(c>x+110)
            return false;
    if(board[a+1][c+2]==(char)176&&board[a+1][c]==NULL){
        delet(a,c);
        bul--;
        return true;}

    if(board[a+1][c+2]==NULL)
        return true;
    if(board[a+2][c+2]==(char)178)
    {
        delet(a,c);
        scor+=20;

        for(int i=0;i<5;i++)
            if(t[i].yt==a&&t[i].xt==c)
                t[i].f=0;

        return false;
    }
    return false;
}

void bullets(int a)
{
    if(a==1)
    {
        for(int i=0;i<3;i++)
            if(b[i].f==1)
                delet(b[i].yb,b[i].xb);
        for(int i=0;i<3;i++)
    {
        if(b[i].f==1){
        if(b[i].d==1)
        {
            if(validb(b[i].yb,b[i].xb+8))
                b[i].xb+=8;
            else{
                    delet(b[i].yb,b[i].xb);
                b[i].f=0;
                bul--;}
        }
        else
        {
            if(validb(b[i].yb,b[i].xb-8))
                b[i].xb-=8;
            else{
                    delet(b[i].yb,b[i].xb);
                b[i].f=0;bul--;}
        }
        }
    }
    for(int i=0;i<3;i++)
        if(b[i].f==1)
        bullet(b[i].yb,b[i].xb);
    return;
    }
    if(a==2)
    {
        if(bul<3){
        if(dir==1)
        {
            if(validb(ym,xm+8)){
                b[bul].yb=ym-jump;
                b[bul].xb=xm+8;
                b[bul].d=dir;
                b[bul++].f=1;
                bullet(ym-jump,xm+8);
            }
        }
        if(dir==2)
        {
            if(validb(ym,xm-8)){
                b[bul].yb=ym-jump;
                b[bul].xb=xm-8;
                b[bul].d=dir;
                b[bul++].f=1;
                bullet(ym-jump,xm-8);
                }
        }
        }
    }
    return;
}

void joc()
{
    int c,ok=1,nl=0;
    char n[5000];
    if(dir==1)
            marioR(ym,xm);
        else
            marioL(ym,xm);
    ///
    system("cls");
        n[nl++]=(char)201;
    for(int i=1;i<111;i++)
        n[nl++]=(char)205;
    n[nl++]=(char)187;
    n[nl++]='\n';

    for(int w=0;w<30;w++){
        for(int i=0;i<=111;i++)
            if(i==0||i==111)
                n[nl++]=(char)186;
            else
            {
                if(board[y+w][x+i-1]==NULL)
                n[nl++]=' ';
                else
                    n[nl++]=board[y+w][x+i-1];
            }
        n[nl++]='\n';
    }

    n[nl++]=(char)204;
    for(int j=0;j<110;j++)
            n[nl++]=(char)205;
    n[nl++]=(char)185;
    n[nl++]='\n';

    n[nl++]=(char)186;
    if(scor/100!=0){
        n[nl++]=' ';
        n[nl++]='S';
        n[nl++]='C';
        n[nl++]='O';
        n[nl++]='R';
        n[nl++]=':';
        n[nl++]=' ';
        n[nl++]=(char)(scor/100+'0');
        n[nl++]=(char)(scor/10%10+'0');
        n[nl++]=(char)(scor%10+'0');
        for(int i=0;i<100;i++)
            n[nl++]=' ';
        n[nl++]=(char)186;n[nl++]='\n';
    }
    else
    {
        if(scor/10!=0){
        n[nl++]=' ';
        n[nl++]='S';
        n[nl++]='C';
        n[nl++]='O';
        n[nl++]='R';
        n[nl++]=':';
        n[nl++]=' ';
        n[nl++]=(char)(scor/10%10+'0');
        n[nl++]=(char)(scor%10+'0');
        for(int i=0;i<101;i++)
            n[nl++]=' ';
        n[nl++]=(char)186;n[nl++]='\n';
        }

    else
    {
        if(scor/10==0){
        n[nl++]=' ';
        n[nl++]='S';
        n[nl++]='C';
        n[nl++]='O';
        n[nl++]='R';
        n[nl++]=':';
        n[nl++]=' ';
        n[nl++]=(char)(scor%10+'0');
        for(int i=0;i<102;i++)
            n[nl++]=' ';
        n[nl++]=(char)186;n[nl++]='\n';
        }
    }
    }

    n[nl++]=(char)200;
    for(int i=1;i<111;i++)
        n[nl++]=(char)205;
    n[nl++]=(char)188;
    printf("%s", n);
    ///
    while(ok)
    {
        Sleep(30);
        nl=0;
        if(ym==148&&xm==200)
            winner();
        turtles();
        bullets(1);
        ////////////////////////////////////////
        if(jump==-1)
            delet(ym,xm);
        else
            delet(ym-jump,xm);

        if(_kbhit()){
        c=getch();
        if(c==27)
        {
            ok=0;
            meniu();
        }
        else
        {
            switch(c) {
        case 32:
            if(jump==0)
            {
                jump=-1;
                jump2=0;
            }
            break;
        case 72:
            bullets(2);
            break;
        case 75:
            if(valid(ym-jump,xm-8,2)&&xm-8>=x)
            {
                xm-=8;
            }
            dir=2;
            break;
        case 77:
            if(valid(ym-jump,xm+8,2))
            {
                if(xm+8<=280&&y<=58||xm+8<=200&&y>58)
                xm+=8;
                if(xm-x>72&&x+8<184&&y<=58||xm-x>72&&xm+8<=200&&y>58)
                    x+=8;
            }
            dir=1;
            break;

        }
        }
        }
        if(jump==0&&ym-y<14&&y-12>=-6)
                y-=12;
        if(jump==0&&ym-y>=26)
                    y+=12;
        if(jump!=0)
        {
            if(jump2==1)
            {
                if(valid(ym-jump+4,xm,3))
                    jump-=4;
                else
                {
                    ym=ym-jump;
                    jump=0;
                    jump2=0;
                }
            }
            else
            {
                if(jump<16)
                {
                    if(jump==-1)
                        jump=4;
                    else
                    {
                        if(valid(ym-jump-4,xm,1))
                            jump+=4;
                        else
                            if(jump!=0)
                                jump2=1;
                    }
                }
                else
                    jump2=1;
            }
        }
        if(valid(ym-jump+4,xm,3)&&jump==0)
                    ym+=4;
        if(dir==1){
            marioR(ym-jump,xm);
        }
        else
            marioL(ym-jump,xm);
        ////////////////////////////////////////
           system("cls");
        n[nl++]=(char)201;
    for(int i=1;i<111;i++)
        n[nl++]=(char)205;
    n[nl++]=(char)187;
    n[nl++]='\n';

    for(int w=0;w<30;w++){
        for(int i=0;i<=111;i++)
            if(i==0||i==111)
                n[nl++]=(char)186;
            else
            {
                if(board[y+w][x+i-1]==NULL)
                n[nl++]=' ';
                else
                    n[nl++]=board[y+w][x+i-1];
            }
        n[nl++]='\n';
    }

    n[nl++]=(char)204;
    for(int j=0;j<110;j++)
            n[nl++]=(char)205;
    n[nl++]=(char)185;
    n[nl++]='\n';

    n[nl++]=(char)186;
    if(scor/100!=0){
        n[nl++]=' ';
        n[nl++]='S';
        n[nl++]='C';
        n[nl++]='O';
        n[nl++]='R';
        n[nl++]=':';
        n[nl++]=' ';
        n[nl++]=(char)(scor/100+'0');
        n[nl++]=(char)(scor/10%10+'0');
        n[nl++]=(char)(scor%10+'0');
        for(int i=0;i<100;i++)
            n[nl++]=' ';
        n[nl++]=(char)186;n[nl++]='\n';
    }
    else
    {
        if(scor/10!=0){
        n[nl++]=' ';
        n[nl++]='S';
        n[nl++]='C';
        n[nl++]='O';
        n[nl++]='R';
        n[nl++]=':';
        n[nl++]=' ';
        n[nl++]=(char)(scor/10%10+'0');
        n[nl++]=(char)(scor%10+'0');
        for(int i=0;i<101;i++)
            n[nl++]=' ';
        n[nl++]=(char)186;n[nl++]='\n';
        }

    else
    {
        if(scor/10==0){
        n[nl++]=' ';
        n[nl++]='S';
        n[nl++]='C';
        n[nl++]='O';
        n[nl++]='R';
        n[nl++]=':';
        n[nl++]=' ';
        n[nl++]=(char)(scor%10+'0');
        for(int i=0;i<102;i++)
            n[nl++]=' ';
        n[nl++]=(char)186;n[nl++]='\n';
        }
    }
    }

    n[nl++]=(char)200;
    for(int i=1;i<111;i++)
        n[nl++]=(char)205;
    n[nl++]=(char)188;
    printf("%s", n);
    ///////////////////
    }
    return;
}

void help()
{
    system("cls");
    cout<<"merge help";
    system("cls");
        cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"TASTE:";
    for(int i=0;i<57;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"SPACE = saritura";
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"< = stanga";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"> = dreapta";
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"^ = impusca";
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<1;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    cout<<(char)186;
    for(int i=0;i<47;i++)
        cout<<' ';
    cout<<"ESC = back";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    int c=getch();
    meniu();
    return;
}

void b_men(int m)
{
    if(m==1)
    {
        system("cls");
        cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)204;
    for(int j=0;j<110;j++)
            cout<<(char)205;
    cout<<(char)185<<endl;
    cout<<(char)186;
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<"START";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    cout<<(char)204;
    for(int j=0;j<110;j++)
            cout<<(char)205;
    cout<<(char)185<<endl;
    cout<<(char)186;
    for(int i=0;i<50;i++)
        cout<<' ';
    cout<<"AJUTOR,MAI";
    for(int i=0;i<50;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    cout<<(char)186;
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<"IESIRE";
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    }
    else
    if(m==2)
    {
        system("cls");
        cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<"START";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    cout<<(char)204;
    for(int j=0;j<110;j++)
            cout<<(char)205;
    cout<<(char)185<<endl;
    cout<<(char)186;
    for(int i=0;i<50;i++)
        cout<<' ';
    cout<<"AJUTOR,MAI";
    for(int i=0;i<50;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    cout<<(char)204;
    for(int j=0;j<110;j++)
            cout<<(char)205;
    cout<<(char)185<<endl;
    cout<<(char)186;
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<"IESIRE";
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    }
    else
    if(m==3)
    {
        system("cls");
        cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<"START";
    for(int i=0;i<53;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    cout<<(char)186;
    for(int j=0;j<110;j++)
            cout<<' ';
    cout<<(char)186<<endl;
    cout<<(char)186;
    for(int i=0;i<50;i++)
        cout<<' ';
    cout<<"AJUTOR,MAI";
    for(int i=0;i<50;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    cout<<(char)204;
    for(int j=0;j<110;j++)
            cout<<(char)205;
    cout<<(char)185<<endl;
    cout<<(char)186;
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<"IESIRE";
    for(int i=0;i<52;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    cout<<(char)204;
    for(int j=0;j<110;j++)
            cout<<(char)205;
    cout<<(char)185<<endl;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }

    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    }
    return;
}

void meniu()
{
    x=0,y=58,xm=8,ym=80,dir=1,jump2=0,scor=0,km=0;
    int c,m=1,ok=1;
    b_men(m);
    while(ok)
    {
        c=getch();
        switch(c)
        {
        case 72:
            if(m==1)
                m=3;
            else
                m--;
            b_men(m);
            break;
        case 80:
            if(m==3)
                m=1;
            else
                m++;
            b_men(m);
            break;
        case 13:
            ok=0;
            break;

        default:
            break;
        }
    }
    create_board();
    for(int i=0;i<5;i++)
    {
        t[i].d=1;
        t[i].f=1;
    }
    x=0,y=58,ok=1,xm=8,ym=80,dir=1,jump2=0,scor=0,km=0,jump=0;
    if(m==1)
        scorr();
    if(m==2)
        help();
    if(m==3)
        exit(0);
}

void entry()
{
    cout<<(char)201;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)187<<endl;
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<42;i++)
        cout<<' ';
    cout<<"DIMENSIONEAZA-TI FEREASTRA";
    for(int i=0;i<42;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
        cout<<(char)186;
    for(int i=0;i<42+3;i++)
        cout<<' ';
    cout<<"ASTFEL INCAT SA VEZI";
    for(int i=0;i<42+3;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    cout<<(char)186;
    for(int i=0;i<42+7;i++)
        cout<<' ';
    cout<<"TOT CHENARUL";
    for(int i=0;i<42+7;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)186;
    for(int i=0;i<42+5;i++)
        cout<<' ';
    cout<<"APASA ORICE TASTA";
    for(int i=0;i<42+4;i++)
        cout<<' ';
    cout<<(char)186<<endl;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<112;j++)
            if(j==0||j==111)
                cout<<(char)186;
            else
                cout<<' ';
        cout<<endl;
    }
    cout<<(char)200;
    for(int i=1;i<111;i++)
        cout<<(char)205;
    cout<<(char)188;
    int c;
    c=getch();
    system("cls");
    meniu();
    return;
}
////////////////////////////////////////////////
int main()
{

    ifstream fin("scor.in");
    fin>>v[0]>>v[1]>>v[2];

    create_board();
    entry();

    return 0;
}
