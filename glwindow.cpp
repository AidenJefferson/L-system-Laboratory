#include "glwindow.h"
#include "module.h"
#include <QtDebug>

GLWindow::GLWindow(QWidget *parent)
    :   QOpenGLWidget{parent}
{
}

// Initialise OpenGL so that we can draw
void GLWindow::initializeGL()
{

    initializeOpenGLFunctions();

    glClearColor(0.999f,0.999f,0.999f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GLU_CULLING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(ANTIALIASED_QUALITY);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

}

void GLWindow::paintGL()
{

    Modules::reset_render_info();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // deals with
    glTranslatef(0,-this->camera_shift/3.5,-this->camera_shift);

    // runs through each L-system module and performs the correct turtle action
    for(std::shared_ptr<Modules::Module> X : this->L_sys.Modules){
        X->render();
    }

}

void GLWindow::resizeGL(int w, int h)
{

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 0.001, 50000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}
