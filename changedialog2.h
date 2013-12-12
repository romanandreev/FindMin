#ifndef CHANGEDIALOG2_H
#define CHANGEDIALOG2_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <drawwidget.h>
#include <functionandlimits.h>
#include <expression.h>
class changeDialog2 : public QMainWindow
{
    Q_OBJECT
public:
    explicit changeDialog2(minimization*, DrawWidget*);

signals:

public slots:
    void pressed();

private:
    QLineEdit * str1, *str2, *str3, *str4, *str5;
    minimization* minim;
    DrawWidget* dw;
};

#endif // CHANGEDIALOG2_H
