#ifndef PLAYER_H
#define PLAYER_H
#include "player_enum.h"
#include "construction_enum.h"
#include "terrain.h"
#include "road.h"
#include <map>
#include "point.h"
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
    void add_sea_shore_point(int index);
    int caculate_road_length();
    int caculate_score();
    void set_is_longest(bool longest);
    set<int>& get_occupied_points();
    int get_score();
    int get_road_length();
    int get_total_sources();
    bool get_longest();
    int dfs(int point_index, set<int> unvisited_road);
    player_type get_player_type();
    map<constructon,int>get_constructions_remained();
    map<Terrain_type,int> get_owned_sources();
    vector<int>get_small_house_owned();
    vector<int>get_occupied_sea_shore_point();
    void change_trade_with_bank_rules(enum Terrain_type terrain,int num);
    map<Terrain_type,int> get_trade_with_bank_rule();
private:
    enum player_type type;
    set<int>occupied_point;//记录占领的点
    vector<int>small_house_owned;//记录建的小房子的点的索引
    vector<int>big_house_owned;//记录建的大房子的点的索引
    set<int>occupied_road;//记录占领的路
    map<Terrain_type,int>sources_owned;//记录玩家手上的资源
    map<constructon,int>constructions_remained;//记录玩家剩余的可建建筑数
    map<Terrain_type,int>trade_with_bank_rule;
    vector<int>occupied_sea_shore_point;
    int road_length;//记录已建的最长道路长度
    bool is_longest;
    int score;
    int total_sources;
signals:

public slots:
    void get_sources(int dice_point);//获取资源槽函数，接收dice信号的点数参数
    void get_sources(map<Terrain_type,int>sources);
    void consume_sources(map<Terrain_type,int>source_to_get);//消耗资源槽函数，接收construct信号的资源消耗参数
    void consume_constructions(enum constructon facility);
    void exchange_sources(map<Terrain_type,int>give_out,map<Terrain_type,int>get_in);
};

#endif // PLAYER_H
