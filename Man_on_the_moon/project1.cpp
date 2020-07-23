

#include<glut.h>

#include<stdio.h>
#include<math.h>
#include<string.h>
int state = 0;
int color;
char f[] = "Flag:";
char ind[] = "Press i for Indian flag";
char white[] = "Press c for cream color flag";
char p[] = "Plant:";
char flower[] = "Press p for plant";
char ent[] = "Press a key to start!";
char des[] = "This project simulates the lunar surface along with the robotic";
char des1[] = " technology that is used to explore the surface of the moon.";
char des2[] = "Choose an object that the robot has to hold.";
char title[] = "Man On The Moon";
float th = 0.0;
int count = 1;
void renderText(float x, float y, void* font, char* pstring)//to render text at specified position
{
	char* cptr;
	glRasterPos2i(x, y);
	for (cptr = pstring; *cptr != '\0'; cptr++)
	{
		glutBitmapCharacter(font, *cptr);
	}
}




typedef struct wcPt3D
{
    GLfloat x, y, z;
};
void bino(GLint n, GLint* C)
{
    GLint k, j;
    for (k = 0; k <= n; k++)
    {
        C[k] = 1;
        for (j = n; j >= k + 1; j--)
            C[k] *= j;
        for (j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}
void computeBezPt(GLfloat u, wcPt3D* bezPt, GLint nCtrlPts, wcPt3D* ctrlPts, GLint* C)
{
    GLint k, n = nCtrlPts - 1;
    GLfloat bezBlendFcn;
    bezPt->x = bezPt->y = bezPt->z = 0.0;
    for (k = 0; k < nCtrlPts; k++)
    {
        bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}
void bezier(wcPt3D* ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
    wcPt3D bezCurvePt;
    GLfloat u;
    GLint* C, k;
    C = new GLint[nCtrlPts];
    bino(nCtrlPts - 1, C);
    glBegin(GL_LINE_STRIP);
    for (k = 0; k <= nBezCurvePts; k++)
    {
        u = GLfloat(k) / GLfloat(nBezCurvePts);
        computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
        glVertex3f(bezCurvePt.x, bezCurvePt.y, -9);
    }
    glEnd();
    delete[]C;
}

void land()
{

    GLint nCtrlPts = 4, nBezCurvePts = 20;
    static float theta = 0;
    /* wcPt3D ctrlPts[4] = {
    {2, 0, 0},
     {3,2.1, 0},
     {5, 0.9, 0},
     {-9,-1, 0} };*/

    wcPt3D ctrlPts[4] = {
        {-9,-1, 0},
  {-6, 3, 0},
   {-5,-3, 0},
   {-1, 0.9, 0},
    };

    wcPt3D ctrlPts1[4] = { {-1.0, 0.9, 0},
    { 6,1.75,0 },
    { 6.2,-1.5,0 },
    { 11,4,0 } };

    theta += 0.1;
    // glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5);
    for (float i = 0; i < 14; i = i + 1.2)
    {


        glPushMatrix();
        glLineWidth(1000);

        // glColor3f(19 / 255.0, 136 / 255.0, 8 / 255.0); //Indian flag: green color code

        glColor3f(0.6, 0.3, 0.20);
        glTranslatef(-1.2, 0 - i, 0.0);
        bezier(ctrlPts, nCtrlPts, nBezCurvePts);
        bezier(ctrlPts1, nCtrlPts, nBezCurvePts);


        glPopMatrix();
    }

}

void* currentfont;
void drawstring(float x, float y, float z, char* string)
{
    char* c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++)
    {
        glColor3f(0.0, 1.0, 1.0);
        glutBitmapCharacter(currentfont, *c);
    }
}


void setFont(void* font)
{
    currentfont = font;
}


void outputText(GLfloat x, GLfloat y, char* text)
{
    glColor3f(1.0, 0.0, 0.0);
    // setFont(GLUT_BITMAP_HELVETICA_18);
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    drawstring(-7 + th, -3.75, 0, text);
}

void flag()
{
    if (color == 1 || color == 2)
    {


        if (count == 4000)
            glTranslatef(-6.0 + th, -12.2f, -7.0);
        else
            glTranslatef(-7.7 + th, -9.2f, -7.0);
        //glTranslatef(4.2, -5, 0);

        glColor3f(0.7, 0.5, 0.3);//pole

        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex3f(4, 8, 0);
        glVertex3f(4, 4, 0);
        glEnd();

        // glTranslatef(-6.7 + th, -9.2f, -7.0);
        if (color == 1)
            glColor3f(1.0, 0.5, 0.0);//orange
        else if (color == 2)
            glColor3f(0.9, 0.8, 0.7);
        glBegin(GL_QUADS);
        glVertex3f(5.5, 7.5, 0);
        glVertex3f(5.5, 8, 0);
        glVertex3f(4.01, 8, 0);
        glVertex3f(4.01, 7.5, 0);
        glEnd();

        if (color == 1)
            glColor3f(1.0, 1.0, 1.0);//white
        else if (color == 2)
            glColor3f(0.9, 0.8, 0.7);
        glBegin(GL_QUADS);
        glVertex3f(5.5, 7.5, 0);
        glVertex3f(5.5, 7, 0);
        glVertex3f(4.01, 7, 0);
        glVertex3f(4.01, 7.5, 0);
        glEnd();

        if (color == 1)
            glColor3f(0.0, 1.0, 0.0);//green
        else if (color == 2)
            glColor3f(0.9, 0.8, 0.7);
        glBegin(GL_QUADS);
        glVertex3f(5.5, 7, 0);
        glVertex3f(5.5, 6.5, 0);
        glVertex3f(4.01, 6.5, 0);
        glVertex3f(4.01, 7, 0);
        glEnd();

        GLUquadricObj* c = gluNewQuadric();
        if (color == 1)
            glColor3f(0.0, 0.0, 1.0);
        else if (color == 2)
            glColor3f(0.9, 0.8, 0.7);
        glTranslatef(4.71, 7.21, 0.0);
        gluSphere(c, 0.25, 10, 10);
    }
    else
    {
        if (count == 4000)
            glTranslatef(-6.0 + th, -12.2f, -7.0);
        else
            glTranslatef(-7.7 + th, -9.2f, -7.0);
        //glTranslatef(4.2, -5, 0);

        glColor3f(0.7, 0.5, 0.3);//pole

        glLineWidth(5);
        glBegin(GL_LINES);
        glVertex3f(4, 8, 0);
        glVertex3f(4, 4, 0);
        glEnd();


        glBegin(GL_TRIANGLES);
        glColor3f(0,0.3,0);
        glVertex3f(4,7, 0);
        glVertex3f(4,6.5, 0);
        glVertex3f(3,7.5, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0, 0.3, 0);
        glVertex3f(4, 6, 0);
        glVertex3f(4, 5.5, 0);
        glVertex3f(3, 6.5, 0);
        glEnd();
        
        glBegin(GL_TRIANGLES);
        glColor3f(0, 0.3, 0);
        glVertex3f(4, 6.5, 0);
        glVertex3f(4, 6, 0);
        glVertex3f(5, 7, 0);
        glEnd();

        glBegin(GL_TRIANGLES);
        glColor3f(0, 0.3, 0);
        glVertex3f(4, 5, 0);
        glVertex3f(4, 4.5, 0);
        glVertex3f(5, 5.5, 0);
        glEnd();

        

        GLUquadricObj* c1 = gluNewQuadric();       
       // glColor3f(1.0, 0.3, 0.0);   
        glColor3f(0.5,0.5,0.0);
        glTranslatef(4.0, 8.21, 0.0);
        gluSphere(c1, 0.25, 10, 10);

       // glColor3f(0.5, 0.5, 0.0);
        glColor3f(0.9,0.5,0.5);
        GLUquadricObj* p1 = gluNewQuadric();       
        glTranslatef(-0.4, 0.4, 0.0);
        gluSphere(p1, 0.3, 10, 10);

        GLUquadricObj* p2 = gluNewQuadric();       
        glTranslatef(0.5, 0.1, 0.0);
        gluSphere(p2, 0.3, 10, 10);
        
       GLUquadricObj* p3 = gluNewQuadric();      
        glTranslatef(0.45, -0.4, 0.0);
        gluSphere(p3, 0.3, 10, 10);

        GLUquadricObj* p4 = gluNewQuadric();        
        glTranslatef(-0.2, -0.55, 0.0);
        gluSphere(p4, 0.3, 10, 10);

        GLUquadricObj* p5 = gluNewQuadric();        
        glTranslatef(-0.6, -0.1, 0.0);
        gluSphere(p5, 0.3, 10, 10);

        GLUquadricObj* p6 = gluNewQuadric();       
        glTranslatef(-0.3, 0.4, 0.0);
        gluSphere(p6, 0.3, 10, 10);

    }

}
void stars()
{
    glPushMatrix();
    glTranslatef(-5.2, 7, 0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    glVertex3f(5, 1, 0);
    glVertex3f(6, 2, 0);
    glVertex3f(2, -1, 0);
    glVertex3f(8, 1, 0);
    glVertex3f(3, 1, 0);
    glVertex3f(9, -2, 0);

    glVertex3f(12, 0, 0);
    glVertex3f(13, 2, 0);
    glVertex3f(1, 0.25, 0);
    glVertex3f(-1, 1, 0);
    glVertex3f(3.5, -0.5, 0);
    glVertex3f(-4, 2, 0);

    glVertex3f(-3, 2, 0);
    glVertex3f(-2.5, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    glPopMatrix();

}

void spacecraft()
{


    glPushMatrix();
    glTranslatef(-3.2, 7, -8.1);
    glBegin(GL_POINTS);


    glBegin(GL_TRIANGLES);//left top
   glColor3f(0.3, 0.3, 1.0);   
    glVertex3f(-6, -5, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -5, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-5, -4, 0);
    glEnd();

    glBegin(GL_TRIANGLES);//top right
    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-4, -5, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-3, -5, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-4, -4, 0);
    glEnd();

    glBegin(GL_QUADS);//top square

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -4, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-4, -4, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-4, -5, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -5, 0);
    glEnd();

    glBegin(GL_QUADS);//square left
    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-6, -5, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-5, -5, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -6, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-6, -6, 0);
    glEnd();

    glBegin(GL_QUADS);//square middle
    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -5, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-4, -5, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-4, -6, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -6, 0);
    glEnd();

    glBegin(GL_QUADS);//square right
    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-4, -5, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-3, -5, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-3, -6, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-4, -6, 0);
    glEnd();

    glBegin(GL_QUADS);//square bottom
    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -6, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-4, -6, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-4, -7, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -7, 0);
    glEnd();

    glBegin(GL_TRIANGLES);//bottom left
    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-6, -6, 0);

    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-5, -6, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-5, -7, 0);
    glEnd();

    glBegin(GL_TRIANGLES);//bottom right
    glColor3f(0.3, 0.3, 1.0);
    glVertex3f(-4, -6, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-3, -6, 0);

    glColor3f(0.5, 0.5, 1.0);
    glVertex3f(-4, -7, 0);
    glEnd();

    glLineWidth(10);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-5, -7, 0);
    glVertex3f(-5.5, -7.5, 0);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-4, -7, 0);
    glVertex3f(-3.5, -7.5, 0);
    glEnd();
    glPopMatrix();




}

