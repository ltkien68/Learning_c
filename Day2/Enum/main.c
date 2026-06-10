#include <stdio.h>
#include <stdint.h>

typedef enum {
    SUCCESS, 
    NOT_FOUND,
    ERROR      
} RETURN_STATUS;

RETURN_STATUS checkIC(int ic_id) {
    if (ic_id == 1) {
        return SUCCESS; 
    } else if (ic_id == 2) {
        return NOT_FOUND;
    } else {
        return ERROR;
    }
}

int main() {
    RETURN_STATUS result;
    result = checkIC(1);

    if (result == SUCCESS) {
        printf("OK\n");
    } else if (result == NOT_FOUND) {
        printf("NOT FOUND\n");
    } else {
        printf("ERROR\n");
    }

    return 0;
}