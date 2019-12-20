#include <Cad3d_ShellOnSolidTools.hxx>

#include <Entity_Box3dTools.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_Plane.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Cad3d_ShellOnSolid.hxx>
#include <Cad3d_CurveOnPlaneTools.hxx>
#include <Cad3d_SurfaceOnSolidTools.hxx>
#include <Cad3d_EdgeOnSolidTools.hxx>
#include <TColCad3d_HBasicQueueOfSurfaceOnSolid.hxx>
#include <TColCad3d_HBasicQueueOfShellOnSolid.hxx>
#include <TColCad3d_HNumbAvlTreeOfEdgeOnSolid.hxx>
#include <TColCad3d_HNumbAvlTreeOfSurfaceOnSolid.hxx>
#include <TColCad3d_HNumbAvlTreeOfShellOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

Standard_Boolean AutLib::CadLib::Cad3d_ShellOnSolidTools::IsLess
(
	Global_Handle(Cad3d_ShellOnSolid) const & theShell1,
	Global_Handle(Cad3d_ShellOnSolid) const & theShell2
)
{
	Debug_Null_Pointer(theShell1);
	Debug_Null_Pointer(theShell2);

	return theShell1->Index() < theShell2->Index();
}

namespace AutLib
{
	namespace CadLib
	{

		inline static Global_Handle(Cad3d_ShellOnSolid) GetItemFrom(TColCad3d_HNumbAvlTreeOfShellOnSolid& theRegister)
		{
			if (theRegister.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

			Global_Handle(Cad3d_ShellOnSolid) Item;

			theRegister.Root(Item);
			Try_Exception_Handle_Exit(theRegister.Remove(Item));

			return Item;
		}

		inline static void RegisterWires(Global_Handle(Cad3d_ShellOnSolid) InnerCandid, Global_Handle(Cad3d_ShellOnSolid) OutterCandid, TColCad3d_HBasicQueueOfShellOnSolid& QInners, Global_Handle(Cad3d_ShellOnSolid)& theOutter)
		{
			if (InnerCandid) QInners.EnQueue(InnerCandid);

			if (theOutter)
			{
				if (Entity_Box3dTools::IsBoxInsideBox(OutterCandid->BoundingBox(), theOutter->BoundingBox()))
				{
					QInners.EnQueue(OutterCandid);
				}
				else
				{
					Debug_If_Condition_Message(NOT Entity_Box3dTools::IsBoxInsideBox(theOutter->BoundingBox(), OutterCandid->BoundingBox()), "Conflict Data");

					QInners.EnQueue(theOutter);
					theOutter = OutterCandid;
				}
			}
			else
			{
				theOutter = OutterCandid;
			}
		}

		static void TrackBoundaries(TColCad3d_HNumbAvlTreeOfShellOnSolid& theRegister, TColCad3d_HBasicQueueOfShellOnSolid& QInners, Global_Handle(Cad3d_ShellOnSolid)& theOutter)
		{
			if (theRegister.IsEmpty()) { return; }

			Global_Handle(Cad3d_ShellOnSolid) Outter;
			Global_Handle(Cad3d_ShellOnSolid) Inner;

			Outter = GetItemFrom(theRegister);

			if (theRegister.IsEmpty())
			{
				RegisterWires(NULL, Outter, QInners, theOutter);
				return;
			}

			Inner = GetItemFrom(theRegister);

			const Entity_Box3d& OutterBox = Outter->BoundingBox();
			const Entity_Box3d& InnerBox = Inner->BoundingBox();

			if (Entity_Box3dTools::IsBoxInsideBox(InnerBox, OutterBox))
			{
				RegisterWires(Inner, Outter, QInners, theOutter);
				TrackBoundaries(theRegister, QInners, theOutter);
			}
			else if (Entity_Box3dTools::IsBoxInsideBox(OutterBox, InnerBox))
			{
				RegisterWires(Outter, Inner, QInners, theOutter);
				TrackBoundaries(theRegister, QInners, theOutter);
			}
			else
			{
				QInners.EnQueue(Inner);
				QInners.EnQueue(Outter);
				TrackBoundaries(theRegister, QInners, theOutter);
			}
		}
	}
}

Standard_Boolean AutLib::CadLib::Cad3d_ShellOnSolidTools::IdentifyBoundaries(const TColCad3d_HAry1dOfShellOnSolid & theShells, Cad3d_InnerBoundariesOnSolid & theInners, Cad3d_OutterBoundaryOnSolid & theOutter)
{
	if (theShells.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

	TColCad3d_HNumbAvlTreeOfShellOnSolid Register;
	Register.SetComparable(&Cad3d_ShellOnSolidTools::IsLess);
	Try_Exception_Handle_Exit(Register.Insert(theShells));

	Global_Handle(Cad3d_ShellOnSolid) Outter(0);
	TColCad3d_HBasicQueueOfShellOnSolid QInners;
	::TrackBoundaries(Register, QInners, Outter);

	if (NOT Outter) { return Standard_False; }

	theOutter = Outter;
	QInners.RetrieveTo(theInners);

	Debug_Null_Pointer(Outter);
	//Outter->SetOrientation(Cad2d_WireOnPlaneOrientation_CCW);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theInners)
	)
	{
		Debug_Null_Pointer(theInners[Index]);
		//theInners[Index]->SetOrientation(Cad2d_WireOnPlaneOrientation_CW);
	}
	return Standard_True;
}

namespace AutLib
{
	namespace CadLib
	{

