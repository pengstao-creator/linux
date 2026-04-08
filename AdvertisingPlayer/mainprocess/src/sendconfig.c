#include <glib-2.0/glib.h>
#include "sendconfig.h"
#include "data.h"
#include "log.h"
#include "tool.h"
#define MACHINE_CODE_PATH "/etc/machine-id"


// 返回新分配的字符串，调用者需使用 g_free() 释放
gchar* get_sn(void) 
{
    gchar *contents = NULL;
    size_t length = 0;
    GError *gerror = NULL;

    if (g_file_get_contents(MACHINE_CODE_PATH, &contents, &length, &gerror)) {
        return contents; // 调用者负责 g_free(contents)
    } else {
        handleError("读取机器码失败",gerror);
        return NULL;
    }
}

size_t on_response(char* buffer,size_t size,size_t nitems,void* userdata)
{
    MLOG_D("回掉函数执行");
    return 0;
}


void sendConfigRequest(const char * inipath)
{
    //从配置文件中读取信息
    GKeyFile * newfile = g_key_file_new();
    GError * gerror = NULL;
    if(newfile)
    {
        if (!g_key_file_load_from_file(newfile, inipath, G_KEY_FILE_NONE, &gerror))
        {
            handleError("文件读取失败", gerror);
        }
        else
        {
     
            gchar * backendUrl = g_key_file_get_string(newfile, "serverAddress", "backendUrl", &gerror);
            if (!backendUrl)
            {
                handleError("读取backendUrl失败", gerror);
            }
            gchar * chip = g_key_file_get_string(newfile, "Address", "chip", &gerror);
            if (!chip)
            {
                handleError("读取chip失败", gerror);
            }
            gchar * detailAddr = g_key_file_get_string(newfile, "Address", "detailAddr", &gerror);
            if (!detailAddr)
            {
                handleError("读取detailAddr失败", gerror);
            }

            //构建后端服务器访问网址
            gchar * sn = get_sn();
            const char * urlform = "http://%s?chip=%s&detailAddr=%s&sn=%s";
            gchar url[SIZE256];
            sprintf(url,urlform,backendUrl,chip,detailAddr,sn);
            g_free(sn);
            sendGetRequest(url,on_response);
        }
        g_key_file_free(newfile);
    }
    
}
