#include <cstdlib>

#include <raylib.h>

#include <NutBlast.h>

#include "cmake.hpp"
#include "defer.hpp"
#include "game.hpp"

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

int main(int, char*[]) {
    NutBlast_SetGameID(FULL_GAME_TITLE);
    NutBlast_SetLogger(nutblast_raylib_logger);
    defer([] { NutBlast_Cleanup(); });

    InitWindow(800, 600, FULL_GAME_TITLE);
    defer([] { CloseWindow(); });

    InitAudioDevice();
    defer([] { CloseAudioDevice(); });

    SetExitKey(KEY_NULL);
    SetTargetFPS(TICKRATE);

    while (!WindowShouldClose()) {
        NutBlast_Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(::camera);
        DrawCube({0.f, 0.f, 0.f}, 1.f, 1.f, 1.f, RED);
        EndMode3D();

        DrawFPS(5, 5);
        EndDrawing();
    }

    return EXIT_SUCCESS;
}
