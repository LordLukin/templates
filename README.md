# C++ Templates

In C++03 we could have template classes and template functions. From C++11 we can have also template variables, but they are really barely used, so we will not talk about them.
Templates are used to avoid code duplication.

## Template functions

Let's assume that we have below function:

```
int add(int first, int second)
{
	return first + second;
}
```

If we want to have a function that takes doubles as well, we need to wrtie:

```
double add(double first, double second)
{
	return first + second;
}
```

And if we want funcion that can take complex numbers or any other we would need to write:

```
std::complex<int> add(std::complex<int> first, std::complex<int> second)
{
	return first + second;
}
```

You can see that here we already used templates. `std::complex` is a template class, but now we are talking about template functions, so let me introduce template classes later.
You can easily see that we have a code duplication here. Instead of writing so many functions we can have only one - template function:

```
template <typename Type>
Type add(Type first, Type second)
{
	return first + second;
}
```

Instead of `Type` you can have any name as you wish, typically you'll see just `T` as a typename, but it's better to have a longer name than only one character, especially when where are more than only one template types.
If you want not to use this functions you can do it like this:

```
auto resultI = add<int>(4, 5);  // resultI type is int
auto resultD = add<double>(4.0, 5.0); // resultD type is double
auto resultC = add<std::complex<int>>({1, 2}, {2, 3);  // resultC type is std::complex<int>
```

You can play with the code here: https://ideone.com/NU0L8k

But in C++ there is something called function template types deduction. It means that you can skip this part with angled braces <> and write it like here:

```
auto resultI = add(4, 5);  // resultI type is int
auto resultD = add(4.0, 5.0);  // resultD type is double
auto resultC = add({1, 2}, {2, 3});  // error, does not compile
```

resultC will not compile, because in this case compiler will not know what is the type of {1, 2} or {2, 3}. Unfortunately here we need to type it explicitly:

```
auto resultC = add(std::complex<int>{1, 2}, std::complex<int>{2, 3});
```
or like above
```
auto resultC = add<std::complex<int>>({1, 2}, {2, 3);
```

---
**Exercise**
Write a function which create `std::complex` number from two provided numbers. If the types of numbers are different, it should created `std::complex` of the first parameter. Usage:
```
std::complex<int> a = makeComplex(4, 5);
std::complex<double> b = makeComplex(3.0, 2.0);
std::complex<int> c = makeComplex(1, 5.0);
```
---

The compiler itself deduce which template function parameters should be use. However if you write the code like this:

```
auto resultC = add(4, 5.0);  // error: int + double
```

We will have a compilation error. Compiler will not deduce proper parameter, because our template function takes only one type and both parameters must be of the same type. We can fix this by adding a new version of template of add function:

```
template <typename TypeA, typename TypeB>
TypeA add(TypeA first, TypeB second)
{
	return first + second;
}
```

Now the code should work:

```
auto resultC = add(4, 5.0);  // resultC type is int
```

The output type is the same as first argument type, because it was defined in template function above as `TypeA`.
Generally you can freely use template types inside functions, for example you can create new variables of provided types:

```
#include <typeinfo>

template <class T>
void doNothing()
{
	T value;
	std::cout << "Type: " << typeid(value).name() << std::endl;
}
```

You can use `typeid().name()` to print variable type. You need to include `typeinfo` header for this. You can also see that instead of `typename` keyword, `class` keyword can be used. They are interchangable.
In this case if you want to use doNothing function without providing explicit templates parameters, the code will not compile:

```
int main() {
	doNothing();
	return 0;
}
```

```
prog.cpp: In function ‘int main()’:
prog.cpp:15:12: error: no matching function for call to ‘doNothing()’
  doNothing();
            ^
prog.cpp:7:6: note: candidate: template<class T> void doNothing()
 void doNothing()
      ^~~~~~~~~
prog.cpp:7:6: note:   template argument deduction/substitution failed:
prog.cpp:15:12: note:   couldn't deduce template parameter ‘T’
  doNothing();
```

The compiler cannot deduce template parameter, because the function does not take any parameters. You need to provide the type explicitly:

```
int main() {
	doNothing<int>();
	return 0;
}
```

or like this:

```
int main() {
	doNothing<std::vector<char>>();
	return 0;
}
```

You can play with the code here: https://ideone.com/oZZybw


## Template classes

Template classes are as well used to avoid code duplication, but also you can have some so called metaprograms created with them.
Simple template class and it's usage look like this:

```
#include <iostream>
using namespace std;

template <typename T>
class SomeClass
{
public:
    T getValue() { return value; }
private:
    T value;
};

int main() {
	SomeClass<int> sc;
	std::cout << sc.getValue() << std::endl;
	return 0;
}
```

Template classes are heavily used in STL. For example std::vector, std::list and every other container is a template class and if you want to use them you do it like here:

```
std::vector<int> v = {1, 2, 3};
std::list<char> l{'c', 'd', 'b'};
```

---
**Exercise**
Write a template class which create an _overengineered_ `std::map` :) It should hold 2 std::vectors inside with the same size, each with different types. Usage should look like this
```
VectorMap<int, char> map;
map.insert(1, 'c');
map[1] = 'e';  // replaces value under 1
std::cout << map[1];  // prints 'e'
map.at(2); // throw std::out_of_range
```
First vector should hold keys, the other one values. Elements at the same position in both vectors should create a pair like 1 and 'c' above. Try to implement as much of `std::map` interface as possible, at least the mentioned above `insert`, `operator[]`, `at` - http://en.cppreference.com/w/cpp/container/map

---

## Advanced topic: Variadic Templates
