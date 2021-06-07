#include <GL/glew.h>
#include <GL/freeglut.h>

// OpenGL global variables
static GLsizei window_width = 1280, window_height = 720;

int main(int argc, char **argv)
{
    // pass potential input arguments to glutInit
    glutInit(&argc, argv);

    // create window
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Solar System");

    // add support for GLEW
    glewInit();
}
