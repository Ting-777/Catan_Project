#include "point.h"
#include <algorithm>
vector<int>point_x_pos={443,575,707,377,509,641,773,377,509,641,773,311,443,575,707,
                        839,311,443,575,707,839,245,377,509,641,773,905,245,377,509,
                        641,773,905,311,443,575,707,839,311,443,575,707,839,377,509,
                        641,773,377,509,641,773,443,575,707};
vector<int>point_y_pos={91,91,91,128,128,128,128,206,206,206,206,243,243,243,243,243,
                        321,321,321,321,321,358,358,358,358,358,358,436,436,436,436,
                        436,436,473,473,473,473,473,551,551,551,551,551,588,588,588,
                        588,666,666,666,666,703,703,703};

vector<vector<int>>points_neighbour_terrain={{0},{1},{2},
                                            {0},{0,1},{1,2},{2},
                                            {0,3},{0,1,4},{1,2,5},{2,6},
                                            {3},{0,3,4},{1,4,5},{2,5,6},{6},
                                            {3,7},{3,4,8},{4,5,9},{5,6,10},{6,11},
                                            {7},{3,7,8},{4,8,9},{5,9,10},{6,10,11},{11},
                                            {7},{7,8,12},{8,9,13},{9,10,14},{10,11,15},{11},
                                            {7,12},{8,12,13},{9,13,14},{10,14,15},{11,15},
                                            {12},{12,13,16},{13,14,17},{14,15,18},{15},
                                            {12,16},{13,16,17},{14,17,18},{15,18},
                                            {16},{16,17},{17,18},{18},
                                            {16},{17},{18}};
vector<vector<int>>points_neighbour_points={{3,4},{4,5},{5,6},
                                             {0,7},{0,1,8},{1,2,9},{2,10},
                                             {3,11,12},{4,12,13},{5,13,14},{6,14,15},
                                             {7,16},{7,8,17},{8,9,18},{9,10,19},{10,20},
                                             {11,21,22},{12,22,23},{13,23,24},{14,24,25},{15,25,26},
                                             {16,27},{16,17,28},{17,18,29},{18,19,30},{19,20,31},{20,32},
                                             {21,33},{22,33,34},{23,34,35},{24,35,36},{25,36,37},{26,37},
                                             {27,28,38},{28,29,39},{29,30,40},{30,31,41},{31,32,42},
                                             {33,43},{34,43,44},{35,44,45},{36,45,46},{37,46},
                                             {38,39,47},{39,40,48},{40,41,49},{41,42,50},
                                             {43,51},{44,51,52},{45,52,53},{46,53},
                                             {47,48},{48,49},{49,50}};
Point::Point(int i)
{
    index_for_point=i;
    index_for_neighbour_point=points_neighbour_points[i];
    index_for_neighbour_terrain=points_neighbour_terrain[i];

    direction_able_to_counstruct_road=points_neighbour_points[i];
    direction_already_with_road={};
    owner_of_this_point={};
    can_build_house_here=true;
    already_house_here=false;
    house_type_here=house_type::no_house;
}

int Point::get_index_for_point()
{
    return index_for_point;
}

vector<int>Point::get_index_for_neighbour_terrain()
{
    return index_for_neighbour_terrain;
}

vector<int>Point::get_index_for_neighbour_point()
{
    return index_for_neighbour_point;
}

vector<int>Point::get_direction_able_to_counstruct_road()
{
    return direction_able_to_counstruct_road;
}

void Point::set_direction_able_to_counstruct_road(int direction_to_delete)
{
    auto pos=find(direction_able_to_counstruct_road.begin(),direction_able_to_counstruct_road.end(),direction_to_delete);
    direction_able_to_counstruct_road.erase(pos);
}

vector<int>Point::get_direction_already_with_road()
{
    return direction_already_with_road;
}

void Point::set_direction_already_with_road(int direction_to_add)
{
    direction_already_with_road.push_back(direction_to_add);
}

vector<player_type>Point::get_owner_of_this_point()
{
    return owner_of_this_point;
}

void Point::set_owner_of_this_point(player_type new_occupier)
{
    owner_of_this_point.push_back(new_occupier);
}

bool Point::get_can_build_house_here()
{
    return can_build_house_here;
}

void Point::set_can_build_house_here(bool has_built)
{
    if(has_built)can_build_house_here=false;
}

bool Point::get_already_house_here()
{
    return already_house_here;
}

void Point::set_already_house_here(bool has_built)
{
    if(has_built)already_house_here=true;
}

house_type Point::get_house_type_here()
{
    return house_type_here;
}

void Point::set_house_type_here(house_type house)
{
    house_type_here=house;
}

