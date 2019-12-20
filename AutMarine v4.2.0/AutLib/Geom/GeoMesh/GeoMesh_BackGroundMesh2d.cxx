#include <GeoMesh_BackGroundMesh2d.hxx>

#include <Entity_Box2d.hxx>
#include <IO_Tecplot.hxx>
#include <Primitive_Field.hxx>
#include <Entity_Triangulation2d.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::GeoMesh_BackGroundMesh2d::GeoMesh_BackGroundMesh2d()
	: theCurrentElement_(NULL)
	, theBoundingBox_(NULL)
{
}

AutLib::GeoLib::GeoMesh_BackGroundMesh2d::GeoMesh_BackGroundMesh2d(const GeoMesh_TriangleMesh2d & StaticMesh)
	: theMesh_(StaticMesh)
	, theBoundingBox_(NULL)
{
	Debug_If_Condition_Message(NOT theMesh_.ElementsSequence().Size(), "Empty Elements sequence");
	theCurrentElement_ = theMesh_.ElementsSequence()[0];
}

AutLib::GeoLib::GeoMesh_BackGroundMesh2d::~GeoMesh_BackGroundMesh2d()
{
	FreePointer(theBoundingBox_);
}

Primitive_Field AutLib::GeoLib::GeoMesh_BackGroundMesh2d::Field() const
{
	if (NOT theSources_.Size())
	{
		THROW_STANDARD_EXCEPTION(" No space function detected");
	}

	Primitive_Field Field(1, theSources_.Size());

	Field.SetVariablesName("Source");

	forThose
	(
		Index,
		0,
		MaxIndexOf(theSources_)
	)
	{
		Field.SetValue
		(
			Index,
			0,
			theSources_[Index]
		);
	}

	MOVE(Field);
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh2d::SetBoundingBox(const Entity_Box2d & theBoundingBox)
{
	FreePointer(theBoundingBox_);
	theBoundingBox_ = new Entity_Box2d(theBoundingBox);
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh2d::InitiateCurrentElement() const
{
	theCurrentElement_ = theMesh_.FirstElement();
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh2d::SetCurrentElement(const Global_Handle(Entity_Element2d) theElement) const
{
	theCurrentElement_ = (Global_Handle(Entity_Element2d))theElement;
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh2d::HvCorrection
(
	const Standard_Real Factor, 
	const Standard_Integer MaxInnerIteration
)
{
	Standard_Real factor = MIN(1.0, MAX(Factor, 0.0));

	Get_Const_Object(Nodes) = theMesh_.NodesSequence();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		const Entity_Node2d& Node = *Nodes[Index];

		TColEntity_HAry1dOfEdge2d Edges;
		Node.Edges(Edges);

		forThose(Iter, 1, MaxInnerIteration)
		{
			forThose
			(
				I,
				0,
				MaxIndexOf(Edges)
			)
			{
				const Entity_Edge2d& Edge = *Edges[I];

				Global_Handle(Entity_Node2d) Side = Edge.Node(1);
				if (Side EQUAL &Node) Side = Edge.Node(0);

				Standard_Real length1 = Length(Node.Coord(), Side->Coord());
				Standard_Real length2 = Length(Side->Coord(), Node.Coord());

				Try_Exception_Handle_Exit(theSources_[Index_Of(Node.Index())] = MIN(theSources_[Index_Of(Node.Index())], theSources_[Index_Of(Side->Index())] * (1.0 + factor*length2)));
				Try_Exception_Handle_Exit(theSources_[Index_Of(Side->Index())] = MIN(theSources_[Index_Of(Side->Index())], theSources_[Index_Of(Node.Index())] * (1.0 + factor*length1)));
			}
		}
	}

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		const Entity_Node2d& Node = *Nodes[MaxIndexOf(Nodes) - Index];

		TColEntity_HAry1dOfEdge2d Edges;
		Node.Edges(Edges);

		forThose(Iter, 1, MaxInnerIteration)
		{
			forThose
			(
				I,
				0,
				MaxIndexOf(Edges)
			)
			{
				const Entity_Edge2d& Edge = *Edges[I];

				Global_Handle(Entity_Node2d) Side = Edge.Node(1);
				if (Side == &Node) Side = Edge.Node(0);

				Standard_Real length1 = Length(Node.Coord(), Side->Coord());
				Standard_Real length2 = Length(Side->Coord(), Node.Coord());

				Try_Exception_Handle_Exit(theSources_[Index_Of(Node.Index())] = MIN(theSources_[Index_Of(Node.Index())], theSources_[Index_Of(Side->Index())] * (1.0 + factor*length2)));
				Try_Exception_Handle_Exit(theSources_[Index_Of(Side->Index())] = MIN(theSources_[Index_Of(Side->Index())], theSources_[Index_Of(Node.Index())] * (1.0 + factor*length1)));
			}
		}
	}
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh2d::LaplacianSmoothing
(
	const Standard_Integer NbIterations, 
	const Standard_Real Factor
)
{
	Get_Const_Object(Nodes) = theMesh_.NodesSequence();

	forThose(Iter, 1, NbIterations)
	{
		forThose
		(
			Index,
			0,
			MaxIndexOf(Nodes)
		)
		{
			TColEntity_HAry1dOfEdge2d Edges;
			Nodes[Index]->Edges(Edges);

			Standard_Real Avg = 0.0;
			forThose
			(
				I,
				0,
				MaxIndexOf(Edges)
			)
			{
				const Entity_Edge2d& Edge = *Edges[I];

				Global_Handle(Entity_Node2d) Side = Edge.Node(1);
				if (Side == Nodes[Index]) Side = Edge.Node(0);

				Avg += theSources_[Index_Of(Side->Index())];
			}
			Avg /= (Standard_Real)Edges.Size();

			theSources_[Index_Of(Nodes[Index]->Index())] = theSources_[Index_Of(Nodes[Index]->Index())] + Factor*(Avg - theSources_[Index_Of(Nodes[Index]->Index())]);
		}
	}
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh2d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportField(theMesh_.Static(), Field(), File);
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh2d::ExportMeshToPlt(fstream & File) const
{
	theMesh_.ExportToPlt(File);
}
