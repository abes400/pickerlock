#pragma once

extern char savePath[];

/**
 * Generates the correct Save Path using the OS's API.
 * The path is saved on a global buffer.
 */
int initSavePath();

/**
 * Loads the highscores and the settings on the known path provided by the OS.
 */
void load();

/**
 * Saves the highscores and the settings on the known path provided by the OS.
 */
void save();