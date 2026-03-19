#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0;

void spinDisplay(void)
{
	spin = spin + 2.0;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-25.0, -25.0);
	glVertex2f(25.0, -25.0);
	glVertex2f(25.0, 25.0);
	glVertex2f(-25.0, 25.0);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		glutIdleFunc(spinDisplay);
		break;
	case 'X':
		glutIdleFunc(NULL);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (state != GLUT_DOWN)
		return;

	if (button == GLUT_LEFT_BUTTON)
		glutIdleFunc(spinDisplay);
	else if (button == GLUT_RIGHT_BUTTON)
		glutIdleFunc(NULL);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(NULL);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