		static void TrackShell(const Global_Handle(Cad3d_SurfaceOnSolid) theSurface, TColCad3d_HNumbAvlTreeOfSurfaceOnSolid& theRegister, TColCad3d_HBasicQueueOfSurfaceOnSolid& theList)
		{
			Debug_Null_Pointer(theSurface);

			Get_Const_Object(Surface) = *theSurface;

			TColCad3d_HAry1dOfEdgeOnSolid Edges = Surface.Edges();
			forThose
			(
				Index,
				0,
				MaxIndexOf(Edges)
			)
			{
				Debug_Null_Pointer(Edges[Index]);

				if (Edges[Index]->IsDegenerate()) continue;

				Get_Const_Pointer(Paired) = Edges[Index]->Paired();

				if (NOT Paired) continue;  // Debug July, 24, 2018
				Debug_Null_Pointer(Paired);

				Get_Const_Pointer(Neighbor) = Paired->Surface();
				Debug_Null_Pointer(Neighbor);

				if (Neighbor NOT_EQUAL theSurface AND theRegister.IsContains((Global_Handle(Cad3d_SurfaceOnSolid))Neighbor))
				{
					Try_Exception_Handle_Exit(theRegister.Remove((Global_Handle(Cad3d_SurfaceOnSolid))Neighbor));

					theList.EnQueue((Global_Handle(Cad3d_SurfaceOnSolid))Neighbor);

					Try_Exception_Handle_Exit(TrackShell(Neighbor, theRegister, theList));
				}
			}
		}

		static inline void TrackShell(TColCad3d_HNumbAvlTreeOfSurfaceOnSolid& theRegister, TColCad3d_HBasicQueueOfSurfaceOnSolid& theList)
		{
			Debug_If_Condition_Message(theRegister.IsEmpty(), "The List is empty");

			Global_Handle(Cad3d_SurfaceOnSolid) Root;
			theRegister.Root(Root);

			theList.EnQueue(Root);

			Try_Exception_Handle_Exit(theRegister.Remove(Root));

			Try_Exception_Handle_Exit(TrackShell(Root, theRegister, theList));
		}
	}
}

TColCad3d_HAry1dOfShellOnSolid AutLib::CadLib::Cad3d_ShellOnSolidTools::TrackShells(const TColCad3d_HAry1dOfSurfaceOnSolid & theSurfaces)
{
	if (theSurfaces.Size() < 1) { THROW_STANDARD_EXCEPTION("Empty list"); }

	TColCad3d_HAry1dOfEdgeOnSolid Edges = Cad3d_EdgeOnSolidTools::RetrieveEdgesFrom(theSurfaces);
	/*forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);
		if (NOT Edges[Index]->IsDegenerate() AND NOT Edges[Index]->Paired())
		{
			THROW_STANDARD_EXCEPTION("Invalid Solid");
		}
	}*/

	TColCad3d_HNumbAvlTreeOfSurfaceOnSolid Register;
	Register.SetComparable(&Cad3d_SurfaceOnSolidTools::IsLess);

	Try_Exception_Handle_Exit(Register.Insert(theSurfaces));

	Standard_Integer K = 0;
	TColCad3d_HBasicQueueOfShellOnSolid QShells;
	while (NOT Register.IsEmpty())
	{
		TColCad3d_HBasicQueueOfSurfaceOnSolid QSurfaces;
		::TrackShell(Register, QSurfaces);

		TColCad3d_HAry1dOfSurfaceOnSolid Surfaces;
		QSurfaces.RetrieveTo(Surfaces);

		QShells.EnQueue(new Cad3d_ShellOnSolid(++K, Surfaces));
	}
	TColCad3d_HAry1dOfShellOnSolid Shells;
	QShells.RetrieveTo(Shells);

	MOVE(Shells);
}

namespace AutLib
{
	namespace CadLib
	{

