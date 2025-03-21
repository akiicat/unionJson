#include <gtest/gtest.h>

#include "env.hh"
#include "json.hh"

TEST(JsonObjectTest, CreateObject) {
    /* Arrange */
    size_t capacity = 10;

    /* Act */
    union json_t j = json_create_obj(capacity);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(0, json_length(j));
    EXPECT_LE(capacity, json_capacity(j));

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, GetFromObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", 1);
    json_set(&j, "B", "2");

    /* Act */
    union json_t *res = json_get(j, "B");

    /* Assert */
    EXPECT_EQ(JT_STRING, res->type);
    EXPECT_STREQ("2", res->tok.text);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, RemoveFromObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", 1);
    json_set(&j, "B", "2");

    /* Act */
    union json_t res = json_remove(&j, "B");
    union json_t res_not_exist = json_remove(&j, "C");

    /* Assert */
    EXPECT_EQ(JT_STRING, res.type);
    EXPECT_STREQ("2", res.tok.text);
    EXPECT_EQ(1, json_length(j));
    EXPECT_EQ(JT_MISSING, res_not_exist.type);

    /* Clean */
    json_clean(&j);
    json_clean(&res);
}

TEST(JsonObjectTest, DeleteFromObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", 1);
    json_set(&j, "B", "2");

    /* Act */
    json_delete(&j, "B");

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(1, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, ObjectLength) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", 1);
    json_set(&j, "B", "2");

    /* Act */
    size_t res = json_length(j);

    /* Assert */
    EXPECT_EQ(2, res);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, ObjectCapacity) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", 1);
    json_set(&j, "B", "2");

    /* Act */
    size_t res = json_capacity(j);

    /* Assert */
    EXPECT_LE(2, res);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetString) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_str(&j, "A", "1");
    json_set_str(&j, "B", "2");

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_STRING, json_get(j, "A")->type);
    EXPECT_EQ(JT_STRING, json_get(j, "B")->type);
    EXPECT_STREQ("1", json_get(j, "A")->m_text);
    EXPECT_STREQ("2", json_get(j, "B")->m_text);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetBool) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_bool(&j, "A", true);
    json_set_bool(&j, "B", false);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_BOOL, json_get(j, "A")->type);
    EXPECT_EQ(JT_BOOL, json_get(j, "B")->type);
    EXPECT_TRUE(json_get(j, "A")->m_bool);
    EXPECT_FALSE(json_get(j, "B")->m_bool);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetNull) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_null(&j, "A", NULL);
    json_set_null(&j, "B", NULL);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_NULL, json_get(j, "A")->type);
    EXPECT_EQ(JT_NULL, json_get(j, "B")->type);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetI8) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_i8(&j, "A", 1);
    json_set_i8(&j, "B", -2);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(JT_INT, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);
    EXPECT_EQ(-2, json_get(j, "B")->m_i64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetI16) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_i16(&j, "A", 1);
    json_set_i16(&j, "B", -2);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(JT_INT, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);
    EXPECT_EQ(-2, json_get(j, "B")->m_i64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetI32) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_i32(&j, "A", 1);
    json_set_i32(&j, "B", -2);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(JT_INT, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);
    EXPECT_EQ(-2, json_get(j, "B")->m_i64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetI64) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_i64(&j, "A", 1);
    json_set_i64(&j, "B", -2);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(JT_INT, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);
    EXPECT_EQ(-2, json_get(j, "B")->m_i64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetU8) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_u8(&j, "A", 1);
    json_set_u8(&j, "B", 2);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_UINT, json_get(j, "A")->type);
    EXPECT_EQ(JT_UINT, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_u64);
    EXPECT_EQ(2, json_get(j, "B")->m_u64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetU16) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_u16(&j, "A", 1);
    json_set_u16(&j, "B", 2);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_UINT, json_get(j, "A")->type);
    EXPECT_EQ(JT_UINT, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_u64);
    EXPECT_EQ(2, json_get(j, "B")->m_u64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetU32) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_u32(&j, "A", 1);
    json_set_u32(&j, "B", 2);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_UINT, json_get(j, "A")->type);
    EXPECT_EQ(JT_UINT, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_u64);
    EXPECT_EQ(2, json_get(j, "B")->m_u64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetU64) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_u64(&j, "A", 1);
    json_set_u64(&j, "B", 2);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_UINT, json_get(j, "A")->type);
    EXPECT_EQ(JT_UINT, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_u64);
    EXPECT_EQ(2, json_get(j, "B")->m_u64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetF32) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_f32(&j, "A", 1.0);
    json_set_f32(&j, "B", -2.0);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_FLOAT, json_get(j, "A")->type);
    EXPECT_EQ(JT_FLOAT, json_get(j, "B")->type);
    EXPECT_EQ(1.0, json_get(j, "A")->m_f64);
    EXPECT_EQ(-2.0, json_get(j, "B")->m_f64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetF64) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set_f64(&j, "A", 1.0);
    json_set_f64(&j, "B", -2.0);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_FLOAT, json_get(j, "A")->type);
    EXPECT_EQ(JT_FLOAT, json_get(j, "B")->type);
    EXPECT_EQ(1.0, json_get(j, "A")->m_f64);
    EXPECT_EQ(-2.0, json_get(j, "B")->m_f64);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetValue) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    union json_t jobj = JSON_OBJECT;
    union json_t jarr = JSON_ARRAY;
    json_set(&jobj, "A", 1);
    json_append(&jarr, "2");

    /* Act */
    json_set_value(&j, "A", JSON_INT(1));
    json_set_value(&j, "B", JSON_STRING("2"));
    json_set_value(&j, "C", jobj);
    json_set_value(&j, "D", jarr);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(4, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(JT_STRING, json_get(j, "B")->type);
    EXPECT_EQ(JT_OBJECT, json_get(j, "C")->type);
    EXPECT_EQ(JT_ARRAY, json_get(j, "D")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);
    EXPECT_STREQ("2", json_get(j, "B")->m_text);
    EXPECT_EQ(1, json_get(*json_get(j, "C"), "A")->m_i64);
    EXPECT_STREQ("2", json_get(*json_get(j, "D"), 0)->m_text);

    /* Clean */
    json_clean(&j);
    json_clean(&jobj);
    json_clean(&jarr);
}

