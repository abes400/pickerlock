#pragma once

extern char savePath[PATH_MAX];
extern  short saveFileBufferSize;

/**
 * Generates the correct Save Path using the OS's API.
 * 
 * The path is saved on a global buffer, no need to free it.
 * 
 * @return Whether the correct save path was successfully fetched.
 */
bool initSavePath();