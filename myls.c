#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>


int main(int argc, char *argv[]) {
    
    char directory[256];
    struct dirent *file;
    struct stat info;
    int flag = 0;
    DIR *dir;

    if(argc > 3){
        printf("Incorrect format");
        return 0;
    }

    //gets directory info and sets -l flag if present
    if(argc == 1)
       getcwd(directory, sizeof(directory)); //no directory input
    else if (argc == 2){
        if(strcmp(argv[1], "-l") == 0){ //-l flag
            getcwd(directory, sizeof(directory));
            flag = 1;
        }
        else //no -l flag
            strcpy(directory, argv[1]);
    }
    else{       
        strcpy(directory, argv[2]);
        flag = 1;
    }

    dir = opendir(directory);

    //checks to see if it is a valid directory
    if(dir == NULL){
        printf("Incorrect directory \n");
        return 0;
    }
    
    while((file = readdir(dir)) != NULL)
    {
        //prints out stat information
       if(flag){
            stat(file->d_name, &info);

            printf("File: %s\n", file->d_name);
            printf("File Size: %ld \n", info.st_size);
            printf("Blocks Allocated: %ld \n", info.st_blocks);
            printf("Reference Count: %u \n", (unsigned) info.st_nlink);
            printf("Permissions (rwx): User - %c", (info.st_mode & S_IRUSR) ? 'r': '-');
            printf((info.st_mode & S_IWUSR) ? "w": "-");
            printf((info.st_mode & S_IXUSR) ? "x": "-");
            printf(" , Group - %c", (info.st_mode & S_IRGRP) ? 'r': '-');
            printf((info.st_mode & S_IWGRP) ? "w": "-");
            printf((info.st_mode & S_IXGRP) ? "x\n": "-\n");
            printf("File Inode: %u\n\n", (unsigned) info.st_ino);
       }
       else //prints file names
            printf("%s\n", file->d_name);
    }


    
    
    
    
    return 0;
}