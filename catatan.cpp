#include <GL/glut.h>
#include <math.h>

float object = 10.0;
float PI = 3.146;
float radius = 20.0; // Reduced radius for better visibility of all planets
float rotationAngle = 0.0;
float rotation = 0.0;
float rotationCube = 0.0;
float aspect;


// Radius tiap planet
float radiusMatahari = 8.0;    // Ukuran Matahari
float radiusMerkurius = 0.5;    // Ukuran Merkurius
float radiusVenus = 0.8;        // Ukuran Venus
float radiusBumi = 0.9;         // Ukuran Bumi
float radiusMars = 0.47;        // Ukuran Mars
float radiusJupiter = 2.3;      // Ukuran Jupiter
float radiusSaturnus = 2.1;     // Ukuran Saturnus
float radiusUranus = 1.3;       // Ukuran Uranus
float radiusNeptunus = 1.3;     // Ukuran Neptunus

// Jarak tiap planet dari matahari
float jarakPlanetMerkurius = 10.0;
float jarakPlanetVenus = 15.0;
float jarakPlanetBumi = 25.0;
float jarakPlanetMars = 30.0;
float jarakPlanetJupiter = 40.0;
float jarakPlanetSaturnus = 50.0;
float jarakPlanetUranus = 60.0;
float jarakPlanetNeptunus = 70.0;

float kecepatanRotasi = 0.1;

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

GLfloat light_position[] = { 0.0, 150.0, 0.0, 1.0 };
GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

float xLookAt = -20.0;
float yLookAt = 60.0;
float zLookAt = 100.0;

void reshape(int w, int h) {
	if (h == 0) {
 		h = 1;
 	}
 	aspect = (float)w / (float)h;
 	glViewport(0, 0, w, h);
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
 	gluPerspective(45.0, aspect, 1.0, 300.0);  // Slightly reduce far plane for better zooming
 	gluLookAt(xLookAt, yLookAt, zLookAt, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
// 	gluLookAt(-20.0, 60.0, 55.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
// 	gluLookAt(-20.0, 20.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
 	glLoadIdentity();
}

bool showOrbit = true; 

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
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

void drawOrbit(float jarakPlanet) {
    if (!showOrbit) return; // Jika orbit tidak ditampilkan, keluar dari fungsi
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); // Warna putih untuk lintasan orbit
    glBegin(GL_LINE_LOOP);
    int numSegments = 100; // Jumlah segmen untuk membentuk lingkaran
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * PI * float(i) / float(numSegments); // Sudut dalam radian
        float x = jarakPlanet * cos(angle);
        float z = jarakPlanet * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
    glPopMatrix();
}

void matahari() {
	glPushMatrix();
 	glColor3ub(212, 246, 255);
 	glRotatef(rotation += 0.01, 0, 1, 0);
 	glRotatef(90, 1.0, 0.0, 0.0);
 	glutWireSphere(radiusMatahari, 30, 30);
 	glPopMatrix();
}

void merkurius(float rotationAnglePlanet, float jarakPlanet, float radiusPlanet) {
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAnglePlanet;
 	float x = jarakPlanet * cos(angle);
 	float z = jarakPlanet * sin(angle);
	
	glPushMatrix();
 	glTranslatef(x, 0.0f, z);
 	glColor3f(0.6f, 0.6f, 0.6f);
 	glutWireSphere(radiusPlanet, 30, 30);
 	glPopMatrix();
}

void venus() {
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAngleVenus;
 	float x = jarakPlanetVenus * cos(angle);
 	float z = jarakPlanetVenus * sin(angle);
 	
 	glPushMatrix();
 	glTranslatef(x, 0.0f, z);
 	glColor3f(0.8f, 0.6f, 0.2f); // Adjusted color
 	glutWireSphere(radiusVenus, 30, 30);
 	glPopMatrix();
}

