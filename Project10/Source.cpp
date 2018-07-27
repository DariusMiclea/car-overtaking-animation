#include<windows.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>

using namespace std;

static GLdouble v_masina1 = 3.0, v_masina2 = 4.0, stop = 200, constanta = -203, x_masina2 = 0.0, i1 = 0.0, i2 = 0.0, y = 0.0, *adresa_y = &y;
static float angle = 0, angle2 = 0;

int initial_time = time(NULL), final_time, frame_count = 0, fps, contor = 7;
bool depasire1 = false, depasire2 = false, play, reset;

const double TWO_PI = 6.2831853;
GLuint regHex, regHex2;

class scrPt
{
public:
	GLint x, y;
};

void init(void)
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 10000; k++)
	{
		hexTheta = TWO_PI * k / 10000;
		hexVertex.x = 755 + 6 * cos(hexTheta);
		hexVertex.y = 20 + 6 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();

	regHex2 = glGenLists(2);
	glNewList(regHex, GL_COMPILE);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 10000; k++)
	{
		hexTheta = TWO_PI * k / 10000;
		hexVertex.x = 755 + 4 * cos(hexTheta);
		hexVertex.y = 20 + 4 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
	}
	glEnd();
	glEndList();
}

void butoane()
{
	glColor3f(0.0, 0.0, 0.0);  //negru
	glRecti(740, 10, 770, 30);//buton1

	glColor3f(0.0, 0.0, 0.0);  //negru
	glRecti(700, 10, 730, 30);//buton2

	glColor3f(0.0, 0.0, 0.0);  //negru
	glRecti(660, 10, 690, 30);//buton3

	glColor3f(1, 1, 1);//play
	glBegin(GL_POLYGON);
	glVertex2i(667, 28);
	glVertex2i(667, 12);
	glVertex2i(683, 20);
	glEnd();

	glColor3f(1, 1, 1); //pause
	glRecti(707, 13, 711, 27);
	glRecti(717, 13, 721, 27);

	glCallList(regHex); //replay
	glCallList(regHex2);
	glRecti(755, 20, 770, 25);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2i(756, 19);
	glVertex2i(764, 19);
	glVertex2i(760, 23);
	glEnd();
}

