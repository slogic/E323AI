#ifndef THREATMAP_H
#define THREATMAP_H

#include "headers/Defines.h"
#include "headers/HEngine.h"

class AIClasses;
class CGroup;

enum ThreatMapType {
	TMT_NONE = 0,
	TMT_AIR,
	TMT_SURFACE,
	TMT_UNDERWATER
};

class CThreatMap {
	public:
		CThreatMap(AIClasses *ai);
		~CThreatMap();

		void update(int frame);
		float getThreat(float3 &center, float radius, ThreatMapType type = TMT_SURFACE);
		float getThreat(float3 &center, float radius, CGroup *group);
		float *getMap(ThreatMapType);
		
		int X, Z;
		int RES;

	private:
		AIClasses *ai;	
		int *units;
		float REAL;
		std::map<ThreatMapType,float> maxPower;
		std::map<ThreatMapType,float*> maps;
		std::map<ThreatMapType,int> handles;

		float gauss(float x, float sigma, float mu);
		void reset();
		void draw(ThreatMapType type = TMT_SURFACE);
};

#endif
