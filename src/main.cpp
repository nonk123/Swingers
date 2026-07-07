#include <cstdlib>

#include <raylib.h>

#include <NutBlast.h>

#include "cmake.hpp"
#include "defer.hpp"
#include "game.hpp"

static void nutblast_raylib_logger(NutBlast_LogLevel level, const char* line) {
    TraceLog(level == NB_LogInfo ? LOG_INFO : LOG_ERROR, "%s", line);
}

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
        DrawFPS(5, 5);
        EndDrawing();
    }

    return EXIT_SUCCESS;
}
