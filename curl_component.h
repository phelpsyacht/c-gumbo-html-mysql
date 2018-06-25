#ifndef CURL_COMPONENT_H_
#define CURL_COMPONENT_H_

#include <gumbo.h>

#define PERMISSION_WRITE "写入权限" 
#define MODE S_IRWXU | S_IXGRP | S_IROTH | S_IXOTH

void print_intosql(GumboNode *node,GumboAttribute *attr);
 
void get_content(GumboNode *node);

char *file_pt(char *url, char *fname);

#endif