TEST(JsonObjectTest, SetValueP) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    union json_t jobj = JSON_OBJECT;
    union json_t jarr = JSON_ARRAY;
    json_set(&jobj, "A", 1);
    json_append(&jarr, "2");

    /* Act */
    json_set_value_p(&j, "A", &jobj);
    json_set_value_p(&j, "B", &jarr);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_OBJECT, json_get(j, "A")->type);
    EXPECT_EQ(JT_ARRAY, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(*json_get(j, "A"), "A")->m_i64);
    EXPECT_STREQ("2", json_get(*json_get(j, "B"), 0)->m_text);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetTerminalToken) {
    /* Arrange */
    union json_t j = JSON_OBJECT;

    /* Act */
    json_set(&j, "A", 1);
    json_set(&j, "B", "2");
    json_set(&j, "C", 3.14);
    json_set(&j, "D", (void *)NULL);
    json_set(&j, "E", JSON_NULL);
    json_set(&j, "F", JSON_TRUE);
    json_set(&j, "G", JSON_FALSE);
    json_set(&j, "H", JSON_BOOL(true));
    json_set(&j, "I", JSON_INT(-1));
    json_set(&j, "J", JSON_UINT(1));
    json_set(&j, "K", JSON_STRING("2"));
    json_set(&j, "L", JSON_NUMBER("1.0"));

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(12, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(JT_STRING, json_get(j, "B")->type);
    EXPECT_EQ(JT_FLOAT, json_get(j, "C")->type);
    EXPECT_EQ(JT_NULL, json_get(j, "D")->type);
    EXPECT_EQ(JT_NULL, json_get(j, "E")->type);
    EXPECT_EQ(JT_BOOL, json_get(j, "F")->type);
    EXPECT_EQ(JT_BOOL, json_get(j, "G")->type);
    EXPECT_EQ(JT_BOOL, json_get(j, "H")->type);
    EXPECT_EQ(JT_INT, json_get(j, "I")->type);
    EXPECT_EQ(JT_UINT, json_get(j, "J")->type);
    EXPECT_EQ(JT_STRING, json_get(j, "K")->type);
    EXPECT_EQ(JT_NUMBER, json_get(j, "L")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);
    EXPECT_STREQ("2", json_get(j, "B")->m_text);
    EXPECT_EQ(3.14, json_get(j, "C")->m_f64);
    EXPECT_TRUE(json_get(j, "F")->m_bool);
    EXPECT_FALSE(json_get(j, "G")->m_bool);
    EXPECT_TRUE(json_get(j, "H")->m_bool);
    EXPECT_EQ(-1, json_get(j, "I")->m_i64);
    EXPECT_EQ(1, json_get(j, "J")->m_u64);
    EXPECT_STREQ("2", json_get(j, "K")->m_text);
    EXPECT_STREQ("1.0", json_get(j, "L")->m_text);

    /* Clean */
    json_clean(&j);
}

TEST(JsonObjectTest, SetReturnValue) {
    /* Arrange */
    union json_t jobj = JSON_OBJECT;
    union json_t jarr = JSON_ARRAY;

    /* Act */
    bool res_1 = json_set(&jobj, "A", 1);
    bool res_2 = json_set(&jobj, "B", { .type = JT_MISSING });
    bool res_3 = json_set(&jarr, "C", 3);

    /* Assert */
    EXPECT_TRUE(res_1);
    EXPECT_TRUE(res_2);
    EXPECT_FALSE(res_3);
    EXPECT_EQ(JT_OBJECT, jobj.type);
    EXPECT_EQ(1, json_length(jobj));
    EXPECT_EQ(JT_INT, json_get(jobj, "A")->type);
    EXPECT_EQ(1, json_get(jobj, "A")->m_i64);
    EXPECT_EQ(NULL, json_get(jobj, "B"));
    EXPECT_EQ(NULL, json_get(jarr, "C"));

    /* Clean */
    json_clean(&jobj);
    json_clean(&jarr);
}

TEST(JsonObjectTest, SetNestedArray) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    union json_t jarr = JSON_ARRAY;
    json_append(&jarr, 1);
    json_append(&jarr, 2);

    /* Act */
    json_set(&j, "A", jarr);
    json_set(&j, "B", 3);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_ARRAY, json_get(j, "A")->type);
    EXPECT_EQ(2, json_length(*json_get(j, "A")));
    EXPECT_EQ(JT_INT, json_get(*json_get(j, "A"), 0)->type);
    EXPECT_EQ(JT_INT, json_get(*json_get(j, "A"), 1)->type);
    EXPECT_EQ(1, json_get(*json_get(j, "A"), 0)->m_i64);
    EXPECT_EQ(2, json_get(*json_get(j, "A"), 1)->m_i64);
    EXPECT_EQ(3, json_get(j, "B")->m_i64);

    /* Clean */
    json_clean(&j);
    json_clean(&jarr);
}

