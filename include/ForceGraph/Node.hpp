// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>
#include <vector>

namespace fg {

/**
 * @brief      Class that represents a simple node to be added to the simulation.
 */
class Node {
public:
	/**
	 * @brief      Constructor
	 *
	 * @param[in]  label  The label
	 * @param[in]  links  The links
	 * @param[in]  mass   The mass
	 */
	Node(const std::string &label = "Undefined", unsigned mass = 20, const std::vector<std::string> &links = {});

	std::string label;
	unsigned mass;
	std::vector<std::string> links;
};

}  // namespace fg
