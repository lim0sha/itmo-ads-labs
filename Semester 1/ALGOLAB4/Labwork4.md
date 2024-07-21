# Labwork №4 - Heaps

***

## Task A - "Пирамида ли?"

Структуру данных неубывающая пирамида можно реализовать на основе массива. Для этого должно выполняться основное
свойство неубывающей пирамиды, которое заключается в том, что для каждого 1 ≤ **_i_** ≤ **_n_** выполняются условия:

- Если **_2i_** ≤ **_n_**, то **_a_**[**_i_**] ≤ **_a_**[**_2i_**]
- Если **_2i+1_** ≤ **_n_**, то **_a_**[**_i_**] ≤ **_a_**[**_2i+1_**]

Дан массив целых чисел. Определите, является ли он неубывающей пирамидой.

### Input data:

Первая строка входного файла содержит целое число **_n_** (1 ≤ **_n_** ≤ 10^5)

Вторая строка содержит **_n_** целых чисел по модулю не превосходящих 2 * 10^9.

### Output data:

Выведите **_YES_**, если массив является неубывающей пирамидой, и **_NO_** в противном случае.

### STDIN:

5\
1 0 1 2 0

### STDOUT:

NO
***

## Task B - "Реализуйте приоритетную очередь"

Ваша очередь должна поддерживать операции, описанные во входных данных. Гарантируется, что размер любой очереди в
процессе выполнения команд не превысит 10^6 элементов.

### Input data:

Вход содердит описание операций с очередью. Количество операций не более, чем 10^6. Операции могут быть следующими:
Очередь с номером **_k_** — очередь, которая была создана **_k_**-й по счету (индексация очередей начинается с 0 и
создание кучи происходит в результате операции **_create_** или **_merge_**). Гарантируется, что на момент операции над
очередью с номером **_k_**, она уже создана.

- **_create_** — создать новую очередь
- **_insert k x_** — добавить элемент **_x_** в очередь с номером **_k_**.
- **_extract-min k_** — удалить из очереди с номером **_k_** минимальный элемент и вывести его в ответ. Если очередь
  пуста, в ответ требуется вывести звездочку `*`.
- **_merge k m_** — создать новую очередь путем слияния двух очередей с номерами **_k_** и **_m_**.
- **_decrease-key k x y_** — заменить в очереди с номером **_k_** значение элемента **_x_** на значение **_y_**.
  Гарантируется, что **_x_** ≥ **_y_**.

В очередь помещаются и извлекаются только целые числа, не превышающие по модулю 10^9.

### Output data:

Выведите последовательно результат выполнения всех операций **_extract-min_**, по одному в каждой строке ответа.

### STDIN:

create\
insert 0 1\
insert 0 3\
insert 0 5\
extract-min 0\
create\
insert 1 2\
insert 1 4\
insert 1 6\
merge 0 1\
decrease-key 2 5 1\
extract-min 2\
extract-min 2\
extract-min 0\
extract-min 0\
extract-min 0

### STDOUT:

1\
1\
2\
3\
5\
`*`
***

## Task C - "Шаверма патруль"

Ни для кого не секрет, что самая вкусная шаверма на Петроградке - “Шаверма от Шера”. Из-за своей внезапной популярности
среди студентов у ларька очень много заказов, поэтому владелец в срочном порядке решил нанять **_n_** шаурмистов, где у
**_i_**-ого шаурмиста зарплата составляет **_a_i_** рублей в минуту. Жадность Шера сгубила, поэтому он решил грамотно
организовать прием всех заказов таким образом, чтобы в момент прихода нового заказа он отдавался свободному работнику с
минимальной зарплатой. Если оказалось, что свободных шаурмистов нет, то заказ просто не выполняется.

### Input data:

В первой строке даны два числа **_n_** и **_m_** (1 ≤ **_n,m_** ≤ 3*10^5) — количество шаурмистов и заказов.

Во второй строке даны **_n_** чисел **_a_1_**, **_a_2_**, ..., **_a_n_**, разделенных пробелами, — зарплата каждого из
шаурмистов (руб./мин). Обратите внимание, что ни у каких двух шаурмистов не совпадает размер зарплаты (все **_a_i_**
различны).

В следующих **_m_** строках заданы описания заказов, **_i_**-я строка описывает **_i_**-й заказ:

Два числа **_t_i_** и **_f_i_** (1 ≤ **_t_i_** ≤ 10^9, 1 ≤ **_f_i_** ≤ 10^6), разделенные пробелом, — момент получения *
*_i_**-го заказа и время его выполнения (мин).

