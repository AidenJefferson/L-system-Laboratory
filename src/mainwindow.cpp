#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QString>
#include <QValidator>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QFile>
#include <sstream>
#include <QTextStream>
#include <QRegExpValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(800+400, this->height());
    setWindowIcon(QIcon(":/icon/icon.ico"));
    ui->GL_Splitter->setSizes(QList<int>() << 650 << 450 );
    ui->Recursion_Slider->setRange(1,15);
    ui->Recursion_Slider->setValue(1);
    ui->Zoom_Slider->setRange(1,50);
    ui->Zoom_Slider->setValue(1);
    ui->Rule1_Box->setHidden(true);

    // set validations
    QDoubleValidator *dv = new QDoubleValidator(0, 1000, 3, this);
    ui->Def1_Value->setValidator( dv );
    ui->Def2_Value->setValidator( dv );
    ui->Def3_Value->setValidator( dv );
    ui->Def4_Value->setValidator( dv );
    ui->Def5_Value->setValidator( dv );
    ui->Def5_Value->setValidator( dv );

    QRegExp rx_char("[a-eg-z]{1}");
    QRegExpValidator *ev_char = new QRegExpValidator(rx_char, this);
    ui->Def1_Char->setValidator( ev_char );
    ui->Def2_Char->setValidator( ev_char );
    ui->Def3_Char->setValidator( ev_char );
    ui->Def4_Char->setValidator( ev_char );
    ui->Def5_Char->setValidator( ev_char );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Recursion_Slider_valueChanged(int value)
{
    ui->Recursion_Val->clear();
    ui->Recursion_Val->insert(QString::number(value));
}

void MainWindow::on_Output_Button_clicked()
{
    ui->Output_Text->selectAll();
    ui->Output_Text->copy();
}

void MainWindow::on_Instructions_Button_clicked()
{
    Instructions insWindow;
    insWindow.setModal(true);
    insWindow.exec();
}

void MainWindow::on_Zoom_Slider_sliderMoved(int position)
{
    ui->GL->camera_shift = position + (position - 1) * 3;
    ui->GL->update();
}

void MainWindow::on_Generate_Button_pressed()
{
    int Recursion{ 1 };
    std::string Axium;
    std::vector<std::pair<char,double>> Defines;
    std::vector<Production_Rule> Rules;

    /* Store the Defines Set */
    if(ui->Def1_Box->isChecked()){
        std::string ch = ui->Def1_Char->text().toStdString();
        double val = ui->Def1_Value->text().toDouble();

        Defines.push_back({ch[0], val});
    }
    if(ui->Def2_Box->isChecked()){
        std::string ch = ui->Def2_Char->text().toStdString();
        double val = ui->Def2_Value->text().toDouble();

        Defines.push_back({ch[0], val});
    }
    if(ui->Def3_Box->isChecked()){
        std::string ch = ui->Def3_Char->text().toStdString();
        double val = ui->Def3_Value->text().toDouble();

        Defines.push_back({ch[0], val});
    }
    if(ui->Def4_Box->isChecked()){
        std::string ch = ui->Def4_Char->text().toStdString();
        double val = ui->Def4_Value->text().toDouble();

        Defines.push_back({ch[0], val});
    }
    if(ui->Def5_Box->isChecked()){
        std::string ch = ui->Def5_Char->text().toStdString();
        double val = ui->Def5_Value->text().toDouble();

        Defines.push_back({ch[0], val});
    }
    if(ui->Def6_Box->isChecked()){
        std::string ch = ui->Def6_Char->text().toStdString();
        double val = ui->Def6_Value->text().toDouble();

        Defines.push_back({ch[0], val});
    }

    /* Store the Recursion Set */
    Recursion = ui->Recursion_Slider->value();

    /* Store the Axium Set */
    Axium = ui->Axium_Entry->text().toStdString();

    /* Store the Production Rules */
    if(ui->Rule1_Box->isChecked()){
        std::string pre = ui->Rule1_Pre->text().toStdString();
        std::string suc = ui->Rule1_Suc->text().toStdString();

        Rules.push_back({pre,suc});
    }
    if(ui->Rule2_Box->isChecked()){
        std::string pre = ui->Rule2_Pre->text().toStdString();
        std::string suc = ui->Rule2_Suc->text().toStdString();

        Rules.push_back({pre,suc});
    }
    if(ui->Rule3_Box->isChecked()){
        std::string pre = ui->Rule3_Pre->text().toStdString();
        std::string suc = ui->Rule3_Suc->text().toStdString();

        Rules.push_back({pre,suc});
    }
    if(ui->Rule4_Box->isChecked()){
        std::string pre = ui->Rule4_Pre->text().toStdString();
        std::string suc = ui->Rule4_Suc->text().toStdString();

        Rules.push_back({pre,suc});
    }
    if(ui->Rule5_Box->isChecked()){
        std::string pre = ui->Rule5_Pre->text().toStdString();
        std::string suc = ui->Rule5_Suc->text().toStdString();

        Rules.push_back({pre,suc});
    }
    if(ui->Rule6_Box->isChecked()){
        std::string pre = ui->Rule6_Pre->text().toStdString();
        std::string suc = ui->Rule6_Suc->text().toStdString();

        Rules.push_back({pre,suc});
    }

    try{
        ui->GL->L_sys.update( Recursion, Axium , Rules, Defines );
    }
    catch(std::exception& e){
        QMessageBox::warning(this, "Error:", e.what());
    }
    ui->GL->update();
}


