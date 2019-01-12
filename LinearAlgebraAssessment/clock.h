#pragma once
#include <chrono>

using timer = std::chrono::steady_clock;
using delta_time = timer::duration;

inline timer::time_point now() { return timer::now(); }

inline float to_seconds(delta_time dt) {
	return std::chrono::duration_cast<std::chrono::duration<float>>(dt).count();
}

inline delta_time from_seconds(float sec) {
	return std::chrono::duration_cast<delta_time>(
		std::chrono::duration<float>(sec));
}