void background()
{
	glColor3f(0.133, 0.545, 0.133); //iarba
	glRecti(-30, 0, 470, 140);
	glRecti(620, 0, 800, 140);
	glRecti(-30, 260, 470, 700);
	glRecti(530, 260, 800, 700);

	//glRasterPos2f(0, 280);
	///*Acesta este jocul meu*/

	glColor3f(0.412, 0.412, 0.412); //soseaua-gri
	glRecti(-30, 180, 800, 260);
	glRecti(510, 0, 590, 700);

	glColor3f(0.184, 0.310, 0.310); //trotuarul
	glRecti(-30, 140, 510, 180);
	glRecti(470, 0, 510, 180);
	glRecti(590, 0, 630, 180);
	glRecti(590, 140, 800, 180);
	glRecti(-30, 260, 510, 300);
	glRecti(470, 260, 510, 700);
	glRecti(590, 260, 800, 300);
	glRecti(590, 260, 630, 700);

	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES); //contur sosea
	glLineWidth(10);
	glColor3f(0, 0, 0);
	glVertex2i(-30, 180);
	glVertex2i(510, 180);
	glVertex2i(590, 180);
	glVertex2i(800, 180);
	glVertex2i(-30, 260);
	glVertex2i(510, 260);
	glVertex2i(590, 260);
	glVertex2i(800, 260);
	glVertex2i(510, 0);
	glVertex2i(510, 180);
	glVertex2i(510, 260);
	glVertex2i(510, 800);
	glVertex2i(590, 0);
	glVertex2i(590, 180);
	glVertex2i(590, 260);
	glVertex2i(590, 800);
	glVertex2i(-30, 140);
	glVertex2i(470, 140);
	glVertex2i(470, 0);
	glVertex2i(470, 140);
	glVertex2i(-30, 300);
	glVertex2i(470, 300);
	glVertex2i(470, 300);
	glVertex2i(470, 700);
	glVertex2i(630, 0);
	glVertex2i(630, 140);
	glVertex2i(630, 140);
	glVertex2i(800, 140);
	glVertex2i(630, 300);
	glVertex2i(800, 300);
	glVertex2i(630, 300);
	glVertex2i(630, 700);
	glEnd();
	glDisable(GL_LINE_SMOOTH);

	glBegin(GL_LINES); //delimitarea benzilor
	glColor3f(0, 0, 0);
	glVertex2i(-30, 180);
	glVertex2i(510, 180);
	glVertex2i(-30, 260);
	glVertex2i(510, 260);
	glVertex2i(590, 260);
	glVertex2i(800, 260);
	glVertex2i(590, 180);
	glVertex2i(800, 180);
	glVertex2i(510, 700); //sus stanga
	glVertex2i(510, 260);
	glVertex2i(590, 700); //sus dreapta
	glVertex2i(590, 260);
	glVertex2i(510, 180); //jos stanga
	glVertex2i(510, 0);
	glVertex2i(590, 180); //jos dreapta
	glVertex2i(590, 0);
	glEnd();

	glEnable(GL_LINE_STIPPLE);//liniile punctate
	glLineStipple(13, 0xAAAA);
	glBegin(GL_LINES);
	glVertex2i(-30, 220);
	glVertex2i(780, 220);
	glVertex2i(550, 700);
	glVertex2i(550, 0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glEnable(GL_LINE_STIPPLE);//liniile punctate
	glLineStipple(3, 0xAAAA);
	glBegin(GL_LINES);
	glVertex2i(430, 180);
	glVertex2i(430, 220);
	glVertex2i(550, 103);
	glVertex2i(590, 103);
	glVertex2i(670, 220);
	glVertex2i(670, 260);
	glVertex2i(510, 340);
	glVertex2i(550, 340);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glBegin(GL_LINES); //trotuar -linii
	glColor3f(0, 0, 0);
	glVertex2i(-10, 140);
	glVertex2i(-10, 180);
	glVertex2i(20, 140);
	glVertex2i(20, 180);
	glVertex2i(50, 140);
	glVertex2i(50, 180);
	glVertex2i(80, 140);
	glVertex2i(80, 180);
	glVertex2i(110, 140);
	glVertex2i(110, 180);
	glVertex2i(140, 140);
	glVertex2i(140, 180);
	glVertex2i(170, 140);
	glVertex2i(170, 180);
	glVertex2i(200, 140);
	glVertex2i(200, 180);
	glVertex2i(230, 140);
	glVertex2i(230, 180);
	glVertex2i(260, 140);
	glVertex2i(260, 180);
	glVertex2i(290, 140);
	glVertex2i(290, 180);
	glVertex2i(320, 140);
	glVertex2i(320, 180);
	glVertex2i(350, 140);
	glVertex2i(350, 180);
	glVertex2i(380, 140);
	glVertex2i(380, 180);
	glVertex2i(410, 140);
	glVertex2i(410, 180);
	glVertex2i(440, 140);
	glVertex2i(440, 180);
	glVertex2i(470, 140);
	glVertex2i(470, 180);
	glVertex2i(510, 140);
	glVertex2i(470, 140);
	glVertex2i(510, 110);
	glVertex2i(470, 110);
	glVertex2i(510, 80);
	glVertex2i(470, 80);
	glVertex2i(510, 50);
	glVertex2i(470, 50);
	glVertex2i(510, 20);
	glVertex2i(470, 20);
	glVertex2i(590, 140);
	glVertex2i(630, 140);
	glVertex2i(590, 110);
	glVertex2i(630, 110);
	glVertex2i(590, 80);
	glVertex2i(630, 80);
	glVertex2i(590, 50);
	glVertex2i(630, 50);
	glVertex2i(590, 20);
	glVertex2i(630, 20);
	glVertex2i(630, 140);
	glVertex2i(630, 180);
	glVertex2i(660, 140);
	glVertex2i(660, 180);
	glVertex2i(690, 140);
	glVertex2i(690, 180);
	glVertex2i(720, 140);
	glVertex2i(720, 180);
	glVertex2i(750, 140);
	glVertex2i(750, 180);
	glVertex2i(-10, 260);
	glVertex2i(-10, 300);
	glVertex2i(20, 260);
	glVertex2i(20, 300);
	glVertex2i(50, 260);
	glVertex2i(50, 300);
	glVertex2i(80, 260);
	glVertex2i(80, 300);
	glVertex2i(110, 260);
	glVertex2i(110, 300);
	glVertex2i(140, 260);
	glVertex2i(140, 300);
	glVertex2i(170, 260);
	glVertex2i(170, 300);
	glVertex2i(200, 260);
	glVertex2i(200, 300);
	glVertex2i(230, 260);
	glVertex2i(230, 300);
	glVertex2i(260, 260);
	glVertex2i(260, 300);
	glVertex2i(290, 260);
	glVertex2i(290, 300);
	glVertex2i(320, 260);
	glVertex2i(320, 300);
	glVertex2i(350, 260);
	glVertex2i(350, 300);
	glVertex2i(380, 260);
	glVertex2i(380, 300);
	glVertex2i(410, 260);
	glVertex2i(410, 300);
	glVertex2i(440, 260);
	glVertex2i(440, 300);
	glVertex2i(470, 260);
	glVertex2i(470, 300);
	glVertex2i(470, 300);
	glVertex2i(510, 300);
	glVertex2i(470, 330);
	glVertex2i(510, 330);
	glVertex2i(470, 360);
	glVertex2i(510, 360);
	glVertex2i(470, 390);
	glVertex2i(510, 390);
	glVertex2i(470, 420);
	glVertex2i(510, 420);
	glVertex2i(470, 450);
	glVertex2i(510, 450);
	glVertex2i(470, 480);
	glVertex2i(510, 480);
	glVertex2i(470, 500);
	glVertex2i(510, 500);
	glVertex2i(470, 530);
	glVertex2i(510, 530);
	glVertex2i(470, 560);
	glVertex2i(510, 560);
	glVertex2i(470, 590);
	glVertex2i(510, 590);
	glVertex2i(590, 300);
	glVertex2i(630, 300);
	glVertex2i(590, 330);
	glVertex2i(630, 330);
	glVertex2i(590, 360);
	glVertex2i(630, 360);
	glVertex2i(590, 390);
	glVertex2i(630, 390);
	glVertex2i(590, 420);
	glVertex2i(630, 420);
	glVertex2i(590, 450);
	glVertex2i(630, 450);
	glVertex2i(590, 480);
	glVertex2i(630, 480);
	glVertex2i(590, 500);
	glVertex2i(630, 500);
	glVertex2i(590, 530);
	glVertex2i(630, 530);
	glVertex2i(590, 560);
	glVertex2i(630, 560);
	glVertex2i(590, 590);
	glVertex2i(630, 590);
	glVertex2i(630, 260);
	glVertex2i(630, 300);
	glVertex2i(660, 260);
	glVertex2i(660, 300);
	glVertex2i(690, 260);
	glVertex2i(690, 300);
	glVertex2i(720, 260);
	glVertex2i(720, 300);
	glVertex2i(750, 260);
	glVertex2i(750, 300);
	glEnd();

	glColor3f(1.0, 1.0, 1.0); //treceri de pietoni
	glRecti(435, 183, 500, 188);
	glRecti(435, 193, 500, 198);
	glRecti(435, 203, 500, 208);
	glRecti(435, 213, 500, 218);
	glRecti(435, 223, 500, 228);
	glRecti(435, 233, 500, 238);
	glRecti(435, 243, 500, 248);
	glRecti(435, 253, 500, 258);
	glRecti(600, 183, 665, 188);
	glRecti(600, 193, 665, 198);
	glRecti(600, 203, 665, 208);
	glRecti(600, 213, 665, 218);
	glRecti(600, 223, 665, 228);
	glRecti(600, 233, 665, 238);
	glRecti(600, 243, 665, 248);
	glRecti(600, 253, 665, 258);
	glRecti(513, 270, 518, 335);
	glRecti(523, 270, 528, 335);
	glRecti(533, 270, 538, 335);
	glRecti(543, 270, 548, 335);
	glRecti(553, 270, 558, 335);
	glRecti(563, 270, 568, 335);
	glRecti(573, 270, 578, 335);
	glRecti(583, 270, 588, 335);
	glRecti(513, 108, 518, 173);
	glRecti(523, 108, 528, 173);
	glRecti(533, 108, 538, 173);
	glRecti(543, 108, 548, 173);
	glRecti(553, 108, 558, 173);
	glRecti(563, 108, 568, 173);
	glRecti(573, 108, 578, 173);
	glRecti(583, 108, 588, 173);
}

