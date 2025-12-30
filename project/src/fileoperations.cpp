#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <climits>
#include "globals.hpp"
#include "options.hpp"
#include "raylib.h"

char savePath[PATH_MAX];
const short saveFileBufferSize = 8 * sizeof(uint16_t) + 3 * sizeof(uint8_t);

#if defined(__APPLE__)

#include <sysdir.h>
#include <glob.h>

/**
 * Generates the correct Save Path using the OS's API.
 * 
 * The path is saved on a global buffer, no need to free it.
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

/**
 * Generates the correct Save Path using the OS's API.
 * 
 * The path is saved on a global buffer, no need to free it.
 * 
 * @return Whether the correct save path was successfully fetched.
 */
int initSavePath() {
    
}

#endif

/**
 * Loads the highscores and the settings on the known path provided by the OS.
 */
void loadFile() {
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
    // then it is safe to assign the values to the actual variables

    for(short i = 0; i < 3; i++) {
        Globals::highscores[i]        = hsTimed[i];
        Globals::highscoresEndless[i] = hsEndlss[i];
    }
    Opts::msc = msc;
    Opts::sfx = sfx;
    Opts::fsc = fsc;
}

/**
 * Saves the highscores and the settings on the known path provided by the OS.
 */
void saveFile() {
    uint8_t     saveFileBuffer[saveFileBufferSize];                 // Buffer to be written from
    uint8_t     tempOpts[]  = {Opts::msc, Opts::sfx, Opts::fsc};    // Used separate array for sake of performance
    uint16_t    checksum    = Opts::msc + Opts::sfx + Opts::fsc;    // The validation value written on both ends of the buffer
                                                                    // Initialized w/ values of settings
    uint8_t*    cursor      = saveFileBuffer + sizeof(checksum);    // Skipped by uint16_t size for the first checksum!


    // Copying timed mode highscores on buffer (and computing checksum)
    memmove(cursor, Globals::highscores, sizeof(Globals::highscores));
    checksum += Globals::highscores[Globals::EASY] 
              + Globals::highscores[Globals::MEDIUM] 
              + Globals::highscores[Globals::HARD];
    cursor   += sizeof(Globals::highscores);

    // Copying endless mode highscores on buffer (and computing checksum)
    memmove(cursor, Globals::highscoresEndless, sizeof(Globals::highscoresEndless));
    checksum += Globals::highscoresEndless[Globals::EASY] 
              + Globals::highscoresEndless[Globals::MEDIUM] 
              + Globals::highscoresEndless[Globals::HARD];
    cursor   += sizeof(Globals::highscoresEndless);

    // Copying settings on buffer (checksum already computed)
    memmove(cursor, tempOpts, sizeof(tempOpts));
    cursor += sizeof(tempOpts);

    // Copying checksums on each end of the buffer
    memmove(cursor, &checksum, sizeof(checksum));
    memmove(saveFileBuffer, &checksum, sizeof(checksum));

    MakeDirectory(GetPrevDirectoryPath(savePath));
    SaveFileData(savePath, saveFileBuffer, saveFileBufferSize);
}