#include "player.h"
#include <iostream>
extern vector<Point> points;
extern vector<Road> roads;
extern vector<Terrain> terrains;
Player::Player(enum player_type p_type)
{
    type=p_type;
    occupied_point={};
    occupied_road={};
    small_house_owned={};
    big_house_owned={};
    sources_owned={{Terrain_type::lumber,0},{Terrain_type::wool,0},{Terrain_type::brick,0},{Terrain_type::grain,0},{Terrain_type::ore,0}};
    constructions_remained={{constructon::road,15},{constructon::small_house,5},{constructon::big_house,4}};
    road_length=0;
    is_longest=false;
    score=0;
}

set<int> Player:: get_occupied_points()
{
    return occupied_point;
}

void Player::add_road(int index_of_road)
{
    occupied_road.insert(index_of_road);
}

void Player::add_point(int index_of_point)
{
    occupied_point.insert(index_of_point);
}

void Player::add_small_house(int index_of_point)
{
    small_house_owned.push_back(index_of_point);
}

void Player::enhance_from_small_to_big(int index_of_point)
{
    auto pos=find(small_house_owned.begin(),small_house_owned.end(),index_of_point);
    small_house_owned.erase(pos);
    big_house_owned.push_back(index_of_point);
}

int Player::caculate_score()
{
    int temp_score=0;
    temp_score+=small_house_owned.size()+big_house_owned.size()*2;
    if(is_longest)temp_score+=2;
    score=temp_score;
    return score;
}

int Player::dfs(int point_index, set<int> unvisited_road)
{


    if (points[point_index].get_already_house_here() && find(small_house_owned.begin(),small_house_owned.end(),point_index)== small_house_owned.end()
           && find(big_house_owned.begin(),big_house_owned.end(),point_index)== big_house_owned.end())
        return 0;
    if (unvisited_road.empty())
            return 0;

    int cmax = 0;
    vector<int> initial_loop_roads_index = {};
    for(auto neighbour_index : points[point_index].get_index_for_neighbour_point())
    {
         if (find(occupied_point.begin(),occupied_point.end(),neighbour_index)!= occupied_point.end())
         {

             for(auto road_index : occupied_road)
             {

                 vector<int> endpoint = roads[road_index].get_endpoints();

                 if(point_index == endpoint[0] || point_index == endpoint[1])
                 {
                     if(neighbour_index == endpoint[0] || neighbour_index == endpoint[1])
                         initial_loop_roads_index.push_back(road_index);

                 }
             }
         }
    }
    for (auto roads_initial : initial_loop_roads_index)
    {

        if(find(unvisited_road.begin(),unvisited_road.end(),roads_initial)!= unvisited_road.end())
        {
            vector<int> endpoint = roads[roads_initial].get_endpoints();
            int next_point_index = (endpoint[0]!= point_index)?endpoint[0]:endpoint[1];
            auto erase_iter = find(unvisited_road.begin(),unvisited_road.end(),roads_initial);
            int visited_index = *(erase_iter);

            unvisited_road.erase(erase_iter);
            cmax = max(cmax, 1 + dfs(next_point_index,unvisited_road));
           unvisited_road.insert(visited_index);
        }
    }
    return cmax;

}

int Player::caculate_road_length()
{
    if (occupied_road.empty())
        return 0;
    if(occupied_road.size() == 1)
        return 1;

    int road_max = 0;
    for(auto point : occupied_point)
    {

        road_max = max(road_max, dfs(point,occupied_road));
    }
    return road_max;
}

void Player::set_is_longest(bool longest)
{
    if(longest) is_longest=true;
    else is_longest=false;
}

map<Terrain_type,int> Player::get_owned_sources()
{
    return sources_owned;
}

void Player::get_sources(int dice_point)
{
    for(vector<int>::size_type temp=0;temp<small_house_owned.size();temp++)
    {
        vector<int> neibourgh_terrain=points[small_house_owned[temp]].get_index_for_neighbour_terrain();
        for(vector<int>::size_type temp1=0;temp1<neibourgh_terrain.size();temp1++)
        {
            if(terrains[neibourgh_terrain[temp1]].get_source_point()==dice_point)
                sources_owned[terrains[neibourgh_terrain[temp1]].get_terrain_type()]++;
        }
    }
    for(vector<int>::size_type temp=0;temp<big_house_owned.size();temp++)
    {
        vector<int> neibourgh_terrain=points[big_house_owned[temp]].get_index_for_neighbour_terrain();
        for(vector<int>::size_type temp1=0;temp1<neibourgh_terrain.size();temp1++)
        {
            if(terrains[neibourgh_terrain[temp1]].get_source_point()==dice_point)
                sources_owned[terrains[neibourgh_terrain[temp1]].get_terrain_type()]+=2;
        }
    }
}

void Player::consume_sources(map<Terrain_type,int>source_to_pay)
{
    for(auto b=source_to_pay.begin();b!=source_to_pay.end();b++)
    {
        sources_owned[b->first]-=b->second;
    }
}

void Player::consume_constructions(enum constructon facility)
{
    constructions_remained[facility]--;
}

void Player::exchange_sources(map<Terrain_type,int>give_out,map<Terrain_type,int>get_in)
{
    for(auto b=give_out.begin();b!=give_out.end();b++)
    {
        sources_owned[b->first]-=b->second;
    }
    for(auto b=get_in.begin();b!=get_in.end();b++)
    {
        sources_owned[b->first]+=b->second;
    }
}

int Player::get_score()
{
    return score;
}

int Player::get_road_length()
{
    return road_length;
}

map<constructon,int>Player::get_constructions_remained()
{
    return constructions_remained;
}