TEST(JsonObjectTest, DeleteNestedArray) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    union json_t jarr = JSON_ARRAY;
    json_append(&jarr, 1);
    json_append(&jarr, 2);
    json_set(&j, "A", jarr);
    json_set(&j, "B", 3);

    /* Act */
    json_delete(&j, "A");

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(1, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "B")->type);
    EXPECT_EQ(3, json_get(j, "B")->m_i64);

    /* Clean */
    json_clean(&j);
    json_clean(&jarr);
}

TEST(JsonObjectTest, SetNestedObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    union json_t jobj = JSON_OBJECT;
    json_set(&jobj, "A", 1);
    json_set(&jobj, "B", 2);

    /* Act */
    json_set(&j, "A", jobj);
    json_set(&j, "B", 3);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_OBJECT, json_get(j, "A")->type);
    EXPECT_EQ(2, json_length(*json_get(j, "A")));
    EXPECT_EQ(JT_INT, json_get(*json_get(j, "A"), "A")->type);
    EXPECT_EQ(JT_INT, json_get(*json_get(j, "A"), "B")->type);
    EXPECT_EQ(1, json_get(*json_get(j, "A"), "A")->m_i64);
    EXPECT_EQ(2, json_get(*json_get(j, "A"), "B")->m_i64);
    EXPECT_EQ(3, json_get(j, "B")->m_i64);

    /* Clean */
    json_clean(&j);
    json_clean(&jobj);
}

