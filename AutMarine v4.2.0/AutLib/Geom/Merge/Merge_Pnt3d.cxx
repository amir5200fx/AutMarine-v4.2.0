#include <Merge_Pnt3d.hxx>

#include <Geometry_Tools.hxx>
#include <Geometry_Distance.hxx>
#include <TColGeom_BasicQueueOfPnt3d.hxx>
#include <Global_DefineException.hxx>

#define KEYX(x) (AutLib::GeoLib::Geometry_Tools::Round(MAX(x - theParams_.Xmin(), 0) / theParams_.Delta()))
#define KEYY(x) (AutLib::GeoLib::Geometry_Tools::Round(MAX(x - theParams_.Ymin(), 0) / theParams_.Delta()))
#define KEYZ(x) (AutLib::GeoLib::Geometry_Tools::Round(MAX(x - theParams_.Zmin(), 0) / theParams_.Delta()))

#define FINDKEY(x, y, z) (KEYX(x) + KEYY(y) + KEYZ(z))

using namespace AutLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_RESOLUTION = 1.0E-3;
static const Standard_Real DEFAULT_RADIUS = 1.0E-6;

AutLib::GeoLib::Merge_Pnt3d::Merge_Pnt3d()
	: theResolution_(DEFAULT_RESOLUTION)
	, theRadius_(DEFAULT_RADIUS)
{
}

AutLib::GeoLib::Merge_Pnt3d::Merge_Pnt3d
(
	const Standard_Real Resolution,
	const Standard_Real Radius
)
	: theResolution_(Resolution)
	, theRadius_(Radius)
{
}

const TColStd_Ary1dOfInteger & AutLib::GeoLib::Merge_Pnt3d::Indices() const
{
	return theIndices_;
}

TColGeom_Ary1dOfPnt3d AutLib::GeoLib::Merge_Pnt3d::CompactPoints() const
{
	TColGeom_BasicQueueOfPnt3d MergedPoints;
	Get_Const_Object(Points) = *thePoints_;

	forThose(Index, 0, MaxIndexOf(Points))
		if (theIndices_[Index + 1] EQUAL Index + 1) { MergedPoints.EnQueue(Points[Index]); }
	return MergedPoints.Retrive();
}

TColStd_Ary1dOfInteger AutLib::GeoLib::Merge_Pnt3d::CompactIndices() const
{
	TColStd_Ary1dOfInteger Num(theIndices_.Size());

	forThose(Index, 0, MaxIndexOf(theIndices_))
	{
		if (theIndices_[Index] EQUAL Index) { Num[Index] = -1; }
		else { Num[Index] = theIndices_[Index]; }
	}

	Num[0] = 0;

	Standard_Integer k = 0;

	forThose
	(
		Index,
		1,
		MaxIndexOf(Num)
	)
	{
		if (Num[Index] < 0)
			Num[Index] = ++k;
	}

	forThose(Index, 1, MaxIndexOf(Num))
	{
		if (theIndices_[Index] NOT_EQUAL Index)
			Try_Exception_Handle_Exit(Num[Index] = Num[Num[Index]]);
	}

	MOVE(Num);
}

void AutLib::GeoLib::Merge_Pnt3d::SetCoords(const Global_Handle(TColGeom_Ary1dOfPnt3d) Points)
{
	thePoints_ = Points;
}

namespace AutLib
{
	namespace GeoLib
	{
		TColMerge_Ary1dOfMerge3dNode GetNodes(const TColGeom_Ary1dOfPnt3d & Points)
		{
			TColMerge_Ary1dOfMerge3dNode Nodes(Points.Size());

			forThose
			(
				Index,
				0,
				MaxIndexOf(Nodes)
			)
			{
				Nodes[Index].SetIndex(Index + 1);
				Nodes[Index].SetCoord(Points[Index]);
			}

			MOVE(Nodes);
		}

		void FindMinMax
		(
			const TColMerge_Ary1dOfMerge3dNode& Nodes,
			Standard_Real& Xmin,
			Standard_Real& Xmax,
			Standard_Real& Ymin,
			Standard_Real& Ymax,
			Standard_Real& Zmin,
			Standard_Real& Zmax
		)
		{
			Get_Const_Object(First) = Nodes.First().Coord();

			Xmin = Xmax = First.X();
			Ymin = Ymax = First.Y();
			Zmin = Zmax = First.Z();

			forThose
			(
				Index,
				1,
				MaxIndexOf(Nodes)
			)
			{
				Get_Const_Object(Point) = Nodes.Value(Index).Coord();

				if (Point.X() < Xmin)
					Xmin = Point.X();

				if (Point.Y() < Ymin)
					Ymin = Point.Y();

				if (Point.Z() < Zmin)
					Zmin = Point.Z();

				if (Point.X() > Xmax)
					Xmax = Point.X();

				if (Point.Y() > Ymax)
					Ymax = Point.Y();

				if (Point.Z() > Zmax)
					Zmax = Point.Z();
			}
		}
	}
}

