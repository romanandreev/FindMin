#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

#include <QMainWindow>
class MainWindow;
class changeDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit changeDialog(MainWindow *parent);

signals:

public slots:
private:
    MainWindow *prev;
};

#endif // CHANGEDIALOG_H
