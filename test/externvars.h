#pragma once
#include "terrain.h"
#include "point.h"
#include "player_enum.h"
#include "player_state_enum.h"
#include "point_disp.h"
#include <QGraphicsView>
#include <QGraphicsScene>
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
extern player_type current_player;
extern player_state current_player_state;
extern vector<QGraphicsView*>points_view;
extern vector<QGraphicsScene*>points_scene;
