#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
double _zc_pow(double, double) __asm__("pow");
#include <unistd.h>
#include <fcntl.h>
#define ZC_SIMD(T, N) T __attribute__((vector_size(N * sizeof(T))))
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202300L
#define ZC_AUTO auto
#define ZC_AUTO_INIT(var, init) auto var = (init)
#else
#define ZC_AUTO __auto_type
#define ZC_AUTO_INIT(var, init) __auto_type var = (init)
#endif
#define ZC_CAST(T, x) ((T)(x))
#ifdef __TINYC__
#undef ZC_AUTO
#define ZC_AUTO __auto_type
#undef ZC_AUTO_INIT
#define ZC_AUTO_INIT(var, init) __typeof__((init)) var = (init)

#ifndef __builtin_expect
#define __builtin_expect(x, v) (x)
#endif

#ifndef __builtin_unreachable
#define __builtin_unreachable()
#endif
#else
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202300L
#define ZC_AUTO_INIT(var, init) auto var = (init)
#else
#define ZC_AUTO_INIT(var, init) __auto_type var = (init)
#endif
#endif
static inline const char *_z_bool_str(_Bool b)
{
    return b ? "true" : "false";
}
#ifdef __SIZEOF_INT128__
static inline const char *_z_u128_str(unsigned __int128 val)
{
    static _Thread_local char buf[40];
    if (val == 0)
    {
        return "0";
    }
    int i = 38;
    buf[39] = 0;
    while (val > 0)
    {
        buf[i--] = (char)((val % 10) + '0');
        val /= 10;
    }
    return &buf[i + 1];
}
static inline const char *_z_i128_str(__int128 val)
{
    static _Thread_local char buf[41];
    if (val == 0)
    {
        return "0";
    }
    int neg = val < 0;
    unsigned __int128 uval = neg ? -val : val;
    int i = 39;
    buf[40] = 0;
    while (uval > 0)
    {
        buf[i--] = (char)((uval % 10) + '0');
        uval /= 10;
    }
    if (neg)
    {
        buf[i--] = '-';
    }
    return &buf[i + 1];
}
#define _z_128_map , __int128 : "%s", unsigned __int128 : "%s"
#else
#define _z_128_map
#endif
#ifdef __OBJC__
#define _z_objc_map , id : "%s", Class : "%s", SEL : "%s"
#define _z_objc_arg_map(x)                                                                         \
    , id : [(id)(x) description].UTF8String, Class : class_getName((Class)(x)),                    \
                                                     SEL : sel_getName((SEL)(x))
#else
#define _z_objc_map
#define _z_objc_arg_map(x)
#endif

#define _z_str(x)                                                                                  \
    _Generic((x),                                                                                  \
        _Bool: "%s",                                                                               \
        char: "%c",                                                                                \
        signed char: "%c",                                                                         \
        unsigned char: "%u",                                                                       \
        short: "%d",                                                                               \
        unsigned short: "%u",                                                                      \
        int: "%d",                                                                                 \
        unsigned int: "%u",                                                                        \
        long: "%ld",                                                                               \
        unsigned long: "%lu",                                                                      \
        long long: "%lld",                                                                         \
        unsigned long long: "%llu",                                                                \
        float: "%f",                                                                               \
        double: "%f",                                                                              \
        char *: "%s",                                                                              \
        const char *: "%s",                                                                        \
        void *: "%p" _z_128_map _z_objc_map)
#ifdef __SIZEOF_INT128__
#define _z_safe_i128(x) _Generic((x), __int128: (x), default: (__int128)0)
#define _z_safe_u128(x) _Generic((x), unsigned __int128: (x), default: (unsigned __int128)0)
#define _z_128_arg_map(x)                                                                          \
    , __int128 : _z_i128_str(_z_safe_i128(x)), unsigned __int128 : _z_u128_str(_z_safe_u128(x))
#else
#define _z_128_arg_map(x)
#endif
#define _z_safe_bool(x) _Generic((x), _Bool: (x), default: (_Bool)0)
#define _z_arg(x)                                                                                  \
    _Generic((x),                                                                                  \
        _Bool: _z_bool_str(_z_safe_bool(x)) _z_128_arg_map(x) _z_objc_arg_map(x),                  \
        default: (x))
typedef size_t usize;
typedef char *string;
typedef struct
{
    void *func;
    void *ctx;
    void (*drop)(void *);
} z_closure_T;
static void *_z_closure_ctx_stash[256];
typedef void U0;
typedef int8_t I8;
typedef uint8_t U8;
typedef int16_t I16;
typedef uint16_t U16;
typedef int32_t I32;
typedef uint32_t U32;
typedef int64_t I64;
typedef uint64_t U64;
#define F32 float
#define F64 double
#define z_malloc malloc
#define z_realloc realloc
#define z_free free
#define z_print printf
void z_panic(const char *msg)
{
    fprintf(stderr, "Panic: %s\n", msg);
    exit(1);
}
#if defined(__APPLE__)
#define _ZC_SEC __attribute__((used, section("__DATA,__zarch")))
#elif defined(_WIN32)
#define _ZC_SEC __attribute__((used))
#else
#define _ZC_SEC __attribute__((used, section(".note.zarch")))
#endif
static const unsigned char _zc_abi_v1[] _ZC_SEC = {0x07, 0xd5, 0x59, 0x30, 0x7c, 0x7f, 0x66,
                                                   0x75, 0x30, 0x69, 0x7f, 0x65, 0x3c, 0x30,
                                                   0x59, 0x7c, 0x79, 0x7e, 0x73, 0x71};
void _z_autofree_impl(void *p)
{
    void **pp = (void **)p;
    if (*pp)
    {
        z_free(*pp);
        *pp = NULL;
    }
}
#define assert(cond, ...)                                                                          \
    if (!(cond))                                                                                   \
    {                                                                                              \
        fprintf(stderr, "Assertion failed: " __VA_ARGS__);                                         \
        exit(1);                                                                                   \
    }
string _z_readln_raw()
{
    size_t cap = 64;
    size_t len = 0;
    char *line = z_malloc(cap);
    if (!line)
    {
        return NULL;
    }
    int c;
    while ((c = fgetc(stdin)) != EOF)
    {
        if (c == '\n')
        {
            break;
        }
        if (len + 1 >= cap)
        {
            cap *= 2;
            char *n = z_realloc(line, cap);
            if (!n)
            {
                z_free(line);
                return NULL;
            }
            line = n;
        }
        line[len++] = c;
    }
    if (len == 0 && c == EOF)
    {
        z_free(line);
        return NULL;
    }
    line[len] = 0;
    return line;
}
int _z_scan_helper(const char *fmt, ...)
{
    char *l = _z_readln_raw();
    if (!l)
    {
        return 0;
    }
    va_list ap;
    va_start(ap, fmt);
    int r = vsscanf(l, fmt, ap);
    va_end(ap);
    z_free(l);
    return r;
}
int _z_orig_stdout = -1;
void _z_suppress_stdout()
{
    fflush(stdout);
    if (_z_orig_stdout == -1)
    {
        _z_orig_stdout = dup(STDOUT_FILENO);
    }
    int nullfd = open("/dev/null", O_WRONLY);
    dup2(nullfd, STDOUT_FILENO);
    close(nullfd);
}
void _z_restore_stdout()
{
    fflush(stdout);
    if (_z_orig_stdout != -1)
    {
        dup2(_z_orig_stdout, STDOUT_FILENO);
        close(_z_orig_stdout);
        _z_orig_stdout = -1;
    }
}
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
typedef char *string;
typedef struct
{
    void **data;
    int len;
    int cap;
} Vec;
#define Vec_new() (Vec){.data = 0, .len = 0, .cap = 0}
void _z_vec_push(Vec *v, void *item)
{
    if (v->len >= v->cap)
    {
        v->cap = v->cap ? v->cap * 2 : 8;
        v->data = z_realloc(v->data, v->cap * sizeof(void *));
    }
    v->data[v->len++] = item;
}
static inline Vec _z_make_vec(int count, ...)
{
    Vec v = {0};
    v.cap = count > 8 ? count : 8;
    v.data = z_malloc(v.cap * sizeof(void *));
    v.len = 0;
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++)
    {
        v.data[v.len++] = va_arg(args, void *);
    }
    va_end(args);
    return v;
}
#define Vec_push(v, i) _z_vec_push(&(v), (void *)(uintptr_t)(i))
static inline long _z_check_bounds(long index, long limit)
{
    if (index < 0 || index >= limit)
    {
        fprintf(stderr, "Index out of bounds: %ld (limit %ld)\n", index, limit);
        exit(1);
    }
    return index;
}

typedef struct Result_bool Result_bool;
typedef struct VecIterResult_Header VecIterResult_Header;
typedef struct VecIterRef_Header VecIterRef_Header;
typedef struct VecIter_Header VecIter_Header;
typedef struct Vec_Header Vec_Header;
typedef struct Result_size_t Result_size_t;
typedef struct VecIterResult_String VecIterResult_String;
typedef struct VecIterRef_String VecIterRef_String;
typedef struct VecIter_String VecIter_String;
typedef struct Vec_String Vec_String;
typedef struct VecIterResult_int32_t VecIterResult_int32_t;
typedef struct VecIterRef_int32_t VecIterRef_int32_t;
typedef struct VecIter_int32_t VecIter_int32_t;
typedef struct Vec_int32_t Vec_int32_t;
typedef struct VecIterResult_size_t VecIterResult_size_t;
typedef struct VecIterRef_size_t VecIterRef_size_t;
typedef struct VecIter_size_t VecIter_size_t;
typedef struct Vec_size_t Vec_size_t;
typedef struct Option_size_t Option_size_t;
typedef struct Option_int32_t Option_int32_t;
typedef struct VecIterResult_char VecIterResult_char;
typedef struct VecIterRef_char VecIterRef_char;
typedef struct Option_char Option_char;
typedef struct VecIter_char VecIter_char;
typedef struct Vec_char Vec_char;
typedef struct Mutex Mutex;
typedef struct Thread Thread;
typedef struct Dns Dns;
typedef struct Server Server;
typedef struct TcpListener TcpListener;
typedef struct TcpStream TcpStream;
typedef struct StringCharsIter StringCharsIter;
typedef struct String String;
typedef struct Sort Sort;
typedef struct Result_Thread Result_Thread;
typedef struct Result_String Result_String;
typedef struct Result_TcpListener Result_TcpListener;
typedef struct Result_TcpStream Result_TcpStream;
typedef struct Option_String Option_String;
typedef struct Url Url;
typedef struct Response Response;
typedef struct Request Request;
typedef struct Header Header;
typedef struct Result_Url Result_Url;
typedef struct Option_Header Option_Header;
typedef struct Clone_VTable
{
    void *(*clone)(void *self);
} Clone_VTable;
typedef struct Clone
{
    void *self;
    Clone_VTable *vtable;
} Clone;
Clone Clone__clone(Clone *self)
{
    void *ret = self->vtable->clone(self->self);
    return (Clone){.self = ret, .vtable = self->vtable};
}

typedef struct Copy_VTable
{
} Copy_VTable;
typedef struct Copy
{
    void *self;
    Copy_VTable *vtable;
} Copy;

typedef struct Drop_VTable
{
    void (*drop)(void *self);
} Drop_VTable;
typedef struct Drop
{
    void *self;
    Drop_VTable *vtable;
} Drop;
void Drop__drop(Drop *self)
{
    return self->vtable->drop(self->self);
}

#define panic(msg) _zen_panic(__FILE__, __LINE__, __func__, msg)

#define ZC_IMPL_SORT(T)                                                                            \
    static int _z_partition_##T(T *arr, int low, int high)                                         \
    {                                                                                              \
        T pivot = arr[high];                                                                       \
        int i = low - 1;                                                                           \
        for (int j = low; j < high; j++)                                                           \
        {                                                                                          \
            if (arr[j] < pivot)                                                                    \
            {                                                                                      \
                i++;                                                                               \
                T temp = arr[i];                                                                   \
                arr[i] = arr[j];                                                                   \
                arr[j] = temp;                                                                     \
            }                                                                                      \
        }                                                                                          \
        T temp2 = arr[i + 1];                                                                      \
        arr[i + 1] = arr[high];                                                                    \
        arr[high] = temp2;                                                                         \
        return i + 1;                                                                              \
    }                                                                                              \
    static void _z_quick_sort_##T(T *arr, int low, int high)                                       \
    {                                                                                              \
        if (low < high)                                                                            \
        {                                                                                          \
            int pivot_idx = _z_partition_##T(arr, low, high);                                      \
            _z_quick_sort_##T(arr, low, pivot_idx - 1);                                            \
            _z_quick_sort_##T(arr, pivot_idx + 1, high);                                           \
        }                                                                                          \
    }                                                                                              \
    void sort_##T(T *arr, size_t len)                                                              \
    {                                                                                              \
        if (len > 1)                                                                               \
        {                                                                                          \
            _z_quick_sort_##T(arr, 0, (int)len - 1);                                               \
        }                                                                                          \
    }

// Pre-declare standard library types
ZC_IMPL_SORT(int)
ZC_IMPL_SORT(long)
ZC_IMPL_SORT(float)
ZC_IMPL_SORT(double)

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#include <stdint.h>
typedef intptr_t ssize_t;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#endif

#ifdef _WIN32
int _z_net_initialized = 0;
void _z_net_ensure_init(void)
{
    if (!_z_net_initialized)
    {
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        _z_net_initialized = 1;
    }
}
#else
void _z_net_ensure_init(void)
{
}
#endif

static ssize_t _z_socket(int domain, int type, int proto)
{
#ifdef _WIN32
    _z_net_ensure_init();
    return (ssize_t)socket(domain, type, proto);
#else
    return socket(domain, type, proto);
#endif
}

static int _z_close(ssize_t fd)
{
#ifdef _WIN32
    return closesocket((SOCKET)fd);
#else
    return close((int)fd);
#endif
}

static ssize_t _z_read(ssize_t fd, void *buf, size_t count)
{
#ifdef _WIN32
    return recv((SOCKET)fd, (char *)buf, (int)count, 0);
#else
    return read((int)fd, buf, count);
#endif
}

static int _z_net_bind(ssize_t fd, const char *host, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &addr.sin_addr) <= 0)
    {
        return -1;
    }

    int opt = 1;
#ifdef _WIN32
    setsockopt((SOCKET)fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
    if (bind((SOCKET)fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        return -2;
    }
    if (listen((SOCKET)fd, 10) < 0)
    {
        return -3;
    }
#else
    setsockopt((int)fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind((int)fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        return -2;
    }
    if (listen((int)fd, 10) < 0)
    {
        return -3;
    }
#endif
    return 0;
}

static int _z_net_bind_udp(ssize_t fd, const char *host, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &addr.sin_addr) <= 0)
    {
        return -1;
    }

    int opt = 1;
#ifdef _WIN32
    setsockopt((SOCKET)fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
    if (bind((SOCKET)fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        return -2;
    }
#else
    setsockopt((int)fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind((int)fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        return -2;
    }
#endif
    return 0;
}

static int _z_net_connect(ssize_t fd, const char *host, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &addr.sin_addr) <= 0)
    {
        return -1;
    }

#ifdef _WIN32
    if (connect((SOCKET)fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        return -2;
    }
#else
    if (connect((int)fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        return -2;
    }
#endif
    return 0;
}

static ssize_t _z_net_accept(ssize_t fd)
{
#ifdef _WIN32
    return (ssize_t)accept((SOCKET)fd, NULL, NULL);
#else
    return accept((int)fd, NULL, NULL);
#endif
}

static ssize_t _z_net_write(ssize_t fd, const char *buf, size_t n)
{
#ifdef _WIN32
    return send((SOCKET)fd, buf, (int)n, 0);
#else
    return write((int)fd, (const void *)buf, n);
#endif
}

static ssize_t _z_net_recvfrom(ssize_t fd, char *buf, size_t len, char *host_out, int *port_out)
{
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
#ifdef _WIN32
    ssize_t n = recvfrom((SOCKET)fd, buf, (int)len, 0, (struct sockaddr *)&addr, &addr_len);
#else
    ssize_t n = recvfrom((int)fd, buf, len, 0, (struct sockaddr *)&addr, &addr_len);
#endif
    if (n >= 0 && host_out != NULL && port_out != NULL)
    {
        inet_ntop(AF_INET, &addr.sin_addr, host_out, INET_ADDRSTRLEN);
        *port_out = ntohs(addr.sin_port);
    }
    return n;
}

static ssize_t _z_net_sendto(ssize_t fd, const char *buf, size_t len, const char *host, int port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, host, &addr.sin_addr) <= 0)
    {
        return -1;
    }

#ifdef _WIN32
    return sendto((SOCKET)fd, buf, (int)len, 0, (struct sockaddr *)&addr, sizeof(addr));
#else
    return sendto((int)fd, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr));
#endif
}

static int _z_dns_resolve(const char *host, char *out_buf, size_t out_len)
{
    _z_net_ensure_init();
    struct addrinfo hints;
    struct addrinfo *result, *rp;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; // Allow IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0; /* Any protocol */

    int s = getaddrinfo(host, NULL, &hints, &result);
    if (s != 0)
    {
        return s;
    }

    // Just pick the first one for now
    int found = 0;
    for (rp = result; rp != NULL; rp = rp->ai_next)
    {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)rp->ai_addr;
        void *addr = &(ipv4->sin_addr);

        if (inet_ntop(rp->ai_family, addr, out_buf, out_len) != NULL)
        {
            found = 1;
            break;
        }
    }

    freeaddrinfo(result);
    return found ? 0 : -1;
}

struct Result_bool
{
    bool is_ok;
    bool val;
    char *err;
};

struct VecIterResult_Header
{
    Header *ptr;
};

struct VecIterRef_Header
{
    Header *data;
    size_t count;
    size_t idx;
};

struct VecIter_Header
{
    Header *data;
    size_t count;
    size_t idx;
};

struct Vec_Header
{
    Header *data;
    size_t len;
    size_t cap;
};

struct Result_size_t
{
    bool is_ok;
    size_t val;
    char *err;
};

struct VecIterResult_String
{
    String *ptr;
};

struct VecIterRef_String
{
    String *data;
    size_t count;
    size_t idx;
};

struct VecIter_String
{
    String *data;
    size_t count;
    size_t idx;
};

struct Vec_String
{
    String *data;
    size_t len;
    size_t cap;
};

struct VecIterResult_int32_t
{
    int32_t *ptr;
};

struct VecIterRef_int32_t
{
    int32_t *data;
    size_t count;
    size_t idx;
};

struct VecIter_int32_t
{
    int32_t *data;
    size_t count;
    size_t idx;
};

struct Vec_int32_t
{
    int32_t *data;
    size_t len;
    size_t cap;
};

struct VecIterResult_size_t
{
    size_t *ptr;
};

struct VecIterRef_size_t
{
    size_t *data;
    size_t count;
    size_t idx;
};

struct VecIter_size_t
{
    size_t *data;
    size_t count;
    size_t idx;
};

struct Vec_size_t
{
    size_t *data;
    size_t len;
    size_t cap;
};

struct Option_size_t
{
    bool is_some;
    size_t val;
};

struct Option_int32_t
{
    bool is_some;
    int32_t val;
};

struct VecIterResult_char
{
    char *ptr;
};

struct VecIterRef_char
{
    char *data;
    size_t count;
    size_t idx;
};

struct Option_char
{
    bool is_some;
    char val;
};

struct VecIter_char
{
    char *data;
    size_t count;
    size_t idx;
};

struct Vec_char
{
    char *data;
    size_t len;
    size_t cap;
};

struct Mutex
{
    void *handle;
};

struct Thread
{
    void *handle;
};

struct Dns
{
    char _placeholder;
};

struct Server
{
    int32_t port;
    void (*handler)(Request *, Response *);
};

struct TcpListener
{
    ptrdiff_t handle;
};

struct TcpStream
{
    ptrdiff_t handle;
};

struct StringCharsIter
{
    char *data;
    size_t len;
    size_t pos;
};

struct String
{
    Vec_char vec;
};

struct Sort
{
    char _placeholder;
};

struct Result_Thread
{
    bool is_ok;
    Thread val;
    char *err;
};

struct Result_String
{
    bool is_ok;
    String val;
    char *err;
};

struct Result_TcpListener
{
    bool is_ok;
    TcpListener val;
    char *err;
};

struct Result_TcpStream
{
    bool is_ok;
    TcpStream val;
    char *err;
};

struct Option_String
{
    bool is_some;
    String val;
};

struct Url
{
    String scheme;
    String host;
    int32_t port;
    String path;
    String query;
};

struct Response
{
    int32_t status;
    Vec_Header headers;
    String body;
};

struct Request
{
    String method;
    String path;
    Vec_Header headers;
    String body;
};

struct Header
{
    String key;
    String value;
};

struct Result_Url
{
    bool is_ok;
    Url val;
    char *err;
};

struct Option_Header
{
    bool is_some;
    Header val;
};

typedef void (*ZenThreadFunc)(void *);

struct ZenThreadCtx
{
    void *func_ptr;
    void *ctx;
};

static void *_z_thread_trampoline(void *arg)
{
    z_closure_T *closure = (z_closure_T *)arg;
    void (*f)(void *) = (void (*)(void *))closure->func;
    f(closure->ctx);
    if (closure->drop)
    {
        closure->drop(closure->ctx);
    }
    free(closure);
    return NULL;
}

static int _z_thread_equal(void *handle1, void *handle2)
{
    return pthread_equal((pthread_t)handle1, (pthread_t)handle2);
}

static int _z_thread_spawn(void *ctx_copy, size_t *out_handle)
{
    pthread_t pt;
    int ret = pthread_create(&pt, NULL, _z_thread_trampoline, ctx_copy);
    if (ret == 0)
    {
        *out_handle = (size_t)pt;
    }
    return (int)ret;
}

static int _z_thread_join(void *handle)
{
    return (int)pthread_join((pthread_t)handle, NULL);
}

static int _z_thread_detach(void *handle)
{
    return pthread_detach((pthread_t)handle);
}

static int _z_thread_cancel(void *handle)
{
    return pthread_cancel((pthread_t)handle);
}

static void _z_mutex_init(void *ptr)
{
    pthread_mutex_init((pthread_mutex_t *)ptr, NULL);
}

static void _z_mutex_lock(void *ptr)
{
    pthread_mutex_lock((pthread_mutex_t *)ptr);
}

static void _z_mutex_unlock(void *ptr)
{
    pthread_mutex_unlock((pthread_mutex_t *)ptr);
}

static void _z_mutex_destroy(void *ptr)
{
    pthread_mutex_destroy((pthread_mutex_t *)ptr);
}

