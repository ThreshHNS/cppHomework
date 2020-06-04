#ifndef NEP_SAFE_LONG_LONG_H
#define NEP_SAFE_LONG_LONG_H

#include <iostream>

class safe_long_long {
private:
    long long l;

public:
    safe_long_long(long long get_l);

    safe_long_long(safe_long_long const &get_l);

    safe_long_long();

    long long get_l() const;

    void operator=(const safe_long_long &get_l);

    safe_long_long operator++();

    safe_long_long operator++(int);

    safe_long_long operator--();

    safe_long_long operator--(int);

    void operator+=(safe_long_long l1);

    void operator-=(safe_long_long l1);

    void operator*=(safe_long_long l1);

    void operator/=(safe_long_long l1);

    void operator%=(safe_long_long l1);

    ~safe_long_long() = default;


};

safe_long_long operator+(safe_long_long l1, safe_long_long l2);

safe_long_long operator-(safe_long_long l1, safe_long_long l2);

safe_long_long operator*(safe_long_long l1, safe_long_long l2);

safe_long_long operator/(safe_long_long l1, safe_long_long l2);

safe_long_long operator%(safe_long_long l1, safe_long_long l2);

bool operator==(safe_long_long const &l1, safe_long_long const &l2);

bool operator!=(safe_long_long const &l1, safe_long_long const &l2);

bool operator<(safe_long_long const &l1, safe_long_long const &l2);

bool operator>(safe_long_long const &l1, safe_long_long const &l2);

bool operator<=(safe_long_long const &l1, safe_long_long const &l2);

bool operator>=(safe_long_long const &l1, safe_long_long const &l2);

std::ostream &operator<<(std::ostream &s, safe_long_long l1);

std::istream &operator>>(std::istream &s, safe_long_long &l1);

#endif //NEP_SAFE_LONG_LONG_H
