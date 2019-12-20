#pragma once
#ifndef _Mesh3d_SmoothingConfig_Header
#define _Mesh3d_SmoothingConfig_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_SmoothingConfig
		{

		private:

			Standard_Integer theMaxIterations_;
			Standard_Integer theMaxLineIterations_;

			Standard_Real theActiveSetFactor_;
			Standard_Real theMinStepSize_;
			Standard_Real theMinSmoothingImprovement_;

		public:

			Mesh3d_SmoothingConfig();

			Standard_Integer MaxLineIterations() const;

			Standard_Integer MaxSmoothingIterations() const;

			Standard_Real ActiveSetFactor() const;

			Standard_Real MinStepSize() const;

			Standard_Real MinSmoothingImprovement() const;
		};
	}
}

#endif // !_Mesh3d_SmoothingConfig_Header
