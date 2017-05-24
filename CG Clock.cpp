

/*
 CG Project
 */
#include<Windows.h>
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glut.h>3
//#include<openglut.h>

//#include<GL/freeglut.h>

#include<time.h>
#include<math.h>
#include<sys/timeb.h>
#include<string.h>
/* Function that returns -1,0,1 depending on whether x */
/* is <0, =0, >0 respectively */
#define sign(x) ((x>0)?1:((x<0)?-1:0))
void createmenu(void);
int hour,minute,second,a,b,c,d,e,f,z=2,hmax,mmax,smax,htmr,mtmr,stmr,t,times,n,yAn=200;
static int mmenu;
static int dmenu;
static int amenu;
static int wtmenud;
static int wtmenua;
static int window;
static int currentt;
static int alarmd;
static int alarma;
static int timerd;
static int timera;
int value;


/* Function to plot a point */

void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

/* Generalized Bresenham's Algorithm */
void bres_general(int x1, int y1, int x2, int y2)
{
  glColor3f(0.0,1.0,0.0);
  int dx, dy, x, y, d, s1, s2, swap=0, temp;

  dx = abs(x2 - x1);
  dy = abs(y2 - y1);
  s1 = sign(x2-x1);
  s2 = sign(y2-y1);

  /* Check if dx or dy has a greater range */
  /* if dy has a greater range than dx swap dx and dy */
  if(dy > dx){temp = dx; dx = dy; dy = temp; swap = 1;}

  /* Set the initial decision parameter and the initial point */
  d = 2 * dy - dx;
  x = x1;
  y = y1;

  int i;
  for(i = 1; i <= dx; i++)
  {
    setPixel(x,y);

    while(d >= 0)
    {
      if(swap) x = x + s1;
      else
      {
        y = y + s2;
        d = d - 2* dx;
      }
    }
    if(swap) y = y + s2;
    else x = x + s1;
    d = d + 2 * dy;
  }
  glFlush();
}
void drawbres(int num,int x,int y)
{
    switch(num)
    {
       case 1: bres_general(x+80,y,x+80,y+80);
               bres_general(x+80,y+80,x+80,y+160);
               break;

       case 2: bres_general(x,y+160,x+80,y+160);
               bres_general(x+80,y+160,x+80,y+80);
               bres_general(x+80,y+80,x,y+80);
               bres_general(x,y+80,x,y);
               bres_general(x,y,x+80,y);
               break;

       case 3: bres_general(x,y+160,x+80,y+160);
               bres_general(x+80,y+160,x+80,y+80);
               bres_general(x+80,y+80,x,y+80);
               bres_general(x+80,y+80,x+80,y);
               bres_general(x,y,x+80,y);
               break;

       case 4: bres_general(x,y+80,x,y+160);
               bres_general(x,y+80,x+80,y+80);
               bres_general(x+80,y+160,x+80,y+80);
               bres_general(x+80,y+80,x+80,y);
               break;

       case 5: bres_general(x,y+160,x+80,y+160);
               bres_general(x,y+80,x,y+160);
               bres_general(x,y+80,x+80,y+80);
               bres_general(x+80,y+80,x+80,y);
               bres_general(x,y,x+80,y);
               break;

       case 6: bres_general(x,y,x,y+80);
               bres_general(x,y+160,x+80,y+160);
               bres_general(x,y+80,x,y+160);
               bres_general(x,y+80,x+80,y+80);
               bres_general(x+80,y+80,x+80,y);
               bres_general(x,y,x+80,y);
               break;

       case 7: bres_general(x,y+160,x+80,y+160);
               bres_general(x+80,y+160,x+80,y+80);
               bres_general(x+80,y+80,x+80,y);
               break;

       case 8: bres_general(x,y,x,y+80);
               bres_general(x,y+160,x+80,y+160);
               bres_general(x,y+80,x,y+160);
               bres_general(x,y+80,x+80,y+80);
               bres_general(x+80,y+80,x+80,y);
               bres_general(x,y,x+80,y);
               bres_general(x+80,y+80,x+80,y+160);
               break;

       case 9: bres_general(x,y+160,x+80,y+160);
               bres_general(x,y+80,x,y+160);
               bres_general(x,y+80,x+80,y+80);
               bres_general(x+80,y+80,x+80,y);
               bres_general(x+80,y+80,x+80,y+160);
               break;

       case 0: bres_general(x,y,x,y+80);
               bres_general(x,y+160,x+80,y+160);
               bres_general(x,y+80,x,y+160);
               bres_general(x+80,y+80,x+80,y);
               bres_general(x,y,x+80,y);
               bres_general(x+80,y+80,x+80,y+160);
               break;
    }
}


