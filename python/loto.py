# -*- coding: utf-8 -*-w
"""Лото

Правила игры в лото.

Игра ведется с помощью специальных карточек, на которых отмечены числа, 
и фишек (бочонков) с цифрами.

Количество бочонков — 90 штук (с цифрами от 1 до 90).

Каждая карточка содержит 3 строки по 9 клеток. В каждой строке по 5 случайных цифр, 
расположенных по возрастанию. Все цифры в карточке уникальны. Пример карточки:

--------------------------
    9 43 62          74 90
 2    27    75 78    82
   41 56 63     76      86 
--------------------------

В игре 2 игрока: пользователь и компьютер. Каждому в начале выдается 
случайная карточка. 

Каждый ход выбирается один случайный бочонок и выводится на экран.
Также выводятся карточка игрока и карточка компьютера.

Пользователю предлагается зачеркнуть цифру на карточке или продолжить.
Если игрок выбрал "зачеркнуть":
	Если цифра есть на карточке - она зачеркивается и игра продолжается.
	Если цифры на карточке нет - игрок проигрывает и игра завершается.
Если игрок выбрал "продолжить":
	Если цифра есть на карточке - игрок проигрывает и игра завершается.
	Если цифры на карточке нет - игра продолжается.
	
Побеждает тот, кто первый закроет все числа на своей карточке.

Пример одного хода:

Новый бочонок: 70 (осталось 76)
------ Ваша карточка -----
 6  7          49    57 58
   14 26     -    78    85
23 33    38    48    71   
--------------------------
-- Карточка компьютера ---
 7 87     - 14    11      
      16 49    55 88    77    
   15 20     -       76  -
--------------------------
Зачеркнуть цифру? (y/n)

Подсказка: каждый следующий случайный бочонок из мешка удобно получать 
с помощью функции-генератора.

Подсказка: для работы с псевдослучайными числами удобно использовать 
модуль random: http://docs.python.org/2/library/random.html

"""
from __future__ import print_function
import random
import os


class Card(object):
   def __init__(self):
      elements = random.sample(range(1, 91), 15)
      self._rows = [
         elements[5 * i:5 * (i + 1)] for i in range(3)
      ]
      self._positions = {elements[i]: (i / 5, i % 5) for i in range(len(elements))}

   def exists(self, number):
      if number < 1 or number > 90:
         raise ValueError('Numbers on card must be in range [1, 90]')
      if number in self._positions:
         return True
      return False

   def delete_num(self, number):
      i, j = self._positions[number]
      self._rows[i][j] = 'X'
      del self._positions[number]

   def __len__(self):
      return len(self._positions)

   def __str__(self):
      res = '-' * (4 + 3 * 5) + '\n'
      res += '\n'.join(' '.join('{:>3}'.format(num) for num in row) for row in self._rows)
      res += '\n' + '-' * (4 + 3 * 5)
      return res


class Game(object):
   def __init__(self):
      self._player_card = Card()
      self._computer_card = Card()
      self._numbers = range(1, 91)

   def start(self):
         while self._player_card and self._computer_card:
            # clear console
            os.system('clear')
            
            curr_number = random.choice(self._numbers)
            self._numbers.remove(curr_number)
            self._print_barrel(curr_number)
            self._print_cards()
            if self._computer_card.exists(curr_number):
               self._computer_card.delete_num(curr_number)
            # input 
            
            user_input = self._user_input()
            if not self._user_move_correctness(user_input, curr_number):
               break
            
   def _user_move_correctness(self, user_input, curr_number):
      if user_input == 'y':
         if self._player_card.exists(curr_number):
            self._player_card.delete_num(curr_number)
         else:
            print('Such barrel doesn\'t exists in your card')
            self._gameover()
            return False
      else:
         if self._player_card.exists(curr_number):
            print('Such barrel exists in your card')
            self._gameover()
            return False
      return True

   @staticmethod
   def _user_input():
      while True:
         player_input = raw_input('Cross barrel ? (y / n) : ')
         if player_input in {'y', 'n', 'e'}:
            if player_input == 'e':
               print('Exiting')
               return
            break
         print("Input incorrect. Enter 'y', 'n' or 'e'. 'e' - to exit")
      return player_input

   @staticmethod
   def _print_barrel(number):
      print('Current barrel is {}'.format(number))
      print()

   def _print_cards(self):
      print(
         'Cards:', 
         'Player:',
         self._player_card,
         '\nComputer:',
         self._computer_card,
         sep='\n'
      )

   def _gameover(self):
      if not self._player_card and not self._computer_card:
         print('Draw')
      elif not self._player_card:
         print('You win!')
      else:
         print('Computer win!')


def main():
   game = Game()
   game.start()


if __name__ == '__main__':
   main()