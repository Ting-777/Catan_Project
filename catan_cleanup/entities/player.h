#ifndef PLAYER_H
#define PLAYER_H
#include "player_enum.h"
#include "construction_enum.h"
#include "terrain.h"
#include <map>
#include "point.h"
#include "road.h"
#include <set>
#include "construction_enum.h"
class Player
{
public:
    Player(enum player_type p_type);
    void add_road(int index_of_road);
    void add_point(int index_of_point);
    void add_small_house(int index_of_point);
    void enhance_from_small_to_big(int index_of_point);
    int caculate_road_length();//还没有实现，需要road类
    int caculate_score();
    void set_is_longest(bool longest);
    set<int> get_occupied_points();
    int get_score();
    int dfs(int point_index, set<int> unvisited_road);
    int get_road_length();
    map<constructon,int>get_constructions_remained();
    map<Terrain_type,int> get_owned_sources();
private:
    enum player_type type;
    set<int>occupied_point;//记录占领的点
    vector<int>small_house_owned;//记录建的小房子的点的索引
    vector<int>big_house_owned;//记录建的大房子的点的索引
    set<int>occupied_road;//记录占领的路
    map<Terrain_type,int>sources_owned;//记录玩家手上的资源
    map<constructon,int>constructions_remained;//记录玩家剩余的可建建筑数
    int road_length;//记录已建的最长道路长度
    bool is_longest;
    int score;
signals:

public slots:
    void get_sources(int dice_point);//获取资源槽函数，接收dice信号的点数参数
    void consume_sources(map<Terrain_type,int>source_to_get);//消耗资源槽函数，接收construct信号的资源消耗参数
    void consume_constructions(enum constructon facility);
    void exchange_sources(map<Terrain_type,int>give_out,map<Terrain_type,int>get_in);
};

#endif // PLAYER_H
