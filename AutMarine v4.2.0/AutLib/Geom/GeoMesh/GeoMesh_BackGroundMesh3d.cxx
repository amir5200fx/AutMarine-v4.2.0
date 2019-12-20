#include <GeoMesh_BackGroundMesh3d.hxx>

#include <Entity_Box3d.hxx>
#include <Entity_Element3dTools.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <GeoMesh_TetrahedronMesh.hxx>
#include <Primitive_Field.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;

AutLib::GeoLib::GeoMesh_BackGroundMesh3d::GeoMesh_BackGroundMesh3d()
	: theCurrentElement_(NULL)
{
}

//AutLib::GeoLib::GeoMesh_BackGroundMesh3d::GeoMesh_BackGroundMesh3d(const GeoMesh_TetrahedronMesh & theStaticMesh)
//	: theMesh_(theStaticMesh)
//{
//	Debug_If_Condition_Message(NOT theMesh_.ElementsSequence().Size(), "Empty Elements sequence");
//	theCurrentElement_ = theMesh_.ElementsSequence()[0];
//}

AutLib::GeoLib::GeoMesh_BackGroundMesh3d::~GeoMesh_BackGroundMesh3d()
{
	FreePointer(theBoundingBox_);
}

Standard_Real AutLib::GeoLib::GeoMesh_BackGroundMesh3d::ElementSize
(
	const Geom_Pnt3d & theCoord,
	Standard_Boolean & Sense
) const
{
	Global_Handle(Entity_Element3d) ElementPtr = theMesh_.TetrahedronLocation(theCurrentElement_, theCoord);

	if (NOT ElementPtr)
	{
		Sense = Standard_False;
		return -1;
	}

	theCurrentElement_ = ElementPtr;

	const Entity_Element3d& Element = *ElementPtr;

	Standard_Integer V1, V2, V3;

	Entity_Element3dTools::FacetIndices(0, V1, V2, V3);
	Standard_Real A1 = Geometry_Tools::VolumeOfTetrahedron
	(
		Element.Node(Index_Of(V1))->Coord(),
		Element.Node(Index_Of(V2))->Coord(),
		Element.Node(Index_Of(V3))->Coord(),
		theCoord
	);

	Entity_Element3dTools::FacetIndices(1, V1, V2, V3);
	Standard_Real A2 = Geometry_Tools::VolumeOfTetrahedron
	(
		Element.Node(Index_Of(V1))->Coord(),
		Element.Node(Index_Of(V2))->Coord(),
		Element.Node(Index_Of(V3))->Coord(),
		theCoord
	);

	Entity_Element3dTools::FacetIndices(2, V1, V2, V3);
	Standard_Real A3 = Geometry_Tools::VolumeOfTetrahedron
	(
		Element.Node(Index_Of(V1))->Coord(), 
		Element.Node(Index_Of(V2))->Coord(),
		Element.Node(Index_Of(V3))->Coord(),
		theCoord
	);

	Entity_Element3dTools::FacetIndices(3, V1, V2, V3);
	Standard_Real A4 = Geometry_Tools::VolumeOfTetrahedron
	(
		Element.Node(Index_Of(V1))->Coord(),
		Element.Node(Index_Of(V2))->Coord(), 
		Element.Node(Index_Of(V3))->Coord(), 
		theCoord
	);

	Standard_Real H1 = theSources_[Index_Of(Element.Node0()->Index())];
	Standard_Real H2 = theSources_[Index_Of(Element.Node1()->Index())];
	Standard_Real H3 = theSources_[Index_Of(Element.Node2()->Index())];
	Standard_Real H4 = theSources_[Index_Of(Element.Node3()->Index())];

	Sense = Standard_True;

	return (A1*H1 + A2*H2 + A3*H3 + A4*H4) / (A1 + A2 + A3 + A4);
}

Primitive_Field AutLib::GeoLib::GeoMesh_BackGroundMesh3d::Field() const
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

void AutLib::GeoLib::GeoMesh_BackGroundMesh3d::SetBoundingBox(const Entity_Box3d & theBoundingBox)
{
	FreePointer(theBoundingBox_);
	theBoundingBox_ = new Entity_Box3d(theBoundingBox);
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh3d::InitiateCurrentElement() const
{
	theCurrentElement_ = theMesh_.FirstElement();
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh3d::HvCorrection
(
	const Standard_Real Factor,
	const Standard_Integer MaxInnerIteration
) const
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
		const Entity_Node3d& Node = *Nodes[Index];

		TColEntity_HAry1dOfEdge3d Edges;
		Node.Edges(Edges);

		forThose
		(
			Iter,
			1,
			MaxInnerIteration
		)
		{
			forThose
			(
				I,
				0,
				MaxIndexOf(Edges)
			)
			{
				const Entity_Edge3d& Edge = *Edges[I];

				Global_Handle(Entity_Node3d) Side = Edge.Node(1);
				if (Side == &Node) Side = Edge.Node(0);

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
		const Entity_Node3d& Node = *Nodes[MaxIndexOf(Nodes) - Index];

		TColEntity_HAry1dOfEdge3d Edges;
		Node.Edges(Edges);

		forThose
		(
			Iter, 
			1, 
			MaxInnerIteration
		)
		{
			forThose
			(
				I,
				0,
				MaxIndexOf(Edges)
			)
			{
				const Entity_Edge3d& Edge = *Edges[I];

				Global_Handle(Entity_Node3d) Side = Edge.Node(1);
				if (Side == &Node) Side = Edge.Node(0);

				Standard_Real length1 = Length(Node.Coord(), Side->Coord());
				Standard_Real length2 = Length(Side->Coord(), Node.Coord());

				Try_Exception_Handle_Exit(theSources_[Index_Of(Node.Index())] = MIN(theSources_[Index_Of(Node.Index())], theSources_[Index_Of(Side->Index())] * (1.0 + factor*length2)));
				Try_Exception_Handle_Exit(theSources_[Index_Of(Side->Index())] = MIN(theSources_[Index_Of(Side->Index())], theSources_[Index_Of(Node.Index())] * (1.0 + factor*length1)));
			}
		}
	}
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh3d::LaplacianSmoothing
(
	const Standard_Integer NbIterations,
	const Standard_Real Factor
) const
{
	Get_Const_Object(Nodes) = theMesh_.NodesSequence();

	forThose
	(
		Iter,
		1, 
		NbIterations
	)
	{
		forThose
		(
			Index,
			0,
			MaxIndexOf(Nodes)
		)
		{
			TColEntity_HAry1dOfEdge3d Edges;
			Nodes[Index]->Edges(Edges);

			Standard_Real Avg = 0.0;
			forThose
			(
				I,
				0,
				MaxIndexOf(Edges)
			)
			{
				const Entity_Edge3d& Edge = *Edges[I];

				Global_Handle(Entity_Node3d) Side = Edge.Node(1);
				if (Side == Nodes[Index]) Side = Edge.Node(0);

				Avg += theSources_[Index_Of(Side->Index())];
			}
			Avg /= (Standard_Real)Edges.Size();

			theSources_[Index_Of(Nodes[Index]->Index())] = theSources_[Index_Of(Nodes[Index]->Index())] + Factor*(Avg - theSources_[Index_Of(Nodes[Index]->Index())]);
		}
	}
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh3d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportField(theMesh_.Static(), Field(), File);
}

void AutLib::GeoLib::GeoMesh_BackGroundMesh3d::ExportMeshToPlt(fstream & File) const
{
	theMesh_.ExportToPlt(File);
}