TEST(JsonObjectTest, DeleteNestedObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    union json_t jobj = JSON_OBJECT;
    json_set(&jobj, "A", 1);
    json_set(&jobj, "B", 2);
    json_set(&j, "C", jobj);
    json_set(&j, "D", 3);

    /* Act */
    json_delete(&j, "C");

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(1, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "D")->type);
    EXPECT_EQ(3, json_get(j, "D")->m_i64);

    /* Clean */
    json_clean(&j);
    json_clean(&jobj);
}

TEST(JsonObjectTest, JsonDupObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", 1);
    json_set(&j, "B", "2");

    /* Act */
    union json_t res = json_dup(j);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(JT_STRING, json_get(j, "B")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);
    EXPECT_STREQ("2", json_get(j, "B")->m_text);
    EXPECT_EQ(JT_OBJECT, res.type);
    EXPECT_EQ(2, json_length(res));
    EXPECT_EQ(JT_INT, json_get(res, "A")->type);
    EXPECT_EQ(JT_STRING, json_get(res, "B")->type);
    EXPECT_EQ(1, json_get(res, "A")->m_i64);
    EXPECT_STREQ("2", json_get(res, "B")->m_text);

    /* Clean */
    json_clean(&j);
    json_clean(&res);
}

TEST(JsonObjectTest, CleanObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", 1);
    json_set(&j, "B", 2);

    /* Act */
    json_clean(&j);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(0, json_length(j));
}

TEST(JsonObjectTest, CleanDupObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A",  1);
    json_set(&j, "B",  "2");

    /* Act */
    union json_t res = json_dup(j);
    json_clean(&j);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, res.type);
    EXPECT_EQ(2, json_length(res));
    EXPECT_EQ(JT_INT, json_get(res, "A")->type);
    EXPECT_EQ(JT_STRING, json_get(res, "B")->type);

    /* Clena */
    json_clean(&res);
}

TEST(JsonObjectTest, DumpsObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", JSON_INT(1));
    json_set(&j, "B", JSON_STRING("2"));

    /* Act */
    char *res = json_dumps(j, .indent = 2);

    /* Assert */
    EXPECT_STREQ("{\n  \"A\": 1, \n  \"B\": \"2\"\n}", res);

    /* Clean */
    free(res);
    json_clean(&j);
}

TEST(JsonObjectTest, DumpsDupNestedObject) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", JSON_INT(1));
    json_set(&j, "B", JSON_OBJECT);
    json_set(json_get(j, "B"), "C", JSON_STRING("2"));

    /* Act */
    union json_t res = json_dup(j);
    char *res_str = json_dumps(res, .indent = 2);

    /* Assert */
    EXPECT_STREQ("{\n  \"A\": 1, \n  \"B\": {\n    \"C\": \"2\"\n  }\n}", res_str);

    /* Clean */
    free(res_str);
    json_clean(&j);
    json_clean(&res);
}

