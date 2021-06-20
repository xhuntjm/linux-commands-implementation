#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {

    struct stat info;

    if(argc != 2){
        printf("no arguments \n");
        return 0;
    }

    if(stat(argv[1], &info) == -1){
        printf("invalid arguments \n");
        return 0;
    }

    printf("File: %s\n\n", argv[1]);
    printf("File Size: %ld \n", info.st_size);
    printf("Blocks Allocated: %ld \n", info.st_blocks);
    printf("Reference Count: %u \n", (unsigned) info.st_nlink);
    printf("Permissions (rwx): User - %c", (info.st_mode & S_IRUSR) ? 'r': '-');
    printf((info.st_mode & S_IWUSR) ? "w": "-");
    printf((info.st_mode & S_IXUSR) ? "x": "-");
    printf(" , Group - %c", (info.st_mode & S_IRGRP) ? 'r': '-');
    printf((info.st_mode & S_IWGRP) ? "w": "-");
    printf((info.st_mode & S_IXGRP) ? "x\n": "-\n");
    printf("File Inode: %u\n", (unsigned) info.st_ino);
    
    return 0;
}