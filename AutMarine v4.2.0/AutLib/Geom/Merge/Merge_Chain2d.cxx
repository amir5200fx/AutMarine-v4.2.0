#include <Merge_Chain2d.hxx>

#include <Entity_StaticChain2d.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>
#include <TColEntity_BasicQueueOfEdgeIndex.hxx>
#include <Merge_Pnt2d.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::Merge_Chain2d::Merge_Chain2d
(
	Standard_Real Resolution,
	Standard_Real Radius
)
	: theResolution_(Resolution)
	, theRadius_(Radius)
	, IsDone_(Standard_False)
	, HandleDegeneray_(Standard_True)
{
}

Global_Handle(Entity_StaticChain2d) AutLib::GeoLib::Merge_Chain2d::Merged() const
{
	Debug_If_Condition_Message(NOT IsDone_, " Merging NOT performed");

	return theChain_;
}

Standard_Boolean AutLib::GeoLib::Merge_Chain2d::IsDone() const
{
	return IsDone_;
}

void AutLib::GeoLib::Merge_Chain2d::SetDegeneracy(const Standard_Boolean Degeneracy)
{
	HandleDegeneray_ = Degeneracy;
}

void AutLib::GeoLib::Merge_Chain2d::Import(const TColEntity_HAry1dOfStaticChain2d & Chains)
{
	theChain_ = new Entity_StaticChain2d;

	Debug_Null_Pointer(theChain_);

	Get_Object(Chain) = *theChain_;

	TColGeom_BasicQueueOfPnt2d QPoints;

	forThose
	(
		I,
		0,
		MaxIndexOf(Chains)
	)
	{
		Debug_Null_Pointer(Chains[I]);

		Get_Const_Object(Points) = Chains[I]->Coords();

		forThose
		(
			J,
			0,
			MaxIndexOf(Points)
		)
		{
			QPoints.EnQueue(Points[J]);
		}
	}

	// Import Points to the Chain
	Chain.SetCoords(QPoints.Retrive());

	// Gather Edges
	TColEntity_BasicQueueOfEdgeIndex QEdges;

	Standard_Integer NbPts = 0;

	forThose(I, 0, MaxIndexOf(Chains))
	{
		Debug_Null_Pointer(Chains[I]);

		Get_Const_Object(Edges) = Chains[I]->Edges();

		forThose(J, 0, MaxIndexOf(Edges))
		{
			M_GEO Entity_EdgeIndex Edge;

			Edge.V0() = Edges[J].V0() + NbPts;
			Edge.V1() = Edges[J].V1() + NbPts;

			QEdges.EnQueue(Edge);
		}

		NbPts += Chains[I]->NbPoints();
	}

	// Import Indices to the Chain
	Chain.SetEdges(QEdges.Retrive());
}

void AutLib::GeoLib::Merge_Chain2d::Import(const Entity_StaticChain2d & Static)
{
	theChain_ = new Entity_StaticChain2d;

	Debug_Null_Pointer(theChain_);

	Get_Object(Chain) = *theChain_;

	// Import Points to the Chain
	Chain.SetCoords(Static.Coords());

	// Import Indices to the Chain
	Chain.SetEdges(Static.Edges());
}

void AutLib::GeoLib::Merge_Chain2d::Perform()
{
	IsDone_ = Standard_True;

	Debug_Null_Pointer(theChain_);

	Get_Object(Chain) = *theChain_;

	Merge_Pnt2d Merge(theResolution_, theRadius_);

	Merge.SetCoords(&Chain.Coords());

	// Merging the points
	Try_Exception_Handle_Exit(Merge.Perform());

	// Import Merged Points to the Chain
	Chain.SetCoords(Merge.CompactPoints());

	Get_Const_Object(Indices) = Merge.CompactIndices();

	Get_Object(Edges) = Chain.Edges();

	TColEntity_BasicQueueOfEdgeIndex QEdges;

	if (HandleDegeneray_)
	{
		forThose
		(
			Index,
			0,
			MaxIndexOf(Edges)
		)
		{
			// Renumbering the Indices
			if (Indices[Edges[Index].V0()] NOT_EQUAL Indices[Edges[Index].V1()])
				QEdges.EnQueue(Entity_EdgeIndex(Indices[Edges[Index].V0()], Indices[Edges[Index].V1()]));
			//Try_Exception_Handle_Exit(Edges[Index].SetV12(Indices[Edges[Index].V0()], Indices[Edges[Index].V1()]));
		}
	}
	else
	{
		forThose
		(
			Index,
			0,
			MaxIndexOf(Edges)
		)
		{
			// Renumbering the Indices
			QEdges.EnQueue(Entity_EdgeIndex(Indices[Edges[Index].V0()], Indices[Edges[Index].V1()]));
		}
	}

	QEdges.RetrieveTo(Chain.Edges());
}

void AutLib::GeoLib::Merge_Chain2d::ReleaseMemory()
{
	FreePointer(theChain_);
}