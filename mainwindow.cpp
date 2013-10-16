#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector3D>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <iostream>
#include <cmath>
#include <ctime>

#include <QMatrix4x4>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ExitButton_clicked()
{
    exit(0);
}

double minval;
double maxval;
double calc(double x, double y) {
    return x * x - y * y;
}
QColor getColor(double val) {
    val = (val - minval) / max(0.1, maxval - minval);
    if (val < 0.45) {
        val = val / 0.45;
        return QColor((int)((1 - val) * 0 + val * 0),
                      (int)((1 - val) * 0 + val * 140),
                      (int)((1 - val) * 128 + val * 240));
    } else
    if (val < 0.55) {
        val = (val - 0.45) / 0.1;
        return QColor((int)((1 - val) * 0 + val * 0),
                      (int)((1 - val) * 140 + val * 255),
                      (int)((1 - val) * 240 + val * 0));
    } else {
        val = (val - 0.55) / 0.45;
        return QColor((int)((1 - sqrt(val)) * 0 + sqrt(val) * 144),
                      (int)((1 - sqrt(val)) * 255 + sqrt(val) * 77),
                      (int)((1 - sqrt(val)) * 0 + sqrt(val) * 48));
    }
}
QMatrix4x4 camera, rot, rot1;
QVector3D eye, cent;
void print(QVector4D p) {
    cout<<p.x()<<" "<<p.y()<<" "<<p.z()<<" "<<p.w()<<endl;
}
/*QPoint transf(QVector4D a) {
    a = camera.map(a);
    a /= a.w();
    a /= a.z();
    a.setX(-a.x());
    a *= 100;
    return a.toPoint();
}*/

void addTriangle(vector<pair<pair<double, QColor>, QPolygon> >& list, QVector4D a, QVector4D b, QVector4D c, int type) {
    /*a = rot.map(a);
    b = rot.map(b);
    c = rot.map(c);*/

    QColor color = getColor((a.z() + b.z() + c.z()) / 3);
    if (type == 1) {
        color = Qt::cyan;
    } else
    if (type == 2) {
        color = Qt::magenta;
    } else
    if (type == 3) {
        color = Qt::yellow;
    }

    /*cout<<"Before"<<endl;
    print(a);
    print(b);
    print(c);
    cout<<"After"<<endl;*/
    a = camera.map(a);
    b = camera.map(b);
    c = camera.map(c);
    a /= a.w();
    b /= b.w();
    c /= c.w();
    double h = -(a.z() + b.z() + c.z()) / 3;
    if (a.z() > 0 || b.z() > 0 || c.z() > 0) return;
    if (true) {
        a /= a.z();
        b /= b.z();
        c /= c.z();
    } else {
        a *= -1;
        b *= -1;
        c *= -1;
    }
    a.setX(-a.x());
    b.setX(-b.x());
    c.setX(-c.x());
    a *= 300;
    b *= 300;
    c *= 300;

/*    print(a);
    print(b);
    print(c);
    cout<<"--"<<endl;*/

    QPolygon poly;
    poly << a.toPoint() << b.toPoint() << c.toPoint();
    list.push_back(make_pair(make_pair(h, color), poly));
}
bool comp(const pair<pair<double, QColor>, QPolygon>& a, const pair<pair<double,QColor>, QPolygon>& b) {
    return a.first.first < b.first.first;
}
double** val;
double dx;
double dy;
int nxmax;
int nymax;
double minx;
double maxx;
double miny;
double maxy;
QGraphicsScene *scene;
double tim;
void Draw() {
    tim = clock() * 1./ CLOCKS_PER_SEC;
    scene->clear();
    //scene->addRect(-1000,-1000,1000, 1000, QPen(Qt::white), QBrush(Qt::white));
    //scene->addEllipse(-10,-10,20, 20, QPen(Qt::black), QBrush(Qt::red));
    camera.setToIdentity();
    camera.lookAt(eye, cent, QVector3D(0, 0, 1));
    vector<pair<pair<double,QColor>, QPolygon> > list;
    for (int i = 0; i < nxmax; ++i) {
        for (int j = 0; j < nymax; ++j) {
            addTriangle(list,  QVector4D(minx + dx * i, miny + dy * j, val[i][j], 1),
                               QVector4D(minx + dx * (i + 1), miny + dy * j, val[i + 1][j], 1),
                               QVector4D(minx + dx * (i + 1), miny + dy * (j + 1), val[i + 1][j + 1], 1), 0);
            addTriangle(list,  QVector4D(minx + dx * i, miny + dy * j, val[i][j], 1),
                               QVector4D(minx + dx * i, miny + dy * (j + 1), val[i][j + 1], 1),
                               QVector4D(minx + dx * (i + 1), miny + dy * (j + 1), val[i + 1][j + 1], 1), 0);
        }
    }
    for (int i = 0; i < nxmax; i++) {
        addTriangle(list,  QVector4D(minx + dx * i, miny, minval, 1),
                           QVector4D(minx + dx * (i + 0.5), miny, minval, 1),
                           QVector4D(minx + dx * (i + 1), miny, minval, 1), 1);
    }
    for (int i = 0; i < nymax; i++) {
        addTriangle(list,  QVector4D(minx, miny + dy * i, minval, 1),
                           QVector4D(minx, miny + dy * (i + 0.5), minval, 1),
                           QVector4D(minx, miny +  dy * (i + 1), minval, 1), 2);
    }
    int nzmax = max(nxmax, nymax);
    double dz = (maxval - minval) / (nzmax);
    for (int i = 0; i < nzmax; i++) {
        addTriangle(list,  QVector4D(minx, miny, minval + i * dz, 1),
                           QVector4D(minx, miny, minval + (i + 0.5) * dz, 1),
                           QVector4D(minx, miny, minval + (i + 1) * dz, 1), 3);
    }
   /* addTriangle(list,  QVector4D(minx, (miny + maxy) / 2, (minval + maxval) / 2, 1),
                       QVector4D((minx + maxx) / 2, (miny + maxy) / 2, (minval + maxval) / 2, 1),
                       QVector4D(maxx, (miny + maxy) / 2, (minval + maxval) / 2, 1), 1);
    addTriangle(list,  QVector4D((minx + maxx) / 2, miny, (minval + maxval) / 2, 1),
                       QVector4D((minx + maxx) / 2, (miny + maxy) / 2, (minval + maxval) / 2, 1),
                       QVector4D((minx + maxx) / 2, maxy, (minval + maxval) / 2, 1), 2);
    addTriangle(list,  QVector4D((minx + maxx) / 2, (miny + maxy) / 2, minval, 1),
                       QVector4D((minx + maxx) / 2, (miny + maxy) / 2, (minval + maxval) / 2, 1),
                       QVector4D((minx + maxx) / 2, (miny + maxy) / 2, maxval, 1), 3);*/
    sort(list.begin(), list.end(), comp);
    QPen pen(Qt::transparent);
    QBrush brush(Qt::green);
    //cerr<<(int)list.size()<<endl;
    for (int i = (int)list.size() - 1; i >= 0; --i) {
        if (list[i].first.first <= 1) break;
        if (list[i].first.second != Qt::cyan && list[i].first.second != Qt::magenta && list[i].first.second != Qt::yellow) {
            brush.setColor(list[i].first.second);
            scene->addPolygon(list[i].second, pen, brush);
        } else {
            pen.setColor(list[i].first.second);
            scene->addPolygon(list[i].second, pen);
            pen.setColor(Qt::transparent);
        }
    }

    scene->update();
    cerr<<(clock() * 1./ CLOCKS_PER_SEC - tim)<<endl;
}