Во входных данных заказы расположены по возрастанию **_t_i_**, все **_t_i_** различны.

### Output data:

Выведите одно число - суммарная зарплата, которую владелец выплатит всем шаурмистам. Важно, что зарплату шаурмисты
получают только в момент работы.

### STDIN:

4 7\
3 2 6 4\
1 3\
2 5\
3 7\
4 10\
5 5\
6 100\
9 2

### STDOUT:

105

### Additional info:

Рассмотрим работу заведения поминутно:

- `t=1`: приходит первый заказ, все шаурмисты свободны. Второй шаурист занимается приготовлением 3 минуты
- `t=2`: приходит вторый заказ. Второй шаурист занят, поэтому первый шаурист занимается ее приготовлением 5 минут
- `t=3`: приходит третий заказ и четвертый шаурист занимается ее приготовлением 7 минут
- `t=4`: приходит четвертый заказ. Второй шаурист освободился в данный момент, а потому занимается ее приготовлением 10
  минут
- `t=5`: приходит пятый заказ и последний шаурист занимается ее приготовлением 5 минут
- `t=6`: приходит шестой заказ. Все шауристы еще заняты, поэтому заказ отбрасывается
- `t=7`: освобождается первый шаурмист
- `t=9`: приходит седьмой заказ и первый шаурист занимается ее приготовлением 2 минуты
- `t=10`: освобождаются третий и четвертый шаурмист.
- `t=11`: освобождается первый шаурмист
- `t=14`: освобождается второй шаурмист

Общая зарплата равна: `3*2 + 5*3 + 7*4 + 10*2 + 5*6 + 2*3 = 6 + 15 + 28 + 20 + 30 + 6 = 105`

- Подумайте, как можно быстро построить кучу?
- Человек с какой зарплатой должен оказаться на самом верху кучи?
- Достаточно ли только условия по минимизации зарплаты? Что можно сказать про время выполнения заказа?

***

## Task D - "Я покорю всю Россию"

У немолодой исполнительцы Альбины в октябре этого года стартует концертный тур “Я покорю всю Россию” во многих городах
нашей страны. Каждый город, в котором потенциально будет проходить концерт, обладает тремя параметрами:

- код города — уникальное натуральное число
- рейтинг города - натуральное число
- гонорар за выступление - натуральное число

При выборе следующего города продюссер выбирал город с максимальным рейтингом и гонораром. Если оказывалось так, что
город с максимальным рейтингом и город с максимальным гонораром совпадает, то продюссер добавляет его в тур, если же
нет, то он связывался с организаторами и пытался повысить гонорар для Альбины. Если просьба была удволетворена, то
продюссер вносил этот город в предстоящий тур, если же нет, то он оскорблялся и убирал этот город из потенциального
списка городов.

### Input data:

В первой строчке дано число **_n_** — количество потенциальных городов.

Далее идут **_n_** строчек, где в каждой пробел записаны характеристики города — код, рейтинг, гонорар.

После описания городов на вход дается число **_m_** — количество ответов организаторов на просьбу повышения гонорара.

Далее идут **_m_** строчек двух видов:

- **_YES_** — удовлетворительный ответ
- **_NO_** — неудовлетворительный ответ

### Output data:

В первой строчке вывести **_m_** элементов, где **_i_**-ый элемент указывает **_i_**-ый код города, с которым продюсер
связывается для повышения гонорара.

Во второй строчке необходимо вывести последовательность кодов городов, в которых будет проходить тур.

### STDIN:

5\
1 9 10\
2 2 2\
3 4 3\
4 8 1\
5 1 4\
3\
YES\
NO\
YES

### STDOUT:

4 3 2\
1 4 2 5

### STDIN:

9\
0 41 18467\
1 6334 26500\
2 19169 15724\
3 11478 29358\
4 26962 24464\
5 5705 28145\
6 23281 16827\
7 9961 491\
8 2995 11942\
2\
NO\
YES

### STDOUT:

4 6\
6 3 5

### Additional info:

1. Можем ли мы искать оптимальный город по рейтингу и стоимости в одной куче?
2. Что стоит делать при нахождении оптимального по рейтингу и стоимости города?
3. Рассмотрите два случая ответа. Что происходит при положительном ответе? Что ожидается при отказе от повышения
   гонорара?
4. Рассмотрите случай, когда ответ не пришел

***

## Task E - "Величайший кроссовер"

В поисках приключений бабушка Дуся решила отдохнуть от огородней суеты и отправиться на отдых в Египет.

