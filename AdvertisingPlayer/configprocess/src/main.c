#include "configprocess.h"


void fn(struct mg_connection *c, int ev, void *ev_data)
{
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        // 处理根路径请求，返回 index.html 文件
        if(mg_match(hm->uri, mg_str("/form_response.html"), NULL))
        {
            struct mg_http_serve_opts opts = {.root_dir = "."};
            mg_http_serve_file(c, hm,RESPONSE , &opts);
        }
        else if (mg_match(hm->uri, mg_str("/submit"), NULL)) 
        {
            parseConfig(c,hm);
            
            
        }
        else 
        {
            // 直接返回 index.html 文件
            struct mg_http_serve_opts opts = {.root_dir = "."};
            mg_http_serve_file(c, hm, HTML_ROOT, &opts);
        }
    }
}

int main()
{
    struct mg_mgr mgr;          // 1. 声明一个事件管理器
    mg_mgr_init(&mgr);          // 2. 初始化管理器

    // 3. 监听8888端口，并将 fn 设置为该端口上所有连接的事件处理函数
    mg_http_listen(&mgr, "http://0.0.0.0:8888", fn, NULL);

    printf("Server started on http://0.0.0.0:8888\n");
    printf("Visit http://localhost:8888 for the test page\n");

    // 4. 主事件循环，持续处理网络事件
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);          // 5. 释放资源
    return 0;
}