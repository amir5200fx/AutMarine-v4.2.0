#pragma once
#ifndef _Cad2d_BlockEdgeOnPlane_Header
#define _Cad2d_BlockEdgeOnPlane_Header

#include <TColCad2d_IndexedMapOfEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfCurveOnPlane.hxx>
#include <TColStd_BasicQueueOfInteger.hxx>
#include <Standard_String.hxx>
#include <Standard_OStream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_BlockEdgeOnPlane
		{

			friend class Cad2d_EdgesOnPlane;

		private:

			TColCad2d_IndexedMapOfEdgeOnPlane theCurves_;

			Standard_String theName_;

			mutable TColStd_BasicQueueOfInteger theSelected_;

		public:

			Cad2d_BlockEdgeOnPlane();

			Cad2d_BlockEdgeOnPlane(const TColCad2d_HAry1dOfEdgeOnPlane& Curves, const Standard_String Name = "Block Curve");

			~Cad2d_BlockEdgeOnPlane();

			TColCad2d_HAry1dOfEdgeOnPlane Curves() const;

			Standard_String Name() const;

			Standard_Integer Size() const;

			void SelectCurve(const Standard_Integer Index) const;

			void UnSelectAll() const;

			void RetrieveTo(TColCad2d_HAry1dOfEdgeOnPlane& Curves) const;

			void RetrieveTo(TColCad2d_HBasicQueueOfEdgeOnPlane& Curves) const;

			void RetrieveTo(TColCad2d_HAry1dOfCurveOnPlane& Curves) const;

			void RetrieveTo(TColCad2d_HBasicQueueOfCurveOnPlane& Curves) const;

			void Print(Standard_OStream& Ostream = cout) const;

			void Clear();

			Global_Handle(Cad2d_BlockEdgeOnPlane) Copy(const TColCad2d_IndexedMapOfEdgeOnPlane& theEdges) const;

		private:

			Standard_Boolean IsContains(Global_Handle(Cad2d_EdgeOnPlane) Curve) const;

			Standard_Boolean IsContains(const Standard_Integer theIndex) const;

			void SetName(const Standard_String Name);

			void SplitByPatch(Cad2d_BlockEdgeOnPlane& Other);

			//! Throw an exception if find duplicate data
			void SetCurves(const TColCad2d_HAry1dOfEdgeOnPlane& Curves);

			//! Throw an exception if find duplicate data
			void Add(Global_Handle(Cad2d_EdgeOnPlane) Curve);

			//! Throw an exception if not found the curve
			void Remove(Global_Handle(Cad2d_EdgeOnPlane) Curve);

			void Remove(const Standard_Integer theIndex);

			void ReleaseMemory();
		};
	}
}

#endif // !_Cad2d_BlockEdgeOnPlane_Header
