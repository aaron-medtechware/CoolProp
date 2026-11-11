/* N2O-only embedded build: satisfy libstdc++/newlib wchar refs that
 * otherwise come from unused locale/wstring paths. */
#include <wchar.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef putwc
#    undef putwc
#endif
#ifdef getwc
#    undef getwc
#endif
#ifdef ungetwc
#    undef ungetwc
#endif

wint_t putwc(wchar_t wc, FILE* stream) {
    (void)wc;
    (void)stream;
    return WEOF;
}

wint_t getwc(FILE* stream) {
    (void)stream;
    return WEOF;
}

wint_t ungetwc(wint_t wc, FILE* stream) {
    (void)wc;
    (void)stream;
    return WEOF;
}

int swprintf(wchar_t* s, size_t n, const wchar_t* format, ...) {
    (void)s;
    (void)n;
    (void)format;
    return -1;
}
