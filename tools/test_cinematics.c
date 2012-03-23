// gcc -I ../modules/math/geometry -I ../include test_cinematics.c ../modules/math/geometry/*.c -o test_cinematics -ldl -lglut -lGL -lGLU -lm -Llib -L/usr/X11R6/lib -lX11 -lXext -lXmu -lXi
#include <stdio.h>

#include <stdlib.h>
#include <circles.h>

#include <math.h>

#include <GL/glu.h>
#include <GL/freeglut.h>
#include <GL/gl.h>



#define DEG(a) ((a) * 180 / M_PI)

point_t p1, p2;
circle_t c1, c2;


void draw_circle(circle_t c) {
	int i;
	glPushMatrix();
	glTranslated(c.x, c.y, 0.);
	glScalef(c.r, c.r, 0.);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<50;i++) {
		float a = (i/50.) * 2 * M_PI;
		glVertex2f(cos(a), sin(a));
	}
	glEnd();
	glPopMatrix();
	
}

void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glOrtho(-300, 300, -300, 300, -1, 1);
	
	
	if(p1.x != p2.x && p1.y != p2.y) {
		glColor3f(0., 1., 0.);
		glBegin(GL_LINE_STRIP);
		glVertex2f(c1.x, c1.y);
		glVertex2f(p1.x, p1.y);
		glVertex2f(c2.x, c2.y);
		glEnd();
	}
	
	glColor3f(0., 0., 1.);
	glBegin(GL_LINE_STRIP);
	glVertex2f(c1.x, c1.y);
	glVertex2f(p2.x, p2.y);
	glVertex2f(c2.x, c2.y);
	glEnd();

	
	glColor3f(1., 1., 0.);
	draw_circle(c1);
	draw_circle(c2);
	
	glutSwapBuffers();
	glutPostRedisplay();
	
}


void main(int argc, char **argv) {

	
	
	if(argc != 3) {
		printf("usage : %s x y\n", argv[0]);
		return;
	}
	
	
	c1.x = 0;
	c1.y = 0;
	c1.r = 155.;
	
	c2.x = atof(argv[1]);
	c2.y = atof(argv[2]);
	c2.r = 75.;
	
	
	switch(circle_intersect(&c2, &c1, &p1, &p2)) {
		case 0:
			printf("Point unreachable\n");
			break;
			
		case 1:
			printf("Position du coude :(%f;%f)\n", p1.x, p1.y);
			printf("Longueur epaule : %f ? %f\n", sqrt(p1.x*p1.x+p1.y*p1.y), c1.r);
			break;
			
		case 2:
			printf("Position du coude :(%f;%f) ou (%f;%f)\n", p1.x, p1.y, p2.x, p2.y);
			printf("Longueur epaule : %f ? %f\n", sqrt(p2.x*p2.x+p2.y*p2.y), c1.r);
			printf("Longueur epaule : %f ? %f\n", sqrt(p2.x*p2.x+p2.y*p2.y), c1.r);
			printf("Alpha 1 : %d, Beta 1 %d\n", (int)DEG(atan2(p1.y, p1.x)), (int)DEG(atan2(c2.y-p1.y,c2.x-p1.x ))); 
			break;
		
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(600, 600);

	glutCreateWindow("Test Cinematique inverse");
	
	glutDisplayFunc(draw);
	
	glClearColor(0., 0., 0., 1.);
	
	
	glutMainLoop();
	

}
