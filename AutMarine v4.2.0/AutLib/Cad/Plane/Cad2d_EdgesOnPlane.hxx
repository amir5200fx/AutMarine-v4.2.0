#pragma once
#ifndef _Cad2d_EdgesOnPlane_Header
#define _Cad2d_EdgesOnPlane_Header

#include <TColCad2d_StringMapOfHBlockEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColStd_BasicQueueOfString.hxx>
#include <TColCad2d_HAry1dOfBlockEdgeOnPlane.hxx>
#include <TColCad2d_IndexedMapOfEdgeOnPlane.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_EdgesOnPlane
		{

			friend class Cad2d_Plane;

		private:

			TColCad2d_StringMapOfHBlockEdgeOnPlane theBlocks_;

			mutable TColStd_BasicQueueOfString theSelected_;

		public:

			Cad2d_EdgesOnPlane();

			~Cad2d_EdgesOnPlane();

			Cad2d_EdgesOnPlane(const Global_Handle(Cad2d_BlockEdgeOnPlane) Curves, const Standard_String Name = "Block Curve");

			void SetBlockCurve(const Global_Handle(Cad2d_BlockEdgeOnPlane) Curves, const Standard_String Name = "Block Curve");

			Global_Handle(Cad2d_BlockEdgeOnPlane) SelectBlockCurve(const Standard_String BlockName) const;

			void SelectAll();

			void UnSelectAll();

			void Combine();

			void Combine(const Standard_String BlockName);

			void CompactBlocks(const Standard_String BlockName);

			void Split(const Standard_String BlockName = "Block Curve");

			void RenameBlock(const Standard_String BlockName);

			void RetrieveTo(TColCad2d_HAry1dOfEdgeOnPlane& Curves) const;

			void RetrieveTo(TColCad2d_HAry1dOfBlockEdgeOnPlane& Blocks) const;

			void Print(const Standard_Boolean PrintCurves = Standard_False, Standard_OStream& Ostream = cout) const;

			Standard_Integer Size() const;

			Standard_Integer NbBlocks() const;

			Standard_Boolean GetBlockCurve(const Standard_String BlockName, Global_Handle(Cad2d_BlockEdgeOnPlane)& Curve) const;

			Global_Handle(Cad2d_BlockEdgeOnPlane) GetBlockCurve(const Standard_String BlockName) const;

			Global_Handle(Cad2d_EdgesOnPlane) Copy(const TColCad2d_IndexedMapOfEdgeOnPlane& theEdges) const;

		private:

			Standard_Boolean Remove(Global_Handle(Cad2d_EdgeOnPlane) Edge);

			Standard_Boolean Remove(const Standard_Integer theIndex);

			void ReplaceEdgesWith(const TColCad2d_HAry1dOfEdgeOnPlane& Edges);

			void ImportBlockCurve(const Global_Handle(Cad2d_BlockEdgeOnPlane) Curves, const Standard_String Name);

			void ReleaseMemory();
		};
	}
}

#endif // !_Cad2d_EdgesOnPlane_Header
