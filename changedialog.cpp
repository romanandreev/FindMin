#include "changedialog.h"

changeDialog::changeDialog(FunctionAndLimits* FL, DrawWidget* dw):FL(FL), dw(dw)
{
    this->setWindowTitle("Change function");


    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *text1 = new QLabel("<b>Enter new function:</b>");
    str1 = new QLineEdit;
    QString ss = FL->F->name.c_str();
    str1->setText(ss);

    QLabel *text2 = new QLabel("<b>Enter new min x:</b>");
    str2 = new QLineEdit;
    ss.setNum(FL->l0[0]);
    str2->setText(ss);

    QLabel *text3 = new QLabel("<b>Enter new min y:</b>");
    str3 = new QLineEdit;
    ss.setNum(FL->l0[1]);
    str3->setText(ss);

    QLabel *text4 = new QLabel("<b>Enter new max x:</b>");
    str4 = new QLineEdit;
    ss.setNum(FL->r0[0]);
    str4->setText(ss);

    QLabel *text5 = new QLabel("<b>Enter new max y:</b>");
    str5 = new QLineEdit;
    ss.setNum(FL->r0[1]);
    str5->setText(ss);

    QPushButton *button = new QPushButton;
    button->setText("Apply");
    layout->addWidget(text1);
    layout->addWidget(str1);
    layout->addWidget(text2);
    layout->addWidget(str2);
    layout->addWidget(text3);
    layout->addWidget(str3);
    layout->addWidget(text4);
    layout->addWidget(str4);
    layout->addWidget(text5);
    layout->addWidget(str5);
    layout->addWidget(button);

    central->setLayout(layout);
    this->setCentralWidget(central);

    connect(button, SIGNAL(pressed()), this, SLOT(pressed()));
}

void changeDialog::pressed() {
    int res = Expression::good(str1->text().toStdString());
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
    }
}
