#include <Cad3d_EntitiesOnSolid.hxx>

#include <Cad3d_BlockEntityOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Cad3d_EntitiesOnSolid::Cad3d_EntitiesOnSolid()
{
}

AutLib::CadLib::Cad3d_EntitiesOnSolid::Cad3d_EntitiesOnSolid
(
	const Global_Handle(Cad3d_BlockEntityOnSolid) Entity, 
	const Standard_String Name
)
{
	ImportBlockEntity(Entity, Name);
}

AutLib::CadLib::Cad3d_EntitiesOnSolid::Cad3d_EntitiesOnSolid(const TColCad3d_HAry1dOfBlockEntityOnSolid & theBlocks)
{
	Init(theBlocks);
}

AutLib::CadLib::Cad3d_EntitiesOnSolid::~Cad3d_EntitiesOnSolid()
{
	ReleaseMemory();
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::Init
(
	const Global_Handle(Cad3d_BlockEntityOnSolid) Entity,
	const Standard_String Name
)
{
	ImportBlockEntity(Entity, Name);
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::Init(const TColCad3d_HAry1dOfBlockEntityOnSolid & theBlocks)
{
	forThose(Index, 0, MaxIndexOf(theBlocks))
		ImportBlockEntity(theBlocks[Index], theBlocks[Index]->Name());
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::SelectAll()
{
	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		theStringSelected_.EnQueue(Iter->first);
		Iter++;
	}
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::UnSelectAll()
{
	Standard_String String;
	while (theStringSelected_.DeQueue(String))
	{
		Global_Handle(Cad3d_BlockEntityOnSolid) Block = GetBlockEntity(String);

		if (Block) Block->UnSelectAll();
	}
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::Combine()
{
	if (theStringSelected_.Size() < 2)
		return;

	Standard_String BlockName;
	theStringSelected_.DeQueue(BlockName);

	TColCad3d_StringMapOfHBlockEntityOnSolid::iterator Block = theBlocks_.find(BlockName);

	Debug_If_Condition(Block EQUAL theBlocks_.end());

	while (theStringSelected_.DeQueue(BlockName))
	{
		TColCad3d_StringMapOfHBlockEntityOnSolid::iterator Iter = theBlocks_.find(BlockName);

		Debug_If_Condition(Iter EQUAL theBlocks_.end());

		TColCad3d_HAry1dOfEntityOnSolid Entities;
		Iter->second->RetrieveTo(Entities);

		forThose(Index, 0, MaxIndexOf(Entities))
			Try_Exception_Handle_Exit(Block->second->Add(Entities[Index]));

		theBlocks_.erase(Iter);
	}
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::Combine(const Standard_String BlockName)
{
	Cad3d_EntitiesOnSolid::Combine();

	RenameBlock(BlockName);
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::CompactBlocks(const Standard_String BlockName)
{
	SelectAll();

	Combine(BlockName);
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::Split(const Standard_String BlockName)
{
	if (theStringSelected_.Size() NOT_EQUAL 1)
	{
		UnSelectAll();
		return;
	}

	Standard_String String;
	theStringSelected_.DeQueue(String);

	Global_Handle(Cad3d_BlockEntityOnSolid) Block = GetBlockEntity(String);

	if (Block)
	{
		Global_Handle(Cad3d_BlockEntityOnSolid) newBlock = new Cad3d_BlockEntityOnSolid;

		Debug_Null_Pointer(newBlock);

		Block->SplitByPatch(*newBlock);
		newBlock->SetName(BlockName);

		ImportBlockEntity(newBlock, newBlock->Name());
	}
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::RenameBlock(const Standard_String BlockName)
{
	if (theStringSelected_.Size() NOT_EQUAL 1)
	{
		UnSelectAll();
		return;
	}

	Standard_String String;
	theStringSelected_.DeQueue(String);

	Global_Handle(Cad3d_BlockEntityOnSolid) Block = GetBlockEntity(String);

	if (Block)
	{
		theBlocks_.erase(String);

		Block->SetName(BlockName);

		ImportBlockEntity(Block, Block->Name());
	}
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::RetrieveTo(TColCad3d_HAry1dOfEntityOnSolid & Entity) const
{
	TColCad3d_HBasicQueueOfEntityOnSolid QEdges;
	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.begin();

	while (Iter NOT_EQUAL theBlocks_.end())
	{
		Iter->second->RetrieveTo(QEdges);
		Iter++;
	}
	QEdges.RetrieveTo(Entity);
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::RetrieveTo(TColCad3d_HAry1dOfBlockEntityOnSolid & Blocks) const
{
	Blocks.Resize((Standard_Integer)theBlocks_.size());
	Standard_Integer K = 0;

	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		Blocks[K++] = Iter->second;
		Iter++;
	}
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::Print(const Standard_Boolean PrintCurves, Standard_OStream & Ostream) const
{
	Ostream << "-----------------{ Entities Blocks Informations }-----------------\n";
	Ostream << " Nb. of Blocks: " << theBlocks_.size() << endl;
	Ostream << " Block List: " << endl;

	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		Ostream << endl;
		Ostream << "  - " << Iter->first;
		if (PrintCurves)
		{
			Iter->second->Print(Ostream);
		}
		Iter++;
	}

	Ostream << endl;
	Ostream << "-----------------{ End of Entities Blocks Informations }-----------------\n";
}

Standard_Integer AutLib::CadLib::Cad3d_EntitiesOnSolid::Size() const
{
	Standard_Integer K = 0;

	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		K += Iter->second->Size();
		Iter++;
	}
	return K;
}

Standard_Boolean AutLib::CadLib::Cad3d_EntitiesOnSolid::GetBlockEntity(const Standard_String BlockName, Global_Handle(Cad3d_BlockEntityOnSolid)& Block) const
{
	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.find(BlockName);

	if (Iter EQUAL theBlocks_.end())
		return Standard_False;

	Block = Iter->second;
	return Standard_True;
}

Standard_Boolean AutLib::CadLib::Cad3d_EntitiesOnSolid::HasBlock(const Standard_String BlockName) const
{
	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.find(BlockName);

	if (Iter EQUAL theBlocks_.end())
		return Standard_False;

	return Standard_True;
}

Global_Handle(Cad3d_BlockEntityOnSolid) AutLib::CadLib::Cad3d_EntitiesOnSolid::SelectBlockEntity(const Standard_String BlockName) const
{
	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.find(BlockName);
	if (Iter NOT_EQUAL theBlocks_.end())
	{
		theStringSelected_.EnQueue(BlockName);
		return Iter->second;
	}
	return 0;
}

Global_Handle(Cad3d_BlockEntityOnSolid) AutLib::CadLib::Cad3d_EntitiesOnSolid::GetBlockEntity(const Standard_String BlockName) const
{
	TColCad3d_StringMapOfHBlockEntityOnSolid::const_iterator Iter = theBlocks_.find(BlockName);

	if (Iter EQUAL theBlocks_.end())
		return 0;

	return Iter->second;
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::ImportBlockEntity
(
	const Global_Handle(Cad3d_BlockEntityOnSolid) Entity,
	const Standard_String Name
)
{
	std::pair<TColCad3d_StringMapOfHBlockEntityOnSolid::iterator, Standard_Boolean> Insert;
	Insert = theBlocks_.insert(std::pair<Standard_String, Global_Handle(Cad3d_BlockEntityOnSolid)>(Name, (Global_Handle(Cad3d_BlockEntityOnSolid))Entity));

	if (Insert.second EQUAL Standard_False)
	{
		ImportBlockEntity(Entity, Name + "(1)");
		return;
	}
}

void AutLib::CadLib::Cad3d_EntitiesOnSolid::ReleaseMemory()
{
	TColCad3d_StringMapOfHBlockEntityOnSolid::iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		FreePointer(Iter->second);
		Iter++;
	}
}