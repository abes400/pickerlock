#pragma once

extern char savePath[];

/**
 * Generates the correct Save Path using the OS's API.
 * 
 * The path is saved on a global buffer, no need to free it.
 * 
 * WARNING: NOT AVAILABLE ON WIN32 (YET) DUE TO THE LIMITATIONS OF RAYLIB
 * 
 * @return Whether the correct save path was successfully fetched.
 */
bool initSavePath();