void MainWindow::on_System1_Button_pressed()
{

    /* Set-Up Defines */
    this->ui->Def1_Box->clicked(true);
    this->ui->Def1_Box->setChecked(true);
    this->ui->Def1_Comment->clear();
    this->ui->Def1_Comment->insert("Trunk Contraction Ratio");
    this->ui->Def1_Char->clear();
    this->ui->Def1_Char->insert(QString('r'));
    this->ui->Def1_Value->clear();
    this->ui->Def1_Value->insert(QString::number(0.95));

    this->ui->Def2_Box->clicked(true);
    this->ui->Def2_Box->setChecked(true);
    this->ui->Def2_Comment->clear();
    this->ui->Def2_Comment->insert("Branch Contraction Ratio");
    this->ui->Def2_Char->clear();
    this->ui->Def2_Char->insert(QString('s'));
    this->ui->Def2_Value->clear();
    this->ui->Def2_Value->insert(QString::number(0.66));

    this->ui->Def3_Box->clicked(true);
    this->ui->Def3_Box->setChecked(true);
    this->ui->Def3_Comment->clear();
    this->ui->Def3_Comment->insert("Branch Angle From Trunk");
    this->ui->Def3_Char->clear();
    this->ui->Def3_Char->insert(QString('a'));
    this->ui->Def3_Value->clear();
    this->ui->Def3_Value->insert(QString::number(45));

    this->ui->Def4_Box->clicked(true);
    this->ui->Def4_Box->setChecked(true);
    this->ui->Def4_Comment->clear();
    this->ui->Def4_Comment->insert("Branch Angle From Lateral Axis");
    this->ui->Def4_Char->clear();
    this->ui->Def4_Char->insert(QString('b'));
    this->ui->Def4_Value->clear();
    this->ui->Def4_Value->insert(QString::number(30));

    this->ui->Def5_Box->clicked(true);
    this->ui->Def5_Box->setChecked(true);
    this->ui->Def5_Comment->clear();
    this->ui->Def5_Comment->insert("Divergence Angle");
    this->ui->Def5_Char->clear();
    this->ui->Def5_Char->insert(QString('d'));
    this->ui->Def5_Value->clear();
    this->ui->Def5_Value->insert(QString::number(137.5));

    this->ui->Def6_Box->clicked(true);
    this->ui->Def6_Box->setChecked(true);
    this->ui->Def6_Comment->clear();
    this->ui->Def6_Comment->insert("Width Decrease Rate");
    this->ui->Def6_Char->clear();
    this->ui->Def6_Char->insert(QString('v'));
    this->ui->Def6_Value->clear();
    this->ui->Def6_Value->insert(QString::number(0.707));

    /* Set-Up Recursion */
    this->ui->Recursion_Slider->setValue(12);

    /* Set-Up Axium */
    this->ui->Axium_Entry->clear();
    this->ui->Axium_Entry->insert("A(10,1.25)");

    /* Set-Up Production Rules */
    this->ui->Rule1_Pre->clear();
    this->ui->Rule1_Pre->insert("A(l,w)");
    this->ui->Rule1_Suc->clear();
    this->ui->Rule1_Suc->insert("!(w)F(l)[&(a)B(l*s,w*v)]>(d)A(l*r,w*v)");
    this->ui->Rule2_Box->clicked(true);
    this->ui->Rule2_Box->setChecked(true);
    this->ui->Rule2_Pre->clear();
    this->ui->Rule2_Pre->insert("B(l,w)");
    this->ui->Rule2_Suc->clear();
    this->ui->Rule2_Suc->insert("!(w)F(l)[-(b)C(l*s,w*v)]+(40)>(49)&(18)C(l*r,w*v)");
    this->ui->Rule3_Box->clicked(true);
    this->ui->Rule3_Box->setChecked(true);
    this->ui->Rule3_Pre->clear();
    this->ui->Rule3_Pre->insert("C(l,w)");
    this->ui->Rule3_Suc->clear();
    this->ui->Rule3_Suc->insert("!(w)F(l)[+(b)B(l*s,w*v)]-(b)<(10)^(36)B(l*r,w*v)");
    this->ui->Rule4_Box->clicked(false);
    this->ui->Rule4_Box->setChecked(false);
    this->ui->Rule4_Pre->clear();
    this->ui->Rule4_Suc->clear();
    this->ui->Rule5_Box->clicked(false);
    this->ui->Rule5_Box->setChecked(false);
    this->ui->Rule5_Pre->clear();
    this->ui->Rule5_Suc->clear();
    this->ui->Rule6_Box->clicked(false);
    this->ui->Rule6_Box->setChecked(false);
    this->ui->Rule6_Pre->clear();
    this->ui->Rule6_Suc->clear();

}