void bumi() {
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAngleBumi;
 	float x = jarakPlanetBumi * cos(angle);
 	float z = jarakPlanetBumi * sin(angle);

	glPushMatrix();
 	glTranslatef(x, 0.0f, z);
 	glColor3f(0.2f, 0.6f, 1.0f); // Adjusted color for Earth
 	glutWireSphere(radiusBumi, 30, 30);
 	glPopMatrix();	
}

void mars() {
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAngleMars;
 	float x = jarakPlanetMars * cos(angle);
 	float z = jarakPlanetMars * sin(angle);

	glPushMatrix();
 	glTranslatef(x, 0.0f, z);
 	glColor3f(1.0f, 0.0f, 0.0f); // Mars color
 	glutWireSphere(radiusMars, 30, 30);
 	glPopMatrix();
}

void jupiter() {
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAngleJupiter;
 	float x = jarakPlanetJupiter * cos(angle);
 	float z = jarakPlanetJupiter * sin(angle);

	glPushMatrix();
 	glTranslatef(x, 0.0f, z);
 	glColor3f(1.0f, 1.0f, 0.0f); // Jupiter color
 	glutWireSphere(radiusJupiter, 30, 30);
 	glPopMatrix();
}

void saturnus() {
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAngleSaturnus;
 	float x = jarakPlanetSaturnus * cos(angle);
 	float z = jarakPlanetSaturnus * sin(angle);

	glPushMatrix();
 	glTranslatef(x, 0.0f, z);
 	glColor3f(1.0f, 0.5f, 0.0f); // Saturn color
 	glutWireSphere(radiusSaturnus, 30, 30);
 	glPopMatrix();
}

void uranus() {
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAngleUranus;
 	float x = jarakPlanetUranus * cos(angle);
 	float z = jarakPlanetUranus * sin(angle);

	glPushMatrix();
 	glTranslatef(x, 0.0f, z);
 	glColor3f(0.0f, 0.0f, 1.0f); // Uranus color
 	glutWireSphere(radiusUranus, 30, 30);
 	glPopMatrix();
}

void neptunus() {
	float angle = (14 * (360.0f / object) * (PI / 180.0f)) + rotationAngleNeptunus;
 	float x = jarakPlanetNeptunus * cos(angle);
 	float z = jarakPlanetNeptunus * sin(angle);

	glPushMatrix();
 	glTranslatef(x, 0.0f, z);
 	glColor3f(0.0f, 0.0f, 1.0f); // Neptune color
 	glutWireSphere(radiusNeptunus, 30, 30);
 	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
 	// Posisi dan pengaturan cahaya
 	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
 	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
 	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
 	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
 	
 	glEnable(GL_LIGHTING);
 	glEnable(GL_LIGHT0);
 	
 	matahari();
 	
    // Orbit dan planet
    drawOrbit(jarakPlanetMerkurius);
    merkurius(rotationAngleMerkurius, jarakPlanetMerkurius, radiusMerkurius);

    drawOrbit(jarakPlanetVenus);
    venus();

    drawOrbit(jarakPlanetBumi);
    bumi();

    drawOrbit(jarakPlanetMars);
    mars();

    drawOrbit(jarakPlanetJupiter);
    jupiter();

    drawOrbit(jarakPlanetSaturnus);
    saturnus();

    drawOrbit(jarakPlanetUranus);
    uranus();

    drawOrbit(jarakPlanetNeptunus);
    neptunus();
 	
 	glPushMatrix();
 	glRotatef(5.0, 1.0, 0.0, 0.5);
 	for (int i = 0; i < object; ++i) {
 		float angle = (i * (360.0f / object) * (PI / 180.0f)) - rotationAngle;
 		float x = radius * cos(angle);
 		float z = radius * sin(angle);
 	}
 	glPopMatrix();
 
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

void inisialisasi() {
 	glEnable(GL_DEPTH_TEST);
 	glEnable(GL_COLOR_MATERIAL);
 	glClearColor(0.1, 0.1, 0.1, 1.0);
}
	
int main(int argc, char** argv) {
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

