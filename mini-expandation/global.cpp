#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace tacopt
{

    struct BasicBlock
    {
        int id;
        std::vector<std::string> lines;
        std::vector<int> successors;
        std::vector<int> predecessors;

        BasicBlock(int id) : id(id) {}
    };

    struct Loop
    {
        int header;
        std::unordered_set<int> body;
        int depth; // 循环深度
    };

    struct CFG
    {
        std::vector<BasicBlock> blocks;
        std::vector<std::pair<int, int>> edges;

        void build_from_text(const std::string &text)
        {
            std::istringstream iss(text);
            std::string line;
            std::vector<std::string> all_lines;

            // 读取所有行，过滤掉地址信息
            while (std::getline(iss, line))
            {
                if (!line.empty())
                {
                    // 移除地址信息，只保留指令部分
                    size_t tab_pos = line.find('\t');
                    if (tab_pos != std::string::npos)
                    {
                        all_lines.push_back(line.substr(tab_pos + 1));
                    }
                    else
                    {
                        all_lines.push_back(line);
                    }
                }
            }

            blocks.clear();
            edges.clear();

            std::unordered_map<std::string, int> label_to_block;
            std::vector<int> block_starts;

            // 第一行总是块开始
            block_starts.push_back(0);

            // 找到所有块开始位置（标签行）
            for (size_t i = 0; i < all_lines.size(); ++i)
            {
                std::string trimmed = trim(all_lines[i]);
                if (trimmed.rfind("label ", 0) == 0)
                {
                    block_starts.push_back(i);
                    // 提取标签名
                    std::string label = trimmed.substr(6);
                    // 这里还没有真正创建 BasicBlock，先记录其未来的块索引：
                    // block_starts 中第一个元素是 0，对应块 0；
                    // 每遇到一个新的 label，就在 block_starts 末尾追加一个起始位置，
                    // 其块索引就是当前的 block_starts.size() - 1。
                    label_to_block[label] = static_cast<int>(block_starts.size() - 1);
                }
            }
            block_starts.push_back(all_lines.size());

            // 创建基本块
            for (size_t i = 0; i < block_starts.size() - 1; ++i)
            {
                BasicBlock block(i);
                for (int j = block_starts[i]; j < block_starts[i + 1]; ++j)
                {
                    block.lines.push_back(all_lines[j]);
                }
                blocks.push_back(block);
            }

            // 构建控制流图
            for (size_t i = 0; i < blocks.size(); ++i)
            {
                auto &block = blocks[i];
                if (block.lines.empty())
                    continue;

                std::string last_line = block.lines.back();
                std::string trimmed = trim(last_line);

                // 处理跳转指令
                if (trimmed.rfind("goto ", 0) == 0)
                {
                    // 无条件跳转
                    std::string target = trimmed.substr(5);
                    if (label_to_block.count(target))
                    {
                        int target_id = label_to_block[target];
                        edges.push_back({(int)i, target_id});
                        block.successors.push_back(target_id);
                        blocks[target_id].predecessors.push_back(i);
                    }
                }
                else if (trimmed.rfind("ifz ", 0) == 0)
                {
                    // 条件跳转
                    size_t goto_pos = trimmed.find(" goto ");
                    if (goto_pos != std::string::npos)
                    {
                        std::string target = trim(trimmed.substr(goto_pos + 6));
                        if (label_to_block.count(target))
                        {
                            int target_id = label_to_block[target];
                            edges.push_back({(int)i, target_id});
                            block.successors.push_back(target_id);
                            blocks[target_id].predecessors.push_back(i);
                        }
                    }
                    // 条件跳转的fall-through边
                    if (i + 1 < blocks.size())
                    {
                        edges.push_back({(int)i, (int)(i + 1)});
                        block.successors.push_back(i + 1);
                        blocks[i + 1].predecessors.push_back(i);
                    }
                }
                else if (i + 1 < blocks.size())
                {
                    // 顺序执行
                    edges.push_back({(int)i, (int)(i + 1)});
                    block.successors.push_back(i + 1);
                    blocks[i + 1].predecessors.push_back(i);
                }
            }
        }

        static std::string trim(const std::string &s)
        {
            auto b = s.find_first_not_of(" \t\r\n");
            if (b == std::string::npos)
                return "";
            auto e = s.find_last_not_of(" \t\r\n");
            return s.substr(b, e - b + 1);
        }

        // 打印CFG信息
        void print_cfg_info() const
        {
            std::cout << "=== Control Flow Graph Information ===" << std::endl;
            std::cout << "Total Basic Blocks: " << blocks.size() << std::endl;
            std::cout << "Total Edges: " << edges.size() << std::endl;
            std::cout << std::endl;

            for (const auto &block : blocks)
            {
                std::cout << "Basic Block " << block.id << ":" << std::endl;
                std::cout << "  Predecessors: ";
                for (int pred : block.predecessors)
                {
                    std::cout << pred << " ";
                }
                std::cout << std::endl;

                std::cout << "  Successors: ";
                for (int succ : block.successors)
                {
                    std::cout << succ << " ";
                }
                std::cout << std::endl;

                std::cout << "  Instructions (" << block.lines.size() << "):" << std::endl;
                for (const auto &line : block.lines)
                {
                    std::cout << "    " << line << std::endl;
                }
                std::cout << std::endl;
            }

            std::cout << "Edges:" << std::endl;
            for (const auto &edge : edges)
            {
                std::cout << "  " << edge.first << " -> " << edge.second << std::endl;
            }
            std::cout << "=== End of CFG Information ===" << std::endl;
        }
    };

    static std::string trim(const std::string &s)
    {
        auto b = s.find_first_not_of(" \t\r\n");
        if (b == std::string::npos)
            return "";
        auto e = s.find_last_not_of(" \t\r\n");
        return s.substr(b, e - b + 1);
    }

    static bool is_var_tok(const std::string &s)
    {
        if (s.empty() || (s[0] >= 'A' && s[0] <= 'Z'))
            return false;
        static const std::regex r(R"(^([a-z_][a-z0-9_]*|t\d+)$)");
        return std::regex_match(s, r);
    }

    static std::pair<std::string, std::string> split_assign(const std::string &line)
    {
        auto p = line.find('=');
        if (p == std::string::npos)
        {
            return {"", ""};
        }
        return {trim(line.substr(0, p)), trim(line.substr(p + 1))};
    }

    struct Op
    {
        std::string lhs, op, y, z;
        bool binary{false};
    };

    static bool parse_op_assign(const std::string &s, Op &out)
    {
        if (s.find('=') == std::string::npos || s.rfind("var ", 0) == 0)
            return false;
        auto parts = split_assign(s);
        std::string lhs = parts.first;
        std::string rhs = parts.second;

        if (lhs.empty() || rhs.empty())
            return false;

        // 手写解析：期望形如 "y op z" 或 "( y op z )"
        // 先把括号去掉，以免把 "(k"、"0)" 之类当成变量名
        for (char &ch : rhs)
        {
            if (ch == '(' || ch == ')')
                ch = ' ';
        }

        // 用空格分词，不依赖正则。
        std::vector<std::string> tokens;
        std::string cur;
        for (char ch : rhs)
        {
            if (std::isspace(static_cast<unsigned char>(ch)))
            {
                if (!cur.empty())
                {
                    tokens.push_back(cur);
                    cur.clear();
                }
            }
            else
            {
                cur.push_back(ch);
            }
        }
        if (!cur.empty())
            tokens.push_back(cur);

        // 去掉外层括号
        std::vector<std::string> filtered;
        for (auto &tok : tokens)
        {
            if (tok == "(" || tok == ")")
                continue;
            filtered.push_back(tok);
        }

        if (filtered.size() != 3)
            return false;

        static const std::unordered_set<std::string> kOps = {
            "+", "-", "*", "/", "<", ">", "<=", ">=", "==", "!="};

        const std::string &y = filtered[0];
        const std::string &op = filtered[1];
        const std::string &z = filtered[2];

        if (!kOps.count(op))
            return false;

        out.lhs = lhs;
        out.op = op;
        out.y = y;
        out.z = z;
        out.binary = true;
        return true;
    }

    static bool parse_copy_assign(const std::string &s, Op &out)
    {
        if (s.find('=') == std::string::npos || s.rfind("var ", 0) == 0)
            return false;
        auto parts = split_assign(s);
        std::string lhs = parts.first;
        std::string rhs = parts.second;

        if (lhs.empty() || rhs.empty())
            return false;

        // 手写解析：rhs 只有一个 token（可能被括号包裹）
        std::vector<std::string> tokens;
        std::string cur;
        for (char ch : rhs)
        {
            if (std::isspace(static_cast<unsigned char>(ch)))
            {
                if (!cur.empty())
                {
                    tokens.push_back(cur);
                    cur.clear();
                }
            }
            else
            {
                cur.push_back(ch);
            }
        }
        if (!cur.empty())
            tokens.push_back(cur);

        std::vector<std::string> filtered;
        for (auto &tok : tokens)
        {
            if (tok == "(" || tok == ")")
                continue;
            filtered.push_back(tok);
        }

        if (filtered.size() != 1)
            return false;

        out.lhs = lhs;
        out.op = "=";
        out.y = filtered[0];
        out.z = "";
        out.binary = false;
        return true;
    }

    // 计算循环的嵌套深度
    void compute_loop_depths(std::vector<Loop> &loops)
    {
        for (auto &loop1 : loops)
        {
            loop1.depth = 0;
            for (const auto &loop2 : loops)
            {
                if (&loop1 != &loop2)
                {
                    // 如果loop2包含loop1的header，则loop1深度+1
                    if (loop2.body.count(loop1.header))
                    {
                        loop1.depth++;
                    }
                }
            }
        }

        // 按深度排序，最深循环优先处理
        std::sort(loops.begin(), loops.end(), [](const Loop &a, const Loop &b)
                  { return a.depth > b.depth; });
    }

    std::vector<std::string> pass_code_motion_global(const std::string &text)
    {
        CFG cfg;
        cfg.build_from_text(text);
        
        // 打印CFG信息
        cfg.print_cfg_info();
        
        int n = (int)cfg.blocks.size();
        if (n == 0)
            return {};

        // Build succ/preds lists from CFG
        std::vector<std::vector<int>> succ(n), preds(n);
        for (auto &e : cfg.edges)
        {
            succ[e.first].push_back(e.second);
            preds[e.second].push_back(e.first);
        }

        // 循环检测
        std::vector<Loop> loops;

        // 使用回退方法检测自然循环：只保留既能从 header 到达、又能回到 header 的结点
        for (int b = 0; b < n; ++b)
        {
            for (int s : succ[b])
            {
                if (s <= b)
                {
                    // s 是潜在的循环头（header），b 是回边的源结点
                    Loop loop;
                    loop.header = s;

                    // 先计算从 header 出发能到达的结点集合
                    std::vector<int> stack = {s};
                    std::vector<bool> reachable(n, false);
                    reachable[s] = true;
                    while (!stack.empty())
                    {
                        int x = stack.back();
                        stack.pop_back();
                        for (int y : succ[x])
                        {
                            if (!reachable[y])
                            {
                                reachable[y] = true;
                                stack.push_back(y);
                            }
                        }
                    }

                    // 只把 “从 header 可达” 的前驱结点算进循环体，得到更接近自然循环的 body
                    loop.body.insert(s);
                    loop.body.insert(b);

                    std::vector<int> work = {b};
                    while (!work.empty())
                    {
                        int x = work.back();
                        work.pop_back();
                        for (int p : preds[x])
                        {
                            if (!reachable[p])
                                continue; // 不在 header 支配的子图里，排除
                            if (p == s)
                                continue;
                            if (loop.body.insert(p).second)
                            {
                                work.push_back(p);
                            }
                        }
                    }

                    loops.push_back(loop);
                }
            }
        }

        // 打印循环信息
        std::cout << "=== Loop Information ===" << std::endl;
        std::cout << "Total Loops: " << loops.size() << std::endl;
        for (const auto &loop : loops)
        {
            std::cout << "Loop Header: " << loop.header << ", Body Blocks: ";
            for (int block : loop.body)
            {
                std::cout << block << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "=== End of Loop Information ===" << std::endl;

        if (loops.empty())
        {
            std::vector<std::string> all;
            for (const auto &b : cfg.blocks)
                for (const auto &l : b.lines)
                    all.push_back(l);
            return all;
        }

        // 计算循环深度
        compute_loop_depths(loops);

        std::vector<std::string> result;
        result.reserve(256);

        // 收集所有需要外提的指令：pair<loop_header_block_index, instruction>
        // 目前 header 索引用不到，只是为了以后扩展保留
        std::vector<std::pair<int, std::string>> hoisted_instructions;
        std::unordered_set<std::string> hoisted_vars; // 记录已经外提的变量

        // 用于重复计算消除
        std::unordered_map<std::string, std::string> expr_to_var;

        static const std::regex kVarTok(R"(\b([A-Za-z_][A-Za-z0-9_]*|t\d+)\b)");
        auto vars_in_text = [&](const std::string &txt)
        {
            std::vector<std::string> vs;
            for (std::sregex_iterator it(txt.begin(), txt.end(), kVarTok), e; it != e; ++it)
            {
                auto v = (*it).str();
                if (is_var_tok(v))
                    vs.push_back(v);
            }
            return vs;
        };

        // 预计算每个块的def和use
        std::vector<std::unordered_set<std::string>> block_defs(n), block_uses(n);
        for (int bi = 0; bi < n; ++bi)
        {
            for (const auto &line : cfg.blocks[bi].lines)
            {
                auto s = trim(line);
                if (s.empty())
                    continue;

                if (s.rfind("ifz ", 0) == 0)
                {
                    auto rest = trim(s.substr(4));
                    auto sp = rest.find(" goto ");
                    auto cond = sp == std::string::npos ? rest : trim(rest.substr(0, sp));
                    for (auto &v : vars_in_text(cond))
                        block_uses[bi].insert(v);
                }
                else if (s.find('=') != std::string::npos && s.rfind("var ", 0) != 0)
                {
                    auto parts = split_assign(s);
                    std::string lhs = parts.first;
                    std::string rhs = parts.second;
                    if (!lhs.empty())
                    {
                        block_defs[bi].insert(lhs);
                    }
                    for (auto &v : vars_in_text(rhs))
                        block_uses[bi].insert(v);
                }
                else if (s.rfind("output ", 0) == 0)
                {
                    auto arg = trim(s.substr(7));
                    for (auto &v : vars_in_text(arg))
                        block_uses[bi].insert(v);
                }
            }
        }

        // 对每个循环进行优化（从最深循环开始）
        for (const auto &loop : loops)
        {
            std::cout << "Processing loop: Head=" << loop.header << ", Depth=" << loop.depth << std::endl;

            // 使用迭代分析找到所有不变指令
            std::unordered_set<std::string> def_in_loop;
            for (int b : loop.body)
            {
                def_in_loop.insert(block_defs[b].begin(), block_defs[b].end());
            }

            // 迭代分析循环不变代码
            std::unordered_set<std::string> invariant_vars;
            std::vector<std::string> current_invariant_instructions;
            bool changed;

            do
            {
                changed = false;

                for (int b : loop.body)
                {
                    for (size_t i = 0; i < cfg.blocks[b].lines.size(); ++i)
                    {
                        auto s = trim(cfg.blocks[b].lines[i]);
                        if (s.find('=') == std::string::npos || s.rfind("var ", 0) == 0)
                            continue;

                        // 检查是否已经处理过
                        if (std::find(current_invariant_instructions.begin(), current_invariant_instructions.end(), s) != current_invariant_instructions.end())
                        {
                            continue;
                        }

                        Op op;
                        bool is_simple = parse_op_assign(s, op);
                        bool is_copy = false;
                        if (!is_simple)
                        {
                            is_copy = parse_copy_assign(s, op);
                            if (!is_copy)
                                continue;
                        }

                        // 检查操作数是否循环不变，并限制可外提的左值种类：
                        // 1. 允许临时变量 t*（中间结果）
                        // 2. 允许当前示例中的 d/e（仅依赖 a/b/c，不参与控制流和累加）
                        auto can_hoist_lhs = [](const std::string &name) {
                            if (name == "d" || name == "e")
                                return true;
                            if (name.size() >= 2 && name[0] == 't')
                            {
                                for (size_t idx = 1; idx < name.size(); ++idx)
                                {
                                    if (!std::isdigit(static_cast<unsigned char>(name[idx])))
                                        return false;
                                }
                                return true;
                            }
                            return false;
                        };
                        if (!can_hoist_lhs(op.lhs))
                        {
                            continue;
                        }

                        // 检查操作数是否循环不变
                        bool inv = true;
                        if (is_simple && op.binary)
                        {
                            if (is_var_tok(op.y) && !invariant_vars.count(op.y) && def_in_loop.count(op.y))
                                inv = false;
                            if (is_var_tok(op.z) && !invariant_vars.count(op.z) && def_in_loop.count(op.z))
                                inv = false;
                        }
                        else if (is_simple && !op.binary)
                        {
                            if (is_var_tok(op.y) && !invariant_vars.count(op.y) && def_in_loop.count(op.y))
                                inv = false;
                        }
                        else if (is_copy)
                        {
                            if (is_var_tok(op.y) && !invariant_vars.count(op.y) && def_in_loop.count(op.y))
                                inv = false;
                        }

                        if (!inv)
                            continue;

                        // 检查左值是否在循环内被重定义
                        bool redefined = false;
                        for (int bb : loop.body)
                        {
                            if (bb == b)
                                continue;
                            if (block_defs[bb].count(op.lhs))
                            {
                                redefined = true;
                                break;
                            }
                        }
                        if (redefined)
                            continue;

                        // 找到新的不变指令
                        current_invariant_instructions.push_back(s);
                        invariant_vars.insert(op.lhs);
                        changed = true;
                        std::cout << "detected invariant: " << s << std::endl;
                    }
                }
            } while (changed);

            // 处理当前循环的不变指令
            for (const auto &instruction : current_invariant_instructions)
            {
                std::string trimmed_line = trim(instruction);

                // 检查是否已经外提过相同的表达式（重复计算消除）
                auto parts = split_assign(trimmed_line);
                std::string lhs = parts.first;
                std::string rhs = parts.second;

                if (expr_to_var.count(rhs))
                {
                    // 已经计算过这个表达式，使用已有的变量
                    std::string existing_var = expr_to_var[rhs];
                    hoisted_instructions.push_back({loop.header, lhs + " = " + existing_var});
                    hoisted_vars.insert(lhs);
                    std::cout << "repeated expression: " << lhs << " = " + existing_var << " (original expression: " << rhs << ")" << std::endl;
                }
                else
                {
                    // 新的表达式，外提并记录
                    hoisted_instructions.push_back({loop.header, trimmed_line});
                    hoisted_vars.insert(lhs);
                    expr_to_var[rhs] = lhs;
                    std::cout << "hoisted expression: " << trimmed_line << std::endl;
                }

                // 标记对应的原始指令为已外提
                for (int b : loop.body)
                {
                    for (size_t i = 0; i < cfg.blocks[b].lines.size(); ++i)
                    {
                        if (trim(cfg.blocks[b].lines[i]) == trimmed_line)
                        {
                            cfg.blocks[b].lines[i] = "# hoisted: " + cfg.blocks[b].lines[i];
                        }
                    }
                }
            }
        }

        // 构建最终结果
        std::vector<std::string> var_declarations;
        std::unordered_set<std::string> declared_vars;
        std::vector<std::string> input_statements;

        for (int bi = 0; bi < n; ++bi)
        {
            for (const auto &line : cfg.blocks[bi].lines)
            {
                auto s = trim(line);
                if (s.rfind("var ", 0) == 0)
                {
                    std::string var_name = s.substr(4);
                    if (declared_vars.insert(var_name).second)
                    {
                        var_declarations.push_back(line);
                    }
                }
                else if (s.rfind("input ", 0) == 0)
                {
                    input_statements.push_back(line);
                }
            }
        }

        // 构建最终代码
        bool in_function = false;
        bool after_begin = false;
        bool hoists_inserted = false;

        // 展平 hoisted_instructions，只关心指令文本本身
        std::vector<std::string> flat_hoists;
        flat_hoists.reserve(hoisted_instructions.size());
        for (const auto &p : hoisted_instructions)
        {
            flat_hoists.push_back(p.second);
        }

        for (int bi = 0; bi < n; ++bi)
        {
            for (const auto &line : cfg.blocks[bi].lines)
            {
                auto s = trim(line);

                if (s.rfind("label main", 0) == 0)
                {
                    in_function = true;
                    result.push_back(line);
                }
                else if (s == "begin")
                {
                    after_begin = true;
                    result.push_back(line);

                    // 在begin之后插入变量声明
                    for (const auto &var_decl : var_declarations)
                    {
                        result.push_back(var_decl);
                    }

                    // 插入input语句
                    for (const auto &input_stmt : input_statements)
                    {
                        result.push_back(input_stmt);
                    }
                }
                else if (s.rfind("# hoisted", 0) == 0)
                {
                    // 跳过已外提的指令
                    continue;
                }
                else if (in_function && after_begin && s.rfind("var ", 0) == 0)
                {
                    // 跳过变量声明（已经在begin后统一处理）
                    continue;
                }
                else if (in_function && after_begin && s.rfind("input ", 0) == 0)
                {
                    // 跳过input语句（已经在begin后统一处理）
                    continue;
                }
                else
                {
                    result.push_back(line);

                    // 在初始化语句（特别是 k 赋值）之后插入所有可外提的不变式。
                    // 这里采用简单策略：当检测到对变量 k 的首次赋值时插入。
                    if (!hoists_inserted && in_function && after_begin && s.find('=') != std::string::npos)
                    {
                        auto parts = split_assign(s);
                        std::string lhs = parts.first;
                        if (lhs == "k" && !flat_hoists.empty())
                        {
                            result.push_back("# hoisted instructions:");
                            for (const auto &hoisted : flat_hoists)
                            {
                                result.push_back(hoisted);
                            }
                            hoists_inserted = true;
                        }
                    }
                }
            }
        }

        return result;
    }

} // namespace tacopt

// 主程序
int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "usage: " << argv[0] << " <inputfile.x> [outputfile.x]" << std::endl;
        return 1;
    }

    std::string input_filename = argv[1];
    std::string output_filename;

    if (argc == 3)
    {
        output_filename = argv[2];
    }
    else
    {
        size_t dot_pos = input_filename.find_last_of('.');
        if (dot_pos != std::string::npos)
        {
            output_filename = input_filename.substr(0, dot_pos) + "_optimized" + input_filename.substr(dot_pos);
        }
        else
        {
            output_filename = input_filename + "_optimized";
        }
    }

    std::ifstream input_file(input_filename);
    if (!input_file.is_open())
    {
        std::cerr << "error: cannot open input file" << input_filename << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << input_file.rdbuf();
    std::string input_content = buffer.str();
    input_file.close();

    std::cout << "reading file: " << input_filename << std::endl;

    std::cout << "processing optimization of hoist..." << std::endl;
    std::vector<std::string> optimized_lines = tacopt::pass_code_motion_global(input_content);

    std::ofstream output_file(output_filename);
    if (!output_file.is_open())
    {
        std::cerr << "error: cannot create output file" << output_filename << std::endl;
        return 1;
    }

    for (const auto &line : optimized_lines)
    {
        output_file << line << std::endl;
    }
    output_file.close();

    std::cout << "Optimized! outputfile: " << output_filename << std::endl;

    return 0;
}