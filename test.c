#include "xprintf.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "float.h"


int total_errors = 0, total_warings = 0, total_tests = 0;


void test_error(int allow_to_fail, const char *format, const char *a, const char *b)
{
    total_tests++;
    if (strcmp(a, b) == 0)
    {
        printf("\033[0;32mTest passed...\033[0m\n");
        return;
    }

    if (allow_to_fail)
    {
        total_warings++;
        printf("\033[0;33mWaring: Test <%s> failed [allowed to fail]\033[0m\n", format);
        printf("xsprintf: [wrong]\n<%s>\nsprintf: [correct]\n<%s>\n", a, b);
        return;
    }
    total_errors++;

    printf("\033[0;31mError at test: <%s>\033[0m\n", format);
    printf("xsprintf: [wrong]\n<%s>\nsprintf: [correct]\n<%s>\n", a, b);
}



#define TEST(X, buf_size, format, ...) \
    { \
        char buf1[buf_size], buf2[buf_size]; \
        xsprintf(buf1, format __VA_OPT__(,) __VA_ARGS__); \
        sprintf(buf2, format __VA_OPT__(,) __VA_ARGS__); \
        test_error(X, format, buf1, buf2); \
    }
#define TEST_A(...) TEST(0, __VA_ARGS__)
#define TEST_B(...) TEST(1, __VA_ARGS__)

