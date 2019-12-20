#pragma once
#ifndef _Mesh3d_ShapeDiscrete_Header
#define _Mesh3d_ShapeDiscrete_Header

#include <Entity_Triangulation3d.hxx>
#include <TColMesh3d_HAry1dOfFaceDiscrete.hxx>

class TopoDS_Shape;

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_ShapeDiscrete
		{

		private:

			const TopoDS_Shape& theShape_;

			Standard_Real theSize_;

			TColMesh3d_HAry1dOfFaceDiscrete theMesh_;

			M_GEO Entity_Triangulation3d theMergedMesh_;

			Standard_Boolean ApplySmoothing_;
			Standard_Boolean ApplyOptimization_;
			Standard_Boolean UseExactMetric_;
			Standard_Boolean IsDone_;

			Standard_String theShapeName_;

			Standard_Integer theVerbose_;

		public:

			Mesh3d_ShapeDiscrete(const Standard_Real theSize, const TopoDS_Shape& theShape);

			~Mesh3d_ShapeDiscrete();

			//! Throw an exception if ShapeMesher is not performed
			const M_GEO Entity_Triangulation3d& Mesh() const;

			Standard_Boolean IsDone() const;

			void SetSize(const Standard_Real theSize);

			void SetName(const Standard_String theShapeName);

			void ApplyMetricSmoothing(const Standard_Boolean ApplySmoothing);

			void SetToUseExactMetric();

			void Perform();

			//! Throw an exception if ShapeMesher is not performed
			void ExportMeshToPlt(fstream& File) const;

			void ExportMergedMeshToPlt(fstream& File) const;

		private:

			void Merging();

			void ReleaseMemory();
		};
	}
}

#include <Mesh3d_ShapeDiscreteI.hxx>

#endif // !_Mesh3d_Discrete_Header
