#include <iostream>
#include <stdio.h>

#include <math.h>
#include <vector>
#include <string.h>
#include <time.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

string str(char* c){return string(c, strlen(c));}

struct ColorFactory {

};

struct Color {
    double r, g, b;

    Color(Color& c):
	r(c.r), g(c.g), b(c.b){};

    Color(double rr, double gg, double bb) :
	r(rr), g(gg), b(bb){};

    Color(int rr, int gg, int bb) :
	r(rr/255.0), g(gg/255.0), b(bb/255.0) {}
    
    void set() {glColor3f(r, g, b);}

    void setBackground() {glClearColor(r,g,b,0);}

    void print() {printf("%f %f %f\n",r,g,b);}
};

Color* colorDiv(Color* a, int x){
    return new Color(a->r/x,a->g/x,a->b/x);
}

Color* colorSub(Color* a, Color* c){
    return new Color(a->r-c->r,a->g-c->g,a->b-c->b);
}

Color* colorAdd(Color* a, Color* c){
    return new Color(a->r+c->r,a->g+c->g,a->b+c->b);
}

Color* orange = new Color(255, 153, 0);
Color* red_orange = new Color(255,100,20);
Color* white = new Color(255, 255, 255);
Color* black = new Color(0,0,0);
Color* blue = new Color(0,0,255);
Color* red = new Color(255,0,0);
Color* green = new Color(0,255,0);
Color* grey = new Color(127,127,127);
Color* yellow = new Color(255,255,0);

#define PI 3.14159265359

static const double rads = 2*PI;

#define SPKS 60 //spokes
#define DGR 360/SPKS //degrees per spoke

const int len = SPKS*2;
double wheel[len];

void populate(){
    int i, j; double ii = rads/SPKS;
for (i=j=0; i<SPKS; i++){
    double z = PI/2 - i*ii;
    wheel[j++]=cos(z);
    wheel[j++]=sin(z);
}}

double px(int index){return wheel[index%len];}

void drawCircle(int x, int y, int r, int b=0, int e=SPKS+1, Color* c=black, Color* m=white){
    glBegin(GL_TRIANGLE_FAN);
    m->set();
    glVertex3f(x, y, 0);
    c->set();
    if (b>e) e+=SPKS;

    int i;
    for(i=2*b; b<=e; b++, i=(i+2)%len){
	glVertex3f(x+r*wheel[i], y+r*wheel[i+1], 0);
    }

    glEnd();
}

void drawRect(int x, int y, int w, int h, Color* ca=black, Color* cb=white)
{
    glBegin(GL_TRIANGLE_STRIP);
    ca->set();
    glVertex3f(x,y,0);
    glVertex3f(x,y+h,0);
    cb->set();
    glVertex3f(x+w,y+h,0);
    glVertex3f(x+w,y,0);

    ca->set();
    glVertex3f(x,y,0);
    glEnd();
}
