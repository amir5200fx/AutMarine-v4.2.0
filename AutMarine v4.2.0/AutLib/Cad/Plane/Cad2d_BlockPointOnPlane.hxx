#pragma once
#ifndef _Cad2d_BlockPointOnPlane_Header
#define _Cad2d_BlockPointOnPlane_Header

#include <TColCad2d_IndexedMapOfPointOnPlane.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfPointOnPlane.hxx>
#include <TColStd_BasicQueueOfInteger.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>
#include <Standard_String.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_BlockPointOnPlane
		{

			friend class Cad2d_PointsOnPlane;

		private:

			TColCad2d_IndexedMapOfPointOnPlane thePoints_;

			Standard_String theName_;

			mutable TColStd_BasicQueueOfInteger theSelected_;

		public:

			Cad2d_BlockPointOnPlane();

			Cad2d_BlockPointOnPlane(const TColCad2d_HAry1dOfPointOnPlane& Points, const Standard_String Name = "Block Point");

			~Cad2d_BlockPointOnPlane();

			TColCad2d_HAry1dOfPointOnPlane Points() const;

			Standard_String Name() const;

			Standard_Integer Size() const;

			void SelectSharpCorners(const Standard_Real theAngle);

			void SelectPoint(const Standard_Integer Index) const;

			void UnSelectAll() const;

			void RetrieveTo(TColCad2d_HAry1dOfPointOnPlane& Points) const;

			void RetrieveTo(TColCad2d_HBasicQueueOfPointOnPlane& Points) const;

			void RetrieveTo(TColGeom_Ary1dOfPnt2d& Points) const;

			void RetrieveTo(TColGeom_BasicQueueOfPnt2d& Points) const;

			void Print(Standard_OStream& Ostream) const;

			void Clear();

			Global_Handle(Cad2d_BlockPointOnPlane) Copy(const TColCad2d_IndexedMapOfPointOnPlane& theBlock) const;

		private:

			Standard_Boolean IsContains(const Standard_Integer theIndex) const;

			void Split(Cad2d_BlockPointOnPlane& Other);

			void SetName(const Standard_String Name);

			//! Throw an exception if find duplicate data
			void SetPoints(const TColCad2d_HAry1dOfPointOnPlane& Points);

			//! Throw an exception if find duplicate data
			void Add(Global_Handle(Cad2d_PointOnPlane) Point);

			//! Throw an exception if not found the curve
			void Remove(Global_Handle(Cad2d_PointOnPlane) Point);

			void Remove(const Standard_Integer theIndex);

			void ReleaseMemory();
		};
	}
}

#endif // !_Cad2d_BlockPointOnPlane_Header
