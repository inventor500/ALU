#include "wire.h"
#include <iostream>

WireObject::WireObject(std::string label)
	:label{label}, value{false} {}

std::string WireObject::get_label() const {
	return label;
}

void WireObject::set(bool new_value) {
	value = new_value;
	for (auto x : actions) {
		x();
	}
}

bool WireObject::get() const {
	return value;
}

void WireObject::on_change(Action action) {
	action();
	actions.push_back(action);
}

Wire make_wire(std::string label) {
	return std::make_shared<WireObject>(label);
}

void probe(Wire wire) {
	auto pwire = wire.get(); // get the raw pointer
	auto print_value = [=](){ std::cout << pwire->get_label() << " set to " << pwire->get() << '\n'; };
	wire->on_change(print_value);
}
