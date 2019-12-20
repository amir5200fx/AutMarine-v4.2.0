#pragma once
#ifndef _Cad3d_EntitiesOnSolid_Header
#define _Cad3d_EntitiesOnSolid_Header

#include <TColStd_BasicQueueOfString.hxx>
#include <TColCad3d_HAry1dOfEntityOnSolid.hxx>
#include <TColCad3d_HAry1dOfBlockEntityOnSolid.hxx>
#include <TColCad3d_StringMapOfHBlockEntityOnSolid.hxx>
#include <TColCad3d_IndexedMapOfEntityOnSolid.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_EntitiesOnSolid
		{

		private:

			TColCad3d_StringMapOfHBlockEntityOnSolid theBlocks_;

			mutable TColStd_BasicQueueOfString theStringSelected_;

		public:

			Cad3d_EntitiesOnSolid();

			Cad3d_EntitiesOnSolid(const Global_Handle(Cad3d_BlockEntityOnSolid) Entity, const Standard_String Name);

			Cad3d_EntitiesOnSolid(const TColCad3d_HAry1dOfBlockEntityOnSolid& theBlocks);

			~Cad3d_EntitiesOnSolid();

			void Init(const Global_Handle(Cad3d_BlockEntityOnSolid) Entity, const Standard_String Name);

			void Init(const TColCad3d_HAry1dOfBlockEntityOnSolid& theBlocks);

			void SelectAll();

			void UnSelectAll();

			void Combine();

			void Combine(const Standard_String BlockName);

			void CompactBlocks(const Standard_String BlockName);

			void Split(const Standard_String BlockName);

			void RenameBlock(const Standard_String BlockName);

			void RetrieveTo(TColCad3d_HAry1dOfEntityOnSolid& Entity) const;

			void RetrieveTo(TColCad3d_HAry1dOfBlockEntityOnSolid& Blocks) const;

			void Print(const Standard_Boolean PrintCurves = Standard_False, Standard_OStream& Ostream = cout) const;

			Standard_Integer Size() const;

			Standard_Integer NbBlocks() const;

			Standard_Boolean GetBlockEntity(const Standard_String BlockName, Global_Handle(Cad3d_BlockEntityOnSolid)& Block) const;

			Standard_Boolean HasBlock(const Standard_String BlockName) const;

			Global_Handle(Cad3d_BlockEntityOnSolid) SelectBlockEntity(const Standard_String BlockName) const;

			Global_Handle(Cad3d_BlockEntityOnSolid) GetBlockEntity(const Standard_String BlockName) const;

			Global_Handle(Cad3d_EntitiesOnSolid) Copy(const TColCad3d_IndexedMapOfEntityOnSolid& theEntities) const;

		private:

			void ImportBlockEntity(const Global_Handle(Cad3d_BlockEntityOnSolid) Entity, const Standard_String Name);

			void ReleaseMemory();
		};
	}
}

#include <Cad3d_EntitiesOnSolidI.hxx>

#endif // !_Cad3d_EntitiesOnSolid_Header
