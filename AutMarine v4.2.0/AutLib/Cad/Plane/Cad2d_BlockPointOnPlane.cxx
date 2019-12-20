#include <Cad2d_BlockPointOnPlane.hxx>

#include <Cad2d_PointOnPlane.hxx>
#include <Geom_Pnt2d.hxx>
#include <Geometry_Tools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Cad2d_BlockPointOnPlane::Cad2d_BlockPointOnPlane()
	: theName_("Block Point")
{
}

AutLib::CadLib::Cad2d_BlockPointOnPlane::Cad2d_BlockPointOnPlane
(
	const TColCad2d_HAry1dOfPointOnPlane & Points,
	const Standard_String Name
)
	: theName_(Name)
{
	SetPoints(Points);
}

AutLib::CadLib::Cad2d_BlockPointOnPlane::~Cad2d_BlockPointOnPlane()
{
	ReleaseMemory();
}

M_AUT TColCad2d_HAry1dOfPointOnPlane AutLib::CadLib::Cad2d_BlockPointOnPlane::Points() const
{
	TColCad2d_HAry1dOfPointOnPlane Points((Standard_Integer)thePoints_.size());
	Standard_Integer K = 0;

	TColCad2d_IndexedMapOfPointOnPlane::const_iterator Iter = thePoints_.begin();
	while (Iter NOT_EQUAL thePoints_.end())
	{
		Points[K++] = Iter->second;
		Iter++;
	}

	MOVE(Points);
}

Standard_String AutLib::CadLib::Cad2d_BlockPointOnPlane::Name() const
{
	return theName_;
}

