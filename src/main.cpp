#include <cstdlib>
#include <random>
#include <string>

#include <raylib.h>

#include <NutBlast.h>

#include "clock.hpp"
#include "cmake.hpp"
#include "defer.hpp"
#include "game.hpp"
#include "net.hpp"

static void nutblast_raylib_logger(NutBlast_LogLevel level, const char* line) {
    TraceLog(level == NB_LogInfo ? LOG_INFO : LOG_ERROR, "%s", line);
}

Camera3D camera = {
    .position = {-5.f, 5.f, -5.f},
    .target = {0.f, 0.f, 0.f},
    .up = {0.f, 1.f, 0.f},
    .fovy = 45.f,
    .projection = CAMERA_PERSPECTIVE,
};

static bool attempt_to_host = false;

static void on_nutblast_disconnected(NutBlast_Reason reason) {
    if (std::string(reason.code) == NUTBLAST_ERROR_LOBBY_NOT_FOUND)
        attempt_to_host = true;
}

static void generate_name() {
    std::mt19937 mt(NutBlast_TimeNS());
    std::uniform_int_distribution<size_t> dist(0, 9999);
    NutBlast_SetPlayerField(NUTBLAST_FIELD_PLAYER_NAME, TextFormat("Player%04d", dist(mt)));
}

namespace sh {
    Shader lighting = {0};
};

int main(int, char*[]) {
    NutBlast_SetGameID(FULL_GAME_TITLE);
    NutBlast_SetLogger(nutblast_raylib_logger);
    defer([] { NutBlast_Cleanup(); });

    NutBlast_OnDisconnected(on_nutblast_disconnected);

    generate_name();

    InitWindow(800, 600, FULL_GAME_TITLE);
    defer([] { CloseWindow(); });

    InitAudioDevice();
    defer([] { CloseAudioDevice(); });

    SetExitKey(KEY_NULL);
    SetTargetFPS(TICKRATE);

    sh::lighting = LoadShader("assets/lighting.vs", "assets/lighting.fs");

    while (!WindowShouldClose()) {
        static Clock join_clock(1.0);

        if (!NutBlast_IsOnline() && join_clock) {
            if (attempt_to_host) {
                NutBlast_Host(1, NUTBLAST_MAX_PLAYERS, false);
                attempt_to_host = false;
            } else {
                NutBlast_Join(1);
            }
        }

        NutBlast_Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(::camera);

        BeginShaderMode(sh::lighting);
        DrawCube({0.f, 0.f, 0.f}, 1.f, 1.f, 1.f, RED);
        EndShaderMode();

        EndMode3D();

        const int fs = 30;
        int y = 5;

        for (const auto& id : player_ids()) {
            const char* name = NutBlast_GetPlayerField(id, NUTBLAST_FIELD_PLAYER_NAME);
            DrawText(name, GetScreenWidth() - MeasureText(name, fs), y, fs, BLACK);
            y += fs;
        }

        DrawFPS(5, 5);

        EndDrawing();

        if (IsKeyPressed(KEY_M))
            break;
    }

    return EXIT_SUCCESS;
}
