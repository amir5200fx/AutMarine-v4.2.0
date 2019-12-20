#include <FvMesh2d.hxx>

#include <Entity_Box2dTools.hxx>
#include <Geom_ADTree2d.hxx>
#include <FvGeom_ElementConnectivity2d.hxx>
#include <FvGeom_Node2d.hxx>
#include <FvGeom_Face2d.hxx>
#include <FvGeom_Element2d.hxx>
#include <FvEntity_Node2d.hxx>
#include <FvEntity_TriElement2d.hxx>
#include <FvEntity_QuadElement2d.hxx>
#include <FvEntity_PolyElement2d.hxx>
#include <FvEntity_Element2dTools.hxx>
#include <FvEntity_BoundaryFace2d.hxx>
#include <FvEntity_Face2dTools.hxx>
#include <FvGeom_StaticMesh2d.hxx>
#include <TColFvEntity_HAry1dOfNode2d.hxx>
#include <TColFvEntity_HBasicQueueOfFace2d.hxx>

using namespace AutLib;
using namespace FvLib;
using namespace GeoLib;

AutLib::FvLib::FvMesh2d::FvMesh2d()
{
}

namespace AutLib
{
	namespace FvLib
	{
		static TColFvEntity_HAry1dOfNode2d GetPolygonNodes(const FvGeom_Element2d& theElement, const TColFvEntity_HAry1dOfNode2d& theNodes)
		{
			TColFvEntity_HAry1dOfNode2d Nodes(theElement.Connectivity()->Size());
			Get_Const_Object(Indices) = theElement.Connectivity();
			forThose(Index, 0, MaxIndexOf(Nodes))
				Nodes[Index] = theNodes.Value(Index_Of(Indices->Value(Index)));
			MOVE(Nodes);
		}

		static Global_Handle(FvEntity_Element2d) CreateElement(const FvGeom_Element2d& theElement, const TColFvEntity_HAry1dOfNode2d& theNodes)
		{
			Global_Handle(FvEntity_Element2d) newElement(0);

			switch (theElement.Type())
			{
			case FvGeom_ElementType_Triangle:
			{
				Get_Const_Object(Indices) = theElement.Connectivity();
				newElement = new FvEntity_TriElement2d(theElement.Index(), theNodes[Index_Of(Indices->Value(0))], theNodes[Index_Of(Indices->Value(1))], theNodes[Index_Of(Indices->Value(2))]);

				theNodes[Index_Of(Indices->Value(0))]->ImportElement(newElement);
				theNodes[Index_Of(Indices->Value(1))]->ImportElement(newElement);
				theNodes[Index_Of(Indices->Value(2))]->ImportElement(newElement);
				return newElement;
			}
			case FvGeom_ElementType_Quadrangle:
			{
				Get_Const_Object(Indices) = theElement.Connectivity();
				newElement = new FvEntity_QuadElement2d(theElement.Index(), theNodes[Index_Of(Indices->Value(0))], theNodes[Index_Of(Indices->Value(1))], theNodes[Index_Of(Indices->Value(2))], theNodes[Index_Of(Indices->Value(3))]);

				theNodes[Index_Of(Indices->Value(0))]->ImportElement(newElement);
				theNodes[Index_Of(Indices->Value(1))]->ImportElement(newElement);
				theNodes[Index_Of(Indices->Value(2))]->ImportElement(newElement);
				theNodes[Index_Of(Indices->Value(3))]->ImportElement(newElement);
				return newElement;
			}
			case FvGeom_ElementType_Polygon:
			{
				newElement = new FvEntity_PolyElement2d(theElement.Index(), GetPolygonNodes(theElement, theNodes));
				forThose(Index, 0, newElement->NbNodes() - 1)
				{
					((Global_Handle(FvEntity_Node2d))newElement->Node(Index))->ImportElement(newElement);
				}
				return newElement;
			}
			default:
				THROW_STANDARD_EXCEPTION("Wrong Element's type");
			}
		}

		static Global_Handle(FvEntity_Face2d) FindMinDistanceFace(const Geom_Pnt2d& theCentre, const TColFvEntity_HAry1dOfFace2d& theFaces)
		{
			Standard_Real MinDistance = RealLast();
			Global_Handle(FvEntity_Face2d) Face(0);
			forThose(Index, 0, MaxIndexOf(theFaces))
			{
				Debug_Null_Pointer(theFaces[Index]);

				Standard_Real Dis = DistanceSQ(theCentre, theFaces[Index]->Centre());
				if (Dis < MinDistance)
				{
					MinDistance = Dis;
					Face = theFaces[Index];
				}
			}
			return Face;
		}

