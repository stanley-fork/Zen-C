#include <ctype.h>
#include "cmd.h"
#include "colors.h"
#include "../zprep.h"
#include "../codegen/compat.h"
#include "../zen/zen_facts.h"
#include "../platform/os.h"
#include "../parser/parser.h"

void print_search_paths()
{
    printf("Search paths:\n");
    for (int i = 0; i < g_config.include_path_count; i++)
    {
        printf("  %s\n", g_config.include_paths[i]);
    }
    printf("  ./\n");
    if (g_config.root_path)
    {
        printf("  %s\n", g_config.root_path);
        printf("  %s/std\n", g_config.root_path);
    }
}

void print_version()
{
    printf(COLOR_BOLD "zc" COLOR_RESET " %s\n", ZEN_VERSION);
}

static int get_visible_length(const char *str)
{
    int len = 0;
    const char *p = str;
    while (*p)
    {
        if (*p == '\033' && *(p + 1) == '[')
        {
            p += 2;
            while (*p && *p != 'm')
            {
                p++;
            }
            if (*p == 'm')
            {
                p++;
            }
        }
        else
        {
            len++;
            p++;
        }
    }
    return len;
}

static void print_help_item(const char *option, const char *description)
{
    printf("  %s", option);
    int visible_len = get_visible_length(option) + 2; // +2 for the leading spaces
    int target_col = 30;

    if (visible_len >= target_col - 1)
    {
        printf("\n%-*s", target_col, "");
    }
    else
    {
        for (int i = 0; i < target_col - visible_len; i++)
        {
            putchar(' ');
        }
    }
    printf("%s\n", description);
}

void print_usage()
{
    printf(COLOR_BOLD "Zen C" COLOR_RESET " - The language of monks\n\n");
    printf(COLOR_BOLD "USAGE:" COLOR_RESET " zc [COMMAND] [OPTIONS] [FILES...]\n\n");
    printf("A modern, high-performance C transpiler with advanced features.\n\n");

    printf(COLOR_BOLD "COMMANDS:" COLOR_RESET "\n");
    print_help_item(COLOR_GREEN "run" COLOR_RESET, "Compile and execute the program immediately");
    print_help_item(COLOR_GREEN "build" COLOR_RESET, "Compile to a standalone executable");
    print_help_item(COLOR_GREEN "check" COLOR_RESET, "Perform syntax and type checking only");
    print_help_item(COLOR_GREEN "repl" COLOR_RESET, "Start the interactive REPL shell");
    print_help_item(COLOR_GREEN "transpile" COLOR_RESET, "Generate C code without compilation");
    print_help_item(COLOR_GREEN "lsp" COLOR_RESET, "Start the Language Server (LSP)");

    printf("\n" COLOR_BOLD "GENERAL OPTIONS:" COLOR_RESET "\n");
    print_help_item(COLOR_CYAN "-o" COLOR_RESET " <file>", "Set the output executable name");
    print_help_item(COLOR_CYAN "-I" COLOR_RESET " <dir>", "Add directory to include search path");
    print_help_item(COLOR_CYAN "-L" COLOR_RESET " <dir>", "Add directory to library search path");
    print_help_item(COLOR_CYAN "-l" COLOR_RESET " <lib>", "Link against a specific library");
    print_help_item(COLOR_CYAN "-D" COLOR_RESET " <name>[=val]", "Define a preprocessor macro");
    print_help_item(COLOR_CYAN "--cc" COLOR_RESET " <compiler>",
                    "Specify the backend C compiler (gcc, clang, tcc)");

    printf("\n" COLOR_BOLD "BUILD & OPTIMIZATION:" COLOR_RESET "\n");
    print_help_item(COLOR_CYAN "-O" COLOR_RESET "<level>", "Set optimization level (0-3)");
    print_help_item(COLOR_CYAN "-g" COLOR_RESET, "Include debug information (default)");
    print_help_item(COLOR_CYAN "-g0" COLOR_RESET ", " COLOR_CYAN "--no-debug" COLOR_RESET,
                    "Disable debug information");
    print_help_item(COLOR_CYAN "--release" COLOR_RESET, "Enable release mode (no-debug + -O3)");
    print_help_item(COLOR_CYAN "-c" COLOR_RESET, "Compile only; do not link");
    print_help_item(COLOR_CYAN "-S" COLOR_RESET, "Produce assembly code instead of executable");
    print_help_item(COLOR_CYAN "-E" COLOR_RESET, "Preprocess the source files only");
    print_help_item(COLOR_CYAN "-shared" COLOR_RESET, "Create a shared library (.so, .dll)");

    printf("\n" COLOR_BOLD "LANGUAGE & SEMANTICS:" COLOR_RESET "\n");
    print_help_item(COLOR_CYAN "--check" COLOR_RESET,
                    "Enable full semantic analysis (borrow/move checker)");
    print_help_item(COLOR_CYAN "--cpp" COLOR_RESET, "Enable C++ compatibility mode");
    print_help_item(COLOR_CYAN "--objective-c" COLOR_RESET,
                    "Enable Objective-C compatibility mode");
    print_help_item(COLOR_CYAN "--cuda" COLOR_RESET,
                    "Enable CUDA compatibility mode (requires nvcc)");
    print_help_item(COLOR_CYAN "--freestanding" COLOR_RESET,
                    "Enable freestanding mode (no standard library)");

    printf("\n" COLOR_BOLD "OUTPUT & DEBUGGING:" COLOR_RESET "\n");
    print_help_item(COLOR_CYAN "-v" COLOR_RESET ", " COLOR_CYAN "--verbose" COLOR_RESET,
                    "Display verbose compilation output");
    print_help_item(COLOR_CYAN "-q" COLOR_RESET ", " COLOR_CYAN "--quiet" COLOR_RESET,
                    "Suppress all non-essential output");
    print_help_item(COLOR_CYAN "--json" COLOR_RESET, "Emit compilation diagnostics in JSON format");
    print_help_item(COLOR_CYAN "--no-suppress-warnings" COLOR_RESET,
                    "Display all default C backend warnings");
    print_help_item(COLOR_CYAN "--emit-c" COLOR_RESET, "Keep the generated C source files");
    print_help_item(COLOR_CYAN "--keep-comments" COLOR_RESET,
                    "Preserve comments in the generated C code");

    printf("\n" COLOR_BOLD "ADVANCED C-BACKEND OPTIONS:" COLOR_RESET "\n");
    print_help_item(COLOR_CYAN "-W" COLOR_RESET "<warn>", "Forward warning flag to C compiler");
    print_help_item(COLOR_CYAN "-f" COLOR_RESET "<feat>", "Forward feature flag to C compiler");
    print_help_item(COLOR_CYAN "-m" COLOR_RESET "<arch>",
                    "Forward architecture flag to C compiler");
    print_help_item(COLOR_CYAN "-x" COLOR_RESET "<lang>", "Specify input language to C compiler");

    printf("\n" COLOR_BOLD "INFO & MISC:" COLOR_RESET "\n");
    print_help_item(COLOR_CYAN "--help" COLOR_RESET, "Display this help message and exit");
    print_help_item(COLOR_CYAN "--paths" COLOR_RESET, "Display library search paths");
    print_help_item(COLOR_CYAN "--version" COLOR_RESET, "Display version information and exit");
    print_help_item(COLOR_CYAN "--zen" COLOR_RESET, "Display Zen facts and easter eggs");
}

