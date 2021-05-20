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
};

class Terrain_disp
{
private:
public:
    int x;
    int y;
    QPixmap tile_pic;
    QPixmap num_pic;
    void display(MainWindow *win);
    Terrain_disp(int i);
};





