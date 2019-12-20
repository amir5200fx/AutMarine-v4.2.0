#pragma once
#ifndef _Cad2d_PointsOnPlane_Header
#define _Cad2d_PointsOnPlane_Header

#include <TColCad2d_StringMapOfHBlockPointOnPlane.hxx>
#include <TColStd_BasicQueueOfString.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>
#include <TColCad2d_HAry1dOfBlockPointOnPlane.hxx>
#include <TColCad2d_IndexedMapOfPointOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_PointsOnPlane
		{

		private:

			TColCad2d_StringMapOfHBlockPointOnPlane theBlocks_;

			mutable TColStd_BasicQueueOfString theSelected_;

		public:

			Cad2d_PointsOnPlane();

			Cad2d_PointsOnPlane(const Global_Handle(Cad2d_BlockPointOnPlane) BlockPoint, const Standard_String Name = "Block Point");

			~Cad2d_PointsOnPlane();

			//void SelectSharpCorners(const Standard_Real theAngle);

			void SetBlockPoint(const Global_Handle(Cad2d_BlockPointOnPlane) BlockPoint, const Standard_String Name = "Block Point");

			Global_Handle(Cad2d_BlockPointOnPlane) SelectBlockPoint(const Standard_String BlockName) const;

			void SelectAll();

			void UnSelectAll();

			void RemoveEmptyBlocks();

			void Combine();

			void Combine(const Standard_String BlockName);

			void CompactBlocks(const Standard_String BlockName);

			void Split(const Standard_String BlockName = "Block Point");

			void RenameBlock(const Standard_String BlockName);

			void RetrieveTo(TColCad2d_HAry1dOfPointOnPlane& Points) const;

			void RetrieveTo(TColCad2d_HAry1dOfBlockPointOnPlane& Blocks) const;

			void Print(const Standard_Boolean Sense = Standard_False, Standard_OStream& Ostream = cout) const;

			Standard_Integer Size() const;

			Standard_Integer NbBlocks() const;

			Standard_Boolean GetBlockPoint(const Standard_String BlockName, Global_Handle(Cad2d_BlockPointOnPlane)& Curve) const;

			Global_Handle(Cad2d_BlockPointOnPlane) GetBlockPoint(const Standard_String BlockName) const;

			Global_Handle(Cad2d_PointsOnPlane) Copy(const TColCad2d_IndexedMapOfPointOnPlane& theBlock) const;

		private:

			Standard_Boolean Remove(const Standard_Integer theIndex);

			void ImportBlockPoint(const Global_Handle(Cad2d_BlockPointOnPlane) Points, const Standard_String Name);

			void ReleaseMemory();
		};
	}
}

#endif // !_Cad2d_PointsOnPlane_Header