void AutLib::GeoLib::Merge_Pnt3d::Perform()
{
	if (IsNULL(thePoints_))
	{
		THROW_STANDARD_EXCEPTION(" No Point Lists detected");
	}

	Get_Const_Object(Points) = *thePoints_;

	if (NOT Points.Size())
	{
		THROW_STANDARD_EXCEPTION(" Point Lists is empty");
	}

	theIndices_.Resize(Points.Size() + 1);
	theIndices_.Init(0);

	if (Points.Size() EQUAL 1)
	{
		theIndices_[1] = 1;
		return;
	}

	Merging
	(
		GetNodes(Points),
		theIndices_
	);
}

TColMerge_Ary1dOfMerge3dNode AutLib::GeoLib::Merge_Pnt3d::Search
(
	const Standard_Real Xo,
	const Standard_Real Yo,
	const Standard_Real Zo,
	const Merge3dTable & Grid
) const
{
	Standard_Real d = 0.499*theParams_.Delta();

	TColStd_Ary1dOfInteger Indices(27);

	Indices[0] = FINDKEY(Xo - d, Yo - d, Zo - d);
	Indices[1] = FINDKEY(Xo, Yo - d, Zo - d);
	Indices[2] = FINDKEY(Xo + d, Yo - d, Zo - d);
	Indices[3] = FINDKEY(Xo - d, Yo, Zo - d);
	Indices[4] = FINDKEY(Xo, Yo, Zo - d);
	Indices[5] = FINDKEY(Xo + d, Yo, Zo - d);
	Indices[6] = FINDKEY(Xo - d, Yo + d, Zo - d);
	Indices[7] = FINDKEY(Xo, Yo + d, Zo - d);
	Indices[8] = FINDKEY(Xo + d, Yo + d, Zo - d);

	Indices[9] = FINDKEY(Xo - d, Yo - d, Zo);
	Indices[10] = FINDKEY(Xo, Yo - d, Zo);
	Indices[11] = FINDKEY(Xo + d, Yo - d, Zo);
	Indices[12] = FINDKEY(Xo - d, Yo, Zo);
	Indices[13] = FINDKEY(Xo, Yo, Zo);
	Indices[14] = FINDKEY(Xo + d, Yo, Zo);
	Indices[15] = FINDKEY(Xo - d, Yo + d, Zo);
	Indices[16] = FINDKEY(Xo, Yo + d, Zo);
	Indices[17] = FINDKEY(Xo + d, Yo + d, Zo);

	Indices[18] = FINDKEY(Xo - d, Yo - d, Zo + d);
	Indices[19] = FINDKEY(Xo, Yo - d, Zo + d);
	Indices[20] = FINDKEY(Xo + d, Yo - d, Zo + d);
	Indices[21] = FINDKEY(Xo - d, Yo, Zo + d);
	Indices[22] = FINDKEY(Xo, Yo, Zo + d);
	Indices[23] = FINDKEY(Xo + d, Yo, Zo + d);
	Indices[24] = FINDKEY(Xo - d, Yo + d, Zo + d);
	Indices[25] = FINDKEY(Xo, Yo + d, Zo + d);
	Indices[26] = FINDKEY(Xo + d, Yo + d, Zo + d);

	TColStd_Ary1dOfInteger MergedIndices = Geometry_Tools::RemoveMults(Indices);

	TColMerge_BasicQueueOfMerge3dNode Nodes;

	forThose
	(
		Index,
		0,
		MaxIndexOf(MergedIndices)
	)
	{
		Get_Const_Pointer(Ptr) = Grid[MergedIndices[Index]];

		if (NOT Ptr) continue;

		Debug_Null_Pointer(Ptr);

		Nodes.EnQueue(Ptr->Retrive());
	}

	return Nodes.Retrive();
}