void Circle(int xCenter,int yCenter){

  int r=2;
  int x=0,y=r;
  int d = 3/2 - r;    // = 1 - r
  //glClear(GL_COLOR_BUFFER_BIT);
  glColor3f( 0 ,1, 0);
  while(x<=y){
    setPixel(xCenter+x,yCenter+y);
    setPixel(xCenter+y,yCenter+x);  //find other points by symmetry
    setPixel(xCenter-x,yCenter+y);
    setPixel(xCenter+y,yCenter-x);
    setPixel(xCenter-x,yCenter-y);
    setPixel(xCenter-y,yCenter-x);
    setPixel(xCenter+x,yCenter-y);
    setPixel(xCenter-y,yCenter+x);
    if (d<0)
  d += (2*x)+3;
    else {
 d += (2*(x-y))+5;
 y -= 1;
    }
    x++;
  }

  glFlush();
}
/* Function to draw a rhombus inscribed in a rectangle and roll */
/* number printed in it */
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawbres(a,60,200);
  drawbres(b,170,200);
  drawbres(c,310,200);
  drawbres(d,420,200);
  drawbres(e,560,200);
  drawbres(f,670,200);
  Circle(280,280);
  Circle(280,360);
  Circle(530,280);
  Circle(530,360);

  glFlush();
}

void draw1(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawbres(a,60,yAn);
  drawbres(b,170,yAn);
  drawbres(c,310,yAn);
  drawbres(d,420,yAn);
  drawbres(e,560,yAn);
  drawbres(f,670,yAn);
  Circle(280,yAn+40);
  Circle(280,yAn+120);
  Circle(530,yAn+40);
  Circle(530,yAn+120);

  glFlush();
}

void init() {
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(840, 480);
  glutCreateWindow("Digital Clock");
  glClearColor(0.0,0.0,0.0,0);
  glColor3f(1.0,1.0,1.0);
  gluOrtho2D(0,840,0,480);



}



