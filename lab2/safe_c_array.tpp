#include "safe_c_array.h"

template<class T>
safe_c_array<T>::safe_c_array(size_t size) {
    _size = size;
    _data = new T[size];
}

template<class T>
safe_c_array<T>::safe_c_array(const safe_c_array &data) {
    _size = data._size;
    _data = new T[_size];
    for (int i = 0; i < _size; ++i) {
        _data[i] = data[i];
    }
}

template<class T>
safe_c_array<T>::~safe_c_array() {
    delete[] _data;
}


template<class T>
const T safe_c_array<T>::operator[](int index) const {
    if (index < 0 || index >= _size) {
        std::cout << "Out of bounds";
        exit(-1);
    }

    return _data[index];
}

template<class T>
T &safe_c_array<T>::operator[](int index) {
    if (index < 0 || index >= _size) {
        std::cout << "Out of bounds";
        exit(-1);
    }

    return _data[index];
}

template<class T>
void safe_c_array<T>::operator=(const safe_c_array &data) {
    if(this != &data) {
        delete[] _data;
        _size = data._size;
        _data = new T[_size];
        for (int i = 0; i < _size; ++i) {
            _data[i] = data[i];
        }
    }
}
