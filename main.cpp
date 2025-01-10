#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <stdio.h>
#include <math.h>

float object = 10.0;
float PI = 3.146;
float scaleMatahari = 1.0f;
const float MAX_SCALE_MATAHARI = 1.1f;
const float MIN_SCALE_MATAHARI = 0.5f;
float rotationAngleMatahari = 0.0;
float aspect;

GLuint texture_Matahari_ID;
GLuint texture_Merkurius_ID;
GLuint texture_Venus_ID;
GLuint texture_Bumi_ID;
GLuint texture_Mars_ID;
GLuint texture_Jupiter_ID;
GLuint texture_Saturnus_ID;
GLuint texture_Uranus_ID;
GLuint texture_Neptunus_ID;
GLuint texture_Bulan_ID;

struct Planet
{
	float radius;
	float jarak;
	float revolusiAngle;
	float rotationAngle;
	float kecepatanRevolusi;
	float kecepatanRotasi;
};

struct Planet merkurius = {0.5, 10.0, 0.0, 0.0, 0.002, 0.307};
struct Planet venus = {0.8, 15.0, 0.0, 0.0, 0.001, 0.55};
struct Planet bumi = {0.9, 25.0, 0.0, 0.0, 0.0005, 1.8};
struct Planet mars = {0.47, 30.0, 0.0, 0.0, 0.0004, 1.74755};
struct Planet jupiter = {2.3, 40.0, 0.0, 0.0, 0.0003, 4.39025};
struct Planet saturnus = {2.1, 50.0, 0.0, 0.0, 0.0002, 4.0};
struct Planet uranus = {1.3, 60.0, 0.0, 0.0, 0.0001, 2.5};
struct Planet neptunus = {1.3, 70.0, 0.0, 0.0, 0.00008, 2.68655};
struct Planet bulan = {0.3, 2.0, 0.0, 0.0, 0.001, 0.0659};

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
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool hiddenCartecius = true;

void drawCartecius()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);

	// Sumbu X
	glVertex3f(-200.0, 0.0, 0.0);
	glVertex3f(200.0, 0.0, 0.0);

	// Sumbu Y
	glVertex3f(0.0, -200.0, 0.0);
	glVertex3f(0.0, 200.0, 0.0);

	// Sumbu Z
	glVertex3f(0.0, 0.0, -200.0);
	glVertex3f(0.0, 0.0, 200.0);
	glEnd();
}

bool showOrbit = true;

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e':
	case 'E':
		showOrbit = !showOrbit;
		break;
	case 'r':
	case 'R':
		hiddenCartecius = !hiddenCartecius;
		break;
	case 'w':
	case 'W':
		exit(0);
		break;
	case 't':
		scaleMatahari += 0.1f;
		if (scaleMatahari > MAX_SCALE_MATAHARI) 
			scaleMatahari = MAX_SCALE_MATAHARI;		
		break;
	case 'y':
		scaleMatahari -= 0.1f;
		if (scaleMatahari < MIN_SCALE_MATAHARI)
			scaleMatahari = MIN_SCALE_MATAHARI; 
		break;
	case '1':
		xLookAt = -20.0;
		yLookAt = 30.0;
		zLookAt = 115.0;
		reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
	case '2':
		xLookAt = -20.0;
		yLookAt = 10.0;
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

