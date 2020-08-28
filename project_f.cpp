#include<stdio.h>
#include<graphics.h>
#include<time.h>
typedef struct{
    int r;
    int x,y,xc,yc;
    int clr;
}Ball;
int curcol=WHITE;
void DisplayChange(int col)
{
    setcolor(col);
    for(int i=0;i<=getmaxx();i++)
        line(i,0,i,getmaxy());
}
void boundaryfill(int x,int y,int bcl,int ncl)
{
    int t=getpixel(x,y);
    if(t!=bcl && t!=ncl)
    {
        putpixel(x,y,ncl);
        boundaryfill(x+1,y,bcl,ncl);
        boundaryfill(x,y+1,bcl,ncl);
        boundaryfill(x-1,y,bcl,ncl);
        boundaryfill(x,y-1,bcl,ncl);
    }
}
void drawball(Ball b)
{
    setcolor(BLACK);
    circle(b.x,b.y,b.r);
    boundaryfill(b.x,b.y,BLACK,b.clr);
}
int moveball(Ball *b)
{
    int ispos=0;
    if(b->x + b->r + b->xc > getmaxx() || b->x - b->r + b->xc < 0)
    {
        b->xc=-b->xc;
        ispos=1;
    }
    if(b->y + b->r + b->yc > getmaxy() || b->y - b->r + b->yc <0)
    {
        b->yc=-b->yc;
        ispos=1;
    }
    b->x+=b->xc;
    b->y+=b->yc;
    return ispos;
}
void balldelete(Ball b)
{
    setcolor(curcol);
    boundaryfill(b.x,b.y,BLACK,curcol);
    circle(b.x,b.y,b.r);

}
void rectTouch(Ball *b)
{
    if(b->x + b->r + b->xc > getmaxx()-10)
    {
         b->xc=-b->xc;
         b->clr=getpixel(getmaxx()-5,b->y);
         //printf("%d",getpixel(getmaxx()-5,b->y));

    }
    if(b->x - b->r + b->xc < 11)
    {
        b->xc=-b->xc;
        b->clr=getpixel(5, b->y);
        //printf("%d",getpixel(5, b->y));
    }
    if(b->y + b->r + b->yc > getmaxy()-10)
    {
        b->yc=-b->yc;
        b->clr=getpixel(b->x,getmaxy()-5);
        //printf("%d",getpixel(b->x,getmaxy()-5));
    }
    if(b->y - b->r + b->yc <11)
    {
        b->yc=-b->yc;
        b->clr=getpixel(b->x,5);
        //printf("%d",getpixel(b->x,5));
    }
    if(b->clr== BLACK)
        b->clr=RED;

    b->x+=b->xc;
    b->y+=b->yc;
}
void drawball2(Ball b)
{
    setcolor(b.clr);
    for(int i=0;i<=b.r;i++)
        circle(b.x,b.y,i);
}
void balldelete2(Ball b)
{
    setcolor(curcol);
    for(int i=0;i<=b.r;i++)
        circle(b.x,b.y,i);

}
int main()
{
    int gd=DETECT,gm;
    Ball b;
    int col,i;
    srand(time(0));
    b.r=10;
    b.x=rand()%(getmaxx()-2*b.r)+b.r;
    b.y=rand()%(getmaxy()-2*b.r)+b.r;
    b.xc=rand()%15+5;
    b.yc=rand()%15+5;
    b.clr=RED;
    //==
    initgraph(&gd,&gm,NULL);
    DisplayChange(WHITE);
    for(i=0;i<100;i++){
        drawball(b);
        delay(100);
        balldelete(b);
        col=moveball(&b);
        if(col==1)
        {
            curcol=(curcol+1)%16;
            while(curcol==RED||curcol==BLACK)
                curcol=(curcol+1)%16;
            DisplayChange(curcol);
        }
    }
    curcol=LIGHTCYAN;
    DisplayChange(curcol);
    setcolor(BLACK);
    //blue
    rectangle(0,0,10,getmaxy()/2);
    boundaryfill(5,5,BLACK,BLUE);
    //yellow
    rectangle(0,getmaxy()/2,10,getmaxy());
    boundaryfill(2,getmaxy()/2+10,BLACK,YELLOW);
    //green
    rectangle(0,0,getmaxx()/2,10);
    boundaryfill(20,2,BLACK,GREEN);
    //magenta
    rectangle(getmaxx()/2,0,getmaxx(),10);
    boundaryfill(getmaxx()/2+10,5,BLACK,MAGENTA);
    //brown
    rectangle(getmaxx()-10,0,getmaxx(),getmaxy()/2);
    boundaryfill(getmaxx()-3,20,BLACK,BROWN);
    //light blue
    rectangle(getmaxx()-10,getmaxy()/2,getmaxx(),getmaxy());
    boundaryfill(getmaxx()-5,getmaxy()/2+10,BLACK,LIGHTBLUE);
    //light green
    rectangle(0,getmaxy()-10,getmaxx()/2,getmaxy());
    boundaryfill(20,getmaxy()-5,BLACK,LIGHTGREEN);
    //light red
    rectangle(getmaxx()/2,getmaxy()-10,getmaxx(),getmaxy());
    boundaryfill(getmaxx()-20,getmaxy()-5,BLACK,LIGHTRED);
    srand(time(0));
    b.r=10;
    b.x=rand()%(getmaxx()-2*b.r-20)+b.r+10;
    b.y=rand()%(getmaxy()-2*b.r-20)+b.r+10;
    b.xc=rand()%10+15;
    b.yc=rand()%10+15;
    b.clr=RED;
     for(i=0;i<500;i++){
        drawball(b);
        delay(100);
        balldelete(b);
        rectTouch(&b);
    }
    //3
    DisplayChange(WHITE);
    curcol=WHITE;
    Ball c[10];
    for(i=0;i<10;i++){
    	c[i].r=10;
    	c[i].x=rand()%(getmaxx()-2*c[i].r)+c[i].r;
   		c[i].y=rand()%(getmaxy()-2*c[i].r)+c[i].r;
    	c[i].xc=rand()%7+3;
    	c[i].yc=rand()%7+3;
    	c[i].clr=rand()%13+1;
    }
    for(int j=0;j<2000;j++){
		for(i=0;i<10;i++)
            drawball2(c[i]);
            delay(5);
        for(i=0;i<10;i++){
            balldelete2(c[i]);
            moveball(&c[i]);
        }
   	}
    getch();
    closegraph();
    return 0;
}
