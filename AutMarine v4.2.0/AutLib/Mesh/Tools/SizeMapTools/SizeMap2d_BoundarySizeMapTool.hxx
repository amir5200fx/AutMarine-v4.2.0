#pragma once
#ifndef _SizeMap2d_BoundarySizeMapTool_Header
#define _SizeMap2d_BoundarySizeMapTool_Header

#include <Global_Memory.hxx>
#include <SizeMap2d_SizeMapTool.hxx>
#include <TColStd_BasicQueueOfString.hxx>
#include <TColStd_Ary1dOfString.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh_ReferenceValues;

		class SizeMap2d_BoundarySizeMapTool : public SizeMap2d_SizeMapTool
		{

		protected:

			TColStd_BasicQueueOfString thePointPatches_;
			TColStd_BasicQueueOfString theCurvePatches_;

		protected:

			SizeMap2d_BoundarySizeMapTool(const Global_Handle(Mesh_ReferenceValues) theReference, const Global_Handle(M_CAD Cad2d_Plane) thePlane);

		public:

			virtual ~SizeMap2d_BoundarySizeMapTool();			

			Standard_Integer NbPointPatches() const;

			Standard_Integer NbCurvePatches() const;

			Standard_Boolean RemovePointPatch(const Standard_String PatchName);

			Standard_Boolean RemoveCurvePatch(const Standard_String PatchName);

			void ImportPointPatch(const Standard_String PatchName);

			void ImportCurvePatch(const Standard_String PatchName);

			void RetrievePointPatchesTo(TColStd_Ary1dOfString& Patches) const;

			void RetrieveCurvePatchesTo(TColStd_Ary1dOfString& Patches) const;

			void RetrievePointsTo(TColCad2d_HAry1dOfPointOnPlane& Points) const;

			void RetrieveCurvesTo(TColCad2d_HAry1dOfEdgeOnPlane& Edges) const;

			void PrintPoints(Standard_OStream& Ostream = cout) const;

			void PrintEdges(Standard_OStream& Ostream = cout) const;

		protected:

			
		};
	}
}

#include <SizeMap2d_BoundarySizeMapToolI.hxx>

#endif // !_SizeMap2d_BoundarySizeMapTool_Header
