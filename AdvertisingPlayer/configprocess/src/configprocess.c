#include <glib-2.0/glib.h>
#include "configprocess.h"

void fn(struct mg_connection *c, int ev, void *ev_data)
{

    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        // 处理根路径请求，返回 index.html 文件
        if (mg_match(hm->uri, mg_str("/"), NULL)) {
            // 直接返回 index.html 文件
            struct mg_http_serve_opts opts = {.root_dir = "."};
            mg_http_serve_file(c, hm, HTML_ROOT, &opts);
        }
        // 处理 /api/hello 的 API 请求，返回一个 JSON
        else if (mg_match(hm->uri, mg_str("/api/hello"), NULL)) {
            mg_http_reply(c, 200, "Content-Type: application/json; charset=utf-8\n", "{\"result\": %d, \"message\": \"你好，来自 Mongoose！\"}\n", 1);
        }
        // 处理 /api/time 的 API 请求，返回当前时间
        else if (mg_match(hm->uri, mg_str("/api/time"), NULL)) {
            time_t now = time(NULL);
            struct tm *tm_info = localtime(&now);
            char time_str[64];
            strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);
            mg_http_reply(c, 200, "Content-Type: application/json; charset=utf-8\n", "{\"time\": \"%s\"}\n", time_str);
        }
        // 处理表单提交
        else if (mg_match(hm->uri, mg_str("/submit"), NULL)) {
            // 解析表单数据
            char name[100] = {0};
            mg_http_get_var(&hm->body, "name", name, sizeof(name));
            //返回
            struct mg_http_serve_opts opts = {.root_dir = "."};
            mg_http_serve_file(c, hm, RESPONSE, &opts);
            printf("返回表单响应-------------\n");
        }
        // 处理不同的 HTTP 方法
        else if (mg_match(hm->uri, mg_str("/method-test"), NULL)) {
            if (mg_match(hm->method, mg_str("GET"), NULL)) {
                mg_http_reply(c, 200, "Content-Type: text/plain; charset=utf-8\n", "这是一个 GET 请求\n");
            } else if (mg_match(hm->method, mg_str("POST"), NULL)) {
                mg_http_reply(c, 200, "Content-Type: text/plain; charset=utf-8\n", "这是一个 POST 请求\n");
            } else if (mg_match(hm->method, mg_str("PUT"), NULL)) {
                mg_http_reply(c, 200, "Content-Type: text/plain; charset=utf-8\n", "这是一个 PUT 请求\n");
            } else if (mg_match(hm->method, mg_str("DELETE"), NULL)) {
                mg_http_reply(c, 200, "Content-Type: text/plain; charset=utf-8\n", "这是一个 DELETE 请求\n");
            } else {
                mg_http_reply(c, 405, "Content-Type: text/plain; charset=utf-8\n", "不允许的方法\n");
            }
        }
        // 其他所有请求，都当作静态文件处理，从当前目录（"."）寻找
        else {
            struct mg_http_serve_opts opts = {.root_dir = "."};
            mg_http_serve_dir(c, hm, &opts);
        }
    }
}