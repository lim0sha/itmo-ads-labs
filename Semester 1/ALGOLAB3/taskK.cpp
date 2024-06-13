#include <iostream>

using namespace std;

struct Node {
  int data;
  Node *prev = NULL;
  Node *next = NULL;
};

int Cycle(Node *head, Node &MemoryPoint) {
  // запускаем два указателя
  Node *slow = head;
  Node *fast = head;
  if (fast == NULL or fast->next == NULL) {
    return -1;
  }
  // Поскольку fast итератор движется в два раза быстрее,
  // чем slow, то один раз fast будет первым, кто войдет в цикл
  // После этого slow войдет в цикл
  fast = fast->next->next;
  slow = slow->next;
  // На этом этапе мы можем быть уверены, что fast догонит slow, пройдя не более
  // m (длинна списка) шагов, потому что он движется быстрее. Прежде чем это произойдет, у нас будет несколько случаев

  // Если они встречаются у нас должен быть цикл, потому что fast вернулся, чтобы встретить slow
  // если fast это на один шаг раньше slow, то на следующем шаге они встретятся. Следовательно, у нас есть цикл
  // если fast это два шага до slow, то на следующем шаге у fast будет один шаг до slow, что аналогично случаю 2

  while (fast != slow) {
    if (fast == NULL or fast->next == NULL) {
      return -1;
    }
    fast = fast->next->next;
    slow = slow->next;
  }
  if (head == head->next) {
    return -1;
  }
  // поскольку fast перемещается на два шага вперед,
  // расстояние между обоими итераторами будет уменьшаться на один шаг каждый раз,
  // пока они не встретятся.
  MemoryPoint = *fast;
  return 1;
}
int main() {

  int n;
  cin >> n;
  int temp;
  int i;
  i = 0;
  Node array[n];
  while (cin >> temp) {
    array[i].next = &array[temp - 1];
    i += 1;
  }
  Node Temp_pos;
  int way;
  way = 0;
  for (int j = 0; j < n; j++) {
    if (Cycle(&array[j], Temp_pos) == 1) {
      // если есть цикл, то идём пока не дойдем в исходную точку и накапливаем длину
      Node *newNode = &Temp_pos;
      // минимальная длина
      way += 1;
      newNode = newNode->next;
      while (newNode->next != Temp_pos.next) {
        way += 1;
        newNode = newNode->next;
      }
      break;
    }
  }
  if (way != 0) {
    cout << way;
  } else {
    cout << "-1";
  }
}