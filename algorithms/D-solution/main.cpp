#include <iostream>
#include <vector>
#include "min_queue.h"

using namespace std;

const int INF = 1e9;

// главная идея решения задачи
// использовать динамическое программирование от двух параметров
// 1. текущий интервал
// 2. количество часов, которое отработала первая девушка, с учётом того, что последней работала она
//
// при решении задачи понадобится 3 массива размера n + 1
//
// моё решение достаточно сложное, интересно узнать авторское решение
//
// суть решения:
// 1. заметим, что на несменных интервалах ничего не происходит,
// т.е., зная значения на предыдущем времени, можно сдвинуть их
// и получить новый слой, а сдвинутые значения заполнить бесконечностями,
// т.к. они невозможны
// 2. зная значения на начале сменного интервала, можно найти значения на конце этого интервала,
// не проходя все значения в нём

// итоговая сложность O(kn)
// но получилась достаточно большая константа из-за очереди с минимумом
// её можно заменить другим алгоритмом поиска минимума в скользящем окне


int main() {
  int n, k;
  cin >> n >> k;
  vector<pair<int, int>> intervals(k);
  for (int i = 0; i < k; ++i) {
    int start, end;
    cin >> start >> end;
    intervals[i] = make_pair(start, end);
  }

  // смена в момент времени 2 * n бесполезна
  if (intervals.back().second == 2 * n) {
    if (intervals.back().first == 2 *n) {
      intervals.pop_back();
    } else {
      intervals.back().second = 2 * n - 1;
    }
  }

  vector<int> prev_t(n + 1);
  vector<int> curr_l(n + 1);
  vector<int> curr_r(n + 1);
  int prev = 0;

  for (auto [l, r] : intervals) {

    // shift values on static interval
    for (int i = 1; i <= l - prev; i++) {
      curr_l[i] = INF;
    }
    // fill values from last computed t
    for (int i = l - prev + 1; i < min(l, n + 1); i++) {
      curr_l[i] = prev_t[i - (l - prev)];
    }

    curr_r[0] = 0;
    if (l <= n)
      curr_l[l] = 0;

    for (int i = 1; i <= min(r - l + 1, n); i++) {
      curr_r[i] = 1;
    }

    curr_r[0] = 0;
    if (r + 1 <= n)
      curr_r[r + 1] = 0;

    // sliding window for find minimal value
    // MinQueue.min() return max_value, if queue is empty
    MinQueue<int> left_to_right(INF);
    MinQueue<int> right_to_left(INF);

    for (int i = 2; i < r - l + 2; i++) {
      left_to_right.push(i <= min(l, n)? curr_l[i] + 2 : INF);
      right_to_left.push(l - i == 0 ? 2 :
                         0 < l - i && l - i <= min(l, n) ? curr_l[l - i] + 1 : INF);
    }

    for (int i = r - l + 2; i < min(r + 1, n + 1); i++) {
      int r1, r2, r3, r4;
      int second_girl_work = r + 1 - i; // время, которая должна обработать вторая девочка
      r1 = l - second_girl_work <= min(n, l) ? curr_l[l - second_girl_work] : INF; // когда первая девочка может продолжить работать
      r2 = second_girl_work <= min(n, l) ? curr_l[second_girl_work] + 1 : INF; // когда первая девочка может поменяться со второй
      r3 = left_to_right.min();
      r4 = right_to_left.min();
      curr_r[i] = min(min(r1, r2), min(r3, r4));

      if (l < r) {
        left_to_right.pop();
        right_to_left.pop();
      }
      left_to_right.push(i <= min(l, n) ? curr_l[i] + 2 : INF);
      right_to_left.push(l - i == 0 ? 2 :
                         0 < l - i && l - i <= min(l, n) ? curr_l[l - i] + 1 : INF);
    }
    prev = r + 1;
    prev_t.assign(curr_r.begin(), curr_r.end());
  }

  int ans = n - (2 *n - prev) > 0 ? prev_t[n - (2 * n - prev)] : INF;

  if (ans == INF) {
    cout << "NO";
  } else {
    cout << "YES" << endl << ans;
  }

  return 0;
}