		static void ConnectFaces(const TColFvEntity_HAry1dOfFace2d& theFaces)
		{
			Geom_ADTree2d<Global_Handle(FvEntity_Face2d)> Register;
			Register.SetCoordinateFunction(&FvEntity_Face2dTools::GetCoordOf);

			const Standard_Real Radius = 1.0E-6;
			forThose
			(
				Index,
				0,
				MaxIndexOf(theFaces)
			)
			{
				Debug_Null_Pointer(theFaces[Index]);

				Get_Const_Object(Face) = *theFaces[Index];

				TColFvEntity_HAry1dOfFace2d Items;
				Register.Search(Entity_Box2dTools::BoxOf(Face.Centre(), Radius), Items);

				if (Items.IsEmpty())
				{
					Try_Exception_Handle_Exit(Register.Insert(theFaces[Index]));
					continue;
				}

				if (Items.Size() EQUAL 1)
				{
					theFaces[Index]->SetPair(Items.First());
					Items.First()->SetPair(theFaces[Index]);

					Try_Exception_Handle_Exit(Register.Remove(Items.First()));
				}
				else
				{
					Global_Handle(FvEntity_Face2d) Item = FindMinDistanceFace(Face.Centre(), Items);

					Item->SetPair(theFaces[Index]);
					theFaces[Index]->SetPair(Item);

					Try_Exception_Handle_Exit(Register.Remove(Item));
				}
			}
		}
	}
}

void AutLib::FvLib::FvMesh2d::ImportFrom(const FvGeom_StaticMesh2d & theStaticMesh)
{
	theNodes_.Resize(theStaticMesh.NbNodes());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theNodes_)
	)
	{
		Get_Const_Object(Node) = theStaticMesh.Node(Index);
		theNodes_[Index] = new FvEntity_Node2d(Node.Index(), Node.Coord());
	}

	theElements_.Resize(theStaticMesh.NbElements());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theElements_)
	)
	{
		Get_Const_Object(Element) = theStaticMesh.Element(Index);
		theElements_[Index] = CreateElement(Element, theNodes_);

		FvEntity_Element2dTools::CalcGeometry(*theElements_[Index]);
	}

	TColFvEntity_HBasicQueueOfFace2d QFaces;
	Standard_Integer Count = 0;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theElements_)
	)
	{
		Debug_Null_Pointer(theElements_[Index]);
		Get_Object(Element) = *theElements_[Index];

		forThose
		(
			K,
			0,
			Element.NbNodes() - 1
		)
		{
			Standard_Integer V1 = K;
			Standard_Integer V2 = (V1 + 1) % Element.NbNodes();

			Global_Handle(FvEntity_Face2d) Face = new FvEntity_Face2d(++Count, theNodes_[Index_Of(V1)], theNodes_[Index_Of(V2)]);
			QFaces.EnQueue(Face);

			Face->SetElement(&Element);
			Element.SetFace(K, Face);
		}
	}
	QFaces.RetrieveTo(theFaces_);

	theBoundaries_.Resize(theStaticMesh.NbFaces());
	forThose
	(
		Index,
		0,
		theStaticMesh.NbFaces() - 1
	)
	{
		Get_Const_Object(StaticFace) = theStaticMesh.Face(Index);

		Standard_Integer V1 = StaticFace.Connectivity().Value(0);
		Standard_Integer V2 = StaticFace.Connectivity().Value(1);

		Global_Handle(FvEntity_Face2d) Face = new FvEntity_BoundaryFace2d(++Count, theNodes_[Index_Of(V1)], theNodes_[Index_Of(V2)]);
		theBoundaries_[Index] = Face;
	}

	TColFvEntity_HBasicQueueOfFace2d QtotFaces;
	QtotFaces.EnQueue(theFaces_);
	QtotFaces.EnQueue(theBoundaries_);

	TColFvEntity_HAry1dOfFace2d totFaces;
	QtotFaces.RetrieveTo(totFaces);

	ConnectFaces(totFaces);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theBoundaries_)
	)
	{
		Debug_Null_Pointer(theBoundaries_[Index]);
		Debug_Null_Pointer(theBoundaries_[Index]->Pair());
		Debug_Null_Pointer(theBoundaries_[Index]->Pair()->Element());

		((Global_Handle(FvEntity_Element2d))theBoundaries_[Index]->Pair()->Element())->SetPhysics(theBoundaries_[Index]->Physics());
	}
}