#pragma once
#include "terrain.h"
#include "point.h"
#include "player_enum.h"
#include "player_state_enum.h"
#include "point_disp.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include "player.h"
#include <QLabel>
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
extern vector<QLabel*>source_card_number;//顺序存放lumber grain brick wool ore的资源数QLabel
extern vector<QLabel*>score_labels;//顺序存放red green blue玩家的分数QLabel
extern vector<QLabel*>rescard_number_labels;//顺序存放red green blue玩家的手上资源牌总数QLabel
extern vector<QLabel*>longest_road_number_labels;//顺序存放　red green blue 玩家的路的长度QLabel
extern vector<Player>players;//顺序存放red green blue玩家对象
extern vector<int>current_point_able_to_build_road;
extern vector<int>current_point_able_to_build_small_house;
extern vector<int>current_point_able_to_build_big_house;
