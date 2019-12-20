#pragma once
#ifndef _Mesh2d_BoundarySizeMapControl_Header
#define _Mesh2d_BoundarySizeMapControl_Header

#include <Mesh2d_SizeMapControl.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class SizeMap2d_AdaptiveCurvesSizeMapTool;

		class Mesh2d_BoundarySizeMapControl : public Mesh2d_SizeMapControl
		{

		public:

			Mesh2d_BoundarySizeMapControl(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

			~Mesh2d_BoundarySizeMapControl();

			virtual void CreateNewMap(const Standard_String& theName);

			Global_Handle(SizeMap2d_AdaptiveCurvesSizeMapTool) SelectMap(const Standard_String& theName) const;

		};
	}
}

#endif // !_Mesh2d_BoundarySizeMapControl_Header
