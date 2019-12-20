#include <SizeMap2d_UniSizeTools.hxx>

#include <Entity_Box2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <SubDivide_BalancedQuadTree.hxx>
#include <SizeMap2d_UniSize.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

namespace AutLib
{
	namespace MeshLib
	{

		class QuadTreeObject
		{

		public:

			QuadTreeObject() {}

		};

		class QuadTreeObjectTools
		{

		public:

			static Standard_Boolean Subdivide(const Entity_Box2d& theBox, const Global_Handle(QuadTreeObject) theObject) { return Standard_False; }

		};
	}
}

Global_Handle(GeoLib::GeoMesh_BackGroundMesh2d) AutLib::MeshLib::SizeMap2d_UniSizeTools::GetBackMeshFrom(const SizeMap2d_UniSize & theSizeMap, const GeoLib::Entity_Box2d & theBox)
{
	QuadTreeObject Object;

	SubDivide_BalancedQuadTree<QuadTreeObject> Tree;

	Tree.SetDomain(theBox);

	Tree.SetMinLevel(2);
	Tree.SetMaxLevel(2);

	Tree.SetObject(&Object);
	Tree.SetSubDivider(&QuadTreeObjectTools::Subdivide);

	Tree.Init();
	Tree.Perform();

	// Retrieve Boxes of the leaves
	TColEntity_HAry1dOfBox2d Boxes;
	Tree.RetrieveTo(Boxes);

	// Triangulation of the boxes to generate a background mesh
	Entity_Triangulation2d Triangulation;
	Entity_Box2dTools::Triangulation(Boxes, &Triangulation);

	Global_Handle(GeoMesh_BackGroundMesh2d) BackMesh = new GeoMesh_BackGroundMesh2d;
	BackMesh->Mesh().Construct(Triangulation);
	BackMesh->InitiateCurrentElement();
	BackMesh->SetBoundingBox(theBox);

	Standard_Real ElementSize = theSizeMap.BaseSize();

	Get_Object(Sources) = BackMesh->Sources();
	Get_Const_Object(Nodes) = BackMesh->Mesh().NodesSequence();
	Sources.Resize(Nodes.Size());
	forThose(Index, 0, MaxIndexOf(Sources))
	{
		Sources[Index] = ElementSize;
	}
	return BackMesh;
}

