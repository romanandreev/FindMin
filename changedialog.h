#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <drawwidget.h>
#include <functionandlimits.h>
#include <expression.h>
class changeDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit changeDialog(FunctionAndLimits*, DrawWidget*);

signals:

public slots:
    void pressed();

private:
    QLineEdit * str1, *str2, *str3, *str4, *str5;
    FunctionAndLimits* FL;
    DrawWidget* dw;
};

#endif // CHANGEDIALOG_H
