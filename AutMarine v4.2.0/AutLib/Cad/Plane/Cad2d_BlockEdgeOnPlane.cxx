#include <Cad2d_BlockEdgeOnPlane.hxx>

#include <Cad2d_EdgeOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Cad2d_BlockEdgeOnPlane()
	: theName_("Block Curve")
{
}

AutLib::CadLib::Cad2d_BlockEdgeOnPlane::~Cad2d_BlockEdgeOnPlane()
{
	ReleaseMemory();
}

AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Cad2d_BlockEdgeOnPlane
(
	const TColCad2d_HAry1dOfEdgeOnPlane & Curves,
	const Standard_String Name
)
	: theName_(Name)
{
	Try_Exception_Handle_Exit(SetCurves(Curves));
}

M_AUT TColCad2d_HAry1dOfEdgeOnPlane AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Curves() const
{
	TColCad2d_HAry1dOfEdgeOnPlane Curves((Standard_Integer)theCurves_.size());
	Standard_Integer K = 0;

	TColCad2d_IndexedMapOfEdgeOnPlane::const_iterator Iter = theCurves_.begin();
	while (Iter NOT_EQUAL theCurves_.end())
	{
		Curves[K++] = Iter->second;
		Iter++;
	}

	MOVE(Curves);
}

Standard_String AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Name() const
{
	return theName_;
}

