#include <GL/glew.h>
#include <GL/freeglut.h>

// define the features of each planet
typedef struct {
    const char* name;
    GLint current_day;
    const GLint n_stacks, n_slices, name_len, days_in_year;
    const GLfloat x, amb[4], diff[4], spec[4], shine[1], radius;
} Planet;

// OpenGL global variables
static GLsizei window_width = 1280, window_height = 720;

// globals
static const GLfloat planets_z = -30.0;  // planets position on z axis
static const GLfloat light_pos[] = {0.0, 0.0, planets_z, 1.0};  // light coordinates
static const int planets_num = 8;  // number of planets in the solar system
static Planet planets[] = {  // array to hold all planets
    { .name = "Mercury", .x = 1.0,  .n_stacks = 10, .n_slices = 10, .current_day = 1, .days_in_year = 88,    .name_len = 7, .radius = 0.02439, .amb = {0.50, 0.40, 0.30, 1.0}, .diff = {1.0, 0.9, 0.8, 1.0}, .spec = {0.25, 0.20, 0.15, 1.0}, .shine = {20.0}},
    { .name = "Venus",   .x = 2.0,  .n_stacks = 10, .n_slices = 10, .current_day = 1, .days_in_year = 225,   .name_len = 5, .radius = 0.06052, .amb = {0.50, 0.35, 0.20, 1.0}, .diff = {1.0, 0.7, 0.4, 1.0}, .spec = {0.25, 0.15, 0.10, 1.0}, .shine = {20.0}},
    { .name = "Earth",   .x = 3.0,  .n_stacks = 10, .n_slices = 10, .current_day = 1, .days_in_year = 365,   .name_len = 5, .radius = 0.06371, .amb = {0.20, 0.20, 0.50, 1.0}, .diff = {0.4, 0.4, 1.0, 1.0}, .spec = {0.10, 0.10, 0.25, 1.0}, .shine = {20.0}},
    { .name = "Mars",    .x = 4.0,  .n_stacks = 10, .n_slices = 10, .current_day = 1, .days_in_year = 687,   .name_len = 4, .radius = 0.03390, .amb = {0.50, 0.20, 0.10, 1.0}, .diff = {1.0, 0.4, 0.2, 1.0}, .spec = {0.25, 0.10, 0.05, 1.0}, .shine = {20.0}},
    { .name = "Jupiter", .x = 6.0,  .n_stacks = 50, .n_slices = 50, .current_day = 1, .days_in_year = 4333,  .name_len = 7, .radius = 0.69911, .amb = {0.50, 0.35, 0.25, 1.0}, .diff = {1.0, 0.7, 0.5, 1.0}, .spec = {0.25, 0.20, 0.10, 1.0}, .shine = {20.0}},
    { .name = "Saturn",  .x = 8.0,  .n_stacks = 50, .n_slices = 50, .current_day = 1, .days_in_year = 10759, .name_len = 6, .radius = 0.58232, .amb = {0.50, 0.45, 0.30, 1.0}, .diff = {1.0, 0.9, 0.6, 1.0}, .spec = {0.15, 0.10, 0.00, 0.2}, .shine = {20.0}},
    { .name = "Uranus",  .x = 10.0, .n_stacks = 25, .n_slices = 25, .current_day = 1, .days_in_year = 30687, .name_len = 6, .radius = 0.25362, .amb = {0.20, 0.40, 0.50, 1.0}, .diff = {0.4, 0.8, 1.0, 1.0}, .spec = {0.10, 0.20, 0.25, 1.0}, .shine = {20.0}},
    { .name = "Neptune", .x = 11.0, .n_stacks = 25, .n_slices = 25, .current_day = 1, .days_in_year = 60190, .name_len = 7, .radius = 0.24622, .amb = {0.10, 0.10, 0.50, 1.0}, .diff = {0.3, 0.3, 1.0, 1.0}, .spec = {0.05, 0.05, 0.25, 1.0}, .shine = {20.0}},
};

// display routine
void display(void)
{
    // position light
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Push initial state on the stack
    glPushMatrix();

    // turn on light
    glEnable(GL_LIGHT0);

    for (size_t i = 0; i < planets_num; ++i) {
        glPopMatrix();
        glPushMatrix();

        // set material properties of the planet
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   planets[i].amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   planets[i].diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  planets[i].spec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, planets[i].shine);

        /* Draw Planet */
        // place in the scene
        glTranslatef(0.0, 0.0, planets_z);
        // adjust for orbital period
        glRotatef(((GLfloat) planets[i].current_day / planets[i].days_in_year) * 360.0, 0.0, 1.0, 0.0);
        // set in correct position on x axis
        glTranslatef(planets[i].x, 0.0, 0.0);
        // draw planet
        glutSolidSphere(planets[i].radius, planets[i].n_slices, planets[i].n_stacks);
    }

    // pop initial state from the stack
    glPopMatrix();

    glFinish();

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
