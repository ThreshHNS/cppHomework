#pragma once

#include "structures.h"

struct strategy_interface_t {
	virtual step_t select_step(const field_t& field) = 0;
	virtual void on_incorrect_select_step(const step_t& step) const = 0;

	virtual step_t make_step(const field_t& field) = 0;
	virtual void on_incorrect_move_step(const step_t& step) const = 0;

	virtual step_t attack_step(const field_t& field) = 0;
	virtual void on_incorrect_attack_step(const step_t& step) const = 0;

	virtual void on_win() = 0;
	virtual void on_lose() = 0;
	virtual void on_tie() = 0;

	int who;
};