Standard_Integer AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Size() const
{
	return (Standard_Integer)theCurves_.size();
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::SelectCurve(const Standard_Integer Index) const
{
	TColCad2d_IndexedMapOfEdgeOnPlane::const_iterator Iter = theCurves_.find(Index);
	if (Iter EQUAL theCurves_.end())
	{
		cout << " The Curve is NOT in the List" << endl;
		return;
	}
	theSelected_.EnQueue(Index);
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::UnSelectAll() const
{
	theSelected_.Clear();
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::SplitByPatch(Cad2d_BlockEdgeOnPlane& Other)
{
	if (NOT theSelected_.Size())
		return;

	Standard_Integer Index;
	while (theSelected_.DeQueue(Index))
	{
		TColCad2d_IndexedMapOfEdgeOnPlane::const_iterator Iter = theCurves_.find(Index);

		Debug_If_Condition(Iter EQUAL theCurves_.end());

		Other.Add(Iter->second);
		theCurves_.erase(Iter);
	}
}

Standard_Boolean AutLib::CadLib::Cad2d_BlockEdgeOnPlane::IsContains(Global_Handle(Cad2d_EdgeOnPlane) Curve) const
{
	TColCad2d_IndexedMapOfEdgeOnPlane::const_iterator Iter = theCurves_.find(Curve->Index());

	if (Iter EQUAL theCurves_.end())
	{
		return Standard_False;
	}
	return Standard_True;
}

Standard_Boolean AutLib::CadLib::Cad2d_BlockEdgeOnPlane::IsContains(const Standard_Integer theIndex) const
{
	TColCad2d_IndexedMapOfEdgeOnPlane::const_iterator Iter = theCurves_.find(theIndex);

	if (Iter EQUAL theCurves_.end())
	{
		return Standard_False;
	}
	return Standard_True;
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::SetName(const Standard_String Name)
{
	theName_ = Name;
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::SetCurves(const TColCad2d_HAry1dOfEdgeOnPlane & Curves)
{
	forThose(Index, 0, MaxIndexOf(Curves))
		Add(Curves[Index]);
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::RetrieveTo(TColCad2d_HAry1dOfEdgeOnPlane & Curves) const
{
	TColCad2d_HBasicQueueOfEdgeOnPlane QCurves;
	RetrieveTo(QCurves);

	QCurves.RetrieveTo(Curves);
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::RetrieveTo(TColCad2d_HBasicQueueOfEdgeOnPlane & Curves) const
{
	TColCad2d_IndexedMapOfEdgeOnPlane::const_iterator Iter = theCurves_.begin();
	while (Iter NOT_EQUAL theCurves_.end())
	{
		Curves.EnQueue(Iter->second);
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::RetrieveTo(TColCad2d_HAry1dOfCurveOnPlane & Curves) const
{
	TColCad2d_HBasicQueueOfCurveOnPlane QCurves;
	RetrieveTo(QCurves);

	QCurves.RetrieveTo(Curves);
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::RetrieveTo(TColCad2d_HBasicQueueOfCurveOnPlane & Curves) const
{
	TColCad2d_IndexedMapOfEdgeOnPlane::const_iterator Iter = theCurves_.begin();
	while (Iter NOT_EQUAL theCurves_.end())
	{
		Curves.EnQueue((Global_Handle(Cad2d_CurveOnPlane))Iter->second->Curve());
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Add(Global_Handle(Cad2d_EdgeOnPlane) Curve)
{
	std::pair<TColCad2d_IndexedMapOfEdgeOnPlane::iterator, Standard_Boolean> Insert;
	Insert = theCurves_.insert(std::pair<Standard_Integer, Global_Handle(Cad2d_EdgeOnPlane)>(Curve->Index(), Curve));

	if (Insert.second EQUAL Standard_False)
	{
		THROW_STANDARD_EXCEPTION(" Duplicate Data");
		return;
	}
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Remove(Global_Handle(Cad2d_EdgeOnPlane) Curve)
{
	TColCad2d_IndexedMapOfEdgeOnPlane::iterator Iter = theCurves_.find(Curve->Index());

	if (Iter EQUAL theCurves_.end())
	{
		THROW_STANDARD_EXCEPTION(" Not found the Curve");
		return;
	}

	theCurves_.erase(Iter);
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Remove(const Standard_Integer theIndex)
{
	TColCad2d_IndexedMapOfEdgeOnPlane::iterator Iter = theCurves_.find(theIndex);

	if (Iter EQUAL theCurves_.end())
	{
		THROW_STANDARD_EXCEPTION(" Not found the Curve");
		return;
	}

	theCurves_.erase(Iter);
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::ReleaseMemory()
{
	TColCad2d_IndexedMapOfEdgeOnPlane::iterator Iter = theCurves_.begin();
	while (Iter NOT_EQUAL theCurves_.end())
	{
		FreePointer(Iter->second);
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Print(Standard_OStream & Ostream) const
{
	Ostream << " Nb. of Curves = " << Size() << endl;
	Ostream << " Curve List: " << endl;

	TColCad2d_IndexedMapOfEdgeOnPlane::const_iterator Iter = theCurves_.begin();
	while (Iter NOT_EQUAL theCurves_.end())
	{
		Ostream << Iter->first << "  ";
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Clear()
{
	theCurves_.clear();
}

Global_Handle(Cad2d_BlockEdgeOnPlane) AutLib::CadLib::Cad2d_BlockEdgeOnPlane::Copy(const TColCad2d_IndexedMapOfEdgeOnPlane& theBlock) const
{
	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	RetrieveTo(Edges);

	Global_Handle(Cad2d_BlockEdgeOnPlane) Copy = new Cad2d_BlockEdgeOnPlane;
	Get_Object(Curves) = Copy->theCurves_;

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Global_Handle(Cad2d_EdgeOnPlane) Edge = theBlock.at(Edges[Index]->Index());

		Debug_Null_Pointer(Edge);

		std::pair<TColCad2d_IndexedMapOfEdgeOnPlane::iterator, Standard_Boolean> Insert;
		Insert = Curves.insert(std::pair<Standard_Integer, Global_Handle(Cad2d_EdgeOnPlane)>(Edges[Index]->Index(), Edge));

		if (Insert.second EQUAL Standard_False)
		{
			THROW_STANDARD_EXCEPTION(" Duplicate Data");
			return NULL;
		}
	}
	Copy->SetName(theName_);
	return Copy;
}