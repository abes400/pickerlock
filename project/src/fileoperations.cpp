#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <climits>
#include "globals.hpp"
#include "raylib.h"

char savePath[PATH_MAX];
const short saveFileBufferSize = 8 * sizeof(uint16_t) + 3 * sizeof(uint8_t);

#if defined(__APPLE__)

#include <sysdir.h>
#include <glob.h>

/**
 * Generates the correct Save Path using the OS's API.
 * The path is saved on a global buffer.
 */
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
/**
 * Generates the correct Save Path using the OS's API.
 * The path is saved on a global buffer.
 */
int initSavePath() {
    
}

#endif

void load() {
    
}

/**
 * Saves the highscores and the settings on the known path provided by the OS.
 */
void save() {
    uint8_t     saveFileBuffer[saveFileBufferSize];                 // Buffer to be written from
    uint8_t*    cursor      = saveFileBuffer + sizeof(uint16_t);    // Skipped by uint16_t size for the first checksum!
    uint8_t     tempOpts[]  = {Opts::msc, Opts::sfx, Opts::fsc};    // Used separate array for sake of performance
    uint16_t    checksum    = Opts::msc + Opts::sfx + Opts::fsc;    // The validation value written on both ends of the buffer
                                                                    // Initialized w/ values of settings


    // Copying timed mode highscores on buffer (and computing checksum)
    memmove(cursor, Globals::highscores, 3 * sizeof(uint16_t));
    checksum += Globals::highscores[Globals::EASY] 
              + Globals::highscores[Globals::MEDIUM] 
              + Globals::highscores[Globals::HARD];
    cursor   += 3 * sizeof(uint16_t);

    // Copying endless mode highscores on buffer (and computing checksum)
    memmove(cursor, Globals::highscoresEndless, 3 * sizeof(uint16_t));
    checksum += Globals::highscoresEndless[Globals::EASY] 
              + Globals::highscoresEndless[Globals::MEDIUM] 
              + Globals::highscoresEndless[Globals::HARD];
    cursor   += 3 * sizeof(uint16_t);

    // Copying settings on buffer (checksum already computed)
    memmove(cursor, tempOpts, 3 * sizeof(uint8_t));
    cursor += 3 * sizeof(uint8_t);

    // Copying checksums on each end of the buffer
    memmove(cursor, &checksum, sizeof(uint16_t));
    memmove(saveFileBuffer, &checksum, sizeof(uint16_t));

    // Saving the buffer contents on the file
    SaveFileData(savePath, saveFileBuffer, saveFileBufferSize);
}