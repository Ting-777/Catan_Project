#include "mainwindow.h"
#include "terrain.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <QApplication>
#include "point.h"
#include "point_disp.h"
#include "player_enum.h"
#include "player_state_enum.h"
#include <QSplashScreen>

using namespace std;

extern vector<Terrain_type> types;
extern vector<int> numbers;
extern vector<int> xs;
extern vector<int> ys;
extern vector<Terrain> terrains;
extern vector<Terrain_disp> terrain_disps;
extern vector<Point> points;
extern vector<Point_disp*>points_disp;
extern vector<int>point_x_pos;
extern vector<int>point_y_pos;
extern vector<vector<int>>points_neighbour_points;
extern vector<vector<int>>points_neighbour_terrain;
vector<int>sea_shore_point={0,3,1,5,10,15,26,32,46,42,47,51,52,49,33,38,11,16};
map<Terrain_type,int>sea_shore_trade_condition={{Terrain_type::ore,2},{Terrain_type::ore,2},
                                                {Terrain_type::no_particular_type,3},{Terrain_type::no_particular_type,3},
                                                {Terrain_type::wool,2},{Terrain_type::wool,2},
                                                {Terrain_type::no_particular_type,3},{Terrain_type::no_particular_type,3},
                                                {Terrain_type::no_particular_type,3},{Terrain_type::no_particular_type,3},
                                                {Terrain_type::lumber,2},{Terrain_type::lumber,2},
                                                {Terrain_type::no_particular_type,3},{Terrain_type::no_particular_type,3},
                                                {Terrain_type::brick,2},{Terrain_type::brick,2},
                                                {Terrain_type::grain,2},{Terrain_type::grain,2}};//和上面的sea_shore_point一一对应
player_type current_player=player_type::red_player;
player_state current_player_state=player_state::idle;
int current_player_index=0;
int game_status=0;
bool is_in_normal_round=false;
bool is_sea_shore_mode=false;

int main(int argc, char *argv[])
{
    //qputenv("QT_SCALE_FACTOR", "0.8");





    int currentExitCode = 0;
    do {
     QApplication a(argc, argv);
     QSplashScreen *splash = new QSplashScreen;
     splash->setPixmap(QPixmap(":/firstpage/assets/firstpage/colonist_firstpage.png"));
     splash->show();
     MainWindow w;
     w.show();
     delete splash;
     currentExitCode = a.exec();
    } while( currentExitCode == -123456789 );
    return currentExitCode;
}
