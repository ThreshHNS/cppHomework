#pragma once

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <map>

struct step_t {
	int r, c;

	step_t() {}
	step_t(int r, int c) : r(r), c(c) {}
	step_t(std::pair<int, int> _) : r(_.first), c(_.second) {}
};

struct field_t {
	char fld[8][8];

	field_t() {
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				fld[r][c] = (!((r + c) & 1) ? '.' : ("bbb00www"[r]));
			}
		}
	}

	void print() const {
		std::cout << "Field:" << std::endl;
		std::cout << " |A|B|C|D|E|F|G|H|" << std::endl;
		for (int r = 0; r < 8; r++) {
			std::cout << (8 - r) << '|';
			for (auto c : fld[r]) {
				std::cout << (c != '0' ? c : '.') << '|';
			}
			std::cout << std::endl;
		}
	}
};

bool check_possible_pos(int, int);

bool is_opposite(int, char);

void check_possible_move(std::set<std::pair<int, int>>&, int, const field_t&);

void check_possible_move(std::vector<std::pair<int, int>>&, int, const field_t&);

bool check_one_checker(step_t, int, const field_t&);

void check_all_checkers(std::set<std::pair<int, int>>&, int, const field_t&);

void check_all_checkers(std::vector<std::pair<int, int>>&, int, const field_t&);
