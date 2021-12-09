// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <vector>

namespace fg {

/**
 * @brief      Class that represents a single node to be added to the simulation.
 */
class Node {
public:
	/**
	 * @brief      Constructor
	 *
	 * @param[in]  label  Label of the current node
	 * @param[in]  links  The labels of other nodes, that this node should connect to.
	 * @param[in]  mass   The mass (determines size and movement)
	 */
	Node(const std::string &label = "Undefined", unsigned mass = 20,
		 const std::vector<std::string> &links = {});

	std::string label;
	unsigned mass;
	std::vector<std::string> links;
};

}  // namespace fg