void initGL() {

    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 32);

    float dim[] = { 0.5F, 0.5F, 0.5F, 1 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dim);
    glLightfv(GL_LIGHT0, GL_SPECULAR, dim);

    float red[] = { 0.5F, 0, 0, 1 };
    float reda[] = { 0.1F, 0, 0, 1 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, reda);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT1, GL_SPECULAR, red);

    float gr[] = { 0, 0.5F, 0, 1 };
    float gra[] = { 0, 0.1F, 0, 1 };
    glLightfv(GL_LIGHT2, GL_AMBIENT, gra);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, gr);
    glLightfv(GL_LIGHT2, GL_SPECULAR, gr);

    float bl[] = { 0, 0, 0.5F, 1 };
    float bla[] = { 0, 0, 0.1F, 1 };
    glLightfv(GL_LIGHT3, GL_AMBIENT, bla);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, bl);
    glLightfv(GL_LIGHT3, GL_SPECULAR, bl);




}

float xth = 0;
float yth = 0;


float xtth = -0.2;
float ytth = -0.2;

void earth()
{
    glPushMatrix();
    GLUquadricObj* s = gluNewQuadric();
    GLfloat mat_specular[] = { 1.0, 0.5, 0.0 };
    GLfloat mat_diffuse[] = { 1.0, 0.5, 0.0 };
    GLfloat mat_ambient[] = { 1.0, 0.5, 0.0 };
    GLfloat mat_shininess = { 100.0 };
    GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glTranslatef(4.2, 7, 0);
    // glColor3f(1.0, 0.5, 0.0);//orange
    glColor3f(0.0, 0.5, 1.0);
    gluSphere(s, 1, 20, 10);

    glPopMatrix();
}
void torso()
{
    //gluLookAt(-5.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glTranslatef(-6.0 + th, -3.55f, -7.0);  // Move right and into the screen

    glBegin(GL_QUADS);

    glColor3f(0.40f, 0.40f, 0.40f);//grey front
    glVertex3f(-1.5 - xtth, 1.7 + ytth, 0);

    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(1.5 + xtth, 1.7 + ytth, 0);

    glColor3f(0.7, 0.7, 0.7);
    glVertex3f(1.5 + xtth, -1.7 - ytth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-1.5 - xtth, -1.7 - ytth, 0);


    glColor3f(0.40f, 0.4f, 0.40f);
    // glColor3f(0.60f, 1.6f, 0.60f);//light green back
    glVertex3f(-2.0 - xtth, 2.2 + ytth, -0.1);
    glVertex3f(0.5 + xtth, 2.2 + ytth, -0.1);
    glVertex3f(0.5 + xtth, -1.2 - ytth, -0.1);
    glVertex3f(-2.0 - xtth, -1.2 - ytth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    //glColor3f(0.0, 0.0, 1.0f);//blue left side
    glVertex3f(-2.0 - xtth, 2.2 + ytth, -0.1);
    glVertex3f(-1.5 - xtth, 1.7 + ytth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-1.5 - xtth, -1.7 - ytth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-2.0 - xtth, -1.2 - ytth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    // glColor3f(1.0, 0.0, 0.0f);//red right side
    glVertex3f(0.5 + xtth, 2.2 + ytth, -0.1);
    glVertex3f(1.5 + xtth, 1.7 + ytth, 0);
    glVertex3f(1.5 + xtth, -1.7 - ytth, 0);
    glVertex3f(0.5 + xtth, -1.2 - yth, -0.1);

    glEnd();
    glLoadIdentity();



}
float xhth = -0.5;
float yhth = -0.5;
void head()
{

    glPushMatrix();
    glShadeModel(GL_SMOOTH);
    GLUquadricObj* s = gluNewQuadric();

    //gluLookAt(-5.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glTranslatef(-6.0 + th, -0.55f, -7.0);  // Move right and into the screen

    glBegin(GL_QUADS);
    glColor3f(0.40f, 0.40f, 0.40f);//grey front	
    glVertex3f(-1.5 - xhth, 1.7 + yhth, 0);

    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(1.5 + xhth, 1.7 + yhth, 0);

    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(1.5 + xhth, -1.7 - yhth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-1.5 - xhth, -1.7 - yhth, 0);

    glColor3f(0.60f, 0.6f, 0.60f);
    //glColor3f(0.60f, 1.6f, 0.60f);//light green back
    glVertex3f(-2.0 - xhth, 2.2 + yhth, -0.1);
    glVertex3f(0.5 + xhth, 2.2 + yhth, -0.1);
    glVertex3f(0.5 + xhth, -1.2 - yhth, -0.1);
    glVertex3f(-2.0 - xhth, -1.2 - yhth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    // glColor3f(0.0, 0.0, 1.0f);//blue left side
    glVertex3f(-2.0 - xhth, 2.2 + yhth, -0.1);
    glVertex3f(-1.5 - xhth, 1.7 + yhth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-1.5 - xhth, -1.7 - yhth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-2.0 - xhth, -1.2 - yhth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    // glColor3f(1.0, 0.0, 0.0f);//red right side
    glVertex3f(0.5 + xhth, 2.2 + yhth, -0.1);
    glVertex3f(1.5 + xhth, 1.7 + yhth, 0);
    glVertex3f(1.5 + xhth, -1.7 - yhth, 0);
    glVertex3f(0.5 + xhth, -1.2 - yhth, -0.1);

    glEnd();
    glPopMatrix();
    glLoadIdentity();



}

void eye()
{
    glPushMatrix();

    GLUquadricObj* e1 = gluNewQuadric();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-5.5 + th, -0.21, 0.0);
    gluSphere(e1, 0.15, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-6.5 + th, -0.24, 0.0);
    gluSphere(e1, 0.15, 10, 10);
    glPopMatrix();
}
void mouth()
{
    glPushMatrix();
    // glTranslatef(-5.5 + th, -0.21, 0.0);



    glTranslatef(-10.5 + th, -9.2f, 7.0);
    //glTranslatef(4.2, -5, 0);
   // glColor3f(0.7, 0.5, 0.3);//pole
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.7, 0.1, 0.1);
    glVertex3f(4, 8, 0);
    glVertex3f(5, 8, 0);
    glEnd();


    glPopMatrix();
}
void leftleg()
{
    //gluLookAt(-5.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glTranslatef(-5.2 + th, -6.55f, -7.0);  // Move right and into the screen

    glBegin(GL_QUADS);
    glColor3f(0.40f, 0.4f, 0.40f);//grey front
    glVertex3f(-0.3 - xth, 1.5 + yth, 0);

    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(0.3 + xth, 1.5 + yth, 0);

    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(0.3 + xth, -1.7 - yth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-0.3 - xth, -1.7 - yth, 0);


    glColor3f(0.60f, 1.6f, 0.60f);//light green back
    glVertex3f(-0.6 - xth, 2.0 + yth, -0.1);
    glVertex3f(0 + xth, 2.0 + yth, -0.1);
    glVertex3f(0 + xth, -1.2 - yth, -0.1);
    glVertex3f(-0.6 - xth, -1.2 - yth, -0.1);

    glColor3f(0.40, 0.40, 0.4f);//blue left side
    glVertex3f(-0.3 - xth, 1.5 + yth, 0);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-0.6 - xth, 2.0 + yth, -0.1);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-0.6 - xth, -1.2 - yth, -0.1);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-0.3 - xth, -1.7 - yth, 0);


    glColor3f(1.0, 0.0, 0.0f);//red right side
    glVertex3f(0 + xth, 2.0 + yth, -0.1);
    glVertex3f(0.3 + xth, 1.5 + yth, 0);
    glVertex3f(0 + xth, -1.2 - yth, -0.1);
    glVertex3f(0.3 + xth, -1.7 - yth, 0);

    glEnd();
    glLoadIdentity();


}

