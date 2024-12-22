#include <GL/glut.h>
#include <math.h>

float object = 10.0;
float PI = 3.146;
float rotation = 0.0;
float aspect;

struct Planet
{
	float radius;
	float jarak;
	float rotationAngle;
	float kecepatanRotasi;
	float color[3];
};

struct Planet merkurius = {0.5, 10.0, 0.0, 0.002, {0.6f, 0.6f, 0.6f}};
struct Planet venus = {0.8, 15.0, 0.0, 0.001, {0.8f, 0.6f, 0.2f}};
struct Planet bumi = {0.9, 25.0, 0.0, 0.0005, {0.2f, 0.6f, 1.0f}};
struct Planet mars = {0.47, 30.0, 0.0, 0.0004, {1.0f, 0.0f, 0.0f}};
struct Planet jupiter = {2.3, 40.0, 0.0, 0.0003, {1.0f, 1.0f, 0.0f}};
struct Planet saturnus = {2.1, 50.0, 0.0, 0.0002, {1.0f, 0.5f, 0.0f}};
struct Planet uranus = {1.3, 60.0, 0.0, 0.0001, {0.0f, 0.0f, 1.0f}};
struct Planet neptunus = {1.3, 70.0, 0.0, 0.00008, {0.0f, 0.0f, 1.0f}};
struct Planet bulan = {0.3, 2.0, 0.0, 0.001, {0.8f, 0.8f, 0.8f}};

struct Light
{
	GLfloat position[4];
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
};

struct Light light1 = {{10.0, 0.0, 0.0, 1.0}, {0.1, 0.1, 0.1, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}};
struct Light light2 = {{-10.0, 0.0, 0.0, 1.0}, {0.1, 0.1, 0.1, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}};
struct Light light3 = {{0.0, 0.0, 10.0, 1.0}, {0.1, 0.1, 0.1, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}};
struct Light light4 = {{0.0, 0.0, -10.0, 1.0}, {0.1, 0.1, 0.1, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}};

float xLookAt = -20.0;
float yLookAt = 30.0;
float zLookAt = 115.0;

void reshape(int w, int h)
{
	if (h == 0)
	{
		h = 1;
	}
	aspect = (float)w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 1.0, 300.0);
	gluLookAt(xLookAt, yLookAt, zLookAt, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// gluLookAt(-20.0, 60.0, 55.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// gluLookAt(-20.0, 20.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool showOrbit = true;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case 'Q':
		showOrbit = !showOrbit;
		break;
	case 'w':
	case 'W':
		exit(0);
		break;
	case '1':
		xLookAt = -20.0;
		yLookAt = 30.0;
		zLookAt = 115.0;
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case '2':
		xLookAt = -20.0;
		yLookAt = 30.0;
		zLookAt = 90.0;
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case '3':
		xLookAt = -10.0;
		yLookAt = 60.0;
		zLookAt = 70.0;
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case '4':
		xLookAt = -20.0;
		yLookAt = 10.0;
		zLookAt = 50.0;
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	}
}

void drawOrbit(float jarakPlanet)
{
	if (!showOrbit)
		return; // Jika orbit tidak ditampilkan, keluar dari fungsi
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	int numSegments = 100;
	for (int i = 0; i < numSegments; i++)
	{
		float angle = 2.0f * PI * float(i) / float(numSegments);
		float x = jarakPlanet * cos(angle);
		float z = jarakPlanet * sin(angle);
		glVertex3f(x, 0.0f, z);
	}
	glEnd();
	glPopMatrix();
}

void drawRing(float innerRadius, float outerRadius, int numOrbits)
{
	glPushMatrix();
	glColor3f(0.8f, 0.8f, 0.5f); // Warna cincin

	// Interval antar orbit
	float radiusStep = (outerRadius - innerRadius) / numOrbits;

	// Menggambar banyak orbit
	for (int orbit = 0; orbit < numOrbits; orbit++)
	{
		float currentRadius = innerRadius + orbit * radiusStep;
		glBegin(GL_LINE_LOOP);

		int numSegments = 100; // Jumlah segmen untuk membuat orbit halus
		for (int i = 0; i <= numSegments; i++)
		{
			float angle = 2.0f * PI * float(i) / float(numSegments);
			float x = currentRadius * cos(angle);
			float z = currentRadius * sin(angle);

			glVertex3f(x, 0.0f, z); // Titik pada orbit
		}

		glEnd();
	}

	glPopMatrix();
}

