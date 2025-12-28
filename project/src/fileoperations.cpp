#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"

#ifdef _WIN32
constexpr const char* saveFilePath = "%localappdata%/flying map entertainment/pickerlock";
#endif

void load() {
    
}

void save() {
    char* a = getenv("LOCALAPPDATA");
    printf("%s", a);
}