#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gumbo.h>
#include <unistd.h>
#include <mysql/mysql.h>

#include "curl_component.h"
#include "sql_crud.h"

void thread_book();

int main(void){
    /*command:gcc -o p_w -g  curl_book_process.c split_string.c  curl_component.c sql_crud.c -lgumbo -lcurl  -lmysqlclient*/ 
    sql_init();
    sql_connect();
    
    printf("main process:\n");

    thread_book();
    /*thread_catalog();
    thread_charpter();*/

    sql_close();  

    printf("return====>ok\n");

    return 0;
}

int book_lists(char *cn, char * fn){
    GumboOutput *output;
    char *buf;
    
    char url[108] = "http://www.www.com/index.php?page=";
    strcat(url ,cn);
    printf("link is %s\n", url);  
 
    buf=file_pt(url, fn);
    if (!buf) return -1;
    output=gumbo_parse(buf);
    if (!output){
        free(buf);
        return -1;
    }
    get_content(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions,output);
    free(buf);

    return 0;
}

void thread_book(){
    char cn[10];
    int n = 1;
    while(n < 1000){
        sprintf(cn, "%d", n);
        int book_pn = book_lists(cn, "index.html");
        if (book_pn == 0){
            printf("curl book executed successfully\n");
        }

        n++;
    }

    return;
}

 

