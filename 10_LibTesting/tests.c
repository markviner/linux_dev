#include <check.h>
#include "growable_buf.h"

START_TEST(test_growable_buf_init) {
    growable_buf buf;
    growable_buf_init(&buf);
    ck_assert_int_eq(buf.len, 0);
    ck_assert_int_eq(buf.cap, GROWABLE_BUF_INIT);
}
END_TEST

START_TEST(test_growable_buf_add) {
    growable_buf buf;
    growable_buf_init(&buf);
    growable_buf_add(&buf, 'a');
    ck_assert_int_eq(buf.len, 1);
    ck_assert_int_eq(buf.buf[0], 'a');
}
END_TEST

START_TEST(test_growable_buf_free) {
    growable_buf buf;
    growable_buf_init(&buf);
    growable_buf_add(&buf, 'b');
    growable_buf_free(&buf);
    ck_assert_ptr_eq(buf.buf, NULL);
    ck_assert_int_eq(buf.len, 0);
    ck_assert_int_eq(buf.cap, 0);
}
END_TEST

Suite *growable_buf_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("GrowableBuf");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_growable_buf_init);
    tcase_add_test(tc_core, test_growable_buf_add);
    tcase_add_test(tc_core, test_growable_buf_free);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = growable_buf_suite();
    sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