Standard_Integer AutLib::CadLib::Cad2d_BlockPointOnPlane::Size() const
{
	return (Standard_Integer)thePoints_.size();
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::SelectSharpCorners(const Standard_Real theAngle)
{
	Standard_Real Angle = Geometry_Tools::DegToRadian(theAngle);

	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveTo(Points);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);

		if (Points[Index]->IsSharp(Angle)) { SelectPoint(Points[Index]->Index()); }
	}
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::SelectPoint(const Standard_Integer Index) const
{
	TColCad2d_IndexedMapOfPointOnPlane::const_iterator Iter = thePoints_.find(Index);
	if (Iter EQUAL thePoints_.end())
	{
		cout << " The Point is NOT in the List" << endl;
		return;
	}

	theSelected_.EnQueue(Index);
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::UnSelectAll() const
{
	theSelected_.Clear();
}

Standard_Boolean AutLib::CadLib::Cad2d_BlockPointOnPlane::IsContains(const Standard_Integer theIndex) const
{
	TColCad2d_IndexedMapOfPointOnPlane::const_iterator Iter = thePoints_.find(theIndex);

	if (Iter EQUAL thePoints_.end())
	{
		return Standard_False;
	}
	return Standard_True;
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::Split(Cad2d_BlockPointOnPlane & Other)
{
	if (NOT theSelected_.Size())
		return;

	Standard_Integer Index;
	while (theSelected_.DeQueue(Index))
	{
		TColCad2d_IndexedMapOfPointOnPlane::const_iterator Iter = thePoints_.find(Index);

		Debug_If_Condition(Iter EQUAL thePoints_.end());

		Other.Add(Iter->second);
		thePoints_.erase(Iter);
	}
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::SetName(const Standard_String Name)
{
	theName_ = Name;
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::SetPoints(const TColCad2d_HAry1dOfPointOnPlane & Points)
{
	forThose(Index, 0, MaxIndexOf(Points))
		Try_Exception_Handle_Exit(Add(Points[Index]));
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::RetrieveTo(TColCad2d_HAry1dOfPointOnPlane & Points) const
{
	TColCad2d_HBasicQueueOfPointOnPlane QPoints;
	RetrieveTo(QPoints);

	QPoints.RetrieveTo(Points);
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::RetrieveTo(TColCad2d_HBasicQueueOfPointOnPlane & Points) const
{
	TColCad2d_IndexedMapOfPointOnPlane::const_iterator Iter = thePoints_.begin();
	while (Iter NOT_EQUAL thePoints_.end())
	{
		Points.EnQueue(Iter->second);
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::RetrieveTo(TColGeom_Ary1dOfPnt2d & Points) const
{
	TColGeom_BasicQueueOfPnt2d QPoints;
	RetrieveTo(QPoints);

	QPoints.RetrieveTo(Points);
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::RetrieveTo(TColGeom_BasicQueueOfPnt2d & Points) const
{
	TColCad2d_IndexedMapOfPointOnPlane::const_iterator Iter = thePoints_.begin();
	while (Iter NOT_EQUAL thePoints_.end())
	{
		Points.EnQueue(Iter->second->Coord());
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::Add(Global_Handle(Cad2d_PointOnPlane) Point)
{
	std::pair<TColCad2d_IndexedMapOfPointOnPlane::iterator, Standard_Boolean> Insert;
	Insert = thePoints_.insert(std::pair<Standard_Integer, Global_Handle(Cad2d_PointOnPlane)>(Point->Index(), Point));

	if (Insert.second EQUAL Standard_False)
	{
		THROW_STANDARD_EXCEPTION(" Duplicate Data");
		return;
	}
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::Remove(Global_Handle(Cad2d_PointOnPlane) Point)
{
	TColCad2d_IndexedMapOfPointOnPlane::iterator Iter = thePoints_.find(Point->Index());

	if (Iter EQUAL thePoints_.end())
	{
		THROW_STANDARD_EXCEPTION(" Not found the Curve");
		return;
	}

	thePoints_.erase(Iter);
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::Remove(const Standard_Integer theIndex)
{
	TColCad2d_IndexedMapOfPointOnPlane::iterator Iter = thePoints_.find(theIndex);

	if (Iter EQUAL thePoints_.end())
	{
		THROW_STANDARD_EXCEPTION(" Not found the Curve");
		return;
	}

	thePoints_.erase(Iter);
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::Print(Standard_OStream & Ostream) const
{
	Ostream << " Nb. of Points = " << Size() << endl;
	Ostream << " Point List: " << endl;

	TColCad2d_IndexedMapOfPointOnPlane::const_iterator Iter = thePoints_.begin();
	while (Iter NOT_EQUAL thePoints_.end())
	{
		Ostream << Iter->first << "  ";
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::Clear()
{
	thePoints_.clear();
}

Global_Handle(Cad2d_BlockPointOnPlane) AutLib::CadLib::Cad2d_BlockPointOnPlane::Copy(const TColCad2d_IndexedMapOfPointOnPlane& theBlock) const
{
	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveTo(Points);

	Global_Handle(Cad2d_BlockPointOnPlane) Copy = new Cad2d_BlockPointOnPlane;
	Get_Object(Block) = Copy->thePoints_;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);

		Global_Handle(Cad2d_PointOnPlane) Point = theBlock.at(Points[Index]->Index());

		Debug_Null_Pointer(Point);

		std::pair<TColCad2d_IndexedMapOfPointOnPlane::iterator, Standard_Boolean> Insert;
		Insert = Block.insert(std::pair<Standard_Integer, Global_Handle(Cad2d_PointOnPlane)>(Points[Index]->Index(), Point));

		if (Insert.second EQUAL Standard_False)
		{
			THROW_STANDARD_EXCEPTION(" Duplicate Data");
			return NULL;
		}
	}
	Copy->SetName(theName_);
	return Copy;
}

void AutLib::CadLib::Cad2d_BlockPointOnPlane::ReleaseMemory()
{
	TColCad2d_IndexedMapOfPointOnPlane::iterator Iter = thePoints_.begin();
	while (Iter NOT_EQUAL thePoints_.end())
	{
		FreePointer(Iter->second);
		Iter++;
	}
}