static void _z_usleep(int micros)
{
    usleep(micros);
}

const int Z_AF_INET = 2;
const int Z_SOCK_STREAM = 1;
const int Z_SOCK_DGRAM = 2;
size_t __zen_hash_seed = 14695981039346656037ULL;
const size_t _HASH_MAGIC = 1099511628211;
Result_bool Result_bool__Ok(bool v);
Result_bool Result_bool__Err(char *e);
bool Result_bool__is_ok(Result_bool *self);
bool Result_bool__is_err(Result_bool *self);
void Result_bool__forget(Result_bool *self);
bool Result_bool__unwrap(Result_bool *self);
bool *Result_bool__unwrap_ref(Result_bool *self);
bool Result_bool__expect(Result_bool *self, char *msg);
Result_Thread Result_Thread__Ok(Thread v);
Result_Thread Result_Thread__Err(char *e);
bool Result_Thread__is_ok(Result_Thread *self);
bool Result_Thread__is_err(Result_Thread *self);
void Result_Thread__forget(Result_Thread *self);
Thread Result_Thread__unwrap(Result_Thread *self);
Thread *Result_Thread__unwrap_ref(Result_Thread *self);
Thread Result_Thread__expect(Result_Thread *self, char *msg);
Result_String Result_String__Ok(String v);
Result_String Result_String__Err(char *e);
bool Result_String__is_ok(Result_String *self);
bool Result_String__is_err(Result_String *self);
void Result_String__forget(Result_String *self);
String Result_String__unwrap(Result_String *self);
String *Result_String__unwrap_ref(Result_String *self);
String Result_String__expect(Result_String *self, char *msg);
Result_Url Result_Url__Ok(Url v);
Result_Url Result_Url__Err(char *e);
bool Result_Url__is_ok(Result_Url *self);
bool Result_Url__is_err(Result_Url *self);
void Result_Url__forget(Result_Url *self);
Url Result_Url__unwrap(Result_Url *self);
Url *Result_Url__unwrap_ref(Result_Url *self);
Url Result_Url__expect(Result_Url *self, char *msg);
Vec_Header Vec_Header__new(void);
Vec_Header Vec_Header__with_capacity(size_t cap);
void Vec_Header__grow(Vec_Header *self);
void Vec_Header__grow_to_fit(Vec_Header *self, size_t new_len);
VecIter_Header Vec_Header__iterator(Vec_Header *self);
VecIterRef_Header Vec_Header__iter_ref(Vec_Header *self);
void Vec_Header__push(Vec_Header *self, Header item);
void Vec_Header__insert(Vec_Header *self, size_t idx, Header item);
Header Vec_Header__pop(Vec_Header *self);
Option_Header Vec_Header__pop_opt(Vec_Header *self);
Header Vec_Header__remove(Vec_Header *self, size_t idx);
void Vec_Header__append(Vec_Header *self, Vec_Header other);
Header Vec_Header__get(Vec_Header *self, size_t idx);
Header Vec_Header__index(Vec_Header *self, size_t idx);
Header *Vec_Header__get_ref(Vec_Header *self, size_t idx);
Header Vec_Header__last(Vec_Header *self);
size_t Vec_Header__length(Vec_Header *self);
bool Vec_Header__contains(Vec_Header *self, Header item);
bool Vec_Header__is_empty(Vec_Header *self);
void Vec_Header__clear(Vec_Header *self);
void Vec_Header__free(Vec_Header *self);
Header Vec_Header__first(Vec_Header *self);
void Vec_Header__set(Vec_Header *self, size_t idx, Header item);
void Vec_Header__reverse(Vec_Header *self);
bool Vec_Header__eq(Vec_Header *self, Vec_Header *other);
void Vec_Header__forget(Vec_Header *self);
Vec_Header Vec_Header__add(Vec_Header *self, Vec_Header *other);
void Vec_Header__add_assign(Vec_Header *self, Vec_Header *other);
bool Vec_Header__neq(Vec_Header *self, Vec_Header *other);
void Vec_Header__shl(Vec_Header *self, Header item);
void Vec_Header__shr(Vec_Header *self, Header *out_item);
Vec_Header Vec_Header__mul(Vec_Header *self, size_t count);
void Vec_Header__mul_assign(Vec_Header *self, size_t count);
Vec_Header Vec_Header__clone(Vec_Header *self);
VecIterResult_Header VecIterRef_Header__next(VecIterRef_Header *self);
VecIterRef_Header VecIterRef_Header__iterator(VecIterRef_Header *self);
bool VecIterResult_Header__is_none(VecIterResult_Header *self);
Header *VecIterResult_Header__unwrap(VecIterResult_Header *self);
Option_Header VecIter_Header__next(VecIter_Header *self);
VecIter_Header VecIter_Header__iterator(VecIter_Header *self);
Option_Header Option_Header__Some(Header v);
Option_Header Option_Header__None(void);
bool Option_Header__is_some(Option_Header *self);
bool Option_Header__is_none(Option_Header *self);
void Option_Header__forget(Option_Header *self);
Header Option_Header__unwrap(Option_Header *self);
Header *Option_Header__unwrap_ref(Option_Header *self);
Header Option_Header__unwrap_or(Option_Header *self, Header def_val);
Header Option_Header__expect(Option_Header *self, char *msg);
Option_Header Option_Header__or_else(Option_Header *self, Option_Header other);
void Vec_Header__Drop_drop(Vec_Header *self);
Result_TcpListener Result_TcpListener__Ok(TcpListener v);
Result_TcpListener Result_TcpListener__Err(char *e);
bool Result_TcpListener__is_ok(Result_TcpListener *self);
bool Result_TcpListener__is_err(Result_TcpListener *self);
void Result_TcpListener__forget(Result_TcpListener *self);
TcpListener Result_TcpListener__unwrap(Result_TcpListener *self);
TcpListener *Result_TcpListener__unwrap_ref(Result_TcpListener *self);
TcpListener Result_TcpListener__expect(Result_TcpListener *self, char *msg);
Result_TcpStream Result_TcpStream__Ok(TcpStream v);
Result_TcpStream Result_TcpStream__Err(char *e);
bool Result_TcpStream__is_ok(Result_TcpStream *self);
bool Result_TcpStream__is_err(Result_TcpStream *self);
void Result_TcpStream__forget(Result_TcpStream *self);
TcpStream Result_TcpStream__unwrap(Result_TcpStream *self);
TcpStream *Result_TcpStream__unwrap_ref(Result_TcpStream *self);
TcpStream Result_TcpStream__expect(Result_TcpStream *self, char *msg);
Result_size_t Result_size_t__Ok(size_t v);
Result_size_t Result_size_t__Err(char *e);
bool Result_size_t__is_ok(Result_size_t *self);
bool Result_size_t__is_err(Result_size_t *self);
void Result_size_t__forget(Result_size_t *self);
size_t Result_size_t__unwrap(Result_size_t *self);
size_t *Result_size_t__unwrap_ref(Result_size_t *self);
size_t Result_size_t__expect(Result_size_t *self, char *msg);
Vec_String Vec_String__new(void);
Vec_String Vec_String__with_capacity(size_t cap);
void Vec_String__grow(Vec_String *self);
void Vec_String__grow_to_fit(Vec_String *self, size_t new_len);
VecIter_String Vec_String__iterator(Vec_String *self);
VecIterRef_String Vec_String__iter_ref(Vec_String *self);
void Vec_String__push(Vec_String *self, String item);
void Vec_String__insert(Vec_String *self, size_t idx, String item);
String Vec_String__pop(Vec_String *self);
Option_String Vec_String__pop_opt(Vec_String *self);
String Vec_String__remove(Vec_String *self, size_t idx);
void Vec_String__append(Vec_String *self, Vec_String other);
String Vec_String__get(Vec_String *self, size_t idx);
String Vec_String__index(Vec_String *self, size_t idx);
String *Vec_String__get_ref(Vec_String *self, size_t idx);
String Vec_String__last(Vec_String *self);
size_t Vec_String__length(Vec_String *self);
bool Vec_String__contains(Vec_String *self, String item);
bool Vec_String__is_empty(Vec_String *self);
void Vec_String__clear(Vec_String *self);
void Vec_String__free(Vec_String *self);
String Vec_String__first(Vec_String *self);
void Vec_String__set(Vec_String *self, size_t idx, String item);
void Vec_String__reverse(Vec_String *self);
bool Vec_String__eq(Vec_String *self, Vec_String *other);
void Vec_String__forget(Vec_String *self);
Vec_String Vec_String__add(Vec_String *self, Vec_String *other);
void Vec_String__add_assign(Vec_String *self, Vec_String *other);
bool Vec_String__neq(Vec_String *self, Vec_String *other);
void Vec_String__shl(Vec_String *self, String item);
void Vec_String__shr(Vec_String *self, String *out_item);
Vec_String Vec_String__mul(Vec_String *self, size_t count);
void Vec_String__mul_assign(Vec_String *self, size_t count);
Vec_String Vec_String__clone(Vec_String *self);
VecIterResult_String VecIterRef_String__next(VecIterRef_String *self);
VecIterRef_String VecIterRef_String__iterator(VecIterRef_String *self);
bool VecIterResult_String__is_none(VecIterResult_String *self);
String *VecIterResult_String__unwrap(VecIterResult_String *self);
Option_String VecIter_String__next(VecIter_String *self);
VecIter_String VecIter_String__iterator(VecIter_String *self);
Option_String Option_String__Some(String v);
Option_String Option_String__None(void);
bool Option_String__is_some(Option_String *self);
bool Option_String__is_none(Option_String *self);
void Option_String__forget(Option_String *self);
String Option_String__unwrap(Option_String *self);
String *Option_String__unwrap_ref(Option_String *self);
String Option_String__unwrap_or(Option_String *self, String def_val);
String Option_String__expect(Option_String *self, char *msg);
Option_String Option_String__or_else(Option_String *self, Option_String other);
void Vec_String__Drop_drop(Vec_String *self);
Vec_int32_t Vec_int32_t__new(void);
Vec_int32_t Vec_int32_t__with_capacity(size_t cap);
void Vec_int32_t__grow(Vec_int32_t *self);
void Vec_int32_t__grow_to_fit(Vec_int32_t *self, size_t new_len);
VecIter_int32_t Vec_int32_t__iterator(Vec_int32_t *self);
VecIterRef_int32_t Vec_int32_t__iter_ref(Vec_int32_t *self);
void Vec_int32_t__push(Vec_int32_t *self, int32_t item);
void Vec_int32_t__insert(Vec_int32_t *self, size_t idx, int32_t item);
int32_t Vec_int32_t__pop(Vec_int32_t *self);
Option_int32_t Vec_int32_t__pop_opt(Vec_int32_t *self);
int32_t Vec_int32_t__remove(Vec_int32_t *self, size_t idx);
void Vec_int32_t__append(Vec_int32_t *self, Vec_int32_t other);
int32_t Vec_int32_t__get(Vec_int32_t *self, size_t idx);
int32_t Vec_int32_t__index(Vec_int32_t *self, size_t idx);
int32_t *Vec_int32_t__get_ref(Vec_int32_t *self, size_t idx);
int32_t Vec_int32_t__last(Vec_int32_t *self);
size_t Vec_int32_t__length(Vec_int32_t *self);
bool Vec_int32_t__contains(Vec_int32_t *self, int32_t item);
bool Vec_int32_t__is_empty(Vec_int32_t *self);
void Vec_int32_t__clear(Vec_int32_t *self);
void Vec_int32_t__free(Vec_int32_t *self);
int32_t Vec_int32_t__first(Vec_int32_t *self);
void Vec_int32_t__set(Vec_int32_t *self, size_t idx, int32_t item);
void Vec_int32_t__reverse(Vec_int32_t *self);
bool Vec_int32_t__eq(Vec_int32_t *self, Vec_int32_t *other);
void Vec_int32_t__forget(Vec_int32_t *self);
Vec_int32_t Vec_int32_t__add(Vec_int32_t *self, Vec_int32_t *other);
void Vec_int32_t__add_assign(Vec_int32_t *self, Vec_int32_t *other);
bool Vec_int32_t__neq(Vec_int32_t *self, Vec_int32_t *other);
void Vec_int32_t__shl(Vec_int32_t *self, int32_t item);
void Vec_int32_t__shr(Vec_int32_t *self, int32_t *out_item);
Vec_int32_t Vec_int32_t__mul(Vec_int32_t *self, size_t count);
void Vec_int32_t__mul_assign(Vec_int32_t *self, size_t count);
Vec_int32_t Vec_int32_t__clone(Vec_int32_t *self);
VecIterResult_int32_t VecIterRef_int32_t__next(VecIterRef_int32_t *self);
VecIterRef_int32_t VecIterRef_int32_t__iterator(VecIterRef_int32_t *self);
bool VecIterResult_int32_t__is_none(VecIterResult_int32_t *self);
int32_t *VecIterResult_int32_t__unwrap(VecIterResult_int32_t *self);
Option_int32_t VecIter_int32_t__next(VecIter_int32_t *self);
VecIter_int32_t VecIter_int32_t__iterator(VecIter_int32_t *self);
void Vec_int32_t__Drop_drop(Vec_int32_t *self);
Vec_size_t Vec_size_t__new(void);
Vec_size_t Vec_size_t__with_capacity(size_t cap);
void Vec_size_t__grow(Vec_size_t *self);
void Vec_size_t__grow_to_fit(Vec_size_t *self, size_t new_len);
VecIter_size_t Vec_size_t__iterator(Vec_size_t *self);
VecIterRef_size_t Vec_size_t__iter_ref(Vec_size_t *self);
void Vec_size_t__push(Vec_size_t *self, size_t item);
void Vec_size_t__insert(Vec_size_t *self, size_t idx, size_t item);
size_t Vec_size_t__pop(Vec_size_t *self);
Option_size_t Vec_size_t__pop_opt(Vec_size_t *self);
size_t Vec_size_t__remove(Vec_size_t *self, size_t idx);
void Vec_size_t__append(Vec_size_t *self, Vec_size_t other);
size_t Vec_size_t__get(Vec_size_t *self, size_t idx);
size_t Vec_size_t__index(Vec_size_t *self, size_t idx);
size_t *Vec_size_t__get_ref(Vec_size_t *self, size_t idx);
size_t Vec_size_t__last(Vec_size_t *self);
size_t Vec_size_t__length(Vec_size_t *self);
bool Vec_size_t__contains(Vec_size_t *self, size_t item);
bool Vec_size_t__is_empty(Vec_size_t *self);
void Vec_size_t__clear(Vec_size_t *self);
void Vec_size_t__free(Vec_size_t *self);
size_t Vec_size_t__first(Vec_size_t *self);
void Vec_size_t__set(Vec_size_t *self, size_t idx, size_t item);
void Vec_size_t__reverse(Vec_size_t *self);
bool Vec_size_t__eq(Vec_size_t *self, Vec_size_t *other);
void Vec_size_t__forget(Vec_size_t *self);
Vec_size_t Vec_size_t__add(Vec_size_t *self, Vec_size_t *other);
void Vec_size_t__add_assign(Vec_size_t *self, Vec_size_t *other);
bool Vec_size_t__neq(Vec_size_t *self, Vec_size_t *other);
void Vec_size_t__shl(Vec_size_t *self, size_t item);
void Vec_size_t__shr(Vec_size_t *self, size_t *out_item);
Vec_size_t Vec_size_t__mul(Vec_size_t *self, size_t count);
void Vec_size_t__mul_assign(Vec_size_t *self, size_t count);
Vec_size_t Vec_size_t__clone(Vec_size_t *self);
VecIterResult_size_t VecIterRef_size_t__next(VecIterRef_size_t *self);
VecIterRef_size_t VecIterRef_size_t__iterator(VecIterRef_size_t *self);
bool VecIterResult_size_t__is_none(VecIterResult_size_t *self);
size_t *VecIterResult_size_t__unwrap(VecIterResult_size_t *self);
Option_size_t VecIter_size_t__next(VecIter_size_t *self);
VecIter_size_t VecIter_size_t__iterator(VecIter_size_t *self);
void Vec_size_t__Drop_drop(Vec_size_t *self);
Option_size_t Option_size_t__Some(size_t v);
Option_size_t Option_size_t__None(void);
bool Option_size_t__is_some(Option_size_t *self);
bool Option_size_t__is_none(Option_size_t *self);
void Option_size_t__forget(Option_size_t *self);
size_t Option_size_t__unwrap(Option_size_t *self);
size_t *Option_size_t__unwrap_ref(Option_size_t *self);
size_t Option_size_t__unwrap_or(Option_size_t *self, size_t def_val);
size_t Option_size_t__expect(Option_size_t *self, char *msg);
Option_size_t Option_size_t__or_else(Option_size_t *self, Option_size_t other);
Option_int32_t Option_int32_t__Some(int32_t v);
Option_int32_t Option_int32_t__None(void);
bool Option_int32_t__is_some(Option_int32_t *self);
bool Option_int32_t__is_none(Option_int32_t *self);
void Option_int32_t__forget(Option_int32_t *self);
int32_t Option_int32_t__unwrap(Option_int32_t *self);
int32_t *Option_int32_t__unwrap_ref(Option_int32_t *self);
int32_t Option_int32_t__unwrap_or(Option_int32_t *self, int32_t def_val);
int32_t Option_int32_t__expect(Option_int32_t *self, char *msg);
Option_int32_t Option_int32_t__or_else(Option_int32_t *self, Option_int32_t other);
Vec_char Vec_char__new(void);
Vec_char Vec_char__with_capacity(size_t cap);
void Vec_char__grow(Vec_char *self);
void Vec_char__grow_to_fit(Vec_char *self, size_t new_len);
VecIter_char Vec_char__iterator(Vec_char *self);
VecIterRef_char Vec_char__iter_ref(Vec_char *self);
void Vec_char__push(Vec_char *self, char item);
void Vec_char__insert(Vec_char *self, size_t idx, char item);
char Vec_char__pop(Vec_char *self);
Option_char Vec_char__pop_opt(Vec_char *self);
char Vec_char__remove(Vec_char *self, size_t idx);
void Vec_char__append(Vec_char *self, Vec_char other);
char Vec_char__get(Vec_char *self, size_t idx);
char Vec_char__index(Vec_char *self, size_t idx);
char *Vec_char__get_ref(Vec_char *self, size_t idx);
char Vec_char__last(Vec_char *self);
size_t Vec_char__length(Vec_char *self);
bool Vec_char__contains(Vec_char *self, char item);
bool Vec_char__is_empty(Vec_char *self);
void Vec_char__clear(Vec_char *self);
void Vec_char__free(Vec_char *self);
char Vec_char__first(Vec_char *self);
void Vec_char__set(Vec_char *self, size_t idx, char item);
void Vec_char__reverse(Vec_char *self);
bool Vec_char__eq(Vec_char *self, Vec_char *other);
void Vec_char__forget(Vec_char *self);
Vec_char Vec_char__add(Vec_char *self, Vec_char *other);
void Vec_char__add_assign(Vec_char *self, Vec_char *other);
bool Vec_char__neq(Vec_char *self, Vec_char *other);
void Vec_char__shl(Vec_char *self, char item);
void Vec_char__shr(Vec_char *self, char *out_item);
Vec_char Vec_char__mul(Vec_char *self, size_t count);
void Vec_char__mul_assign(Vec_char *self, size_t count);
Vec_char Vec_char__clone(Vec_char *self);
VecIterResult_char VecIterRef_char__next(VecIterRef_char *self);
VecIterRef_char VecIterRef_char__iterator(VecIterRef_char *self);
bool VecIterResult_char__is_none(VecIterResult_char *self);
char *VecIterResult_char__unwrap(VecIterResult_char *self);
Option_char VecIter_char__next(VecIter_char *self);
VecIter_char VecIter_char__iterator(VecIter_char *self);
Option_char Option_char__Some(char v);
Option_char Option_char__None(void);
bool Option_char__is_some(Option_char *self);
bool Option_char__is_none(Option_char *self);
void Option_char__forget(Option_char *self);
char Option_char__unwrap(Option_char *self);
char *Option_char__unwrap_ref(Option_char *self);
char Option_char__unwrap_or(Option_char *self, char def_val);
char Option_char__expect(Option_char *self, char *msg);
Option_char Option_char__or_else(Option_char *self, Option_char other);
void Vec_char__Drop_drop(Vec_char *self);
void handler(Request *_req, Response *res);
void assert_true(bool cond, char *msg);
void sleep_ms(int32_t ms);
void _z_usleep(int micros);
void _z_mutex_destroy(void *ptr);
void _z_mutex_unlock(void *ptr);
void _z_mutex_lock(void *ptr);
void _z_mutex_init(void *ptr);
int _z_thread_cancel(void *handle);
int _z_thread_detach(void *handle);
int _z_thread_join(void *handle);
int _z_thread_spawn(void *ctx, size_t *out);
int _z_thread_equal(void *handle1, void *handle2);
Response fetch(String url);
char *strstr(const char *haystack, const char *needle);
int32_t atoi(const char *s);
int32_t _z_dns_resolve(const char *host, char *out_buf, size_t out_len);
void _z_net_ensure_init(void);
int32_t atoi(const char *s);
Vec_Header _parse_headers(Vec_String lines, size_t start_idx);
size_t _map_hash_str(const char *str);
size_t hash_get_seed(void);
void hash_set_seed(size_t seed);
size_t hash_compute(const void *data, size_t len);
size_t hash_combine(size_t a, size_t b);
int _z_net_bind_udp(ptrdiff_t fd, const char *host, int port);
ptrdiff_t _z_net_sendto(ptrdiff_t fd, const char *buf, size_t len, const char *host, int port);
ptrdiff_t _z_net_recvfrom(ptrdiff_t fd, char *buf, size_t len, char *host_out, int *port_out);
ptrdiff_t _z_net_write(ptrdiff_t fd, const char *buf, size_t n);
ptrdiff_t _z_net_accept(ptrdiff_t fd);
int _z_net_connect(ptrdiff_t fd, const char *host, int port);
int _z_net_bind(ptrdiff_t fd, const char *host, int port);
void _z_net_ensure_init(void);
char *strerror(int errnum);
ptrdiff_t _z_read(ptrdiff_t fd, void *buf, size_t count);
int _z_close(ptrdiff_t fd);
ptrdiff_t _z_socket(int domain, int type, int proto);
int32_t strcasecmp(const char *s1, const char *s2);
void sort_double(double *arr, size_t len);
void sort_float(float *arr, size_t len);
void sort_long(long *arr, size_t len);
void sort_int(int32_t *arr, size_t len);
void _zen_panic(const char *file, int32_t line, const char *func, const char *msg);
void exit(int32_t code);
void Mutex__Drop_drop(Mutex *self);
Mutex Mutex__new(void);
void Mutex__lock(Mutex *self);
void Mutex__unlock(Mutex *self);
void Mutex__free(Mutex *self);
bool Thread__eq(Thread *self, const Thread other);
bool Thread__neq(Thread *self, const Thread other);
Result_Thread Thread__spawn(z_closure_T func);
Result_bool Thread__join(Thread *self);
Result_bool Thread__detach(Thread *self);
Result_bool Thread__cancel(Thread *self);
Result_String Dns__resolve(char *host);
Result_Url Url__parse(String raw);
void Url__destroy(Url *self);
Server Server__new(int32_t port, void (*handler)(Request *, Response *));
void Server__start(Server *self);
Response Response__new(int32_t status);
void Response__set_header(Response *self, String key, String value);
void Response__set_header_str(Response *self, char *key, char *value);
void Response__set_body(Response *self, String body);
void Response__set_body_str(Response *self, char *body);
Request Request__new(String method, String path);
void TcpListener__Drop_drop(TcpListener *self);
Result_TcpListener TcpListener__bind(char *host, int port);
Result_TcpStream TcpListener__accept(TcpListener *self);
void TcpListener__close(TcpListener *self);
void TcpStream__Drop_drop(TcpStream *self);
Result_size_t TcpStream__read(TcpStream *self, char *buf, size_t len);
Result_size_t TcpStream__read_exact(TcpStream *self, char *buf, size_t len);
Result_size_t TcpStream__write(TcpStream *self, uint8_t *buf, size_t len);
void TcpStream__close(TcpStream *self);
Result_TcpStream TcpStream__connect(char *host, int port);
String String__new(char *s);
String String__from(char *s);
String String__from_rune(int32_t r);
String String__from_runes(int32_t *runes, size_t count);
char *String__c_str(String *self);
char *String__to_string(String *self);
void String__destroy(String *self);
void String__forget(String *self);
void String__append(String *self, String *other);
void String__append_c(String *self, char *s);
void String__push_rune(String *self, int32_t r);
void String__append_c_ptr(String *ptr, char *s);
String String__add(String *self, String *other);
void String__add_assign(String *self, String *other);
bool String__eq(String *self, String *other);
bool String__neq(String *self, String *other);
int32_t String__compare(String *self, String *other);
bool String__lt(String *self, String *other);
bool String__gt(String *self, String *other);
bool String__le(String *self, String *other);
bool String__ge(String *self, String *other);
int32_t String__compare_ignore_case(String *self, String *other);
bool String__eq_ignore_case(String *self, String *other);
bool String__eq_str(String *self, char *s);
size_t String__length(String *self);
String String__substring(String *self, size_t start, size_t len);
bool String__contains_str(String *self, char *target);
Option_size_t String__find_str(String *self, char *target);
Vec_size_t String__find_all_str(String *self, char *target);
String String__to_lowercase(String *self);
String String__pad_right(String *self, size_t target_len, char pad_char);
String String__pad_left(String *self, size_t target_len, char pad_char);
String String__to_uppercase(String *self);
Option_size_t String__find(String *self, char target);
void String__print(String *self);
void String__println(String *self);
bool String__is_empty(String *self);
bool String__contains(String *self, char target);
bool String__starts_with(String *self, char *prefix);
bool String__ends_with(String *self, char *suffix);
void String__reserve(String *self, size_t cap);
void String__free(String *self);
size_t String___utf8_seq_len(char first_byte);
size_t String__utf8_len(String *self);
String String__utf8_at(String *self, size_t idx);
int32_t String__utf8_get(String *self, size_t idx);
Vec_int32_t String__runes(String *self);
StringCharsIter String__chars(String *self);
String String__from_runes_vec(Vec_int32_t runes);
void String__insert_rune(String *self, size_t idx, int32_t r);
int32_t String__remove_rune_at(String *self, size_t idx);
String String__utf8_substr(String *self, size_t start_idx, size_t num_chars);
Vec_String String__split(String *self, char delim);
String String__trim(String *self);
String String__replace(String *self, char *target, char *replacement);
Option_int32_t StringCharsIter__next(StringCharsIter *self);
Drop_VTable Mutex_Drop_VTable = {.drop = (__typeof__(((Drop_VTable *)0)->drop))Mutex__Drop_drop};
Drop_VTable TcpListener_Drop_VTable = {
    .drop = (__typeof__(((Drop_VTable *)0)->drop))TcpListener__Drop_drop};