void TimerFunc(int value)
{
    time_t now=time(0);
                         tm *local=localtime(&now);


                         hour=local->tm_hour;
                         minute=local->tm_min;
                         second=local->tm_sec;

                          if(z==1 && hour>12)
                            hour=hour-12;
                         if(z==1 && hour==0)
                            hour=12;

                         a=hour/10;
                         b=hour%10;
                         c=minute/10;
                         d=minute%10;
                         e=second/10;
                         f=second%10;
                         glutPostRedisplay();

                         glutTimerFunc(1000,TimerFunc,1);
}
void TimerFunc1(int value)
{
 time_t now=time(0);
                         tm *local=localtime(&now);

                         hour=local->tm_hour;
                         minute=local->tm_min;
                         second=local->tm_sec;

                         if(hour==hmax && second==smax && minute==mmax)
                             {
                                glClearColor(1,0,0,1);
                                PlaySound("C:\\Users\\Aditya\\Desktop\\Piano\\alarm.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

                             }
                         a=hour/10;
                         b=hour%10;
                         c=minute/10;
                         d=minute%10;
                         e=second/10;
                         f=second%10;
                         glutPostRedisplay();
                         glutTimerFunc(1000,TimerFunc1,1);
}

void TimerFunc2(int value)
{
    if(hour==0 && minute==0 && second==0)
    {

        PlaySound("C:\\Users\\Aditya\\Desktop\\Piano\\pager.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    }
    else
    {
        if(hour==0 && minute==0 && second==1)
            glClearColor(1,0,0,1);
        if(second==0 && minute==0)
        {
            hour--;
            second=59;
            minute=59;
        }
        else if(second==0)
        {
            minute--;
            second=59;
        }
        else
            second--;

         a=hour/10;
         b=hour%10;
         c=minute/10;
         d=minute%10;
         e=second/10;
         f=second%10;
         glutPostRedisplay();
         glutTimerFunc(1000,TimerFunc2,1);
    }

}

void TimerFunc3(int value)
{
                         time_t now=time(0);
                         tm *local=localtime(&now);
                         switch(t)
                         {
                        case 1:     {
                                    local=gmtime(&now);
                                    hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour>=4)
                                        hour-=4;
                                    else
                                        hour=20+hour;

                                    break;
                                     }

                            case 2: {
                                    local=gmtime(&now);
                                    hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                     break;
                                   }
                            case 3: {
                                    local=gmtime(&now);
                                    hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour<13)
                                        hour=hour+11;
                                    else
                                        hour=hour-13;
                                    break;
                                    }
                            case 4: {
                                      local=gmtime(&now);
                                    hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour<16)
                                        hour=hour+8;
                                    else
                                        hour=hour-16;
                                    break;
                                     }
                            case 5:  {
                                      local=gmtime(&now);
                                     hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour<16)
                                        hour=hour+8;
                                    else
                                        hour=hour-16;
                                    break;
                                      }

                            case 6:  {
                                      local=gmtime(&now);
                                     hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour<15)
                                        hour=hour+9;
                                    else
                                        hour=hour-15;
                                    break;

                                   }

                            case 7: {
                                       local=localtime(&now);
                                        hour=local->tm_hour;
                                        minute=local->tm_min;
                                        second=local->tm_sec;
                                        break;
                                    }

                            default: {
                                     printf("Wrong choice\n");
                                     return;
                                     }
                         }
                         a=hour/10;
                         b=hour%10;
                         c=minute/10;
                         d=minute%10;
                         e=second/10;
                         f=second%10;
                         glutPostRedisplay();


                         glutTimerFunc(1000,TimerFunc3,1);

}


const float clockR    = 80.0f,
            clockVol  = 100.0f,

            angle1min = M_PI / 30.0f,

            minStart  = 0.9f,
            minEnd    = 1.0f,

            stepStart = 0.8f,
            stepEnd   = 1.0f;

float angleHour = 0,
      angleMin  = 0,
      angleSec  = 0;



void newLine(float rStart, float rEnd, float angle){
  float c = cos(angle), s = sin(angle);
  glVertex2f( clockR*rStart*c, clockR*rStart*s);
  glVertex2f( clockR*rEnd*c, clockR*rEnd*s);
}



void RenderScene(void){
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);

  glBegin(GL_LINES);
    for(i=0; i<60; i++){
      if(i%5){ // normal minute
        if(i%5 == 1)
          glColor3f(0.0f, 1.0f, 0.0f);
        newLine(minStart, minEnd, i*angle1min);
      }else{
        glColor3f(1.0f, 0.0f, 0.0f);
        newLine(stepStart, stepEnd, i*angle1min);
      }
    }
  glEnd();

  glLineWidth(3.0f);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.5f, -angleHour+M_PI/2);
    newLine(0.0f, 0.8f, -angleMin+M_PI/2);
  glEnd();

  glLineWidth(1.0f);
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.8f, -angleSec+M_PI/2);
  glEnd();

  glutSwapBuffers();
}

void RenderScene1(void){
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0f, 0.0f, 0.0f);
  glLineWidth(2.0f);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);


  glBegin(GL_LINES);

    for(i=0; i<60; i++){
      if(i%5){ // normal minute
        if(i%5 == 1)
          glColor3f(0.0f, 1.0f, 0.0f);
        newLine(minStart, minEnd, i*angle1min);
      }else{
        glColor3f(1.0f, 0.0f, 0.0f);
        newLine(stepStart, stepEnd, i*angle1min);
      }
    }
  glEnd();