void createMatahari()
{
	glPushMatrix();
	glColor3ub(212, 246, 255);
	glRotatef(rotation += 0.01, 0, 1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glutSolidSphere(8.0, 30, 30);
	glPopMatrix();
}

void createPlanet(float rotationAnglePlanet, float jarakPlanet, float radiusPlanet, float color[3])
{
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAnglePlanet;
	float x = jarakPlanet * cos(angle);
	float z = jarakPlanet * sin(angle);

	glPushMatrix();
	glTranslatef(x, 0.0f, z);
	glColor3f(color[0], color[1], color[2]);
	glutSolidSphere(radiusPlanet, 30, 30);
	glPopMatrix();
}

void createBumi()
{
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + bumi.rotationAngle;
	float x = bumi.jarak * cos(angle);
	float z = bumi.jarak * sin(angle);

	glPushMatrix();
	glTranslatef(x, 0.0f, z);
	glColor3f(bumi.color[0], bumi.color[1], bumi.color[2]);
	glutSolidSphere(bumi.radius, 30, 30);
	drawOrbit(bulan.jarak);
	createPlanet(bulan.rotationAngle, bulan.jarak, bulan.radius, bulan.color);
	glPopMatrix();
}

void createSaturnus()
{
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + saturnus.rotationAngle;
	float x = saturnus.jarak * cos(angle);
	float z = saturnus.jarak * sin(angle);

	glPushMatrix();
	glTranslatef(x, 0.0f, z);
	glColor3f(saturnus.color[0], saturnus.color[1], saturnus.color[2]);
	glutSolidSphere(saturnus.radius, 30, 30);
	drawRing(3.0, 5.0, 100.0);
	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Atur posisi dan properti lampu
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	// Lampu 0
	glLightfv(GL_LIGHT0, GL_POSITION, light1.position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light1.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light1.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light1.specular);

	// Lampu 1
	glLightfv(GL_LIGHT1, GL_POSITION, light2.position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light2.ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light2.diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light2.specular);

	// Lampu 2
	glLightfv(GL_LIGHT2, GL_POSITION, light3.position);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light3.ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light3.diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light3.diffuse);

	// Lampu 3
	glLightfv(GL_LIGHT3, GL_POSITION, light4.position);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light4.ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light4.diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light4.specular);

	// Gambar Matahari
	createMatahari();

	// Orbit dan planet
	drawOrbit(merkurius.jarak);
	createPlanet(merkurius.rotationAngle, merkurius.jarak, merkurius.radius, merkurius.color);

	drawOrbit(venus.jarak);
	createPlanet(venus.rotationAngle, venus.jarak, venus.radius, venus.color);

	drawOrbit(bumi.jarak);
	createBumi();

	drawOrbit(mars.jarak);
	createPlanet(mars.rotationAngle, mars.jarak, mars.radius, mars.color);

	drawOrbit(jupiter.jarak);
	createPlanet(jupiter.rotationAngle, jupiter.jarak, jupiter.radius, jupiter.color);

	drawOrbit(saturnus.jarak);
	createSaturnus();

	drawOrbit(uranus.jarak);
	createPlanet(uranus.rotationAngle, uranus.jarak, uranus.radius, uranus.color);

	drawOrbit(neptunus.jarak);
	createPlanet(neptunus.rotationAngle, neptunus.jarak, neptunus.radius, neptunus.color);

	glutSwapBuffers();
	glutPostRedisplay();

	merkurius.rotationAngle += merkurius.kecepatanRotasi;
	venus.rotationAngle += venus.kecepatanRotasi;
	bumi.rotationAngle += bumi.kecepatanRotasi;
	mars.rotationAngle += mars.kecepatanRotasi;
	jupiter.rotationAngle += jupiter.kecepatanRotasi;
	saturnus.rotationAngle += saturnus.kecepatanRotasi;
	uranus.rotationAngle += uranus.kecepatanRotasi;
	neptunus.rotationAngle += neptunus.kecepatanRotasi;
}

void inisialisasi()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.1, 0.1, 0.1, 1.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("2306116 - Rifki Ramdani");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutFullScreen();
	inisialisasi();
	glutMainLoop();
	return 0;
}
