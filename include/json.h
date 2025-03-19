#ifndef __JSON_H__
#define __JSON_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
void print_trace();
// --------------------------------------------------
//                  JSON TOKEN
// --------------------------------------------------
enum json_token_type_t {
    JT_MISSING,
    JT_EMPTY,
    JT_STRING,
    JT_NUMBER,
    JT_BOOL,
    JT_NULL,
    JT_INT,
    JT_UINT,
    JT_FLOAT,
    JT_OBJECT,
    JT_ARRAY,
    JT_TOKEN_SIZE,
};

struct json_tok_t {
    enum json_token_type_t type;
    char *text;
    union {
        bool boolean;
        int8_t i8;
        int16_t i16;
        int32_t i32;
        int64_t i64;
        uint8_t u8;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;
        float f32;
        double f64;
    };
};

struct json_obj_t {
    enum json_token_type_t type;
    void *pairs;
};

struct json_arr_t {
    enum json_token_type_t type;
    void *values;
};

typedef union json_t {
    enum json_token_type_t type;
    struct json_tok_t tok;
    struct json_obj_t obj;
    struct json_arr_t arr;
#define m_text tok.text
#define m_bool tok.boolean
#define m_i8 tok.i8
#define m_i16 tok.i16
#define m_i32 tok.i32
#define m_i64 tok.i64
#define m_u8 tok.u8
#define m_u16 tok.u16
#define m_u32 tok.u32
#define m_u64 tok.u64
#define m_f32 tok.f32
#define m_f64 tok.f64
} json_t;

struct json_pair_t {
    char *key;
    union json_t value;
};

#ifndef __cplusplus
#define JSON_MISSING ((union json_t){.tok = {.type = JT_MISSING}})
#define JSON_EMPTY ((union json_t){.tok = {.type = JT_EMPTY}})
#define JSON_ARRAY ((union json_t){.arr = {.type = JT_ARRAY}})
#define JSON_OBJECT ((union json_t){.obj = {.type = JT_OBJECT}})
#define JSON_NULL ((union json_t){.tok = {.type = JT_NULL}})
#define JSON_TRUE ((union json_t){.tok = {.type = JT_BOOL, .boolean = true}})
#define JSON_FALSE ((union json_t){.tok = {.type = JT_BOOL, .boolean = false}})
#define JSON_STRING(x) ((union json_t){.tok = {.type = JT_STRING, .text = (char *)(x)}})
#define JSON_NUMBER(x) ((union json_t){.tok = {.type = JT_NUMBER, .text = (char *)(x)}})
#define JSON_BOOL(x) ((union json_t){.tok = {.type = JT_BOOL, .boolean = (x)}})
#define JSON_INT(x) ((union json_t){.tok = {.type = JT_INT, .i64 = (int64_t)(x)}})
#define JSON_UINT(x) ((union json_t){.tok = {.type = JT_UINT, .u64 = (uint64_t)(x)}})
#define JSON_FLOAT(x) ((union json_t){.tok = {.type = JT_FLOAT, .f64 = (double)(x)}})
#endif

#define json_is_object(j) ((j).type == JT_OBJECT)
#define json_is_array(j) ((j).type == JT_ARRAY)
#define json_is_int(j) ((j).type == JT_INT)
#define json_is_uint(j) ((j).type == JT_UINT)
#define json_is_string(j) ((j).type == JT_STRING)
#define json_is_raw_number(j) ((j).type == JT_NUMBER)
#define json_is_bool(j) ((j).type == JT_BOOL)
#define json_is_null(j) ((j).type == JT_NULL)
#define json_is_float(j) ((j).type == JT_FLOAT)
#define json_is_terminal_token(j)                                                                                      \
    ((j).type == JT_MISSING || (j).type == JT_EMPTY || (j).type == JT_NULL || (j).type == JT_BOOL || (j).type == JT_INT || \
        (j).type == JT_UINT || (j).type == JT_FLOAT || (j).type == JT_STRING || (j).type == JT_NUMBER)
#define json_is_empty(j) ((j).type == JT_EMPTY)
#define json_is_missing(j) ((j).type == JT_MISSING)

const char *json_token2str(enum json_token_type_t type);


const char *json_type2str(enum json_token_type_t type);

// --------------------------------------------------
//     JSON UNDER LAYER DATA STRUCTURE EXTENSION
// --------------------------------------------------

typedef void (*json_obj_iter_cb)(struct json_pair_t *pair, void *args);
typedef void (*json_arr_iter_cb)(size_t index, union json_t *value, void *args);

void jsonext_obj_new(union json_t *j, size_t capacity);
void jsonext_arr_new(union json_t *j, size_t capacity);

void jsonext_obj_insert(union json_t *j, struct json_pair_t *pair);
void jsonext_arr_append(union json_t *j, union json_t *value);

