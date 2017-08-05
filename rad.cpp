#include "base.hpp"

using namespace std;

GLuint starList;

static double G = (1 + sqrt(5)) / 2;

#define E 2.71828182845904523536



void drawLump(double xp, double yp, double r, int lumps, int depth, int n, Color* a, Color* change){

    Color* newColor = colorSub(a, change);

//    newColor->set();

    double x, y, rr;
    int rah =((depth%2)?E:G)*r; double rt = r+rah;
    double xt=rt, yt=0;

    double z=0, zi = rads/n;

    rt /= 2;  n/=2; 
    if (--depth == -1) return;
    drawLump(xp, yp, rt/PI, lumps,depth,n,newColor,change);
    int i; for(i=0;i<lumps;i++){
	double tht = rads*i/lumps;// + PI/lumps;
	drawLump(xp+rt*cos(tht), yp+rt*sin(tht), rt/PI, lumps,depth,n,newColor,change);
    }
    rt*=2; n*=2;

    a->set();

    glPushMatrix();

    glTranslatef(rt+xp,yp,0);

     while(z<rads){
	glCallList(starList);
	rr=r+rah*cos(lumps*z); //sharpness*cos(lumps*z)

	x = -xt;
	xt = rr*cos(z);
	x += xt;

	y = -yt;
	yt = rr*sin(z);
	y += yt;

	z += zi;

	glTranslatef(x,y,0);
    }

    glPopMatrix();

}

void drawLumpO(double xp, double yp, double r, int lumps, int depth, int n, Color* a, Color* b){
    Color* change = colorDiv(colorSub(a,b),depth);
    change->print();
    drawLump(xp,yp,r ,lumps,depth,n,a,change);
}

double xv = 100, sv=0;

void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    //double xp, double yp, double r, int lumps, int depth, int dots
    drawLumpO(0,0,30,4,5,4200*3,black,orange);

    // Flush created objects to the screen, i.e., force rendering.
    glFlush(); 
}

// Initialization routine.
void setup(void) 
{
    // Set background (or clearing) color.
    glClearColor(1.0, 1.0, 1.0, 0.0); 

    glClear(GL_COLOR_BUFFER_BIT);
    glClearDepth(1.0);

    glDepthFunc(GL_LEQUAL);

    glewInit(); //Don't forget this guy

    starList = glGenLists(1);

    glNewList(starList, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    double r = .3;
    double xf, yf;
    xf = yf = r*cos(PI/4);

    glVertex3f(0,r,0);
    glVertex3f(xf,-yf,0);
    glVertex3f(-xf,-yf,0);

    glVertex3f(xf,yf,0);
    glVertex3f(-xf,yf,0);
    glVertex3f(0,-r,0);
    glEnd();

    glEndList();
}


// OpenGL window reshape routine.
void resize(int w, int h)
{
    // Set viewport size to be entire OpenGL window.
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  
    // Set matrix mode to projection.
    glMatrixMode(GL_PROJECTION);

    // Clear current projection matrix to identity.
    glLoadIdentity();

    // define the viewing box.
    glOrtho(xv+sv, -xv+sv, -xv, xv, -1, 1);

    // Set matrix mode to modelview.
    glMatrixMode(GL_MODELVIEW);

    // Clear current modelview matrix to identity.
    glLoadIdentity();
}


// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key) 
    {
        // Press escape to exit.

     case 'i':
	 xv/=2; resize(900,900); drawScene();
         break;
     case 'o':
	 xv*=2; resize(900,900); drawScene();
         break;
     case 27:
         exit(0);
         break;
//newline    case 13:
     default:
         break;
    }
}


// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) 
{  

    // Initialize GLUT.
    glutInit(&argc, argv);
 
    // Set display mode as single-buffered and RGB color.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
   
    // Set OpenGL window size.
    glutInitWindowSize(900, 900);

    // Set position of OpenGL window upper-left corner.
    glutInitWindowPosition(100, 100); 
   
    // Create OpenGL window with title.
    glutCreateWindow("Display List Cube");
   
    // Initialize.
    setup(); 
   
    // Register display routine.
    glutDisplayFunc(drawScene); 
   
    // Register reshape routine.
    glutReshapeFunc(resize);  

    // Register keyboard routine.
    glutKeyboardFunc(keyInput);

    // Begin processing.
    glutMainLoop(); 

    return 0;  
}