void build_compile_arg_list(ArgList *list, const char *outfile, const char *temp_source_file)
{
    // Compiler
    arg_list_add_from_string(list, g_config.cc);

    // GCC Flags
    arg_list_add_from_string(list, g_config.gcc_flags);
    arg_list_add_from_string(list, g_cflags);

    // Suppress warnings triggered by transpiled code
    if (!g_config.no_suppress_warnings)
    {
        arg_list_add(list, "-Wno-parentheses");
        arg_list_add(list, "-Wno-unused-value");
        arg_list_add(list, "-Wno-unused-variable");
        arg_list_add(list, "-Wno-unused-parameter");
        arg_list_add(list, "-Wno-unused-function");
        arg_list_add(list, "-Wno-unused-but-set-variable");
        arg_list_add(list, "-Wno-sign-compare");
        arg_list_add(list, "-Wno-missing-field-initializers");
    }

    // Freestanding
    if (g_config.is_freestanding)
    {
        arg_list_add(list, "-ffreestanding");
    }

    // Quiet
    if (g_config.quiet)
    {
        arg_list_add(list, "-w");
    }

    // C++ compatibility flags
    if (g_config.use_cpp)
    {
        arg_list_add(list, "-fpermissive");
        arg_list_add(list, "-Wno-write-strings");
    }

    // Output file
    arg_list_add(list, "-o");
    arg_list_add(list, outfile);

    // Input files
    arg_list_add(list, temp_source_file);
    for (int i = 0; i < g_config.c_file_count; i++)
    {
        arg_list_add(list, g_config.c_files[i]);
    }

    // Platform flags
    if (!z_is_windows() && !g_config.is_freestanding)
    {
        arg_list_add(list, "-lm");
        if (g_parser_ctx && g_parser_ctx->has_async)
        {
            arg_list_add(list, "-lpthread");
        }
    }

    // Linker flags
    arg_list_add_from_string(list, g_link_flags);
    if (z_is_windows())
    {
        arg_list_add(list, "-lws2_32");
    }

    // Include paths
    if (g_config.root_path && g_config.root_path[0])
    {
        arg_list_add_fmt(list, "-I%s", g_config.root_path);

        char tre_path[1024];
        snprintf(tre_path, sizeof(tre_path), "%s/std/third-party/tre/include", g_config.root_path);

        if (!g_config.is_freestanding && access(tre_path, F_OK) == 0)
        {
            arg_list_add_fmt(list, "-I%s", tre_path);
        }
    }
    else
    {
        arg_list_add(list, "-I.");
    }
}