void rightleg()
{
    //gluLookAt(-5.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glTranslatef(-6.5 + th, -6.55f, -7.0);  // Move right and into the screen

    glBegin(GL_QUADS);
    glColor3f(0.40f, 0.4f, 0.40f);//grey front
    glVertex3f(-0.3 - xth, 1.5 + yth, 0);

    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(0.3 + xth, 1.5 + yth, 0);

    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(0.3 + xth, -1.7 - yth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-0.3 - xth, -1.7 - yth, 0);


    glColor3f(0.60f, 1.6f, 0.60f);//light green back
    glVertex3f(-0.6 - xth, 2.0 + yth, -0.1);
    glVertex3f(0 + xth, 2.0 + yth, -0.1);
    glVertex3f(0 + xth, -1.2 - yth, -0.1);
    glVertex3f(-0.6 - xth, -1.2 - yth, -0.1);


    glColor3f(0.40f, 0.40f, 0.40f);//blue left side
    glVertex3f(-0.3 - xth, 1.5 + yth, 0);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-0.6 - xth, 2.0 + yth, -0.1);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-0.6 - xth, -1.2 - yth, -0.1);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-0.3 - xth, -1.7 - yth, 0);


    glColor3f(1.0, 0.0, 0.0f);//red right side
    glVertex3f(0 + xth, 2.0 + yth, -0.1);
    glVertex3f(0.3 + xth, 1.5 + yth, 0);
    glVertex3f(0 + xth, -1.2 - yth, -0.1);
    glVertex3f(0.3 + xth, -1.7 - yth, 0);

    glEnd();
    glLoadIdentity();


}
void righthand()
{
    glTranslatef(-8.0 + th, -3.55f, -7.0);  // Move right and into the screen
    glRotatef(-20, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);

    glColor3f(0.40f, 0.4f, 0.40f);//grey front
    glVertex3f(-0.3 - xth, 1.5 + yth, 0);

    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(0.3 + xth, 1.5 + yth, 0);

    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(0.3 + xth, -1.7 - yth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-0.3 - xth, -1.7 - yth, 0);


    glColor3f(0.60f, 0.6f, 0.60f);//light green back
    glVertex3f(-0.6 - xth, 2.0 + yth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    glVertex3f(0 + xth, 2.0 + yth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    glVertex3f(0 + xth, -1.2 - yth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    glVertex3f(-0.6 - xth, -1.2 - yth, -0.1);


    glColor3f(0.40f, 0.40f, 0.40f);//blue left side
    glVertex3f(-0.3 - xth, 1.5 + yth, 0);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-0.6 - xth, 2.0 + yth, -0.1);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-0.6 - xth, -1.2 - yth, -0.1);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-0.3 - xth, -1.7 - yth, 0);


    glColor3f(0.6, 0.6, 0.6f);//red right side
    glVertex3f(0 + xth, 2.0 + yth, -0.1);

    glColor3f(0.6, 0.6, 0.6f);
    glVertex3f(0.3 + xth, 1.5 + yth, 0);

    glColor3f(0.8, 0.8, 0.8f);
    glVertex3f(0 + xth, -1.2 - yth, -0.1);

    glColor3f(0.8, 0.8, 0.8f);
    glVertex3f(0.3 + xth, -1.7 - yth, 0);

    glEnd();
    glLoadIdentity();
}

