#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "terrain.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
using namespace std;

extern vector<Terrain_type> types;
extern vector<int> numbers;
extern vector<int> xs;
extern vector<int> ys;
extern vector<Terrain> terrains;
extern vector<Terrain_disp> terrain_disps;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setMinimumSize(1508, 914);
    for(int i = 0; i < 19; i++)
        terrain_disps[i].display(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

