#include "net.hpp"

std::vector<NutBlast_ID> player_ids() {
    std::vector<NutBlast_ID> ids;

    for (auto ptr = NutBlast_GetPlayerIDs(); *ptr; ptr++)
        ids.emplace_back(*ptr);

    return ids;
}
