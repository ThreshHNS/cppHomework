
#include "safe_long_long.h"

safe_long_long::safe_long_long(long long get_l) {
    l = get_l;
}


safe_long_long::safe_long_long(safe_long_long const &get_l) {
    l = get_l.l;
}

safe_long_long::safe_long_long() {
    l = 0;
}

long long safe_long_long::get_l() const {
    return l;
}

void safe_long_long::operator=(const safe_long_long &l1) {
    l = l1.l;
}

safe_long_long safe_long_long::operator++() {
    return safe_long_long(++l);
}

safe_long_long safe_long_long::operator++(int) {
    return safe_long_long(l++);
}

safe_long_long safe_long_long::operator--() {
    return safe_long_long(--l);
}

safe_long_long safe_long_long::operator--(int) {
    return safe_long_long(l--);
}

void safe_long_long::operator+=(safe_long_long l1) {
    l += l1.get_l();
}

void safe_long_long::operator-=(safe_long_long l1) {
    l -= l1.get_l();
}

void safe_long_long::operator*=(safe_long_long l1) {
    l *= l1.get_l();
}

void safe_long_long::operator/=(safe_long_long l1) {
    l /= l1.get_l();
}

void safe_long_long::operator%=(safe_long_long l1) {
    l %= l1.get_l();
}


safe_long_long operator+(safe_long_long l1, safe_long_long l2) {
    safe_long_long tmp = l1;
    tmp += l2;
    return tmp;
}

safe_long_long operator-(safe_long_long l1, safe_long_long l2) {
    safe_long_long tmp = l1;
    tmp -= l2;
    return tmp;
}

safe_long_long operator*(safe_long_long l1, safe_long_long l2) {
    safe_long_long tmp = l1;
    tmp *= l2;
    return tmp;
}

safe_long_long operator/(safe_long_long l1, safe_long_long l2) {
    safe_long_long tmp = l1;
    tmp /= l2;
    return tmp;}

safe_long_long operator%(safe_long_long l1, safe_long_long l2) {
    safe_long_long tmp = l1;
    tmp %= l2;
    return tmp;}

bool operator==(safe_long_long const &l1, safe_long_long const &l2) {
    return l1.get_l() == l2.get_l();
}

bool operator!=(safe_long_long const &l1, safe_long_long const &l2) {
    return !(l1 == l2);
}


std::ostream &operator<<(std::ostream &s, safe_long_long l1) {
    s << l1.get_l();
    return s;
}

std::istream &operator>>(std::istream &s, safe_long_long &l1) {
    long long num;
    s >> num;
    l1 = num;
    return s;
}

bool operator<(safe_long_long const &l1, safe_long_long const &l2) {
    return l1.get_l() < l2.get_l();
}

bool operator>(safe_long_long const &l1, safe_long_long const &l2) {
    return l2 < l1;
}

bool operator<=(safe_long_long const &l1, safe_long_long const &l2) {
    return !(l2 < l1);
}

bool operator>=(safe_long_long const &l1, safe_long_long const &l2) {
    return !(l1 < l2);
}

int main() {
    safe_long_long long_long_1;
    safe_long_long long_long_2;
    std::cin >> long_long_1;
    std::cin >> long_long_2;
    std::cout <<"var_one + var_two = " << (long_long_1 + long_long_2);
    return 0;
}
