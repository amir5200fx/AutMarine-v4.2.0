#pragma once
#ifndef _Mesh2d_Domain_Header
#define _Mesh2d_Domain_Header

#include <Entity_StaticChain2d.hxx>
#include <TColMesh2d_HAry1dOfMeshCurve.hxx>
#include <TColCad2d_HAry1dOfEdgeOnPlane.hxx>
#include <Standard_Stream.hxx>

M_CAD_SPACE(Cad2d_Plane)

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_SizeMap;

		class Mesh2d_Domain
		{

		private:

			const Global_Handle(Mesh2d_SizeMap) theMap_;
			const Global_Handle(M_CAD Cad2d_Plane) thePlane_;

			TColMesh2d_HAry1dOfMeshCurve theMeshCurves_;

			Standard_Real theResolution_;
			Standard_Real theRadius_;
			Standard_Real theDegeneracy_;

			Standard_Boolean IsDone_;

			M_GEO Entity_StaticChain2d theChain_;

		public:

			Mesh2d_Domain();

			Mesh2d_Domain(const Mesh2d_SizeMap& SizeMap, const Global_Handle(M_CAD Cad2d_Plane) Plane, const Standard_Real Tolerance);

			~Mesh2d_Domain();

			Standard_Integer NbCurves() const;

			const Mesh2d_Curve& CurveMesh(const Standard_Integer Index) const;

			const M_GEO Entity_StaticChain2d & Merged() const;

			Standard_Boolean IsDone() const;

			void SetCCWorder();

			void SetTolerance(const Standard_Real Tolerance);

			void SetSizeMap(const Mesh2d_SizeMap& SizeMap);

			void SetPlane(const Global_Handle(M_CAD Cad2d_Plane) Plane);

			void Perform(Standard_Boolean doMerging = Standard_True);

			void ExportCurveMeshToPlt(fstream & File) const;

			void ExportMergedToPlt(fstream & File) const;

		private:

			void Merging();

			void RemoveDegeneracy() const;
		};
	}
}

#include <Mesh2d_DomainI.hxx>

#endif // !_Mesh2d_Domain_Header
