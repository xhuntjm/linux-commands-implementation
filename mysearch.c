#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>


//checks if its actually directory
int isDirectory(char *check) 
{
    struct stat info;
    stat(check, &info);
    return S_ISDIR(info.st_mode);
}


//recursively searches
void recursive_search(char *name, int depth)
{
    char directory[500];
    struct dirent *file;
    DIR *dir;

    dir = opendir(name);

    if(dir == NULL)
        return;

    while((file = readdir(dir)) != NULL){
        if(file->d_name[0] != '.'){

            printf("%*s%s \n", depth , "", file->d_name);

            //gets path info
            strcpy(directory, name);
            strcat(directory, "/");
            strcat(directory,  file->d_name);

            if(isDirectory(directory))
                recursive_search(directory, depth + 2);
            
        }

    }

    closedir(dir);

}

int main(int argc, char *argv[]) {

    char directory[256];
    int depth = 2;

    //checks to make sure arguments are correct
    if (argc > 2){
        printf("Incorrect Format \n");
        return 0;
    }

    //gets directory info
    if(argc == 1)
        getcwd(directory, sizeof(directory));//no directory input
    else     
        strcpy(directory, argv[1]);

    printf("%s \n", directory);
    recursive_search(directory, depth);

    return 0;
}