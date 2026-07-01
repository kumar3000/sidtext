#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios cooked;

void serror(const char *e) {
    perror(e);
    exit(1);
}

void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cooked) == -1) {
        serror("void disableRawMode() { tcsetattr }");
    }
}

void enableRawMode() {
    atexit(disableRawMode);

    if (tcgetattr(STDIN_FILENO, &cooked) == -1) {
        serror("void enableRawMode() { tcgetattr }");
    }

    struct termios raw = cooked;
    
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag != (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        serror("void enableRawMode() { tcsetattr }");
    }
}

char readKey() {
    char c;
    if (read(STDIN_FILENO, &c, 1) == -1) {
        serror("char readKey() { read() }");
    }

    return c;
}

void processKey() {
    char c = readKey();

    switch(c) {
        case CTRL_KEY('q'):
            exit(0);
            break;
    }
}

int main() {
    enableRawMode();

    while (1) {
        processKey();
    }

    return 0;
}
