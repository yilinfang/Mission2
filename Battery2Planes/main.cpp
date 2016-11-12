/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include"factory.h"
#include"plane.h"
#include"planeflock.h"

int winHeight;
int winWidth;
PlaneFlock Mission1;
int sign=0;
int frameNum=0;
/* GLUT callback Handlers */

int  GameState=0; //0:��Ϸ���ڽ��У�1:��̨Ӯ,2:�ɻ�Ӯ




static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    winHeight=height;
    winWidth=width;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
int getFPS()
{
    static int FPS = 0;
    static int lastFPS=0;
    static int tempFPStime=0;

     FPS++;

     int nowtime = GetTickCount();
     if (nowtime - tempFPStime >= 1000){
          lastFPS = FPS;
          tempFPStime = nowtime;
          FPS = 0;
     }
    return lastFPS;
}

void selectFont(int size, int charset, const char* face) {
    HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
        charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
    HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
    DeleteObject(hOldFont);
}
void drawString(const char* str,int x,int y) {
    static int isFirstCall = 1;
    static GLuint lists;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, winWidth-1, 0, winHeight-1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //�����￪ʼ�����ά����
      selectFont(48, ANSI_CHARSET, "Comic Sans MS");  //���������ϵͳ�ļ���Ѱ��
      glColor3f(1.0f, 0.0f, 0.0f);
      glRasterPos2i(x, winHeight-y); //x��y����Ļ���꣬���½�Ϊ(0,0)

    if( isFirstCall ) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
                         // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
         isFirstCall = 0;

         // ����MAX_CHAR����������ʾ�б���
         lists = glGenLists(MAXCHAR);

         // ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
         wglUseFontBitmaps(wglGetCurrentDC(), 0, MAXCHAR, lists);
     }
     // ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
    for(; *str!='\0'; ++str)
         glCallList(lists + *str);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}
static void drawing()
{

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    //gluOrtho2D(0, winWidth-1, 0, winHeight-1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();


    glColor3f(1.0f,1.0f,1.0f);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5, -0.5); //��P1,���½�
    glVertex2f(-0.5, 0.5);  //��P2,���Ͻ�
    glVertex2f(0.5, 0.5);   //��P3,���Ͻ�
    glVertex2f(0.5, -0.5); //��P4,���½�
    glEnd();

    // Mission1.UpdatePosition();
    glColor3f(1.0f,0.0f,0.0f);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(-0.503,0);
    glEnd();
    glColor3f(1.0f,1.0f,1.0f);
    glPointSize(2);
    Mission1.planesDisplay();


    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

static void WinOrLost()
{


     static long stTime = GetTickCount();
     static long remTime=0;

     if(GameState==0)
     {
         remTime = 40000L - GetTickCount() + stTime;
         if(Mission1.PlaneWin())
             GameState = 2;
         else if(remTime<0)
             GameState = 1;
     }


     char str[30];
     sprintf(str,"Time Remaining:%.0fs",remTime/1000.0f);
     drawString(str,10,40);

     if(GameState==2)
     {
        drawString("Plane Win!!!!",10,80);
     }
     if(GameState==1)
     {
         drawString("Emplacement Win!!!!",10,80);
     }


}
static void display(void)
{
    //const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    //const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawing();


    drawString("FPS:",winWidth-150,40);
    WinOrLost();
    int in;
    in=getFPS();
    //printf("%d %d %d\n",in,winHeight,winWidth);
    char out[MAXCHAR];
    itoa(in,out,10);
    drawString(out,winWidth-80,40);
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        /*case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;*/
    }
    glutPostRedisplay();
}

static void idle(void)
{



    Mission1.UpdatePosition();
    Mission1.RemoveDeadPlanes();
    glutPostRedisplay();
}

static void tmrProduceHeavyPlanes(int value) //ÿ2������1�����ͷɻ�
{
    Mission1.addHeavyPlane(1);
    glutTimerFunc(2000, tmrProduceHeavyPlanes, value);
}
static void tmrProduceLightPlanes(int value) //ÿ1������3�����ͷɻ�
{

    Mission1.addLightPlane(3);
    glutTimerFunc(1000, tmrProduceLightPlanes, value);
}

static void tmrLaserAttack(int value) //���⹥����0.5��1��
{
    Mission1.LaserShoot();
    glutTimerFunc(500, tmrLaserAttack, value);
}
static void tmrEMPAttack(int value) //EMP������2��1��
{
    //Mission1.PrintPlanes();
    Mission1.EMPShoot();
    //Mission1.PrintPlanes();
    //Mission1.RemoveDeadPlanes();
    //Mission1.PrintPlanes();
    glutTimerFunc(2000, tmrEMPAttack, value);
}

/*const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };*/

/* Program entry point */

int main(int argc, char *argv[])
{
    //while(frameNum<=2400){
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Battle Field");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);

    glutIdleFunc(idle);

    glClearColor(0,0,0,1);
    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);*/
    glutTimerFunc(2000,tmrProduceHeavyPlanes,1);
    glutTimerFunc(1000,tmrProduceLightPlanes,2);
    glutTimerFunc(500,tmrLaserAttack,3);//0.5��1��
    glutTimerFunc(2000,tmrEMPAttack,4);//2��1��
    glutMainLoop();
    return EXIT_SUCCESS;
    //}
    //if (sign == 1)
        //printf("Planes Win!!!\n");
        //else printf("Emplacements Win!!!\n");
    //return 0;
}