TEST(JsonObjectTest, DumpsDupNestedArray) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", JSON_INT(1));
    json_set(&j, "B", JSON_ARRAY);
    json_append(json_get(j, "B"), JSON_INT(2));

    /* Act */
    union json_t res = json_dup(j);
    char *res_str = json_dumps(res, .indent = 2);

    /* Assert */
    EXPECT_STREQ("{\n  \"A\": 1, \n  \"B\": [\n    2\n  ]\n}", res_str);

    /* Clean */
    free(res_str);
    json_clean(&j);
    json_clean(&res);
}

TEST(JsonObjectTest, SetAgain) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    union json_t jobj = JSON_OBJECT;
    union json_t jarr = JSON_ARRAY;
    json_set(&jobj, "A", 1);
    json_set(&jobj, "B", 2);
    json_append(&jarr, 3);
    json_append(&jarr, 4);
    json_set(&j, "A", 1);
    json_set(&j, "B", 2);
    json_set(&j, "C", 3);
    json_set(&j, "D", 4);
    json_set(&j, "E", 5);
    json_set(&j, "F", 6);
    json_set(&j, "G", jobj);
    json_set(&j, "H", jarr);

    /* Act */
    json_set(&j, "A", 1.0);
    json_set(&j, "B", "2");
    json_set(&j, "C", JSON_ARRAY);
    json_set(&j, "D", JSON_OBJECT);
    json_set(&j, "E", jobj);
    json_set(&j, "F", jarr);
    json_set(&j, "G", JSON_FALSE);
    json_set(&j, "H", JSON_INT(-1));

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(8, json_length(j));
    EXPECT_EQ(JT_FLOAT, json_get(j, "A")->type);
    EXPECT_EQ(JT_STRING, json_get(j, "B")->type);
    EXPECT_EQ(JT_ARRAY, json_get(j, "C")->type);
    EXPECT_EQ(JT_OBJECT, json_get(j, "D")->type);
    EXPECT_EQ(JT_OBJECT, json_get(j, "E")->type);
    EXPECT_EQ(JT_ARRAY, json_get(j, "F")->type);
    EXPECT_EQ(JT_BOOL, json_get(j, "G")->type);
    EXPECT_EQ(JT_INT, json_get(j, "H")->type);
    EXPECT_EQ(1.0, json_get(j, "A")->m_f64);
    EXPECT_STREQ("2", json_get(j, "B")->m_text);
    EXPECT_EQ(0, json_length(*json_get(j, "C")));
    EXPECT_EQ(0, json_length(*json_get(j, "D")));
    EXPECT_EQ(2, json_length(*json_get(j, "E")));
    EXPECT_EQ(2, json_length(*json_get(j, "F")));
    EXPECT_FALSE(json_get(j, "G")->m_bool);
    EXPECT_EQ(-1, json_get(j, "H")->m_i64);
    EXPECT_EQ(1, json_get(*json_get(j, "E"), "A")->m_i64);
    EXPECT_EQ(2, json_get(*json_get(j, "E"), "B")->m_i64);
    EXPECT_EQ(3, json_get(*json_get(j, "F"), 0)->m_i64);
    EXPECT_EQ(4, json_get(*json_get(j, "F"), 1)->m_i64);

    /* Clean */
    json_clean(&j);
    json_clean(&jobj);
    json_clean(&jarr);
}

TEST(JsonObjectTest, SetEmptyToDelete) {
    /* Arrange */
    union json_t j = JSON_OBJECT;
    json_set(&j, "A", 1);
    json_set(&j, "B", 2);
    json_set(&j, "C", 3);
    json_set(&j, "D", 4);

    /* Act */
    json_set(&j, "B", JSON_DELETE);
    json_set(&j, "D", JSON_DELETE);

    /* Assert */
    EXPECT_EQ(JT_OBJECT, j.type);
    EXPECT_EQ(2, json_length(j));
    EXPECT_EQ(JT_INT, json_get(j, "A")->type);
    EXPECT_EQ(JT_INT, json_get(j, "C")->type);
    EXPECT_EQ(1, json_get(j, "A")->m_i64);
    EXPECT_EQ(3, json_get(j, "C")->m_i64);

    /* Clean */
    json_clean(&j);
}
