#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "terrain.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <QPushButton>
#include "point.h"
#include "point_disp.h"
#include "player_enum.h"
#include "player_state_enum.h"
using namespace std;

extern vector<Terrain_type> types;
extern vector<int> numbers;
extern vector<int> xs;
extern vector<int> ys;
extern vector<Terrain> terrains;
extern vector<Terrain_disp> terrain_disps;
vector<Point> points;
vector<Point_disp*>points_disp;
extern vector<int>point_x_pos;
extern vector<int>point_y_pos;
extern vector<vector<int>>points_neighbour_points;
extern vector<vector<int>>points_neighbour_terrain;
extern player_type current_player;
extern player_state current_player_state;
vector<QGraphicsView*>points_view;
vector<QGraphicsScene*>points_scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setMinimumSize(1508, 914);
    for(int i = 0; i < 19; i++)
        terrain_disps[i].display(this);

    QPushButton* build_house=new QPushButton(this);
    build_house->resize(100,100);
    build_house->move(697,802);
    build_house->setText("build small house");
    build_house->show();
    for(int temp=0;temp<54;temp++)
    {
       QGraphicsScene* p_scene=new QGraphicsScene(this);
       QGraphicsView* p_view=new QGraphicsView(this);
       p_view->resize(48,48);
       p_view->move(point_x_pos[temp]-24,point_y_pos[temp]-24);
       p_view->setStyleSheet("padding:0px;border:0px;background: transparent");
       p_view->setScene(p_scene);
       p_view->scale(0.375,0.375);
       p_view->show();
       points_view.push_back(p_view);
       points_scene.push_back(p_scene);
    }
    for(int i=0;i<54;i++)
    {
        Point p=Point(i);
        points.push_back(p);
        Point_disp* p_disp=new Point_disp(i,this);
        points_disp.push_back(p_disp);
    }
    for(int temp=0;temp<54;temp++)
    {
        Point_disp* temp_disp=points_disp[temp];
        connect(build_house,&QPushButton::clicked,temp_disp,[temp_disp,build_house](){current_player_state=player_state::is_building_small_house;
            temp_disp->display_befor_decide();
            disconnect(build_house,0,temp_disp,0);
            connect(temp_disp,&Point_disp::clicked,[temp_disp](){temp_disp->send_build_small_house_signal();});
        });
    }
    for(int temp=0;temp<54;temp++)
    {
        for(int temp1=0;temp1<54;temp1++)
        {
            Point_disp* p1=points_disp[temp];
            Point_disp* p2=points_disp[temp1];
            connect(p1,SIGNAL(has_built_small_house(int)),p2,SLOT(display_after_decide(int)));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

