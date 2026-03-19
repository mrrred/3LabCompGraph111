#include <GL/glut.h>
#include <stdlib.h>

static GLfloat spin = 0.0;
static GLfloat smallSquareX = -50.0f;
static GLfloat smallSquareY = -50.0f;
static const GLfloat smallSquareSize = 5.0f;
static int windowWidth = 250;
static int windowHeight = 250;
static bool isDragging = false;
static GLfloat dragOffsetX = 0.0f;
static GLfloat dragOffsetY = 0.0f;

void screenToWorld(int x, int y, GLfloat& worldX, GLfloat& worldY)
{
	worldX = -50.0f + 100.0f * (GLfloat)x / (GLfloat)windowWidth;
	worldY = 50.0f - 100.0f * (GLfloat)y / (GLfloat)windowHeight;
}

bool isInsideSmallSquare(GLfloat x, GLfloat y)
{
	return x >= smallSquareX && x <= (smallSquareX + smallSquareSize) &&
		y >= smallSquareY && y <= (smallSquareY + smallSquareSize);
}

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

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(smallSquareX, smallSquareY);
	glVertex2f(smallSquareX + smallSquareSize, smallSquareY);
	glVertex2f(smallSquareX + smallSquareSize, smallSquareY + smallSquareSize);
	glVertex2f(smallSquareX, smallSquareY + smallSquareSize);
	glEnd();

	glutSwapBuffers();
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void reshape(int w, int h)
{
   windowWidth = (w > 0) ? w : 1;
	windowHeight = (h > 0) ? h : 1;
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
 if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			GLfloat worldX, worldY;
			screenToWorld(x, y, worldX, worldY);
			if (isInsideSmallSquare(worldX, worldY))
			{
				isDragging = true;
				dragOffsetX = worldX - smallSquareX;
				dragOffsetY = worldY - smallSquareY;
				glutIdleFunc(NULL);
			}
			else
			{
				glutIdleFunc(spinDisplay);
			}
		}
		else if (state == GLUT_UP)
		{
			isDragging = false;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		glutIdleFunc(NULL);
	}
}

void motion(int x, int y)
{
	if (!isDragging)
		return;

	GLfloat worldX, worldY;
	screenToWorld(x, y, worldX, worldY);

	smallSquareX = worldX - dragOffsetX;
	smallSquareY = worldY - dragOffsetY;

	if (smallSquareX < -50.0f)
		smallSquareX = -50.0f;
	if (smallSquareY < -50.0f)
		smallSquareY = -50.0f;
	if (smallSquareX > 45.0f)
		smallSquareX = 45.0f;
	if (smallSquareY > 45.0f)
		smallSquareY = 45.0f;

	glutPostRedisplay();
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
 glutMotionFunc(motion);
	glutIdleFunc(NULL);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}
