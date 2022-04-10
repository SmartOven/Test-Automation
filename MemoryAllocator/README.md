# Petya-Cars
Решение задачи Менеджера памяти
## Задание
[task.md](https://github.com/SmartOven/Test-Automation/blob/main/MemoryAllocator/task.md)

## Как работает тестирующий скрипт?
1) Проверяется наличие переданных и еще не обработанных агрументов
    1) Если еще остались необработанные аргументы - следующим тестом будет тест из следующего аргумента
    2) Иначе запускается генератор тестов, который генерирует случайный корректный тест для задачи
2) Запускается тестируемое решение, в него вводятся данные из полученного теста, ответ программы запоминается
3) Запускается заведомо правильное решение, в него вводятся данные из полученного теста, ответ программы запоминается
4) Ответы, полученные на двух предыдущих шагах, сравниваются. 
   1) При несовпадении в консоль выводятся оба ответа и сам тест. Скрипт завершается
   2) При совпадении скрипт возвращается к первому шагу и так пока не получит отрицательный результат (несовпадение ответов)

## Список файлов
### Тестируемое решение
[solution.cpp](https://github.com/SmartOven/Test-Automation/blob/main/MemoryAllocator/solution.cpp)

### Заведомо правильное решение
[right_solution.cpp](https://github.com/SmartOven/Test-Automation/blob/main/MemoryAllocator/right_solution.cpp)

### Генератор тестов
[test_generator.py](https://github.com/SmartOven/Test-Automation/blob/main/MemoryAllocator/test_generator.py)

### bash-скрипт
[tester.sh](https://github.com/SmartOven/Test-Automation/blob/main/MemoryAllocator/tester.sh)  
Сравнивает выводы тестируемого и заведомо правильного решения
