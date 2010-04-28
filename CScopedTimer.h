#ifndef SCOPEDTIMER_HDR
#define SCOPEDTIMER_HDR

#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include <SDL_timer.h>

#include "headers/Defines.h"
#include "headers/HAIInterface.h"
#include "headers/HEngine.h"

#define PROFILE(x) CScopedTimer t(std::string(#x), ai->cb);

// Time interval in logic frames
#define TIME_INTERVAL 1000

static const float3 colors[] = {
	float3(1.0f, 0.0f, 0.0f),
	float3(0.0f, 1.0f, 0.0f),
	float3(0.0f, 0.0f, 1.0f),
	float3(1.0f, 1.0f, 0.0f),
	float3(0.0f, 1.0f, 1.0f),
	float3(1.0f, 0.0f, 1.0f),
	float3(0.0f, 0.0f, 0.0f),
	float3(1.0f, 1.0f, 1.0f)
};

class CScopedTimer {
	public:
		CScopedTimer(const std::string& s, IAICallback *_cb): cb(_cb), task(s) {
			initialized = true;
			if (!initialized)
				return;

			if (std::find(tasks.begin(), tasks.end(), task) == tasks.end()) {
				taskIDs[task] = tasks.size();
				tasks.push_back(task);
				curTime[task] = cb->GetCurrentFrame();
				prevTime[task] = 0;
			}

			t1 = SDL_GetTicks();
		}

		~CScopedTimer() {
			t2 = SDL_GetTicks();

			if (!initialized)
				return;
		}

	private:
		IAICallback *cb;
		const std::string task;
		unsigned t1, t2;
		bool initialized;

		static std::vector<std::string> tasks;
		static std::map<std::string, int> taskIDs;
		static std::map<std::string, unsigned int> curTime, prevTime;
};

#endif