Отправившись на экскурсию по пирамидам, бабушка заскучала от скучных рассказов и решила погулять отдельно от
туристической группы. Расхаживая по многочисленным лабиринтам, она наткнулась на полностью забитое золотом помещение,
посреди которого стояла Лара Крофт и запихивала сокровища в свой рюкзак. В шоке от такой наглости, бабушка мигом
подлетела к расхитительнице, чтобы непременно ее отругать и вернуть обратно украденное. Но Дуся не знала, что в пирамиде
всюду расставлены ловушки, поэтому случайно наступила на застланную пылью платформу, проход закрылся, а стенки помещения
стали медленно сдвигаться навстречу друг другу.

Пока Лара Крофт стояла, вспоминая лучшие моменты своей жизни, бабушка, не теряя ни секунды, оглянулась вокруг и увидела
настенные рисунки с подсказками и множество весов, расположенных вдоль стены. Быстро сообразив, что нужно делать, она
принялась расставлять сокровища на весы в отсортированном порядке

### Input data:

В первой строке входного файла содержится число **_n_** (1 ≤ **_n_** ≤ 10^5) — количество сокровищ в комнате

Во второй строке находятся **_n_** целых чисел модулю не превосходящих 10^9 — веса сокровищ

### Output data:

Выведите **_n_** чисел — веса сокровищ, расставленных в порядке неубывания, чтобы решить головоломку и спасти попавших в
беду туристок.

### STDIN:

10\
1 8 2 1 4 7 3 2 3 6

### STDOUT:

1 1 2 2 3 3 4 6 7 8

### Additional info:

- Количество весов совпадает с количеством сокровищ
- Необходимо написать сортировку кучей.
- За решения основанные на любых других сортировках баллы ставиться не будут.

***

## Task F - "Забытая советская закалка"

В далеком 1965 году в советских яслях ребятишкам решили устроить отдых, поэтому после изучениях дифференциалов,
интегралов и рядов, задали найти такое минимальное число, что количество всех его делителей равно **_2^n_**. Задача
оказалась непосильной даже для советских ребятишек, поэтому воспитатель подсказал, что в факторизации искомого числа
степени простых делителей являются степенями двойки без единицы (степени принимают значения 1, 3, 7, 15 и т.д.)

### Input data:

Дано число **_n_** (1 ≤ **_n_** ≤ 3 • 10^5)

### Output data:

В первой строчке необходимо вывести **_k_** — количество простых делителей искомого числа. Во второй строчке необходимо
вывести **_k_** простых делителей через пробел в порядке неубывания. Гарантируется, что разложение этого числа содержит
не более 10^6 простых чисел, каждое из которых не более 10^8.

### STDIN:

3

### STDOUT:

4\
2 2 2 3

### STDIN:

1

### STDOUT:

1\
2

### STDIN:

2

### STDOUT:

2\
2 3

### Additional info:

Пояснение к примеру 1:

`2 * 2 * 2 * 3 = 24` У числа 24 ровно 2^3 делителей: `1, 2, 3, 4, 6, 8, 12, 24`

Пояснение к примеру 2:

`1 * 2 = 2` У числа 2 ровно 2^1 делителей: `1, 2`

Пояснение к примеру 3:

`2 * 3 = 6` У числа 6 ровно 2^2 делителей: `1, 2, 3, 6`

1. Что мы можем сказать о простых делителях числа?
2. Какое именно количество простых делителей нам стоит найти?
3. Какой быстрый алгоритм для нахождеия простых чисел существует? Подсказка: он назван в честь греческого математика
4. Что стоит делать после извлечения минимального простого числа? Подумайте про квадрат этого числа
5. Заметим, что ответ должен быть отсортирован

***

## Task G - "Фибоначчиева куча"

Уважаемые студенты, перед вами новый тип задачи. Вам будет детально описана структура данных, которую не рассматривали
на лекциях. Также будут предоставлены ссылки на полезную литературу. От вас же будет требоваться корректная реализация
этой структуры данных и готовность ответить на вопросы преподавателя по теории (в том числе вывод ассимптотик).

На этот раз вам предстоит ознакомиться с фибкучей. Это некоторая структура данных, поддерживающая операции **add(x)**, *
*merge(H_1, H_2)**, **extract-min()** и **decrease_key(x, delta)**. Структурно фибкуча — это набор подвешенных деревьев,
удовлетворяющих некоторым свойствам:

1. каждый элемент дерева ≤ своим детям и ≥ родителя
2. у каждого дерева есть ранг **_k_**, который определяется так: у корня есть **_k_** детей, **_i_**-ый (i = 0,1,2..k-1)
   из которых является корнем поддерева ранга ≥ **_i_**. Заметим, что если мы подвесим дерево за другое дерево того же
   ранга, мы получим дерево с рангом, увеличенным на 1. Дерево ранга 0 — просто вершина.
