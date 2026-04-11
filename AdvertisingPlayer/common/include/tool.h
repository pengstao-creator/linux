#ifndef TOOL_H
#define TOOL_H
#include <glib-2.0/glib.h>
#define CONFIG_PATH "/home/pst/linux/AdvertisingPlayer/common/config/config.ini"

gchar * getConfigPath();


void handleError(const char * errMsg,GError * gerror);


#endif
