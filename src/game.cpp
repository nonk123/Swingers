#include <sstream>
#include <unordered_map>
#include <vector>

#include <raylib.h>

#include <NutBlast.h>

#include "game.hpp"
#include "net.hpp"

enum Channel {
    CHAN_POS,
    CHAN_MAX,
};

static const Fixed PHEIGHT = Double2Fx(1.8), PRADIUS = Double2Fx(0.4);

static std::unordered_map<NutBlast_ID, Player> players;
static std::vector<Platform> platforms = {
    {{0.0, -0.5, 0.0}, {5.0, 0.5, 5.0}},
};

void init() {
    NutBlast_SetMaxChannels(CHAN_MAX);

    NutBlast_OnReady(restart);
    NutBlast_OnPlayerJoined([](NutBlast_ID id) { players.insert_or_assign(id, Player(id)); });
}

void restart() {
    players.clear();
    players.insert_or_assign(NutBlast_GetOurID(), Player(NutBlast_GetOurID()));
}

void update() {
    if (players.contains(NutBlast_GetOurID())) {
        auto& us = players.at(NutBlast_GetOurID());

        Vec3 vel(Fx1 * IsKeyDown(KEY_D) - Fx1 * IsKeyDown(KEY_A), Fx0, Fx1 * IsKeyDown(KEY_W) - Fx1 * IsKeyDown(KEY_S));
        vel *= Double2Fx(10.0 / TICKRATE);
        us.pos += vel;

        std::stringstream ss;
        ss << us.pos.x << ":" << us.pos.y << ":" << us.pos.z;
        const auto msg = ss.str();

        for (const auto& id : player_ids())
            NutBlast_SendTo(CHAN_POS, id, msg.c_str(), -1);
    }

    for (NutBlast_Message nb; NutBlast_NextMessage(CHAN_POS, &nb);) {
        if (!players.contains(nb.from))
            continue;

        std::stringstream ss(nb.data);
        char colon = ':';

        auto& player = players.at(nb.from);
        ss >> player.pos.x >> colon >> player.pos.y >> colon >> player.pos.z;
    }
}

void draw() {
    for (const auto& platform : platforms)
        platform.draw();

    for (const auto& [id, player] : players)
        player.draw();
}

void Platform::draw() const {
    draw_cube(pos, dim, RED);
}

void Player::draw() const {
    const auto clr = id == NutBlast_GetOurID() ? BLUE : GREEN;
    DrawCylinder(pos, Fx2Float(PRADIUS), Fx2Float(PRADIUS), Fx2Float(PHEIGHT), 36, clr);
}

void draw_cube(Vec3 pos, Vec3 dim, Color color) {
    DrawCube(pos, Fx2Float(dim.x), Fx2Float(dim.y), Fx2Float(dim.z), color);
}
