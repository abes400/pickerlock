#if defined(__APPLE__)

#include <stdio.h>
#include <climits>
#include <cstdint>
#include <sysdir.h>
#include <glob.h>

char savePath[PATH_MAX];

/**
 * Generates the correct Save Path using the OS's API.
 * 
 * The path is saved on a global buffer, no need to free it.
 * 
 * WARNING: NOT AVAILABLE ON WIN32 (YET) DUE TO THE LIMITATIONS OF RAYLIB
 * 
 * @return Whether the correct save path was successfully fetched.
 */
bool initSavePath() {

    char path[PATH_MAX];
    sysdir_search_path_enumeration_state state = 
    sysdir_start_search_path_enumeration(SYSDIR_DIRECTORY_APPLICATION_SUPPORT, SYSDIR_DOMAIN_MASK_USER);

    if((state = sysdir_get_next_search_path_enumeration(state, path)) == 0) return false;

    glob_t buffer = {0};
    int result = glob(path, GLOB_TILDE | GLOB_NOSORT, NULL, &buffer);

    if(result) return false;
    if(buffer.gl_pathc <= 0) {
        globfree(&buffer);
        return false;
    }

    int validate = snprintf(savePath, PATH_MAX, "%s/Flying Map Entertainment/Pickerlock/save", buffer.gl_pathv[0]);
    globfree(&buffer);
    return validate >= 0 && validate < PATH_MAX;

}

#elif defined(_WIN32)

#endif