void MainWindow::on_System2_Button_pressed()
{
    /* Set-Up Defines */
    this->ui->Def1_Box->clicked(true);
    this->ui->Def1_Box->setChecked(true);
    this->ui->Def1_Comment->clear();
    this->ui->Def1_Comment->insert("Branching Angle");
    this->ui->Def1_Char->clear();
    this->ui->Def1_Char->insert(QString('d'));
    this->ui->Def1_Value->clear();
    this->ui->Def1_Value->insert(QString::number(25.7));
    this->ui->Def2_Box->clicked(false);
    this->ui->Def2_Box->setChecked(false);
    this->ui->Def2_Comment->clear();
    this->ui->Def2_Char->clear();
    this->ui->Def2_Value->clear();
    this->ui->Def3_Box->clicked(false);
    this->ui->Def3_Box->setChecked(false);
    this->ui->Def3_Comment->clear();
    this->ui->Def3_Char->clear();
    this->ui->Def3_Value->clear();
    this->ui->Def4_Box->clicked(false);
    this->ui->Def4_Box->setChecked(false);
    this->ui->Def4_Comment->clear();
    this->ui->Def4_Char->clear();
    this->ui->Def4_Value->clear();
    this->ui->Def5_Box->clicked(false);
    this->ui->Def5_Box->setChecked(false);
    this->ui->Def5_Comment->clear();
    this->ui->Def5_Char->clear();
    this->ui->Def5_Value->clear();
    this->ui->Def6_Box->clicked(false);
    this->ui->Def6_Box->setChecked(false);
    this->ui->Def6_Comment->clear();
    this->ui->Def6_Char->clear();
    this->ui->Def6_Value->clear();

    /* Set-Up Recursion */
    this->ui->Recursion_Slider->setValue(5);

    /* Set-Up Axium */
    this->ui->Axium_Entry->clear();
    this->ui->Axium_Entry->insert("!(0.015)F(0.1)");

    /* Set-Up Production Rules */
    this->ui->Rule1_Pre->clear();
    this->ui->Rule1_Pre->insert("F(l)");
    this->ui->Rule1_Suc->clear();
    this->ui->Rule1_Suc->insert("F(l)[+(d)F(l)]F(l)[-(d)F(l)]F(l)");
    this->ui->Rule2_Box->clicked(false);
    this->ui->Rule2_Box->setChecked(false);
    this->ui->Rule2_Pre->clear();
    this->ui->Rule2_Suc->clear();
    this->ui->Rule3_Box->clicked(false);
    this->ui->Rule3_Box->setChecked(false);
    this->ui->Rule3_Pre->clear();
    this->ui->Rule3_Suc->clear();
    this->ui->Rule4_Box->clicked(false);
    this->ui->Rule4_Box->setChecked(false);
    this->ui->Rule4_Pre->clear();
    this->ui->Rule4_Suc->clear();
    this->ui->Rule5_Box->clicked(false);
    this->ui->Rule5_Box->setChecked(false);
    this->ui->Rule5_Pre->clear();
    this->ui->Rule5_Suc->clear();
    this->ui->Rule6_Box->clicked(false);
    this->ui->Rule6_Box->setChecked(false);
    this->ui->Rule6_Pre->clear();
    this->ui->Rule6_Suc->clear();

}

