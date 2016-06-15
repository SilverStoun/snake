#include <time.h>
#include <GL\glut.h>

int N = 30, M = 20;
int Scale = 25;

int w = Scale * N;
int h = Scale * M;

int dir, num = 4;

struct {
	int x;
	int y; } s[100];

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

void Tick() {
	for (int i = num; i > 0; --i)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (dir == 0) s[0].y += 1;
	if (dir == 1) s[0].x -= 1;
	if (dir == 2) s[0].x += 1;
	if (dir == 3) s[0].y -= 1;
}

void DrawSnake() {
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < num; i++)
	{
		glRectf(s[i].x * Scale + 2, s[i].y * Scale + 2, (s[i].x + 1) * Scale, (s[i].y + 1) * Scale);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	DrawField();
	DrawSnake();

	glFlush();
}

void timer(int = 0) {
	display();

	Tick();

	glutTimerFunc(250, timer, 0);
}

int main(int argc, char **argv) {

	s[0].x = 10;
	s[0].y = 0;

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