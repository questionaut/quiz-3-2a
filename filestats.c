#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc == 0 || argc == 1) {
        printf("usage: filestats directory_name\n");
    } else if (argc == 2) {

        char* numFiles[1000];
        // Get file names from given directory
        // directory access code referenced from https://www.studytonight.com/c/programs/files-and-streams/program-to-list-files-in-directory
        DIR *d;
        struct dirent *dir;
        d = opendir(argv[1]);

        if (d) {
            int size = 0;
            while ((dir = readdir(d)) != 0) {
                numFiles[size] = dir->d_name;
                size++;
            }
            closedir(d);

            struct stat *buf;
            buf = malloc(sizeof(struct stat));
                
            for (int i = 0; i < size; i++) {
                char* currentFile = argv[1];
                strcat(currentFile, numFiles[i]);
                int error = stat(currentFile, buf);
                if (error == 0) {
                    printf("File name: %s\n", numFiles[i]);
                    printf("inode number: %lu\n", buf->st_ino);
                    free(buf);
                } else {
                    printf("error with stat\n");
                    exit(EXIT_FAILURE);
                }
            }
        } else {
            printf("can't open %s\n", argv[1]);
            exit(EXIT_SUCCESS);
        }
    } else {
        printf("too many arguments");
    }
    
}
