// SPDX-FileCopyrightText: 2021 metaquarx <metaquarx@protonmail.com>
// SPDX-License-Identifier: Apache-2.0

#include "PhysicsSystems.hpp"

#include "Maths.hpp"

namespace fg::systems {

void calculate_forces(stch::Scene &registry, float gravity_c, float force_c) {
	// apply forces towards center
	registry.each<cp::Force, cp::Position>(
		[&](auto, auto &force, auto &pos) { force.value = pos * -1.f * gravity_c; });

	// apply repulsive forces between nodes
	registry.each<cp::Force, cp::Position>([&](auto lhs, auto &lhs_force, auto &lhs_pos) {
		registry.each<cp::Force, cp::Position>([&](auto rhs, auto &rhs_force, auto &rhs_pos) {
			if (lhs >= rhs) {
				return;
			}

			auto dir = rhs_pos - lhs_pos;
			auto force = dir / (magnitude(dir) * magnitude(dir));
			force *= force_c;

			if (!std::isnan(force.x) && !std::isnan(force.y)) {
				lhs_force.value -= force;
				rhs_force.value += force;
			}
		});
	});

	// apply forces according to connections
	registry.each<cp::Force, cp::LinksEntity, cp::Position>([&](auto, auto &force, auto &links, auto &pos) {
		for (auto &link : links) {
			if (registry.all_of<cp::Position, cp::Force>(link.entity)) {
				const auto &[o_pos, o_force] = registry.get<cp::Position, cp::Force>(link.entity);

				auto distance = pos - o_pos;

				force.value -= distance;
				o_force.value += distance;
			}
		}
	});
}

void apply_forces(stch::Scene &registry) {
	// update position using forces
	registry.each<cp::Force, cp::Position, cp::Mass>([&](auto, auto &force, auto &pos, auto &mass) {
		auto velocity = force.value / static_cast<float>(mass);

		pos += velocity;
	});
}

void apply_positions(stch::Scene &registry) {
	// update positions of arrows
	registry.each<cp::LinksEntity, cp::Position>([&](auto, auto &links, auto &position) {
		for (auto &link : links) {
			link.connection.pos_1 = position;

			if (registry.all_of<cp::Position>(link.entity)) {
				link.connection.pos_2 = registry.get<cp::Position>(link.entity);
			}

			link.connection.recalculate_points();
		}
	});

	// update postions of circles
	registry.each<sf::CircleShape, cp::Position>(
		[&](auto, auto &circle, auto &position) { circle.setPosition(position); });
}

}  // namespace fg::systems
