#include "tool.h"
#include "log.h"

gchar *getConfigPath()
{
    // 加载配置文件路径
    GKeyFile *newfile = g_key_file_new();
    gchar *configpath = NULL;
    GError *gerror = NULL;
    if (newfile)
    {
        if (!g_key_file_load_from_file(newfile, CONFIG_PATH, G_KEY_FILE_NONE, &gerror))
        {
            handleError("加载配置文件路径", gerror);
        }
        else
        {
            configpath = g_key_file_get_string(newfile, "config", "configpath", &gerror);
            if (!configpath)
            {
                handleError("读取config组中的configpath失败", gerror);
            }
        }
        g_key_file_free(newfile);
    }
    else
    {
        MLOG_W("g_key_file_new获取失败");
    }
    return configpath;
}

void handleError(const char *errMsg, GError *gerror)
{
    if (gerror)
    {
        MLOG_W("%s,错误码:%d,错误原因:%s", errMsg, gerror->code, gerror->message);
        g_error_free(gerror);
        gerror = NULL;
    }
    else
    {
        MLOG_W("%s,且错误返回为空", errMsg);
    }
}
