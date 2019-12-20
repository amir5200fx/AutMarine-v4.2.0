#include <Cad2d_WireOnPlaneOrientationTools.hxx>

#include <Geometry_Tools.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_RingOnPlane.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

Cad2d_WireOnPlaneOrientationInfo AutLib::CadLib::Cad2d_WireOnPlaneOrientationTools::RetrieveOrientationOf(const TColCad2d_HAry1dOfEdgeOnPlane & theEdges)
{
	TColGeom_Ary1dOfPnt2d Pts;

	if (theEdges.Size() < 1) { THROW_STANDARD_EXCEPTION("Empty List"); }
	if (theEdges.Size() EQUAL 1)
	{
		Global_Handle(Cad2d_RingOnPlane) Ring = Global_DownCast(Cad2d_RingOnPlane, theEdges[0]);
		if (NOT Ring) { THROW_STANDARD_EXCEPTION("Invalid Wire"); }

		Debug_Null_Pointer(theEdges[0]->Curve());
		Get_Const_Object(Curve) = *theEdges[0]->Curve();

		Pts.Resize(3);
		Pts[0] = Curve.NormalizedParameterValue(0);
		Pts[1] = Curve.NormalizedParameterValue(0.33);
		Pts[2] = Curve.NormalizedParameterValue(0.66);
	}
	else if (theEdges.Size() EQUAL 2)
	{
		Pts.Resize(2 * theEdges.Size());
		Standard_Integer K = 0;
		forThose
		(
			Index,
			0,
			MaxIndexOf(theEdges)
		)
		{
			Debug_Null_Pointer(theEdges[Index]);
			Debug_Null_Pointer(theEdges[Index]->Curve());

			if (Global_DownCast(Cad2d_RingOnPlane, theEdges[Index])) { THROW_STANDARD_EXCEPTION("Invalid Wire"); }

			Pts[K] = theEdges[Index]->Curve()->NormalizedParameterValue(0.33);
			++K;

			Pts[K] = theEdges[Index]->Curve()->NormalizedParameterValue(0.66);
			++K;
		}
	}
	else
	{
		Pts.Resize(theEdges.Size());
		forThose
		(
			Index,
			0,
			MaxIndexOf(theEdges)
		)
		{
			Debug_Null_Pointer(theEdges[Index]);
			Debug_Null_Pointer(theEdges[Index]->Curve());

			if (Global_DownCast(Cad2d_RingOnPlane, theEdges[Index])) { THROW_STANDARD_EXCEPTION("Invalid Wire"); }

			Pts[Index] = theEdges[Index]->Curve()->NormalizedParameterValue(0.5);
		}
	}

	if (Geometry_Tools::IsCcwOrder(Pts)) return Cad2d_WireOnPlaneOrientation_CCW;
	else return Cad2d_WireOnPlaneOrientation_CW;
}