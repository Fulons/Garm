#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

namespace garm {
	namespace math {

		inline float lerp(float v0, float v1, float t) {
			return v0 + t*(v1 - v0);
		}

		inline bool pointInRect(glm::vec2 point, glm::vec2 rectSize, glm::vec2 rectPos = glm::vec2()) {
			if (point.x < rectPos.x) return false;
			if (point.y < rectPos.y) return false;
			if (point.x > rectPos.x + rectSize.x) return false;
			if (point.y > rectPos.y + rectSize.y) return false;
			return true;
		}

} }