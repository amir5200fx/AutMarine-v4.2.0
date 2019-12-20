#include <Cad2d_PointsOnPlane.hxx>

#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_BlockPointOnPlane.hxx>
#include <Geometry_Tools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Cad2d_PointsOnPlane::Cad2d_PointsOnPlane()
{
}

AutLib::CadLib::Cad2d_PointsOnPlane::Cad2d_PointsOnPlane
(
	const Global_Handle(Cad2d_BlockPointOnPlane) BlockPoint,
	const Standard_String Name
)
{
	ImportBlockPoint(BlockPoint, Name);
}

AutLib::CadLib::Cad2d_PointsOnPlane::~Cad2d_PointsOnPlane()
{
	ReleaseMemory();
}

//void AutLib::CadLib::Cad2d_PointsOnPlane::CreateSharpCornerBlock(const Standard_Real theAngle)
//{
//	Standard_Real Angle = Geometry_Tools::DegToRadian(theAngle);
//
//	TColCad2d_HAry1dOfPointOnPlane Points;
//	RetrieveTo(Points);
//
//	forThose
//	(
//		Index,
//		0,
//		MaxIndexOf(Points)
//	)
//	{
//		Debug_Null_Pointer(Points[Index]);
//
//		if (Points[Index]->IsSharp(Angle)) { QSharps.EnQueue(Points[Index]); }
//	}
//
//}

void AutLib::CadLib::Cad2d_PointsOnPlane::SetBlockPoint(const Global_Handle(Cad2d_BlockPointOnPlane) BlockPoint, const Standard_String Name)
{
	ImportBlockPoint(BlockPoint, Name);
}

Global_Handle(M_CAD Cad2d_BlockPointOnPlane) AutLib::CadLib::Cad2d_PointsOnPlane::SelectBlockPoint(const Standard_String BlockName) const
{
	TColCad2d_StringMapOfHBlockPointOnPlane::const_iterator Iter = theBlocks_.find(BlockName);
	if (Iter NOT_EQUAL theBlocks_.end())
	{
		theSelected_.EnQueue(BlockName);
		return Iter->second;
	}
	return 0;
}

void AutLib::CadLib::Cad2d_PointsOnPlane::SelectAll()
{
	TColCad2d_StringMapOfHBlockPointOnPlane::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		theSelected_.EnQueue(Iter->first);
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_PointsOnPlane::UnSelectAll()
{
	theSelected_.Clear();
}

void AutLib::CadLib::Cad2d_PointsOnPlane::RemoveEmptyBlocks()
{
	TColCad2d_StringMapOfHBlockPointOnPlane::iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		if (NOT Iter->second->Size())
		{
			theBlocks_.erase(Iter);

			RemoveEmptyBlocks();
			return;
		}
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_PointsOnPlane::Combine()
{
	if (theSelected_.Size() < 2)
		return;

	Standard_String BlockName;
	theSelected_.DeQueue(BlockName);

	TColCad2d_StringMapOfHBlockPointOnPlane::iterator Block = theBlocks_.find(BlockName);

	Debug_If_Condition(Block EQUAL theBlocks_.end());

	while (theSelected_.DeQueue(BlockName))
	{
		TColCad2d_StringMapOfHBlockPointOnPlane::iterator Iter = theBlocks_.find(BlockName);

		Debug_If_Condition(Iter EQUAL theBlocks_.end());

		TColCad2d_HAry1dOfPointOnPlane Points;
		Iter->second->RetrieveTo(Points);

		forThose(Index, 0, MaxIndexOf(Points))
			Try_Exception_Handle_Exit(Block->second->Add(Points[Index]));

		theBlocks_.erase(Iter);
	}
}

void AutLib::CadLib::Cad2d_PointsOnPlane::Combine(const Standard_String newBlockName)
{
	if (theSelected_.Size() < 2)
		return;

	Standard_String BlockName;
	theSelected_.DeQueue(BlockName);

	TColCad2d_StringMapOfHBlockPointOnPlane::iterator Block = theBlocks_.find(BlockName);

	Debug_If_Condition(Block EQUAL theBlocks_.end());

	while (theSelected_.DeQueue(BlockName))
	{
		TColCad2d_StringMapOfHBlockPointOnPlane::iterator Iter = theBlocks_.find(BlockName);

		Debug_If_Condition(Iter EQUAL theBlocks_.end());

		TColCad2d_HAry1dOfPointOnPlane Points;
		Iter->second->RetrieveTo(Points);

		forThose(Index, 0, MaxIndexOf(Points))
			Try_Exception_Handle_Exit(Block->second->Add(Points[Index]));

		theBlocks_.erase(Iter);
	}

	RenameBlock(newBlockName);
}

void AutLib::CadLib::Cad2d_PointsOnPlane::CompactBlocks(const Standard_String BlockName)
{
	SelectAll();

	Combine(BlockName);
}

void AutLib::CadLib::Cad2d_PointsOnPlane::Split(const Standard_String BlockName)
{
	if (theSelected_.Size() NOT_EQUAL 1)
	{
		UnSelectAll();
		return;
	}

	Standard_String String;
	theSelected_.DeQueue(String);

	Global_Handle(Cad2d_BlockPointOnPlane) Block = GetBlockPoint(String);

	if (Block)
	{
		Global_Handle(Cad2d_BlockPointOnPlane) newBlock = new Cad2d_BlockPointOnPlane;

		Debug_Null_Pointer(newBlock);

		Block->Split(*newBlock);
		newBlock->SetName(BlockName);

		ImportBlockPoint(newBlock, newBlock->Name());
	}
}

void AutLib::CadLib::Cad2d_PointsOnPlane::RenameBlock(const Standard_String BlockName)
{
	if (theSelected_.Size() NOT_EQUAL 1)
	{
		UnSelectAll();
		return;
	}

	Standard_String String;
	theSelected_.DeQueue(String);

	Global_Handle(Cad2d_BlockPointOnPlane) Block = GetBlockPoint(String);

	if (Block)
	{
		theBlocks_.erase(String);

		Block->SetName(BlockName);

		ImportBlockPoint(Block, Block->Name());
	}
}

void AutLib::CadLib::Cad2d_PointsOnPlane::RetrieveTo(TColCad2d_HAry1dOfPointOnPlane & Curves) const
{
	TColCad2d_HBasicQueueOfPointOnPlane QPoints;

	TColCad2d_StringMapOfHBlockPointOnPlane::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		Iter->second->RetrieveTo(QPoints);
		Iter++;
	}

	QPoints.RetrieveTo(Curves);
}

void AutLib::CadLib::Cad2d_PointsOnPlane::RetrieveTo(TColCad2d_HAry1dOfBlockPointOnPlane & Blocks) const
{
	Blocks.Resize((Standard_Integer)theBlocks_.size());
	Standard_Integer K = 0;

	TColCad2d_StringMapOfHBlockPointOnPlane::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		Blocks[K++] = Iter->second;
		Iter++;
	}
}

