#ifndef CGROUP_H
#define CGROUP_H

#include <limits>
#include <map>

#include "headers/HEngine.h"
#include "ARegistrar.h"

class ATask;
class CUnit;
class AIClasses;
class UnitType;

struct TargetsFilter {
	unsigned int include, exclude;
	int bestTarget; // can be updated after passing to selectTarget()
	int candidatesLimit;
	float threatRadius;
	float threatCeiling;
	float scoreCeiling; // can be updated after passing to selectTarget()
	float threatFactor;
	float threatValue; // can be updated after passing to selectTarget()
	
	TargetsFilter::TargetsFilter() {
		reset();
	}	

	void reset() {
		bestTarget = -1;
		candidatesLimit = std::numeric_limits<int>::max();
		include = std::numeric_limits<unsigned int>::max();
		exclude = 0;
		threatRadius = 0.0f;
		scoreCeiling = threatCeiling = std::numeric_limits<float>::max();
		threatFactor = 1.0f;
		threatValue = 0.0f;
	}
};

class CGroup: public ARegistrar {
	public:
		CGroup(AIClasses *ai): ARegistrar(counter, std::string("group")) {
			this->ai = ai;
			reset();
			counter++;
		}
		CGroup(): ARegistrar(counter, std::string("group")) {
			counter++;
		};

		~CGroup() {};

		/* Group counter */
		static int counter;
		/* Group category tags */
		unsigned int cats;
		/* Max tech level of all units in a group */
		int techlvl;
		/* Path type with the smallest slope */
		int pathType;
		/* Corresponding maxSlope */
		float maxSlope;
		/* The group strength */
		float strength;
		/* The group's moveSpeed */
		float speed;
		/* The group's buildSpeed */
		float buildSpeed;
		
		float cost;

		float costMetal;
		/* The group's footprint */
		int size;
		/* The group maxrange, buildrange */
		float range, buildRange, los;
		/* Is this group busy? */
		bool busy;
		/* The units <id, CUnit*> */
		std::map<int, CUnit*> units;
		/* Reference to common AI struct */
		AIClasses *ai;

		/* Remove this group, preserve units */
		void remove();
		/* Overloaded */
		void remove(ARegistrar &unit);
		/* Reset for object re-usage */
		void reset();
		/* Reclaim an entity (unit, feature etc.) */
		void reclaim(int entity, bool feature = true);
		/* Rpair target unit */
		void repair(int target);
		/* Set this group to micro mode true/false */
		void micro(bool on);
		/* Add a unit to the group */
		void addUnit(CUnit &unit);
		/* Get the first unit of the group */
		CUnit* firstUnit();
		/* Merge another group with this group */
		void merge(CGroup &group);
		/* Enable abilities on units like cloaking */
		void abilities(bool on);
		/* See if the entire group is idle */
		bool isIdle();
		/* See if the group is microing */
		bool isMicroing();
		/* Get the position of the group center */
		float3 pos(bool force_valid = false);
		/* Group radius when units are placed within a square */
		float radius();

		void assist(ATask &task);
		
		void attack(int target, bool enqueue = false);
		
		void build(float3 &pos, UnitType *ut);
		
		void stop();
		
		void move(float3 &pos, bool enqueue = false);
		
		void guard(int target, bool enqueue = false);
		
		void wait();
		
		void unwait();
		/* Get the maximal lateral dispersion */
		int maxLength();
		/* Can unit exists at this point? */
		bool canTouch(const float3&);
		/* Is position reachable by group */
		bool canReach(const float3&);
		/* Can group attack another unit? */
		bool canAttack(int uid);

		bool canAdd(CUnit *unit);
		
		bool canMerge(CGroup *group);
		
		float getThreat(float3 &target, float radius = 0.0f);

		int selectTarget(std::vector<int> &targets, std::map<int,bool> &occupied, TargetsFilter &tf);

		int selectTarget(float search_radius, std::map<int,bool> &occupied, TargetsFilter &tf);

		/* Overloaded */
		RegistrarType regtype() { return REGT_GROUP; }
		/* output stream */
		friend std::ostream& operator<<(std::ostream &out, const CGroup &group);

	private:
		bool radiusUpdateRequied;
			// when "radius" needs to be recalculated
		float groupRadius;
			// group radius (half of hypotenuse of square in which all units are inscribed)
		
		/* Recalculate group properties based on new unit */
		void recalcProperties(CUnit *unit, bool reset = false);

		void mergeCats(unsigned int);
};

#endif
