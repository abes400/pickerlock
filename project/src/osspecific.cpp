#include <climits>
#include <stdio.h>

char savePath[PATH_MAX];

#if defined(__APPLE__)
#include <cstdint>
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
#include<windows.h>
#include<shlobj.h>

/**
 * Checks whether there is already an instance running on the system.
 * 
 * @return Whether there is already an instance running on the system.
 */
bool instanceAlreadyExists() {
    CreateMutexA(0, 1, "Global\\PickerlockInstanceMutex");

    return GetLastError() == ERROR_ALREADY_EXISTS;
}

/**
 * Generates the correct Save Path using the OS's API.
 * 
 * The path is saved on a global buffer, no need to free it.
 * 
 * @return Whether the correct save path was successfully fetched.
 */

bool initSavePath() {

    PWSTR prog_data_path = nullptr;

    HRESULT hres = SHGetKnownFolderPath((REFKNOWNFOLDERID)FOLDERID_ProgramData, 0, nullptr, &prog_data_path);
    if(FAILED(hres)) return false;

    int pdpath_size_as_multibyte = WideCharToMultiByte(CP_UTF8, 0, prog_data_path, -1, nullptr, 0, nullptr, nullptr);

    char* prog_data_path_multibyte = (char*) malloc(sizeof(char) * pdpath_size_as_multibyte);

    if(!prog_data_path_multibyte) {
        CoTaskMemFree(prog_data_path);
        return false;
    }

    int converted = WideCharToMultiByte(CP_UTF8, 0, prog_data_path, -1, prog_data_path_multibyte, pdpath_size_as_multibyte, nullptr, nullptr);
    CoTaskMemFree(prog_data_path);

    if(!converted) {
        free(prog_data_path_multibyte);
        return false;
    }

    int validate = snprintf(savePath, PATH_MAX, "%s\\Flying Map Entertainment\\Pickerlock\\save", prog_data_path_multibyte);
    free(prog_data_path_multibyte);

    return validate >= 0 && validate < PATH_MAX;
}

#endif