void AutLib::GeoLib::Merge_Pnt3d::Resolution(const TColMerge_Ary1dOfMerge3dNode & Nodes)
{
	Standard_Real
		Xmin,
		Xmax,
		Ymin,
		Ymax,
		Zmin,
		Zmax;

	FindMinMax
	(
		Nodes,
		Xmin,
		Xmax,
		Ymin,
		Ymax,
		Zmin,
		Zmax
	);

	Standard_Real Dx = Xmax - Xmin;
	Standard_Real Dy = Ymax - Ymin;
	Standard_Real Dz = Zmax - Zmin;

	Standard_Real D = MAX(Dx, MAX(Dy, Dz));

	Debug_If_Condition(D <= 0);

	theParams_.SetDelta(2.0*theResolution_*D);

	if (theParams_.Delta() < theRadius_) theParams_.SetDelta(theRadius_);

	Xmin -= 2 * theParams_.Delta();
	Ymin -= 2 * theParams_.Delta();
	Zmin -= 2 * theParams_.Delta();

	theParams_.SetXmin(Xmin);
	theParams_.SetYmin(Ymin);
	theParams_.SetZmin(Zmin);

	theParams_.SetMaxIndex(FINDKEY(Xmax + 2.0*theParams_.Delta(), Ymax + 2.0*theParams_.Delta(), Zmax + 2.0*theParams_.Delta()));

	Debug_If_Condition(theParams_.MaxIndex() <= 0);
}

void AutLib::GeoLib::Merge_Pnt3d::Merging
(
	const TColMerge_Ary1dOfMerge3dNode & Nodes,
	TColStd_Ary1dOfInteger & Indices
)
{
	Resolution(Nodes);

	Merge3dTable Grid(theParams_.MaxIndex() + 1);

	Grid.Init(NULL);

	Standard_Real
		Xi,
		Yi,
		Zi,
		Xq,
		Yq,
		Zq;

	Standard_Integer
		Key,
		MaxKey,
		MinKey,
		Cond,
		Flag;

	Standard_Integer MaxIndex = theParams_.MaxIndex();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Get_Const_Object(Point) = Nodes.Value(Index).Coord();

		Xi = Point.X();
		Yi = Point.Y();
		Zi = Point.Z();

		Key = FINDKEY(Xi, Yi, Zi);

		Debug_If_Condition(Key < 0 OR Key > MaxIndex);

		MaxKey = FINDKEY(Xi + theRadius_, Yi + theRadius_, Zi + theRadius_);
		MinKey = FINDKEY(Xi - theRadius_, Yi - theRadius_, Zi - theRadius_);

		Debug_If_Condition(MinKey < 0 OR MinKey > MaxIndex);
		Debug_If_Condition(MaxKey < 0 OR MaxKey > MaxIndex);

		Cond = 0;

		forThose
		(
			j,
			MinKey,
			MaxKey
		)
		{
			if (Grid[j])
			{
				Cond = 1;

				break;
			}
		}

		if (NOT Cond)
		{
			Grid[Key] = new TColMerge_BasicQueueOfMerge3dNode;

			Grid[Key]->EnQueue(Nodes[Index]);

			Try_Exception_Handle_Exit(Indices[Nodes[Index].Index()] = Nodes[Index].Index());
		}
		else
		{
			TColMerge_Ary1dOfMerge3dNode Found = Search(Xi, Yi, Zi, Grid);

			Flag = 0;

			forThose
			(
				j,
				0,
				MaxIndexOf(Found)
			)
			{
				Get_Const_Object(FoundPoint) = Found[j].Coord();

				Xq = FoundPoint.X();
				Yq = FoundPoint.Y();
				Zq = FoundPoint.Z();

				if (Geometry_Distance::InfNorm(Xi, Yi, Zi, Xq, Yq, Zq) <= theRadius_)
				{
					if (Geometry_Distance::TwoNorm(Xi, Yi, Zi, Xq, Yq, Zq) <= theRadius_)
					{
						Flag = 1;

						Try_Exception_Handle_Exit(Indices[Nodes[Index].Index()] = Found[j].Index());

						break;
					}
				}
			}

			if (NOT Flag)
			{
				if (IsNULL(Grid[Key]))
				{
					Grid[Key] = new TColMerge_BasicQueueOfMerge3dNode;
				}

				Try_Exception_Handle_Exit(Grid[Key]->EnQueue(Nodes[Index]));

				Try_Exception_Handle_Exit(Indices[Nodes[Index].Index()] = Nodes[Index].Index());
			}
		}
	}

	FreeMemory(Grid);
}