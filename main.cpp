#include <GL/glut.h>
#include <math.h>

float object = 10.0;
float PI = 3.146;
float rotation = 0.0;
float aspect;

// Radius tiap planet
float radiusMatahari = 8.0;	 // Ukuran Matahari
float radiusMerkurius = 0.5; // Ukuran Merkurius
float radiusVenus = 0.8;		 // Ukuran Venus
float radiusBumi = 0.9;			 // Ukuran Bumi
float radiusMars = 0.47;		 // Ukuran Mars
float radiusJupiter = 2.3;	 // Ukuran Jupiter
float radiusSaturnus = 2.1;	 // Ukuran Saturnus
float radiusUranus = 1.3;		 // Ukuran Uranus
float radiusNeptunus = 1.3;	 // Ukuran Neptunus

// Jarak tiap planet dari matahari
float jarakPlanetMerkurius = 10.0;
float jarakPlanetVenus = 15.0;
float jarakPlanetBumi = 25.0;
float jarakPlanetMars = 30.0;
float jarakPlanetJupiter = 40.0;
float jarakPlanetSaturnus = 50.0;
float jarakPlanetUranus = 60.0;
float jarakPlanetNeptunus = 70.0;

float rotationAngleMerkurius = 0.0;
float rotationAngleVenus = 0.0;
float rotationAngleBumi = 0.0;
float rotationAngleMars = 0.0;
float rotationAngleJupiter = 0.0;
float rotationAngleSaturnus = 0.0;
float rotationAngleUranus = 0.0;
float rotationAngleNeptunus = 0.0;

float kecepatanRotasiMerkurius = 0.002;
float kecepatanRotasiVenus = 0.001;
float kecepatanRotasiBumi = 0.0005;
float kecepatanRotasiMars = 0.0004;
float kecepatanRotasiJupiter = 0.0003;
float kecepatanRotasiSaturnus = 0.0002;
float kecepatanRotasiUranus = 0.0001;
float kecepatanRotasiNeptunus = 0.00008;

float mercuryColor[3] = {0.6f, 0.6f, 0.6f}; 
float venusColor[3] = {0.8f, 0.6f, 0.2f}; 
float earthColor[3] = {0.2f, 0.6f, 1.0f}; 
float marsColor[3] = {1.0f, 0.0f, 0.0f}; 
float jupiterColor[3] = {1.0f, 1.0f, 0.0f}; 
float saturnColor[3] = {1.0f, 0.5f, 0.0f}; 
float uranusColor[3] = {0.0f, 0.0f, 1.0f}; 
float neptuneColor[3] = {0.0f, 0.0f, 1.0f}; 

// GLfloat light_position[] = {0.0, 150.0, 0.0, 1.0};
GLfloat light_position1[] = {10.0, 0.0, 0.0, 1.0};
GLfloat light_position2[] = {-10.0, 0.0, 0.0, 1.0};
GLfloat light_position3[] = {0.0, 0.0, 10.0, 1.0};
GLfloat light_position4[] = {10.0, 0.0, -10.0, 1.0};

