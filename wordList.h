typedef struct {
FILE *wordListFile;
char **words;
char **stringArray;
int array_size;
int array_filled_num;
}wordList;

/*#define ARRAY_FILL_START 0
#define BASE_ARRAY_SIZE 10

void createEmptyWordList(wordList *words) {
    words->array_filled_num = ARRAY_FILL_START;
    words->array_size = BASE_ARRAY_SIZE;
    words->stringArray = malloc(sizeof(char*)*words->array_size);
}

void expandArray(int *array_size, char **stringArray) {
    *array_size = *array_size * 2;
    stringArray = realloc(stringArray, sizeof(char*)**array_size);
}

void addWord(wordList *words, char *buffer, char **stringArray, int array_filled_num, int array_size) {
    char *temporaryString = malloc(sizeof(char));
    strncpy(temporaryString, buffer, strlen(buffer) - 1);
    if (words->array_filled_num == words->array_size) {
        expandArray(&words->array_size, words->stringArray);
    }
    stringArray[array_filled_num] = strdup(temporaryString);
}

void getWordList(wordList *words) {
    words->wordListFile = fopen("/home/david/Desktop/hangmanCPort/wordList.txt", "r");
    char buffer[256];
    while (fgets(buffer, 256, words->wordListFile) != NULL) {
        addWord(words, buffer, words->stringArray, words->array_filled_num, words->array_size);
        printf("%s\n", words->stringArray[words->array_filled_num]);
        words->array_filled_num++;
        }
}*/
