#pragma once

#include <memory>
#include <vector>
#include <set>

#include "interface.h"
#include "structures.h"

class game_t {
public:
	using player_t = std::shared_ptr<strategy_interface_t>;
	game_t(const player_t& first, const player_t& second);

	void play();

private:
	enum game_outcome_t {
		WIN,
		TIE,
		IN_PROGRESS
	};

	game_outcome_t is_win(int who) const;

	bool apply_select_step(const step_t& step, int who, bool& must_attack);
	bool apply_move_step(const step_t& select_step, const step_t& target_step);
	bool apply_attack_step(step_t& select_step, step_t& attack_step, int who);

	int sign(int x) const;

	field_t field;
	std::vector<player_t> players;
	int step_cnt;
};
