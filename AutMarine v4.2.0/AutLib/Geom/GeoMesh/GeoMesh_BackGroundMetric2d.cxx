#include <GeoMesh_BackGroundMetric2d.hxx>

#include <Primitive_Field.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_Eigen2d.hxx>
#include <Entity_Metric1Tools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Geometry_Distance.hxx>
#include <TColStd_Ary1dOfReal.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::GeoMesh_BackGroundMetric2d::GeoMesh_BackGroundMetric2d()
	: theCurrentElement_(NULL)
	, theBoundingBox_(NULL)
{
	InterSection_ = &Entity_Metric1Tools::IntersectionPD;
}

AutLib::GeoLib::GeoMesh_BackGroundMetric2d::GeoMesh_BackGroundMetric2d(const GeoMesh_TriangleMesh2d & StaticMesh)
	: theMesh_(StaticMesh)
	, theBoundingBox_(NULL)
{
	Debug_If_Condition_Message(NOT theMesh_.ElementsSequence().Size(), "Empty Elements sequence");
	theCurrentElement_ = theMesh_.ElementsSequence()[0];

	InterSection_ = &Entity_Metric1Tools::IntersectionPD;
}

AutLib::GeoLib::GeoMesh_BackGroundMetric2d::~GeoMesh_BackGroundMetric2d()
{
	FreePointer(theBoundingBox_);
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::SetBoundingBox(const Entity_Box2d & theBoundingBox)
{
	FreePointer(theBoundingBox_);
	theBoundingBox_ = new Entity_Box2d(theBoundingBox);
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::SetIntersection(Entity_Metric1(*InterSection)(const M_GEO Entity_Metric1 &, const M_GEO Entity_Metric1 &))
{
	InterSection_ = InterSection;
}

namespace AutLib
{
	namespace GeoLib
	{

		static Standard_Boolean HandleDegeneracy(Entity_Metric1& M1, Entity_Metric1& M2, Standard_Real Eps)
		{
			Standard_Real D1 = M1.Determinant();
			Standard_Real D2 = M2.Determinant();

			if (D1 > Eps AND D2 > Eps) return Standard_True;
			if (D1 < Eps AND D2 < Eps) return Standard_False;

			Entity_Metric1 M;
			if (D1 > D2) M = M1;
			else M = M2;

			M1 = M;
			M2 = M;

			return Standard_True;
		}
	}
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::HvCorrection
(
	const Standard_Real Factor,
	const Standard_Integer MaxInnerIteration
)
{
	Standard_Real factor = Factor;

	Get_Const_Object(Nodes) = theMesh_.NodesSequence();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		TColEntity_HAry1dOfEdge2d EdgesAroundNode = Nodes[Index]->Edges();

		Standard_Integer V1 = Nodes[Index]->Index();

		forThose(Iter, 1, MaxInnerIteration)
		{
			forThose
			(
				I,
				0,
				MaxIndexOf(EdgesAroundNode)
			)
			{
				Standard_Integer V2 = EdgesAroundNode[I]->Node(0)->Index();
				if (V2 EQUAL V1) V2 = EdgesAroundNode[I]->Node(1)->Index();

				if (NOT ::HandleDegeneracy(theSources_[Index_Of(V1)], theSources_[Index_Of(V2)], theTolerance_)) continue;

				Standard_Real Length1 = Geometry_Distance::Distance(Nodes[Index_Of(V1)]->Coord(), Nodes[Index_Of(V2)]->Coord(), theSources_[Index_Of(V1)]);
				Standard_Real Length2 = Geometry_Distance::Distance(Nodes[Index_Of(V1)]->Coord(), Nodes[Index_Of(V2)]->Coord(), theSources_[Index_Of(V2)]);

				Standard_Real Down1 = 1.0 + factor*Length1;
				Standard_Real Down2 = 1.0 + factor*Length2;

				Standard_Real Gama1 = 1.0 / (Down1*Down1);
				Standard_Real Gama2 = 1.0 / (Down2*Down2);

				Try_Exception_Handle_Exit(theSources_[Index_Of(V1)] = InterSection_(theSources_[Index_Of(V1)], Gama2*theSources_[Index_Of(V2)]));
				Try_Exception_Handle_Exit(theSources_[Index_Of(V2)] = InterSection_(theSources_[Index_Of(V2)], Gama1*theSources_[Index_Of(V1)]));
			}
		}
	}

	/*forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		TColEntity_HAry1dOfEdge2d EdgesAroundNode = Nodes[MaxIndexOf(Nodes) - Index]->Edges();

		Standard_Integer V1 = Nodes[MaxIndexOf(Nodes) - Index]->Index();

		forThose(Iter, 1, MaxInnerIteration)
		{
			forThose
			(
				I,
				0,
				MaxIndexOf(EdgesAroundNode)
			)
			{
				Standard_Integer V2 = EdgesAroundNode[I]->Node(0)->Index();
				if (V2 EQUAL V1) V2 = EdgesAroundNode[I]->Node(1)->Index();

				if (NOT::HandleDegeneracy(theSources_[Index_Of(V1)], theSources_[Index_Of(V2)], theTolerance_)) continue;

				Standard_Real Length1 = Geometry_Distance::Distance(Nodes[Index_Of(V1)]->Coord(), Nodes[Index_Of(V2)]->Coord(), theSources_[Index_Of(V1)]);
				Standard_Real Length2 = Geometry_Distance::Distance(Nodes[Index_Of(V1)]->Coord(), Nodes[Index_Of(V2)]->Coord(), theSources_[Index_Of(V2)]);

				Standard_Real Down1 = 1.0 + factor*Length1;
				Standard_Real Down2 = 1.0 + factor*Length2;

				Standard_Real Gama1 = 1.0 / (Down1*Down1);
				Standard_Real Gama2 = 1.0 / (Down2*Down2);

				Try_Exception_Handle_Exit(theSources_[Index_Of(V1)] = InterSection_(theSources_[Index_Of(V1)], Gama2*theSources_[Index_Of(V2)]));
				Try_Exception_Handle_Exit(theSources_[Index_Of(V2)] = InterSection_(theSources_[Index_Of(V2)], Gama1*theSources_[Index_Of(V1)]));
			}
		}
	}*/
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::LaplacianSmoothing
(
	const Standard_Integer NbIterations,
	const Standard_Real MaxRatio,
	const Standard_Real Factor
)
{
	TColGeom_Ary1dOfPnt2d E1Vector(theSources_.Size());
	TColGeom_Ary1dOfPnt2d E2Vector(theSources_.Size());

	TColStd_Ary1dOfReal Lamda1(theSources_.Size());
	TColStd_Ary1dOfReal Lamda2(theSources_.Size());

	TColStd_Ary1dOfReal H1(theSources_.Size());
	TColStd_Ary1dOfReal H2(theSources_.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(theSources_)
	)
	{
		Entity_Eigen2d Eigen;
		Eigen.CalcEigen(theSources_[Index]);

		E1Vector[Index] = Eigen.E1();
		E2Vector[Index] = Eigen.E2();

		H1[Index] = Eigen.H1();
		H2[Index] = Eigen.H2();

		if (Eigen.H1() / Eigen.H2() > MaxRatio) H1[Index] = Eigen.H2()*MaxRatio;
		if (Eigen.H2() / Eigen.H1() > MaxRatio) H2[Index] = Eigen.H1()*MaxRatio;
	}

	theMesh_.LaplacianSmoothing(E1Vector, NbIterations, Factor);
	theMesh_.LaplacianSmoothing(E2Vector, NbIterations, Factor);
	theMesh_.LaplacianSmoothing(H1, NbIterations, Factor);
	theMesh_.LaplacianSmoothing(H2, NbIterations, Factor);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theSources_)
	)
	{
		Standard_Real lamda1 = 1.0 / (H1[Index] * H1[Index]);
		Standard_Real lamda2 = 1.0 / (H2[Index] * H2[Index]);

		theSources_[Index] = Entity_Metric1Tools::CalcMetric(lamda1, lamda2, E1Vector[Index], E2Vector[Index]);
	}
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::InitiateCurrentElement() const
{
	theCurrentElement_ = theMesh_.FirstElement();
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::SetCurrentElement(const Global_Handle(Entity_Element2d) theElement) const
{
	theCurrentElement_ = (Global_Handle(Entity_Element2d))theElement;
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::ExportToPlt(fstream & File) const
{
	Get_Const_Object(Points) = theMesh_.NodesSequence();
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Try_Exception_Handle_Exit(theSources_[Index].ExportToPlt(Points[Index]->Coord(), File));
	}
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::ExportToPlt
(
	fstream & File, 
	const Standard_Real theElementSize
) const
{
	Get_Const_Object(Points) = theMesh_.NodesSequence();
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Try_Exception_Handle_Exit(((1.0 / (theElementSize*theElementSize))*theSources_[Index]).ExportToPlt(Points[Index]->Coord(), File));
	}
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::ExportMeshToPlt(fstream & File) const
{
	theMesh_.ExportToPlt(File);
}

void AutLib::GeoLib::GeoMesh_BackGroundMetric2d::ExportMetricDeterminantToPlt(fstream & File) const
{
	Entity_Triangulation2d Static = theMesh_.Static();

	Get_Const_Object(Points) = Static.Points();

	Primitive_Field Field(1, Static.NbPoints());
	Field.SetVariablesName(" Determinant(0-1)");

	TColStd_Ary1dOfReal D(Static.NbPoints());

	forThose(Index, 0, MaxIndexOf(theSources_))
	{
		D[Index] = theSources_[Index].Determinant();
	}

	Standard_Real Dmax = D[0];
	forThose(Index, 0, MaxIndexOf(D)) if (D[Index] > Dmax) Dmax = D[Index];

	D /= Dmax;

	forThose(Index, 0, MaxIndexOf(theSources_))
	{
		Try_Exception_Handle_Exit(Field.SetValue(Index, 0, D[Index]));
	}

	Try_Exception_Handle_Exit(Static.ExportToPlt(Field, File));
}