GLuint loadTexture(const char *path)
{
	FIBITMAP *bitmap = FreeImage_Load(FIF_JPEG, path);
	if (!bitmap)
	{
		printf("Failed to load image %s\n", path);
		return 0;
	}

	FIBITMAP *bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	FreeImage_Unload(bitmap);

	BYTE *imgData = FreeImage_GetBits(bitmap32);
	int imgWidth = FreeImage_GetWidth(bitmap32);
	int imgHeight = FreeImage_GetHeight(bitmap32);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, imgData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FreeImage_Unload(bitmap32);
	return textureID;
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

void createPlanet(struct Planet *planet, GLuint textureID)
{
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + planet->revolusiAngle;
	float x = planet->jarak * cos(angle);
	float z = planet->jarak * sin(angle);

	glPushMatrix();
	glTranslatef(x, 0.0f, z);
	glRotatef(planet->rotationAngle += planet->kecepatanRotasi, 0, 1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);

	// Aktifkan tekstur
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Gambar bola dengan tekstur
	GLUquadric *object = gluNewQuadric();
	gluQuadricTexture(object, GL_TRUE);
	gluSphere(object, planet->radius, 30, 30);
	gluDeleteQuadric(object); // Hapus quadric setelah digunakan

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void createMatahari()
{
	glPushMatrix();
	glColor3ub(212, 246, 255);
	glRotatef(rotationAngleMatahari += 0.01, 0, 1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);

	glScalef(scaleMatahari, scaleMatahari, scaleMatahari);

	// Aktifkan tekstur
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_Matahari_ID);

	// Gambar bola dengan tekstur
	GLUquadric *object = gluNewQuadric();
	gluQuadricTexture(object, GL_TRUE);
	gluSphere(object, 8.0, 30, 30);
	gluDeleteQuadric(object); // Hapus quadric setelah digunakan

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void createBumi()
{
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + bumi.revolusiAngle;
	float x = bumi.jarak * cos(angle);
	float z = bumi.jarak * sin(angle);

	glPushMatrix();
	glTranslatef(x, 0.0f, z);

	glPushMatrix();
	glRotatef(bumi.rotationAngle += bumi.kecepatanRotasi, 0, 1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);

	// Aktifkan tekstur
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_Bumi_ID);

	// Gambar bola dengan tekstur
	GLUquadric *object = gluNewQuadric();
	gluQuadricTexture(object, GL_TRUE);
	gluSphere(object, bumi.radius, 30, 30);
	gluDeleteQuadric(object); // Hapus quadric setelah digunakan

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	drawOrbit(bulan.jarak);

	float moonAngle = bulan.revolusiAngle * (PI / 180.0f);
	float moonX = bulan.jarak * cos(moonAngle);
	float moonZ = bulan.jarak * sin(moonAngle);

	// Gambar bulan
	glPushMatrix();
	glTranslatef(moonX, 0.0f, moonZ);
	glColor3f(1.0f, 1.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_Bulan_ID);

	// Gambar bola dengan tekstur
	GLUquadric *objectBulan = gluNewQuadric();
	gluQuadricTexture(objectBulan, GL_TRUE);
	gluSphere(objectBulan, bulan.radius, 30, 30);
	gluDeleteQuadric(objectBulan); // Hapus quadric setelah digunakan

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPopMatrix();

	// Perbarui sudut rotasi bulan
	bulan.revolusiAngle += bulan.kecepatanRevolusi * 360.0f;
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

void createSaturnus()
{
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + saturnus.revolusiAngle;
	float x = saturnus.jarak * cos(angle);
	float z = saturnus.jarak * sin(angle);

	glPushMatrix();
	glTranslatef(x, 0.0f, z);

	glPushMatrix();
	glRotatef(saturnus.rotationAngle += saturnus.kecepatanRotasi, 0, 1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);

	// Aktifkan tekstur
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_Saturnus_ID);

	// Gambar bola dengan tekstur
	GLUquadric *object = gluNewQuadric();
	gluQuadricTexture(object, GL_TRUE);
	gluSphere(object, saturnus.radius, 30, 30);
	gluDeleteQuadric(object); // Hapus quadric setelah digunakan

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

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
	glPushMatrix();
	createMatahari();

	// Orbit dan planet
	drawOrbit(merkurius.jarak);
	createPlanet(&merkurius, texture_Merkurius_ID);

	drawOrbit(venus.jarak);
	createPlanet(&venus, texture_Venus_ID);

	drawOrbit(bumi.jarak);
	createBumi();

	drawOrbit(mars.jarak);
	createPlanet(&mars, texture_Mars_ID);

	drawOrbit(jupiter.jarak);
	createPlanet(&jupiter, texture_Jupiter_ID);

	drawOrbit(saturnus.jarak);
	createSaturnus();

	drawOrbit(uranus.jarak);
	createPlanet(&uranus, texture_Uranus_ID);

	drawOrbit(neptunus.jarak);
	createPlanet(&neptunus, texture_Neptunus_ID);
	glPopMatrix();

	if (hiddenCartecius)
	{
		drawCartecius();
	}

	glutSwapBuffers();
	glutPostRedisplay();

	merkurius.revolusiAngle += merkurius.kecepatanRevolusi;
	venus.revolusiAngle += venus.kecepatanRevolusi;
	bumi.revolusiAngle += bumi.kecepatanRevolusi;
	mars.revolusiAngle += mars.kecepatanRevolusi;
	jupiter.revolusiAngle += jupiter.kecepatanRevolusi;
	saturnus.revolusiAngle += saturnus.kecepatanRevolusi;
	uranus.revolusiAngle += uranus.kecepatanRevolusi;
	neptunus.revolusiAngle += neptunus.kecepatanRevolusi;
}

void inisialisasi()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.1, 0.1, 0.1, 1.0);

	// Muat tekstur matahari dan planet
	texture_Matahari_ID = loadTexture("texture/matahari.jpg");
	texture_Merkurius_ID = loadTexture("texture/merkurius.jpg");
	texture_Venus_ID = loadTexture("texture/venus.jpg");
	texture_Bumi_ID = loadTexture("texture/bumi.jpg");
	texture_Mars_ID = loadTexture("texture/mars.jpg");
	texture_Jupiter_ID = loadTexture("texture/jupiter.jpg");
	texture_Saturnus_ID = loadTexture("texture/saturnus.jpg");
	texture_Uranus_ID = loadTexture("texture/uranus.jpg");
	texture_Neptunus_ID = loadTexture("texture/neptunus.jpg");
	texture_Bulan_ID = loadTexture("texture/bulan.jpg");
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