Drop_VTable TcpStream_Drop_VTable = {
    .drop = (__typeof__(((Drop_VTable *)0)->drop))TcpStream__Drop_drop};
// Auto-Generated RAII Glue for Vec_Header
void Vec_Header__Drop_glue(Vec_Header *self)
{
    Vec_Header__Drop_drop(self);
}

// Auto-Generated RAII Glue for Vec_String
void Vec_String__Drop_glue(Vec_String *self)
{
    Vec_String__Drop_drop(self);
}

// Auto-Generated RAII Glue for Vec_int32_t
void Vec_int32_t__Drop_glue(Vec_int32_t *self)
{
    Vec_int32_t__Drop_drop(self);
}

// Auto-Generated RAII Glue for Vec_size_t
void Vec_size_t__Drop_glue(Vec_size_t *self)
{
    Vec_size_t__Drop_drop(self);
}

// Auto-Generated RAII Glue for Vec_char
void Vec_char__Drop_glue(Vec_char *self)
{
    Vec_char__Drop_drop(self);
}

// Auto-Generated RAII Glue for Mutex
void Mutex__Drop_glue(Mutex *self)
{
    Mutex__Drop_drop(self);
}

// Auto-Generated RAII Glue for TcpListener
void TcpListener__Drop_glue(TcpListener *self)
{
    TcpListener__Drop_drop(self);
}

// Auto-Generated RAII Glue for TcpStream
void TcpStream__Drop_glue(TcpStream *self)
{
    TcpStream__Drop_drop(self);
}

// Auto-Generated RAII Glue for String
void String__Drop_glue(String *self)
{
    Vec_char__Drop_glue(&self->vec);
}

// Auto-Generated RAII Glue for Url
void Url__Drop_glue(Url *self)
{
    String__Drop_glue(&self->scheme);
    String__Drop_glue(&self->host);
    String__Drop_glue(&self->path);
    String__Drop_glue(&self->query);
}

// Auto-Generated RAII Glue for Response
void Response__Drop_glue(Response *self)
{
    Vec_Header__Drop_glue(&self->headers);
    String__Drop_glue(&self->body);
}

// Auto-Generated RAII Glue for Request
void Request__Drop_glue(Request *self)
{
    String__Drop_glue(&self->method);
    String__Drop_glue(&self->path);
    Vec_Header__Drop_glue(&self->headers);
    String__Drop_glue(&self->body);
}

// Auto-Generated RAII Glue for Header
void Header__Drop_glue(Header *self)
{
    String__Drop_glue(&self->key);
    String__Drop_glue(&self->value);
}

struct Lambda_0_Ctx
{
    Server server;
};

static void _lambda_0_drop(void *_ctx)
{
    struct Lambda_0_Ctx *ctx = (struct Lambda_0_Ctx *)_ctx;
    free(_ctx);
}

void _lambda_0(void *_ctx)
{
    struct Lambda_0_Ctx *ctx = (struct Lambda_0_Ctx *)_ctx;
    Server__start((&ctx->server));
}

static void _z_test_0()
{
    {
        Server server = Server__new(8081, handler);
        Thread__spawn(({
            struct Lambda_0_Ctx *_z_ctx_0 = malloc(sizeof(struct Lambda_0_Ctx));
            _z_ctx_0->server = server;
            (z_closure_T){.func = _lambda_0, .ctx = _z_ctx_0, .drop = _lambda_0_drop};
        }));
        sleep_ms(100);
        int __z_drop_flag_response = 1;
        Response response = fetch(String__new("http://127.0.0.1:8081/hello"));
        assert_true((response.status == 200), "Status 200");
        assert_true((!String__is_empty((&response.body))), "Body not empty");
        assert_true(String__eq_str((&response.body), "Hello World"), "Body content match");
        if (__z_drop_flag_response)
        {
            Response__Drop_glue(&response);
        }
    }
}

void _z_run_tests()
{
    _z_test_0();
}

Result_bool Result_bool__Ok(bool v)
{
    {
        return (Result_bool){.is_ok = true, .val = v};
    }
}

Result_bool Result_bool__Err(char *e)
{
    {
        return (Result_bool){.is_ok = false, .err = e};
    }
}

bool Result_bool__is_ok(Result_bool *self)
{
    {
        return self->is_ok;
    }
}

bool Result_bool__is_err(Result_bool *self)
{
    {
        return (!self->is_ok);
    }
}

void Result_bool__forget(Result_bool *self)
{
    {
        memset((&self->val), 0, sizeof(bool));
    }
}

bool Result_bool__unwrap(Result_bool *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        bool v = self->val;
        memset((&self->val), 0, sizeof(bool));
        return v;
    }
}

bool *Result_bool__unwrap_ref(Result_bool *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

bool Result_bool__expect(Result_bool *self, char *msg)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "%s", ": ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Result_Thread Result_Thread__Ok(Thread v)
{
    {
        return (Result_Thread){.is_ok = true, .val = v};
    }
}

Result_Thread Result_Thread__Err(char *e)
{
    {
        return (Result_Thread){.is_ok = false, .err = e};
    }
}

bool Result_Thread__is_ok(Result_Thread *self)
{
    {
        return self->is_ok;
    }
}

bool Result_Thread__is_err(Result_Thread *self)
{
    {
        return (!self->is_ok);
    }
}

void Result_Thread__forget(Result_Thread *self)
{
    {
        memset((&self->val), 0, sizeof(Thread));
    }
}

Thread Result_Thread__unwrap(Result_Thread *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        Thread v = self->val;
        memset((&self->val), 0, sizeof(Thread));
        return v;
    }
}

