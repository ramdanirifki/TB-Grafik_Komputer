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

struct Camera
{
    float xLookAt = -20.0;
    float yLookAt = 30.0;
    float zLookAt = 100.0;
} posCam;

struct Planet merkurius = {0.5, 10.0, 0.0, 0.002, {0.6f, 0.6f, 0.6f}};
struct Planet venus = {0.8, 15.0, 0.0, 0.001, {0.8f, 0.6f, 0.2f}};
struct Planet bumi = {0.9, 25.0, 0.0, 0.0005, {0.2f, 0.6f, 1.0f}};
struct Planet mars = {0.47, 30.0, 0.0, 0.0004, {1.0f, 0.0f, 0.0f}};
struct Planet jupiter = {2.3, 40.0, 0.0, 0.0003, {1.0f, 1.0f, 0.0f}};
struct Planet saturnus = {2.1, 50.0, 0.0, 0.0002, {1.0f, 0.5f, 0.0f}};
struct Planet uranus = {1.3, 60.0, 0.0, 0.0001, {0.0f, 0.0f, 1.0f}};
struct Planet neptunus = {1.3, 70.0, 0.0, 0.00008, {0.0f, 0.0f, 1.0f}};

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

/*
--------------- New Function ----------------
*/
void updateCamera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 300.0);
    gluLookAt(posCam.xLookAt, posCam.yLookAt, posCam.zLookAt, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool showOrbit = true;

/*
--------------- Fungsi keyboard ----------------
*/

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
        showOrbit = !showOrbit;
        break;
    case 27:
        exit(0);
        break;
    case '1':
        posCam.xLookAt = -20.0;
        posCam.yLookAt = 60.0;
        posCam.zLookAt = 100.0;
        updateCamera();
        glutPostRedisplay();
        break;
    case '2':
        posCam.xLookAt = -20.0;
        posCam.yLookAt = 60.0;
        posCam.zLookAt = 50.0;
        updateCamera();
        glutPostRedisplay();
        break;
    case '3':
        posCam.xLookAt = -20.0;
        posCam.yLookAt = 20.0;
        posCam.zLookAt = 50.0;
        updateCamera();
        glutPostRedisplay();
        break;
    case '4':
        posCam.xLookAt = -20.0;
        posCam.yLookAt = 30.0;
        posCam.zLookAt = 100.0;
        updateCamera();
        glutPostRedisplay();
        break;
    }
}

/*
--------------- Fungsi reshape ----------------
*/
void reshape(int w, int h)
{
    if (h == 0)
    {
        h = 1;
    }
    aspect = (float)w / (float)h;
    glViewport(0, 0, w, h);
    updateCamera();
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

void matahari()
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
    drawOrbit(merkurius.jarak);
    createPlanet(merkurius.rotationAngle, merkurius.jarak, merkurius.radius, merkurius.color);

    drawOrbit(venus.jarak);
    createPlanet(venus.rotationAngle, venus.jarak, venus.radius, venus.color);

    drawOrbit(bumi.jarak);
    createPlanet(bumi.rotationAngle, bumi.jarak, bumi.radius, bumi.color);

    drawOrbit(mars.jarak);
    createPlanet(mars.rotationAngle, mars.jarak, mars.radius, mars.color);

    drawOrbit(jupiter.jarak);
    createPlanet(jupiter.rotationAngle, jupiter.jarak, jupiter.radius, jupiter.color);

    drawOrbit(saturnus.jarak);
    createPlanet(saturnus.rotationAngle, saturnus.jarak, saturnus.radius, saturnus.color);

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
