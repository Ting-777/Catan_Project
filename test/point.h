#ifndef POINT_H
#define POINT_H
#include <vector>
#include "player_enum.h"
#include "house_enum.h"
using namespace std;
class Point
{
private:
    int index_for_point;
    vector<int> index_for_neighbour_terrain;
    vector<int> index_for_neighbour_point;
    vector<int> direction_able_to_counstruct_road;
    vector<int> direction_already_with_road;
    vector<player_type>owner_of_this_point;
    bool can_build_house_here;
    bool already_house_here;
    house_type house_type_here;
public:
    Point(int i);

    int get_index_for_point();

    vector<int>get_index_for_neighbour_terrain();

    vector<int>get_index_for_neighbour_point();

    vector<int>get_direction_able_to_counstruct_road();

    void set_direction_able_to_counstruct_road(int direction_to_delete);

    vector<int>get_direction_already_with_road();

    void set_direction_already_with_road(int direction_to_add);

    vector<player_type>get_owner_of_this_point();

    void set_owner_of_this_point(player_type new_occupier);

    bool get_can_build_house_here();

    void set_can_build_house_here(bool has_built);

    bool get_already_house_here();

    void set_already_house_here(bool has_built);

    house_type get_house_type_here();

    void set_house_type_here(house_type house);
};

#endif // POINT_H
