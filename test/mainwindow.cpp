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
#include <QLabel>
#include <QDebug>
#include "construction_button.h"
#include "construction_enum.h"
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
    this->setFixedSize(QSize(1508,914));
    setWindowTitle("Catan");
    //显示背景(蓝色海洋)
    QGraphicsScene* bkscene=new QGraphicsScene(this);
    bkscene->addPixmap(QPixmap(":/background/picture_sources/background/background.png"));
    QGraphicsView* bkview=new QGraphicsView(this);
    bkview->resize(1508,914);
    bkview->move(0,0);
    bkview->setStyleSheet("padding:0px;border:0px;background: transparent");
    bkview->setScene(bkscene);
    bkview->show();

    //资源显示背景
    QGraphicsScene* source_bk=new QGraphicsScene(this);
    source_bk->addPixmap(QPixmap(":/player_related/picture_sources/player_related/bg_section2.png"));
    QGraphicsView* source_view=new QGraphicsView(this);
    source_view->resize(610,92);
    source_view->move(0,802);
    source_view->setStyleSheet("padding:0px;border:0px;background: transparent");
    source_view->setScene(source_bk);
    source_view->show();

    //资源卡显示
    vector<QGraphicsScene*>source_card_scene;
    vector<QGraphicsView*>source_card_view;
    vector<QLabel*>source_card_corner;
    vector<QLabel*>source_card_number;
    vector<int>source_card_scene_x_pos{90,180,270,360,450};
    for(int temp=0;temp<5;temp++)
    {
        QString temp_str;
        switch (temp) {
        case 0:
            temp_str=":/card/picture_sources/card/card_lumber.png";
            break;
        case 1:
            temp_str=":/card/picture_sources/card/card_grain.png";
            break;
        case 2:
            temp_str=":/card/picture_sources/card/card_brick.png";
            break;
        case 3:
            temp_str=":/card/picture_sources/card/card_wool.png";
            break;
        case 4:
            temp_str=":/card/picture_sources/card/card_ore.png";
            break;
        }
        QGraphicsScene* card=new QGraphicsScene(this);
        card->addPixmap(QPixmap(temp_str));
        QGraphicsView* view=new QGraphicsView(this);
        view->resize(60,84);
        view->move(source_card_scene_x_pos[temp],802);
        view->setStyleSheet("padding:0px;border:0px;background: transparent");
        view->setScene(card);
        view->scale(0.2,0.2);
        view->show();
        source_card_scene.push_back(card);
        source_card_view.push_back(view);
        QLabel* corner_label=new QLabel(this);
        corner_label->resize(28,28);
        QPixmap source_corner(":/player_related/picture_sources/player_related/button_badge_background_blue.png");
        source_corner=source_corner.scaled(28,28);
        corner_label->setPixmap(source_corner);
        corner_label->move(source_card_scene_x_pos[temp]+30,802);
        source_card_corner.push_back(corner_label);
        QLabel* number_label=new QLabel(this);
        number_label->resize(28,28);
        QFont ft("Microsoft YaHei", 10);
        ft.setBold(true);
        number_label->setFont(ft);
        number_label->setText("13");
        number_label->setStyleSheet("color:white;");
        number_label->move(source_card_scene_x_pos[temp]+35,802);
        number_label->show();
        source_card_number.push_back(number_label);
    }

    //玩家面板显示
    vector<int>player_panel_ypos{758,626,494};
    vector<QLabel*>score_labels;
    vector<QLabel*>rescard_number_labels;
    vector<QLabel*>longest_road_number_labels;
    for(int temp=0;temp<3;temp++)
    {
        QString temp_str;
        switch (temp) {
        case 0:
            temp_str=":/player_related/picture_sources/player_related/player_bg_red.png";
            break;
        case 1:
            temp_str=":/player_related/picture_sources/player_related/player_bg_blue.png";
            break;
        case 2:
            temp_str=":/player_related/picture_sources/player_related/player_bg_green.png";
            break;
        }
        QLabel* bk_label=new QLabel(this);//背景板（白色渐变的圆角矩形）
        bk_label->resize(355,127);
        QPixmap bk_pic(":/player_related/picture_sources/player_related/bg_section1.png");
        bk_pic=bk_pic.scaled(355,127);
        bk_label->setPixmap(bk_pic);
        bk_label->move(1148,player_panel_ypos[temp]);

        QLabel* circle_label=new QLabel(this);//玩家头像圆圈（红绿蓝）
        circle_label->resize(75,75);
        QPixmap circle_pic(temp_str);
        circle_pic=circle_pic.scaled(75,75);
        circle_label->setPixmap(circle_pic);
        circle_label->move(1170,player_panel_ypos[temp]+32);

        QLabel* man_label=new QLabel(this);//玩家头像（小人）
        man_label->resize(75,75);
        QPixmap man_pic(":/player_related/picture_sources/player_related/icon_player.png");
        man_pic=man_pic.scaled(75,75);
        man_label->setPixmap(man_pic);
        man_label->move(1170,player_panel_ypos[temp]+32);

        QLabel* ribbon_label=new QLabel(this);//玩家得分背景栏（绸缎）
        ribbon_label->resize(75,21);
        QPixmap ribbon_pic(":/player_related/picture_sources/player_related/ribbon_small.png");
        ribbon_pic=ribbon_pic.scaled(75,21);
        ribbon_label->setPixmap(ribbon_pic);
        ribbon_label->move(1172,player_panel_ypos[temp]+99);

        QLabel* score_label=new QLabel(this);//玩家分数显示栏
        score_label->resize(75,21);
        score_label->move(1172,player_panel_ypos[temp]+99);
        QFont ft("Microsoft YaHei", 10);
        ft.setBold(true);
        score_label->setFont(ft);
        score_label->setAlignment(Qt::AlignCenter);
        score_label->setText("0");
        score_labels.push_back(score_label);

        QLabel* rescard_label=new QLabel(this);//玩家手上牌数栏
        QPixmap rescard_pic(":/player_related/picture_sources/player_related/card_rescardback.png");
        rescard_pic=rescard_pic.scaled(74,103);
        rescard_label->resize(74,103);
        rescard_label->setPixmap(rescard_pic);
        rescard_label->move(1267,player_panel_ypos[temp]+13);

        QLabel* rescard_corner=new QLabel(this);
        QPixmap rescard_corner_pic(":/player_related/picture_sources/player_related/card_badge_background.png");
        rescard_corner_pic=rescard_corner_pic.scaled(37,37);
        rescard_corner->resize(37,37);
        rescard_corner->setPixmap(rescard_corner_pic);
        rescard_corner->move(1304,player_panel_ypos[temp]+13);

        QLabel* rescard_number_label=new QLabel(this);
        rescard_number_label->resize(37,37);
        rescard_number_label->move(1308,player_panel_ypos[temp]+13);
        rescard_number_label->setFont(ft);
        rescard_number_label->setAlignment(Qt::AlignCenter);
        rescard_number_label->setStyleSheet("color:white;");
        rescard_number_label->setText("0");
        rescard_number_labels.push_back(rescard_number_label);

        QLabel* longest_road_label=new QLabel(this);
        QPixmap longest_road_pic(":/player_related/picture_sources/player_related/icon_longest_road.png");
        longest_road_pic=longest_road_pic.scaled(100,100);
        longest_road_label->resize(100,100);
        longest_road_label->setPixmap(longest_road_pic);
        longest_road_label->move(1361,player_panel_ypos[temp]+13);

        QLabel* longest_road_number_label=new QLabel(this);
        longest_road_number_label->resize(100,21);
        longest_road_number_label->move(1361,player_panel_ypos[temp]+97);
        longest_road_number_label->setFont(ft);
        longest_road_number_label->setAlignment(Qt::AlignCenter);
        longest_road_number_label->setText("0");
        longest_road_number_labels.push_back(longest_road_number_label);
    }

    //显示terrain
    for(int i = 0; i < 19; i++)
        terrain_disps[i].display(this);

    //建筑按钮
    Construction_button* buildroad=new Construction_button(constructon::road,this);
    Construction_button* build_small_house=new Construction_button(constructon::small_house,this);
    Construction_button* build_big_house=new Construction_button(constructon::big_house,this);
    buildroad->show();
    build_big_house->show();
    build_small_house->show();

    //显示Point相关
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
        connect(build_small_house,&QPushButton::clicked,temp_disp,[temp_disp,build_small_house](){current_player_state=player_state::is_building_small_house;
            temp_disp->display_befor_decide();
            disconnect(build_small_house,0,temp_disp,0);
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

