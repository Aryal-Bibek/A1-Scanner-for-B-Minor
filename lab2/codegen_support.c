#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int label_count =0;

int scratchTable[7];
// 0 : % rbx 1 : %r10 2 : % r11 3: %r12 4: %r13 5: %r14 6 : %r15

int scratch_alloc() {
    for (int  i =0 ; i < 7; i++){
        if (scratchTable[i] == 0){
            scratchTable[i]=1;
            return i;
        }
    }
    printf("error ran out of scratch registers");
    exit(1);
}

void scratch_free( int r ){
    scratchTable[r]=0;
}
const char * scratch_name (int r){
    switch(r){
        case 0:
            return "%rbx";
        case 1:
            return "%r10";
        case 2:
            return "%r11";
        case 3:
            return "%r12";
        case 4:
            return "%r13";
        case 5:
            return "%r14";
        case 6:
            return "%r15";
        default:
            printf("error: free register out of bounds");
            exit(0);
    }
}

int label_create(){
    int tmp = label_count;
    label_count++;
    return tmp;
}

const char * label_name (int label){
    char * label_to_print = (char*)malloc(99 * sizeof(char));
    sprintf(label_to_print,".L%d", label);
    return label_to_print;
}