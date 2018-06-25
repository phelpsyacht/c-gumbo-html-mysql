#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <mysql/mysql.h>

#include "split_string.h"
#include "curl_component.h"
#include "sql_crud.h"

void get_content(GumboNode *node){
    GumboVector *children;
    GumboAttribute *attr;
    int n;

    if (node->type != GUMBO_NODE_ELEMENT) return;
    /*page link*/
    if (attr=gumbo_get_attribute(&node->v.element.attributes,"class")){
        print_intosql(node,attr);
    }
    /*subnode*/
    children=&node->v.element.children;
   
    for (n=0;n < children->length;++n){
        get_content(children->data[n]);
    }
}

void print_intosql(GumboNode *node,GumboAttribute *attr){
    /*node*/
    GumboNode *book_lists=(GumboNode *)(&node->v.element.children)->data[0];
    /*class node text, then insert into mysql */
        if (book_lists->type == GUMBO_NODE_TEXT){
            char *attr_value = NULL, *bo = NULL;
            char book_name[80]={0};
            char *table_name = "book_name";
            attr_value = (char *)attr->value;
            bo = (char *)book_lists->v.text.text;
            /*split string*/
            if (strstr(attr_value, "index.html")){
                 if (bo != NULL && strstr(bo, "read the book") == NULL){
                    sprintf(book_name, "%s", bo);
                    char *book_attr = NULL;
                    char book_url[41] = {0};
                    strcpy(book_url, attr_value);
                    book_attr = attr_value;
                    long int attr_len = strlen(book_attr);
                    char book_attr_str[attr_len];
                    char *book_str = NULL;
                    book_str = book_attr_str;
                    replace_string(book_str, book_attr, "//", "");
                    replace_string(book_str, book_attr, "/index.htm", "");
                    char folder[108] = {0};
                    sprintf(folder, "%s", book_str);

                    char *field = "book_name, done, folder";
                    char msg[100]={0};
                    int cmp = -1;
                    int enable = 0;
                    int in_len = 300;
                    char fd[200] = {0};
                    sprintf(fd, "%s%s", "/var/www/", folder);
                    printf("book folder===>%s\n", folder);
                    if (access(fd, F_OK) == -1){
                        mkdir(fd, MODE);
                    }
                    sprintf(msg, "\'%s\',%d, \'%s\'", bo, enable, folder);
                    insert_msg(table_name, field, msg ,in_len);
                }
            }
        }
}

char *file_pt(char *url, char *fname){
    CURL *curl = NULL;
    FILE *fp = NULL, *fp_read = NULL, *log_fp =  NULL;
    CURLcode res;
    char errbuf[CURL_ERROR_SIZE];
    int file_size = 0;
    int log_size = 0;
    char *tmp = NULL;
    int flag = 0;
    char key[1024] = {0};
    char str1[128] = {0};
    char str2[128] = {0};

    if ((fp = fopen(fname, "w")) == NULL)
    {
        return PERMISSION_WRITE;
    }
    printf("filename is %s, url is %s\n", fname, url);
    curl = curl_easy_init();

    flag = 1;

    curl_easy_setopt(curl, CURLOPT_URL, url);     
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);  
    curl_easy_setopt(curl, CURLOPT_REFERER, "https://www.baidu.com/");
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0L);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); 
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    curl_easy_setopt(curl, CURLOPT_ENCODING, "gzip" );
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 80L);

    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);

    /* perform the request */
    res = curl_easy_perform(curl);

    errbuf[0] = 0;
    
    size_t len = strlen(errbuf);
    fprintf(stderr, "\nlibcurl: (%d) ", res);
    if (len){
        fprintf(stderr, "%s%s", errbuf, ((errbuf[len - 1] != '\n') ? "\n" : ""));
    }else{
        fprintf(stderr, "%s\n", curl_easy_strerror(res));
    }
    log_fp = fopen("log", "wb");
    if (log_fp == NULL){
        printf("create log wrong!\n");
    }
    fprintf(log_fp, "%d\n", res);
    fprintf(log_fp, "%s", curl_easy_strerror(res));
    fclose(log_fp);
    curl_easy_cleanup(curl);
    fclose(fp);

    fp_read = fopen(fname, "rb");
    if (fp_read == NULL){
        printf("create file wrong!\n");
    }
    fseek(fp_read, 0, SEEK_END); 
    file_size = ftell(fp_read)     ;
    fseek(fp_read, 0, SEEK_SET);    
    tmp = (char *)malloc(file_size * sizeof(char));   
    printf("file_size:%d\n", file_size);

    fread(tmp, file_size, sizeof(char), fp_read);  

    fclose(fp_read);
    return tmp;
}
