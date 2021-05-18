#include "module.h"
#include <iostream>
#include <QOpenGLFunctions>
#include <QtDebug>

namespace Modules {

    Render_Info R_I;

    void Forward::render(void) {

        static const double PI = 3.14159;
        glColor4f(0.f, 0.f, 0.f, 0.f); // draw shape in black

        /* top triangle */
        double i, result = 0.1;
        glTranslatef(0, 0, 0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, this->Length, 0); /* center */
        for (i = 0; i <= 2 * PI; i += result)
            glVertex3f(R_I.Render_Width * cos(i), this->Length, R_I.Render_Width * sin(i));
        glEnd();

        // bottom triangle
        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0, 0, 0); /* center */
            for (i = 2 * PI; i >= 0; i -= result)
            glVertex3f(R_I.Render_Width * cos(i), 0, R_I.Render_Width * sin(i));
            glVertex3f(R_I.Render_Width, this->Length, 0);
        glEnd();

        /* middle tube */
        glBegin(GL_QUAD_STRIP);
            for (i = 0; i <= 2 * PI; i += result)    {
            glVertex3f(R_I.Render_Width * cos(i), 0, R_I.Render_Width * sin(i));
            glVertex3f(R_I.Render_Width * cos(i), this->Length, R_I.Render_Width * sin(i));
        }
        /*loop back to zero degrees */
        glVertex3f(R_I.Render_Width, 0, 0);
        glVertex3f(R_I.Render_Width, this->Length, 0);
        glEnd();

        glTranslatef(0,this->Length,0);

    }

    void NoForward::render(void) {
        glTranslatef(0,this->Length,0);
    }

    void LeftTurn::render(void) {
        R_I.rotation_current[0] += this->Angle;
        glRotatef(this->Angle, 0, 0, 1);
    }

    void RightTurn::render(void) {
        R_I.rotation_current[0] -= this->Angle;
        glRotatef(-this->Angle, 0, 0, 1);
    }

    void UpPitch::render(void) {
        R_I.rotation_current[1] += this->Angle;
        glRotatef(this->Angle,1,0,0);
    }

    void DownPitch::render(void) {
        R_I.rotation_current[1] -= this->Angle;
        glRotatef(-this->Angle,1,0,0);
    }

    void LeftRoll::render(void) {
        R_I.rotation_current[2] += this->Angle;
        glRotatef(this->Angle,0,1,0);
    }

    void RightRoll::render(void) {
        R_I.rotation_current[2] -= this->Angle;
        glRotatef(-this->Angle,0,1,0);
    }

    void Virtical::render(void) {
        //glRotatef(70,0,1,0);

        //glRotatef(-R_I.rotation_current[2],0,1,0);
        //glRotatef(-R_I.rotation_current[1],1,0,0);
        //glRotatef(-R_I.rotation_current[0],0,0,1);
    }

    void StartBranch::render(void) {
        glPushMatrix();
        R_I.Temp_Render_Width.push_back(R_I.Render_Width);
        R_I.rotation_branch.push_back(R_I.rotation_current); // put current position in branch pos vector
    }

    void EndBranch::render(void) {
        glPopMatrix();
        R_I.Render_Width = R_I.Temp_Render_Width[R_I.Temp_Render_Width.size()-1];
        R_I.Temp_Render_Width.pop_back();
        R_I.rotation_current = R_I.rotation_branch[R_I.rotation_branch.size() - 1 ]; // get last position in branch
        R_I.rotation_branch.pop_back();
    }

    void SetWidth::render(void) {
        R_I.Render_Width = this->Width;
    }

    void Placer::render(void) {
        // empty function as this module does not require any rendering it only acts as a placeholder
    }

    void Forward::print(void) {
        std::cout << Type << '(' << Length << ')' << std::endl;
    }

    void NoForward::print(void) {
        std::cout << Type << '(' << Length << ')' << std::endl;
    }

    void LeftTurn::print(void) {
        std::cout << Type << '(' << Angle << ')' << std::endl;
    }

    void RightTurn::print(void) {
        std::cout << Type << '(' << Angle << ')' << std::endl;
    }

    void UpPitch::print(void) {
        std::cout << Type << '(' << Angle << ')' << std::endl;
    }

    void DownPitch::print(void) {
        std::cout << Type << '(' << Angle << ')' << std::endl;
    }

    void LeftRoll::print(void) {
        std::cout << Type << '(' << Angle << ')' << std::endl;
    }

    void RightRoll::print(void) {
        std::cout << Type << '(' << Angle << ')' << std::endl;
    }

    void Virtical::print(void) {
        std::cout << Type << std::endl;
    }

    void StartBranch::print(void) {
        std::cout << Type << std::endl;
    }

    void EndBranch::print(void) {
        std::cout << Type << std::endl;
    }

    void SetWidth::print(void) {
        std::cout << Type << '(' << Width << ')' << std::endl;
    }

    void Placer::print(void) {
        std::cout << Type << '(' << Length << ',' << Width << ')' << std::endl;
    }

    char Forward::type(void) {
        return Type;
    }

    char NoForward::type(void) {
        return Type;
    }

    char LeftTurn::type(void) {
        return Type;
    }

    char RightTurn::type(void) {
        return Type;
    }

    char UpPitch::type(void) {
        return Type;
    }

    char DownPitch::type(void) {
        return Type;
    }

    char LeftRoll::type(void) {
        return Type;
    }

    char RightRoll::type(void) {
        return Type;
    }

    char Virtical::type(void) {
        return Type;
    }

    char StartBranch::type(void) {
        return Type;
    }

    char EndBranch::type(void) {
        return Type;
    }

    char SetWidth::type(void) {
        return Type;
    }

    char Placer::type(void) {
        return Type;
    }

    double Forward::value1(void) {
        return Length;
    }

    double NoForward::value1(void) {
        return Length;
    }

    double LeftTurn::value1(void) {
        return Angle;
    }

    double RightTurn::value1(void) {
        return Angle;
    }

    double UpPitch::value1(void) {
        return Angle;
    }

    double DownPitch::value1(void) {
        return Angle;
    }

    double LeftRoll::value1(void) {
        return Angle;
    }

    double RightRoll::value1(void) {
        return Angle;
    }

    double SetWidth::value1(void) {
        return Width;
    }

    double Placer::value1(void) {
        return Length;
    }

    double Placer::value2(void) {
        return Width;
    }


    void reset_render_info(void){
        R_I.rotation_current = {0,0,0};
        R_I.Render_Width = 0.1;
        R_I.rotation_branch.clear();
        R_I.Temp_Render_Width.clear();
    }
}
