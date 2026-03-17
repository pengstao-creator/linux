#!/usr/bin/env python3
# generate_network_io_mindmap.py
import json

# 思维导图结构（嵌套字典，易维护）
mindmap_data = {
    "网络IO模型": [
        {"课程简介": ["TCP编程基础", "四种网络IO模型"]},
        {
            "TCP基础": [
                "三次握手", "四次挥手",
                {
                    "基本编程结构": [
                        {"服务端流程": ["创建socket", "绑定地址", "监听连接", "接受连接", "数据收发", "关闭连接"]},
                        {"客户端流程": ["创建socket", "连接服务端", "数据收发", "关闭连接"]}
                    ]
                }
            ]
        },
        {
            "阻塞IO模型(Blocking IO)": [
                {"原理": ["两个阶段都被block(等待数据、拷贝数据)", "系统调用不返回直到操作完成"]},
                {"优缺点": ["优点：开发简单，容易入门", "缺点：一个线程维护一个IO，不适合大并发"]},
                {"适用场景": ["小规模并发(100以内)", "线程池/连接池技术"]}
            ]
        },
        # ... 此处按相同结构补充其他节点（epoll/select/poll等）
        {
            "IO多路复用模型": [
                {"共同目标": ["一个线程处理多个连接", "高效检测\"操作是否完成\""]},
                {
                    "epoll(Linux特有)": [
                        "实现方式：基于红黑树",
                        "跨平台性：仅Linux",
                        "连接数限制：无固定上限(受硬件限制)",
                        {"工作模式": [
                            "水平触发(LT)：默认，支持阻塞/非阻塞",
                            "边沿触发(ET)：高效，仅支持非阻塞"
                        ]}
                    ]
                }
            ]
        },
        {"模型对比与选择": [
            "小规模并发：阻塞IO + 线程池",
            "跨平台需求：select",
            "Linux高性能：epoll",
            "特定场景：信号驱动IO"
        ]}
    ]
}

def dict_to_markdown(node, indent=0):
    """递归生成缩进式Markdown（XMind兼容格式）"""
    lines = []
    if isinstance(node, dict):
        for k, v in node.items():
            prefix = "- " if indent > 0 else ""
            lines.append("  " * indent + prefix + k)
            if isinstance(v, list):
                for child in v:
                    lines.extend(dict_to_markdown(child, indent + 1))
    elif isinstance(node, str):
        lines.append("  " * indent + "- " + node)
    elif isinstance(node, list):
        for item in node:
            lines.extend(dict_to_markdown(item, indent))
    return lines

# 生成并保存
output = "\n".join(dict_to_markdown(mindmap_data))
with open("network_io_mindmap.md", "w", encoding="utf-8") as f:
    f.write(output)

print("✅ Markdown 生成成功！")
print("👉 操作：XMind → 文件 → 导入 → Markdown → 选择 network_io_mindmap.md")
print("💡 导入后立即保存为 .xmind 文件即可！")