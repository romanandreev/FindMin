#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include "base.h"
#include "myrand.h"
#include "point.h"
#include "function.h"
#include "expression.h"
#include "minimization.h"
#include "methods.h"
#include "functionandlimits.h"
#include "drawwidget.h"
//#include "changedialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
private slots:
    void about();
    void change_function();
    //void change_method();

signals:
    void changeFName(QString);
private:        
    void init_f();
    FunctionAndLimits *FL;
    minimization *minim;
    DrawWidget *dw;
};

#endif // MAINWINDOW_H
