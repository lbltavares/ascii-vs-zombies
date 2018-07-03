#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <windows.h>
#include <winuser.h>
#include <conio.h>
#include <time.h>

#define RANDOM(min, max) rand()%(max - min + 1) + min

void gotoxy(int x, int y);
void setcolor(WORD color);
void setForeGroundAndBackGroundColor(int ForeGroundColor,int BackGroundColor);
void cls();
void drawpixel( unsigned char x, unsigned char y, unsigned char Color);
void drawpixel2( unsigned char x, unsigned char y, unsigned char Color, char character);
void drawcircle(int x, int y, int a, int b, int color);
void drawline(int x0, int y0, int x1, int y1, int color);
void drawfilledrectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char bkcol);
void drawframe(unsigned x,unsigned y,unsigned sx,unsigned sy,unsigned char col,unsigned char col2,char text_[]);
void drawwindow(unsigned x,unsigned y,unsigned sx,unsigned sy,unsigned char col,unsigned char col2,unsigned char bkcol,char text_[]);

void setConsoleSize(int w, int h);

void getMonitorResolution(int *w, int *h);
void getBufferResolution(int *wpx, int *hpx);
void getMouseXY(int *x, int *y);
void getConsoleSize(int *w, int *h);
char getCursorChar();
void hidecursor();

void clearPixel(int x, int y);
long long getCurrentMillis();

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

//*****************************************************************************

long long getCurrentMillis() {
    struct timeval te;
    gettimeofday(&te, NULL);
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000;
    return milliseconds;
}

//*****************************************************************************

void clearPixel(int x, int y)
{
    gotoxy(x,y);
    printf(" ");
}

//*****************************************************************************

char getCursorChar()
{
    char c = '\0';
    CONSOLE_SCREEN_BUFFER_INFO con;
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hcon != INVALID_HANDLE_VALUE &&
        GetConsoleScreenBufferInfo(hcon,&con))
    {
        DWORD read = 0;
        if (!ReadConsoleOutputCharacterA(hcon,&c,1,
            con.dwCursorPosition,&read) || read != 1
            )
            c = '\0';
    }
    return c;
}

//*****************************************************************************

void setConsoleSize(int w, int h)
{
    HANDLE wHnd;
    HANDLE rHnd;

    SMALL_RECT windowSize = {0, 0, w, h};
    COORD bufferSize = {w+1, h+1};
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    SetConsoleScreenBufferSize(wHnd, bufferSize);
}

//*****************************************************************************

void getMonitorResolution(int *w, int *h)
{
    *h = GetSystemMetrics(SM_CYSCREEN);
    *w = GetSystemMetrics(SM_CXSCREEN);
}

//*****************************************************************************

void getBufferResolution(int *wpx, int *hpx)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);
    *wpx = csbi.dwSize.X;
    *hpx = csbi.dwSize.Y;
}

void getConsoleSize(int *w, int *h)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

//*****************************************************************************

void getMouseXY(int *x, int *y)
{
    POINT pt;
    GetCursorPos(&pt);
    *x = pt.x;
    *y = pt.y;
}

//*****************************************************************************

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}

//*****************************************************************************

void setcolor(WORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    return;
}

//*****************************************************************************


//
//     colors:
//     0 = Black
//     1 = Blue
//     2 = Green
//     3 = Cyan
//     4 = Red
//     5 = Magenta
//     6 = Yellow
//     7 = LightGray
//     8 = DarkGray
//     9 = LightBlue
//     10 = LightGreen
//     11 = LightCyan
//     12 = LightRed
//     13 = LightMagenta
//     14 = LightYellow
//     15 = White


//

//*****************************************************************************

void setForeGroundAndBackGroundColor(int ForeGroundColor,int BackGroundColor){
   int color=16*BackGroundColor+ForeGroundColor;
   setcolor(color);
}

//*****************************************************************************

void cls()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

//*****************************************************************************

void drawpixel( unsigned char x, unsigned char y, unsigned char Color){
        setcolor(Color);
        gotoxy(x,y);printf("Û");
}
//*****************************************************************************

void drawpixel2( unsigned char x, unsigned char y, unsigned char Color, char character){
        setcolor(Color);
        gotoxy(x,y);printf("%c",character);
}

//*****************************************************************************