/*
  glLineWidth(3.0f);
  glColor3f(1.0f,1.0f,0.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.5f, -angleHour+M_PI/2);
    newLine(0.0f, 0.8f, -angleMin+M_PI/2);
  glEnd();
*/
  glLineWidth(1.0f);
  glColor3f(1.0f, 1.0f, 0.0f);
  glBegin(GL_LINES);
    newLine(0.0f, 0.8f, -angleSec+M_PI/2);
  glEnd();

  glutSwapBuffers();
}

void SetupRC(void){
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}


// Called by GLUT library when the window has changed size
void ChangeSize(GLsizei w, GLsizei h){
  GLfloat aspectRatio;

  // Prevent a divide by zero
  if(h == 0)
    h = 1;

  // Set viewport to window dimensions
  glViewport(0, 0, w, h);

  // Reset coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Establish clipping volume (left, right, bottom, top, near, far)
  aspectRatio = (GLfloat)w / (GLfloat)h;
  if (w <= h)
    glOrtho (-clockVol, clockVol, -clockVol / aspectRatio, clockVol / aspectRatio, 1.0, -1.0);
  else
    glOrtho (-clockVol * aspectRatio, clockVol * aspectRatio, -clockVol, clockVol, 1.0, -1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


void TimerFunction4(int value){
  struct timeb tb;
  time_t tim=time(0);
  struct tm* t;
  t=localtime(&tim);
  ftime(&tb);

  //angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
  angleSec = (float)(t->tm_sec)/30.0f * M_PI;
  angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
  angleHour = (float)(t->tm_hour > 12 ? t->tm_hour-12 : t->tm_hour)/6.0f * M_PI+
              angleMin/12.0f;


  glutPostRedisplay();
  glutTimerFunc(1000,TimerFunction4, 1);
}

void TimerFunction5(int value){
  struct timeb tb;
  time_t tim=time(0);
  struct tm* t;
  t=localtime(&tim);
  ftime(&tb);

if(hour==23 && minute==59 && second==59)
    {
        hour=0;
        second=0;
        minute=0;
    }
    else
        if(minute==59 && second==59)
    {
        hour++;
        minute=0;
        second=0;
    }
    else
        if(second==59)
    {
        minute++;
        second=0;
    }
    else
        second++;
  t->tm_sec=second;
  t->tm_min=minute;
  t->tm_hour=hour;

  //angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
  angleSec = (float)(t->tm_sec)/30.0f * M_PI;
  angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
  angleHour = (float)(t->tm_hour > 12 ? t->tm_hour-12 : t->tm_hour)/6.0f * M_PI+
              angleMin/12.0f;


  glutPostRedisplay();
  glutTimerFunc(1000,TimerFunction5, 1);
}

void TimerFunction6(int value){
  struct timeb tb;
  time_t tim=time(0);
  struct tm* t;
  t=localtime(&tim);
  ftime(&tb);
  struct tm *local=t;
  time_t now=tim;

  switch(times)
  {
                             case 1:{
                                    local=gmtime(&now);
                                    hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour>=4)
                                        hour-=4;
                                    else
                                        hour=20+hour;

                                    break;
                                     }

                            case 2: {
                                    local=gmtime(&now);
                                    hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                     break;
                                   }
                            case 3: {
                                    local=gmtime(&now);
                                    hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour<13)
                                        hour=hour+11;
                                    else
                                        hour=hour-13;
                                    break;
                                    }
                            case 4: {
                                      local=gmtime(&now);
                                    hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour<16)
                                        hour=hour+8;
                                    else
                                        hour=hour-16;
                                    break;
                                     }
                            case 5:  {
                                      local=gmtime(&now);
                                     hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour<16)
                                        hour=hour+8;
                                    else
                                        hour=hour-16;
                                    break;
                                      }

                            case 6:  {
                                      local=gmtime(&now);
                                     hour=local->tm_hour;
                                    minute=local->tm_min;
                                    second=local->tm_sec;
                                    if(hour<15)
                                        hour=hour+9;
                                    else
                                        hour=hour-15;
                                    break;

                                   }

                             case 7: {
                                         local=localtime(&now);
                                         hour=local->tm_hour;
                                         minute=local->tm_min;
                                         second=local->tm_sec;
                                         break;
                                     }

                            default: {
                                     printf("Wrong choice\n");
                                     return;
                                     }
  }

  t->tm_sec=second;
  t->tm_min=minute;
  t->tm_hour=hour;

  //angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
  angleSec = (float)(t->tm_sec)/30.0f * M_PI;
  angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
  angleHour = (float)(t->tm_hour > 12 ? t->tm_hour-12 : t->tm_hour)/6.0f * M_PI+angleMin/12.0f;


  glutPostRedisplay();
  glutTimerFunc(1000,TimerFunction6, 1);
}

