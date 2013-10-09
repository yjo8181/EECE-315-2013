// Given the name of an executable, find it in the PATH and return the full PATH

#include "lookupPath.h"


// Reference: http://www.cplusplus.com/reference/cstring/strtok/
char *lookupPath(char prog [])
{
    /* Attempts to find prog in PATH.
       Returns the first path in PATH for prog. If prog is not found
       in any path in PATH, returns "FILENOTFOUND" */
    char *ret_buffer = (char *)malloc(MAX_LINE_LEN);
    char *paths = (char *)malloc(MAX_PATH_LEN);
    //printf("getenv(\"PATH\"): %s", getenv("PATH")); //DEBUGGING
    strcpy(paths, getenv("PATH"));  // Get PATH environment variable
    //printf("paths: %s\n", paths); //DEBUGGING
    char *path = strtok(paths, ":");

    //printf("prog: %s\n", prog); //DEBUGGING
    while (path != NULL)
    {
        // This will return the path where the executable is first encountered; is this the behaviour we want?
        if (checkFileInDir(path, prog))
        {
            snprintf(ret_buffer, MAX_LINE_LEN * sizeof(char), "%s/%s", path, prog);
            //printf("ret_buffer: %s\n", ret_buffer); //DEBUGGING //DEBUGGING
            return ret_buffer;
        }
        path = strtok(NULL, ":");

        //printf("paths: %s\npath: %s\n", paths, path); //DEBUGGING
    }

    //return "FILENOTFOUND";
    snprintf(ret_buffer, MAX_LINE_LEN * sizeof(char), "FILENOTFOUND");
    //printf("ret_buffer: %s\n", ret_buffer); //DEBUGGING //DEBUGGING
    return ret_buffer;
}


// Some code adapted from: http://stackoverflow.com/questions/4204666/
bool checkFileInDir(char *path, char *file)
{
    /* If file is present in path, return true, otherwise false

    Usage example: checkFileInDir("/bin", "ls");
    */
    DIR *directory;
    struct dirent *dir_entry;
    directory = opendir(path);

    // If directory exists, continuously read its contents. If the name
    // of one of the contents matches file, return true.
    if (directory)
    {
        // Each iteration, get a directory entry
        while ((dir_entry = readdir(directory)) != NULL)
        {
            if (!strcmp(file, dir_entry->d_name))
            {
                return true;
            }
        }
        closedir(directory);
    }

    return false;
}
