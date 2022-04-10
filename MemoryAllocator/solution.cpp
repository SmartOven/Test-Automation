#include <iostream>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::vector;
using std::string;

template <class T>
class ListNode {
public:
    ListNode() = default;
    explicit ListNode(T value) {
        this->prev = nullptr;
        this->value = value;
        this->next = nullptr;
    }
    ListNode(ListNode* prev, T value, ListNode* next) {
        this->prev = prev;
        this->value = value;
        this->next = next;
    }
    void setNext(ListNode* _next) {
        this->next = _next;
    }
    void setPrev(ListNode* _prev) {
        this->prev = _prev;
    }
    void setValue(T _value) {
        this->value = _value;
    }
    ListNode* getNext() {
        return this->next;
    }
    ListNode* getPrev() {
        return this->prev;
    }
    T getValue() const {
        return this->value;
    }
    bool operator > (const ListNode<T>& obj) {
        return this->getValue() > obj.getValue();
    }
    bool operator < (const ListNode<T>& obj) {
        return this->getValue() < obj.getValue();
    }
private:
    T value;
    ListNode* prev;
    ListNode* next;
};

template <class T>
class DoubleLinkedList {
public:
    DoubleLinkedList() {
        size = 0;

        T nullT = T();
        head = new ListNode<T>(nullT);
        tail = new ListNode<T>(nullT);

        head->setNext(tail);
        tail->setPrev(head);
    }
    ~DoubleLinkedList() {
        ListNode<T>* current = head->getNext();
        while (current != tail) {
            delete current->getPrev();
        }
        delete current;
    }
    void addFront(T value) {
        insertNode(value, head, tail);
    }
    // Создает новый элемент и вставляет его между prevNode и nextNode
    void insertNode(T value, ListNode<T>* prevNode, ListNode<T>* nextNode) {
        // Создаем новый элемент
        auto* newNode = new ListNode<T>(value);

        // Указываем друг на друга prevNode <-> newNode
        prevNode->setNext(newNode);
        newNode->setPrev(prevNode);

        // Указываем друг на друга newNode <-> nextNode
        newNode->setNext(nextNode);
        nextNode->setPrev(newNode);

        // Увеличиваем size на 1
        size++;
    }

    // Удаляет элемент по указателю на него и возвращает его значение
    void removeNode(ListNode<T>* node) {
        ListNode<T>* nodePrev = node->getPrev();
        ListNode<T>* nodeNext = node->getNext();

        // Удаляем указатели на данную ноду из соседей
        // Было: nodePrev <-> node <-> nodeNext
        // Стало: nodePrev <-> nodeNext
        if (nodePrev != nullptr) {
            nodePrev->setNext(nodeNext);
        }
        if (nodeNext != nullptr) {
            nodeNext->setPrev(nodePrev);
        }

        // Уменьшаем size на 1
        size--;

        // Запоминаем значение ноды и удаляем ее из памяти
//        delete node;
        if (node != nullptr) {
            free(node);
        }
    }
    ListNode<T>* begin() {
        return head->getNext();
    }
    ListNode<T>* end() {
        return tail;
    }
private:
    size_t size;

    ListNode<T>* head;
    ListNode<T>* tail;
};

template <class T>
class Heap {
public:
    Heap() = default;
    ~Heap() {
        _data.clear();
    }
    int getSize() {
        return (int) _data.size();
    }

    void add(T value) {
        _data.push_back(value);
        int i = getSize() - 1;
        int parent = (i - 1) / 2;
        T tmp;
        while (i > 0 && *_data[parent] < *_data[i]) {
            tmp = _data[i];
            _data[i] = _data[parent];
            _data[parent] = tmp;

            i = parent;
            parent = (i - 1) / 2;
        }
    }

    void heapify(int i) {
        int leftChild;
        int rightChild;
        int largestChild;
        T tmp;

        for (;;) {
            leftChild = 2 * i + 1;
            rightChild = 2 * i + 2;
            largestChild = i;

            if (leftChild < getSize() && *_data[leftChild] > *_data[largestChild]) {
                largestChild = leftChild;
            }

            if (rightChild < getSize() && *_data[rightChild] > *_data[largestChild]) {
                largestChild = rightChild;
            }

            if (largestChild == i) {
                break;
            }

            tmp = _data[i];
            _data[i] = _data[largestChild];
            _data[largestChild] = tmp;
            i = largestChild;
        }
    }

    T getMax() {
        T result = _data[0];
        _data[0] = _data[getSize() - 1];
        _data.erase(_data.begin() + getSize() - 1);
        heapify(0);
        return result;
    }

    void removeNull() {
        heapify(0);
        int i = _data.size() - 1;
        for (; i > 0 && _data[i - 1]->getValue().getSize() <= 0; i--) {}
        _data.erase(_data.begin() + i);
    }

private:
    vector<T> _data;
};

class MemorySection {
public:
    MemorySection() = default;
    MemorySection(int startIndex, int size, bool isFree) {
        this->startIndex = startIndex;
        this->size = size;
        this->isFree = isFree;
    }
    int getStartIndex() const {
        return startIndex;
    }
    int getSize() const {
        return size;
    }
    bool getIsFree() const {
        return isFree;
    }

    void setStartIndex(int _startIndex) {
        this->startIndex = _startIndex;
    }
    void setSize(int _size) {
        this->size = _size;
    }
    void setIsFree(bool _isFree) {
        this->isFree = _isFree;
    }

