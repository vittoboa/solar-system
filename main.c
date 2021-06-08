#include <GL/glew.h>
#include <GL/freeglut.h>

// OpenGL global variables
static GLsizei window_width = 1280, window_height = 720;

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
    const float ratio = (float) window_width / (float) window_height, scale = 1.2;
    glFrustum(-(ratio * scale), ratio * scale, - scale, scale, 5.0, 60.0);

    // initialize model view transforms
    glMatrixMode(GL_MODELVIEW);
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
    glutMainLoop();

    return 0;
}
