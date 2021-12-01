// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "ForceGraph/ForceSimulation.hpp"

static void add(fg::ForceSimulation &fs, std::vector<unsigned> &handled, unsigned &to_add) {
	// Check to see we haven't already added this number
	if (std::find(handled.begin(), handled.end(), to_add) != handled.end()) {
		return;
	}

	unsigned target;
	// Set the node to target according to standard collatz conjecture rules.
	if (to_add % 2 == 0) {
		target = to_add / 2;
	} else {
		target = to_add * 3 + 1;
	}

	// Add the current number, with a link to the next in the series.
	fg::Node node;
	node.label = std::to_string(to_add);
	node.links.push_back(std::to_string(target));
	fs.append({node});
	handled.push_back(to_add);

	// Recursively add the next numbers in the series
	add(fs, handled, target);
}

int main() {
	// Create a new simulation with a title.
	fg::ForceSimulation fs("Collatz Conjecture Simulation");

	std::vector<unsigned> handled;	// Used to store numbers we have already added to the simulation
	unsigned next_up = 4;  // Used to store the next number to add

	fs.on_event.push_back([&fs, &handled, &next_up](sf::Event event) {
		// Whenever the user clicks, add the next number in the collatz sequence to the simulation
		if (event.type == sf::Event::MouseButtonReleased) {
			add(fs, handled, next_up);
			fs.recalculate_connections();
			next_up++;
		}

		// Whenever the user presses escape, end the simulation
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Escape) {
				fs.pause();
			}
		}
	});

	// Start the simulation
	fs.play();
	// Since there is nothing afterwards, once we pause the simulation, the program ends.
}
