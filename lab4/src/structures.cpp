#include "structures.h"

bool check_possible_pos(int r, int c) {
	return (0 <= std::min(r, c) && std::max(r, c) < 8);
}

bool is_opposite(int who, char cell) {
	return ("bw"[who] == std::tolower(cell));
}

void check_possible_move(std::set<std::pair<int, int>>& checkers, int who, const field_t& field) {
	checkers.clear();
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (std::isupper(field.fld[r][c])) {
				if (!is_opposite(who, field.fld[r][c])) {
					for (auto dir : std::vector<std::pair<int, int>>{ {1,1}, {1,-1}, {-1,1}, {-1,-1} }) {
						if (check_possible_pos(r + dir.first, c + dir.second) && field.fld[r + dir.first][c + dir.second] == '0') {
							checkers.insert(std::make_pair(r, c));
							break;
						}
					}
				}
			}
			else if (std::islower(field.fld[r][c])) {
				if (!is_opposite(who, field.fld[r][c])) {
					for (auto dir : std::map<char, std::vector<std::pair<int, int>>>{ { 'w', { {-1,-1}, {-1,1} } }, { 'b', { {1,1}, {1,-1} } } }[field.fld[r][c]]) {
						if (check_possible_pos(r + dir.first, c + dir.second) && field.fld[r + dir.first][c + dir.second] == '0') {
							checkers.insert(std::make_pair(r, c));
							break;
						}
					}
				}
			}
		}
	}
}

void check_possible_move(std::vector<std::pair<int, int>>& checkers, int who, const field_t& field) {
	checkers.clear();
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (std::isupper(field.fld[r][c])) {
				if (!is_opposite(who, field.fld[r][c])) {
					for (auto dir : std::vector<std::pair<int, int>>{ {1,1}, {1,-1}, {-1,1}, {-1,-1} }) {
						if (check_possible_pos(r + dir.first, c + dir.second) && field.fld[r + dir.first][c + dir.second] == '0') {
							checkers.emplace_back(r, c);
							break;
						}
					}
				}
			}
			else if (std::islower(field.fld[r][c])) {
				if (!is_opposite(who, field.fld[r][c])) {
					for (auto dir : std::map<char, std::vector<std::pair<int, int>>>{ { 'w', { {-1,-1}, {-1,1} } }, { 'b', { {1,1}, {1,-1} } } }[field.fld[r][c]]) {
						if (check_possible_pos(r + dir.first, c + dir.second) && field.fld[r + dir.first][c + dir.second] == '0') {
							checkers.emplace_back(r, c);
							break;
						}
					}
				}
			}
		}
	}
}

bool check_one_checker(step_t select_step, int who, const field_t& field) {
	if (std::islower(field.fld[select_step.r][select_step.c])) {
		for (auto d : std::vector<std::pair<int, int>>{ {1,1}, {-1,-1}, {1,-1}, {-1,1} }) {
			int r = select_step.r + d.first;
			int c = select_step.c + d.second;
			int r_next = r + d.first;
			int c_next = c + d.second;
			if (check_possible_pos(r_next, c_next) && is_opposite(who, field.fld[r][c]) && field.fld[r_next][c_next] == '0') {
				return true;
			}
		}
	}
	if (std::isupper(field.fld[select_step.r][select_step.c])) {
		for (auto dir : std::vector<std::pair<int, int>>{ {1,1}, {1,-1}, {-1,1}, {-1,-1} }) {
			for (int dst = 1; dst < 8; dst++) {
				int r = select_step.r + dst * dir.first;
				int c = select_step.c + dst * dir.second;
				int r_next = r + dir.first;
				int c_next = c + dir.second;
				if (check_possible_pos(r_next, c_next)) {
					if (is_opposite(!who, field.fld[r][c])) {
						break;
					}
					if (is_opposite(who, field.fld[r][c]) && is_opposite(who, field.fld[r_next][c_next])) {
						break;
					}
					if (is_opposite(who, field.fld[r][c]) && field.fld[r_next][c_next] == '0') {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void check_all_checkers(std::set<std::pair<int, int>>& checkers, int who, const field_t& field) {
	checkers.clear();
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (((r + c) & 1) && is_opposite(!who, field.fld[r][c]) && check_one_checker(step_t(r, c), who, field)) {
				checkers.insert(std::make_pair(r, c));
			}
		}
	}
}

void check_all_checkers(std::vector<std::pair<int, int>>& checkers, int who, const field_t& field) {
	checkers.clear();
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (((r + c) & 1) && is_opposite(!who, field.fld[r][c]) && check_one_checker(step_t(r, c), who, field)) {
				checkers.push_back(std::make_pair(r, c));
			}
		}
	}
}