double alp = acos(-1.) / 12.;

void MainWindow::init() {

    scene = new QGraphicsScene(ui->graphicsView);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(400, 400);
    //scene->setSceneRect(0, 0, 100, 100);

    minx = -1;
    maxx = 1;
    miny = -1;
    maxy = 1;
    nxmax = 50;
    nymax = 50;
    dx = (maxx - minx) / nxmax;
    dy = (maxy - miny) / nymax;
    val = new double*[nxmax + 1];
    for (int i = 0; i <= nxmax; ++i) {
        val[i] = new double[nymax + 1];
    }
    minval = 1e9;
    maxval = -1e9;
    for (int i = 0; i <= nxmax; ++i) {
        for (int j = 0; j <= nymax; ++j) {
            val[i][j] = calc(minx + dx * i, miny + dy * j);
            minval = min(minval, val[i][j]);
            maxval = max(maxval, val[i][j]);
        }
    }
    if (fabs(minval - maxval) < 1e-3) {
            maxval = minval + 1;
            minval = minval - 1;
    }
    cent = QVector3D((maxx + minx) / 2, (maxy + miny) / 2, (maxval + minval) / 2);
    eye = cent;
    eye.setY(eye.y() - 4 * (maxx - minx) / 2);
    /*rot.setToIdentity();
    rot1.setToIdentity();
    rot1.setColumn(0, QVector4D(cos(alp), sin(alp), 0, 0));
    rot1.setColumn(1, QVector4D(-sin(alp), cos(alp), 0, 0));*/
    Draw();
}


void MainWindow::on_pushButton_2_clicked()
{
    eye = QVector3D(eye.x() * cos(alp) - eye.y() * sin(alp),
                    eye.x() * sin(alp) + eye.y() * cos(alp),
                    eye.z());
    //rot *= rot1;
    Draw();
}


void MainWindow::on_pushButton_3_clicked()
{
    eye = QVector3D(eye.x() * cos(alp) + eye.y() * sin(alp),
                   -eye.x() * sin(alp) + eye.y() * cos(alp),
                    eye.z());
    //rot *= rot1.inverted();
    Draw();
}

void MainWindow::on_pushButton_5_clicked()
{
    eye.setZ(eye.z() + (maxval - minval) / 10);
    Draw();
}

void MainWindow::on_pushButton_4_clicked()
{
    eye.setZ(eye.z() - (maxval - minval) / 10);
    Draw();
}
