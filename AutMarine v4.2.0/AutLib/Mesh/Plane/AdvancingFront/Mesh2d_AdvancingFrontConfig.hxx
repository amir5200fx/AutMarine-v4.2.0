#pragma once
#ifndef _Mesh2d_AdvancingFrontConfig_Header
#define _Mesh2d_AdvancingFrontConfig_Header

#include <Mesh2d_FrontType.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_AdvancingFrontConfig
		{

		private:

			Mesh2d_FrontType theFrontType_;

		public:

			Mesh2d_AdvancingFrontConfig();

			Mesh2d_FrontType FrontType() const;

			void SetFrontType(const Mesh2d_FrontType& theType);

		};
	}
}

#include <Mesh2d_AdvancingFrontConfigI.hxx>

#endif // !_Mesh2d_AdvancingFrontConfig_Header