GLfloat light_ambient1[] = {0.1, 0.1, 0.1, 1.0};
GLfloat light_diffuse1[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular1[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light_ambient2[] = {0.1, 0.1, 0.1, 1.0};
GLfloat light_diffuse2[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular2[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light_ambient3[] = {0.1, 0.1, 0.1, 1.0};
GLfloat light_diffuse3[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular3[] = {1.0, 1.0, 1.0, 1.0};

GLfloat light_ambient4[] = {0.1, 0.1, 0.1, 1.0};
GLfloat light_diffuse4[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_specular4[] = {1.0, 1.0, 1.0, 1.0};

float xLookAt = -20.0;
float yLookAt = 30.0;
float zLookAt = 100.0;

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
	gluPerspective(45.0, aspect, 1.0, 300.0); // Slightly reduce far plane for better zooming
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
		//		case '1':
		//            float xLookAt = -20.0;
		//			float yLookAt = 60.0;
		//			float zLookAt = 100.0;
		//			glutPostRedisplay();
		//			break;
		//		case '2':
		//            float xLookAt = -20.0;
		//			float yLookAt = 60.0;
		//			float zLookAt = 50.0;
		//			glutPostRedisplay();
		//			break;
		//		case '3':
		//            float xLookAt = -20.0;
		//			float yLookAt = 20.0;
		//			float zLookAt = 50.0;
		//			glutPostRedisplay();
		//			break;
	}
}

void drawOrbit(float jarakPlanet)
{
	if (!showOrbit)
		return; // Jika orbit tidak ditampilkan, keluar dari fungsi
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f); // Warna putih untuk lintasan orbit
	glBegin(GL_LINE_LOOP);
	int numSegments = 100; // Jumlah segmen untuk membentuk lingkaran
	for (int i = 0; i < numSegments; i++)
	{
		float angle = 2.0f * PI * float(i) / float(numSegments); // Sudut dalam radian
		float x = jarakPlanet * cos(angle);
		float z = jarakPlanet * sin(angle);
		glVertex3f(x, 0.0f, z);
	}
	glEnd();
	glPopMatrix();
}

void matahari()
{
	glPushMatrix();
	glColor3ub(212, 246, 255);
	glRotatef(rotation += 0.01, 0, 1, 0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glutSolidSphere(radiusMatahari, 30, 30);
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

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Atur posisi dan properti lampu
	glEnable(GL_LIGHTING); // Aktifkan pencahayaan
	glEnable(GL_LIGHT0);   // Aktifkan lampu 0
	glEnable(GL_LIGHT1);   // Aktifkan lampu 1
	glEnable(GL_LIGHT2);   // Aktifkan lampu 2
	glEnable(GL_LIGHT3);   // Aktifkan lampu 3

	// Lampu 0
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular1);

	// Lampu 1
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);

	// Lampu 2
	glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular3);

	// Lampu 3
	glLightfv(GL_LIGHT3, GL_POSITION, light_position4);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient4);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse4);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular4);

	// Gambar Matahari
	matahari();

	// Orbit dan planet
	drawOrbit(jarakPlanetMerkurius);
	createPlanet(rotationAngleMerkurius, jarakPlanetMerkurius, radiusMerkurius, mercuryColor);

	drawOrbit(jarakPlanetVenus);
	createPlanet(rotationAngleVenus, jarakPlanetVenus, radiusVenus, venusColor);

	drawOrbit(jarakPlanetBumi);
	createPlanet(rotationAngleBumi, jarakPlanetBumi, radiusBumi, earthColor);

	drawOrbit(jarakPlanetMars);
	createPlanet(rotationAngleMars, jarakPlanetMars, radiusMars, marsColor);

	drawOrbit(jarakPlanetJupiter);
	createPlanet(rotationAngleJupiter, jarakPlanetJupiter, radiusJupiter, jupiterColor);

	drawOrbit(jarakPlanetSaturnus);
	createPlanet(rotationAngleSaturnus, jarakPlanetSaturnus, radiusSaturnus, saturnColor);

	drawOrbit(jarakPlanetUranus);
	createPlanet(rotationAngleUranus, jarakPlanetUranus, radiusUranus, uranusColor);

	drawOrbit(jarakPlanetNeptunus);
	createPlanet(rotationAngleNeptunus, jarakPlanetNeptunus, radiusNeptunus, neptuneColor);

	glutSwapBuffers();
	glutPostRedisplay();

	rotationAngleMerkurius += kecepatanRotasiMerkurius;
	rotationAngleVenus += kecepatanRotasiVenus;
	rotationAngleBumi += kecepatanRotasiBumi;
	rotationAngleMars += kecepatanRotasiMars;
	rotationAngleJupiter += kecepatanRotasiJupiter;
	rotationAngleSaturnus += kecepatanRotasiSaturnus;
	rotationAngleUranus += kecepatanRotasiUranus;
	rotationAngleNeptunus += kecepatanRotasiNeptunus;
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
