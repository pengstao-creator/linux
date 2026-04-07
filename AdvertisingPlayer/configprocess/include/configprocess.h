#ifndef CONFIG_PRO
#define CONFIG_PRO
#include "../../3rd-lib/include/mongoose.h"

#define HTML_ROOT "../html/index.html"
#define RESPONSE "../html/form_response.html"

void fn(struct mg_connection *c, int ev, void *ev_data);

#endif