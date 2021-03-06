#include "int_list_t.h"

int_list_t::int_list_t() {
    first = new node_t(0, nullptr, nullptr);
    last = new node_t(0, first, nullptr);
    first->next = last;
    _size = 0;
}

int_list_t::~int_list_t() {
    clear();
    delete first;
    delete last;
}

size_t int_list_t::size() const {
    return _size;
}

bool int_list_t::empty() const {
    return _size == 0;
}

void int_list_t::swap(int_list_t &other) {
    std::swap(first, other.first);
    std::swap(last, other.last);
    std::swap(_size, other._size);
}

int &int_list_t::back() {
    return last->prev->value;
}


const int int_list_t::front() const {
    return first->next->value;
}

int_list_t::node_t *int_list_t::get(int pos) const {
    if (pos <= size() / 2) {
        node_t *pointer = first;
        do {
            pointer = pointer->next;
        } while (pos--);

        return pointer;
    } else {
        pos = pos - size() + 1;
        pos = abs(pos);
        node_t *pointer = last;
        do {
            pointer = pointer->prev;
        } while (pos--);

        return pointer;
    }

}

void int_list_t::insert(size_t pos, int new_val) {

    if (pos == _size) {
        node_t *pointer = last;
        node_t *new_node = new node_t(new_val, pointer->prev, pointer);
        pointer->prev->set_next(new_node);
        pointer->set_prev(new_node);
        _size++;
        return;
        }
    node_t *pointer = get(pos);
    node_t *new_node = new node_t(new_val, pointer->prev, pointer);
    pointer->prev->set_next(new_node);
    pointer->set_prev(new_node);

    _size++;
}

int &int_list_t::operator[](size_t pos) {
    node_t *pointer = get(pos);
    return pointer->value;
}

const int &int_list_t::operator[](size_t pos) const {
    node_t *pointer = get(pos);
    return pointer->value;
}

void int_list_t::push_front(int new_val) {
    insert(0, new_val);
}

void int_list_t::push_back(int new_val) {
    insert(_size, new_val);
}

void int_list_t::erase(size_t pos) {
    node_t *pointer = get(pos);
    pointer->prev->set_next(pointer->next);
    pointer->next->set_prev(pointer->prev);
    delete pointer;
    _size--;
}

void int_list_t::pop_front() {
    erase(0);
}

void int_list_t::pop_back() {
    erase(_size - 1);
}

int_list_t::int_list_t(const int_list_t &other) : int_list_t() {

    auto pointer = other.first;
    pointer = pointer->next;
    while (pointer != other.last) {
        push_back(pointer->value);
        pointer = pointer->next;
    }
}

int_list_t::int_list_t(size_t count, int value) : int_list_t() {
    for (int i = 0; i < count; ++i) {
        push_front(value);
    }
}

int_list_t &int_list_t::operator=(const int_list_t &other) {
    if (this != &other) {
        int_list_t tmp(other);
        swap(tmp);
    }
    return *this;
}

void int_list_t::clear() {
    node_t *pointer = first->next;
    node_t *next = pointer->next;
    for (int i = 0; i < size(); ++i) {
        delete pointer;
        pointer = next;
        next = pointer->next;
    }
    first->next = last;
    last->prev = first;
    _size = 0;
}

std::ostream &operator<<(std::ostream &stream, const int_list_t &list) {
    auto pointer = list.first;
    pointer = pointer->next;
    while (pointer != list.last) {
        stream << pointer->value << ' ';
        pointer = pointer->next;
    }
    return stream;
}

int_list_t int_list_t::splice(size_t start_pos, size_t count) {
    int_list_t new_list;

    node_t *pointer = first;

    for (int i = 0; i < start_pos + 1; ++i) {
        pointer = pointer->next;
    }

    node_t *prev_p = pointer->prev;
    new_list.first->set_next(pointer);
    pointer->set_prev(new_list.first);

    for (int i = 0; i < count - 1; ++i) {
        pointer = pointer->next;
    }

    new_list.last->set_prev(pointer);
    node_t *next_p = pointer->next;
    pointer->set_next(new_list.last);
    prev_p->set_next(next_p);
    next_p->set_prev(prev_p);
    _size -= count;
    new_list._size = count;
    return new_list;
}

std::istream &operator>>(std::istream &stream, int_list_t &list) {
    list.clear();
    int i = 0;
    std::string str_list;
    stream >> str_list;
    while (i < str_list.length()) {
        list.push_back(str_list[i]-'0');
        i++;
    }
    return stream;
}

int_list_t &int_list_t::merge(int_list_t &other) {
    if (this != &other) {
        
        last->prev->set_next(other.first->next);
        other.first->next->set_prev(last->prev);
        last->set_prev(other.last->prev);
        other.last->prev->set_next(last);
        other.first->set_next(other.last);
        other.last->set_prev(other.first);
        _size += other.size();
        other._size = 0;
    }
    return *this;
}

void int_list_t::reverse() {
    node_t *tmp = first->next;
    node_t *pointer = first->next;
    node_t *new_tmp;

    while (pointer != last) {
        new_tmp = pointer->next;
        std::swap(pointer->prev, pointer->next);
        pointer = new_tmp;
    }
    first->next = last->prev;
    first->next->prev = first;
    last->prev = tmp;
    last->prev->next = last;
}