Thread *Result_Thread__unwrap_ref(Result_Thread *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

Thread Result_Thread__expect(Result_Thread *self, char *msg)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "%s", ": ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Result_String Result_String__Ok(String v)
{
    int __z_drop_flag_v = 1;
    {
        {
            Result_String _z_ret = (Result_String){.is_ok = true, .val = v};
            if (__z_drop_flag_v)
            {
                String__Drop_glue(&v);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_v)
    {
        String__Drop_glue(&v);
    }
}

Result_String Result_String__Err(char *e)
{
    {
        return (Result_String){.is_ok = false, .err = e};
    }
}

bool Result_String__is_ok(Result_String *self)
{
    {
        return self->is_ok;
    }
}

bool Result_String__is_err(Result_String *self)
{
    {
        return (!self->is_ok);
    }
}

void Result_String__forget(Result_String *self)
{
    {
        memset((&self->val), 0, sizeof(String));
    }
}

String Result_String__unwrap(Result_String *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int __z_drop_flag_v = 1;
        String v = self->val;
        memset((&self->val), 0, sizeof(String));
        return ({
            ZC_AUTO _z_ret_mv = v;
            memset(&v, 0, sizeof(_z_ret_mv));
            __z_drop_flag_v = 0;
            if (__z_drop_flag_v)
            {
                String__Drop_glue(&v);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_v)
        {
            String__Drop_glue(&v);
        }
    }
}

String *Result_String__unwrap_ref(Result_String *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

String Result_String__expect(Result_String *self, char *msg)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "%s", ": ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Result_Url Result_Url__Ok(Url v)
{
    int __z_drop_flag_v = 1;
    {
        {
            Result_Url _z_ret = (Result_Url){.is_ok = true, .val = v};
            if (__z_drop_flag_v)
            {
                Url__Drop_glue(&v);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_v)
    {
        Url__Drop_glue(&v);
    }
}

Result_Url Result_Url__Err(char *e)
{
    {
        return (Result_Url){.is_ok = false, .err = e};
    }
}

bool Result_Url__is_ok(Result_Url *self)
{
    {
        return self->is_ok;
    }
}

bool Result_Url__is_err(Result_Url *self)
{
    {
        return (!self->is_ok);
    }
}

void Result_Url__forget(Result_Url *self)
{
    {
        memset((&self->val), 0, sizeof(Url));
    }
}

Url Result_Url__unwrap(Result_Url *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int __z_drop_flag_v = 1;
        Url v = self->val;
        memset((&self->val), 0, sizeof(Url));
        return ({
            ZC_AUTO _z_ret_mv = v;
            memset(&v, 0, sizeof(_z_ret_mv));
            __z_drop_flag_v = 0;
            if (__z_drop_flag_v)
            {
                Url__Drop_glue(&v);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_v)
        {
            Url__Drop_glue(&v);
        }
    }
}

Url *Result_Url__unwrap_ref(Result_Url *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

Url Result_Url__expect(Result_Url *self, char *msg)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "%s", ": ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Vec_Header Vec_Header__new(void)
{
    {
        return (Vec_Header){};
    }
}

Vec_Header Vec_Header__with_capacity(size_t cap)
{
    {
        if ((cap == 0))
        {
            return (Vec_Header){};
        }
        return (Vec_Header){.data = ((Header *)(malloc((cap * sizeof(Header))))), .cap = cap};
    }
}

void Vec_Header__grow(Vec_Header *self)
{
    {
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        else
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((Header *)(realloc(self->data, (self->cap * sizeof(Header))))));
    }
}

void Vec_Header__grow_to_fit(Vec_Header *self, size_t new_len)
{
    {
        if ((self->cap >= new_len))
        {
            return;
        }
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        while ((self->cap < new_len))
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((Header *)(realloc(self->data, (self->cap * sizeof(Header))))));
    }
}

VecIter_Header Vec_Header__iterator(Vec_Header *self)
{
    {
        return (VecIter_Header){.data = self->data, .count = self->len};
    }
}

VecIterRef_Header Vec_Header__iter_ref(Vec_Header *self)
{
    {
        return (VecIterRef_Header){.data = self->data, .count = self->len};
    }
}

void Vec_Header__push(Vec_Header *self, Header item)
{
    int __z_drop_flag_item = 1;
    {
        if ((self->len >= self->cap))
        {
            Vec_Header__grow(self);
        }
        (self->data[self->len] = item);
        (self->len = (self->len + 1));
    }
    if (__z_drop_flag_item)
    {
        Header__Drop_glue(&item);
    }
}

void Vec_Header__insert(Vec_Header *self, size_t idx, Header item)
{
    int __z_drop_flag_item = 1;
    {
        if ((idx > self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Insert index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        if ((self->len >= self->cap))
        {
            Vec_Header__grow(self);
        }
        if ((idx < self->len))
        {
            memmove(((self->data + idx) + 1), (self->data + idx),
                    ((self->len - idx) * sizeof(Header)));
        }
        (self->data[idx] = item);
        (self->len = (self->len + 1));
    }
    if (__z_drop_flag_item)
    {
        Header__Drop_glue(&item);
    }
}

Header Vec_Header__pop(Vec_Header *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: pop called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->len = (self->len - 1));
        return self->data[self->len];
    }
}

Option_Header Vec_Header__pop_opt(Vec_Header *self)
{
    {
        if ((self->len == 0))
        {
            return Option_Header__None();
        }
        (self->len = (self->len - 1));
        return Option_Header__Some(self->data[self->len]);
    }
}

Header Vec_Header__remove(Vec_Header *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Remove index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int __z_drop_flag_item = 1;
        Header item = self->data[idx];
        if ((idx < (self->len - 1)))
        {
            memmove((self->data + idx), ((self->data + idx) + 1),
                    (((self->len - idx) - 1) * sizeof(Header)));
        }
        (self->len = (self->len - 1));
        return ({
            ZC_AUTO _z_ret_mv = item;
            memset(&item, 0, sizeof(_z_ret_mv));
            __z_drop_flag_item = 0;
            if (__z_drop_flag_item)
            {
                Header__Drop_glue(&item);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_item)
        {
            Header__Drop_glue(&item);
        }
    }
}

void Vec_Header__append(Vec_Header *self, Vec_Header other)
{
    int __z_drop_flag_other = 1;
    {
        size_t new_len = (self->len + other.len);
        Vec_Header__grow_to_fit(self, new_len);
        memcpy((self->data + self->len), other.data, (other.len * sizeof(Header)));
        (self->len = new_len);
        Vec_Header__forget(&other);
    }
    if (__z_drop_flag_other)
    {
        Vec_Header__Drop_glue(&other);
    }
}

Header Vec_Header__get(Vec_Header *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[idx];
    }
}

Header Vec_Header__index(Vec_Header *self, size_t idx)
{
    {
        return Vec_Header__get(self, idx);
    }
}

Header *Vec_Header__get_ref(Vec_Header *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->data[idx]);
    }
}

Header Vec_Header__last(Vec_Header *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: last called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[(self->len - 1)];
    }
}

size_t Vec_Header__length(Vec_Header *self)
{
    {
        return self->len;
    }
}

bool Vec_Header__contains(Vec_Header *self, Header item)
{
    int __z_drop_flag_item = 1;
    {
        size_t i = 0;
        while ((i < self->len))
        {
            if ((memcmp((&self->data[i]), (&item), sizeof(Header)) == 0))
            {
                {
                    bool _z_ret = true;
                    if (__z_drop_flag_item)
                    {
                        Header__Drop_glue(&item);
                    }
                    return _z_ret;
                }
            }
            (i++);
        }
        {
            bool _z_ret = false;
            if (__z_drop_flag_item)
            {
                Header__Drop_glue(&item);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_item)
    {
        Header__Drop_glue(&item);
    }
}

bool Vec_Header__is_empty(Vec_Header *self)
{
    {
        return (self->len == 0);
    }
}

void Vec_Header__clear(Vec_Header *self)
{
    {
        (self->len = 0);
    }
}

void Vec_Header__free(Vec_Header *self)
{
    {
        if (self->data)
        {
            free(self->data);
        }
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

Header Vec_Header__first(Vec_Header *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: first called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[0];
    }
}

void Vec_Header__set(Vec_Header *self, size_t idx, Header item)
{
    int __z_drop_flag_item = 1;
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: set index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->data[idx] = item);
    }
    if (__z_drop_flag_item)
    {
        Header__Drop_glue(&item);
    }
}

void Vec_Header__reverse(Vec_Header *self)
{
    {
        size_t i = 0;
        size_t j = (self->len - 1);
        while ((i < j))
        {
            int __z_drop_flag_tmp = 1;
            Header tmp = self->data[i];
            (self->data[i] = self->data[j]);
            (self->data[j] = tmp);
            (i++);
            (j--);
            if (__z_drop_flag_tmp)
            {
                Header__Drop_glue(&tmp);
            }
        }
    }
}

bool Vec_Header__eq(Vec_Header *self, Vec_Header *other)
{
    {
        bool result = true;
        if ((self->len != (*other).len))
        {
            (result = false);
        }
        else
        {
            size_t i = 0;
            while ((i < self->len))
            {
                if ((memcmp((&self->data[i]), (&(*other).data[i]), sizeof(Header)) != 0))
                {
                    (result = false);
                    break;
                }
                (i = (i + 1));
            }
        }
        return result;
    }
}

void Vec_Header__forget(Vec_Header *self)
{
    {
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

Vec_Header Vec_Header__add(Vec_Header *self, Vec_Header *other)
{
    {
        int __z_drop_flag_result = 1;
        Vec_Header result = Vec_Header__clone(self);
        Vec_Header__append(&result, Vec_Header__clone(other));
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_Header__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_Header__Drop_glue(&result);
        }
    }
}

void Vec_Header__add_assign(Vec_Header *self, Vec_Header *other)
{
    {
        Vec_Header__append(self, Vec_Header__clone(other));
    }
}

bool Vec_Header__neq(Vec_Header *self, Vec_Header *other)
{
    {
        bool result = (!Vec_Header__eq(self, other));
        return result;
    }
}

void Vec_Header__shl(Vec_Header *self, Header item)
{
    int __z_drop_flag_item = 1;
    {
        Vec_Header__push(self, item);
    }
    if (__z_drop_flag_item)
    {
        Header__Drop_glue(&item);
    }
}

void Vec_Header__shr(Vec_Header *self, Header *out_item)
{
    {
        if ((out_item != 0))
        {
            ((*out_item) = Vec_Header__pop(self));
        }
        else
        {
            Vec_Header__pop(self);
        }
    }
}

Vec_Header Vec_Header__mul(Vec_Header *self, size_t count)
{
    {
        int __z_drop_flag_result = 1;
        Vec_Header result = Vec_Header__with_capacity((self->len * count));
        size_t c = 0;
        while ((c < count))
        {
            Vec_Header__append(&result, Vec_Header__clone(self));
            (c = (c + 1));
        }
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_Header__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_Header__Drop_glue(&result);
        }
    }
}

void Vec_Header__mul_assign(Vec_Header *self, size_t count)
{
    {
        if ((count == 0))
        {
            Vec_Header__clear(self);
            return;
        }
        if ((count == 1))
        {
            return;
        }
        size_t original_len = self->len;
        Vec_Header__grow_to_fit(self, (self->len * count));
        size_t c = 1;
        while ((c < count))
        {
            memcpy((self->data + (original_len * c)), self->data, (original_len * sizeof(Header)));
            (self->len = (self->len + original_len));
            (c = (c + 1));
        }
    }
}

Vec_Header Vec_Header__clone(Vec_Header *self)
{
    {
        if ((self->len == 0))
        {
            return (Vec_Header){};
        }
        Header *new_data = ((Header *)(malloc((self->len * sizeof(Header)))));
        size_t i = 0;
        while ((i < self->len))
        {
            (new_data[i] = self->data[i]);
            (i = (i + 1));
        }
        return (Vec_Header){.data = new_data, .len = self->len, .cap = self->len};
    }
}

VecIterResult_Header VecIterRef_Header__next(VecIterRef_Header *self)
{
    {
        if ((self->idx < self->count))
        {
            Header *item = (&self->data[self->idx]);
            (self->idx = (self->idx + 1));
            return (VecIterResult_Header){.ptr = item};
        }
        return (VecIterResult_Header){};
    }
}

VecIterRef_Header VecIterRef_Header__iterator(VecIterRef_Header *self)
{
    {
        return (*self);
    }
}

bool VecIterResult_Header__is_none(VecIterResult_Header *self)
{
    {
        return (self->ptr == 0);
    }
}

Header *VecIterResult_Header__unwrap(VecIterResult_Header *self)
{
    {
        if ((self->ptr == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on null VecIterResult");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->ptr;
    }
}

Option_Header VecIter_Header__next(VecIter_Header *self)
{
    {
        if ((self->idx < self->count))
        {
            int __z_drop_flag_item = 1;
            Header item = self->data[self->idx];
            (self->idx = (self->idx + 1));
            {
                Option_Header _z_ret = Option_Header__Some(item);
                if (__z_drop_flag_item)
                {
                    Header__Drop_glue(&item);
                }
                return _z_ret;
            }
            if (__z_drop_flag_item)
            {
                Header__Drop_glue(&item);
            }
        }
        return Option_Header__None();
    }
}

VecIter_Header VecIter_Header__iterator(VecIter_Header *self)
{
    {
        return (*self);
    }
}

Option_Header Option_Header__Some(Header v)
{
    int __z_drop_flag_v = 1;
    {
        {
            Option_Header _z_ret = (Option_Header){.is_some = true, .val = v};
            if (__z_drop_flag_v)
            {
                Header__Drop_glue(&v);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_v)
    {
        Header__Drop_glue(&v);
    }
}

Option_Header Option_Header__None(void)
{
    {
        return (Option_Header){.is_some = false};
    }
}

bool Option_Header__is_some(Option_Header *self)
{
    {
        return self->is_some;
    }
}

bool Option_Header__is_none(Option_Header *self)
{
    {
        return (!self->is_some);
    }
}

void Option_Header__forget(Option_Header *self)
{
    {
        memset((&self->val), 0, sizeof(Header));
    }
}

Header Option_Header__unwrap(Option_Header *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int __z_drop_flag_v = 1;
        Header v = self->val;
        memset((&self->val), 0, sizeof(Header));
        return ({
            ZC_AUTO _z_ret_mv = v;
            memset(&v, 0, sizeof(_z_ret_mv));
            __z_drop_flag_v = 0;
            if (__z_drop_flag_v)
            {
                Header__Drop_glue(&v);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_v)
        {
            Header__Drop_glue(&v);
        }
    }
}

Header *Option_Header__unwrap_ref(Option_Header *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

Header Option_Header__unwrap_or(Option_Header *self, Header def_val)
{
    int __z_drop_flag_def_val = 1;
    {
        if (self->is_some)
        {
            {
                Header _z_ret = self->val;
                if (__z_drop_flag_def_val)
                {
                    Header__Drop_glue(&def_val);
                }
                return _z_ret;
            }
        }
        return ({
            ZC_AUTO _z_ret_mv = def_val;
            memset(&def_val, 0, sizeof(_z_ret_mv));
            __z_drop_flag_def_val = 0;
            if (__z_drop_flag_def_val)
            {
                Header__Drop_glue(&def_val);
            }
            _z_ret_mv;
        });
    }
    if (__z_drop_flag_def_val)
    {
        Header__Drop_glue(&def_val);
    }
}

Header Option_Header__expect(Option_Header *self, char *msg)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Option_Header Option_Header__or_else(Option_Header *self, Option_Header other)
{
    {
        if (self->is_some)
        {
            return (*self);
        }
        return other;
    }
}

void Vec_Header__Drop_drop(Vec_Header *self)
{
    {
        Vec_Header__free(self);
    }
}

Result_TcpListener Result_TcpListener__Ok(TcpListener v)
{
    int __z_drop_flag_v = 1;
    {
        {
            Result_TcpListener _z_ret = (Result_TcpListener){.is_ok = true, .val = v};
            if (__z_drop_flag_v)
            {
                TcpListener__Drop_glue(&v);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_v)
    {
        TcpListener__Drop_glue(&v);
    }
}

Result_TcpListener Result_TcpListener__Err(char *e)
{
    {
        return (Result_TcpListener){.is_ok = false, .err = e};
    }
}

bool Result_TcpListener__is_ok(Result_TcpListener *self)
{
    {
        return self->is_ok;
    }
}

bool Result_TcpListener__is_err(Result_TcpListener *self)
{
    {
        return (!self->is_ok);
    }
}

void Result_TcpListener__forget(Result_TcpListener *self)
{
    {
        memset((&self->val), 0, sizeof(TcpListener));
    }
}

TcpListener Result_TcpListener__unwrap(Result_TcpListener *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int __z_drop_flag_v = 1;
        TcpListener v = self->val;
        memset((&self->val), 0, sizeof(TcpListener));
        return ({
            ZC_AUTO _z_ret_mv = v;
            memset(&v, 0, sizeof(_z_ret_mv));
            __z_drop_flag_v = 0;
            if (__z_drop_flag_v)
            {
                TcpListener__Drop_glue(&v);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_v)
        {
            TcpListener__Drop_glue(&v);
        }
    }
}

TcpListener *Result_TcpListener__unwrap_ref(Result_TcpListener *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

TcpListener Result_TcpListener__expect(Result_TcpListener *self, char *msg)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "%s", ": ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Result_TcpStream Result_TcpStream__Ok(TcpStream v)
{
    int __z_drop_flag_v = 1;
    {
        {
            Result_TcpStream _z_ret = (Result_TcpStream){.is_ok = true, .val = v};
            if (__z_drop_flag_v)
            {
                TcpStream__Drop_glue(&v);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_v)
    {
        TcpStream__Drop_glue(&v);
    }
}

Result_TcpStream Result_TcpStream__Err(char *e)
{
    {
        return (Result_TcpStream){.is_ok = false, .err = e};
    }
}

bool Result_TcpStream__is_ok(Result_TcpStream *self)
{
    {
        return self->is_ok;
    }
}

bool Result_TcpStream__is_err(Result_TcpStream *self)
{
    {
        return (!self->is_ok);
    }
}

void Result_TcpStream__forget(Result_TcpStream *self)
{
    {
        memset((&self->val), 0, sizeof(TcpStream));
    }
}

TcpStream Result_TcpStream__unwrap(Result_TcpStream *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int __z_drop_flag_v = 1;
        TcpStream v = self->val;
        memset((&self->val), 0, sizeof(TcpStream));
        return ({
            ZC_AUTO _z_ret_mv = v;
            memset(&v, 0, sizeof(_z_ret_mv));
            __z_drop_flag_v = 0;
            if (__z_drop_flag_v)
            {
                TcpStream__Drop_glue(&v);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_v)
        {
            TcpStream__Drop_glue(&v);
        }
    }
}

TcpStream *Result_TcpStream__unwrap_ref(Result_TcpStream *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

TcpStream Result_TcpStream__expect(Result_TcpStream *self, char *msg)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "%s", ": ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Result_size_t Result_size_t__Ok(size_t v)
{
    {
        return (Result_size_t){.is_ok = true, .val = v};
    }
}

Result_size_t Result_size_t__Err(char *e)
{
    {
        return (Result_size_t){.is_ok = false, .err = e};
    }
}

bool Result_size_t__is_ok(Result_size_t *self)
{
    {
        return self->is_ok;
    }
}

bool Result_size_t__is_err(Result_size_t *self)
{
    {
        return (!self->is_ok);
    }
}

void Result_size_t__forget(Result_size_t *self)
{
    {
        memset((&self->val), 0, sizeof(size_t));
    }
}

size_t Result_size_t__unwrap(Result_size_t *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        size_t v = self->val;
        memset((&self->val), 0, sizeof(size_t));
        return v;
    }
}

size_t *Result_size_t__unwrap_ref(Result_size_t *self)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on Err: ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

size_t Result_size_t__expect(Result_size_t *self, char *msg)
{
    {
        if ((!self->is_ok))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "%s", ": ");
                fprintf(stderr, "%s", self->err);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Vec_String Vec_String__new(void)
{
    {
        return (Vec_String){};
    }
}

Vec_String Vec_String__with_capacity(size_t cap)
{
    {
        if ((cap == 0))
        {
            return (Vec_String){};
        }
        return (Vec_String){.data = ((String *)(malloc((cap * sizeof(String))))), .cap = cap};
    }
}

void Vec_String__grow(Vec_String *self)
{
    {
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        else
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((String *)(realloc(self->data, (self->cap * sizeof(String))))));
    }
}

void Vec_String__grow_to_fit(Vec_String *self, size_t new_len)
{
    {
        if ((self->cap >= new_len))
        {
            return;
        }
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        while ((self->cap < new_len))
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((String *)(realloc(self->data, (self->cap * sizeof(String))))));
    }
}

VecIter_String Vec_String__iterator(Vec_String *self)
{
    {
        return (VecIter_String){.data = self->data, .count = self->len};
    }
}

VecIterRef_String Vec_String__iter_ref(Vec_String *self)
{
    {
        return (VecIterRef_String){.data = self->data, .count = self->len};
    }
}

void Vec_String__push(Vec_String *self, String item)
{
    int __z_drop_flag_item = 1;
    {
        if ((self->len >= self->cap))
        {
            Vec_String__grow(self);
        }
        (self->data[self->len] = item);
        (self->len = (self->len + 1));
    }
    if (__z_drop_flag_item)
    {
        String__Drop_glue(&item);
    }
}

void Vec_String__insert(Vec_String *self, size_t idx, String item)
{
    int __z_drop_flag_item = 1;
    {
        if ((idx > self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Insert index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        if ((self->len >= self->cap))
        {
            Vec_String__grow(self);
        }
        if ((idx < self->len))
        {
            memmove(((self->data + idx) + 1), (self->data + idx),
                    ((self->len - idx) * sizeof(String)));
        }
        (self->data[idx] = item);
        (self->len = (self->len + 1));
    }
    if (__z_drop_flag_item)
    {
        String__Drop_glue(&item);
    }
}

String Vec_String__pop(Vec_String *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: pop called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->len = (self->len - 1));
        return self->data[self->len];
    }
}

Option_String Vec_String__pop_opt(Vec_String *self)
{
    {
        if ((self->len == 0))
        {
            return Option_String__None();
        }
        (self->len = (self->len - 1));
        return Option_String__Some(self->data[self->len]);
    }
}

String Vec_String__remove(Vec_String *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Remove index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int __z_drop_flag_item = 1;
        String item = self->data[idx];
        if ((idx < (self->len - 1)))
        {
            memmove((self->data + idx), ((self->data + idx) + 1),
                    (((self->len - idx) - 1) * sizeof(String)));
        }
        (self->len = (self->len - 1));
        return ({
            ZC_AUTO _z_ret_mv = item;
            memset(&item, 0, sizeof(_z_ret_mv));
            __z_drop_flag_item = 0;
            if (__z_drop_flag_item)
            {
                String__Drop_glue(&item);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_item)
        {
            String__Drop_glue(&item);
        }
    }
}

void Vec_String__append(Vec_String *self, Vec_String other)
{
    int __z_drop_flag_other = 1;
    {
        size_t new_len = (self->len + other.len);
        Vec_String__grow_to_fit(self, new_len);
        memcpy((self->data + self->len), other.data, (other.len * sizeof(String)));
        (self->len = new_len);
        Vec_String__forget(&other);
    }
    if (__z_drop_flag_other)
    {
        Vec_String__Drop_glue(&other);
    }
}

String Vec_String__get(Vec_String *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[idx];
    }
}

String Vec_String__index(Vec_String *self, size_t idx)
{
    {
        return Vec_String__get(self, idx);
    }
}

String *Vec_String__get_ref(Vec_String *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->data[idx]);
    }
}

String Vec_String__last(Vec_String *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: last called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[(self->len - 1)];
    }
}

size_t Vec_String__length(Vec_String *self)
{
    {
        return self->len;
    }
}

bool Vec_String__contains(Vec_String *self, String item)
{
    int __z_drop_flag_item = 1;
    {
        size_t i = 0;
        while ((i < self->len))
        {
            if ((memcmp((&self->data[i]), (&item), sizeof(String)) == 0))
            {
                {
                    bool _z_ret = true;
                    if (__z_drop_flag_item)
                    {
                        String__Drop_glue(&item);
                    }
                    return _z_ret;
                }
            }
            (i++);
        }
        {
            bool _z_ret = false;
            if (__z_drop_flag_item)
            {
                String__Drop_glue(&item);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_item)
    {
        String__Drop_glue(&item);
    }
}

bool Vec_String__is_empty(Vec_String *self)
{
    {
        return (self->len == 0);
    }
}

void Vec_String__clear(Vec_String *self)
{
    {
        (self->len = 0);
    }
}

void Vec_String__free(Vec_String *self)
{
    {
        if (self->data)
        {
            free(self->data);
        }
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

String Vec_String__first(Vec_String *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: first called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[0];
    }
}

void Vec_String__set(Vec_String *self, size_t idx, String item)
{
    int __z_drop_flag_item = 1;
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: set index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->data[idx] = item);
    }
    if (__z_drop_flag_item)
    {
        String__Drop_glue(&item);
    }
}

void Vec_String__reverse(Vec_String *self)
{
    {
        size_t i = 0;
        size_t j = (self->len - 1);
        while ((i < j))
        {
            int __z_drop_flag_tmp = 1;
            String tmp = self->data[i];
            (self->data[i] = self->data[j]);
            (self->data[j] = tmp);
            (i++);
            (j--);
            if (__z_drop_flag_tmp)
            {
                String__Drop_glue(&tmp);
            }
        }
    }
}

bool Vec_String__eq(Vec_String *self, Vec_String *other)
{
    {
        bool result = true;
        if ((self->len != (*other).len))
        {
            (result = false);
        }
        else
        {
            size_t i = 0;
            while ((i < self->len))
            {
                if ((memcmp((&self->data[i]), (&(*other).data[i]), sizeof(String)) != 0))
                {
                    (result = false);
                    break;
                }
                (i = (i + 1));
            }
        }
        return result;
    }
}

void Vec_String__forget(Vec_String *self)
{
    {
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

Vec_String Vec_String__add(Vec_String *self, Vec_String *other)
{
    {
        int __z_drop_flag_result = 1;
        Vec_String result = Vec_String__clone(self);
        Vec_String__append(&result, Vec_String__clone(other));
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_String__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_String__Drop_glue(&result);
        }
    }
}

void Vec_String__add_assign(Vec_String *self, Vec_String *other)
{
    {
        Vec_String__append(self, Vec_String__clone(other));
    }
}

bool Vec_String__neq(Vec_String *self, Vec_String *other)
{
    {
        bool result = (!Vec_String__eq(self, other));
        return result;
    }
}

void Vec_String__shl(Vec_String *self, String item)
{
    int __z_drop_flag_item = 1;
    {
        Vec_String__push(self, item);
    }
    if (__z_drop_flag_item)
    {
        String__Drop_glue(&item);
    }
}

void Vec_String__shr(Vec_String *self, String *out_item)
{
    {
        if ((out_item != 0))
        {
            ((*out_item) = Vec_String__pop(self));
        }
        else
        {
            Vec_String__pop(self);
        }
    }
}

Vec_String Vec_String__mul(Vec_String *self, size_t count)
{
    {
        int __z_drop_flag_result = 1;
        Vec_String result = Vec_String__with_capacity((self->len * count));
        size_t c = 0;
        while ((c < count))
        {
            Vec_String__append(&result, Vec_String__clone(self));
            (c = (c + 1));
        }
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_String__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_String__Drop_glue(&result);
        }
    }
}

void Vec_String__mul_assign(Vec_String *self, size_t count)
{
    {
        if ((count == 0))
        {
            Vec_String__clear(self);
            return;
        }
        if ((count == 1))
        {
            return;
        }
        size_t original_len = self->len;
        Vec_String__grow_to_fit(self, (self->len * count));
        size_t c = 1;
        while ((c < count))
        {
            memcpy((self->data + (original_len * c)), self->data, (original_len * sizeof(String)));
            (self->len = (self->len + original_len));
            (c = (c + 1));
        }
    }
}

Vec_String Vec_String__clone(Vec_String *self)
{
    {
        if ((self->len == 0))
        {
            return (Vec_String){};
        }
        String *new_data = ((String *)(malloc((self->len * sizeof(String)))));
        size_t i = 0;
        while ((i < self->len))
        {
            (new_data[i] = self->data[i]);
            (i = (i + 1));
        }
        return (Vec_String){.data = new_data, .len = self->len, .cap = self->len};
    }
}

VecIterResult_String VecIterRef_String__next(VecIterRef_String *self)
{
    {
        if ((self->idx < self->count))
        {
            String *item = (&self->data[self->idx]);
            (self->idx = (self->idx + 1));
            return (VecIterResult_String){.ptr = item};
        }
        return (VecIterResult_String){};
    }
}

VecIterRef_String VecIterRef_String__iterator(VecIterRef_String *self)
{
    {
        return (*self);
    }
}

bool VecIterResult_String__is_none(VecIterResult_String *self)
{
    {
        return (self->ptr == 0);
    }
}

String *VecIterResult_String__unwrap(VecIterResult_String *self)
{
    {
        if ((self->ptr == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on null VecIterResult");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->ptr;
    }
}

Option_String VecIter_String__next(VecIter_String *self)
{
    {
        if ((self->idx < self->count))
        {
            int __z_drop_flag_item = 1;
            String item = self->data[self->idx];
            (self->idx = (self->idx + 1));
            {
                Option_String _z_ret = Option_String__Some(item);
                if (__z_drop_flag_item)
                {
                    String__Drop_glue(&item);
                }
                return _z_ret;
            }
            if (__z_drop_flag_item)
            {
                String__Drop_glue(&item);
            }
        }
        return Option_String__None();
    }
}

VecIter_String VecIter_String__iterator(VecIter_String *self)
{
    {
        return (*self);
    }
}

Option_String Option_String__Some(String v)
{
    int __z_drop_flag_v = 1;
    {
        {
            Option_String _z_ret = (Option_String){.is_some = true, .val = v};
            if (__z_drop_flag_v)
            {
                String__Drop_glue(&v);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_v)
    {
        String__Drop_glue(&v);
    }
}

Option_String Option_String__None(void)
{
    {
        return (Option_String){.is_some = false};
    }
}

bool Option_String__is_some(Option_String *self)
{
    {
        return self->is_some;
    }
}

bool Option_String__is_none(Option_String *self)
{
    {
        return (!self->is_some);
    }
}

void Option_String__forget(Option_String *self)
{
    {
        memset((&self->val), 0, sizeof(String));
    }
}

String Option_String__unwrap(Option_String *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int __z_drop_flag_v = 1;
        String v = self->val;
        memset((&self->val), 0, sizeof(String));
        return ({
            ZC_AUTO _z_ret_mv = v;
            memset(&v, 0, sizeof(_z_ret_mv));
            __z_drop_flag_v = 0;
            if (__z_drop_flag_v)
            {
                String__Drop_glue(&v);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_v)
        {
            String__Drop_glue(&v);
        }
    }
}

String *Option_String__unwrap_ref(Option_String *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

String Option_String__unwrap_or(Option_String *self, String def_val)
{
    int __z_drop_flag_def_val = 1;
    {
        if (self->is_some)
        {
            {
                String _z_ret = self->val;
                if (__z_drop_flag_def_val)
                {
                    String__Drop_glue(&def_val);
                }
                return _z_ret;
            }
        }
        return ({
            ZC_AUTO _z_ret_mv = def_val;
            memset(&def_val, 0, sizeof(_z_ret_mv));
            __z_drop_flag_def_val = 0;
            if (__z_drop_flag_def_val)
            {
                String__Drop_glue(&def_val);
            }
            _z_ret_mv;
        });
    }
    if (__z_drop_flag_def_val)
    {
        String__Drop_glue(&def_val);
    }
}

String Option_String__expect(Option_String *self, char *msg)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Option_String Option_String__or_else(Option_String *self, Option_String other)
{
    {
        if (self->is_some)
        {
            return (*self);
        }
        return other;
    }
}

void Vec_String__Drop_drop(Vec_String *self)
{
    {
        Vec_String__free(self);
    }
}

Vec_int32_t Vec_int32_t__new(void)
{
    {
        return (Vec_int32_t){};
    }
}

Vec_int32_t Vec_int32_t__with_capacity(size_t cap)
{
    {
        if ((cap == 0))
        {
            return (Vec_int32_t){};
        }
        return (Vec_int32_t){.data = ((int32_t *)(malloc((cap * sizeof(int32_t))))), .cap = cap};
    }
}

void Vec_int32_t__grow(Vec_int32_t *self)
{
    {
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        else
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((int32_t *)(realloc(self->data, (self->cap * sizeof(int32_t))))));
    }
}

void Vec_int32_t__grow_to_fit(Vec_int32_t *self, size_t new_len)
{
    {
        if ((self->cap >= new_len))
        {
            return;
        }
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        while ((self->cap < new_len))
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((int32_t *)(realloc(self->data, (self->cap * sizeof(int32_t))))));
    }
}

VecIter_int32_t Vec_int32_t__iterator(Vec_int32_t *self)
{
    {
        return (VecIter_int32_t){.data = self->data, .count = self->len};
    }
}

VecIterRef_int32_t Vec_int32_t__iter_ref(Vec_int32_t *self)
{
    {
        return (VecIterRef_int32_t){.data = self->data, .count = self->len};
    }
}

void Vec_int32_t__push(Vec_int32_t *self, int32_t item)
{
    {
        if ((self->len >= self->cap))
        {
            Vec_int32_t__grow(self);
        }
        (self->data[self->len] = item);
        (self->len = (self->len + 1));
    }
}

void Vec_int32_t__insert(Vec_int32_t *self, size_t idx, int32_t item)
{
    {
        if ((idx > self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Insert index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        if ((self->len >= self->cap))
        {
            Vec_int32_t__grow(self);
        }
        if ((idx < self->len))
        {
            memmove(((self->data + idx) + 1), (self->data + idx),
                    ((self->len - idx) * sizeof(int32_t)));
        }
        (self->data[idx] = item);
        (self->len = (self->len + 1));
    }
}

int32_t Vec_int32_t__pop(Vec_int32_t *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: pop called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->len = (self->len - 1));
        return self->data[self->len];
    }
}

Option_int32_t Vec_int32_t__pop_opt(Vec_int32_t *self)
{
    {
        if ((self->len == 0))
        {
            return Option_int32_t__None();
        }
        (self->len = (self->len - 1));
        return Option_int32_t__Some(self->data[self->len]);
    }
}

int32_t Vec_int32_t__remove(Vec_int32_t *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Remove index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int32_t item = self->data[idx];
        if ((idx < (self->len - 1)))
        {
            memmove((self->data + idx), ((self->data + idx) + 1),
                    (((self->len - idx) - 1) * sizeof(int32_t)));
        }
        (self->len = (self->len - 1));
        return item;
    }
}

void Vec_int32_t__append(Vec_int32_t *self, Vec_int32_t other)
{
    int __z_drop_flag_other = 1;
    {
        size_t new_len = (self->len + other.len);
        Vec_int32_t__grow_to_fit(self, new_len);
        memcpy((self->data + self->len), other.data, (other.len * sizeof(int32_t)));
        (self->len = new_len);
        Vec_int32_t__forget(&other);
    }
    if (__z_drop_flag_other)
    {
        Vec_int32_t__Drop_glue(&other);
    }
}

int32_t Vec_int32_t__get(Vec_int32_t *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[idx];
    }
}

int32_t Vec_int32_t__index(Vec_int32_t *self, size_t idx)
{
    {
        return Vec_int32_t__get(self, idx);
    }
}

int32_t *Vec_int32_t__get_ref(Vec_int32_t *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->data[idx]);
    }
}

int32_t Vec_int32_t__last(Vec_int32_t *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: last called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[(self->len - 1)];
    }
}

size_t Vec_int32_t__length(Vec_int32_t *self)
{
    {
        return self->len;
    }
}

bool Vec_int32_t__contains(Vec_int32_t *self, int32_t item)
{
    {
        size_t i = 0;
        while ((i < self->len))
        {
            if ((memcmp((&self->data[i]), (&item), sizeof(int32_t)) == 0))
            {
                return true;
            }
            (i++);
        }
        return false;
    }
}

bool Vec_int32_t__is_empty(Vec_int32_t *self)
{
    {
        return (self->len == 0);
    }
}

void Vec_int32_t__clear(Vec_int32_t *self)
{
    {
        (self->len = 0);
    }
}

void Vec_int32_t__free(Vec_int32_t *self)
{
    {
        if (self->data)
        {
            free(self->data);
        }
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

int32_t Vec_int32_t__first(Vec_int32_t *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: first called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[0];
    }
}

void Vec_int32_t__set(Vec_int32_t *self, size_t idx, int32_t item)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: set index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->data[idx] = item);
    }
}

void Vec_int32_t__reverse(Vec_int32_t *self)
{
    {
        size_t i = 0;
        size_t j = (self->len - 1);
        while ((i < j))
        {
            int32_t tmp = self->data[i];
            (self->data[i] = self->data[j]);
            (self->data[j] = tmp);
            (i++);
            (j--);
        }
    }
}

bool Vec_int32_t__eq(Vec_int32_t *self, Vec_int32_t *other)
{
    {
        bool result = true;
        if ((self->len != (*other).len))
        {
            (result = false);
        }
        else
        {
            size_t i = 0;
            while ((i < self->len))
            {
                if ((memcmp((&self->data[i]), (&(*other).data[i]), sizeof(int32_t)) != 0))
                {
                    (result = false);
                    break;
                }
                (i = (i + 1));
            }
        }
        return result;
    }
}

void Vec_int32_t__forget(Vec_int32_t *self)
{
    {
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

Vec_int32_t Vec_int32_t__add(Vec_int32_t *self, Vec_int32_t *other)
{
    {
        int __z_drop_flag_result = 1;
        Vec_int32_t result = Vec_int32_t__clone(self);
        Vec_int32_t__append(&result, Vec_int32_t__clone(other));
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_int32_t__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_int32_t__Drop_glue(&result);
        }
    }
}

void Vec_int32_t__add_assign(Vec_int32_t *self, Vec_int32_t *other)
{
    {
        Vec_int32_t__append(self, Vec_int32_t__clone(other));
    }
}

bool Vec_int32_t__neq(Vec_int32_t *self, Vec_int32_t *other)
{
    {
        bool result = (!Vec_int32_t__eq(self, other));
        return result;
    }
}

void Vec_int32_t__shl(Vec_int32_t *self, int32_t item)
{
    {
        Vec_int32_t__push(self, item);
    }
}

void Vec_int32_t__shr(Vec_int32_t *self, int32_t *out_item)
{
    {
        if ((out_item != 0))
        {
            ((*out_item) = Vec_int32_t__pop(self));
        }
        else
        {
            Vec_int32_t__pop(self);
        }
    }
}

Vec_int32_t Vec_int32_t__mul(Vec_int32_t *self, size_t count)
{
    {
        int __z_drop_flag_result = 1;
        Vec_int32_t result = Vec_int32_t__with_capacity((self->len * count));
        size_t c = 0;
        while ((c < count))
        {
            Vec_int32_t__append(&result, Vec_int32_t__clone(self));
            (c = (c + 1));
        }
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_int32_t__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_int32_t__Drop_glue(&result);
        }
    }
}

void Vec_int32_t__mul_assign(Vec_int32_t *self, size_t count)
{
    {
        if ((count == 0))
        {
            Vec_int32_t__clear(self);
            return;
        }
        if ((count == 1))
        {
            return;
        }
        size_t original_len = self->len;
        Vec_int32_t__grow_to_fit(self, (self->len * count));
        size_t c = 1;
        while ((c < count))
        {
            memcpy((self->data + (original_len * c)), self->data, (original_len * sizeof(int32_t)));
            (self->len = (self->len + original_len));
            (c = (c + 1));
        }
    }
}

Vec_int32_t Vec_int32_t__clone(Vec_int32_t *self)
{
    {
        if ((self->len == 0))
        {
            return (Vec_int32_t){};
        }
        int32_t *new_data = ((int32_t *)(malloc((self->len * sizeof(int32_t)))));
        size_t i = 0;
        while ((i < self->len))
        {
            (new_data[i] = self->data[i]);
            (i = (i + 1));
        }
        return (Vec_int32_t){.data = new_data, .len = self->len, .cap = self->len};
    }
}

VecIterResult_int32_t VecIterRef_int32_t__next(VecIterRef_int32_t *self)
{
    {
        if ((self->idx < self->count))
        {
            int32_t *item = (&self->data[self->idx]);
            (self->idx = (self->idx + 1));
            return (VecIterResult_int32_t){.ptr = item};
        }
        return (VecIterResult_int32_t){};
    }
}

VecIterRef_int32_t VecIterRef_int32_t__iterator(VecIterRef_int32_t *self)
{
    {
        return (*self);
    }
}

bool VecIterResult_int32_t__is_none(VecIterResult_int32_t *self)
{
    {
        return (self->ptr == 0);
    }
}

int32_t *VecIterResult_int32_t__unwrap(VecIterResult_int32_t *self)
{
    {
        if ((self->ptr == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on null VecIterResult");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->ptr;
    }
}

Option_int32_t VecIter_int32_t__next(VecIter_int32_t *self)
{
    {
        if ((self->idx < self->count))
        {
            int32_t item = self->data[self->idx];
            (self->idx = (self->idx + 1));
            return Option_int32_t__Some(item);
        }
        return Option_int32_t__None();
    }
}

VecIter_int32_t VecIter_int32_t__iterator(VecIter_int32_t *self)
{
    {
        return (*self);
    }
}

void Vec_int32_t__Drop_drop(Vec_int32_t *self)
{
    {
        Vec_int32_t__free(self);
    }
}

Vec_size_t Vec_size_t__new(void)
{
    {
        return (Vec_size_t){};
    }
}

Vec_size_t Vec_size_t__with_capacity(size_t cap)
{
    {
        if ((cap == 0))
        {
            return (Vec_size_t){};
        }
        return (Vec_size_t){.data = ((size_t *)(malloc((cap * sizeof(size_t))))), .cap = cap};
    }
}

void Vec_size_t__grow(Vec_size_t *self)
{
    {
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        else
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((size_t *)(realloc(self->data, (self->cap * sizeof(size_t))))));
    }
}

void Vec_size_t__grow_to_fit(Vec_size_t *self, size_t new_len)
{
    {
        if ((self->cap >= new_len))
        {
            return;
        }
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        while ((self->cap < new_len))
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((size_t *)(realloc(self->data, (self->cap * sizeof(size_t))))));
    }
}

VecIter_size_t Vec_size_t__iterator(Vec_size_t *self)
{
    {
        return (VecIter_size_t){.data = self->data, .count = self->len};
    }
}

VecIterRef_size_t Vec_size_t__iter_ref(Vec_size_t *self)
{
    {
        return (VecIterRef_size_t){.data = self->data, .count = self->len};
    }
}

void Vec_size_t__push(Vec_size_t *self, size_t item)
{
    {
        if ((self->len >= self->cap))
        {
            Vec_size_t__grow(self);
        }
        (self->data[self->len] = item);
        (self->len = (self->len + 1));
    }
}

void Vec_size_t__insert(Vec_size_t *self, size_t idx, size_t item)
{
    {
        if ((idx > self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Insert index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        if ((self->len >= self->cap))
        {
            Vec_size_t__grow(self);
        }
        if ((idx < self->len))
        {
            memmove(((self->data + idx) + 1), (self->data + idx),
                    ((self->len - idx) * sizeof(size_t)));
        }
        (self->data[idx] = item);
        (self->len = (self->len + 1));
    }
}

size_t Vec_size_t__pop(Vec_size_t *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: pop called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->len = (self->len - 1));
        return self->data[self->len];
    }
}

Option_size_t Vec_size_t__pop_opt(Vec_size_t *self)
{
    {
        if ((self->len == 0))
        {
            return Option_size_t__None();
        }
        (self->len = (self->len - 1));
        return Option_size_t__Some(self->data[self->len]);
    }
}

size_t Vec_size_t__remove(Vec_size_t *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Remove index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        size_t item = self->data[idx];
        if ((idx < (self->len - 1)))
        {
            memmove((self->data + idx), ((self->data + idx) + 1),
                    (((self->len - idx) - 1) * sizeof(size_t)));
        }
        (self->len = (self->len - 1));
        return item;
    }
}

void Vec_size_t__append(Vec_size_t *self, Vec_size_t other)
{
    int __z_drop_flag_other = 1;
    {
        size_t new_len = (self->len + other.len);
        Vec_size_t__grow_to_fit(self, new_len);
        memcpy((self->data + self->len), other.data, (other.len * sizeof(size_t)));
        (self->len = new_len);
        Vec_size_t__forget(&other);
    }
    if (__z_drop_flag_other)
    {
        Vec_size_t__Drop_glue(&other);
    }
}

size_t Vec_size_t__get(Vec_size_t *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[idx];
    }
}

size_t Vec_size_t__index(Vec_size_t *self, size_t idx)
{
    {
        return Vec_size_t__get(self, idx);
    }
}

size_t *Vec_size_t__get_ref(Vec_size_t *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->data[idx]);
    }
}

size_t Vec_size_t__last(Vec_size_t *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: last called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[(self->len - 1)];
    }
}

size_t Vec_size_t__length(Vec_size_t *self)
{
    {
        return self->len;
    }
}

bool Vec_size_t__contains(Vec_size_t *self, size_t item)
{
    {
        size_t i = 0;
        while ((i < self->len))
        {
            if ((memcmp((&self->data[i]), (&item), sizeof(size_t)) == 0))
            {
                return true;
            }
            (i++);
        }
        return false;
    }
}

bool Vec_size_t__is_empty(Vec_size_t *self)
{
    {
        return (self->len == 0);
    }
}

void Vec_size_t__clear(Vec_size_t *self)
{
    {
        (self->len = 0);
    }
}

void Vec_size_t__free(Vec_size_t *self)
{
    {
        if (self->data)
        {
            free(self->data);
        }
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

size_t Vec_size_t__first(Vec_size_t *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: first called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[0];
    }
}

void Vec_size_t__set(Vec_size_t *self, size_t idx, size_t item)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: set index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->data[idx] = item);
    }
}

void Vec_size_t__reverse(Vec_size_t *self)
{
    {
        size_t i = 0;
        size_t j = (self->len - 1);
        while ((i < j))
        {
            size_t tmp = self->data[i];
            (self->data[i] = self->data[j]);
            (self->data[j] = tmp);
            (i++);
            (j--);
        }
    }
}

bool Vec_size_t__eq(Vec_size_t *self, Vec_size_t *other)
{
    {
        bool result = true;
        if ((self->len != (*other).len))
        {
            (result = false);
        }
        else
        {
            size_t i = 0;
            while ((i < self->len))
            {
                if ((memcmp((&self->data[i]), (&(*other).data[i]), sizeof(size_t)) != 0))
                {
                    (result = false);
                    break;
                }
                (i = (i + 1));
            }
        }
        return result;
    }
}

void Vec_size_t__forget(Vec_size_t *self)
{
    {
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

Vec_size_t Vec_size_t__add(Vec_size_t *self, Vec_size_t *other)
{
    {
        int __z_drop_flag_result = 1;
        Vec_size_t result = Vec_size_t__clone(self);
        Vec_size_t__append(&result, Vec_size_t__clone(other));
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_size_t__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_size_t__Drop_glue(&result);
        }
    }
}

void Vec_size_t__add_assign(Vec_size_t *self, Vec_size_t *other)
{
    {
        Vec_size_t__append(self, Vec_size_t__clone(other));
    }
}

bool Vec_size_t__neq(Vec_size_t *self, Vec_size_t *other)
{
    {
        bool result = (!Vec_size_t__eq(self, other));
        return result;
    }
}

void Vec_size_t__shl(Vec_size_t *self, size_t item)
{
    {
        Vec_size_t__push(self, item);
    }
}

void Vec_size_t__shr(Vec_size_t *self, size_t *out_item)
{
    {
        if ((out_item != 0))
        {
            ((*out_item) = Vec_size_t__pop(self));
        }
        else
        {
            Vec_size_t__pop(self);
        }
    }
}

Vec_size_t Vec_size_t__mul(Vec_size_t *self, size_t count)
{
    {
        int __z_drop_flag_result = 1;
        Vec_size_t result = Vec_size_t__with_capacity((self->len * count));
        size_t c = 0;
        while ((c < count))
        {
            Vec_size_t__append(&result, Vec_size_t__clone(self));
            (c = (c + 1));
        }
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_size_t__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_size_t__Drop_glue(&result);
        }
    }
}

void Vec_size_t__mul_assign(Vec_size_t *self, size_t count)
{
    {
        if ((count == 0))
        {
            Vec_size_t__clear(self);
            return;
        }
        if ((count == 1))
        {
            return;
        }
        size_t original_len = self->len;
        Vec_size_t__grow_to_fit(self, (self->len * count));
        size_t c = 1;
        while ((c < count))
        {
            memcpy((self->data + (original_len * c)), self->data, (original_len * sizeof(size_t)));
            (self->len = (self->len + original_len));
            (c = (c + 1));
        }
    }
}

Vec_size_t Vec_size_t__clone(Vec_size_t *self)
{
    {
        if ((self->len == 0))
        {
            return (Vec_size_t){};
        }
        size_t *new_data = ((size_t *)(malloc((self->len * sizeof(size_t)))));
        size_t i = 0;
        while ((i < self->len))
        {
            (new_data[i] = self->data[i]);
            (i = (i + 1));
        }
        return (Vec_size_t){.data = new_data, .len = self->len, .cap = self->len};
    }
}

VecIterResult_size_t VecIterRef_size_t__next(VecIterRef_size_t *self)
{
    {
        if ((self->idx < self->count))
        {
            size_t *item = (&self->data[self->idx]);
            (self->idx = (self->idx + 1));
            return (VecIterResult_size_t){.ptr = item};
        }
        return (VecIterResult_size_t){};
    }
}

VecIterRef_size_t VecIterRef_size_t__iterator(VecIterRef_size_t *self)
{
    {
        return (*self);
    }
}

bool VecIterResult_size_t__is_none(VecIterResult_size_t *self)
{
    {
        return (self->ptr == 0);
    }
}

size_t *VecIterResult_size_t__unwrap(VecIterResult_size_t *self)
{
    {
        if ((self->ptr == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on null VecIterResult");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->ptr;
    }
}

Option_size_t VecIter_size_t__next(VecIter_size_t *self)
{
    {
        if ((self->idx < self->count))
        {
            size_t item = self->data[self->idx];
            (self->idx = (self->idx + 1));
            return Option_size_t__Some(item);
        }
        return Option_size_t__None();
    }
}

VecIter_size_t VecIter_size_t__iterator(VecIter_size_t *self)
{
    {
        return (*self);
    }
}

void Vec_size_t__Drop_drop(Vec_size_t *self)
{
    {
        Vec_size_t__free(self);
    }
}

Option_size_t Option_size_t__Some(size_t v)
{
    {
        return (Option_size_t){.is_some = true, .val = v};
    }
}

Option_size_t Option_size_t__None(void)
{
    {
        return (Option_size_t){.is_some = false};
    }
}

bool Option_size_t__is_some(Option_size_t *self)
{
    {
        return self->is_some;
    }
}

bool Option_size_t__is_none(Option_size_t *self)
{
    {
        return (!self->is_some);
    }
}

void Option_size_t__forget(Option_size_t *self)
{
    {
        memset((&self->val), 0, sizeof(size_t));
    }
}

size_t Option_size_t__unwrap(Option_size_t *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        size_t v = self->val;
        memset((&self->val), 0, sizeof(size_t));
        return v;
    }
}

size_t *Option_size_t__unwrap_ref(Option_size_t *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

size_t Option_size_t__unwrap_or(Option_size_t *self, size_t def_val)
{
    {
        if (self->is_some)
        {
            return self->val;
        }
        return def_val;
    }
}

size_t Option_size_t__expect(Option_size_t *self, char *msg)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Option_size_t Option_size_t__or_else(Option_size_t *self, Option_size_t other)
{
    {
        if (self->is_some)
        {
            return (*self);
        }
        return other;
    }
}

Option_int32_t Option_int32_t__Some(int32_t v)
{
    {
        return (Option_int32_t){.is_some = true, .val = v};
    }
}

Option_int32_t Option_int32_t__None(void)
{
    {
        return (Option_int32_t){.is_some = false};
    }
}

bool Option_int32_t__is_some(Option_int32_t *self)
{
    {
        return self->is_some;
    }
}

bool Option_int32_t__is_none(Option_int32_t *self)
{
    {
        return (!self->is_some);
    }
}

void Option_int32_t__forget(Option_int32_t *self)
{
    {
        memset((&self->val), 0, sizeof(int32_t));
    }
}

int32_t Option_int32_t__unwrap(Option_int32_t *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        int32_t v = self->val;
        memset((&self->val), 0, sizeof(int32_t));
        return v;
    }
}

int32_t *Option_int32_t__unwrap_ref(Option_int32_t *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

int32_t Option_int32_t__unwrap_or(Option_int32_t *self, int32_t def_val)
{
    {
        if (self->is_some)
        {
            return self->val;
        }
        return def_val;
    }
}

int32_t Option_int32_t__expect(Option_int32_t *self, char *msg)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Option_int32_t Option_int32_t__or_else(Option_int32_t *self, Option_int32_t other)
{
    {
        if (self->is_some)
        {
            return (*self);
        }
        return other;
    }
}

Vec_char Vec_char__new(void)
{
    {
        return (Vec_char){};
    }
}

Vec_char Vec_char__with_capacity(size_t cap)
{
    {
        if ((cap == 0))
        {
            return (Vec_char){};
        }
        return (Vec_char){.data = ((char *)(malloc((cap * sizeof(char))))), .cap = cap};
    }
}

void Vec_char__grow(Vec_char *self)
{
    {
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        else
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((char *)(realloc(self->data, (self->cap * sizeof(char))))));
    }
}

void Vec_char__grow_to_fit(Vec_char *self, size_t new_len)
{
    {
        if ((self->cap >= new_len))
        {
            return;
        }
        if ((self->cap == 0))
        {
            (self->cap = 8);
        }
        while ((self->cap < new_len))
        {
            (self->cap = (self->cap * 2));
        }
        (self->data = ((char *)(realloc(self->data, (self->cap * sizeof(char))))));
    }
}

VecIter_char Vec_char__iterator(Vec_char *self)
{
    {
        return (VecIter_char){.data = self->data, .count = self->len};
    }
}

VecIterRef_char Vec_char__iter_ref(Vec_char *self)
{
    {
        return (VecIterRef_char){.data = self->data, .count = self->len};
    }
}

void Vec_char__push(Vec_char *self, char item)
{
    {
        if ((self->len >= self->cap))
        {
            Vec_char__grow(self);
        }
        (self->data[self->len] = item);
        (self->len = (self->len + 1));
    }
}

void Vec_char__insert(Vec_char *self, size_t idx, char item)
{
    {
        if ((idx > self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Insert index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        if ((self->len >= self->cap))
        {
            Vec_char__grow(self);
        }
        if ((idx < self->len))
        {
            memmove(((self->data + idx) + 1), (self->data + idx),
                    ((self->len - idx) * sizeof(char)));
        }
        (self->data[idx] = item);
        (self->len = (self->len + 1));
    }
}

char Vec_char__pop(Vec_char *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: pop called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->len = (self->len - 1));
        return self->data[self->len];
    }
}

Option_char Vec_char__pop_opt(Vec_char *self)
{
    {
        if ((self->len == 0))
        {
            return Option_char__None();
        }
        (self->len = (self->len - 1));
        return Option_char__Some(self->data[self->len]);
    }
}

char Vec_char__remove(Vec_char *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Remove index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        char item = self->data[idx];
        if ((idx < (self->len - 1)))
        {
            memmove((self->data + idx), ((self->data + idx) + 1),
                    (((self->len - idx) - 1) * sizeof(char)));
        }
        (self->len = (self->len - 1));
        return item;
    }
}

void Vec_char__append(Vec_char *self, Vec_char other)
{
    int __z_drop_flag_other = 1;
    {
        size_t new_len = (self->len + other.len);
        Vec_char__grow_to_fit(self, new_len);
        memcpy((self->data + self->len), other.data, (other.len * sizeof(char)));
        (self->len = new_len);
        Vec_char__forget(&other);
    }
    if (__z_drop_flag_other)
    {
        Vec_char__Drop_glue(&other);
    }
}

char Vec_char__get(Vec_char *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[idx];
    }
}

char Vec_char__index(Vec_char *self, size_t idx)
{
    {
        return Vec_char__get(self, idx);
    }
}

char *Vec_char__get_ref(Vec_char *self, size_t idx)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: Index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->data[idx]);
    }
}

char Vec_char__last(Vec_char *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: last called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[(self->len - 1)];
    }
}

