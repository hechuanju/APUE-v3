#include <stdio.h>
#include <setjmp.h>

static jmp_buf long_jmp_buf;

static void func2()
{
    printf("func2 begin\n");
    longjmp(long_jmp_buf, 1);
    printf("func2 end\n");
}

static void func1()
{
    printf("func1\n");
    func2();
}

int main(int argc, char const *argv[])
{
    if (setjmp(long_jmp_buf) == 0) {
        printf("setjump\n");
        func1();
    } else {
        printf("longjmp\n");
    }
    return 0;
}
