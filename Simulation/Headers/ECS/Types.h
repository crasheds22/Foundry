/** Adapted from https://code.austinmorlan.com/austin/ecs/src/branch/master
 */

#pragma once

#include <bitset>
#include <cstdint>

namespace ECS
{
	using Entity = std::uint32_t;
	const Entity MAX_ENTITIES = 5000; //<-------- This should be in a config file somewhere

	using ComponentType = std::uint8_t; //<------ This might have to be a larger uint type
	const ComponentType MAX_COMPONENTS = 32;

	using Signature = std::bitset<MAX_COMPONENTS>;
}