size_t Vec_char__length(Vec_char *self)
{
    {
        return self->len;
    }
}

bool Vec_char__contains(Vec_char *self, char item)
{
    {
        size_t i = 0;
        while ((i < self->len))
        {
            if ((memcmp((&self->data[i]), (&item), sizeof(char)) == 0))
            {
                return true;
            }
            (i++);
        }
        return false;
    }
}

bool Vec_char__is_empty(Vec_char *self)
{
    {
        return (self->len == 0);
    }
}

void Vec_char__clear(Vec_char *self)
{
    {
        (self->len = 0);
    }
}

void Vec_char__free(Vec_char *self)
{
    {
        if (self->data)
        {
            free(self->data);
        }
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

char Vec_char__first(Vec_char *self)
{
    {
        if ((self->len == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: first called on empty Vec");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->data[0];
    }
}

void Vec_char__set(Vec_char *self, size_t idx, char item)
{
    {
        if ((idx >= self->len))
        {
            ({
                fprintf(stderr, "%s", "Panic: set index out of bounds");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        (self->data[idx] = item);
    }
}

void Vec_char__reverse(Vec_char *self)
{
    {
        size_t i = 0;
        size_t j = (self->len - 1);
        while ((i < j))
        {
            char tmp = self->data[i];
            (self->data[i] = self->data[j]);
            (self->data[j] = tmp);
            (i++);
            (j--);
        }
    }
}

bool Vec_char__eq(Vec_char *self, Vec_char *other)
{
    {
        bool result = true;
        if ((self->len != (*other).len))
        {
            (result = false);
        }
        else
        {
            size_t i = 0;
            while ((i < self->len))
            {
                if ((memcmp((&self->data[i]), (&(*other).data[i]), sizeof(char)) != 0))
                {
                    (result = false);
                    break;
                }
                (i = (i + 1));
            }
        }
        return result;
    }
}

void Vec_char__forget(Vec_char *self)
{
    {
        (self->data = 0);
        (self->len = 0);
        (self->cap = 0);
    }
}

Vec_char Vec_char__add(Vec_char *self, Vec_char *other)
{
    {
        int __z_drop_flag_result = 1;
        Vec_char result = Vec_char__clone(self);
        Vec_char__append(&result, Vec_char__clone(other));
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_char__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_char__Drop_glue(&result);
        }
    }
}

void Vec_char__add_assign(Vec_char *self, Vec_char *other)
{
    {
        Vec_char__append(self, Vec_char__clone(other));
    }
}

bool Vec_char__neq(Vec_char *self, Vec_char *other)
{
    {
        bool result = (!Vec_char__eq(self, other));
        return result;
    }
}

void Vec_char__shl(Vec_char *self, char item)
{
    {
        Vec_char__push(self, item);
    }
}

void Vec_char__shr(Vec_char *self, char *out_item)
{
    {
        if ((out_item != 0))
        {
            ((*out_item) = Vec_char__pop(self));
        }
        else
        {
            Vec_char__pop(self);
        }
    }
}

Vec_char Vec_char__mul(Vec_char *self, size_t count)
{
    {
        int __z_drop_flag_result = 1;
        Vec_char result = Vec_char__with_capacity((self->len * count));
        size_t c = 0;
        while ((c < count))
        {
            Vec_char__append(&result, Vec_char__clone(self));
            (c = (c + 1));
        }
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                Vec_char__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            Vec_char__Drop_glue(&result);
        }
    }
}

void Vec_char__mul_assign(Vec_char *self, size_t count)
{
    {
        if ((count == 0))
        {
            Vec_char__clear(self);
            return;
        }
        if ((count == 1))
        {
            return;
        }
        size_t original_len = self->len;
        Vec_char__grow_to_fit(self, (self->len * count));
        size_t c = 1;
        while ((c < count))
        {
            memcpy((self->data + (original_len * c)), self->data, (original_len * sizeof(char)));
            (self->len = (self->len + original_len));
            (c = (c + 1));
        }
    }
}

Vec_char Vec_char__clone(Vec_char *self)
{
    {
        if ((self->len == 0))
        {
            return (Vec_char){};
        }
        char *new_data = ((char *)(malloc((self->len * sizeof(char)))));
        size_t i = 0;
        while ((i < self->len))
        {
            (new_data[i] = self->data[i]);
            (i = (i + 1));
        }
        return (Vec_char){.data = new_data, .len = self->len, .cap = self->len};
    }
}

VecIterResult_char VecIterRef_char__next(VecIterRef_char *self)
{
    {
        if ((self->idx < self->count))
        {
            char *item = (&self->data[self->idx]);
            (self->idx = (self->idx + 1));
            return (VecIterResult_char){.ptr = item};
        }
        return (VecIterResult_char){};
    }
}

VecIterRef_char VecIterRef_char__iterator(VecIterRef_char *self)
{
    {
        return (*self);
    }
}

bool VecIterResult_char__is_none(VecIterResult_char *self)
{
    {
        return (self->ptr == 0);
    }
}

char *VecIterResult_char__unwrap(VecIterResult_char *self)
{
    {
        if ((self->ptr == 0))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on null VecIterResult");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->ptr;
    }
}

Option_char VecIter_char__next(VecIter_char *self)
{
    {
        if ((self->idx < self->count))
        {
            char item = self->data[self->idx];
            (self->idx = (self->idx + 1));
            return Option_char__Some(item);
        }
        return Option_char__None();
    }
}

VecIter_char VecIter_char__iterator(VecIter_char *self)
{
    {
        return (*self);
    }
}

Option_char Option_char__Some(char v)
{
    {
        return (Option_char){.is_some = true, .val = v};
    }
}

Option_char Option_char__None(void)
{
    {
        return (Option_char){.is_some = false};
    }
}

bool Option_char__is_some(Option_char *self)
{
    {
        return self->is_some;
    }
}

bool Option_char__is_none(Option_char *self)
{
    {
        return (!self->is_some);
    }
}

void Option_char__forget(Option_char *self)
{
    {
        memset((&self->val), 0, sizeof(char));
    }
}

char Option_char__unwrap(Option_char *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        char v = self->val;
        memset((&self->val), 0, sizeof(char));
        return v;
    }
}

char *Option_char__unwrap_ref(Option_char *self)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: unwrap_ref called on None");
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return (&self->val);
    }
}

char Option_char__unwrap_or(Option_char *self, char def_val)
{
    {
        if (self->is_some)
        {
            return self->val;
        }
        return def_val;
    }
}

char Option_char__expect(Option_char *self, char *msg)
{
    {
        if ((!self->is_some))
        {
            ({
                fprintf(stderr, "%s", "Panic: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
        return self->val;
    }
}

Option_char Option_char__or_else(Option_char *self, Option_char other)
{
    {
        if (self->is_some)
        {
            return (*self);
        }
        return other;
    }
}

void Vec_char__Drop_drop(Vec_char *self)
{
    {
        Vec_char__free(self);
    }
}

void handler(Request *_req, Response *res)
{
    {
        Response__set_body(res, String__new("Hello World"));
    }
}

void assert_true(bool cond, char *msg)
{
    {
        if ((!cond))
        {
            ({
                fprintf(stderr, "%s", "Assertion failed: ");
                fprintf(stderr, "%s", msg);
                fprintf(stderr, "\n");
                0;
            });
            exit(1);
        }
    }
}

void sleep_ms(int32_t ms)
{
    {
        int micros = ((int)((ms * 1000)));
        _z_usleep(micros);
    }
}

Response fetch(String url)
{
    int __z_drop_flag_url = 1;
    {
        Result_Url u_res = Url__parse(url);
        if (Result_Url__is_err((&u_res)))
        {
            ({
                fprintf(stdout, "%s", "Invalid URL: ");
                fprintf(stdout, "%s", u_res.err);
                fprintf(stdout, "\n");
                0;
            });
            {
                Response _z_ret = Response__new(0);
                if (__z_drop_flag_url)
                {
                    String__Drop_glue(&url);
                }
                return _z_ret;
            }
        }
        int __z_drop_flag_u = 1;
        Url u = Result_Url__unwrap((&u_res));
        if ((!String__eq_str((&u.scheme), "http")))
        {
            ({
                fprintf(stdout, "%s", "Only http:// supported");
                fprintf(stdout, "\n");
                0;
            });
            {
                Response _z_ret = Response__new(0);
                if (__z_drop_flag_u)
                {
                    Url__Drop_glue(&u);
                }
                if (__z_drop_flag_url)
                {
                    String__Drop_glue(&url);
                }
                return _z_ret;
            }
        }
        int __z_drop_flag_host_ip = 1;
        String host_ip = String__new(String__c_str((&u.host)));
        Result_String dns_res = Dns__resolve(String__c_str((&u.host)));
        if (Result_String__is_ok((&dns_res)))
        {
            String__free((&host_ip));
            (host_ip = Result_String__unwrap((&dns_res)));
        }
        char *ip_str = String__c_str((&host_ip));
        Result_TcpStream stream_res = TcpStream__connect(ip_str, u.port);
        if (Result_TcpStream__is_err((&stream_res)))
        {
            ({
                fprintf(stdout, "%s", "Failed to connect to ");
                fprintf(stdout, "%s", String__c_str((&u.host)));
                fprintf(stdout, "%s", ":");
                fprintf(stdout, "%d", u.port);
                fprintf(stdout, "%s", " (");
                fprintf(stdout, "%s", ip_str);
                fprintf(stdout, "%s", ")");
                fprintf(stdout, "\n");
                0;
            });
            {
                Response _z_ret = Response__new(0);
                if (__z_drop_flag_host_ip)
                {
                    String__Drop_glue(&host_ip);
                }
                if (__z_drop_flag_u)
                {
                    Url__Drop_glue(&u);
                }
                if (__z_drop_flag_url)
                {
                    String__Drop_glue(&url);
                }
                return _z_ret;
            }
        }
        int __z_drop_flag_stream = 1;
        TcpStream stream = Result_TcpStream__unwrap((&stream_res));
        int __z_drop_flag_req_line = 1;
        String req_line = String__new("GET ");
        String__append((&req_line), (&u.path));
        if ((!String__is_empty((&u.query))))
        {
            String__append_c((&req_line), "?");
            String__append((&req_line), (&u.query));
        }
        String__append_c((&req_line), " HTTP/1.1\r\nHost: ");
        String__append((&req_line), (&u.host));
        String__append_c((&req_line), "\r\nConnection: close\r\n\r\n");
        TcpStream__write((&stream), ((uint8_t *)(String__c_str((&req_line)))),
                         String__length((&req_line)));
        char buf[4096] = {0};
        Result_size_t n_res = TcpStream__read((&stream), (&buf[_z_check_bounds(0, 4096)]), 4096);
        if (Result_size_t__is_err((&n_res)))
        {
            TcpStream__close((&stream));
            {
                Response _z_ret = Response__new(0);
                if (__z_drop_flag_req_line)
                {
                    String__Drop_glue(&req_line);
                }
                if (__z_drop_flag_stream)
                {
                    TcpStream__Drop_glue(&stream);
                }
                if (__z_drop_flag_host_ip)
                {
                    String__Drop_glue(&host_ip);
                }
                if (__z_drop_flag_u)
                {
                    Url__Drop_glue(&u);
                }
                if (__z_drop_flag_url)
                {
                    String__Drop_glue(&url);
                }
                return _z_ret;
            }
        }
        size_t n = Result_size_t__unwrap((&n_res));
        if ((n == 0))
        {
            TcpStream__close((&stream));
            {
                Response _z_ret = Response__new(0);
                if (__z_drop_flag_req_line)
                {
                    String__Drop_glue(&req_line);
                }
                if (__z_drop_flag_stream)
                {
                    TcpStream__Drop_glue(&stream);
                }
                if (__z_drop_flag_host_ip)
                {
                    String__Drop_glue(&host_ip);
                }
                if (__z_drop_flag_u)
                {
                    Url__Drop_glue(&u);
                }
                if (__z_drop_flag_url)
                {
                    String__Drop_glue(&url);
                }
                return _z_ret;
            }
        }
        if ((n < 4096))
        {
            (buf[_z_check_bounds(n, 4096)] = 0);
        }
        else
        {
            (buf[_z_check_bounds(4095, 4096)] = 0);
        }
        int __z_drop_flag_raw_res = 1;
        String raw_res = String__new((&buf[_z_check_bounds(0, 4096)]));
        Option_size_t first_space = String__find((&raw_res), ' ');
        int32_t status = 0;
        if (Option_size_t__is_some((&first_space)))
        {
            size_t fs = Option_size_t__unwrap((&first_space));
            int __z_drop_flag_rest_line = 1;
            String rest_line =
                String__substring((&raw_res), (fs + 1), ((String__length((&raw_res)) - fs) - 1));
            Option_size_t second_space = String__find((&rest_line), ' ');
            if (Option_size_t__is_some((&second_space)))
            {
                size_t ss = Option_size_t__unwrap((&second_space));
                int __z_drop_flag_code_str = 1;
                String code_str = String__substring((&rest_line), 0, ss);
                (status = atoi(String__c_str((&code_str))));
                if (__z_drop_flag_code_str)
                {
                    String__Drop_glue(&code_str);
                }
            }
            else
            {
                (status = atoi(String__c_str((&rest_line))));
            }
            if (__z_drop_flag_rest_line)
            {
                String__Drop_glue(&rest_line);
            }
        }
        int __z_drop_flag_res = 1;
        Response res = Response__new(status);
        string body_sep = "\r\n\r\n";
        char *body_ptr = strstr(String__c_str((&raw_res)), body_sep);
        if ((body_ptr != NULL))
        {
            size_t body_offset = ((size_t)((body_ptr - String__c_str((&raw_res)))));
            size_t body_start = (body_offset + 4);
            int __z_drop_flag_body_content = 1;
            String body_content = String__substring((&raw_res), body_start,
                                                    (String__length((&raw_res)) - body_start));
            Response__set_body((&res), body_content);
            if (__z_drop_flag_body_content)
            {
                String__Drop_glue(&body_content);
            }
        }
        TcpStream__close((&stream));
        return ({
            ZC_AUTO _z_ret_mv = res;
            memset(&res, 0, sizeof(_z_ret_mv));
            __z_drop_flag_res = 0;
            if (__z_drop_flag_res)
            {
                Response__Drop_glue(&res);
            }
            if (__z_drop_flag_raw_res)
            {
                String__Drop_glue(&raw_res);
            }
            if (__z_drop_flag_req_line)
            {
                String__Drop_glue(&req_line);
            }
            if (__z_drop_flag_stream)
            {
                TcpStream__Drop_glue(&stream);
            }
            if (__z_drop_flag_host_ip)
            {
                String__Drop_glue(&host_ip);
            }
            if (__z_drop_flag_u)
            {
                Url__Drop_glue(&u);
            }
            if (__z_drop_flag_url)
            {
                String__Drop_glue(&url);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_res)
        {
            Response__Drop_glue(&res);
        }
        if (__z_drop_flag_raw_res)
        {
            String__Drop_glue(&raw_res);
        }
        if (__z_drop_flag_req_line)
        {
            String__Drop_glue(&req_line);
        }
        if (__z_drop_flag_stream)
        {
            TcpStream__Drop_glue(&stream);
        }
        if (__z_drop_flag_host_ip)
        {
            String__Drop_glue(&host_ip);
        }
        if (__z_drop_flag_u)
        {
            Url__Drop_glue(&u);
        }
    }
    if (__z_drop_flag_url)
    {
        String__Drop_glue(&url);
    }
}

Vec_Header _parse_headers(Vec_String lines, size_t start_idx)
{
    int __z_drop_flag_lines = 1;
    {
        int __z_drop_flag_headers = 1;
        Vec_Header headers = Vec_Header__new();
        size_t len = lines.len;
        for (size_t i = (size_t)(start_idx); i < len; i = (i + 1))
        {
            String *line = Vec_String__get_ref((&lines), i);
            if (String__is_empty(line))
            {
                break;
            }
            int __z_drop_flag_parts = 1;
            Vec_String parts = String__split(line, ':');
            if ((parts.len >= 2))
            {
                String *key = Vec_String__get_ref((&parts), 0);
                String *val = Vec_String__get_ref((&parts), 1);
                int __z_drop_flag_key_t = 1;
                String key_t = String__trim(key);
                int __z_drop_flag_val_t = 1;
                String val_t = String__trim(val);
                Vec_Header__push((&headers), (struct Header){.key = key_t, .value = val_t});
                if (__z_drop_flag_val_t)
                {
                    String__Drop_glue(&val_t);
                }
                if (__z_drop_flag_key_t)
                {
                    String__Drop_glue(&key_t);
                }
            }
            if (__z_drop_flag_parts)
            {
                Vec_String__Drop_glue(&parts);
            }
        }
        return ({
            ZC_AUTO _z_ret_mv = headers;
            memset(&headers, 0, sizeof(_z_ret_mv));
            __z_drop_flag_headers = 0;
            if (__z_drop_flag_headers)
            {
                Vec_Header__Drop_glue(&headers);
            }
            if (__z_drop_flag_lines)
            {
                Vec_String__Drop_glue(&lines);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_headers)
        {
            Vec_Header__Drop_glue(&headers);
        }
    }
    if (__z_drop_flag_lines)
    {
        Vec_String__Drop_glue(&lines);
    }
}

size_t _map_hash_str(const char *str)
{
    {
        size_t hash = hash_get_seed();
        size_t i = 0;
        while ((str[i] != 0))
        {
            uint8_t b = ((uint8_t)(str[i]));
            (hash = hash_combine(hash, ((size_t)(b))));
            (i = (i + 1));
        }
        return hash;
    }
}

inline size_t hash_get_seed(void)
{
    {
        return __zen_hash_seed;
    }
}

void hash_set_seed(size_t seed)
{
    {
        (__zen_hash_seed = seed);
    }
}

size_t hash_compute(const void *data, size_t len)
{
    {
        size_t hash = __zen_hash_seed;
        uint8_t *bytes = ((uint8_t *)(data));
        for (size_t i = (size_t)(0); i < len; i = (i + 1))
        {
            (hash = hash_combine(hash, ((size_t)(bytes[i]))));
        }
        return hash;
    }
}

inline size_t hash_combine(size_t a, size_t b)
{
    {
        (a = (a ^ b));
        (a = (a * 435));
        return a;
    }
}

void _zen_panic(const char *file, int32_t line, const char *func, const char *msg)
{
    {
        fprintf(stderr, "%s:%d (%s): Panic: %s\n", file, line, func, msg);
        exit(1);
    }
}

void Mutex__Drop_drop(Mutex *self)
{
    {
        Mutex__free(self);
    }
}

Mutex Mutex__new(void)
{
    {
        void *ptr = malloc(64);
        _z_mutex_init(ptr);
        return (struct Mutex){.handle = ptr};
    }
}

void Mutex__lock(Mutex *self)
{
    {
        _z_mutex_lock(self->handle);
    }
}

void Mutex__unlock(Mutex *self)
{
    {
        _z_mutex_unlock(self->handle);
    }
}

void Mutex__free(Mutex *self)
{
    {
        if (self->handle)
        {
            _z_mutex_destroy(self->handle);
            free(self->handle);
            (self->handle = NULL);
        }
    }
}

bool Thread__eq(Thread *self, const Thread other)
{
    {
        return _z_thread_equal(self->handle, other.handle);
    }
}

bool Thread__neq(Thread *self, const Thread other)
{
    {
        return (!Thread__eq(self, other));
    }
}

Result_Thread Thread__spawn(z_closure_T func)
{
    int __z_drop_flag_func = 1;
    {
        size_t out_handle = 0;
        void *ctx = malloc(sizeof(z_closure_T));
        if ((ctx == NULL))
        {
            {
                Result_Thread _z_ret = Result_Thread__Err("OOM");
                if (__z_drop_flag_func && func.drop)
                {
                    func.drop(func.ctx);
                }
                return _z_ret;
            }
        }
        memcpy(ctx, (&func), sizeof(z_closure_T));

        ((z_closure_T *)&func)->drop = NULL;

        int ret = _z_thread_spawn(ctx, (&out_handle));
        if ((ret != 0))
        {
            free(ctx);
            {
                Result_Thread _z_ret = Result_Thread__Err("Failed to create thread");
                if (__z_drop_flag_func && func.drop)
                {
                    func.drop(func.ctx);
                }
                return _z_ret;
            }
        }
        {
            Result_Thread _z_ret =
                Result_Thread__Ok((struct Thread){.handle = ((void *)(out_handle))});
            if (__z_drop_flag_func && func.drop)
            {
                func.drop(func.ctx);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_func && func.drop)
    {
        func.drop(func.ctx);
    }
}

Result_bool Thread__join(Thread *self)
{
    {
        int err = _z_thread_join(self->handle);
        if (err)
        {
            return Result_bool__Err("Join failed");
        }
        return Result_bool__Ok(true);
    }
}

Result_bool Thread__detach(Thread *self)
{
    {
        int err = _z_thread_detach(self->handle);
        if (err)
        {
            return Result_bool__Err("Detach failed");
        }
        return Result_bool__Ok(true);
    }
}

Result_bool Thread__cancel(Thread *self)
{
    {
        int err = _z_thread_cancel(self->handle);
        if (err)
        {
            return Result_bool__Err("Cancel failed");
        }
        return Result_bool__Ok(true);
    }
}

Result_String Dns__resolve(char *host)
{
    {
        char buf[64] = {0};
        int32_t res = _z_dns_resolve(host, (&buf[_z_check_bounds(0, 64)]), 64);
        if ((res != 0))
        {
            return Result_String__Err("DNS resolution failed");
        }
        return Result_String__Ok(String__new((&buf[_z_check_bounds(0, 64)])));
    }
}

Result_Url Url__parse(String raw)
{
    int __z_drop_flag_raw = 1;
    {
        char *u_str = String__c_str((&raw));
        char *scheme_end = strstr(u_str, "://");
        if ((scheme_end == NULL))
        {
            {
                Result_Url _z_ret = Result_Url__Err("Missing scheme");
                if (__z_drop_flag_raw)
                {
                    String__Drop_glue(&raw);
                }
                return _z_ret;
            }
        }
        size_t scheme_len = ((size_t)((scheme_end - u_str)));
        int __z_drop_flag_scheme = 1;
        String scheme = String__substring((&raw), 0, scheme_len);
        char *rest = (scheme_end + 3);
        int32_t default_port = 80;
        if (String__eq_str((&scheme), "https"))
        {
            (default_port = 443);
        }
        ZC_AUTO host_end_slash = strchr(rest, '/');
        ZC_AUTO host_end_q = strchr(rest, '?');
        ZC_AUTO host_end = host_end_slash;
        if ((host_end == NULL))
        {
            (host_end = host_end_q);
        }
        else if (((host_end_q != NULL) && (host_end_q < host_end)))
        {
            (host_end = host_end_q);
        }
        size_t host_len = 0;
        if ((host_end == NULL))
        {
            (host_len = strlen(rest));
        }
        else
        {
            (host_len = ((size_t)((host_end - rest))));
        }
        char *host_port_buf = ((char *)(malloc((host_len + 1))));
        strncpy(host_port_buf, rest, host_len);
        (host_port_buf[host_len] = 0);
        int __z_drop_flag_host_str = 1;
        String host_str = String__new(host_port_buf);
        free(host_port_buf);
        int32_t port = default_port;
        int __z_drop_flag_final_host = 1;
        String final_host = String__new("");
        int __z_drop_flag_parts = 1;
        Vec_String parts = String__split((&host_str), ':');
        if ((parts.len == 2))
        {
            (final_host = String__trim(
                 (__typeof__((Vec_String__get((&parts), 0)))[]){Vec_String__get((&parts), 0)}));
            int __z_drop_flag_p_str = 1;
            String p_str = Vec_String__get((&parts), 1);
            (port = atoi(String__c_str((&p_str))));
            if (__z_drop_flag_p_str)
            {
                String__Drop_glue(&p_str);
            }
        }
        else
        {
            (final_host = String__new(String__c_str((&host_str))));
        }
        String__free((&host_str));
        int __z_drop_flag_path = 1;
        String path = String__new("/");
        int __z_drop_flag_query = 1;
        String query = String__new("");
        if ((host_end != NULL))
        {
            if (((*host_end) == '/'))
            {
                int __z_drop_flag_remaining = 1;
                String remaining = String__new(host_end);
                Option_size_t q_pos = String__find((&remaining), '?');
                if (Option_size_t__is_some((&q_pos)))
                {
                    size_t q_idx = Option_size_t__unwrap((&q_pos));
                    String__free((&path));
                    (path = String__substring((&remaining), 0, q_idx));
                    String__free((&query));
                    (query = String__substring((&remaining), (q_idx + 1),
                                               ((String__length((&remaining)) - q_idx) - 1)));
                }
                else
                {
                    String__free((&path));
                    (path = String__substring((&remaining), 0, String__length((&remaining))));
                }
                String__free((&remaining));
                if (__z_drop_flag_remaining)
                {
                    String__Drop_glue(&remaining);
                }
            }
            else if (((*host_end) == '?'))
            {
                String__free((&query));
                (query = String__new((host_end + 1)));
            }
        }
        {
            Result_Url _z_ret = Result_Url__Ok((struct Url){
                .scheme = scheme, .host = final_host, .port = port, .path = path, .query = query});
            if (__z_drop_flag_query)
            {
                String__Drop_glue(&query);
            }
            if (__z_drop_flag_path)
            {
                String__Drop_glue(&path);
            }
            if (__z_drop_flag_parts)
            {
                Vec_String__Drop_glue(&parts);
            }
            if (__z_drop_flag_final_host)
            {
                String__Drop_glue(&final_host);
            }
            if (__z_drop_flag_host_str)
            {
                String__Drop_glue(&host_str);
            }
            if (__z_drop_flag_scheme)
            {
                String__Drop_glue(&scheme);
            }
            if (__z_drop_flag_raw)
            {
                String__Drop_glue(&raw);
            }
            return _z_ret;
        }
        if (__z_drop_flag_query)
        {
            String__Drop_glue(&query);
        }
        if (__z_drop_flag_path)
        {
            String__Drop_glue(&path);
        }
        if (__z_drop_flag_parts)
        {
            Vec_String__Drop_glue(&parts);
        }
        if (__z_drop_flag_final_host)
        {
            String__Drop_glue(&final_host);
        }
        if (__z_drop_flag_host_str)
        {
            String__Drop_glue(&host_str);
        }
        if (__z_drop_flag_scheme)
        {
            String__Drop_glue(&scheme);
        }
    }
    if (__z_drop_flag_raw)
    {
        String__Drop_glue(&raw);
    }
}

void Url__destroy(Url *self)
{
    {
        String__free((&self->scheme));
        String__free((&self->host));
        String__free((&self->path));
        String__free((&self->query));
    }
}

Server Server__new(int32_t port, void (*handler)(Request *, Response *))
{
    {
        return (struct Server){.port = port, .handler = ((void *)(handler))};
    }
}

void Server__start(Server *self)
{
    {
        string host = "0.0.0.0";
        Result_TcpListener listener_res = TcpListener__bind(host, self->port);
        if (Result_TcpListener__is_err((&listener_res)))
        {
            ({
                fprintf(stdout, "%s", "Failed to bind port ");
                fprintf(stdout, "%d", self->port);
                fprintf(stdout, "\n");
                0;
            });
            return;
        }
        int __z_drop_flag_listener = 1;
        TcpListener listener = Result_TcpListener__unwrap((&listener_res));
        ({
            fprintf(stdout, "%s", "Server listening on port ");
            fprintf(stdout, "%d", self->port);
            fprintf(stdout, "\n");
            0;
        });
        while (true)
        {
            Result_TcpStream client_res = TcpListener__accept((&listener));
            if (Result_TcpStream__is_err((&client_res)))
            {
                continue;
            }
            int __z_drop_flag_client = 1;
            TcpStream client = Result_TcpStream__unwrap((&client_res));
            char buf[4096] = {0};
            Result_size_t read_res =
                TcpStream__read((&client), (&buf[_z_check_bounds(0, 4096)]), 4096);
            if (Result_size_t__is_ok((&read_res)))
            {
                size_t bytes_read = Result_size_t__unwrap((&read_res));
                if ((bytes_read > 0))
                {
                    if ((bytes_read < 4096))
                    {
                        (buf[_z_check_bounds(bytes_read, 4096)] = 0);
                    }
                    else
                    {
                        (buf[_z_check_bounds(4095, 4096)] = 0);
                    }
                    int __z_drop_flag_req_str = 1;
                    String req_str = String__new((&buf[_z_check_bounds(0, 4096)]));
                    int __z_drop_flag_lines = 1;
                    Vec_String lines = String__split((&req_str), '\n');
                    if ((lines.len > 0))
                    {
                        String *first_line = Vec_String__get_ref((&lines), 0);
                        int __z_drop_flag_fl_parts = 1;
                        Vec_String fl_parts = String__split(first_line, ' ');
                        if ((fl_parts.len >= 2))
                        {
                            int __z_drop_flag_method = 1;
                            String method = String__trim(Vec_String__get_ref((&fl_parts), 0));
                            int __z_drop_flag_path = 1;
                            String path = String__trim(Vec_String__get_ref((&fl_parts), 1));
                            int __z_drop_flag_req = 1;
                            Request req = Request__new(method, path);
                            int __z_drop_flag_res = 1;
                            Response res = Response__new(200);
                            void (*h_func)(Request *, Response *) = self->handler;
                            h_func((&req), (&res));
                            int __z_drop_flag_response_str = 1;
                            String response_str = String__new("HTTP/1.1 ");
                            if ((res.status == 200))
                            {
                                String__append_c((&response_str), "200 OK\r\n");
                            }
                            else if ((res.status == 404))
                            {
                                String__append_c((&response_str), "404 Not Found\r\n");
                            }
                            else
                            {
                                String__append_c((&response_str), "500 Internal Server Error\r\n");
                            }
                            for (int i = (int)(0); i < res.headers.len; i = (i + 1))
                            {
                                Header *header = Vec_Header__get_ref((&res.headers), i);
                                String__append((&response_str), (&header->key));
                                String__append_c((&response_str), ": ");
                                String__append((&response_str), (&header->value));
                                String__append_c((&response_str), "\r\n");
                            }
                            String__append_c((&response_str), "Content-Length: ");
                            char len_buf[32] = {0};
                            size_t _body_len = String__length((&res.body));

                            snprintf(len_buf, 32, "%zu", _body_len);

                            String__append_c((&response_str), (&len_buf[_z_check_bounds(0, 32)]));
                            String__append_c((&response_str), "\r\n");
                            String__append_c((&response_str), "\r\n");
                            String__append((&response_str), (&res.body));
                            TcpStream__write((&client),
                                             ((uint8_t *)(String__c_str((&response_str)))),
                                             String__length((&response_str)));
                            if (__z_drop_flag_response_str)
                            {
                                String__Drop_glue(&response_str);
                            }
                            if (__z_drop_flag_res)
                            {
                                Response__Drop_glue(&res);
                            }
                            if (__z_drop_flag_req)
                            {
                                Request__Drop_glue(&req);
                            }
                            if (__z_drop_flag_path)
                            {
                                String__Drop_glue(&path);
                            }
                            if (__z_drop_flag_method)
                            {
                                String__Drop_glue(&method);
                            }
                        }
                        if (__z_drop_flag_fl_parts)
                        {
                            Vec_String__Drop_glue(&fl_parts);
                        }
                    }
                    if (__z_drop_flag_lines)
                    {
                        Vec_String__Drop_glue(&lines);
                    }
                    if (__z_drop_flag_req_str)
                    {
                        String__Drop_glue(&req_str);
                    }
                }
            }
            TcpStream__close((&client));
            if (__z_drop_flag_client)
            {
                TcpStream__Drop_glue(&client);
            }
        }
        if (__z_drop_flag_listener)
        {
            TcpListener__Drop_glue(&listener);
        }
    }
}

Response Response__new(int32_t status)
{
    {
        return (struct Response){
            .status = status, .headers = Vec_Header__new(), .body = String__new("")};
    }
}

void Response__set_header(Response *self, String key, String value)
{
    int __z_drop_flag_key = 1;
    int __z_drop_flag_value = 1;
    {
        int __z_drop_flag_h = 1;
        Header h = (struct Header){.key = key, .value = value};
        Vec_Header__push((&self->headers), h);
        if (__z_drop_flag_h)
        {
            Header__Drop_glue(&h);
        }
    }
    if (__z_drop_flag_value)
    {
        String__Drop_glue(&value);
    }
    if (__z_drop_flag_key)
    {
        String__Drop_glue(&key);
    }
}

void Response__set_header_str(Response *self, char *key, char *value)
{
    {
        Vec_Header__push((&self->headers),
                         (struct Header){.key = String__new(key), .value = String__new(value)});
    }
}

void Response__set_body(Response *self, String body)
{
    int __z_drop_flag_body = 1;
    {
        String__free((&self->body));
        (self->body = body);
    }
    if (__z_drop_flag_body)
    {
        String__Drop_glue(&body);
    }
}

void Response__set_body_str(Response *self, char *body)
{
    {
        String__free((&self->body));
        (self->body = String__new(body));
    }
}

Request Request__new(String method, String path)
{
    int __z_drop_flag_method = 1;
    int __z_drop_flag_path = 1;
    {
        {
            Request _z_ret = (struct Request){.method = method,
                                              .path = path,
                                              .headers = Vec_Header__new(),
                                              .body = String__new("")};
            if (__z_drop_flag_path)
            {
                String__Drop_glue(&path);
            }
            if (__z_drop_flag_method)
            {
                String__Drop_glue(&method);
            }
            return _z_ret;
        }
    }
    if (__z_drop_flag_path)
    {
        String__Drop_glue(&path);
    }
    if (__z_drop_flag_method)
    {
        String__Drop_glue(&method);
    }
}

void TcpListener__Drop_drop(TcpListener *self)
{
    {
        TcpListener__close(self);
    }
}

Result_TcpListener TcpListener__bind(char *host, int port)
{
    {
        ptrdiff_t fd = _z_socket(2, 1, 0);
        if ((fd < 0))
        {
            return Result_TcpListener__Err("Failed to create socket");
        }
        int res = _z_net_bind(fd, host, port);
        if ((res == (-1)))
        {
            _z_close(fd);
            return Result_TcpListener__Err("Invalid address");
        }
        if ((res == (-2)))
        {
            _z_close(fd);
            return Result_TcpListener__Err("Bind failed");
        }
        if ((res == (-3)))
        {
            _z_close(fd);
            return Result_TcpListener__Err("Listen failed");
        }
        return Result_TcpListener__Ok((struct TcpListener){.handle = (fd + 1)});
    }
}

Result_TcpStream TcpListener__accept(TcpListener *self)
{
    {
        ptrdiff_t client_fd = _z_net_accept((self->handle - 1));
        if ((client_fd < 0))
        {
            return Result_TcpStream__Err("Accept failed");
        }
        return Result_TcpStream__Ok((struct TcpStream){.handle = (client_fd + 1)});
    }
}

void TcpListener__close(TcpListener *self)
{
    {
        if ((self->handle > 0))
        {
            _z_close((self->handle - 1));
            (self->handle = 0);
        }
    }
}

void TcpStream__Drop_drop(TcpStream *self)
{
    {
        TcpStream__close(self);
    }
}

Result_size_t TcpStream__read(TcpStream *self, char *buf, size_t len)
{
    {
        ptrdiff_t n = _z_read((self->handle - 1), ((void *)(buf)), len);
        if ((n < 0))
        {
            return Result_size_t__Err(strerror(errno));
        }
        return Result_size_t__Ok(((size_t)(n)));
    }
}

Result_size_t TcpStream__read_exact(TcpStream *self, char *buf, size_t len)
{
    {
        size_t total_read = 0;
        while ((total_read < len))
        {
            Result_size_t res = TcpStream__read(self, (buf + total_read), (len - total_read));
            if (Result_size_t__is_err((&res)))
            {
                return res;
            }
            size_t n = Result_size_t__unwrap((&res));
            if ((n == 0))
            {
                return Result_size_t__Err("Unexpected EOF");
            }
            (total_read = (total_read + n));
        }
        return Result_size_t__Ok(total_read);
    }
}

Result_size_t TcpStream__write(TcpStream *self, uint8_t *buf, size_t len)
{
    {
        ptrdiff_t n = _z_net_write((self->handle - 1), ((char *)(buf)), len);
        if ((n < 0))
        {
            return Result_size_t__Err("Write failed");
        }
        return Result_size_t__Ok(((size_t)(n)));
    }
}

void TcpStream__close(TcpStream *self)
{
    {
        if ((self->handle > 0))
        {
            _z_close((self->handle - 1));
            (self->handle = 0);
        }
    }
}

Result_TcpStream TcpStream__connect(char *host, int port)
{
    {
        ptrdiff_t fd = _z_socket(2, 1, 0);
        if ((fd < 0))
        {
            return Result_TcpStream__Err("Failed to create socket");
        }
        int res = _z_net_connect(fd, host, port);
        if ((res == (-1)))
        {
            _z_close(fd);
            return Result_TcpStream__Err("Invalid address");
        }
        if ((res == (-2)))
        {
            _z_close(fd);
            return Result_TcpStream__Err("Connection failed");
        }
        return Result_TcpStream__Ok((struct TcpStream){.handle = (fd + 1)});
    }
}

String String__new(char *s)
{
    {
        ZC_AUTO len = strlen(s);
        int __z_drop_flag_v = 1;
        Vec_char v = Vec_char__new();
        for (int i = (int)(0); i < len; i = (i + 1))
        {
            Vec_char__push((&v), s[i]);
        }
        Vec_char__push((&v), 0);
        char *d = v.data;
        size_t l = v.len;
        size_t c = v.cap;
        Vec_char__forget((&v));
        {
            String _z_ret = (struct String){.vec = (Vec_char){.data = d, .len = l, .cap = c}};
            if (__z_drop_flag_v)
            {
                Vec_char__Drop_glue(&v);
            }
            return _z_ret;
        }
        if (__z_drop_flag_v)
        {
            Vec_char__Drop_glue(&v);
        }
    }
}

String String__from(char *s)
{
    {
        return String__new(s);
    }
}

String String__from_rune(int32_t r)
{
    {
        int __z_drop_flag_s = 1;
        String s = String__new("");
        String__push_rune(&s, r);
        return ({
            ZC_AUTO _z_ret_mv = s;
            memset(&s, 0, sizeof(_z_ret_mv));
            __z_drop_flag_s = 0;
            if (__z_drop_flag_s)
            {
                String__Drop_glue(&s);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_s)
        {
            String__Drop_glue(&s);
        }
    }
}

String String__from_runes(int32_t *runes, size_t count)
{
    {
        int __z_drop_flag_s = 1;
        String s = String__new("");
        for (size_t i = (size_t)(0); i < count; i = (i + 1))
        {
            String__push_rune(&s, runes[i]);
        }
        return ({
            ZC_AUTO _z_ret_mv = s;
            memset(&s, 0, sizeof(_z_ret_mv));
            __z_drop_flag_s = 0;
            if (__z_drop_flag_s)
            {
                String__Drop_glue(&s);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_s)
        {
            String__Drop_glue(&s);
        }
    }
}

char *String__c_str(String *self)
{
    {
        return self->vec.data;
    }
}

char *String__to_string(String *self)
{
    {
        return String__c_str(self);
    }
}

void String__destroy(String *self)
{
    {
        Vec_char__free((&self->vec));
    }
}

void String__forget(String *self)
{
    {
        Vec_char__forget((&self->vec));
    }
}

void String__append(String *self, String *other)
{
    {
        if ((self->vec.len > 0))
        {
            (self->vec.len = (self->vec.len - 1));
        }
        size_t other_len = (*other).vec.len;
        for (int i = (int)(0); i < other_len; i = (i + 1))
        {
            Vec_char__push((&self->vec), Vec_char__get((&(*other).vec), i));
        }
    }
}

void String__append_c(String *self, char *s)
{
    {
        if ((self->vec.len > 0))
        {
            (self->vec.len = (self->vec.len - 1));
        }
        ZC_AUTO len = strlen(s);
        for (int i = (int)(0); i < len; i = (i + 1))
        {
            Vec_char__push((&self->vec), s[i]);
        }
        Vec_char__push((&self->vec), 0);
    }
}

void String__push_rune(String *self, int32_t r)
{
    {
        if ((self->vec.len > 0))
        {
            (self->vec.len = (self->vec.len - 1));
        }
        uint32_t val = ((uint32_t)(r));
        if ((val < 128))
        {
            Vec_char__push((&self->vec), ((char)(val)));
        }
        else if ((val < 2048))
        {
            Vec_char__push((&self->vec), ((char)((192 | (val >> 6)))));
            Vec_char__push((&self->vec), ((char)((128 | (val & 63)))));
        }
        else if ((val < 65536))
        {
            Vec_char__push((&self->vec), ((char)((224 | (val >> 12)))));
            Vec_char__push((&self->vec), ((char)((128 | ((val >> 6) & 63)))));
            Vec_char__push((&self->vec), ((char)((128 | (val & 63)))));
        }
        else
        {
            Vec_char__push((&self->vec), ((char)((240 | (val >> 18)))));
            Vec_char__push((&self->vec), ((char)((128 | ((val >> 12) & 63)))));
            Vec_char__push((&self->vec), ((char)((128 | ((val >> 6) & 63)))));
            Vec_char__push((&self->vec), ((char)((128 | (val & 63)))));
        }
        Vec_char__push((&self->vec), 0);
    }
}

void String__append_c_ptr(String *ptr, char *s)
{
    {
        if ((ptr->vec.len > 0))
        {
            (ptr->vec.len = (ptr->vec.len - 1));
        }
        ZC_AUTO len = strlen(s);
        for (int i = (int)(0); i < len; i = (i + 1))
        {
            Vec_char__push((&ptr->vec), s[i]);
        }
        Vec_char__push((&ptr->vec), 0);
    }
}

String String__add(String *self, String *other)
{
    {
        int __z_drop_flag_new_s = 1;
        String new_s = String__from(String__c_str(self));
        String__append((&new_s), other);
        char *d = new_s.vec.data;
        size_t l = new_s.vec.len;
        size_t c = new_s.vec.cap;
        String__forget((&new_s));
        {
            String _z_ret = (struct String){.vec = (Vec_char){.data = d, .len = l, .cap = c}};
            if (__z_drop_flag_new_s)
            {
                String__Drop_glue(&new_s);
            }
            return _z_ret;
        }
        if (__z_drop_flag_new_s)
        {
            String__Drop_glue(&new_s);
        }
    }
}

void String__add_assign(String *self, String *other)
{
    {
        String__append(self, other);
    }
}

bool String__eq(String *self, String *other)
{
    {
        int zero = 0;
        return (strcmp(String__c_str(self), String__c_str((&(*other)))) == zero);
    }
}

bool String__neq(String *self, String *other)
{
    {
        return (!String__eq(self, other));
    }
}

int32_t String__compare(String *self, String *other)
{
    {
        return strcmp(String__c_str(self), String__c_str((&(*other))));
    }
}

bool String__lt(String *self, String *other)
{
    {
        return (String__compare(self, other) < 0);
    }
}

bool String__gt(String *self, String *other)
{
    {
        return (String__compare(self, other) > 0);
    }
}

bool String__le(String *self, String *other)
{
    {
        return (String__compare(self, other) <= 0);
    }
}

bool String__ge(String *self, String *other)
{
    {
        return (String__compare(self, other) >= 0);
    }
}

int32_t String__compare_ignore_case(String *self, String *other)
{
    {
        return strcasecmp(String__c_str(self), String__c_str((&(*other))));
    }
}

bool String__eq_ignore_case(String *self, String *other)
{
    {
        int32_t zero = 0;
        return (String__compare_ignore_case(self, other) == zero);
    }
}

bool String__eq_str(String *self, char *s)
{
    {
        int zero = 0;
        return (strcmp(String__c_str(self), s) == zero);
    }
}

size_t String__length(String *self)
{
    {
        if ((self->vec.len == 0))
        {
            return 0;
        }
        return (self->vec.len - 1);
    }
}

String String__substring(String *self, size_t start, size_t len)
{
    {
        if (((start + len) > String__length(self)))
        {
            panic("substring out of bounds");
        }
        int __z_drop_flag_v = 1;
        Vec_char v = Vec_char__new();
        for (size_t i = (size_t)(0); i < len; i = (i + 1))
        {
            Vec_char__push((&v), Vec_char__get((&self->vec), (start + i)));
        }
        Vec_char__push((&v), 0);
        char *d = v.data;
        size_t l = v.len;
        size_t c = v.cap;
        Vec_char__forget((&v));
        {
            String _z_ret = (struct String){.vec = (Vec_char){.data = d, .len = l, .cap = c}};
            if (__z_drop_flag_v)
            {
                Vec_char__Drop_glue(&v);
            }
            return _z_ret;
        }
        if (__z_drop_flag_v)
        {
            Vec_char__Drop_glue(&v);
        }
    }
}

bool String__contains_str(String *self, char *target)
{
    {
        return Option_size_t__is_some((Option_size_t[]){String__find_str(self, target)});
    }
}

Option_size_t String__find_str(String *self, char *target)
{
    {
        ZC_AUTO t_len = strlen(target);
        if ((t_len == 0))
        {
            return Option_size_t__Some(0);
        }
        size_t s_len = String__length(self);
        if ((t_len > s_len))
        {
            return Option_size_t__None();
        }
        for (size_t i = (size_t)(0); i <= (s_len - t_len); i = (i + 1))
        {
            bool is_match = true;
            for (size_t k = (size_t)(0); k < t_len; k = (k + 1))
            {
                if ((Vec_char__get((&self->vec), (i + k)) != target[k]))
                {
                    (is_match = false);
                    break;
                }
            }
            if (is_match)
            {
                return Option_size_t__Some(i);
            }
        }
        return Option_size_t__None();
    }
}

Vec_size_t String__find_all_str(String *self, char *target)
{
    {
        int __z_drop_flag_indices = 1;
        Vec_size_t indices = Vec_size_t__new();
        ZC_AUTO t_len = strlen(target);
        if ((t_len == 0))
        {
            return ({
                ZC_AUTO _z_ret_mv = indices;
                memset(&indices, 0, sizeof(_z_ret_mv));
                __z_drop_flag_indices = 0;
                if (__z_drop_flag_indices)
                {
                    Vec_size_t__Drop_glue(&indices);
                }
                _z_ret_mv;
            });
        }
        size_t s_len = String__length(self);
        if ((t_len > s_len))
        {
            return ({
                ZC_AUTO _z_ret_mv = indices;
                memset(&indices, 0, sizeof(_z_ret_mv));
                __z_drop_flag_indices = 0;
                if (__z_drop_flag_indices)
                {
                    Vec_size_t__Drop_glue(&indices);
                }
                _z_ret_mv;
            });
        }
        for (size_t i = (size_t)(0); i <= (s_len - t_len); i = (i + 1))
        {
            bool is_match = true;
            for (size_t k = (size_t)(0); k < t_len; k = (k + 1))
            {
                if ((Vec_char__get((&self->vec), (i + k)) != target[k]))
                {
                    (is_match = false);
                    break;
                }
            }
            if (is_match)
            {
                Vec_size_t__push((&indices), i);
            }
        }
        return ({
            ZC_AUTO _z_ret_mv = indices;
            memset(&indices, 0, sizeof(_z_ret_mv));
            __z_drop_flag_indices = 0;
            if (__z_drop_flag_indices)
            {
                Vec_size_t__Drop_glue(&indices);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_indices)
        {
            Vec_size_t__Drop_glue(&indices);
        }
    }
}

String String__to_lowercase(String *self)
{
    {
        size_t len = String__length(self);
        int __z_drop_flag_v = 1;
        Vec_char v = Vec_char__new();
        for (size_t i = (size_t)(0); i < len; i = (i + 1))
        {
            char c = Vec_char__get((&self->vec), i);
            if (((c >= 'A') && (c <= 'Z')))
            {
                Vec_char__push((&v), ((char)((((int32_t)(c)) + 32))));
            }
            else
            {
                Vec_char__push((&v), c);
            }
        }
        Vec_char__push((&v), 0);
        char *d = v.data;
        size_t l = v.len;
        size_t c_cap = v.cap;
        Vec_char__forget((&v));
        {
            String _z_ret = (struct String){.vec = (Vec_char){.data = d, .len = l, .cap = c_cap}};
            if (__z_drop_flag_v)
            {
                Vec_char__Drop_glue(&v);
            }
            return _z_ret;
        }
        if (__z_drop_flag_v)
        {
            Vec_char__Drop_glue(&v);
        }
    }
}

String String__pad_right(String *self, size_t target_len, char pad_char)
{
    {
        size_t current_len = String__length(self);
        if ((current_len >= target_len))
        {
            return String__from(String__c_str(self));
        }
        int __z_drop_flag_v = 1;
        Vec_char v = Vec_char__new();
        for (size_t i = (size_t)(0); i < current_len; i = (i + 1))
        {
            Vec_char__push((&v), Vec_char__get((&self->vec), i));
        }
        for (size_t i = (size_t)(current_len); i < target_len; i = (i + 1))
        {
            Vec_char__push((&v), pad_char);
        }
        Vec_char__push((&v), 0);
        char *d = v.data;
        size_t l = v.len;
        size_t c_cap = v.cap;
        Vec_char__forget((&v));
        {
            String _z_ret = (struct String){.vec = (Vec_char){.data = d, .len = l, .cap = c_cap}};
            if (__z_drop_flag_v)
            {
                Vec_char__Drop_glue(&v);
            }
            return _z_ret;
        }
        if (__z_drop_flag_v)
        {
            Vec_char__Drop_glue(&v);
        }
    }
}

String String__pad_left(String *self, size_t target_len, char pad_char)
{
    {
        size_t current_len = String__length(self);
        if ((current_len >= target_len))
        {
            return String__from(String__c_str(self));
        }
        int __z_drop_flag_v = 1;
        Vec_char v = Vec_char__new();
        size_t diff = (target_len - current_len);
        for (size_t i = (size_t)(0); i < diff; i = (i + 1))
        {
            Vec_char__push((&v), pad_char);
        }
        for (size_t i = (size_t)(0); i < current_len; i = (i + 1))
        {
            Vec_char__push((&v), Vec_char__get((&self->vec), i));
        }
        Vec_char__push((&v), 0);
        char *d = v.data;
        size_t l = v.len;
        size_t c_cap = v.cap;
        Vec_char__forget((&v));
        {
            String _z_ret = (struct String){.vec = (Vec_char){.data = d, .len = l, .cap = c_cap}};
            if (__z_drop_flag_v)
            {
                Vec_char__Drop_glue(&v);
            }
            return _z_ret;
        }
        if (__z_drop_flag_v)
        {
            Vec_char__Drop_glue(&v);
        }
    }
}

String String__to_uppercase(String *self)
{
    {
        size_t len = String__length(self);
        int __z_drop_flag_v = 1;
        Vec_char v = Vec_char__new();
        for (size_t i = (size_t)(0); i < len; i = (i + 1))
        {
            char c = Vec_char__get((&self->vec), i);
            if (((c >= 'a') && (c <= 'z')))
            {
                Vec_char__push((&v), ((char)((((int32_t)(c)) - 32))));
            }
            else
            {
                Vec_char__push((&v), c);
            }
        }
        Vec_char__push((&v), 0);
        char *d = v.data;
        size_t l = v.len;
        size_t c_cap = v.cap;
        Vec_char__forget((&v));
        {
            String _z_ret = (struct String){.vec = (Vec_char){.data = d, .len = l, .cap = c_cap}};
            if (__z_drop_flag_v)
            {
                Vec_char__Drop_glue(&v);
            }
            return _z_ret;
        }
        if (__z_drop_flag_v)
        {
            Vec_char__Drop_glue(&v);
        }
    }
}

Option_size_t String__find(String *self, char target)
{
    {
        size_t len = String__length(self);
        for (size_t i = (size_t)(0); i < len; i = (i + 1))
        {
            if ((Vec_char__get((&self->vec), i) == target))
            {
                return Option_size_t__Some(i);
            }
        }
        return Option_size_t__None();
    }
}

void String__print(String *self)
{
    {
        printf("%s", String__c_str(self));
        fflush(stdout);
    }
}

void String__println(String *self)
{
    {
        printf("%s\n", String__c_str(self));
    }
}

bool String__is_empty(String *self)
{
    {
        return (String__length(self) == 0);
    }
}

bool String__contains(String *self, char target)
{
    {
        return Option_size_t__is_some(
            (__typeof__((String__find(self, target)))[]){String__find(self, target)});
    }
}

bool String__starts_with(String *self, char *prefix)
{
    {
        ZC_AUTO plen = strlen(prefix);
        if ((plen > String__length(self)))
        {
            return false;
        }
        int zero = 0;
        return (strncmp(String__c_str(self), prefix, plen) == zero);
    }
}

bool String__ends_with(String *self, char *suffix)
{
    {
        ZC_AUTO slen = strlen(suffix);
        size_t len = String__length(self);
        if ((slen > len))
        {
            return false;
        }
        int32_t offset = ((int32_t)((len - slen)));
        int zero = 0;
        return (strcmp((String__c_str(self) + offset), suffix) == zero);
    }
}

void String__reserve(String *self, size_t cap)
{
    {
        Vec_char__grow_to_fit((&self->vec), (cap + 1));
    }
}

void String__free(String *self)
{
    {
        Vec_char__free((&self->vec));
    }
}

size_t String___utf8_seq_len(char first_byte)
{
    {
        int32_t b = ((int32_t)(first_byte));
        if (((b & 128) == 0))
        {
            return 1;
        }
        if (((b & 224) == 192))
        {
            return 2;
        }
        if (((b & 240) == 224))
        {
            return 3;
        }
        if (((b & 248) == 240))
        {
            return 4;
        }
        return 1;
    }
}

size_t String__utf8_len(String *self)
{
    {
        size_t count = 0;
        size_t i = 0;
        size_t len = String__length(self);
        while ((i < len))
        {
            char c = Vec_char__get((&self->vec), i);
            (i = (i + String___utf8_seq_len(c)));
            (count = (count + 1));
        }
        return count;
    }
}

String String__utf8_at(String *self, size_t idx)
{
    {
        size_t count = 0;
        size_t i = 0;
        size_t len = String__length(self);
        while ((i < len))
        {
            char c = Vec_char__get((&self->vec), i);
            size_t seq = String___utf8_seq_len(c);
            if ((count == idx))
            {
                return String__substring(self, i, seq);
            }
            (i = (i + seq));
            (count = (count + 1));
        }
        return String__new("");
    }
}

int32_t String__utf8_get(String *self, size_t idx)
{
    {
        size_t count = 0;
        size_t i = 0;
        size_t len = String__length(self);
        while ((i < len))
        {
            uint8_t c = ((uint8_t)(Vec_char__get((&self->vec), i)));
            size_t seq = String___utf8_seq_len(((char)(c)));
            if ((count == idx))
            {
                if ((seq == 1))
                {
                    return ((int32_t)(c));
                }
                if ((seq == 2))
                {
                    return ((int32_t)((
                        (((int32_t)((c & 31))) << 6) |
                        (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63))));
                }
                if ((seq == 3))
                {
                    return ((int32_t)((
                        ((((int32_t)((c & 15))) << 12) |
                         ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63)
                          << 6)) |
                        (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 2)))))) & 63))));
                }
                if ((seq == 4))
                {
                    return ((int32_t)((
                        (((((int32_t)((c & 7))) << 18) |
                          ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63)
                           << 12)) |
                         ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 2)))))) & 63)
                          << 6)) |
                        (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 3)))))) & 63))));
                }
            }
            (i = (i + seq));
            (count = (count + 1));
        }
        return ((int32_t)(0));
    }
}

