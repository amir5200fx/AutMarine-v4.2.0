#include <Cad3d_BlockEntityOnSolid.hxx>

#include <Cad3d_EntityOnSolid.hxx>
#include <TColCad3d_StringMapOfHBlockEntityOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Cad3d_BlockEntityOnSolid::Cad3d_BlockEntityOnSolid()
	: theName_("Block Entity")
{
}

AutLib::CadLib::Cad3d_BlockEntityOnSolid::Cad3d_BlockEntityOnSolid
(
	const TColCad3d_HAry1dOfEntityOnSolid & Points,
	const Standard_String Name
)
	: theName_(Name)
{
	Try_Exception_Handle_Exit(SetEntities(Points));
}

AutLib::CadLib::Cad3d_BlockEntityOnSolid::~Cad3d_BlockEntityOnSolid()
{
	ReleaseMemory();
}

TColCad3d_HAry1dOfEntityOnSolid AutLib::CadLib::Cad3d_BlockEntityOnSolid::Entities() const
{
	TColCad3d_HAry1dOfEntityOnSolid Points((Standard_Integer)theEntities_.size());
	Standard_Integer K = 0;

	TColCad3d_IndexedMapOfEntityOnSolid::const_iterator Iter = theEntities_.begin();
	while (Iter NOT_EQUAL theEntities_.end())
	{
		Points[K++] = Iter->second;
		Iter++;
	}

	MOVE(Points);
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::SelectEntity(const Standard_Integer Index) const
{
	TColCad3d_IndexedMapOfEntityOnSolid::const_iterator Iter = theEntities_.find(Index);
	if (Iter EQUAL theEntities_.end()) { THROW_STANDARD_EXCEPTION("The Entity is NOT in the List"); }

	theSelected_.EnQueue(Index);
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::RetrieveTo(TColCad3d_HBasicQueueOfEntityOnSolid & Points) const
{
	TColCad3d_IndexedMapOfEntityOnSolid::const_iterator Iter = theEntities_.begin();
	while (Iter NOT_EQUAL theEntities_.end())
	{
		Points.EnQueue(Iter->second);
		Iter++;
	}
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::Print(Standard_OStream & Ostream) const
{
	Ostream << " Nb. of Entity = " << Size() << endl;
	Ostream << " Entity List: " << endl;

	TColCad3d_IndexedMapOfEntityOnSolid::const_iterator Iter = theEntities_.begin();
	while (Iter NOT_EQUAL theEntities_.end())
	{
		Ostream << Iter->first << "  ";
		Iter++;
	}
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::Clear()
{
	theEntities_.clear();
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::SetName(const Standard_String Name)
{
	theName_ = Name;
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::SplitByPatch(Cad3d_BlockEntityOnSolid & Other)
{
	if (NOT theSelected_.Size())
		return;

	Standard_Integer Index;
	while (theSelected_.DeQueue(Index))
	{
		TColCad3d_IndexedMapOfEntityOnSolid::const_iterator Iter = theEntities_.find(Index);

		if (Iter EQUAL theEntities_.end()) { THROW_STANDARD_EXCEPTION("The Entity is not at list"); }

		Other.Add(Iter->second);
		theEntities_.erase(Iter);
	}
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::SetEntities(const TColCad3d_HAry1dOfEntityOnSolid & Points)
{
	forThose(Index, 0, MaxIndexOf(Points))
		Add(Points[Index]);
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::Add(Global_Handle(Cad3d_EntityOnSolid) Entity)
{
	std::pair<TColCad3d_IndexedMapOfEntityOnSolid::iterator, Standard_Boolean> Insert;
	Insert = theEntities_.insert(std::pair<Standard_Integer, Global_Handle(Cad3d_EntityOnSolid)>(Entity->Index(), Entity));

	if (Insert.second EQUAL Standard_False)
	{
		THROW_STANDARD_EXCEPTION(" Duplicate Data");
		return;
	}
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::Remove(Global_Handle(Cad3d_EntityOnSolid) Entity)
{
	TColCad3d_IndexedMapOfEntityOnSolid::iterator Iter = theEntities_.find(Entity->Index());

	if (Iter EQUAL theEntities_.end())
	{
		THROW_STANDARD_EXCEPTION(" Not found the Curve");
		return;
	}

	theEntities_.erase(Iter);
}

void AutLib::CadLib::Cad3d_BlockEntityOnSolid::ReleaseMemory()
{
	TColCad3d_IndexedMapOfEntityOnSolid::iterator Iter = theEntities_.begin();
	while (Iter NOT_EQUAL theEntities_.end())
	{
		FreePointer(Iter->second);
		Iter++;
	}
}