int main()
{    
    xprintf("<%lld>\n", 18446744073709551615ull);
    xprintf("<%lld>\n", 998244353ll);
    
    // xprintf("%.5000e\n", 123.456);
    // xprintf("%e\n", 1.100);
    // xprintf("%50e\n", 3.1415926/1000000000.0);
    // xprintf("%50e\n", 3.1415926);
    // xprintf("%50e\n", -1e-300);
    // xprintf("%50e\n", -1e-179);
    // xprintf("%.20e\n", -1e-179);
    // xprintf("%+50.e\n", 1e-179);
    // xprintf("%#+50.e\n", 1e-179);
    // xprintf("%-50.20eZOV\n", -1e-179);
    // xprintf("%e\n", 1e300);
    // xprintf("%e\n", DBL_MAX);
    // xprintf("%e\n", -DBL_MAX);
    // xprintf("%e\n", DBL_TRUE_MIN * 2);
    // xprintf("%e\n", DBL_TRUE_MIN * 4);
    // xprintf("%e\n", DBL_TRUE_MIN * 8);
    // xprintf("%e\n", DBL_TRUE_MIN * 10);
    
    xprintf("Hello %% %corld%c, |%-10s|\n", 'W', '!', "What?");

    // %c
    TEST_A(1024, "%c", 'Z')
    TEST_A(1024, "%c%c", 'A', 'B')
    TEST_A(1024, "aa%caa", 'Z')
    TEST_A(1024, "%caa", 'Z')
    TEST_A(1024, "aa%c", 'Z')
    TEST_A(1024, "aa%caa%caa", 'Z', 'Z')
    TEST_A(1024, "aa%caaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa%caa", 'Z', 'X')
    
    TEST_B(1024, "aa%0100caa", 'Z')
    TEST_B(1024, "aa%-0100caa", 'Z')
    TEST_B(1024, "aa%0-100caa", 'Z')

    // %%
    TEST_A(1024, "oo%%oo")

    // formats
    TEST_A(1024, "")
    TEST_A(1024, "ooo")
    TEST_A(1024, "o00000000000000000000000000000000000000000oo")
    TEST_A(1024, "%10c", 'Z')
    TEST_A(1024, "aa%10caa", 'Z')
    TEST_A(1024, "aa%100caa", 'Z')
    TEST_A(1024, "aa%*caa", 10, 'Z')
    TEST_A(1024, "aa%-100caa", 'Z')
    TEST_A(1024, "aa%-*caa", 10, 'Z')
    TEST_A(1024, "aa%*caa", -10, 'Z')

    // %s
    TEST_A(1024, "%s", "xyz")
    TEST_A(1024, "%s", "foooooooooooooooooooooooooooooooooooooooooooooooooooooooo")
    TEST_A(1024, "%s", "fooooooooooooooooooooooooooooooooooooooooooooooooooooooo000000000000000000000000000000000000o")
    TEST_A(1024, "%s", "fooooooooooooooooooooooooooooooooooooooooooooooooooooooo00000000000000000000000000000000000000000000000000000000000000000o")
    TEST_A(1024, "%20s", "foo")
    TEST_A(1024, "%20s", "")
    TEST_A(1024, "%-20s", "")
    TEST_A(1024, "%-20s", "foo")
    TEST_A(1024, "%*s", 20, "foo")
    TEST_A(1024, "%*s", -20, "foo")
    TEST_A(1024, "%.0s", "aboba")
    TEST_A(1024, "%10.0s", "aboba")
    TEST_A(1024, "%-10.0s", "aboba")
    TEST_A(1024, "%10.s", "aboba")
    TEST_A(1024, "%-10.s", "aboba")
    TEST_A(1024, "%.s", "aboba")
    TEST_A(1024, "%.s", (char *)NULL)
    TEST_A(1024, "%.0s", (char *)NULL)
    TEST_A(1024, "%10.0s", (char *)NULL)
    TEST_A(1024, "%-10.0s", (char *)NULL)
    TEST_A(1024, "%10.s", (char *)NULL)
    TEST_A(1024, "%-10.s", (char *)NULL)
    TEST_A(1024, "%.*s", 0, (char *)NULL)
    TEST_A(1024, "%.*s", 0, (char *)NULL)
    TEST_A(1024, "%10.*s", 0, (char *)NULL)
    TEST_A(1024, "%-10.*s", 0, (char *)NULL)
    TEST_A(1024, "%*.*s", 10, 0, (char *)NULL)
    TEST_A(1024, "%*.*s", 10, 0, (char *)NULL)
        
    TEST_B(1024, "aa%0100saa", "fooo")
    TEST_B(1024, "aa%-0100saa", "fopo")
    TEST_B(1024, "aa%0-100saa", "fopo")

    // %f
    TEST_A(1024, "%.300f", 0.0)
    TEST_A(1024, "%300.100f", 0.0)
    TEST_A(1024, "%.0f", 0.0)
    TEST_A(1024, "%-10.0f", 0.0)
    TEST_A(1024, "%#-10.0f", 0.0)
    TEST_A(1024, "%-#10.0f", 0.0)
    TEST_A(1024, "%0.300f", 0.0)
    TEST_A(1024, "%0300.100f", 0.0)
    TEST_A(1024, "%0.0f", 0.0)
    
    TEST_B(1024, "%0-10.0f", 0.0)
    TEST_B(1024, "%0#-10.0f", 0.0)
    TEST_B(1024, "%0-#10.0f", 0.0)

    // TODO: this tests will be A in future
    TEST_B(1024, "%f", 1.0)
    TEST_B(1024, "%.0f", 1.0)


    // %e
    TEST_A(1024, "%e", 1e300)
    TEST_A(1024, "%.4e", -1e300)
    TEST_A(1024, "%.e", -1e300)
    TEST_A(1024, "%#.e", -1e300)
    TEST_A(1024, "%+#.e", 1e300)
    TEST_A(1024, "%#-100.e", 1e300)
    


    printf("\n\n");
    if (total_errors == 0 && total_warings == 0)
    {
        printf("\033[0;32mAll %d tests passed!\033[0m\n", total_tests);
        return 0;
    }
    else if (total_errors == 0)
    {
        printf("\033[0;33mFinished with warings: from %d tests, %d warings. [no errors]\033[0m\n", total_tests, total_warings);
    }
    else
    {
        printf("\033[0;31mERROR: from %d tests, %d failed, %d warings.\033[0m\n", total_tests, total_errors, total_warings);
        return 1;
    }
}
