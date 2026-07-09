#include <raylib.h>

#include <NutBlast.h>

#include "log.hpp"

static void nutblast_raylib_logger(NutBlast_LogLevel level, const char* line) {
    TraceLog(level == NB_LogInfo ? LOG_INFO : LOG_ERROR, "%s", line);
}

void init_logger() {
    NutBlast_SetLogger(nutblast_raylib_logger);
}
