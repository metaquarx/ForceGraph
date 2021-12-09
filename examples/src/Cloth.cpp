// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "ForceGraph/ForceSimulation.hpp"

int main() {
	fg::ForceSimulation fs("Cloth simulation");

	for (unsigned x = 0; x < 8; x++) {
		for (unsigned y = 0; y < 8; y++) {
			fg::Node node;
			node.label = std::to_string(x) + "," + std::to_string(y);
			node.links.push_back(std::to_string(x + 1) + "," + std::to_string(y));
			node.links.push_back(std::to_string(x) + "," + std::to_string(y + 1));
			node.links.push_back(std::to_string(x + 1) + "," + std::to_string(y + 1));
			fs.append({node});
		}
	}
	fs.recalculate_connections();

	fs.play();
}
