// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "Maths.hpp"

namespace fg {

float magnitude(sf::Vector2f vector) {
	return std::sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

float distance(sf::Vector2f lhs, sf::Vector2f rhs) {
	return std::sqrt((lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y));
}

sf::Vector2f normalise(sf::Vector2f vector) {
	float length = distance(vector, {0., 0.});

	if (length != 0.f) {
		return vector / length;
	}

	return vector;
}

sf::Vector2f perpendicular(sf::Vector2f lhs) {
	return {-lhs.y, lhs.x};
}

}  // namespace fg
