#include "changedialog2.h"

changeDialog2::changeDialog2(minimization* minim, DrawWidget* dw):minim(minim), dw(dw)
{
    this->setWindowTitle("Change method preferences");


    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *text1 = new QLabel("<b>Enter hill climbing stop epsilon:</b>");
    str1 = new QLineEdit;
    QString ss = "-";
    if (minim->type == 1) {
        ss.setNum(((hill_climbing *) minim)->Seps);
    }
    str1->setText(ss);

    QLabel *text2 = new QLabel("<b>Enter number of iterations of hill climbing:</b>");
    str2 = new QLineEdit;
    ss = "-";
    if (minim->type == 1) {
        ss.setNum(((hill_climbing *) minim)->Fcnt);
    }
    str2->setText(ss);

    QLabel *text3 = new QLabel("<b>Enter random search radius:</b>");
    str3 = new QLineEdit;
    ss = "-";
    if (minim->type == 2) {
        ss.setNum(((random_search *) minim)->rd);
    }
    str3->setText(ss);

    QLabel *text4 = new QLabel("<b>Enter number of iterations of random search:</b>");
    str4 = new QLineEdit;
    ss = "-";
    if (minim->type == 2) {
        ss.setNum(((random_search *) minim)->Fcnt);
    }
    str4->setText(ss);

    QLabel *text5 = new QLabel("<b>Enter random search probability of staying:</b>");
    str5 = new QLineEdit;
    ss = "-";
    if (minim->type == 2) {
        ss.setNum(((random_search *) minim)->prob);
    }
    str5->setText(ss);

    QPushButton *button = new QPushButton;
    button->setText("Apply");
    layout->addWidget(text1);
    layout->addWidget(str1);
    layout->addWidget(text2);
    layout->addWidget(str2);
    layout->addWidget(text4);
    layout->addWidget(str4);
    layout->addWidget(text3);
    layout->addWidget(str3);
    layout->addWidget(text5);
    layout->addWidget(str5);
    layout->addWidget(button);

    central->setLayout(layout);
    this->setCentralWidget(central);

    connect(button, SIGNAL(pressed()), this, SLOT(pressed()));
}

void changeDialog2::pressed() {
    if (minim->type == 1) {
        ((hill_climbing*)minim)->Seps = str1->text().toDouble();
        ((hill_climbing*)minim)->Fcnt = str2->text().toDouble();
    }
    if (minim->type == 2) {
        ((random_search*)minim)->rd = str3->text().toDouble();
        ((random_search*)minim)->Fcnt = str4->text().toDouble();
        ((random_search*)minim)->prob = str5->text().toDouble();
    }
    this->close();
    /*int res = Expression::good(str1->text().toStdString());
    QMessageBox msg;
    msg.setText("Error!");
    QString ss;
    if (res == -1) {
        point p0, p1;
        p0.push_back(str2->text().toDouble());
        p0.push_back(str3->text().toDouble());
        p1.push_back(str4->text().toDouble());
        p1.push_back(str5->text().toDouble());
        FL->l0 = p0;
        FL->r0 = p1;
        FL->F = new Expression(str1->text().toStdString());
        dw->resize(QSize(dw->width() + 1, dw->height() + 1));
        this->close();
    } else {
        ss.setNum(res);
        msg.setInformativeText("Invalid Function, error at character " + ss);
        msg.exec();
    }*/
}
