#pragma once
#ifndef _Mesh_SurfaceCurvatureValues_Header
#define _Mesh_SurfaceCurvatureValues_Header

#include <Standard_TypeDef.hxx>
#include <Mesh_SurfaceCurvatureInfo.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh_SurfaceCurvatureValues
		{

		private:

			Standard_Real theSpanAngle_;

			Mesh_SurfaceCurvatureInfo theCurvatureInfo_;

		public:

			Mesh_SurfaceCurvatureValues();

			void Init(const Standard_Real SpanAngle, const Mesh_SurfaceCurvatureInfo SurfaceCurvatureInfo);

			Standard_Real SpanAngle() const;

			Mesh_SurfaceCurvatureInfo CurvatureInfo() const;

			void SetSpanAngle(const Standard_Real Value);

			void SetCurvatureInfo(const Mesh_SurfaceCurvatureInfo SurfaceCurvatureInfo);
		};
	}
}

#include <Mesh_SurfaceCurvatureValuesI.hxx>

#endif // !_Mesh_SurfaceCurvatureValues_Header
