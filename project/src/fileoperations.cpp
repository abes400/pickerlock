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
    // Check existance and length of the file
    if(!FileExists(savePath)) return;
    if(GetFileLength(savePath) < saveFileBufferSize) return;

    // Load file
    int bufferSize = saveFileBufferSize;
    uint8_t* saveFileBuffer = LoadFileData(savePath, &bufferSize);
    uint8_t* cursor = saveFileBuffer;

    // Extract data from file to temp fields
    uint16_t checksum1, checksum2, checksumComputed = 0;
    uint16_t hsTimed[3], hsEndlss[3];
    uint8_t  msc, sfx, fsc;

    memmove(&checksum1, cursor, sizeof(checksum1));
    cursor += sizeof(checksum1);

    // Highscores
    memmove(hsTimed, cursor, sizeof(hsTimed));
    cursor += sizeof(hsTimed);
    memmove(hsEndlss, cursor, sizeof(hsEndlss));
    cursor += sizeof(hsEndlss);

    // Options
    memmove(&msc, cursor, sizeof(msc));
    cursor += sizeof(msc);
    memmove(&sfx, cursor, sizeof(sfx));
    cursor += sizeof(sfx);
    memmove(&fsc, cursor, sizeof(fsc));
    cursor += sizeof(fsc);

    memmove(&checksum2, cursor, sizeof(checksum2));

    // Unload file
    UnloadFileData(saveFileBuffer);

    // Doing range tests for the scores and computing checksumTest for validation
    // return if any value is out of range
    for(short i = 0; i < 3; i++) {
        if( hsTimed[i]  > 9999 || hsEndlss[i] > 9999 ) return;
        checksumComputed += hsTimed[i] + hsEndlss[i];
    }

    checksumComputed += msc + sfx + fsc;

    if(checksumComputed != checksum1 || checksumComputed != checksum2) return;

    // If the function reaches here with no early-returns
    // then it is safe to write the values to the actual variables
    printf("If you read this, the file is safe to use\n"); 
}

/**
 * Saves the highscores and the settings on the known path provided by the OS.
 * 
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

    MakeDirectory(GetPrevDirectoryPath(savePath));
    SaveFileData(savePath, saveFileBuffer, saveFileBufferSize);
}