Vec_int32_t String__runes(String *self)
{
    {
        int __z_drop_flag_v = 1;
        Vec_int32_t v = Vec_int32_t__new();
        size_t i = 0;
        size_t len = String__length(self);
        while ((i < len))
        {
            uint8_t c = ((uint8_t)(Vec_char__get((&self->vec), i)));
            size_t seq = String___utf8_seq_len(((char)(c)));
            int32_t val = 0;
            if ((seq == 1))
            {
                (val = ((int32_t)(c)));
            }
            else if ((seq == 2))
            {
                (val = ((int32_t)((
                     (((int32_t)((c & 31))) << 6) |
                     (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63)))));
            }
            else if ((seq == 3))
            {
                (val = ((int32_t)((
                     ((((int32_t)((c & 15))) << 12) |
                      ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63)
                       << 6)) |
                     (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 2)))))) & 63)))));
            }
            else if ((seq == 4))
            {
                (val = ((int32_t)((
                     (((((int32_t)((c & 7))) << 18) |
                       ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63)
                        << 12)) |
                      ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 2)))))) & 63)
                       << 6)) |
                     (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 3)))))) & 63)))));
            }
            Vec_int32_t__push((&v), val);
            (i = (i + seq));
        }
        return ({
            ZC_AUTO _z_ret_mv = v;
            memset(&v, 0, sizeof(_z_ret_mv));
            __z_drop_flag_v = 0;
            if (__z_drop_flag_v)
            {
                Vec_int32_t__Drop_glue(&v);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_v)
        {
            Vec_int32_t__Drop_glue(&v);
        }
    }
}