void lefthand()
{
    glTranslatef(-4.0 + th, -3.2f, -7.0);  // Move right and into the screen
    glRotatef(25, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glColor3f(0.40f, 0.4f, 0.40f);//grey front
    glVertex3f(-0.3 - xth, 1.5 + yth, 0);

    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(0.3 + xth, 1.5 + yth, 0);

    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(0.3 + xth, -1.7 - yth, 0);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-0.3 - xth, -1.7 - yth, 0);


    glColor3f(0.60f, 0.6f, 0.60f);//light green back
    glVertex3f(-0.6 - xth, 2.0 + yth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    glVertex3f(0 + xth, 2.0 + yth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    glVertex3f(0 + xth, -1.2 - yth, -0.1);

    glColor3f(0.60f, 0.6f, 0.60f);
    glVertex3f(-0.6 - xth, -1.2 - yth, -0.1);


    glColor3f(0.40f, 0.40f, 0.40f);//blue left side
    glVertex3f(-0.3 - xth, 1.5 + yth, 0);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-0.6 - xth, 2.0 + yth, -0.1);

    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-0.6 - xth, -1.2 - yth, -0.1);

    glColor3f(0.40f, 0.40f, 0.40f);
    glVertex3f(-0.3 - xth, -1.7 - yth, 0);


    glColor3f(0.6, 0.6, 0.6f);//red right side
    glVertex3f(0 + xth, 2.0 + yth, -0.1);

    glColor3f(0.6, 0.6, 0.6f);
    glVertex3f(0.3 + xth, 1.5 + yth, 0);

    glColor3f(0.8, 0.8, 0.8f);
    glVertex3f(0 + xth, -1.2 - yth, -0.1);

    glColor3f(0.8, 0.8, 0.8f);
    glVertex3f(0.3 + xth, -1.7 - yth, 0);

    glEnd();
    glLoadIdentity();
}

