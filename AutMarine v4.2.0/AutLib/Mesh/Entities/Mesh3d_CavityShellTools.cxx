#include <Mesh3d_CavityShellTools.hxx>

#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_CavityShellFourFacet.hxx>
#include <Mesh3d_CavityShellSixFacet.hxx>
#include <Mesh3d_CavityShellEightFacet.hxx>
#include <Mesh3d_CavityShellTenFacet.hxx>
#include <Mesh3d_CavityShellGeneral.hxx>
#include <TColMesh3d_HBasicQueueOfFacet.hxx>
#include <TColMesh3d_HBasicQueueOfCavityShell.hxx>
#include <TColMesh3d_HAvlTreeOfFacet.hxx>

using namespace AutLib;
using namespace MeshLib;

namespace AutLib
{
	namespace MeshLib
	{

		static void TrackCavityFacets1(Global_Handle(Mesh3d_Facet) theFacet, TColMesh3d_HAvlTreeOfFacet& theAllFacets, TColMesh3d_HBasicQueueOfFacet& theList)
		{
			Debug_Null_Pointer(theFacet);

			Get_Const_Object(Facet) = *theFacet;
			

			forThose
			(
				Index,
				0,
				2
			)
			{
				Debug_Null_Pointer(Facet.Edge(Index));

				TColMesh3d_HAry1dOfFacet FrontFacets = Facet.Edge(Index)->RetrieveFrontFacets();

				if (FrontFacets.Size() > 2)
				{
					THROW_STANDARD_EXCEPTION("Invalid Cavity Shell");
				}

				Global_Handle(Mesh3d_Facet) Next = 0;
				forThose
				(
					J, 
					0,
					MaxIndexOf(FrontFacets)
				)
				{
					Debug_Null_Pointer(FrontFacets[J]);

					if (FrontFacets[J] NOT_EQUAL theFacet AND theAllFacets.IsContains(FrontFacets[J]))
					{
						Next = FrontFacets[J];
						break;
					}
				}

				if (Next)
				{
					
					Try_Exception_Handle_Exit(theAllFacets.Remove(Next));

					theList.EnQueue(Next);

					TrackCavityFacets1(Next, theAllFacets, theList);
				}
			}
		}

		static inline void TrackCavityFacets(TColMesh3d_HAvlTreeOfFacet& theAllFacets, TColMesh3d_HBasicQueueOfFacet& theList)
		{
			Debug_If_Condition_Message(theAllFacets.IsEmpty(), "The List is empty");

			Global_Handle(Mesh3d_Facet) Root;
			theAllFacets.Root(Root);

			theList.EnQueue(Root);

			Try_Exception_Handle_Exit(theAllFacets.Remove(Root));

			Try_Exception_Handle_Exit(TrackCavityFacets1(Root, theAllFacets, theList));
		}
	}
}

void AutLib::MeshLib::Mesh3d_CavityShellTools::IdentifyShells
(
	const TColMesh3d_HAry1dOfFacet & theFacets, 
	TColMesh3d_HAry1dOfCavityShell & theShells
)
{
	TColMesh3d_HAvlTreeOfFacet Register;
	Set_Numbering(Register, Mesh3d_FacetTools::IsLess);

	Try_Exception_Handle_Exit(Register.Insert(theFacets));

	Standard_Integer K = 0;

	TColMesh3d_HBasicQueueOfCavityShell QShells;
	while (NOT Register.IsEmpty())
	{
		TColMesh3d_HBasicQueueOfFacet QFacets;
		::TrackCavityFacets(Register, QFacets);

		TColMesh3d_HAry1dOfFacet Facets;
		QFacets.RetrieveTo(Facets);

		Global_Handle(Mesh3d_CavityShell) newShell = Mesh3d_CavityShellTools::CreateShell(Facets);
		newShell->SetIndex(++K);

		QShells.EnQueue(newShell);
	}
	QShells.RetrieveTo(theShells);
}

Global_Handle(Mesh3d_CavityShell) AutLib::MeshLib::Mesh3d_CavityShellTools::CreateShell(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	if (theFacets.Size() < 4)
	{
		THROW_STANDARD_EXCEPTION("Not valid cavity shell");
	}

	if (theFacets.Size() EQUAL 4)
	{
		Debug_Null_Pointer(theFacets[0]);
		Debug_Null_Pointer(theFacets[1]);
		Debug_Null_Pointer(theFacets[2]);
		Debug_Null_Pointer(theFacets[3]);

		return new Mesh3d_CavityShellFourFacet
		(
			theFacets[0],
			theFacets[1],
			theFacets[2],
			theFacets[3]
		);
	}

	if (theFacets.Size() EQUAL 8)
	{
		Debug_Null_Pointer(theFacets[0]);
		Debug_Null_Pointer(theFacets[1]);
		Debug_Null_Pointer(theFacets[2]);
		Debug_Null_Pointer(theFacets[3]);
		Debug_Null_Pointer(theFacets[4]);
		Debug_Null_Pointer(theFacets[5]);
		Debug_Null_Pointer(theFacets[6]);
		Debug_Null_Pointer(theFacets[7]);

		return new Mesh3d_CavityShellEightFacet
		(
			theFacets[0], 
			theFacets[1], 
			theFacets[2], 
			theFacets[3], 
			theFacets[4], 
			theFacets[5], 
			theFacets[6], 
			theFacets[7]
		);
	}

	if (theFacets.Size() EQUAL 6)
	{
		Debug_Null_Pointer(theFacets[0]);
		Debug_Null_Pointer(theFacets[1]);
		Debug_Null_Pointer(theFacets[2]);
		Debug_Null_Pointer(theFacets[3]);
		Debug_Null_Pointer(theFacets[4]);
		Debug_Null_Pointer(theFacets[5]);

		return new Mesh3d_CavityShellSixFacet
		(
			theFacets[0],
			theFacets[1],
			theFacets[2],
			theFacets[3],
			theFacets[4],
			theFacets[5]
		);
	}

	/*if (theFacets.Size() EQUAL 10)
	{
		Debug_Null_Pointer(theFacets[0]);
		Debug_Null_Pointer(theFacets[1]);
		Debug_Null_Pointer(theFacets[2]);
		Debug_Null_Pointer(theFacets[3]);
		Debug_Null_Pointer(theFacets[4]);
		Debug_Null_Pointer(theFacets[5]);
		Debug_Null_Pointer(theFacets[6]);
		Debug_Null_Pointer(theFacets[7]);
		Debug_Null_Pointer(theFacets[8]);
		Debug_Null_Pointer(theFacets[9]);

		return new Mesh3d_CavityShellTenFacet
		(
			theFacets[0],
			theFacets[1],
			theFacets[2],
			theFacets[3],
			theFacets[4],
			theFacets[5],
			theFacets[6],
			theFacets[7],
			theFacets[8],
			theFacets[9]
		);
	}*/

	return new Mesh3d_CavityShellGeneral(theFacets);
}