void cmd_init(CmdBuilder *cmd)
{
    cmd->cap = 1024;
    cmd->len = 0;
    cmd->buf = xmalloc(cmd->cap);
    cmd->buf[0] = '\0';
}

static void ensure_cap(CmdBuilder *cmd, size_t needed)
{
    if (cmd->len + needed >= cmd->cap)
    {
        while (cmd->len + needed >= cmd->cap)
        {
            cmd->cap *= 2;
        }
        cmd->buf = xrealloc(cmd->buf, cmd->cap);
    }
}

void cmd_add(CmdBuilder *cmd, const char *str)
{
    if (!str || !str[0])
    {
        return;
    }

    size_t len = strlen(str);
    size_t needed = len + 1 + 1; // + space + null terminator

    ensure_cap(cmd, needed);

    if (cmd->len > 0 && cmd->buf[cmd->len - 1] != ' ')
    {
        strcat(cmd->buf, " ");
        cmd->len++;
    }

    strcat(cmd->buf, str);
    cmd->len += len;
}

void cmd_add_fmt(CmdBuilder *cmd, const char *fmt, ...)
{
    va_list args;

    // First pass to get size
    va_start(args, fmt);
    int size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (size < 0)
    {
        return;
    }

    size_t needed = size + 1 + 1; // + space + null
    ensure_cap(cmd, needed);

    if (cmd->len > 0 && cmd->buf[cmd->len - 1] != ' ')
    {
        strcat(cmd->buf, " ");
        cmd->len++;
    }

    va_start(args, fmt);
    vsnprintf(cmd->buf + cmd->len, cmd->cap - cmd->len, fmt, args);
    va_end(args);

    cmd->len += size;
}

void cmd_free(CmdBuilder *cmd)
{
    free(cmd->buf);
    cmd->buf = NULL;
    cmd->len = 0;
    cmd->cap = 0;
}

const char *cmd_to_string(CmdBuilder *cmd)
{
    return cmd->buf;
}

void arg_list_init(ArgList *list)
{
    list->cap = 32;
    list->count = 0;
    list->args = xmalloc(list->cap * sizeof(char *));
}

void arg_list_add(ArgList *list, const char *arg)
{
    if (!arg)
    {
        return;
    }
    if (list->count + 1 >= list->cap)
    {
        list->cap *= 2;
        list->args = xrealloc(list->args, list->cap * sizeof(char *));
    }
    list->args[list->count++] = xstrdup(arg);
    list->args[list->count] = NULL;
}

void arg_list_add_fmt(ArgList *list, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);

    if (size < 0)
    {
        return;
    }

    char *buf = xmalloc(size + 1);
    va_start(args, fmt);
    vsnprintf(buf, size + 1, fmt, args);
    va_end(args);

    arg_list_add(list, buf);
    free(buf);
}

void arg_list_free(ArgList *list)
{
    for (size_t i = 0; i < list->count; i++)
    {
        free(list->args[i]);
    }
    free(list->args);
    list->args = NULL;
    list->count = 0;
    list->cap = 0;
}

int arg_run(ArgList *list)
{
    return z_run_command(list->args);
}

void arg_list_add_from_string(ArgList *list, const char *str)
{
    if (!str || !str[0])
    {
        return;
    }

    const char *p = str;
    while (*p)
    {
        while (*p && isspace((unsigned char)*p))
        {
            p++;
        }
        if (!*p)
        {
            break;
        }

        char arg[4096];
        char *d = arg;
        int in_quote = 0;

        while (*p && (in_quote || (!isspace((unsigned char)*p) && *p != '\r')))
        {
            if (*p == '\\' && *(p + 1) == '\"')
            {
                if (d - arg < 4095)
                {
                    *d++ = '\"';
                }
                p += 2;
            }
            else if (*p == '\"')
            {
                in_quote = !in_quote;
                p++;
            }
            else
            {
                if (d - arg < 4095)
                {
                    *d++ = *p++;
                }
                else
                {
                    p++;
                }
            }
        }
        *d = '\0';
        arg_list_add(list, arg);
    }
}
