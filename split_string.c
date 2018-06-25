#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "curl_component.h"
#include "split_string.h"

void replace_string(char *result, char *source, char* be_reaplceed, char *replace){
    char *q=NULL;
    char *p=NULL;
   
    p=source;
    while((q=strstr(p, be_reaplceed))!=NULL)
    {
        strncpy(result, p, q-p);
        /*very important*/
        result[q-p]= '\0';
        strcat(result, replace);
        strcat(result, q+strlen(be_reaplceed));
        strcpy(p,result);
    }
    strcpy(result, p);    
}





