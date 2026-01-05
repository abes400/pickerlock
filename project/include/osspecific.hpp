#pragma once




#if defined(__APPLE__)

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

#elif defined(_WIN32)

extern char savePath[];

/**
 * Checks whether there is already an instance running on the system.
 * 
 * @return Whether there is already an instance running on the system.
 */
bool instanceAlreadyExists();

#endif