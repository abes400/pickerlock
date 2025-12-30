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

/**
 * Loads the highscores and the settings on the known path provided by the OS.
 */
void loadFile();

/**
 * Saves the highscores and the settings on the known path provided by the OS.
 */
void saveFile();