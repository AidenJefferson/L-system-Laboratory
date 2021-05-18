#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <gl/GLU.h>
#include "lsystem.h"

class GLWindow : public QOpenGLWidget, public QOpenGLFunctions {
public:
    GLWindow(QWidget* parent = nullptr);
    double camera_shift = 1;
    L_System::LSystem L_sys;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void zoom(double c);
};

#endif // GLWINDOW_H
