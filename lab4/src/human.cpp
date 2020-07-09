#include "human.h"

#include <iostream>

human_strategy_t::human_strategy_t(std::string name) : name(std::move(name)) {}

human_strategy_t::~human_strategy_t() {}

step_t human_strategy_t::read_step() const {
	char r, c;
	std::cin >> c >> r;
	if (!('A' <= c && c <= 'H' && '1' <= r && r <= '8')) {
		return step_t(-1, -1);
	}
	return step_t('8' - r, c - 'A');
}

void human_strategy_t::print_step(const step_t& step) const {
	if (step.r == -1) {
		std::cout << "out of bounds A..H 1..8" << std::endl;
	}
	else {
		std::cout << char(step.c + 'A') << (8 - step.r) << std::endl;
	}
}

step_t human_strategy_t::select_step(const field_t& field) {
	field.print();
	std::cout << name << " - select checker: " << std::endl;
	return read_step();
}

void human_strategy_t::on_incorrect_select_step(const step_t& step) const {
	std::cout << name << " - incorrect select step: ";
	print_step(step);
}

step_t human_strategy_t::make_step(const field_t& fld) {
	std::cout << name << " - type coordinates to move: " << std::endl;
	return read_step();
}

void human_strategy_t::on_incorrect_move_step(const step_t& step) const {
	std::cout << name << " - incorrect move step: ";
	print_step(step);
}

step_t human_strategy_t::attack_step(const field_t& field) {
	field.print();
	std::cout << name << " - type coordinates to attack: " << std::endl;
	return read_step();
}

void human_strategy_t::on_incorrect_attack_step(const step_t& step) const {
	std::cout << name << " - incorrect attack step: ";
	print_step(step);
}

void human_strategy_t::on_win() {
	std::cout << name << " - you win!" << std::endl;
}

void human_strategy_t::on_lose() {
	std::cout << name << " - you lose!" << std::endl;
}

void human_strategy_t::on_tie() {
	std::cout << "Tie!" << std::endl;
}
