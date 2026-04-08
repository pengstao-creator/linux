#ifndef REQUEST_METHOD_H
#define REQUEST_METHOD_H
#include <curl/curl.h>

typedef size_t (*curl_write_callback)(char*,size_t,size_t,void*);

void sendGetRequest(const char * url,curl_write_callback fn);

void sendPostRequest(const char * url,const char * msg , curl_write_callback fn);

#endif