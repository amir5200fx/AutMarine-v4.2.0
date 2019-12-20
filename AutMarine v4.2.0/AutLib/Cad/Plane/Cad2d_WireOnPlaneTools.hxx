#pragma once
#ifndef _Cad2d_WireOnPlaneTools_Header
#define _Cad2d_WireOnPlaneTools_Header

#include <Global_Memory.hxx>
#include <Cad2d_WireOnPlane.hxx>
#include <Cad2d_WireOnPlaneOrientationInfo.hxx>
#include <Cad2d_InnerBoundariesOnPlane.hxx>
#include <Cad2d_OutterBoundaryOnPlane.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>
#include <TColCad2d_HAry1dOfWireOnPlane.hxx>

namespace AutLib
{

	namespace CadLib
	{

		class Cad2d_WireOnPlane;

		class Cad2d_WireOnPlaneTools
		{

		public:

			static Standard_Boolean IsLess(Global_Handle(Cad2d_WireOnPlane) const& theWire1, Global_Handle(Cad2d_WireOnPlane) const& theWire2);

			static Standard_Boolean IdentifyBoundaries(const TColCad2d_HAry1dOfWireOnPlane& theWires, Cad2d_InnerBoundariesOnPlane& theInners, Cad2d_OutterBoundaryOnPlane& theOutter);

			static Standard_Boolean CheckRingOrientation(const Cad2d_CurveOnPlane& theCurve, const Cad2d_WireOnPlaneOrientationInfo theOrientation);

			//! Warning: the wire is not removed from memory automaticaly!
			//static Global_Handle(Cad2d_WireOnPlane) MakeWire(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges, const Cad2d_WireOnPlaneOrientationInfo theOrientation);

			//! Warning: the wire is not removed from memory automaticaly!
			//static Global_Handle(Cad2d_WireOnPlane) MakeWire(const TColCad2d_HAry1dOfCurveOnPlane& theCurves, const Cad2d_WireOnPlaneOrientationInfo theOrientation, const Standard_Real theTolerance = 1.0E-6);

			//! Warning: the wire is not removed from memory automaticaly!
			static TColCad2d_HAry1dOfWireOnPlane MakeWire(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges, const Cad2d_WireOnPlaneOrientationInfo theOrientation);

			static TColCad2d_HAry1dOfWireOnPlane TrackWires(const TColCad2d_HAry1dOfEdgeOnPlane& theEdges);

			//! Warning: the wire is not removed from memory automaticaly!
			static Global_Handle(Cad2d_WireOnPlane) SplitEdgeOnWire(const Standard_Real theParameter, const Cad2d_EdgeOnPlane& theEdge);

			//! Warning: the wire is not removed from memory automaticaly!
			static Global_Handle(Cad2d_WireOnPlane) SplitEdgeOnWire(const TColStd_Ary1dOfReal& theParameters, const Cad2d_EdgeOnPlane& theEdge);
		};
	}
}

#include <Cad2d_WireOnPlaneToolsI.hxx>

#endif // !_Cad2d_WireOnPlaneTools_Header
