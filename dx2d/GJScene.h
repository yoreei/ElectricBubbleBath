#pragma once
#include <array>
#include <cmath>
#include <cstdint>

#include "math/vec3.h"

vec3 vec3op(const vec3& v, float(*op)(float)) {
	return vec3{
		op(v.e[0]),
		op(v.e[1]),
		op(v.e[2])
	};
}

struct Entity {
	uint16_t health = 1;
	uint16_t size = 2;
	vec3 momentum;
	vec3 getPos() const {
		vec3 val = vec3op(position, std::floor);
		return val;
	}
	void moveBy(const vec3& by) {
		position += by;
	}
	void setPos(const vec3& newPos) {
		position = newPos;
	}
	void setX(float x) {
		position.e[0] = x;
	}
	void setY(float y) {
		position.e[1] = y;
	}
private:
	vec3 position;
};

enum class State {
	MAINMENU = 0,
	PREGAME,
	INGAME,
	PAUSED,
	LOSS,
	WIN,
	size
};
struct GJScene {
	GJScene() {
	}

	void resetEntities() {
		entities.fill(GJScene::emptyEntity);
		for (int i = 0; i < entities.size(); ++i) {
			entities[i].health = 1;
			entities[i].size = 2;
			entities[i].setPos(vec3{ 180.f, 240.f, 0.f });
		}
	}

	void resetObstacles() {
		obstacles.fill(GJScene::emptyEntity);
	}

	State state = State::MAINMENU;
	bool explodeCd = false;
	bool qLeapCd = false;
	bool qLeapActive = false;
	uint64_t hiScore = 0;
	uint64_t points = 100;
	std::array<Entity, 4> entities{};
	std::array<Entity, 25> obstacles{};
	static inline Entity emptyEntity;
};
