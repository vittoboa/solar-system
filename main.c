#include <GL/glew.h>
#include <GL/freeglut.h>

// OpenGL global variables
static GLsizei window_width = 1280, window_height = 720;

// globals
static const GLfloat planets_z = -30.0;  // planets position on z axis
static const GLfloat light_pos[] = {0.0, 0.0, planets_z, 1.0};  // light coordinates

// display routine
void display(void)
{
    // position light
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // turn on light
    glEnable(GL_LIGHT0);

    // swap buffer
    glutSwapBuffers();

    glutPostRedisplay();
}

void init(void)
{
    // global ambient light
    const float globAmb[] = {0.1, 0.1, 0.1, 1.0};

    // light property vectors
    const float lightAmb[]  = {0.2, 0.2, 0.2, 1.0};
    const float lightDif[]  = {1.0, 1.0, 1.0, 1.0};
    const float lightSpec[] = {0.1, 0.1, 0.1, 0.5};

    // select clearing color
    glClearColor(0.1, 0.1, 0.1, 0.0);

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glLoadIdentity();

    // set projection
    glMatrixMode(GL_PROJECTION);
    const float ratio = (float) window_width / (float) window_height, scale = 1.2;
    glFrustum(-(ratio * scale), ratio * scale, - scale, scale, 5.0, 60.0);

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);

    // turn on OpenGL lighting
    glEnable(GL_LIGHTING);

    // set light properties
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

    // global ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);

    // enable local viewpoint
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // set shading model
    glShadeModel(GL_SMOOTH);
}

// OpenGL window resize routine
void resize(int new_width, int new_height)
{
    glViewport(0, 0, new_width, new_height);
    window_width  = new_width;
    window_height = new_height;
}

int main(int argc, char **argv)
{
    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // create window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");
    glutReshapeFunc(resize);

    // add support for GLEW
    glewInit();

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
