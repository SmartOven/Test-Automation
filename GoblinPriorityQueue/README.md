# GoblinPriorityQueue
Решение задачи о Гоблинской приоритетной очереди
## Задание
[task.md](https://github.com/SmartOven/Test-Automation/blob/main/GoblinPriorityQueue/task.md)

## Как работает тестирующий скрипт?
1) Запускается генератор тестов, который генерирует случайный корректный тест для задачи
2) Запускается тестируемое решение, в него вводятся данные из сгенерированного теста, ответ программы запоминается
3) Запускается заведомо правильное решение, в него вводятся данные из сгенерированного теста, ответ программы запоминается
4) Ответы, полученные на двух предыдущих шагах, сравниваются. 
   1) При несовпадении в консоль выводятся оба ответа и сам тест. Скрипт завершается
   2) При совпадении скрипт возвращается к первому шагу и так пока не получит отрицательный результат (несовпадение ответов)

## Список файлов
### Тестируемое решение
[solution.cpp](https://github.com/SmartOven/Test-Automation/blob/main/GoblinPriorityQueue/solution.cpp)

### Заведомо правильное решение
[solution.py](https://github.com/SmartOven/Test-Automation/blob/main/GoblinPriorityQueue/solution.py)

### Генератор тестов
[test_generator.py](https://github.com/SmartOven/Test-Automation/blob/main/GoblinPriorityQueue/test_generator.py)

### bash-скрипт
[tester.sh](https://github.com/SmartOven/Test-Automation/blob/main/GoblinPriorityQueue/tester.sh)  
Сравнивает выводы тестируемого и заведомо правильного решения
