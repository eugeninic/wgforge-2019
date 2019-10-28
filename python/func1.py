﻿# Заполните код преведенных ниже функций. Функция main() уже настроена
# для вызова функций с несколькими различными параметрами,
# и выводит 'OK' в случае, если вызов функции корректен.
# Начальный код каждой функции содержит 'return'
# и является просто заготовкой для вашего кода.



# A. Сумма чисел кратных 3 и 5
# Если выписать все натуральные числа меньше 10, кратные 3 или 5, 
# то получим 3, 5, 6 и 9. Сумма этих чисел - 23.
# Найдите сумму всех чисел меньше 1000 кратных 3 или 5.
# Примечание: попробуйте записать решение при помощи генератора
# и встроенной фукнции sum
def multiples():
    return sum(xrange(3, 1000, 3)) + sum(xrange(5, 1000, 5)) - sum(xrange(15, 1000, 15))


# B. Сумма четных чисел ряда Фибоначчи
# Каждый следующий элемент ряда Фибоначчи получается при сложении 
# двух предыдущих. Начиная с 1 и 2, первые 10 элементов будут:
# 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
# Найдите сумму всех элементов ряда Фибоначчи, каждый их которых
# является четным числом и не превышает четырех миллионов.
def fibonacci():
    def num_fib():
        n1, n2 = 0, 2
        while n2 <= 4*1e6:
            yield n2
            n1, n2 = n2, n1 + 4*n2

    return sum(num_fib())


# С. Самый большой палиндром
# Число-палиндром с обеих сторон (справа и слева) читается одинаково. 
# Самое большое число-палиндром, полученное произведением двух двухзначных чисел – 9009 = 91 * 99.
# Найдите самый большой палиндром, полученный произведением двух трёхзначных чисел.
def palindrome():
    ans = -float('inf')
    for i in range(999, 99, -1):
        if i * 999 < ans:
            break
        for j in range(999, i - 1, -1):
            num = i * j
            if str(num) == str(num)[::-1]:
                ans = max(ans, num)
    return ans
#     return 906609 # the best solution


# D. Генератор-преобразователь
# Напишите функцию transform, которая принимает на вход 2 функции, seq_gen и func,
# возвращает функцию-генератор, которая берет следующее значение из seq_gen и пропускает его через функцию func.
def transform(seq_gen, func):
    def gen():
        for val in seq_gen():
            yield func(val)

    return gen


# Простая функция test() используется в main() для вывода
# сравнения того, что возвращает с функция с тем, что она должна возвращать.
def test(got, expected):
    if got == expected:
        prefix = ' OK '
    else:
        prefix = '  X '
    print('%s Получено: %s | Ожидалось: %s' % (prefix, repr(got), repr(expected)))


# Вызывает фунции выше с тестовыми параметрами.
def main():
    print('Сумма чисел кратных 3 и 5')
    test(multiples(), 233168)

    print()
    print('Сумма четных чисел ряда Фибоначчи')
    test(fibonacci(), 4613732)

    print()
    print('Самый большой палиндром')
    test(palindrome(), 906609)

    print()
    print('Генератор-преобразователь')
    test(list(transform(lambda: xrange(5), lambda x: x**2)()), [0, 1, 4, 9, 16])

if __name__ == '__main__':
    main()
