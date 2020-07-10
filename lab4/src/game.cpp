#include "game.h"

#include <cmath>

game_t::game_t(const player_t &first, const player_t &second) : field() {
    players.push_back(first);
    first->who = 0;
    players.push_back(second);
    second->who = 1;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			field.fld[r][c] = (!((r + c) & 1) ? '.' : ("bbb00www"[r]));
		}
	}
}

game_t::game_outcome_t game_t::is_win(int who) const {
    if (step_cnt > 1337) {
        return TIE;
    }
	who ^= 1;
	std::set<std::pair<int, int>> can_attack;
    check_all_checkers(can_attack, who, field);
	if (!can_attack.empty()) {
		return IN_PROGRESS;
	}
    std::set<std::pair<int, int>> can_move;
    check_possible_move(can_move, who, field);
	if (!can_move.empty()) {
		return IN_PROGRESS;
	}
	return WIN;
}

void game_t::play() {
    int who = 1;
    step_cnt = 0;
    while (is_win(who) == IN_PROGRESS) {
        who ^= 1;
        bool correct_step = false;
        while (!correct_step) {
            auto select_step = players[who]->select_step(field);
			auto must_attack = false;
            correct_step = apply_select_step(select_step, who, must_attack);
            if (!correct_step) {
                players[who]->on_incorrect_select_step(select_step);
            } else if (!must_attack) {
				do {
					auto move_step = players[who]->make_step(field);
					correct_step = apply_move_step(select_step, move_step);
					if (!correct_step) {
						players[who]->on_incorrect_move_step(move_step);
						continue;
					}
				} while(!correct_step);				
            } else {
                do {
                    auto attack_step = players[who]->attack_step(field);
                    correct_step = apply_attack_step(select_step, attack_step, who);
                    if (!correct_step) {
                        players[who]->on_incorrect_attack_step(attack_step);
                        continue;
                    }
                } while (check_one_checker(select_step, who, field));
            }
        }
        step_cnt++;
    }
    if (is_win(who) == TIE) {
		players[0]->on_tie();
		players[1]->on_tie();
	}
	else {
		players[who]->on_win();
		players[!who]->on_lose();
	}
}

bool game_t::apply_select_step(const step_t &step, int who, bool& must_attack) {
	if (!check_possible_pos(step.r, step.c)) {
		return false;
	}
	std::set<std::pair<int, int>> can_attack;
	check_all_checkers(can_attack, who, field);
	std::set<std::pair<int, int>> can_move;
	check_possible_move(can_move, who, field);
	return (can_attack.empty() && can_move.count(std::make_pair(step.r, step.c))) || (must_attack = can_attack.count(std::make_pair(step.r, step.c)));
}

int game_t::sign(int x) const {
	return (x < 0 ? -1 : 1);
}

bool game_t::apply_move_step(const step_t &select_step, const step_t &target_step) {
	if (!check_possible_pos(target_step.r, target_step.c)) {
		return false;
	}
	if (std::abs(select_step.r - target_step.r) != std::abs(select_step.c - target_step.c)) {
		return false;
	}
	int dst = std::abs(select_step.r - target_step.r);
	if (dst == 0) {
		return false;
	}
	auto dir = std::make_pair(sign(target_step.r - select_step.r), sign(target_step.c - select_step.c));
	for (int d = 1; d <= dst; d++) {
		if (field.fld[select_step.r + d * dir.first][select_step.c + d * dir.second] != '0') {
			return false;
		}
	}
	char& from = field.fld[select_step.r][select_step.c];
	char& to = field.fld[target_step.r][target_step.c];
	if (std::isupper(from)) {
		std::swap(from, to);
		return true;
	}
	if (dst > 1) {
		return false;
	}
	if ((from == 'w' && dir.first == 1) || (from == 'b' && dir.first == -1)) {
		return false;
	}
	std::swap(from, to);
	if ((to == 'w' && target_step.r == 0) || (to == 'b' && target_step.r == 7)) {
		to = std::toupper(to);
	}
	return true;
}

bool game_t::apply_attack_step(step_t &select_step, step_t &attack_step, int who) {
	if (!check_possible_pos(attack_step.r, attack_step.c)) {
		return false;
	}
	if (field.fld[attack_step.r][attack_step.c] != '0') {
		return false;
	}
	if (std::abs(select_step.r - attack_step.r) != std::abs(select_step.c - attack_step.c)) {
		return false;
	}
	int dst = std::abs(select_step.r - attack_step.r);
	if (dst <= 1) {
		return false;
	}
	char &me = field.fld[select_step.r][select_step.c];
	char &to = field.fld[attack_step.r][attack_step.c];
	if (std::islower(me) && dst != 2) {
		return false;
	}
	auto dir = std::make_pair(sign(attack_step.r - select_step.r), sign(attack_step.c - select_step.c));
	bool ok = true;
	int cnt = 0;
	char *last = nullptr;
	for (int d = 1; d < dst; d++) {
		char &cell = field.fld[select_step.r + d * dir.first][select_step.c + d * dir.second];
		if (std::isalpha(cell)) {
			cnt++;
			last = &cell;
			ok &= is_opposite(who, cell);
		}
	}
	if (!ok || cnt != 1) {
		return false;
	}
	*last = '0';
	std::swap(me, to);
	if ((to == 'w' && attack_step.r == 0) || (to == 'b' && attack_step.r == 7)) {
		to = std::toupper(to);
	}
	select_step = attack_step;
	return true;
}