void TimerFunction7(int value)
{

                            struct timeb tb;
                            time_t tim=time(0);
                            struct tm* t;
                           t=localtime(&tim);
                           ftime(&tb);
                          struct tm *local=t;
                         time_t now=tim;
                         hour=local->tm_hour;
                         minute=local->tm_min;
                         second=local->tm_sec;

                         if(hour==hmax && second==smax && minute==mmax)
                             {
                                glClearColor(0,0,1,1);
                                PlaySound("C:\\Users\\Aditya\\Desktop\\Piano\\alarm.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

                             }
                          // angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
                           angleSec = (float)(t->tm_sec)/30.0f * M_PI;
                           angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
                           angleHour = (float)(t->tm_hour > 12 ? t->tm_hour-12 : t->tm_hour)/6.0f * M_PI+angleMin/12.0f;


                         glutPostRedisplay();
                         glutTimerFunc(1000,TimerFunction7, 1);

}

void TimerFunction8(int value)
{
                           static int i=-1;
                          struct timeb tb;
                          time_t tim=time(0);
                          struct tm* t;
                          t=localtime(&tim);
                          ftime(&tb);
                          struct tm *local=t;
                         time_t now=tim;
                        // hour=local->tm_hour;
                        // minute=local->tm_min;
                        // second=local->tm_sec;

                         if(i==n)
                             {
                                glClearColor(0,0,1,1);
                                PlaySound("C:\\Users\\Aditya\\Desktop\\Piano\\pager.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

                                second=0;

                             }
                        else
                           if(i==60)
                           {
                               second=0;
                               i++;
                           }
                           else
                            if(i==-1)
                           {
                               second=0;
                               i=1;
                           }

                           else
                           {
                               second++;
                               i++;
                           }

                           t->tm_sec=second;
                         // angleSec = (float)(t->tm_sec+ (float)tb.millitm/1000.0f)/30.0f * M_PI;
                          angleSec = (float)(t->tm_sec)/30.0f * M_PI;
                           //angleMin = (float)(t->tm_min)/30.0f * M_PI + angleSec/60.0f;
                           //angleHour = (float)(t->tm_hour > 12 ? t->tm_hour-12 : t->tm_hour)/6.0f * M_PI+angleMin/12.0f;



                         glutPostRedisplay();
                         glutTimerFunc(1000,TimerFunction8, 1);
}

void TimerFunc9(int value)
{
    if(hour==23 && minute==59 && second==59)
    {
        hour=0;
        second=0;
        minute=0;
    }
    else
        if(minute==59 && second==59)
    {
        hour++;
        minute=0;
        second=0;
    }
    else
        if(second==59)
    {
        minute++;
        second=0;
    }
    else
        second++;
    a=hour/10;
    b=hour%10;
    c=minute/10;
    d=minute%10;
    e=second/10;
    f=second%10;
    static int i=0;
    if(i<20)
    {
       yAn=yAn-10;
       i++;
       glutPostRedisplay();
       glutTimerFunc(1000,TimerFunc9,1);

    }k
    else
    if(i<40)
    {
        yAn=yAn+10;
        i++;
        glutPostRedisplay();
        glutTimerFunc(1000,TimerFunc9,1);
    }
    else
    {
        i=0;
        glutPostRedisplay();
        glutTimerFunc(1000,TimerFunc9,1);
    }

}

void Timer()
{
    char s1[]="Clock Application";
    char s2[]="By";
    char s3[]="Swaroop Ranganath";
    char s4[]="Aditya Jayasimha";
    char s5[]="Hriday Kaju";
    char s6[]="Harsha K";
    char c;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1,0);
    //glRasterPos2i(360,300);
    glTranslatef(180,300,0);
    glScalef(0.5,0.5,0);
    for (c=0; c<strlen(s1); c++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s1[c]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,s1[c]);
	}
    //glutSwapBuffers();
    glColor3f(1.0,0.0,0.0);
    glTranslatef(-360,-150,0);
    glScalef(0.5,0.5,0);
    for (c=0; c<strlen(s2); c++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s2[c]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,s2[c]);
	}
	glColor3f(0.0,0.0,1.0);
	glTranslatef(-400,-150,0);
	for (c=0; c<strlen(s3); c++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s2[c]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,s3[c]);
	}
	glColor3f(1.0,1.0,0.0);
	glTranslatef(-1200,-150,0);
	for (c=0; c<strlen(s4); c++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s2[c]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,s4[c]);
	}
   // glutSwapBuffers();
    glColor3f(1.0,0.0,1.0);
    glTranslatef(-1080,-150,0);
	for (c=0; c<strlen(s5); c++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s2[c]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,s5[c]);
	}
	glColor3f(0.0,1.0,1.0);
	glTranslatef(-720,-150,0);
	for (c=0; c<strlen(s6); c++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s2[c]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN,s6[c]);
	}
    glutSwapBuffers();



}
void menu(int num){
  if(num == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    value = num;
    switch(value)
             {
                 case 28: {z=1;}
                 case 29: {
                        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
           glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Digital Clock");
            createmenu();
           glClearColor(0.0,0.0,0.0,0);
        glColor3f(1.0,1.0,1.0);
        gluOrtho2D(0,840,0,480);

                        time_t now=time(0);
                         tm *local=localtime(&now);

                         hour=local->tm_hour;
                         minute=local->tm_min;
                         second=local->tm_sec;

                         if(z==1 && hour>12)
                            hour=hour-12;
                         if(z==1 && hour==0)
                            hour=12;

                         a=hour/10;
                         b=hour%10;
                         c=minute/10;
                         d=minute%10;
                         e=second/10;
                         f=second%10;

                         glutDisplayFunc(draw);

                          glutTimerFunc(1000,TimerFunc,1);
                         glutMainLoop();


                         break;
                 }
                 case 21:
                 case 22:
                 case 23:
                 case 24:
                 case 25:
                 case 26:
                 case 27:
                    {
                            glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
           glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Digital Clock");
            createmenu();
           glClearColor(0.0,0.0,0.0,0);
        glColor3f(1.0,1.0,1.0);
        gluOrtho2D(0,840,0,480);

                           switch(value){
                                case 21: t=1;
                                            break;
                                 case 22: t=2;
                                            break;
                                 case 23: t=3;
                                            break;
                                 case 24: t=4;
                                            break;
                                 case 25: t=5;
                                            break;
                                  case 26: t=6;
                                            break;
                                  case 27: t=7;
                                            break;


                           }
                           glutDisplayFunc(draw);
                           glutTimerFunc(33,TimerFunc3,1);
                           glutMainLoop();
                           break;
                           }

                 case 51:
                 case 52:
                 case 53:
                 case 54:
                            {

                           glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
           glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Digital Clock");
            createmenu();
           glClearColor(0.0,0.0,0.0,0);
        glColor3f(1.0,1.0,1.0);
        gluOrtho2D(0,840,0,480);
                           time_t now=time(0);
                           tm *local=localtime(&now);

                           hmax=hour=local->tm_hour;
                           mmax=minute=local->tm_min;
                           smax=second=local->tm_sec;
                        switch(value){
                            case 51: smax+=10;
                                     break;
                            case 52: mmax+=5;
                                     break;
                            case 53: mmax+=30;
                                     break;
                            case 54: hmax+=1;
                                     break;
                           }
                           if(hmax==24)
                            hmax=0;
                           if(mmax>=60)
                           {
                               mmax=(mmax-60)%60;
                               hmax=(hmax+1)%24;
                           }
                           if(smax>=60)
                           {
                              if(mmax==59)
                                hmax=(hmax+1)%24;
                              mmax=(mmax+1)%60;
                              smax=(smax-60)%60;
                           }
                           a=hour/10;
                           b=hour%10;
                           c=minute/10;
                           d=minute%10;
                           e=second/10;
                           f=second%10;

                           glutDisplayFunc(draw);
                           glutTimerFunc(1000,TimerFunc1,1);

                           glutMainLoop();
                           break;
                           }

                 case 55:
                 case 56:
                 case 57:
                 case 58:
                       {

                           glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
           glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Digital Clock");
            createmenu();
           glClearColor(0.0,0.0,0.0,0);
        glColor3f(1.0,1.0,1.0);
        gluOrtho2D(0,840,0,480);
                           htmr=0;
                           mtmr=0;
                           stmr=0;
                           switch(value){
                            case 55: stmr=10;
                                     break;
                            case 56: mtmr=1;
                                     break;
                            case 57: mtmr+=5;
                                     break;
                            case 58: mtmr+=10;
                                     break;
                           }
                           hour=htmr;
                           minute=mtmr;
                           second=stmr;
                           a=hour/10;
                           b=hour%10;
                           c=minute/10;
                           d=minute%10;
                           e=second/10;
                           f=second%10;

                           glutDisplayFunc(draw);
                           glutTimerFunc(1000,TimerFunc2,1);

                           glutMainLoop();
                           break;
                           }
              case 32:
                  {

                            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Analog Clock");
            createmenu();
            glClearColor(0.0,0.0,0.0,0);
            glColor3f(1.0f,1.0f,1.0f);
            gluOrtho2D(0,840,0,480);
                            glutDisplayFunc(RenderScene);
                            glutReshapeFunc(ChangeSize);
                            glutTimerFunc(33, TimerFunction4, 1);

                            SetupRC();

                            glutMainLoop();

                            break;
                              }

                 case 41:
                 case 42:
                 case 43:
                 case 44:
                 case 45:
                 case 46:
                 case 47:  {
                        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Analog Clock");
            createmenu();
            glClearColor(0.0,0.0,0.0,0);
            glColor3f(1.0f,1.0f,1.0f);
            gluOrtho2D(0,840,0,480);
                            switch(value){
                                case 41: times=1;
                                            break;
                                 case 42: times=2;
                                            break;
                                 case 43: times=3;
                                            break;
                                 case 44: times=4;
                                            break;
                                 case 45: times=5;
                                            break;
                                  case 46: times=6;
                                            break;
                                  case 47: times=7;
                                            break;
                            }
                            glutDisplayFunc(RenderScene);
                            glutReshapeFunc(ChangeSize);
                            glutTimerFunc(33, TimerFunction6, 1);
                            SetupRC();
                            glutMainLoop();
                            break;
                          }


                 case 61:
                 case 62:
                 case 63:
                 case 64:
                    {
                     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Analog Clock");
            createmenu();
            glClearColor(0.0,0.0,0.0,0);
            glColor3f(1.0f,1.0f,1.0f);
            gluOrtho2D(0,840,0,480);

                             time_t now=time(0);
                           tm *local=localtime(&now);

                           hmax=local->tm_hour;
                           mmax=local->tm_min;
                           smax=local->tm_sec;
                        switch(value){
                            case 61: smax+=10;
                                     break;
                            case 62: mmax+=5;
                                     break;
                            case 63: mmax+=30;
                                     break;
                            case 64: hmax+=1;
                                     break;
                           }
                           if(hmax==24)
                            hmax=0;
                           if(mmax>=60)
                           {
                               mmax=(mmax-60)%60;
                               hmax=(hmax+1)%24;
                           }
                           if(smax>=60)
                           {
                              if(mmax==59)
                                hmax=(hmax+1)%24;
                              mmax=(mmax+1)%60;
                              smax=(smax-60)%60;
                           }
                             glutDisplayFunc(RenderScene);
                             glutReshapeFunc(ChangeSize);
                             glutTimerFunc(33, TimerFunction7, 1);
                             SetupRC();
                             glutMainLoop();
                             break;
                         }

                  case 65:
                 case 66:
                 case 67:
                 case 68:{
                            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            glutCreateWindow("Analog Clock");
            createmenu();
            glClearColor(0.0,0.0,0.0,0);
            glColor3f(1.0f,1.0f,1.0f);
            gluOrtho2D(0,840,0,480);
                              htmr=0;
                           mtmr=0;
                           stmr=0;
                           switch(value){
                            case 65: stmr+=10;
                                     break;
                            case 66: mtmr+=1;
                                     break;
                            case 67: mtmr+=5;
                                     break;
                            case 68: mtmr+=10;
                                     break;
                           }
                              n=(htmr*3600+mtmr*60+stmr);
                               glutDisplayFunc(RenderScene1);
                               glutReshapeFunc(ChangeSize);
                               glutTimerFunc(33, TimerFunction8, 1);
                             SetupRC();
                             glutMainLoop();
                             break;
                          }
  }
  glutPostRedisplay();
}
}

