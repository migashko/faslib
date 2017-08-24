#ifndef FAS_TESTING_TAGS_HPP
#define FAS_TESTING_TAGS_HPP

namespace fas{ namespace testing{

struct _units_;
struct _suite_stub_; // заглушка

struct _stop_{};
struct _nothing_{};
struct _flush_{};

// suite без ошибок
struct _passed_{};
struct _red_passed_{};
// unit без ошибок
struct _ok_{};
// пропуск unit из-за фатальной ошибки в suit
struct _skip_{};
// ошибка unit'а
struct _fail_{};
// критическия ошибка unit'а, прекращаем все
struct _fatal_{};
// пользовательсокое исключение в unit
struct _except_{};
// запуск unit
struct _run_{};
// пользовательский warning
struct _warning_{};
// пользовательское сообщение
struct _message_{};
// пользовательское сообщение об ошибке
struct _error_{};
//
struct _suite_beg_{};
//
struct _suite_end_{};

struct _unit_fail_res_{};
struct _suite_fail_res_{};
struct _test_fail_res_{};



}}

#endif
