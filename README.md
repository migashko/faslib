# faslib

Библиотека faslib предлагает новый способ модульной разработки программного обеспечения,
называемый аспекто-ориентированным, используя исключительно конструкции языка C++.

faslib тестировалась на следующих компиляторах:

* VC10
* g++ 3.3, g++ 4.4, g++ 4.6, g++ 4.7
* MinGW

## Установка и настройка

Компиляция не требуется, но необходимо конфигурирование с помощью cmake
```
git clone git://github.com/migashko/faslib.github
cd faslib
mkdir build
cd build
cmake ..
```

Для компиляции примеров и тестов
```
make
```

или по отдельности
```
make tests
make examples
make tutorial
```

для запуска тестов
```
ctest
```

## Введение

Основная идея - дать разработчику возможность разрабатывать такие классы, в которых потенциальный пользователь,
при необходимости, мог бы заменить тот или иной функционал с минимумом издержек.

В качестве примера рассмотрим простой класс:

```cpp
class foo1
{
public:
  void method1() { std::cout << "method-1.1" << std::endl; }
  void method2() { std::cout << "method-1.2" << std::endl; }
  void method3() { std::cout << "method-1.3" << std::endl; }
};
```

Предположим требуется предоставить пользователю возможность заменить функционал любого методов этого класса.
Использовать для этого полиморфизм - не лучшая идея, классические стратегии слишком накладно, шаблонные стратегии
неудобно. Более развернутые примеры (в том числе и с этими вариантами реализации) вы можете найти в [tutorial/aop](https://github.com/migashko/faslib/tree/master/tutorial/aop).

Для наглядности изобразим этот класс на картинке в виде монолитного блока:

![foo](https://github.com/migashko/faslib/blob/gh-pages/images/fas/image00.png?raw=true)

Для демонстрации возможностей разработаем класс foo2 с аналогичным функционалом, но используя концепции АОП.
Сначала разобьем его на составляющие, выделив каждый метод в отдельные сущности которые в faslib называются адвайс-классами:

![ad_method](https://github.com/migashko/faslib/blob/gh-pages/images/fas/image01.png?raw=true)

```cpp
struct ad_method1
{
  template<typename T>
  void operator()(T&) { std::cout << "method-2.1" << std::endl; }
};

struct ad_method2
{
  template<typename T>
  void operator()(T&) { std::cout << "method-2.2" << std::endl; }
};

struct ad_method3
{
  template<typename T>
  void operator()(T&) { std::cout << "method-2.3" << std::endl; }
};
```

Каких либо особых требований к адвайс-классам не предъявляется, но использование определенных правил
при разработке адвайс-классов существенно облегчит жизнь и вам и потенциальным пользователям. Использование перегруженного
оператора () с первым шаблонным параметром, в который передается контекст вызова (в данном случае это ссылка на foo2) является
хорошей практикой, даже если в конкретном адвайс-классе он не нужен. Дело в том, что ссылка на контекст может очень понадобиться
пользователю, который решит заменить ваш адвайс своим. Префикс “ad_” подскажет пользователю, что он имеет дело с адвайс-классом.

Далее для каждого адвайс-класса необходимо создать тег, по которому мы сможем обращаться к нему. Методов у нас три поэтому и
тегов нам понадобиться тоже как минимум три:

```cpp
struct _method1_;
struct _method2_;
struct _method3_;
```

Использование знака “_” для обрамления имени тега, чертовски удобная штука.
Следующим этапом необходимо связать теги и адвайс-классы, создав таким образом собственно адвайсы:

![advices](https://github.com/migashko/faslib/blob/gh-pages/images/fas/image02.png?raw=true)

```cpp
typedef fas::advice<_method1_, ad_method1> method1_advice;
typedef fas::advice<_method2_, ad_method2> method2_advice;
typedef fas::advice<_method3_, ad_method3> method3_advice;
```

Далее, необходимо объединить  разрозненные адвайсы в список типов:

![advice list](https://github.com/migashko/faslib/blob/gh-pages/images/fas/image03.png?raw=true)

```cpp
typedef fas::type_list_n<
  method1_advice,
  method2_advice,
  method3_advice
>::type advice_list;
```

Cформируем аспект foo2_aspect:

![foo2_aspect](https://github.com/migashko/faslib/blob/gh-pages/images/fas/image04.png?raw=true)

```cpp
struct foo2_aspect: fas::aspect< advice_list >{};
```

Ну и наконец разработаем сам аспектный класс foo2, в который внедрим аспект foo2_aspect:

```cpp
template<typename A = fas::aspect<> >
class foo2
  : public fas::aspect_class<A, foo2_aspect>
{
public:
  void method1() { this->get_aspect().template get<_method1_>()( *this); }
  void method2() { this->get_aspect().template get<_method2_>()( *this); }
  void method3() { this->get_aspect().template get<_method3_>()( *this); }
};
```
В реализации методов делегируем вызов необходимому адвайсу. Но в большинстве случаев компилятор выполнит inline подстановку.

Использовать аспектный класс foo2<> не сложнее обычного foo1:

```cpp
  foo2<> f2;
  f2.method1();
  f2.method2();
  f2.method3();
```

Класс   foo2<> изобразим следующим образом:

![foo2_aspect](https://github.com/migashko/faslib/blob/gh-pages/images/fas/image05.png?raw=true)

Полный пример [здесь](https://github.com/migashko/faslib/blob/master/examples/aop/foo.cpp)
