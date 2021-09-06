#include <GL/glew.h>
#include <GL/freeglut.h>

// define the features of the material
typedef struct {
    const GLfloat amb[4], diff[4], spec[4], emit[4], shine[1];
} Material;

// define the features of the light
typedef struct {
    const GLfloat amb[4], diff[4], spec[4], pos[4];
} Light;

// define the features of each planet
typedef struct {
    const char* name;
    GLint current_day;
    const GLint n_stacks, n_slices, days_in_year;
    const GLfloat x, radius;
    const Material material;
} Planet;

// OpenGL global variables
static GLsizei window_width = 1280, window_height = 720;

// globals
static const GLfloat planets_z = -30.0;  // planets position on z axis
static const size_t planets_num = 8;  // number of planets in the solar system
static const GLint days_speed = 1;  // how many days are added at each iteration
static const Light lights[] = {
    {  // sunlight
        .amb  = {0.2, 0.2, 0.2, 1.0},
        .diff = {1.0, 0.8, 0.5, 1.0},
        .spec = {1.0, 0.6, 0.1, 1.0},
        .pos  = {0.0, 0.0, planets_z, 1.0}
    }
};

// display routine
void display(void)
{
    // add sunlight
    glLightfv(GL_LIGHT0, GL_POSITION, lights[0].pos);
    glEnable(GL_LIGHT0);

    // clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // push initial state on the stack
    glPushMatrix();

    static Planet planets[] = {  // array to hold all planets
        { .name = "Mercury", .x = 2.0,  .n_stacks = 10, .n_slices = 10, .current_day = 1, .days_in_year = 88,    .radius = 0.02439, .material = { .amb = {0.50, 0.40, 0.30, 1.0}, .diff = {1.0, 0.9, 0.8, 1.0}, .spec = {0.25, 0.20, 0.15, 1.0}, .shine = {20.0} } },
        { .name = "Venus",   .x = 2.5,  .n_stacks = 10, .n_slices = 10, .current_day = 1, .days_in_year = 225,   .radius = 0.06052, .material = { .amb = {0.50, 0.35, 0.20, 1.0}, .diff = {1.0, 0.7, 0.4, 1.0}, .spec = {0.25, 0.15, 0.10, 1.0}, .shine = {20.0} } },
        { .name = "Earth",   .x = 3.0,  .n_stacks = 10, .n_slices = 10, .current_day = 1, .days_in_year = 365,   .radius = 0.06371, .material = { .amb = {0.20, 0.20, 0.50, 1.0}, .diff = {0.4, 0.4, 1.0, 1.0}, .spec = {0.10, 0.10, 0.25, 1.0}, .shine = {20.0} } },
        { .name = "Mars",    .x = 4.0,  .n_stacks = 10, .n_slices = 10, .current_day = 1, .days_in_year = 687,   .radius = 0.03390, .material = { .amb = {0.50, 0.20, 0.10, 1.0}, .diff = {1.0, 0.4, 0.2, 1.0}, .spec = {0.25, 0.10, 0.05, 1.0}, .shine = {20.0} } },
        { .name = "Jupiter", .x = 6.0,  .n_stacks = 50, .n_slices = 50, .current_day = 1, .days_in_year = 4333,  .radius = 0.69911, .material = { .amb = {0.50, 0.35, 0.25, 1.0}, .diff = {1.0, 0.7, 0.5, 1.0}, .spec = {0.25, 0.20, 0.10, 1.0}, .shine = {20.0} } },
        { .name = "Saturn",  .x = 8.0,  .n_stacks = 50, .n_slices = 50, .current_day = 1, .days_in_year = 10759, .radius = 0.58232, .material = { .amb = {0.50, 0.45, 0.30, 1.0}, .diff = {1.0, 0.9, 0.6, 1.0}, .spec = {0.15, 0.10, 0.00, 0.2}, .shine = {20.0} } },
        { .name = "Uranus",  .x = 10.0, .n_stacks = 25, .n_slices = 25, .current_day = 1, .days_in_year = 30687, .radius = 0.25362, .material = { .amb = {0.20, 0.40, 0.50, 1.0}, .diff = {0.4, 0.8, 1.0, 1.0}, .spec = {0.10, 0.20, 0.25, 1.0}, .shine = {20.0} } },
        { .name = "Neptune", .x = 11.0, .n_stacks = 25, .n_slices = 25, .current_day = 1, .days_in_year = 60190, .radius = 0.24622, .material = { .amb = {0.10, 0.10, 0.50, 1.0}, .diff = {0.3, 0.3, 1.0, 1.0}, .spec = {0.05, 0.05, 0.25, 1.0}, .shine = {20.0} } },
    };

    for (size_t i = 0; i < planets_num; ++i) {
        glPopMatrix();
        glPushMatrix();

        // set material properties of the planet
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   planets[i].material.amb);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   planets[i].material.diff);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  planets[i].material.spec);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, planets[i].material.shine);

        /* Draw Planet */
        // place in the scene
        glTranslatef(0.0, 0.0, planets_z);
        // adjust for orbital period
        glRotatef(((GLfloat) planets[i].current_day / planets[i].days_in_year) * 360.0, 0.0, 1.0, 0.0);
        // set in correct position on x axis
        glTranslatef(planets[i].x, 0.0, 0.0);
        // draw planet
        glutSolidSphere(planets[i].radius, planets[i].n_slices, planets[i].n_stacks);

        /* Update days */
        // check if the year is not over
        if (planets[i].current_day < planets[i].days_in_year) {
            // set to next day
            planets[i].current_day += days_speed;
        } else {
            // reset to first day
            planets[i].current_day = 1;
        }
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
    // select clearing color
    glClearColor(0.1, 0.1, 0.1, 0.0);

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    // initialize viewing values
    glLoadIdentity();

    // set projection
    glMatrixMode(GL_PROJECTION);
    const GLdouble ratio = (GLdouble) window_width / window_height, scale = 1.2;
    glFrustum(-(ratio * scale), ratio * scale, - scale, scale, 5.0, 60.0);

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);

    // turn on OpenGL lighting
    glEnable(GL_LIGHTING);

    // set sunlight properties
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lights[0].amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lights[0].diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lights[0].spec);

    // set global ambient light
    const GLfloat globAmb[] = {0.1, 0.1, 0.1, 1.0};
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
