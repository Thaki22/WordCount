#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void count_characters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

    fclose(file);
    printf("字符数：%d\n", count);
}

void count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char ch;
    char prev = ' ';
    while ((ch = fgetc(file)) != EOF) {
        if ((ch == ' ' || ch == '\n' || ch == ',' || ch == '\t') &&
            (prev != ' ' && prev != '\n' && prev != ',' && prev != '\t')) {
            count++;
        }
        prev = ch;
    }
    // Count the last word if the file does not end with a space or comma
    if (prev != ' ' && prev != '\n' && prev != ',' && prev != '\t') {
        count++;
    }

    fclose(file);
    printf("单词数：%d\n", count);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [parameter] [input_file_name]\n", argv[0]);
        fprintf(stderr, "Parameters: -c for character count, -w for word count\n");
        exit(EXIT_FAILURE);
    }

    const char *parameter = argv[1];
    const char *filename = argv[2];

    if (strcmp(parameter, "-c") == 0) {
        count_characters(filename);
    } else if (strcmp(parameter, "-w") == 0) {
        count_words(filename);
    } else {
        fprintf(stderr, "Invalid parameter: %s\n", parameter);
        fprintf(stderr, "Parameters: -c for character count, -w for word count\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