void pietoni()
{
	glPushMatrix();
	if (!reset)
		glTranslated(i1 / 5, 0.0, 0.0);
	glColor3f(0, 0, 1); //om
	glRecti(130, 280, 140, 290);
	glColor3f(1, 0, 0);
	glRecti(130, 290, 140, 306);
	glColor3f(0.804, 0.522, 0.247);
	glRecti(133, 306, 140, 314);
	glColor3f(0, 0, 0);
	glPointSize(2.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(138, 312);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glRecti(130, 314, 140, 316);
	glRecti(130, 306, 133, 316);
	glColor3f(0.502, 0.000, 0.000);
	glRecti(132, 292, 136, 303);
	glPopMatrix();

	glPushMatrix();
	if (!reset)
		glTranslated(i1 / 2, 0.0, 0.0);//om
	glColor3f(0.294, 0.000, 0.510); //pantaloni
	glRecti(430, 290, 440, 300);
	glColor3f(1.000, 0.000, 1.000); //bluza
	glRecti(430, 300, 440, 316);
	glColor3f(0.804, 0.522, 0.247); //fata
	glRecti(433, 316, 440, 324);
	glColor3f(0, 0, 0);
	glPointSize(2.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(438, 322); //ochi
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glRecti(430, 324, 440, 326);//par sus
	glRecti(430, 316, 433, 326);//par jos
	glColor3f(0, 0, 0);
	glRecti(432, 302, 436, 313); //maneca
	glPopMatrix();

	glPushMatrix();
	if (!reset)
		glTranslated(-i1 / 3, 0.0, 0.0);//om
	glColor3f(0.000, 0.000, 0.545); //pantaloni
	glRecti(650, 150, 660, 160);
	glColor3f(0.941, 0.902, 0.540); //bluza
	glRecti(650, 160, 660, 176);
	glColor3f(0.804, 0.522, 0.247); //fata
	glRecti(650, 176, 657, 184);
	glColor3f(0, 0, 0);
	glPointSize(2.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(652, 182); //ochi
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glRecti(650, 184, 660, 186);//par sus
	glRecti(657, 176, 660, 186);//par jos
	glColor3f(0.741, 0.718, 0.420);
	glRecti(654, 162, 658, 173); //maneca
	glPopMatrix();

	glPushMatrix();
	if (!reset)
		glTranslated(i1 / 4, 0.0, 0.0);
	glColor3f(0, 0, 1); //om
	glRecti(60, 140, 70, 150);
	glColor3f(0.255, 0.412, 0.882);
	glRecti(60, 150, 70, 166);
	glColor3f(0.804, 0.522, 0.247);
	glRecti(63, 166, 70, 173);
	glColor3f(0, 0, 0);
	glPointSize(2.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(67, 171);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glRecti(60, 165, 63, 173);
	glRecti(60, 173, 70, 175);
	glColor3f(0.000, 0.000, 0.502);
	glRecti(62, 152, 66, 163);
	glPopMatrix();
}

void semafoare()
{
	glBegin(GL_LINES); //semafoare
	glColor3f(0, 0, 0);
	glVertex2i(450, 150);
	glVertex2i(450, 170);
	glVertex2i(500, 150);
	glVertex2i(500, 170);
	glVertex2i(450, 150);
	glVertex2i(500, 150);
	glVertex2i(450, 170);
	glVertex2i(500, 170);
	glVertex2i(450, 160);
	glVertex2i(430, 160);
	glVertex2i(600, 270);
	glVertex2i(600, 290);
	glVertex2i(650, 270);
	glVertex2i(650, 290);
	glVertex2i(600, 270);
	glVertex2i(650, 270);
	glVertex2i(600, 290);
	glVertex2i(650, 290);
	glVertex2i(650, 280);
	glVertex2i(670, 280);
	glVertex2i(600, 170);
	glVertex2i(620, 170);
	glVertex2i(600, 120);
	glVertex2i(620, 120);
	glVertex2i(600, 170);
	glVertex2i(600, 120);
	glVertex2i(620, 170);
	glVertex2i(620, 120);
	glVertex2i(610, 120);
	glVertex2i(610, 100);
	glVertex2i(480, 270);
	glVertex2i(480, 320);
	glVertex2i(500, 270);
	glVertex2i(500, 320);
	glVertex2i(480, 270);
	glVertex2i(500, 270);
	glVertex2i(480, 320);
	glVertex2i(500, 320);
	glVertex2i(490, 320);
	glVertex2i(490, 340);
	glEnd();

	glColor3f(0.753, 0.753, 0.753); //interiorul semafoarelor
	glRecti(450, 150, 500, 170);
	glRecti(600, 270, 650, 290);
	glRecti(600, 170, 620, 120);
	glRecti(480, 270, 500, 320);

	glColor3f(0.0, 1.0, 0.0); //verde
	glPointSize(10.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(460, 160);
	glVertex2i(640, 280);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glColor3f(1.0, 0.0, 0.0); //rosu
	glPointSize(10.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(610, 160);
	glVertex2i(490, 280);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glColor3f(0.0, 0.0, 0.0); //negru
	glPointSize(10.0);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glVertex2i(475, 160);
	glVertex2i(490, 160);
	glVertex2i(625, 280);
	glVertex2i(610, 280);
	glVertex2i(610, 130);
	glVertex2i(610, 145);
	glVertex2i(490, 295);
	glVertex2i(490, 310);
	glEnd();
	glDisable(GL_POINT_SMOOTH);

	if (i1 > 600)
	{
		glColor3f(0.0, 1.0, 0.0); //verde
		glPointSize(10.0);
		glEnable(GL_POINT_SMOOTH);
		glBegin(GL_POINTS);
		glVertex2i(490, 310);
		glVertex2i(610, 130);
		glEnd();
		glDisable(GL_POINT_SMOOTH);

		glColor3f(1.0, 0.0, 0.0); //rosu
		glPointSize(10.0);
		glEnable(GL_POINT_SMOOTH);
		glBegin(GL_POINTS);
		glVertex2i(490, 160);
		glVertex2i(610, 280);
		glEnd();
		glDisable(GL_POINT_SMOOTH);

		glColor3f(0.0, 0.0, 0.0); //negru
		glPointSize(10.0);
		glEnable(GL_POINT_SMOOTH);
		glBegin(GL_POINTS);
		glVertex2i(460, 160);
		glVertex2i(640, 280);
		glVertex2i(610, 160);
		glVertex2i(490, 280);
		glEnd();
		glDisable(GL_POINT_SMOOTH);
	}
	glPushMatrix();
}

void masini()
{
	if (depasire1)
	{
		v_masina1 = 1;
		v_masina2 = 3;
	}
	if (!reset)
		glTranslated(i1, 0.0, 0.0); //translatare dreptunghi albastru
	glColor3f(0.0, 0.0, 1.0); //albastru
	glRecti(60, 190, 100, 210); //dreptunghiul albastru
	glBegin(GL_POLYGON);
	glVertex2i(100, 190);
	glVertex2i(105, 193);
	glVertex2i(105, 207);
	glVertex2i(100, 210);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(60, 190);
	glVertex2i(55, 193);
	glVertex2i(55, 207);
	glVertex2i(60, 210);
	glEnd();
	glColor3f(1.000, 1.000, 0.878);
	glRecti(85, 195, 90, 205);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glLineWidth(10);
	glVertex2i(85, 189);
	glVertex2i(95, 189);
	glVertex2i(85, 211);
	glVertex2i(95, 211);
	glVertex2i(60, 189);
	glVertex2i(70, 189);
	glVertex2i(60, 211);
	glVertex2i(70, 211);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (!reset)
		glTranslated(-i2, 0, 0);
	glColor3f(1.0, 1.0, 0.0); //galben
	glRecti(700, 230, 740, 250); //dreptunghiul galben

	glBegin(GL_POLYGON);
	glVertex2i(700, 250);
	glVertex2i(695, 247);
	glVertex2i(695, 233);
	glVertex2i(700, 230);
	glBegin(GL_POLYGON);
	glVertex2i(740, 250);
	glVertex2i(745, 247);
	glVertex2i(745, 233);
	glVertex2i(740, 230);
	glEnd();
	glColor3f(1.000, 1.000, 0.878);
	glRecti(705, 235, 710, 245);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glLineWidth(10);
	glVertex2i(700, 228);
	glVertex2i(710, 228);
	glVertex2i(700, 252);
	glVertex2i(710, 252);
	glVertex2i(725, 228);
	glVertex2i(735, 228);
	glVertex2i(725, 252);
	glVertex2i(735, 252);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (!reset)
	{
		if (stop >= 0)
		{
			glTranslated(0.0, -i1, 0.0); //translatare dreptunghi verde
			stop = stop - 1;
		}
		else
			glTranslated(0.0, -203, 0.0);
		if (i1 > 600)
		{
			glTranslated(0, constanta + 203, 0);
			constanta = constanta - 1;
		}
	}
	glColor3f(0.0, 1.0, 0.0); //verde
	glRecti(520, 560, 540, 600); //dreptunghiul verde
	glBegin(GL_POLYGON);
	glVertex2i(540, 600);
	glVertex2i(537, 605);
	glVertex2i(523, 605);
	glVertex2i(520, 600);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(540, 560);
	glVertex2i(537, 555);
	glVertex2i(523, 555);
	glVertex2i(520, 560);
	glEnd();
	glColor3f(1.000, 1.000, 0.878);
	glRecti(525, 570, 535, 575);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glLineWidth(10);
	glVertex2i(519, 565);
	glVertex2i(519, 575);
	glVertex2i(541, 565);
	glVertex2i(541, 575);
	glVertex2i(519, 590);
	glVertex2i(519, 600);
	glVertex2i(541, 590);
	glVertex2i(541, 600);
	glEnd();
	glPopMatrix();
}

void depasire()
{
	glPushMatrix();
	if (!reset)
	{
		glTranslated(i2, 0.0, 0.0);
		if (i2 > (i1 + 80) - 80 && y <= 30 && !depasire2)
		{

			glTranslated(-i2, 0.0, 0.0);
			glRotated(angle, 0.0, 0.0, 1.0);
			glTranslated(i2, y, 0.0);

			if (angle <= 10)
				angle = angle + 0.15;
			if (contor % 7 == 0) //semnalizare
			{
				glColor3f(1.0, 1.0, 0.0); //galben
				glPointSize(7.0);
				glEnable(GL_POINT_SMOOTH);
				glBegin(GL_POINTS);
				glVertex2i(-20, 210);
				glVertex2i(20, 210);
				glEnd();
				glDisable(GL_POINT_SMOOTH);
			}
			contor++;
			y = y + 1;
			depasire1 = true;
			angle2 = angle;
		}
		else if (y >= 30 && depasire1 && angle2 > 0)
		{
			glTranslated(-i2, 0.0, 0.0);
			glRotated(angle2, 0.0, 0.0, 1.0);
			glTranslated(i2, y, 0.0);
			if (y < 35)
				y++;
			angle2 = angle2 - 0.2;
			angle = angle2;
			depasire2 = true;
		}
		else if (angle2 <= 0 && depasire1 && y > 18 && depasire2)
		{
			glTranslated(-i2, 0.0, 0.0);
			glRotated(angle, 0.0, 0.0, 1.0);
			glTranslated(i2, y, 0.0);
			if (contor % 5 == 0) //semnalizare
			{
				glColor3f(1.0, 1.0, 0.0); //galben
				glPointSize(7.0);
				glEnable(GL_POINT_SMOOTH);
				glBegin(GL_POINTS);
				glVertex2i(-20, 190);
				glVertex2i(20, 190);
				glEnd();
				glDisable(GL_POINT_SMOOTH);
			}
			contor++;
			y--;
			if (angle >= -10)
				angle = angle - 0.15;
			angle2 = angle;
		}
		else
		{
			glTranslated(-i2, 0.0, 0.0);
			glRotated(angle2, 0.0, 0.0, 1.0);
			glTranslated(i2, y, 0.0);
			if (y > 0)
				y = y - 1;
			if (angle2 < 0)
				angle2 = angle2 + 0.15;
		}
	}
	glColor3f(1.0, 0.0, 0.0);  //rosu
	glRecti(-20, 190, 20, 210); //dreptunghiul rosu
	glBegin(GL_POLYGON);
	glVertex2i(20, 190);
	glVertex2i(25, 193);
	glVertex2i(25, 207);
	glVertex2i(20, 210);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(-20, 190);
	glVertex2i(-25, 193);
	glVertex2i(-25, 207);
	glVertex2i(-20, 210);
	glEnd();
	glColor3f(1.000, 1.000, 0.878);
	glRecti(5, 195, 10, 205);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glLineWidth(10);
	glVertex2i(5, 189);
	glVertex2i(15, 189);
	glVertex2i(5, 211);
	glVertex2i(15, 211);
	glVertex2i(-10, 189);
	glVertex2i(-20, 189);
	glVertex2i(-10, 211);
	glVertex2i(-20, 211);
	glEnd();
	glPopMatrix();
}

void framerate()
{
	frame_count++;
	final_time = time(NULL);
	if (final_time - initial_time > 0)
	{
		cout << "FPS: " << frame_count / (final_time - initial_time) << endl;
		frame_count = 0;
		initial_time = final_time;

	}
}

void text()
{
	glRasterPos2i(0, 570);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glRasterPos2i(12, 570);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glRasterPos2i(17, 570);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glRasterPos2i(27, 570);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glRasterPos2i(37, 570);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glRasterPos2i(47, 570);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
	glRasterPos2i(57, 570);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glRasterPos2i(67, 570);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Q');

	glRasterPos2i(0, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'P');
	glRasterPos2i(12, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glRasterPos2i(20, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'u');
	glRasterPos2i(30, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
	glRasterPos2i(38, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glRasterPos2i(47, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glRasterPos2i(57, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
	glRasterPos2i(67, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glRasterPos2i(77, 550);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');

	glRasterPos2i(0, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glRasterPos2i(12, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glRasterPos2i(20, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
	glRasterPos2i(30, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
	glRasterPos2i(34, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glRasterPos2i(43, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'y');
	glRasterPos2i(53, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glRasterPos2i(63, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '-');
	glRasterPos2i(73, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glRasterPos2i(83, 530);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	background();
	pietoni();
	semafoare();
	masini();
	depasire();
	butoane();
	framerate();
	text();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle(int)
{
	i1 = i1 + v_masina1;
	i2 = i2 + v_masina2;
	glutPostRedisplay();
	if (play)
		glutTimerFunc(1000 / fps, idle, 0);
}
void reinit()
{
	
	v_masina1 = 3.0;
	v_masina2 = 4.0;
	x_masina2 = 0.0;
	i1 = 0.0;
	i2 = 0.0;
	*adresa_y = 0.0;
	depasire1 = false;
	depasire2 = false;
	angle = 0;
	angle2 = 0;
	contor = 7;
	constanta = -203;
	stop = 200;

}
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q': //play
		glutTimerFunc(1000 / fps, idle, 0);
		play = true;
		reset = false;
		break;

	case 'w': //pause
		play = false;
		reset = false;
		break;

	case 'e': //replay
		play = false;
		reset = true;
		reinit();
		glutTimerFunc(1000 / fps, idle, 0);
		break;

	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN && x >= glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) * 15 / 100
			&& x <= glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) *11.3 / 100
			&& y >= glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) * 5 / 100
			&& y <= glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) *1.5 / 100) ///pozitiile butonului de play relativ la dimensiunea ferestrei
		{
			glutTimerFunc(1000 / fps, idle, 0);
			play = true;
			reset = false;
		}
		if (state == GLUT_DOWN && x >= glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) * 10 / 100
			&& x <= glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) *6.3 / 100
			&& y >= glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) * 5 / 100
			&& y <= glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) *1.5 / 100)
		{
			play = false;
			reset = false;
		}
		if (state == GLUT_DOWN && x >= glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) * 5 / 100
			&& x <= glutGet(GLUT_WINDOW_WIDTH) - glutGet(GLUT_WINDOW_WIDTH) *1.4 / 100
			&& y >= glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) * 5 / 100
			&& y <= glutGet(GLUT_WINDOW_HEIGHT) - glutGet(GLUT_WINDOW_HEIGHT) *1.5 / 100)
		{
			play = false;
			reset = true;
			reinit();
		}
		break;
	default:
		break;
	}
}

void main(int argc, char** argv)
{
	cout << "FPS: "; cin >> fps;
	play = false;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 0);
	glutCreateWindow("Depasire auto");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	
	glutMainLoop();
}