#ifndef SRC_ARRAYLIST_H
#define SRC_ARRAYLIST_H

#include <cstring>
#include <ostream>

template<typename T>
class ArrayList {
public:
    explicit ArrayList(size_t capacity) {
        this->capacity = capacity;
        _size = 0;
        array = new T[capacity];
    }

    ArrayList() : ArrayList(16) {};

    ~ArrayList() {
        delete[] array;
    }

    void add(const T &item) {
        _size++;
        expandIfFull();
        array[_size - 1] = item;
    }

    void insert(size_t index, const T &item) {
        _size++;
        if (index > _size) {
            _size = index + 1;
        }
        expandIfFull();
        memmove(&array[index + 1], &array[index], (_size - index) * sizeof(T));
        array[index] = item;
    }

    void erase(size_t index) {
        memmove(&array[index], &array[index + 1], (_size - index) * sizeof(T));
        _size--;
    }

    size_t size() {
        return this->_size;
    }

    friend std::ostream &operator<<(std::ostream &os, const ArrayList &list) {
        os << "ArrayList[";
        for (int i = 0; i < list._size - 1; i++) {
            os << list[i] << ", ";
        }
        os << list[list._size - 1] << "]";
        return os;
    }

    T operator[](size_t index) const {
        return this->array[index];
    }

    bool operator==(const ArrayList &rhs) const {
        return _size == rhs._size &&
               capacity == rhs.capacity &&
               array == rhs.array;
    }

    bool operator!=(const ArrayList &rhs) const {
        return rhs != *this;
    }

private:
    void expand() {
        capacity <<= 1;
        auto newArray = new T[capacity];
        memcpy(newArray, array, (capacity >> 1) * sizeof(T));
        delete[] array;
        array = newArray;
    }

    void expandIfFull() {
        while (_size >= capacity) {
            expand();
        }
    }

    size_t _size{};
    size_t capacity{};
    T *array;
};


#endif //SRC_ARRAYLIST_H
