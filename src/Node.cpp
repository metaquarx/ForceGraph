// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "ForceGraph/Node.hpp"

namespace fg {

Node::Node(const std::string &label_, unsigned mass_, const std::vector<std::string> &links_)
  : label(label_), mass(mass_), links(links_) {}

}  // namespace fg