void AutLib::CadLib::Cad2d_PointsOnPlane::Print
(
	const Standard_Boolean Sense,
	Standard_OStream & Ostream
) const
{
	Ostream << "-----------------{ Corner Blocks Informations }-----------------\n";
	Ostream << " Nb. of Blocks: " << theBlocks_.size() << endl;
	Ostream << " Block List: " << endl;

	TColCad2d_StringMapOfHBlockPointOnPlane::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		Ostream << endl;
		Ostream << "  - " << Iter->first;
		if (Sense)
		{
			Iter->second->Print(Ostream);
		}
		Iter++;
	}
	Ostream << endl;
	Ostream << "-----------------{ End of Corner Blocks Informations }-----------------\n";
}

Standard_Integer AutLib::CadLib::Cad2d_PointsOnPlane::Size() const
{
	Standard_Integer K = 0;

	TColCad2d_StringMapOfHBlockPointOnPlane::const_iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		K += Iter->second->Size();
		Iter++;
	}
	return K;
}

Standard_Integer AutLib::CadLib::Cad2d_PointsOnPlane::NbBlocks() const
{
	return (Standard_Integer)theBlocks_.size();
}

Standard_Boolean AutLib::CadLib::Cad2d_PointsOnPlane::GetBlockPoint(const Standard_String BlockName, Global_Handle(Cad2d_BlockPointOnPlane)& Curve) const
{
	TColCad2d_StringMapOfHBlockPointOnPlane::const_iterator Iter = theBlocks_.find(BlockName);

	if (Iter EQUAL theBlocks_.end())
		return Standard_False;

	Curve = Iter->second;
	return Standard_True;
}

Global_Handle(M_CAD Cad2d_BlockPointOnPlane) AutLib::CadLib::Cad2d_PointsOnPlane::GetBlockPoint(const Standard_String BlockName) const
{
	TColCad2d_StringMapOfHBlockPointOnPlane::const_iterator Iter = theBlocks_.find(BlockName);

	if (Iter EQUAL theBlocks_.end())
		return 0;

	return Iter->second;
}

Global_Handle(Cad2d_PointsOnPlane) AutLib::CadLib::Cad2d_PointsOnPlane::Copy(const TColCad2d_IndexedMapOfPointOnPlane& theBlock) const
{
	Global_Handle(Cad2d_PointsOnPlane) Copy = new Cad2d_PointsOnPlane;
	TColCad2d_HAry1dOfBlockPointOnPlane Blocks;
	RetrieveTo(Blocks);

	TColCad2d_HAry1dOfBlockPointOnPlane CopyBlocks(Blocks.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(CopyBlocks)
	)
	{
		Debug_Null_Pointer(Blocks[Index]);
		CopyBlocks[Index] = Blocks[Index]->Copy(theBlock);
		Copy->ImportBlockPoint(CopyBlocks[Index], CopyBlocks[Index]->Name());
	}
	return Copy;
}

Standard_Boolean AutLib::CadLib::Cad2d_PointsOnPlane::Remove(const Standard_Integer theIndex)
{
	TColCad2d_HAry1dOfBlockPointOnPlane Blocks;
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

void AutLib::CadLib::Cad2d_PointsOnPlane::ImportBlockPoint(const Global_Handle(Cad2d_BlockPointOnPlane) Points, const Standard_String Name)
{
	std::pair<TColCad2d_StringMapOfHBlockPointOnPlane::iterator, Standard_Boolean> Insert;
	Insert = theBlocks_.insert(std::pair<Standard_String, Global_Handle(Cad2d_BlockPointOnPlane)>(Name, (Global_Handle(Cad2d_BlockPointOnPlane))Points));

	if (Insert.second EQUAL Standard_False)
	{
		ImportBlockPoint(Points, Name + "(1)");
		return;
	}
}

void AutLib::CadLib::Cad2d_PointsOnPlane::ReleaseMemory()
{
	TColCad2d_StringMapOfHBlockPointOnPlane::iterator Iter = theBlocks_.begin();
	while (Iter NOT_EQUAL theBlocks_.end())
	{
		FreePointer(Iter->second);
		Iter++;
	}
}