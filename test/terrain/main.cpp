#include "mainwindow.h"
#include "terrain.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <QApplication>
using namespace std;

extern vector<Terrain_type> types;
extern vector<int> numbers;
extern vector<int> xs;
extern vector<int> ys;
extern vector<Terrain> terrains;
extern vector<Terrain_disp> terrain_disps;

int main(int argc, char *argv[])
{
    unsigned seed = chrono::system_clock::now ().time_since_epoch ().count ();
    shuffle (types.begin (), types.end (), default_random_engine (seed));
    seed = chrono::system_clock::now ().time_since_epoch ().count ();
    shuffle (numbers.begin (), numbers.end (), default_random_engine (seed));
    QApplication a(argc, argv);
    for(int i = 0;i < 19; i++)
    {
        Terrain t = Terrain(i);
        terrains.push_back(t);
        Terrain_disp td = Terrain_disp(i);
        terrain_disps.push_back(td);
    }
    MainWindow w;
    w.show();
    return a.exec();
}
