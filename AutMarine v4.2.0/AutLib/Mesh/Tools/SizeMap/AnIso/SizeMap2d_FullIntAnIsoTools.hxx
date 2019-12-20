#pragma once
#ifndef _SizeMap2d_FullIntAnIsoTools_Header
#define _SizeMap2d_FullIntAnIsoTools_Header

#include <Global_Memory.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		class SizeMap2d_FullIntAnIso;
		class Mesh2d_SizeMap;
		class Mesh2d_MetricMap;

		class SizeMap2d_FullIntAnIsoTools
		{

		public:

			static Global_Handle(SizeMap2d_FullIntAnIso) CreateStdAnIsoSizeMap(const Global_Handle(Mesh2d_SizeMap) theSizeMap, const Global_Handle(Mesh2d_MetricMap) theMetricMap);

			static Global_Handle(SizeMap2d_FullIntAnIso) CreateModifiedSearchAnIsoSizeMap(const Global_Handle(Mesh2d_SizeMap) theSizeMap, const Global_Handle(Mesh2d_MetricMap) theMetricMap);

			static Global_Handle(SizeMap2d_FullIntAnIso) CreateModifiedSearchAndElementSizeAnIsoSizeMap(const Global_Handle(Mesh2d_SizeMap) theSizeMap, const Global_Handle(Mesh2d_MetricMap) theMetricMap);
		};
	}
}

#endif // !_SizeMap2d_FullIntAnIsoTools_Header