struct json_pair_t *jsonext_obj_get(union json_t *j, const char *key);
union json_t *jsonext_arr_get(union json_t *j, size_t index);

struct json_pair_t *jsonext_obj_delete(union json_t *j, const char *key);
union json_t *jsonext_arr_delete(union json_t *j, size_t index);

void jsonext_obj_clean(union json_t *j);
void jsonext_arr_clean(union json_t *j);

size_t jsonext_obj_length(union json_t *j);
size_t jsonext_arr_length(union json_t *j);

size_t jsonext_obj_capacity(union json_t *j);
size_t jsonext_arr_capacity(union json_t *j);

void jsonext_obj_iter(union json_t *j, json_obj_iter_cb f, void *fargs);
struct json_pair_t *jsonext_obj_iter_first(union json_t *j);
struct json_pair_t *jsonext_obj_iter_next(union json_t *j, struct json_pair_t *pair);

// --------------------------------------------------
//                JSON OBJECT FUNCTION
// --------------------------------------------------
union json_t json_create_obj(size_t capacity);

union json_t *__json_get_from_obj(union json_t j, const char *key);
union json_t __json_remove_from_obj(union json_t *j, const char *key);
void __json_delete_from_obj(union json_t *j, const char *key);

bool json_set_str(union json_t *j, const char *key, const char *value);
bool json_set_bool(union json_t *j, const char *key, bool value);
bool json_set_null(union json_t *j, const char *key, void *value);
bool json_set_i8(union json_t *j, const char *key, int8_t value);
bool json_set_i16(union json_t *j, const char *key, int16_t value);
bool json_set_i32(union json_t *j, const char *key, int32_t value);
bool json_set_i64(union json_t *j, const char *key, int64_t value);
bool json_set_u8(union json_t *j, const char *key, uint8_t value);
bool json_set_u16(union json_t *j, const char *key, uint16_t value);
bool json_set_u32(union json_t *j, const char *key, uint32_t value);
bool json_set_u64(union json_t *j, const char *key, uint64_t value);
bool json_set_f32(union json_t *j, const char *key, float value);
bool json_set_f64(union json_t *j, const char *key, double value);
bool json_set_value(union json_t *j, const char *key, union json_t value);
bool json_set_value_p(union json_t *j, const char *key, union json_t *value);
bool json_set_value_np(union json_t *j, const char *key, size_t key_len, union json_t *value);

/*
 * Booling type is compatibale i32, it will not goto bool option in C
 */
#ifndef __cplusplus
#define json_set(j, key, value)                                                                                        \
    _Generic((value),                                                                                                  \
        const char *: json_set_str,                                                                                    \
        char *: json_set_str,                                                                                          \
        bool: json_set_bool,                                                                                           \
        void *: json_set_null,                                                                                         \
        int8_t: json_set_i8,                                                                                           \
        int16_t: json_set_i16,                                                                                         \
        int32_t: json_set_i32,                                                                                         \
        int64_t: json_set_i64,                                                                                         \
        uint8_t: json_set_u8,                                                                                          \
        uint16_t: json_set_u16,                                                                                        \
        uint32_t: json_set_u32,                                                                                        \
        uint64_t: json_set_u64,                                                                                        \
        float: json_set_f32,                                                                                           \
        double: json_set_f64,                                                                                          \
        json_t: json_set_value,                                                                                        \
        json_t *: json_set_value_p,                                                                                    \
        default: json_set_value)((j), (key), (value))
#endif

// --------------------------------------------------
//                JSON ARRAY FUNCTION
// --------------------------------------------------
union json_t json_create_arr(size_t capacity);

union json_t *__json_get_from_arr(union json_t j, long int i);
union json_t __json_remove_from_arr(union json_t *j, long int i);
void __json_delete_from_arr(union json_t *j, long int i);

bool json_append_str(union json_t *j, const char *value);
bool json_append_bool(union json_t *j, bool value);
bool json_append_null(union json_t *j, void *value);
bool json_append_i8(union json_t *j, int8_t value);
bool json_append_i16(union json_t *j, int16_t value);
bool json_append_i32(union json_t *j, int32_t value);
bool json_append_i64(union json_t *j, int64_t value);
bool json_append_u8(union json_t *j, uint8_t value);
bool json_append_u16(union json_t *j, uint16_t value);
bool json_append_u32(union json_t *j, uint32_t value);
bool json_append_u64(union json_t *j, uint64_t value);
bool json_append_f32(union json_t *j, float value);
bool json_append_f64(union json_t *j, double value);
bool json_append_value(union json_t *j, union json_t value);
bool json_append_value_p(union json_t *j, union json_t *value);

