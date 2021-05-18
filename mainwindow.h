#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "instructions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Recursion_Slider_valueChanged(int value);

    void on_Output_Button_clicked();

    void on_Instructions_Button_clicked();

    void on_Zoom_Slider_sliderMoved(int position);

    void on_Generate_Button_pressed();

    void on_System3_Button_pressed();

    void on_System1_Button_pressed();

    void on_System2_Button_pressed();

    void on_Output_Button_pressed();

    void on_Export_Button_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
