#include <time.h>
#include <stdlib.h>
#include <GL\glut.h>
#include <windows.h>


int N = 30, M = 20;
int Scale = 25;

int w = Scale * N;
int h = Scale * M;

int dir, num = 4;

struct {
	int x;
	int y; } s[100];

	class Fructs {
	public:
		int x, y;

		void New() {
			x = rand() % N;
			y = rand() % M;
		}

		void DrawApple() {
			glColor3f(0.0, 0.0, 0.0);
			glRectf(x * Scale, y * Scale, (x + 1) * Scale, (y + 1) * Scale);
		}
	} m[10];

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

	for (int i = 0; i < 10; i++)
	{
		if ((s[0].x == m[i].x) && (s[0].y == m[i].y))
		{
			num++;
			m[i].New();
		}
	}

	if (s[0].x >= N) dir = 1; 
	if (s[0].x <= 0) dir = 2;
	if (s[0].y >= M) dir = 3;
	if (s[0].y <= 0) dir = 0;

	for (int i = 1; i < num; i++)
	{
		if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;
	}
}

void DrawSnake() {
	glColor3f(0.0, 0.0, 0.0);
	for (int i = 0; i < num; i++)
	{
		glRectf(s[i].x * Scale + 2, s[i].y * Scale + 2, (s[i].x + 0.9) * Scale, (s[i].y + 0.9) * Scale);
	}
}

void MyKeyboard(int key, int a, int b) {
	switch (key) {
	case 101: if (dir == 3) { break; } dir = 0; break;
	case 102: if (dir == 1) { break; } dir = 2; break;
	case 100: if (dir == 2) { break; } dir = 1; break;
	case 103: if (dir == 0) { break; } dir = 3; break;
	}
}

void DrawPoint() {

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 10; i++)
		m[i].DrawApple();

	DrawField();
	DrawSnake();
	DrawPoint();

	glFlush();
}

void timer(int = 0) {
	display();

	if (num < 99) { 
		Tick();
	}
	else {

		s[0].x = 10;
		s[0].y = 0;
		num = 4;

		for (int i = 0; i < 4; i++)
		{
			s[i].x = 15;
			s[i].y = 10;
			
		}

	};

	glutTimerFunc(250 - num * 5, timer, 0);
}

int main(int argc, char **argv) {

	for (int i = 0; i < 10; i++)
		m[i].New();

	for (int i = 0; i < 4; i++)
	{
		s[i].x = 15;
		s[i].y = 10;
	}

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
	glutSpecialFunc(MyKeyboard);

	glutMainLoop();
}