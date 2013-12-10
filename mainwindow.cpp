#include "mainwindow.h"

MainWindow::MainWindow()
{
    this->setWindowTitle("2D optimization");
    QWidget *central = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *right = new QVBoxLayout;
    QLabel *textC = new QLabel("<b>Current coordinates:</b>");
    QLabel *valC = new QLabel("");
    QLabel *textV = new QLabel("<b>Current value of F:</b>");
    QLabel *valV = new QLabel("");
    QLabel *textF = new QLabel("<b>Current function:</b>");
    QLabel *valF = new QLabel("");

    connect(this, SIGNAL(changeFName(QString)), valF, SLOT(setText(QString)));
   // cerr<<"!!"<<endl;
    init_f();

    DrawWidget *dw = new DrawWidget(FL, minim);

    connect(minim, SIGNAL(getSeg(point, point)), dw, SLOT(drawSeg(point, point)));
    right->setAlignment(Qt::AlignTop);
    right->addWidget(textC);
    right->addWidget(valC);
    right->addWidget(textV);
    right->addWidget(valV);
    right->addWidget(textF);
    right->addWidget(valF);

    valC->setMaximumWidth(max(textC->width(), textV->width()));
    valV->setMaximumWidth(max(textC->width(), textV->width()));

    layout->addWidget(dw);
    layout->addLayout(right);
    central->setLayout(layout);
    this->setCentralWidget(central);
    QMenu *optionsMenu;
    QAction *changeFunction;
    QAction *changeMethod;
    //QAction *changeGraphics;
    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *aboutQtAction;


    changeFunction = new QAction(tr("Change &function"), this);
    changeFunction->setShortcut(QKeySequence(tr("Ctrl+F")));
    connect(changeFunction, SIGNAL(triggered()), this, SLOT(change_function()));

    changeMethod = new QAction(tr("Change &method"), this);
    changeMethod->setShortcut(QKeySequence(tr("Ctrl+M")));
    connect(changeMethod, SIGNAL(triggered()), this, SLOT(change_method()));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);

    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(changeFunction);
    optionsMenu->addAction(changeMethod);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    connect(dw, SIGNAL(mouseChangeC(QString)), valC, SLOT(setText(QString)));
    connect(dw, SIGNAL(mouseChangeV(QString)), valV, SLOT(setText(QString)));

}

void MainWindow::init_f()
{     
    assert(freopen("input.txt", "r", stdin));
    string s;
    getline(cin, s);    
    FL = new FunctionAndLimits;
    FL->F = new Expression(s);
    int n = FL->F->n;
    assert(n == 2);
    FL->l0.clear();
    FL->r0.clear();
    FL->l0.reserve(n);
    FL->r0.reserve(n);
    for (int i = 0; i < n; i++) {
        ld l, r;
        cin >> l >> r;
        FL->l0.push_back(l);
        FL->r0.push_back(r);
    }
    point p0;
    p0.push_back(3);
    p0.push_back(4);

    emit changeFName(QString(FL->F->name.c_str()));
    minim = new hill_climbing(FL->F, FL->l0, FL->r0, p0);

    //point res = minim->minimize();
//    point res = hillClimbingWithArgMin(p0, 1000, 5);
//    point res = ravineMethod(p0, p1, 100, 10);
//    point res = randomSearch(p0, 0.95, 0.01 * (r0[0] - l0[0]));
    //cerr << "F" << res << " = "<< minim->calcF(res) << endl;
  //  cerr<<"!!"<<endl;
    //delete F;
}

void MainWindow::change_function() {
    /*changeDialog change_dialog(this);
    if (change_dialog.exec()) {
        dw->resize(dw->width(), dw->height());
    }*/
}

MainWindow::~MainWindow()
{

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About 2D optimization"),
            tr("<h2>Optimizator 0.5</h2>"
               "<p>Vizualization of several optimization methods."
               "<p>Copyright &copy; 2013 RomanAndreev and Co"));
}