void drawcircle(int x, int y, int a, int b, int color){
    int wx, wy;
    int thresh;
    int asq = a * a;
    int bsq = b * b;
    int xa, ya;

    drawpixel(x, y+b, color);
    drawpixel(x, y-b, color);

    wx = 0;
    wy = b;
    xa = 0;
    ya = asq * 2 * b;
    thresh = asq / 4 - asq * b;

    for (;;) {
        thresh += xa + bsq;

        if (thresh >= 0) {
            ya -= asq * 2;
            thresh -= ya;
            wy--;
        }

        xa += bsq * 2;
        wx++;

        if (xa >= ya)
          break;


        drawpixel(x+wx, y-wy, color);
        drawpixel(x-wx, y-wy, color);
        drawpixel(x+wx, y+wy, color);
        drawpixel(x-wx, y+wy, color);
    }

    drawpixel(x+a, y, color);
    drawpixel(x-a, y, color);

    wx = a;
    wy = 0;
    xa = bsq * 2 * a;

    ya = 0;
    thresh = bsq / 4 - bsq * a;

    for (;;) {
        thresh += ya + asq;

        if (thresh >= 0) {
            xa -= bsq * 2;
            thresh = thresh - xa;
            wx--;
        }

        ya += asq * 2;
        wy++;

        if (ya > xa)
          break;

        drawpixel(x+wx, y-wy, color);
        drawpixel(x-wx, y-wy, color);
        drawpixel(x+wx, y+wy, color);
        drawpixel(x-wx, y+wy, color);
    }
}

//*****************************************************************************

void drawline(int x0, int y0, int x1, int y1, int color){
    int pix = color;
    int dy = y1 - y0;
    int dx = x1 - x0;
    int stepx, stepy;

    if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
    if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
    dy <<= 1;                                                  // dy is now 2*dy
    dx <<= 1;                                                  // dx is now 2*dx

  drawpixel( x0, y0,pix);
    if (dx > dy) {
        int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
        while (x0 != x1) {
            if (fraction >= 0) {
                y0 += stepy;
                fraction -= dx;                                // same as fraction -= 2*dx
            }
            x0 += stepx;
            fraction += dy;                                    // same as fraction -= 2*dy
            drawpixel( x0, y0,pix);
        }
    } else {
        int fraction = dx - (dy >> 1);
        while (y0 != y1) {
            if (fraction >= 0) {
                x0 += stepx;
                fraction -= dy;
            }
            y0 += stepy;
            fraction += dx;
            drawpixel( x0, y0,pix);
        }
    }
}

//*****************************************************************************


void drawframe(unsigned x,unsigned y,unsigned sx,unsigned sy,unsigned char col,unsigned char col2,char text_[]){
    unsigned i,j,m;{

       m=(sx-x);                       //differential
       j=m/8;                          //adjust
       j=j-1;                          //more adjustment
       gotoxy(x,y);printf("É");       //Top left corner of drawframe
       gotoxy(sx,y);printf("»");      //Top right corner of drawframe
       gotoxy(x,sy);printf("È");      //Bottom left corner of drawframe
       gotoxy(sx,sy);printf("¼");     //Bottom right corner of drawframe

       for (i=x+1;i<sx;i++){
          gotoxy(i,y);printf("Í");     // Top horizontol line
          gotoxy(i,sy);printf("Í");    // Bottom Horizontal line
       }

       for (i=y+1;i<sy;i++){
          gotoxy(x,i);printf("º");     //Left Vertical line
          gotoxy(sx,i);printf("º");    //Right Vertical Line
       }

          gotoxy(x+j,y);printf(text_); //put Title
          gotoxy(1,24);
    }
}

 //*****************************************************************************

void drawfilledrectangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char bkcol){
    int x,y;
    setcolor(bkcol);                       //Set to color bkcol

    for (y=y1;y<y2;y++){                    //Fill Y Region Loop
        for (x=x1;x<x2;x++) {              //Fill X region Loop
          gotoxy(x,y);printf(" ");       //Draw Solid space
        }
    }
}

//*****************************************************************************

void drawwindow(unsigned x,unsigned y,unsigned sx,unsigned sy,
         unsigned char col, unsigned char col2,unsigned char bkcol,char text_[]){
    drawfilledrectangle(x,y,sx,sy,bkcol);
    drawframe(x,y,sx,sy,col,col2,text_);
}

//*****************************************************************************


void drawcolorpalette(){
    for (int i=0;i<16;i++){
        for (int j=0;j<16;j++){
            setForeGroundAndBackGroundColor(i,j);
            gotoxy(i*4,j);printf("%d",(i*j)+1);


        }

    }

}


//*****************************************************************************


#endif //
