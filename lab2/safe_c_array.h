#ifndef NEP_SAFE_C_ARRAY_H
#define NEP_SAFE_C_ARRAY_H

#include <iostream>

template<class T>
class safe_c_array {
private:
    T *_data;
    size_t _size;
public:
    explicit safe_c_array(size_t size);

    safe_c_array(const safe_c_array &data);

    ~safe_c_array();

    const T operator[](int index) const;

    void operator=(const safe_c_array &data);

    T& operator[](int index);
};



#endif //NEP_SAFE_C_ARRAY_H