    bool operator > (const MemorySection& obj) const {
        return this->getSize() > obj.getSize();
    }
    bool operator < (const MemorySection& obj) const {
        return this->getSize() < obj.getSize();
    }

private:
    int startIndex;
    int size;
    bool isFree;
};

class Memory {
public:
    Memory() = default;
    explicit Memory(int size) {
        sections = DoubleLinkedList<MemorySection>();
        MemorySection ms = MemorySection(1, size, true);
        sections.addFront(ms);
        heap.add(sections.begin());

        successfulMemoryAllocations = std::map<int, ListNode<MemorySection>*>();
    }
    int allocate(int id, int size) {
        // Выбираем максимально подходящую свободную секцию памяти
        // Если такой нет - просто возвращаем false
        bool allocationAvailable;
        ListNode<MemorySection>* minEnough;
        int minEnoughSize;

        // Если есть где выделять
        if (heap.getSize() > 0) {
            minEnough = heap.getMax();
            minEnoughSize = minEnough->getValue().getSize();
            allocationAvailable = minEnoughSize >= size;
        } else {
            allocationAvailable = false;
        }

        // Негде выделять
        if (!allocationAvailable) {
            return -1;
        }

        MemorySection section = minEnough->getValue();
        // Если секция заполняется целиком - просто делаем ее isFree = false
        if (size == minEnoughSize) {
            section.setIsFree(false);
            minEnough->setValue(section);
        } else {
            // Вытаскиваем текущие startIndex и size
            int sectionStartIndex = section.getStartIndex();
            int sectionSize = section.getSize();

            // Разделяем секцию на занятую и свободную части
            MemorySection busyPart = MemorySection(sectionStartIndex, size, false);
            MemorySection freePart = MemorySection(sectionStartIndex + size, sectionSize - size, true);

            // Меняем (уменьшаем и делаем занятой) текущую секцию, добавляем новую (свободную)
            minEnough->setValue(busyPart);
            sections.insertNode(freePart, minEnough, minEnough->getNext());

            // Добавляем свободную в heap
            heap.add(minEnough->getNext());
        }
        successfulMemoryAllocations[id] = minEnough;
        return minEnough->getValue().getStartIndex();
    }
    void free(int id) {
        // Если вдруг такой секции вообще нет
        if (successfulMemoryAllocations.find(id) == successfulMemoryAllocations.end()) {
            return;
        }

        // Достаем "освобождаемую" секцию
        ListNode<MemorySection>* section = successfulMemoryAllocations[id];

        // Получаем ее соседей prev и next
        ListNode<MemorySection>* prev = section->getPrev();
        ListNode<MemorySection>* next = section->getNext();

        // Достаем значения всех трех
        MemorySection sectionValue = section->getValue();
        MemorySection prevValue = prev->getValue();
        MemorySection nextValue = next->getValue();

        // Если предыдущая секция свободна - мерджим ее с текущей
        if (prevValue.getIsFree()) {
            // Двигаем начало секции в начало prev и соединяем их размеры
            sectionValue.setStartIndex(prevValue.getStartIndex());
            sectionValue.setSize(sectionValue.getSize() + prevValue.getSize());

            // Удаляем prev
            prev->setValue(MemorySection(0, -1, true));
            heap.removeNull();
            sections.removeNode(prev);
        }

        // Если следующая секция свободна - мерджим ее с текущей
        if (nextValue.getIsFree()) {
            // Соединяем размеры секций
            sectionValue.setSize(sectionValue.getSize() + nextValue.getSize());

            // Удаляем next
            next->setValue(MemorySection(0, -1, true));
            heap.removeNull();
            sections.removeNode(next);
        }
        sectionValue.setIsFree(true);
        section->setValue(sectionValue);
        heap.add(section);
    }
private:
    // Будет содержать секции памяти с параметрами
    // 1) startIndex - индекс начала секции
    // 2) size - размер секции
    // 3) isFree - свободна ли секция или нет
    DoubleLinkedList<MemorySection> sections;

    // Будет содержать только свободные секции (в виде двоичной кучи указателей)
    Heap<ListNode<MemorySection>*> heap;

    // Будет содержать пары значений (id, ptr) для всех успешных операций выделения памяти
    std::map<int, ListNode<MemorySection>*> successfulMemoryAllocations;
};

int main() {
    int memorySize, requestsCount;
    cin >> memorySize >> requestsCount;

    Memory memory = Memory(memorySize);

    int request;
    int id = 1;
    for (int i = 0; i < requestsCount; i++) {
        cin >> request;

        // Запрос на освобождение памяти
        if (request < 0) {
            // Ищем в successfulMemoryAllocations пару с id = id
            // и освобождаем секцию памяти, с началом в startIndex
            // при этом проверяя правого и левого соседей данной ячейки - с каждым свободным из них
            // мерджимся и удаляем свободных
            memory.free(-request);
        } else {
            int size = request;
            // Выделяем память в минимально-подходящей по размеру секции
            // если секция заполняется целиком - меняем тип на busy (isFree = false)
            // если секция заполняется лишь частично - заполняем ее слева-направо, а остаток выделяем в новую секцию
            cout << memory.allocate(id, size) << "\n";
        }
        id++;
    }
    return 0;
}
