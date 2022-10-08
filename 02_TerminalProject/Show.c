#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACE_CODE 32
#define ESC_CODE 27


void renderFileChunk(WINDOW* win, char* fileContent, int scrollCnt) {
    werase(win);
    wmove(win, 1, 0);
    char *curLine = fileContent;
    int curLineCnt = 0;
    
    while (curLine) {
        if (curLineCnt - scrollCnt < LINES - 3) break;
        
        char *nextLine = strchr(curLine, '\n');
        
        if (nextLine) *nextLine = '\0';

        if (curLineCnt >= scrollCnt) wprintw(win, " %.*s\n", COLS - 3, curLine);

        if (nextLine) *nextLine = '\n';
        
        curLine = nextLine ? (nextLine + 1) : NULL;
        curLineCnt++;
    }
    
    box(win, 0, 0);
    wrefresh(win);
}

int getCountFileLines(char* fileContent) {
    int countLines = 0;
    char* curLine = fileContent;
    
    while (curLine) {
        char* nextLine = strchr(curLine, '\n');
        curLine = nextLine ? (nextLine + 1): NULL;
        countLines++;
    }
    
    return countLines;
}

long getFileSize(FILE* fp){
    long size;
    
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size;
}

char* readFile(FILE* fp){
	long size = getFileSize(fp);
	char* content;
    
	content = malloc(size);
    fread(content, 1, size, fp);

	return content;
}

void renderFile(WINDOW* win, char* fileContent){
    int countFileLines = getCountFileLines(fileContent);
    int scrollCnt = 0;
    int inputButton = 0;

    while(1){
        renderFileChunk(win, fileContent, scrollCnt);

        inputButton = wgetch(win);

        if (inputButton == ESC_CODE) break;
        if (inputButton == SPACE_CODE && (scrollCnt + LINES - 3 < countFileLines)) scrollCnt++;
    }
}

WINDOW* createWindow(){
    WINDOW* win = newwin(LINES-1, COLS, 1, 0);
    refresh();
    scrollok (win, TRUE);
    keypad(win, TRUE);

    return win;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        printf("You need passed filename\n");
        return 1;
    }

    char* fileName = argv[1];

    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("File can't be opened\n");
        return 1;
    }
	
    char* fileContent = readFile(file);
    fclose(file);
    
    initscr();
    printw(fileName);

    WINDOW* win = createWindow();
    
    renderFile(win, fileContent);

    delwin(win);
    endwin();
    free(fileContent);
}