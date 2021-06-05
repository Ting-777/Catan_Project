#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include "player_enum.h"
#include "player_state_enum.h"

using namespace std;


class Road
{

public:
    explicit Road(int i);
    int get_index_for_road(void) const;
    player_type get_owned_player(void);
    vector<int> get_endpoints(void) const;
    void set_owned_player(player_type occupier);
    bool get_built(void) const;
    void set_built(void);


private:
    int indexForRoad;
    int indexPointEnd1, indexPointEnd2;
    player_type ownedPlayer;
    bool built;



};


#endif // ROAD_H