		static void MarchOnSurfaces(const Global_Handle(Cad3d_SurfaceOnSolid) theSurface, TColCad3d_HNumbAvlTreeOfSurfaceOnSolid& theRegister)
		{
			Debug_Null_Pointer(theSurface);

			Get_Const_Object(Edges) = theSurface->Edges();
			forThose
			(
				Index, 
				0, 
				MaxIndexOf(Edges)
			)
			{
				Debug_Null_Pointer(Edges[Index]);

				if (Edges[Index]->IsDegenerate()) continue;

				Get_Const_Pointer(Paired) = Edges[Index]->Paired();
				if (NOT Paired) continue;  // Debug July, 17, 2018

				Debug_Null_Pointer(Paired);

				Get_Pointer(Neighbor) = (Global_Handle(Cad3d_SurfaceOnSolid))Paired->Surface();

				Debug_Null_Pointer(Neighbor);

				Get_Const_Pointer(Edge) = Edges[Index];
				
				if (Neighbor NOT_EQUAL theSurface AND theRegister.IsContains(Neighbor))
				{
					//if (Cad3d_EdgeOnSolidTools::IsSameDirection(*Edge, *Paired))
					//{
					//	cout << "Reverse" << endl;
					//	Debug_Null_Pointer(Neighbor);
					//	//Neighbor->UReverseOrientation();
					//}

					if (Cad3d_CurveOnPlaneTools::IsSameDirection(Edge->CurveOnPlane(), Paired->CurveOnPlane(), theSurface->Geometry(), Neighbor->Geometry()))
					{
						Debug_Null_Pointer(Neighbor);
						Neighbor->UReverseOrientation();
					}
				}
			}
			/*return;
			PAUSE;*/
			forThose
			(
				Index,
				0,
				MaxIndexOf(Edges)
			)
			{
				Debug_Null_Pointer(Edges[Index]);

				if (Edges[Index]->IsDegenerate()) continue;

				Get_Const_Pointer(Paired) = Edges[Index]->Paired();
				if (NOT Paired) continue;  // Debug July, 17, 2018

				Debug_Null_Pointer(Paired);

				Get_Pointer(Neighbor) = (Global_Handle(Cad3d_SurfaceOnSolid))Paired->Surface();
				Debug_Null_Pointer(Neighbor);

				Get_Const_Pointer(Edge) = Edges[Index];

				if (Neighbor NOT_EQUAL theSurface AND theRegister.IsContains(Neighbor))
				{
					Try_Exception_Handle_Exit(theRegister.Remove((Global_Handle(Cad3d_SurfaceOnSolid))Neighbor));

					MarchOnSurfaces(Neighbor, theRegister);
				}
			}
		}
	}
}

void AutLib::CadLib::Cad3d_ShellOnSolidTools::SortOrientation(Cad3d_ShellOnSolid & theShell)
{
	Get_Object(Surfaces) = theShell.Surfaces();

	if (Surfaces.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }
	if (Surfaces.Size() EQUAL 1) return;

	TColCad3d_HNumbAvlTreeOfSurfaceOnSolid Register;
	Register.SetComparable(&Cad3d_SurfaceOnSolidTools::IsLess);
	Try_Exception_Handle_Exit(Register.Insert(Surfaces));

	Global_Handle(Cad3d_SurfaceOnSolid) Root;
	Register.Root(Root);
	Try_Exception_Handle_Exit(Register.Remove(Root));

	::MarchOnSurfaces(Root, Register);
}