void createmenu(void){
    wtmenud = glutCreateMenu(menu);
    glutAddMenuEntry("New York(EST)",21);
    glutAddMenuEntry("GMT",22);
    glutAddMenuEntry("Melbourne",23);
    glutAddMenuEntry("Beijing",24);
    glutAddMenuEntry("Singapore",25);
    glutAddMenuEntry("Tokyo",26);
    glutAddMenuEntry("New Delhi",27);

    currentt = glutCreateMenu(menu);
    glutAddMenuEntry("12 Hr Format",28);
    glutAddMenuEntry("24 Hr Format",29);

    alarmd = glutCreateMenu(menu);
    glutAddMenuEntry("10 Seconds",51);
    glutAddMenuEntry("5 Minutes",52);
    glutAddMenuEntry("30 Minutes",53);
    glutAddMenuEntry("1 Hour",54);

    timerd = glutCreateMenu(menu);
    glutAddMenuEntry("10 Seconds",55);
    glutAddMenuEntry("1 Minute",56);
    glutAddMenuEntry("5 Minutes",57);
    glutAddMenuEntry("10 Minutes",58);

    dmenu = glutCreateMenu(menu);
    glutAddSubMenu("Current Time",currentt);
    glutAddSubMenu("World Time",wtmenud);
    glutAddSubMenu("Set Alarm",alarmd);
    glutAddSubMenu("Set Timer",timerd);

    wtmenua = glutCreateMenu(menu);
    glutAddMenuEntry("New York(EST)",41);
    glutAddMenuEntry("GMT",42);
    glutAddMenuEntry("Melbourne",43);
    glutAddMenuEntry("Beijing",44);
    glutAddMenuEntry("Singapore",45);
    glutAddMenuEntry("Tokyo",46);
    glutAddMenuEntry("New Delhi",47);

    alarma = glutCreateMenu(menu);
    glutAddMenuEntry("10 Seconds",61);
    glutAddMenuEntry("5 Minutes",62);
    glutAddMenuEntry("30 Minutes",63);
    glutAddMenuEntry("1 Hour",64);

    timera = glutCreateMenu(menu);
    glutAddMenuEntry("10 Seconds",65);
    glutAddMenuEntry("1 Minute",66);
    glutAddMenuEntry("5 Minutes",67);
    glutAddMenuEntry("10 Minutes",68);

    amenu = glutCreateMenu(menu);
    glutAddMenuEntry("Current Time",32);
    glutAddSubMenu("World Time",wtmenua);
    glutAddSubMenu("Set Alarm",alarma);
    glutAddSubMenu("Set Timer",timera);

    mmenu=glutCreateMenu(menu);
    glutAddSubMenu("Digital Clock",dmenu);
    glutAddSubMenu("Analog Clock",amenu);
    //glutAddMenuEntry("")
    glutAddMenuEntry("Exit",0); glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

  int choice,ch;

  printf("Welcome to clock application\n");
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowPosition(0,0);
            glutInitWindowSize(840, 480);
            window =glutCreateWindow("Welcome to clock application");
            createmenu();
            glClearColor(0.0,0.0,0.0,0);
            glColor3f(1.0f,1.0f,1.0f);
            gluOrtho2D(0,840,0,480);
            glutDisplayFunc(Timer);
            glutMainLoop();
return 0;
}


