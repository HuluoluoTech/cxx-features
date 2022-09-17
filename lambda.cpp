#include <iostream>
#include <functional>
#include <type_traits>

template<typename Callable>
void CallWith(Callable&& fn)
{
    // std::is_nothrow_invocable_v to check if the given callable object is marked with noexcept
    if constexpr(std::is_nothrow_invocable_v<Callable, int>)
    {
        std::cout << "with noexcept." << "\n";
        fn(10);
    }
    else
    {
        std::cout << "Calling normally." << "\n";
        fn(10);
    }
}

template < class... Ts> struct overloaded : Ts... { using Ts:: operator ()...; };
template < class... Ts> overloaded(Ts...) -> overloaded< Ts...> ;

/**
 * Lambda in C++17
 * - constexpr lambda
 *   capture of *this
 */
void _In_Cxx17()
{
    // check if a callable object is marked with noexcept
    int x{10};
    const auto lam = [&x](int y) noexcept { x+=y; };
    CallWith(lam);

    // overload
    const auto overs = overloaded 
    {
        [](const int& i) { std::cout << "int: " << i << "\n"; },
        [](const float& f) { std::cout << "float: " << f << "\n"; }
    };
    overs(3);
}

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

    // recursive lambda
    const auto factorial = [](int n) noexcept 
    {
        const auto f_impl = [](int n, const auto& impl) noexcept -> int 
        {
            return n > 1 ? n * impl(n - 1, impl) : 1;
        };  

        return f_impl(n, f_impl);
    };
    auto factorial_res = factorial(5);
    std::cout << "factorial_res : " << factorial_res << std::endl;
}

int main()
{
    _In_Cxx17();

    return 0;

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
