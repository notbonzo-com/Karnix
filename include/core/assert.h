#ifndef _ASSERT_H
#define _ASSERT_H

[[noreturn]] void _assert_failed(int line, const char* function, const char* expression, const char* message);

#ifdef _DEBUG
#define ASSERT(x, msg) if((x)) {} else _assert_failed(__LINE__, __func__, #x, msg)
#else
#define ASSERT(x)
#endif
#define ASSERTF(x, msg) if((x)) {} else { _assert_failed(__LINE__, __func__, #x, msg); }

#endif // _ASSERT_H