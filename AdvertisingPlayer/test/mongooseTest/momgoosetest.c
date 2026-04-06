#include "../../3rd-lib/include/mongoose.h"

// 事件处理函数，所有网络事件都在这里处理
static void fn(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;

        // 处理根路径请求，返回 index.html 文件
        if (mg_match(hm->uri, mg_str("/"), NULL)) {
            // 直接返回 index.html 文件
            struct mg_http_serve_opts opts = {.root_dir = "."};
            mg_http_serve_file(c, hm, "index.html", &opts);
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
            
            char response[1000] = {0};
            snprintf(response, sizeof(response), 
                "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<title>表单提交</title>"
                "<style>"
                "body { font-family: Arial, sans-serif; margin: 40px; }"
                ".response { padding: 20px; background: #d4edda; color: #155724; border: 1px solid #c3e6cb; border-radius: 4px; max-width: 600px; }"
                "a { color: #007bff; text-decoration: none; }"
                "a:hover { text-decoration: underline; }"
                "</style>"
                "</head>"
                "<body>"
                "<div class='response'>"
                "<h2>表单提交成功！</h2>"
                "<p>你好，%s！感谢您提交表单。</p>"
                "<p><a href='/'>返回首页</a></p>"
                "</div>"
                "</body>"
                "</html>", name);
            
            mg_http_reply(c, 200, "Content-Type: text/html; charset=utf-8\n", "%s", response);
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

int main() {
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
