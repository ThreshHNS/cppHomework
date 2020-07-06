#include "computer.h"

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

computer_strategy_t::computer_strategy_t(std::string name) : name(std::move(name)) {}

step_t computer_strategy_t::select_step(const field_t& field) {
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::vector<std::pair<int, int>> can_attack;
	check_all_checkers(can_attack, who, field);
	std::vector<std::pair<int, int>> can_move;
	check_possible_move(can_move, who, field);
	if (can_attack.empty()) {
		return (selected_checker = step_t(can_move[rng() % can_move.size()]));
	}
	else {
		return (selected_checker = step_t(can_attack[rng() % can_attack.size()]));
	}
}

step_t computer_strategy_t::make_step(const field_t& field) {
	char me = field.fld[selected_checker.r][selected_checker.c];
	std::vector<step_t> candys;
	for (auto dir : std::vector<std::pair<int, int>>{ {1,1}, {1,-1}, {-1,1}, {-1,-1} }) {
		if ((me == 'w' && dir.first == 1) || (me == 'b' && dir.first == -1)) {
			continue;
		}
		for (int dst = 1; ; dst++) {
			int r = selected_checker.r + dst * dir.first;
			int c = selected_checker.c + dst * dir.second;
			if (!check_possible_pos(r, c) || field.fld[r][c] != '0') {
				break;
			}
			candys.emplace_back(r, c);
			if (std::islower(me)) {
				break;
			}
		}
	}
	return (selected_checker = candys[std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count())() % candys.size()]);
}

step_t computer_strategy_t::attack_step(const field_t& field) {
	char me = field.fld[selected_checker.r][selected_checker.c];
	std::vector<step_t> candys;
	for (auto dir : std::vector<std::pair<int, int>>{ {1,1}, {1,-1}, {-1,1}, {-1,-1} }) {
		int cnt = 0;
		for (int dst = 1; cnt < 2; dst++) {
			int r = selected_checker.r + dst * dir.first;
			int c = selected_checker.c + dst * dir.second;
			if (!check_possible_pos(r, c)) {
				break;
			}
			if (std::tolower(field.fld[r][c]) == std::tolower(me)) {
				break;
			}
			cnt += bool(std::isalpha(field.fld[r][c]));
			if (cnt == 1 && field.fld[r][c] == '0') {
				candys.emplace_back(r, c);
			}
			if (std::islower(me) && dst == 2) {
				break;
			}
		}
	}
	return (selected_checker = candys[std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count())() % candys.size()]);
}

void computer_strategy_t::print_stat() const {
	std::cout << "Random model [" << name << "]: " << std::endl;
	computer_interface_t::print_stat();
}
