#include <iostream>
#include <functional>

/**
 *
 * Lambda in C++14
 * - Captures with an initialiser
 * - Generic lambdas
 *   Default parameters for lambdas
 *   Return type as auto
 *
 */
void _In_Cxx14()
{
    // Default parameters for lambda
    const auto lam = [](int a = 10) { std::cout << a << "\n"; };
    lam();
    lam(100);

    // auto return
    auto foo = [](int x)
    {
        if (x < 0) return x * 1.1f;//float
        else       return x * 3.1f; //如果不加 f, 则是 double 类型
    };
    auto res = foo(3);
    std::cout << "res : " << res << "\n";

    // capture with an initialiser
    int x = 1;
    int y = 2;
    const auto bar = [z = x + y] { std::cout << z << "\n"; };
    x = 0;
    y = 0;
    bar();
}

int main()
{
    _In_Cxx14();

    return 0;

    int x = 1;

    // Syntax of Lambda expression
    // [] () specifiers exception attr -> ret { /* code */ }

    // 1. the simplest lambda
    [] {};

    // 2. with params
    [](float f, int a) { return a*f; };

    // 3. with return type
    [](int a) -> int { return a * 1; };

    // 4. additional specifiers: mutable / noexcept
    [](int a, int b) mutable { return a < b; };
    [](int a, int b) mutable noexcept { return a < b; };

    // 5. optional ()
    []() mutable {};
    []() noexcept {}; // () required before mutable / noexcept

    const auto myLambda = [](int a) noexcept -> double {
        return 2.0 * a;
    };

    const std::function<double(int)> myFunc = [](int a) noexcept -> double { return 2.0 * a; };

    std::cout << "sizeof(myLambda) = " << sizeof(myLambda) << std::endl;
    std::cout << "sizeof(myFunc)   = " << sizeof(myFunc) << std::endl;

    const auto lambd1 = [x](int a) -> float
    {
        return 2.0 * a;
    };
    
    std::cout << "sizeof(lambd1)   = " << sizeof(lambd1) << std::endl;
    return 0;
}
