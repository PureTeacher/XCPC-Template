import os

# 你的代码根目录，无需修改
root_dir = r"C:\Users\18354\Desktop\cppcode\templete"
# 最终输出的MD文件
output_md = os.path.join(root_dir, "XCPC模板.md")

# 存储目录、正文内容
toc_list = []
main_content = []

# 遍历所有子目录与文件
for dirpath, dirnames, filenames in os.walk(root_dir):
    # 获取当前子文件夹名称（一级标题）
    folder_name = os.path.basename(dirpath)
    # 跳过最外层根目录本身
    if folder_name == "templete":
        continue

    # 筛选当前文件夹内所有cpp代码文件
    cpp_file_list = [file for file in filenames if file.endswith(".cpp")]
    if len(cpp_file_list) == 0:
        continue

    # ========== 一级标题（文件夹），生成可跳转锚点 ==========
    main_content.append(f"\n# {folder_name}\n")
    # 目录项+可跳转链接
    toc_anchor = folder_name.replace(" ", "")
    toc_list.append(f"- [{folder_name}](#{toc_anchor})")

    # ========== 遍历每个代码文件 ==========
    for cpp_filename in cpp_file_list:
        file_full_path = os.path.join(dirpath, cpp_filename)
        # 【核心】去掉 .cpp 后缀，只保留纯文件名
        pure_name = os.path.splitext(cpp_filename)[0]

        # 读取源码，兼容UTF8/GBK编码，防止中文乱码
        try:
            with open(file_full_path, "r", encoding="utf-8") as code_file:
                code_text = code_file.read()
        except UnicodeDecodeError:
            with open(file_full_path, "r", encoding="gbk") as code_file:
                code_text = code_file.read()

        # 二级标题（无.cpp后缀）+ 标准cpp代码块 + 分割线
        main_content.append(f"## {pure_name}")
        main_content.append("```cpp")
        main_content.append(code_text)
        main_content.append("```")
        main_content.append("\n---\n")

        # 目录子项：无.cpp后缀 + 可跳转锚点链接
        file_anchor = pure_name.replace(" ", "")
        toc_list.append(f"  - [{pure_name}](#{file_anchor})")

# ========== 统一写入最终完整MD文件 ==========
with open(output_md, "w", encoding="utf-8") as md_file:
    # 文档大标题
    md_file.write("# 我的青春算竞物语果然有问题 XCPC 模板\n\n")
    # 顶部完整可跳转目录
    md_file.write("## 完整目录\n")
    md_file.write("\n".join(toc_list))
    md_file.write("\n\n---\n")
    # 正文全部内容
    md_file.write("\n".join(main_content))

print("=" * 50)
print("导出完成！")
print(f"文件保存路径：{output_md}")
print("=" * 50)
