#ifndef CONFIG_PRO
#define CONFIG_PRO
#include "configinfo.h"

#define HTML_ROOT "../html/index.html"
#define RESPONSE "../html/form_response.html"

void parseConfig(struct mg_connection *c,struct mg_http_message *hm);
#endif