StringCharsIter String__chars(String *self)
{
    {
        return (struct StringCharsIter){.data = String__c_str(self), .len = String__length(self)};
    }
}

String String__from_runes_vec(Vec_int32_t runes)
{
    int __z_drop_flag_runes = 1;
    {
        int __z_drop_flag_s = 1;
        String s = String__new("");
        for (size_t i = (size_t)(0); i < runes.len; i = (i + 1))
        {
            String__push_rune((&s), Vec_int32_t__get((&runes), i));
        }
        return ({
            ZC_AUTO _z_ret_mv = s;
            memset(&s, 0, sizeof(_z_ret_mv));
            __z_drop_flag_s = 0;
            if (__z_drop_flag_s)
            {
                String__Drop_glue(&s);
            }
            if (__z_drop_flag_runes)
            {
                Vec_int32_t__Drop_glue(&runes);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_s)
        {
            String__Drop_glue(&s);
        }
    }
    if (__z_drop_flag_runes)
    {
        Vec_int32_t__Drop_glue(&runes);
    }
}

void String__insert_rune(String *self, size_t idx, int32_t r)
{
    {
        size_t i = 0;
        size_t count = 0;
        size_t len = String__length(self);
        while (((i < len) && (count < idx)))
        {
            (i = (i + String___utf8_seq_len(Vec_char__get((&self->vec), i))));
            (count = (count + 1));
        }
        uint32_t val = ((uint32_t)(r));
        if ((val < 128))
        {
            Vec_char__insert((&self->vec), i, ((char)(val)));
        }
        else if ((val < 2048))
        {
            Vec_char__insert((&self->vec), i, ((char)((192 | (val >> 6)))));
            Vec_char__insert((&self->vec), (i + 1), ((char)((128 | (val & 63)))));
        }
        else if ((val < 65536))
        {
            Vec_char__insert((&self->vec), i, ((char)((224 | (val >> 12)))));
            Vec_char__insert((&self->vec), (i + 1), ((char)((128 | ((val >> 6) & 63)))));
            Vec_char__insert((&self->vec), (i + 2), ((char)((128 | (val & 63)))));
        }
        else
        {
            Vec_char__insert((&self->vec), i, ((char)((240 | (val >> 18)))));
            Vec_char__insert((&self->vec), (i + 1), ((char)((128 | ((val >> 12) & 63)))));
            Vec_char__insert((&self->vec), (i + 2), ((char)((128 | ((val >> 6) & 63)))));
            Vec_char__insert((&self->vec), (i + 3), ((char)((128 | (val & 63)))));
        }
    }
}

int32_t String__remove_rune_at(String *self, size_t idx)
{
    {
        size_t i = 0;
        size_t count = 0;
        size_t len = String__length(self);
        while (((i < len) && (count < idx)))
        {
            (i = (i + String___utf8_seq_len(Vec_char__get((&self->vec), i))));
            (count = (count + 1));
        }
        if ((i >= len))
        {
            return ((int32_t)(0));
        }
        uint8_t c = ((uint8_t)(Vec_char__get((&self->vec), i)));
        size_t seq = String___utf8_seq_len(((char)(c)));
        int32_t val = 0;
        if ((seq == 1))
        {
            (val = ((int32_t)(c)));
        }
        else if ((seq == 2))
        {
            (val = ((int32_t)((
                 (((int32_t)((c & 31))) << 6) |
                 (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63)))));
        }
        else if ((seq == 3))
        {
            (val = ((int32_t)((
                 ((((int32_t)((c & 15))) << 12) |
                  ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63) << 6)) |
                 (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 2)))))) & 63)))));
        }
        else if ((seq == 4))
        {
            (val = ((int32_t)((
                 (((((int32_t)((c & 7))) << 18) |
                   ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 1)))))) & 63) << 12)) |
                  ((((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 2)))))) & 63) << 6)) |
                 (((int32_t)(((uint8_t)(Vec_char__get((&self->vec), (i + 3)))))) & 63)))));
        }
        for (size_t j = (size_t)(0); j < seq; j = (j + 1))
        {
            Vec_char__remove((&self->vec), i);
        }
        return val;
    }
}

