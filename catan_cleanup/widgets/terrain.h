#pragma once
#include "mainwindow.h"
#include <vector>
#include <QPixmap>
using namespace std;

enum class Terrain_type{desert,brick,grain,lumber,ore,wool};

class Terrain
{
private:
    Terrain_type type;
    int number;
public:
    Terrain(int i);
    Terrain_type get_terrain_type();
    int get_source_point();
};

class Terrain_disp
{
private:
    int x;
    int y;
    QPixmap tile_pic;
    QPixmap num_pic;
public:
    void display(MainWindow *win);
    Terrain_disp(int i);
};





