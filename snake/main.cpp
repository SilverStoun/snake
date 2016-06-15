#include <time.h>
#include <GL\glut.h>

int N = 30, M = 20;
int Scale = 25;

int w = Scale * N;
int h = Scale * M;

void DrawField() {
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);

	for (int i = 0; i < w; i+= Scale)
	{
		glVertex2f(i, 0);
		glVertex2f(i, h);
	}
	for (int j = 0; j < h; j+= Scale)
	{
		glVertex2f(0, j);
		glVertex2f(w, j);
	}

	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	DrawField();

	glFlush();
}

void timer(int = 0) {
	display();


	glutTimerFunc(50, timer, 0);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutCreateWindow("Snake");
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glutDisplayFunc(display);
	glutTimerFunc(50, timer, 0);

	glutMainLoop();
}