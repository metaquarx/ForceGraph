// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "PhysicsSystems.hpp"

#include "Maths.hpp"

namespace fg::systems {

void calculate_forces(stch::Scene &registry, float gravity_c, float force_c) {
	// apply forces towards center
	for (auto node : registry.view<cp::Force, cp::Position>()) {
		auto gravity = registry.get<cp::Position>(node) * -1.f * gravity_c;
		registry.get<cp::Force>(node).value = gravity;
	}

	// apply repulsive forces between nodes
	for (auto node_i : registry.view<cp::Force, cp::Position>()) {
		for (auto node_j : registry.view<cp::Force, cp::Position>()) {
			if (node_i >= node_j) {
				continue;
			}

			auto &pos = registry.get<cp::Position>(node_i);
			auto dir = registry.get<cp::Position>(node_j) - pos;
			auto force = dir / (magnitude(dir) * magnitude(dir));
			force *= force_c;

			if (!std::isnan(force.x) && !std::isnan(force.y)) {
				registry.get<cp::Force>(node_i).value += force * -1.f;
				registry.get<cp::Force>(node_j).value += force;
			}
		}
	}

	// apply forces according to connections
	for (auto node : registry.view<cp::Force, cp::LinksEntity>()) {
		for (auto &link : registry.get<cp::LinksEntity>(node)) {
			if (registry.all_of<cp::Position, cp::Force>(link.entity)) {
				auto distance = registry.get<cp::Position>(node) - registry.get<cp::Position>(link.entity);

				registry.get<cp::Force>(node).value -= distance;
				registry.get<cp::Force>(link.entity).value += distance;
			}
		}
	}
}

void apply_forces(stch::Scene &registry) {
	// update position using forces
	for (auto node : registry.view<cp::Force, cp::Position, cp::Mass>()) {
		auto &force = registry.get<cp::Force>(node).value;
		auto &mass = registry.get<cp::Mass>(node);

		auto velocity = force / static_cast<float>(mass);

		registry.get<cp::Position>(node) += velocity;
	}
}

void apply_positions(stch::Scene &registry) {
	// update positions of arrows
	for (auto node : registry.view<cp::LinksEntity, cp::Position>()) {
		auto self_pos = registry.get<cp::Position>(node);
		for (auto &link : registry.get<cp::LinksEntity>(node)) {
			link.connection.pos_1 = self_pos;

			if (registry.all_of<cp::Position>(link.entity)) {
				link.connection.pos_2 = registry.get<cp::Position>(link.entity);
			}

			link.connection.recalculate_points();
		}
	}

	// update postions of circles
	for (auto node : registry.view<sf::CircleShape, cp::Position>()) {
		registry.get<sf::CircleShape>(node).setPosition(registry.get<cp::Position>(node));
	}
}

}  // namespace fg::systems
