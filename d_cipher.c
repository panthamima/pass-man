#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 255

FILE *AWE;
char fn[] = "base.db";

int caeXorEnc(char xor_str[SIZE], char *xor_key) {
    int i, // xor_str
        j, // count 
        k; // k % strlen

    i = k = j = 0;
    char buf; 
    char count[SIZE];
    AWE = fopen(fn, "a");

    for(i = 0; xor_str[i] != '\0'; ++i){
        buf = xor_str[i];
        if(buf >= '!' && buf <= '}'){ // от минимально до максимально доступного чара
            buf += strlen(xor_key); // чар + сдвиг
            if(buf > '}'){
                buf = buf - '}' + '!' - 1;
            }
        }
        count[j] = buf;
        count[j] = count[j] ^ xor_key[k % strlen(xor_key)]; // xor
        fputc(count[j], AWE);
        k++;
    }
}

int caeXorDec(char xor_str[SIZE], char *xor_key) {
    char buf;
    int i, k, j;
    i = k = j =0;
    char output[SIZE];
    AWE = fopen(fn, "a");
    for(i = 0; xor_str[i] != '\0'; i++){
        output[j] = xor_str[i] ^ xor_key[k % strlen(xor_key)]; //xor
        k++;
        buf = output[j];
        if(buf >= '!' && buf <= '~'){
            buf -= strlen(xor_key);
			if(buf < '!') {
				buf = buf + '}' - '!' + 1;
			}
        }
        fputc(buf, AWE);
    }
}

int main() {
    char message[SIZE];
    char key[] = "3478fh"; //aa33dss sdfgkhjgh4khjkjjk

    scanf("%s", message);
    caeXorDec(message, key);

    return 0;
}

