#include <Cad2d_EdgesOnPlane.hxx>

#include <Cad2d_BlockEdgeOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Cad2d_EdgesOnPlane::Cad2d_EdgesOnPlane()
{
}

AutLib::CadLib::Cad2d_EdgesOnPlane::~Cad2d_EdgesOnPlane()
{
	ReleaseMemory();
}

AutLib::CadLib::Cad2d_EdgesOnPlane::Cad2d_EdgesOnPlane
(
	const Global_Handle(Cad2d_BlockEdgeOnPlane) Curves,
	const Standard_String Name
)
{
	ImportBlockCurve(Curves, Name);
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::SetBlockCurve
(
	const Global_Handle(Cad2d_BlockEdgeOnPlane) Curves,
	const Standard_String Name
)
{
	ImportBlockCurve(Curves, Name);
}

Global_Handle(M_CAD Cad2d_BlockEdgeOnPlane) AutLib::CadLib::Cad2d_EdgesOnPlane::SelectBlockCurve(const Standard_String BlockName) const
{
	TColCad2d_StringMapOfHBlockEdgeOnPlane::const_iterator Iter = theBlocks_.find(BlockName);
	if (Iter NOT_EQUAL theBlocks_.end())
	{
		theSelected_.EnQueue(BlockName);
		return Iter->second;
	}
	return 0;
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::SelectAll()
{
	TColCad2d_StringMapOfHBlockEdgeOnPlane::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		theSelected_.EnQueue(Iter->first);
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::UnSelectAll()
{
	Standard_String String;
	while (theSelected_.DeQueue(String))
	{
		Global_Handle(Cad2d_BlockEdgeOnPlane) Block = GetBlockCurve(String);

		if (Block) Block->UnSelectAll();
	}
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::Combine()
{
	if (theSelected_.Size() < 2)
		return;

	Standard_String BlockName;
	theSelected_.DeQueue(BlockName);

	TColCad2d_StringMapOfHBlockEdgeOnPlane::iterator Block = theBlocks_.find(BlockName);

	Debug_If_Condition(Block EQUAL theBlocks_.end());

	while (theSelected_.DeQueue(BlockName))
	{
		TColCad2d_StringMapOfHBlockEdgeOnPlane::iterator Iter = theBlocks_.find(BlockName);

		Debug_If_Condition(Iter EQUAL theBlocks_.end());

		TColCad2d_HAry1dOfEdgeOnPlane Curves;
		Iter->second->RetrieveTo(Curves);

		forThose(Index, 0, MaxIndexOf(Curves))
			Try_Exception_Handle_Exit(Block->second->Add(Curves[Index]));

		theBlocks_.erase(Iter);
	}
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::Combine(const Standard_String newBlockName)
{
	Cad2d_EdgesOnPlane::Combine();

	RenameBlock(newBlockName);
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::CompactBlocks(const Standard_String BlockName)
{
	SelectAll();

	Combine(BlockName);
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::Split(const Standard_String BlockName)
{
	if (theSelected_.Size() NOT_EQUAL 1)
	{
		UnSelectAll();
		return;
	}

	Standard_String String;
	theSelected_.DeQueue(String);

	Global_Handle(Cad2d_BlockEdgeOnPlane) Block = GetBlockCurve(String);

	if (Block)
	{
		Global_Handle(Cad2d_BlockEdgeOnPlane) newBlock = new Cad2d_BlockEdgeOnPlane;

		Debug_Null_Pointer(newBlock);

		Block->SplitByPatch(*newBlock);
		newBlock->SetName(BlockName);

		ImportBlockCurve(newBlock, newBlock->Name());
	}
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::RenameBlock(const Standard_String BlockName)
{
	if (theSelected_.Size() NOT_EQUAL 1)
	{
		UnSelectAll();
		return;
	}

	Standard_String String;
	theSelected_.DeQueue(String);

	Global_Handle(Cad2d_BlockEdgeOnPlane) Block = GetBlockCurve(String);

	if (Block)
	{
		theBlocks_.erase(String);

		Block->SetName(BlockName);

		ImportBlockCurve(Block, Block->Name());
	}
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::RetrieveTo(TColCad2d_HAry1dOfEdgeOnPlane & Curves) const
{
	TColCad2d_HBasicQueueOfEdgeOnPlane QCurves;
	TColCad2d_StringMapOfHBlockEdgeOnPlane::const_iterator Iter = theBlocks_.begin();

	while (Iter NOT_EQUAL theBlocks_.end())
	{
		Iter->second->RetrieveTo(QCurves);
		Iter++;
	}
	QCurves.RetrieveTo(Curves);
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::RetrieveTo(TColCad2d_HAry1dOfBlockEdgeOnPlane & Blocks) const
{
	Blocks.Resize((Standard_Integer)theBlocks_.size());
	Standard_Integer K = 0;

	TColCad2d_StringMapOfHBlockEdgeOnPlane::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		Blocks[K++] = Iter->second;
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::Print
(
	const Standard_Boolean PrintCurves,
	Standard_OStream& Ostream
) const
{
	Ostream << "-----------------{ Curves Blocks Informations }-----------------\n";
	Ostream << " Nb. of Blocks: " << theBlocks_.size() << endl;
	Ostream << " Block List: " << endl;

	TColCad2d_StringMapOfHBlockEdgeOnPlane::const_iterator Iter = theBlocks_.begin();
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
	Ostream << "-----------------{ End of Curves Blocks Informations }-----------------\n";
}

Standard_Integer AutLib::CadLib::Cad2d_EdgesOnPlane::Size() const
{
	Standard_Integer K = 0;

	TColCad2d_StringMapOfHBlockEdgeOnPlane::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		K += Iter->second->Size();
		Iter++;
	}
	return K;
}

Standard_Integer AutLib::CadLib::Cad2d_EdgesOnPlane::NbBlocks() const
{
	return (Standard_Integer)theBlocks_.size();
}

Standard_Boolean AutLib::CadLib::Cad2d_EdgesOnPlane::GetBlockCurve(const Standard_String BlockName, Global_Handle(Cad2d_BlockEdgeOnPlane)& Curve) const
{
	TColCad2d_StringMapOfHBlockEdgeOnPlane::const_iterator Iter = theBlocks_.find(BlockName);

	if (Iter EQUAL theBlocks_.end())
		return Standard_False;

	Curve = Iter->second;
	return Standard_True;
}

Global_Handle(M_CAD Cad2d_BlockEdgeOnPlane) AutLib::CadLib::Cad2d_EdgesOnPlane::GetBlockCurve(const Standard_String BlockName) const
{
	TColCad2d_StringMapOfHBlockEdgeOnPlane::const_iterator Iter = theBlocks_.find(BlockName);

	if (Iter EQUAL theBlocks_.end())
		return 0;

	return Iter->second;
}

Global_Handle(Cad2d_EdgesOnPlane) AutLib::CadLib::Cad2d_EdgesOnPlane::Copy(const TColCad2d_IndexedMapOfEdgeOnPlane& theEdges) const
{
	Global_Handle(Cad2d_EdgesOnPlane) Copy = new Cad2d_EdgesOnPlane;
	TColCad2d_HAry1dOfBlockEdgeOnPlane Blocks;
	RetrieveTo(Blocks);

	TColCad2d_HAry1dOfBlockEdgeOnPlane CopyBlocks(Blocks.Size());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(CopyBlocks)
	)
	{
		Debug_Null_Pointer(Blocks[Index]);
		CopyBlocks[Index] = Blocks[Index]->Copy(theEdges);
		Copy->ImportBlockCurve(CopyBlocks[Index], CopyBlocks[Index]->Name());
	}
	return Copy;
}

Standard_Boolean AutLib::CadLib::Cad2d_EdgesOnPlane::Remove(Global_Handle(Cad2d_EdgeOnPlane) Edge)
{
	TColCad2d_HAry1dOfBlockEdgeOnPlane Blocks;
	RetrieveTo(Blocks);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Blocks)
	)
	{
		Debug_Null_Pointer(Blocks[Index]);

		if (Blocks[Index]->IsContains(Edge))
		{
			Blocks[Index]->Remove(Edge);
			return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Boolean AutLib::CadLib::Cad2d_EdgesOnPlane::Remove(const Standard_Integer theIndex)
{
	TColCad2d_HAry1dOfBlockEdgeOnPlane Blocks;
	RetrieveTo(Blocks);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Blocks)
	)
	{
		Debug_Null_Pointer(Blocks[Index]);

		if (Blocks[Index]->IsContains(theIndex))
		{
			Blocks[Index]->Remove(theIndex);
			return Standard_True;
		}
	}
	return Standard_False;
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::ImportBlockCurve
(
	const Global_Handle(Cad2d_BlockEdgeOnPlane) Curves,
	const Standard_String Name
)
{
	std::pair<TColCad2d_StringMapOfHBlockEdgeOnPlane::iterator, Standard_Boolean> Insert;
	Insert = theBlocks_.insert(std::pair<Standard_String, Global_Handle(Cad2d_BlockEdgeOnPlane)>(Name, (Global_Handle(Cad2d_BlockEdgeOnPlane))Curves));

	if (Insert.second EQUAL Standard_False)
	{
		ImportBlockCurve(Curves, Name + "(1)");
		return;
	}
}

void AutLib::CadLib::Cad2d_EdgesOnPlane::ReleaseMemory()
{
	TColCad2d_StringMapOfHBlockEdgeOnPlane::iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		FreePointer(Iter->second);
		Iter++;
	}
}