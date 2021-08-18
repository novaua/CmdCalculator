# Basic Expression Calculator
Command line expression calculator written using C++17 MSVC 2019. Accepted operations are '+ - * ^' and parenthesis.

Interactive usage example in Debug mode:

```
C:\projects\ExprCalculator\x64\Debug>ExprCalculator.exe
Enter expression ('e' or enter to exit)
3 + 3 * (44 + 5)
3 3 44 5 + * +
150
Enter expression ('e' or enter to exit)
2^2
2 2 ^
4
```

Batch usage example:

```
C:\projects\ExprCalculator\x64\Debug>ExprCalculator.exe 2+2*2+1
7
```
Known limitations/issues
Unary minus is not supported
Grouping of power operation is from lef to right i.e. 2^3^2 == 2^(3^2) ==> 512