void MainWindow::on_System3_Button_pressed() // Set-Up Preset L-System
{

    /* Set-Up Defines */
    this->ui->Def1_Box->clicked(true);
    this->ui->Def1_Box->setChecked(true);
    this->ui->Def1_Comment->clear();
    this->ui->Def1_Comment->insert("Branching Angle");
    this->ui->Def1_Char->clear();
    this->ui->Def1_Char->insert(QString('d'));
    this->ui->Def1_Value->clear();
    this->ui->Def1_Value->insert(QString::number(22.5));
    this->ui->Def2_Box->clicked(false);
    this->ui->Def2_Box->setChecked(false);
    this->ui->Def2_Comment->clear();
    this->ui->Def2_Char->clear();
    this->ui->Def2_Value->clear();
    this->ui->Def3_Box->clicked(false);
    this->ui->Def3_Box->setChecked(false);
    this->ui->Def3_Comment->clear();
    this->ui->Def3_Char->clear();
    this->ui->Def3_Value->clear();
    this->ui->Def4_Box->clicked(false);
    this->ui->Def4_Box->setChecked(false);
    this->ui->Def4_Comment->clear();
    this->ui->Def4_Char->clear();
    this->ui->Def4_Value->clear();
    this->ui->Def5_Box->clicked(false);
    this->ui->Def5_Box->setChecked(false);
    this->ui->Def5_Comment->clear();
    this->ui->Def5_Char->clear();
    this->ui->Def5_Value->clear();
    this->ui->Def6_Box->clicked(false);
    this->ui->Def6_Box->setChecked(false);
    this->ui->Def6_Comment->clear();
    this->ui->Def6_Char->clear();
    this->ui->Def6_Value->clear();

    /* Set-Up Recursion */
    this->ui->Recursion_Slider->setValue(6);

    /* Set-Up Axium */
    this->ui->Axium_Entry->clear();
    this->ui->Axium_Entry->insert("!(0.005)A(1,1)");

    /* Set-Up Production Rules */
    this->ui->Rule1_Pre->clear();
    this->ui->Rule1_Pre->insert("A(l,w)");
    this->ui->Rule1_Suc->clear();
    this->ui->Rule1_Suc->insert("F(l/2)-(d)[[A(l/2,w)]+(d)A(l/2,w)]+(d)F(l/2)[+(d)F(l/2)A(l/2,w)]-(d)A(l/2,w)");
    this->ui->Rule2_Box->clicked(true);
    this->ui->Rule2_Box->setChecked(true);
    this->ui->Rule2_Pre->clear();
    this->ui->Rule2_Pre->insert("F(l)");
    this->ui->Rule2_Suc->clear();
    this->ui->Rule2_Suc->insert("F(l/2)F(l/2)");
    this->ui->Rule3_Box->clicked(false);
    this->ui->Rule3_Box->setChecked(false);
    this->ui->Rule3_Pre->clear();
    this->ui->Rule3_Suc->clear();
    this->ui->Rule4_Box->clicked(false);
    this->ui->Rule4_Box->setChecked(false);
    this->ui->Rule4_Pre->clear();
    this->ui->Rule4_Suc->clear();
    this->ui->Rule5_Box->clicked(false);
    this->ui->Rule5_Box->setChecked(false);
    this->ui->Rule5_Pre->clear();
    this->ui->Rule5_Suc->clear();
    this->ui->Rule6_Box->clicked(false);
    this->ui->Rule6_Box->setChecked(false);
    this->ui->Rule6_Pre->clear();
    this->ui->Rule6_Suc->clear();

}

