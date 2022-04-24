#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sodium.h>

// удаление запрещенных символов
char* remove_x_char(char* str) {
    char* temp = str;
    char* add, *buffer;
    for(add = str, buffer = str; *buffer = *add; *add++) {
        if(isspace(*add)) {
            *buffer++;
            continue;
        }
        else if (isalnum(*add)) {
            *buffer++;
        }
    }
    return temp;
}

//reverse string
void reverse(char s[]) { 
    int i, j;
    char c;
    
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

// int to char
void itoc(int num, char str[]) { 
    int i, sign;
    i = 0;

    if ((sign = num) < 0) { /* записываем знак */
        num = -num;          /* делаем n положительным числом */
    }

    do {       /* генерируем цифры в обратном порядке */
        str[i++] = num % 10 + '0';   /* берем следующую цифру */
    } while ((num /= 10) > 0);     /* удаляем */

    if (sign < 0) {
        str[i++] = '-';
    }
    str[i] = '\0';
    reverse(str);
}

// создание категории
void validate_txt(char *filename) {
    reverse(filename);
    if(!strncmp(filename, "txt.", 4)) {
        reverse(filename);
    } else {
        strcmp(filename, ".txt");
    }
}


#define strlen_limited(S_, M_) (strnlen ((S_), (M_)))

// safe strcpy
size_t strlcpy (char * dst, const char * src, size_t dstsize) {
    size_t src_len ;
    size_t len ;
    size_t dstlimit ;

    if (src == 0) {
        if (dst != 0 && 0 < dstsize) {
            dst [0] = 0 ;
        }
        return 0 ;
    }

    src_len = strlen (src) ;
    len = src_len ;

    if (dst == 0 || dstsize == 0) {
        return src_len ;
    }
    dstlimit = dstsize - 1 ;

    if (dstlimit < len) {
        len = dstlimit ;
    }
    memcpy (dst, src, len) ;
    dst [len] = 0 ;

    return src_len ;
}

// safe strcat
size_t strlcat (char * dst, const char * src, size_t dstsize) {
    size_t src_len ;
    size_t dst_len ;
    size_t dstlimit ;

    if (dst == 0) {
        if (src == 0) {
            return 0 ;
        }
        return strlen (src) ;
    }
    /* At this poinit, DST != nullptr && SRC != nullptr */
    src_len = strlen (src) ;
    dst_len = strlen_limited (dst, dstsize) ;
    dstlimit = dstsize - 1 ;

    if (dstlimit < dst_len) {
        /* Already overflowed */
        return dst_len + src_len ;
    }
    else {
        size_t len = src_len ;
        /* dstlen <= dstlimit */
        if (dstlimit < (dst_len + src_len)) {
            len = dstlimit - dst_len ;
        }
        memcpy (dst + dst_len, src, len) ;
        dst [dst_len + len] = 0 ;
        return dst_len + src_len ;
    }
}

enum read_status {
    OK,
    NO_INPUT,
    TOO_LONG
};

int get_line(const char *prompt, char *buf, size_t sz) {
    char fmt[40];
    int i;
    int nscanned;

    printf("%s", prompt);
    fflush(stdout);

    sprintf(fmt, "%%%zu[^\n]%%*[^\n]%%n", sz-1);
    /* read at most sz-1 characters on, discarding the rest */
    i = scanf(fmt, buf, &nscanned);
    if (i > 0) {
        getchar();
        if (nscanned >= sz) {
            return TOO_LONG;
        } else {
            return OK;
        }
    } else {
        return NO_INPUT;
    }
}