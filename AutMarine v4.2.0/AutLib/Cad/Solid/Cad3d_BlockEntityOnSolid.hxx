#pragma once
#ifndef _Cad3d_BlockEntityOnSolid_Header
#define _Cad3d_BlockEntityOnSolid_Header

#include <Standard_String.hxx>
#include <TColStd_BasicQueueOfInteger.hxx>
#include <TColCad3d_HAry1dOfEntityOnSolid.hxx>
#include <TColCad3d_HAry1dOfBlockEntityOnSolid.hxx>
#include <TColCad3d_HBasicQueueOfEntityOnSolid.hxx>
#include <TColCad3d_IndexedMapOfEntityOnSolid.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_BlockEntityOnSolid
		{

			friend class Cad3d_EntitiesOnSolid;

		private:

			TColCad3d_IndexedMapOfEntityOnSolid theEntities_;

			Standard_String theName_;

			mutable TColStd_BasicQueueOfInteger theSelected_;

		public:

			Cad3d_BlockEntityOnSolid();

			Cad3d_BlockEntityOnSolid(const TColCad3d_HAry1dOfEntityOnSolid& theEntities, const Standard_String Name);

			~Cad3d_BlockEntityOnSolid();

			TColCad3d_HAry1dOfEntityOnSolid Entities() const;

			Standard_String Name() const;

			Standard_Integer Size() const;

			//! Throw an exception if not found the edge
			void SelectEntity(const Standard_Integer Index) const;

			void UnSelectAll() const;

			void RetrieveTo(TColCad3d_HAry1dOfEntityOnSolid& theEntities) const;

			void RetrieveTo(TColCad3d_HBasicQueueOfEntityOnSolid& theEntities) const;

			void Print(Standard_OStream& Ostream = cout) const;

			void Clear();

		private:

			void SetName(const Standard_String Name);

			void SplitByPatch(Cad3d_BlockEntityOnSolid& Other);

			//! Throw an exception if find duplicate data
			void SetEntities(const TColCad3d_HAry1dOfEntityOnSolid& Points);

			//! Throw an exception if find duplicate data
			void Add(Global_Handle(Cad3d_EntityOnSolid) Entity);

			//! Throw an exception if not found the curve
			void Remove(Global_Handle(Cad3d_EntityOnSolid) Entity);

			void ReleaseMemory();
		};
	}
}

#include <Cad3d_BlockEntityOnSolidI.hxx>

#endif // !_Cad3d_BlockEntityOnSolid_Header
