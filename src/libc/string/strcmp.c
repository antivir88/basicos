#include "string.h"

#define C_ENDL '\0'

int strcmp(char *str1, char *str2)
{
    int i = 0;
    int failed = 0;

    while(str1[i] != C_ENDL && str2[i] != C_ENDL) {
        if(str1[i] != str2[i]) {
            failed = 1;
            break;
        }

        i++;
    }

    if( (str1[i] == C_ENDL && str2[i] != C_ENDL) || (str1[i] != C_ENDL && str2[i] == C_ENDL) ) {
        failed = 1;
    }
  
    return failed;
}