String String__utf8_substr(String *self, size_t start_idx, size_t num_chars)
{
    {
        if ((num_chars == 0))
        {
            return String__new("");
        }
        size_t byte_start = 0;
        size_t byte_len = 0;
        size_t count = 0;
        size_t i = 0;
        size_t len = String__length(self);
        bool found_start = false;
        while ((i < len))
        {
            if (((!found_start) && (count == start_idx)))
            {
                (byte_start = i);
                (found_start = true);
                (count = 0);
            }
            else if ((!found_start))
            {
                char c = Vec_char__get((&self->vec), i);
                (i = (i + String___utf8_seq_len(c)));
                (count = (count + 1));
                continue;
            }
            if ((count < num_chars))
            {
                char c = Vec_char__get((&self->vec), i);
                size_t seq = String___utf8_seq_len(c);
                (byte_len = (byte_len + seq));
                (i = (i + seq));
                (count = (count + 1));
            }
            else
            {
                break;
            }
        }
        if ((!found_start))
        {
            return String__new("");
        }
        return String__substring(self, byte_start, byte_len);
    }
}

Vec_String String__split(String *self, char delim)
{
    {
        int __z_drop_flag_parts = 1;
        Vec_String parts = Vec_String__new();
        size_t len = String__length(self);
        if ((len == 0))
        {
            return ({
                ZC_AUTO _z_ret_mv = parts;
                memset(&parts, 0, sizeof(_z_ret_mv));
                __z_drop_flag_parts = 0;
                if (__z_drop_flag_parts)
                {
                    Vec_String__Drop_glue(&parts);
                }
                _z_ret_mv;
            });
        }
        size_t start = 0;
        size_t i = 0;
        while ((i < len))
        {
            if ((Vec_char__get((&self->vec), i) == delim))
            {
                Vec_String__push((&parts), String__substring(self, start, (i - start)));
                (start = (i + 1));
            }
            (i = (i + 1));
        }
        if ((start <= len))
        {
            Vec_String__push((&parts), String__substring(self, start, (len - start)));
        }
        return ({
            ZC_AUTO _z_ret_mv = parts;
            memset(&parts, 0, sizeof(_z_ret_mv));
            __z_drop_flag_parts = 0;
            if (__z_drop_flag_parts)
            {
                Vec_String__Drop_glue(&parts);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_parts)
        {
            Vec_String__Drop_glue(&parts);
        }
    }
}

String String__trim(String *self)
{
    {
        size_t start = 0;
        size_t len = String__length(self);
        size_t end = len;
        while ((start < len))
        {
            char c = Vec_char__get((&self->vec), start);
            if (((((c != ' ') && (c != '\t')) && (c != '\n')) && (c != '\r')))
            {
                break;
            }
            (start = (start + 1));
        }
        if ((start == len))
        {
            return String__new("");
        }
        while ((end > start))
        {
            char c = Vec_char__get((&self->vec), (end - 1));
            if (((((c != ' ') && (c != '\t')) && (c != '\n')) && (c != '\r')))
            {
                break;
            }
            (end = (end - 1));
        }
        return String__substring(self, start, (end - start));
    }
}

String String__replace(String *self, char *target, char *replacement)
{
    {
        ZC_AUTO t_len = strlen(target);
        if ((t_len == 0))
        {
            return String__substring(self, 0, String__length(self));
        }
        size_t s_len = String__length(self);
        int __z_drop_flag_result = 1;
        String result = String__new("");
        size_t i = 0;
        while ((i < s_len))
        {
            if (((i + t_len) <= s_len))
            {
                bool is_match = true;
                for (size_t k = (size_t)(0); k < t_len; k = (k + 1))
                {
                    if ((Vec_char__get((&self->vec), (i + k)) != target[k]))
                    {
                        (is_match = false);
                        break;
                    }
                }
                if (is_match)
                {
                    int __z_drop_flag_r_str = 1;
                    String r_str = String__new(replacement);
                    String__append((&result), (&r_str));
                    (i = (i + t_len));
                    if (__z_drop_flag_r_str)
                    {
                        String__Drop_glue(&r_str);
                    }
                    continue;
                    if (__z_drop_flag_r_str)
                    {
                        String__Drop_glue(&r_str);
                    }
                }
            }
            int __z_drop_flag_v = 1;
            Vec_char v = Vec_char__new();
            Vec_char__push((&v), Vec_char__get((&self->vec), i));
            Vec_char__push((&v), 0);
            int __z_drop_flag_ch_s = 1;
            String ch_s = String__new(v.data);
            String__append((&result), (&ch_s));
            String__destroy((&ch_s));
            (i = (i + 1));
            if (__z_drop_flag_ch_s)
            {
                String__Drop_glue(&ch_s);
            }
            if (__z_drop_flag_v)
            {
                Vec_char__Drop_glue(&v);
            }
        }
        return ({
            ZC_AUTO _z_ret_mv = result;
            memset(&result, 0, sizeof(_z_ret_mv));
            __z_drop_flag_result = 0;
            if (__z_drop_flag_result)
            {
                String__Drop_glue(&result);
            }
            _z_ret_mv;
        });
        if (__z_drop_flag_result)
        {
            String__Drop_glue(&result);
        }
    }
}

Option_int32_t StringCharsIter__next(StringCharsIter *self)
{
    {
        if ((self->pos >= self->len))
        {
            return Option_int32_t__None();
        }
        uint8_t c = ((uint8_t)(self->data[self->pos]));
        size_t seq = String___utf8_seq_len(((char)(c)));
        if (((self->pos + seq) > self->len))
        {
            (self->pos = self->len);
            return Option_int32_t__None();
        }
        int32_t val = 0;
        if ((seq == 1))
        {
            (val = ((int32_t)(c)));
        }
        else if ((seq == 2))
        {
            (val = ((int32_t)(((((int32_t)((c & 31))) << 6) |
                               (((int32_t)(((uint8_t)(self->data[(self->pos + 1)])))) & 63)))));
        }
        else if ((seq == 3))
        {
            (val =
                 ((int32_t)((((((int32_t)((c & 15))) << 12) |
                              ((((int32_t)(((uint8_t)(self->data[(self->pos + 1)])))) & 63) << 6)) |
                             (((int32_t)(((uint8_t)(self->data[(self->pos + 2)])))) & 63)))));
        }
        else if ((seq == 4))
        {
            (val = ((
                 int32_t)(((((((int32_t)((c & 7))) << 18) |
                             ((((int32_t)(((uint8_t)(self->data[(self->pos + 1)])))) & 63) << 12)) |
                            ((((int32_t)(((uint8_t)(self->data[(self->pos + 2)])))) & 63) << 6)) |
                           (((int32_t)(((uint8_t)(self->data[(self->pos + 3)])))) & 63)))));
        }
        (self->pos = (self->pos + seq));
        return Option_int32_t__Some(val);
    }
}

int main()
{
    _z_run_tests();
    return 0;
}
