#include <stdio.h>

#define BUFSIZE    1024 // 缓冲区大小
static char buf[BUFSIZE];

/**
 * 该文件主要包含一个方法 char *readline(const char *prompt)
 * 该方法的作用：
 *  如果*prompt不为空，则返回 *prompt的值
 *  否则就返回从stdin中读取的一行内容（如果一行内容长于BUFSIZE 1024,则返回1024长度的字符串
 * 
 */

/* *
 * readline - get a line from stdin 
 * @prompt:        the string to be written to stdout
 *
 * The readline() function will write the input string @prompt to
 * stdout first. If the @prompt is NULL or the empty string,
 * no prompt is issued.
 *
 * This function will keep on reading characters and saving them to buffer
 * 'buf' until '\n' or '\r' is encountered.
 *
 * Note that, if the length of string that will be read is longer than
 * buffer size, the end of string will be discarded.
 *
 * The readline() function returns the text of the line read. If some errors
 * are happened, NULL is returned. The return value is a global variable,
 * thus it should be copied before it is used.
 * */
char *
readline(const char *prompt) {
    if (prompt != NULL) {
        cprintf("%s", prompt);
    }
    int i = 0, c;
    while (1) {
        c = getchar();
        if (c < 0) {
            return NULL;
        }
        else if (c >= ' ' && i < BUFSIZE - 1) {
            cputchar(c);
            buf[i ++] = c;
        }
        else if (c == '\b' && i > 0) {
            cputchar(c);
            i --;
        }
        else if (c == '\n' || c == '\r') {
            cputchar(c);
            buf[i] = '\0';
            return buf;
        }
    }
}

