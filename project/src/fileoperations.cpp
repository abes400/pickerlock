#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include "raylib.h"

char savePath[PATH_MAX];

#if defined(__APPLE__)

#include <sysdir.h>
#include <glob.h>

int initSavePath() {

    char path[PATH_MAX];
    sysdir_search_path_enumeration_state state = 
    sysdir_start_search_path_enumeration(SYSDIR_DIRECTORY_APPLICATION_SUPPORT, SYSDIR_DOMAIN_MASK_USER);

    if((state = sysdir_get_next_search_path_enumeration(state, path)) == 0) return 0;

    glob_t buffer = {0};
    int result = glob(path, GLOB_TILDE | GLOB_NOSORT, NULL, &buffer);

    if(result) return 0;
    if(buffer.gl_pathc <= 0) {
        globfree(&buffer);
        return 0;
    }

    int validate = snprintf(savePath, PATH_MAX, "%s/Flying Map Entertainment/Pickerlock/save", buffer.gl_pathv[0]);
    globfree(&buffer);
    return validate >= 0 && validate < PATH_MAX;

}

#elif defined(_WIN32)

int initSavePath() {
    
}

#endif

void load() {
    
}

void save() {

    SaveFileText(savePath, "testo");

}