3. Существуют деревья ранга `k*`. Это дерево ранга **_k_**, у корня которого отсутствует один ребенок. Заметим, что
   дерево ранга `k*` структурно является деревом ранга **_k-1_**. Единственным отличием является возможность подвешивать
   его как **_k_**-тое поддерево. При переносе в корень кучи ранг `k*` превращается в **_k-1_**, `K**` — в **_k-2_**

Перейдем к описанию операций: **_add(x)_** — добавление числа в кучу. Число представляется в виде дерева ранга 0 и
добавляется в кучу. Для быстрого добавления оптимально использовать двухсвязный список. Ассимптотическая сложность - О(
1).

**_merge(H_1, H_2)_** - слияние двух куч. Выполняется подвязыванием списка деревьев одной кучи к другому.
Асимптотическая сложность - О(1). Заметим, что в этой и предыдущей операции мы по необходимости обновляем минимум.

**_extract-min()_** - извлечение минимума из кучи. Исходя из свойства 1, минимумом будет являться один из корней кучи.
Также заметим, что указатель на минимум мы храним и динамически обновляем при добавлении. При удалении минимума нам
необходимо слить список корней кучи с детьми удаленной вершины. Затем пройти по всем корням и слить деревья одинакового
ранга. Тогда у нас останется не более одного дерева каждого ранга. Заметим, что в каждом дереве ≥ чем **_2^k_**
элементов, поэтому асимптотическая сложность — O(log n).

**_decrease_key(x, delta)_** — уменьшение ключа какой-либо вершины. При уменьшении числа вершина может оказаться меньше
своего родителя. В этом случае переносим эту вершину со всеми поддеревьями в корень кучи, помечая при этом предка
звездочкой. Если же предок уже был помечен, то повторяем операцию, пока не дойдем до непомеченного предка.
Асимптотическая сложность - амортизированная O(1).

Для более глубокого понимания предлагаются следующие ресурсы:

1. https://www.youtube.com/watch?v=CeAjTL-Fshs - лекция Павла Маврина, преподавателя ИТМО КТ.
2. https://www.youtube.com/watch?v=RE4ZThut8wI - лекция Ильи Степанова, преподавателя МФТИ ФПМИ.
3. https://neerc.ifmo.ru/wiki/index.php?title=Фибоначчиева_куча - статья на нирке.

### Input data:

Вход содержит описание операций с кучей. Количество операций не более чем **_10^6_**.
Операции могут быть следующими: куча с номером **_k_** — куча, которая была создана **_k_**-й по счету (индексация куч
начинается с 0 и создание кучи происходит в результате операции **_create_** или **_merge_**). Гарантируется, что на
момент операции над кучей с номером **_k_**, она уже создана

- `create` — создать новую кучу
- `insert k x` — добавить элемент **_x_** в кучу с номером **_k_**.
- `extract-min k` — удалить из кучи с номером **_k_** минимальный элемент и вывести его в ответ. Если куча пуста, в
  ответ требуется вывести `*`.
- `merge k m` — создать новую кучу путем слияния двух куч с номерами **_k_** и **_m_**.
- `decrease-key k x y` — заменить в куче с номером **_k_** значение элемента **_x_** на значение **_y_**. Гарантируется,
  что **_x_** ≥ **_y_**.

В куче помещаются и извлекаются только целые числа, не превышающие по модулю **_10^9_**.

### Output data:

Выведите последовательно результат выполнения всех операций `extract-min`, по одному в каждой строке ответа.

### STDIN:

create\
insert 0 1\
insert 0 3\
insert 0 5\
extract-min 0\
create\
insert 1 2\
insert 1 4\
insert 1 6\
merge 0 1\
decrease-key 2 5 1\
extract-min 2\
extract-min 2\
extract-min 0\
extract-min 0\
extract-min 0

### STDOUT:

1
1
2
3
5
`*`
***

## Task H - "🎰"

### Input data:

В первой строке дано 1 ≤ **_N_** ≤ 6000000.

В следующих **_N_** строках даны **_N_** чисел (-10^1000 ≤ **_a_i_** ≤ 10^1000).

### Output data:

В единственной строке выведите сумму всех **_N_** чисел.

### STDIN:

3\
1\
8\
4

### STDOUT:

13

### Additional info:

1. Как можно представить длинное число? С помощью чего его можно хранить?
2. Как можно сделать сложение в столбик? На какой структуре данных это удобнее всего сделать?

***
