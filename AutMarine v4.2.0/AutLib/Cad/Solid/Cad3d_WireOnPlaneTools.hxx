#pragma once
#ifndef _Cad3d_WireOnPlaneTools_Header
#define _Cad3d_WireOnPlaneTools_Header

#include <Standard_Handle.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_InnerBoundariesOnPlane.hxx>
#include <Cad3d_OutterBoundaryOnPlane.hxx>
#include <Cad3d_WireOnPlaneOrientationInfo.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>

class TopoDS_Wire;
class Geom_Surface;

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_WireOnPlaneTools
		{

		public:

			static Standard_Boolean IdentifyBoundaries(const TColCad3d_HAry1dOfWireOnPlane& theWires, Cad3d_InnerBoundariesOnPlane& theInners, Cad3d_OutterBoundaryOnPlane& theOutter);

			static Standard_Boolean CheckRingOrientation(const Cad3d_CurveOnPlane& theCurve, const Cad3d_WireOnPlaneOrientationInfo theOrientation);

			//! Warning: the wire is not removed from memory automaticaly!
			static TColCad3d_HAry1dOfWireOnPlane MakeWire(const TColCad3d_HAry1dOfEdgeOnPlane& theEdges, const Cad3d_WireOnPlaneOrientationInfo theOrientation);

			static TColCad3d_HAry1dOfWireOnPlane TrackWires(const TColCad3d_HAry1dOfEdgeOnPlane& theEdges, const Standard_String Name = "Unknown");

			static TopoDS_Wire Make_TopoDS_Wire(const TColCad3d_HAry1dOfEdgeOnPlane& theEdges, const Handle(Geom_Surface)& theSurface);
		};
	}
}

#endif // !_Cad3d_WireOnPlaneTools_Header
