#pragma once


extern char savePath[];

/**
 * Generates the correct Save Path using the OS's API.
 * 
 * The path is saved on a global buffer, no need to free it.
 * 
 * @return Whether the correct save path was successfully fetched.
 */
bool initSavePath();

#if defined(_WIN32)
/**
 * Checks whether there is already an instance running on the system.
 * 
 * @return Whether there is already an instance running on the system.
 */
bool instanceAlreadyExists();
#endif