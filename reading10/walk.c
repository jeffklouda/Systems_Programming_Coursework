#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    struct dirent* dp;
    struct stat s;
    DIR* dirp = opendir(".");
    while ((dp = readdir(dirp)) != NULL) {
        if (0 == stat(dp->d_name, &s)) {
            if (S_ISREG(s.st_mode)) {
                printf("%s %d\n", dp->d_name, s.st_size);
            }
        }
    }

    closedir(dirp);
    return 0;
}
