#pragma once
#include <climits>
namespace NovelSample {
	constexpr int FPS = 60;   // FPS
	constexpr int MetricTimes = 30;
	constexpr int GCountMax = INT_MAX;
	class Fps {
	public:
		Fps();
		void update();
		void draw();
		void wait();
	private:
		int elapsedTime_;
		int prevTime_;
		float framePerSecond_;
		int count_;
	};
}

