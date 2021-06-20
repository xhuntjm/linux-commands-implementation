#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

    struct stat info;
    int file;
    int numLines;
    char character;

    if(argc != 3){
        printf("format: mytail -n file \n");
        return 0;
    }

    if(stat(argv[2], &info) == -1){
        printf("invalid file \n");
        return 0;
    }

    numLines = atoi(argv[1]) * -1; //gets line num input

    file = open(argv[2], O_RDONLY); //opens file

    if(file == -1){
        printf("error with file \n");
        return 0;
    }

    
    lseek(file, -1, SEEK_END);//finds end of file
    
    read(file,&character,1);
    if(character == '\n') //checks if there is newline or not at end of file
        lseek(file, -2, SEEK_END);
    else
        lseek(file, -1, SEEK_END);
    
    while(read(file,&character,1) && numLines != 0){//goes backwards

        if(character == '\n')
            numLines = numLines - 1;

        if(lseek(file, -2, SEEK_CUR) == -1){ //case where begnning of file is met
            lseek(file, -1, SEEK_CUR);
            break;
        }
    }

    if(numLines == 0) //skips newline character
        lseek(file, 1, SEEK_CUR);

    //prints from where the search ended
    while(read(file,&character,1))
        printf("%c", character);

    close(file);

    return 0;
}