#ifndef __cplusplus
#define json_append(j, value)                                                                                          \
    _Generic((value),                                                                                                  \
        const char *: json_append_str,                                                                                 \
        char *: json_append_str,                                                                                       \
        bool: json_append_bool,                                                                                        \
        void *: json_append_null,                                                                                      \
        int8_t: json_append_i8,                                                                                        \
        int16_t: json_append_i16,                                                                                      \
        int32_t: json_append_i32,                                                                                      \
        int64_t: json_append_i64,                                                                                      \
        uint8_t: json_append_u8,                                                                                       \
        uint16_t: json_append_u16,                                                                                     \
        uint32_t: json_append_u32,                                                                                     \
        uint64_t: json_append_u64,                                                                                     \
        float: json_append_f32,                                                                                        \
        double: json_append_f64,                                                                                       \
        json_t: json_append_value,                                                                                     \
        json_t *: json_append_value_p,                                                                                 \
        default: json_append_value)((j), (value))
#endif

// --------------------------------------------------
//                JSON COMMON FUNCTION
// --------------------------------------------------

union json_t json_dup(union json_t t);

#ifndef __cplusplus
#define json_get(j, key)                                                                                               \
    _Generic((key), const char *: __json_get_from_obj, char *: __json_get_from_obj, default: __json_get_from_arr)(     \
        (j), (key))
#define json_remove(j, key)                                                                                            \
    _Generic((key),                                                                                                    \
        const char *: __json_remove_from_obj,                                                                          \
        char *: __json_remove_from_obj,                                                                                \
        default: __json_remove_from_arr)((j), (key))
#define json_delete(j, key)                                                                                            \
    _Generic((key),                                                                                                    \
        const char *: __json_delete_from_obj,                                                                          \
        char *: __json_delete_from_obj,                                                                                \
        default: __json_delete_from_arr)((j), (key))
#endif

size_t json_length(json_t j);
size_t json_capacity(json_t j);

void json_clean(json_t *j);

struct json_config {
    int indent;
    int offset;
};

#ifndef __cplusplus
#define json_dumps(j, ...) __json_dumps((j), (struct json_config){__VA_ARGS__})
#define json_dump(j, f, ...) __json_dump((j), (f), (struct json_config){__VA_ARGS__})
#define json_pprint(j, ...) __json_pprint((j), (struct json_config){__VA_ARGS__})
#endif

char *__json_dumps(union json_t j, struct json_config config);
void __json_dump(union json_t j, FILE *f, struct json_config config);
void __json_pprint(union json_t j, struct json_config config);
void json_print(union json_t j);

// TODO foreach
// #define json_foreach_arr(i, it, jp) \
//     union json_t *(it) = NULL; \
//     for (size_t (i) = 0; ({ bool res = i < json_length(jp); it = res ? json_get(jp, i) : it; res; });
//     i++)
// json_foreach_arr(i, it, &j)

// --------------------------------------------------
//                    JSON Lexer
// --------------------------------------------------
enum json_lexer_token_type_t {
    JLT_MISSING,
    JLT_STRING,
    JLT_NUMBER,
    JLT_COMMA,
    JLT_COLON,
    JLT_LPAIR,
    JLT_RPAIR,
    JLT_LARRAY,
    JLT_RARRAY,
    JLT_TRUE,
    JLT_FALSE,
    JLT_NULL,
    JLT_LEXER_TOKEN_SIZE
};

struct json_lexer_token_t {
    enum json_lexer_token_type_t type;
    const char *text;
    size_t index;
    size_t start;
    size_t end;
    size_t column;
    size_t row;
};

struct json_lexer_container_t {
    size_t length;
    size_t capacity;
    struct json_lexer_token_t *list;
};

struct json_lexer_context_t {
    struct json_lexer_container_t tokens;
    int currentChar;
    size_t offset;
    size_t column;
    size_t row;
    const char *from_string;
    size_t from_string_len;
};

struct json_lexer_context_t *json_create_lexer(const char *from_string);
void json_delete_lexer(struct json_lexer_context_t *ctx);
void json_execute_lexer(struct json_lexer_context_t *ctx);
void json_print_lexer(struct json_lexer_context_t *ctx);
// --------------------------------------------------
//                END JSON Lexer
// --------------------------------------------------

// --------------------------------------------------
//                  JSON Parser
// --------------------------------------------------
struct json_parser_context_t {
    size_t token_index;
    struct json_lexer_context_t *lexer;
    union json_t root;
};

struct json_parser_context_t *json_create_parser(struct json_lexer_context_t *lexer);
void json_delete_parser(struct json_parser_context_t *ctx);
void json_execute_parser(struct json_parser_context_t *ctx);
void json_print_parser(struct json_parser_context_t *ctx);

union json_t json_string(const char *input_text);
union json_t json_load(const char *file_path);
union json_t json_file(FILE *f);
// --------------------------------------------------
//                  END JSON Parser
// --------------------------------------------------
#endif /* __JSON_H__ */
