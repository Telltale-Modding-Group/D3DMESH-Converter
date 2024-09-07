#pragma once
#ifndef T3_RESOURCE_USAGE_H
#define T3_RESOURCE_USAGE_H

//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||
//||||||||||||||||||||||||||||| INCLUDED DEPENDENCIES |||||||||||||||||||||||||||||

//Standard C++ Library
#include <string>

//|||||||||||||||||||||||||||||||||||||||| T3 RESOURCE USAGE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3 RESOURCE USAGE ||||||||||||||||||||||||||||||||||||||||
//|||||||||||||||||||||||||||||||||||||||| T3 RESOURCE USAGE ||||||||||||||||||||||||||||||||||||||||
//NOTE: This is a regular int enum

enum T3ResourceUsage
{
	eResourceUsage_Static = 0,
	eResourceUsage_Dynamic = 1,
	eResourceUsage_System = 2,
	eResourceUsage_RenderTarget = 3,
	eResourceUsage_ShaderWrite = 4
};

#endif