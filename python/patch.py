# -*- coding: utf-8 -*-
from functools import wraps
'''
Написать декоратор реализующий подмену аттрибутов модуля.
После работы целевой функции вернуть стандартное поведение.
target - строка вида 'модуль.аттрибут'
obj - подменяющий объект
'''
def epatch(target, obj):
    def decorator(func):
        def wrapper(*args, **kwargs):
            module, attr = target.split('.', 1)
            m = __import__(module)
            old_attr = getattr(m, attr)
            setattr(m, attr, obj)
            ans = func(*args, **kwargs)
            setattr(m, attr, old_attr)
            return ans
        return wrapper 
    return decorator



def cock(res='KO-KO-KO'):
    text = r''' _%s_
< %s >
 -%s-
    \
     \  /\/\
       \   /
       |  0 >>
       |___|
 __((_<|   |
(          |
(__________)
   |      |
   |      |
   /\     /\ '''

    return text % ('_'*len(res), res, '-'*len(res))


def test(got, expected):
    if got == expected:
        prefix = ' OK '
    else:
        prefix = '  X '
    print(u'%s Получено: %s | Ожидалось: %s' % (prefix, repr(got), repr(expected)))

if __name__ == '__main__':
    @epatch('os.getcwd', cock)
    def func():
        from os import getcwd
        return getcwd()
    test(func(), cock())



