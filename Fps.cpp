#include "Fps.h"
#include "DxLib.h"

namespace NovelSample {
	Fps::Fps()
		: elapsedTime_(0), prevTime_(0), framePerSecond_(0), count_(0) {}

	void Fps::update() {
		if (count_ == 0) {
			prevTime_ = DxLib::GetNowCount();
		}
		if (count_ == MetricTimes) {
			int t = DxLib::GetNowCount();
			framePerSecond_ = 1000.f / ((t - prevTime_) / (float)MetricTimes);
			count_ = 0;
			prevTime_ = t;
		}
		count_++;
		if (count_ >= GCountMax) {
			count_ = 0;
		}
	}

	void Fps::draw() {
#ifdef _DEBUG
		if (framePerSecond_ != 0) {
			DxLib::DrawFormatString(8, 480 - 24 * 2, static_cast<int>(DxLib::GetColor(255, 255, 255)),
				"FPS %.1f", framePerSecond_);
		}
#endif
	}

	void Fps::wait() {
		elapsedTime_ = DxLib::GetNowCount() - prevTime_; // calculate 1 loop time
		int waitTime = count_ * 1000 / FPS - elapsedTime_;
		if (waitTime > 0) {
			Sleep(waitTime);
		}
	}

}