void MainWindow::on_Output_Button_pressed()
{
    ui->Output_Text->clear();
    std::stringstream output_text;

    for(auto X : ui->GL->L_sys.Modules){

        switch(X->type()){
        case 'F':
            output_text << "F(" << X->value1() << ")";
            break;
        case 'f':
            output_text << "f(" << X->value1() << ")";
            break;
        case '+':
            output_text << "+(" << X->value1() << ")";
            break;
        case '-':
            output_text << "-(" << X->value1() << ")";
            break;
        case '^':
            output_text << "^(" << X->value1() << ")";
            break;
        case '&':
            output_text << "&(" << X->value1() << ")";
            break;
        case '$':
            output_text << "$";
            break;
        case '<':
            output_text << "<(" << X->value1() << ")";
            break;
        case '>':
            output_text << ">(" << X->value1() << ")";
            break;
        case '[':
            output_text << "[";
            break;
        case ']':
            output_text << "]";
            break;
        case '!':
            output_text << "!(" << X->value1() << ")";
            break;
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'G': case 'H': case 'I':
        case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q':
        case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y':
        case 'Z':
            output_text << X->type() << "(" << X->value1() << "," << X->value2() << ")";
            break;
        }
    }

    ui->Output_Text->insertPlainText(QString::fromStdString(output_text.str()));
}

void MainWindow::on_Export_Button_pressed()
{
    /* Open File */
    QString filter = "Text File (*.txt)";
    QString file_name = QFileDialog::getSaveFileName(this, "Choose save file", QDir::homePath(), filter);
    QFile o_file(file_name);

    if(!o_file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Error:", "Save file not valid.");
    }


    /* Write to File */
    QTextStream os(&o_file);

    // Recursion Value
    os << "n = " << ui->Recursion_Val->text() << "\n\n";
    // User Defines
    if(ui->Def1_Box->isChecked())
        os << "#define " << ui->Def1_Char->text() << " " << ui->Def1_Value->text() << "\t /* " << ui->Def1_Comment->text() << " */\n";
    if(ui->Def2_Box->isChecked())
        os << "#define " << ui->Def2_Char->text() << " " << ui->Def2_Value->text() << "\t /* " << ui->Def2_Comment->text() << " */\n";
    if(ui->Def3_Box->isChecked())
        os << "#define " << ui->Def3_Char->text() << " " << ui->Def3_Value->text() << "\t /* " << ui->Def3_Comment->text() << " */\n";
    if(ui->Def4_Box->isChecked())
        os << "#define " << ui->Def4_Char->text() << " " << ui->Def4_Value->text() << "\t /* " << ui->Def4_Comment->text() << " */\n";
    if(ui->Def5_Box->isChecked())
        os << "#define " << ui->Def5_Char->text() << " " << ui->Def5_Value->text() << "\t /* " << ui->Def5_Comment->text() << " */\n";
    if(ui->Def6_Box->isChecked())
        os << "#define " << ui->Def6_Char->text() << " " << ui->Def6_Value->text() << "\t /* " << ui->Def6_Comment->text() << " */\n";
    os << "\n";
    // Axium
    os << "w  : " << ui->Axium_Entry->text() << "\n";
    // Production Rules
    os << "p1 : " << ui->Rule1_Pre->text() << " : --> " << ui->Rule1_Suc->text() << "\n";
    if(ui->Rule2_Box->isChecked())
        os << "p2 : " << ui->Rule2_Pre->text() << " : --> " << ui->Rule2_Suc->text() << "\n";
    if(ui->Rule3_Box->isChecked())
        os << "p3 : " << ui->Rule3_Pre->text() << " : --> " << ui->Rule3_Suc->text() << "\n";
    if(ui->Rule4_Box->isChecked())
        os << "p4 : " << ui->Rule4_Pre->text() << " : --> " << ui->Rule4_Suc->text() << "\n";
    if(ui->Rule5_Box->isChecked())
        os << "p5 : " << ui->Rule5_Pre->text() << " : --> " << ui->Rule5_Suc->text() << "\n";
    if(ui->Rule6_Box->isChecked())
        os << "p6 : " << ui->Rule6_Pre->text() << " : --> " << ui->Rule6_Suc->text() << "\n";

    /* Clean Up */
    o_file.flush();
    o_file.close();

}