void display()
{
	
	if (state == 1)
	{
       
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            if (count < 4000)
            {
                th = th + 0.002;
                count++;
            }
            else
                th = th;

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            glOrtho(-10, 10, -10, 10, -10, 10);
            // glRotatef(31, 0, 1, 0);

            glMatrixMode(GL_MODELVIEW);

            char a[] = "INDIA";
            char* str = a;
            outputText(-9.7, -3.4, str);
            land();
            earth();
            stars();
            spacecraft();

            head();
            eye();
            mouth();
            torso();
            leftleg();
            rightleg();
            lefthand();
            righthand();
            flag();



            glutPostRedisplay();
            glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
            glFlush();
        
	}
	else
	{

      //  glClearColor(0.0, 0.0, 0.0, 1.0);
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(-10, 10, -10, 10, -10, 10);
        // glRotatef(31, 0, 1, 0);

        glMatrixMode(GL_MODELVIEW);        
        
        glColor3f(0.0, 0.0, 1.0);
        renderText(-4.7, 9.4, GLUT_BITMAP_TIMES_ROMAN_24, title);

        glColor3f(1, 0.44, 0.33);
        renderText(-10, 7.4, GLUT_BITMAP_TIMES_ROMAN_24, des);
        renderText(-10, 6.4, GLUT_BITMAP_TIMES_ROMAN_24, des1);
        renderText(-7, 4.4, GLUT_BITMAP_TIMES_ROMAN_24, des2);

        glColor3f(0.0, 0.0,1.0);
        renderText(-9.7, 2.4, GLUT_BITMAP_TIMES_ROMAN_24, f);

        glColor3f(0.0,0.5,0.0);
        renderText(-6.7, 1.4, GLUT_BITMAP_TIMES_ROMAN_24, ind);
        renderText(-6.7, 0.4, GLUT_BITMAP_TIMES_ROMAN_24, white);

        glColor3f(0.0, 0.0, 1.0);
        renderText(-9.7, -2.4, GLUT_BITMAP_TIMES_ROMAN_24, p);

        glColor3f(0.0, 0.5, 0.0);
        renderText(-6.7, -3.4, GLUT_BITMAP_TIMES_ROMAN_24, flower);

        glColor3f(1,0.24,0.58);
        renderText(-6.7, -6.4, GLUT_BITMAP_TIMES_ROMAN_24, ent);
	}
	glFlush();
}



void myKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'i':
    case 'I'://Ascii of 'enter' key is 13
	{
		state = 1;
        color = 1;
		break;
	}
    case 'c':
    case 'C':
    {
        state = 1;
        color = 2;
        break;
    }
    case 'p':
    case 'P':
    {
        state = 1;
        color = 3;
        break;
    }
	}
}



void timercb(int val)
{
	glutPostRedisplay();
	glutTimerFunc(100000 / 30, timercb, 0);
}

void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GLUT_SINGLE | GLUT_RGB);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	

    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50);
	glutCreateWindow("Man on the Moon");
	printf("Name:Namitha S\nUSN:1BG17CS055\nProject Name:MAN ON THE MOON");
	
	glutTimerFunc(0, timercb, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboardFunc);
	
	myinit();
   // glEnable(GL_DEPTH_TEST);
    //  glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();
	glutMainLoop();
	return 0;
}
