#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int ft_countParams(char *args) {
    int count = 0;
    for (int i = 1; i <= strlen(args); i++) {
        if ((args[i] >= 'A' && args[i] <= 'Z') || (args[i] >= 'a' && args[i] <= 'z'))
            count++;
        else
            break;
    }
    return (count);
}

char *ft_paramsFilter(char *args) {
    int countParams = ft_countParams(args);
    char *arr = NULL;
    if ((arr = malloc((countParams * sizeof(char)) + 1)) == NULL)
        return NULL;
    for (int i = 1, y = 0; i <= countParams; i++) {
        if ((args[i] >= 'A' && args[i] <= 'Z') || (args[i] >= 'a' && args[i] <= 'z'))
            arr[y++] = args[i];
        else
            break;
    }
    return arr;
}

int ft_includes(char *args, char c) {
    for (int i = 0; i < strlen(args); i++) {
        if (args[i] == c)
            return (1);
    }
    return (0);
}

int main(int argc, char *argv[]) {
    DIR *directory = NULL;
    struct dirent *dir_info;


    if (argc > 1 && (strcmp(argv[1], "help") == 0)) {
        printf("ls: usage is 'ls <flags> <path>'\n");
        return (0);
    }
    if (argc > 2 && argv[1][0] == '-')
        directory = opendir(argv[2]);
    else if (argc > 1)
        directory = opendir(argv[1]);
    else
        directory = opendir(".");

    if (directory == NULL) {
        printf("ls: cannot access '%s'\n", (argc > 2 && argv[1][0] == '-' ? argv[2] : (argc > 1 ? argv[1] : "")));
        return (0);
    }

    if (argc > 1 && argv[1][0] == '-' && ft_countParams(argv[1]) > 0) {
        printf("FLAG(S): %s\n\n", ft_paramsFilter(argv[1]));
        while ((dir_info = readdir(directory)) != NULL) {
            if (ft_includes(argv[1], 'l'))
                if (dir_info->d_name[0] == '.' && !ft_includes(argv[1], 'a'))
                    continue;
                else
                    printf("[+] %s\n", dir_info->d_name);
            else {
                if (dir_info->d_name[0] == '.' && !ft_includes(argv[1], 'a'))
                    continue;
                else
                    printf("%s  ", dir_info->d_name);
            }
        }
        if (!ft_includes(argv[1], 'l'))
            printf("\n");
    } else {
        while ((dir_info = readdir(directory)) != NULL) {
            if (dir_info->d_name[0] != '.')
                printf("%s ", dir_info->d_name);
        }
        printf("\n");
    }

    if (closedir(directory) == -1)
        exit(0);
    return (0);
}
