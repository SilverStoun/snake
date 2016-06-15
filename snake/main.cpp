#include <time.h>
#include <GL\glut.h>

int w = 640, h = 480;
int i = 0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_QUADS);
	glVertex2f(50 + i, 50);
	glVertex2f(100 + i, 50);
	glVertex2f(100 + i, 100);
	glVertex2f(50 + i, 100);
	glEnd();

	glFlush();
}

void timer(int = 0) {
	display();

	i++;

	glutTimerFunc(50, timer, 0);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutCreateWindow("Test");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glutDisplayFunc(display);
	glutTimerFunc(50, timer, 0);

	glutMainLoop();
}