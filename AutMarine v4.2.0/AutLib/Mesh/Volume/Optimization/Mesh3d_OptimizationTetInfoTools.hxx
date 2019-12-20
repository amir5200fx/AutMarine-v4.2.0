#pragma once
#ifndef _Mesh3d_OptimizationTetInfoTools_Header
#define _Mesh3d_OptimizationTetInfoTools_Header

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_OptimizationTetInfo;

		class Mesh3d_OptimizationTetInfoTools
		{

		public:

			static void CalcInfo(Mesh3d_OptimizationTetInfo& theTet);
		};
	}
}

#endif // !_Mesh3d_OptimizationTetInfoTools_Header
