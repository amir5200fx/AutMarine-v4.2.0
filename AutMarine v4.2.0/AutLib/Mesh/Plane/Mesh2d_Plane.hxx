#pragma once
#ifndef _Mesh2d_Plane_Header
#define _Mesh2d_Plane_Header

#include <Mesh_LaplacianSmoothingInfo.hxx>
#include <TColMesh2d_HAry1dOfTMesh.hxx>
#include <TColMesh2d_HAry1dOfDomain.hxx>
#include <Standard_Stream.hxx>
#include <Mesh2d_TMesh.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_SizeMap;

		class Mesh2d_Plane
		{

		private:

			TColMesh2d_HAry1dOfTMesh theMeshes_;

			TColMesh2d_HAry1dOfDomain theDomains_;

			Standard_Integer theCurrent_;

			Standard_Boolean AutomaticReleaseMemory_;

			Mesh_LaplacianSmoothingInfo theSmoothing_;

		public:

			Mesh2d_Plane();

			virtual ~Mesh2d_Plane();

			Global_Handle(Mesh2d_TMesh) Mesh(const Standard_Integer Index) const;

			Global_Handle(Mesh2d_TMesh) CurrentMesh() const;

			Global_Handle(Mesh2d_TMesh)& CurrentMesh();

			Mesh_LaplacianSmoothingInfo& LaplacianSmoothing();

			const Mesh_LaplacianSmoothingInfo & LaplacianSmoothing() const;

			const Mesh2d_Domain& Domain(const Standard_Integer Index) const;

			Mesh2d_Domain& Domain(const Standard_Integer Index);

			Standard_Integer NbMeshes() const;

			Standard_Integer Current() const;

			Standard_Integer NbElements() const;

			Standard_Integer NbEdges() const;

			Standard_Integer NbNodes() const;

			void SetCurrent(const Standard_Integer Value);

			void ExportToPlt(fstream & File) const;

			void ExportQualityToPlt(fstream& File, const Mesh2d_SizeMap& theSizeMap) const;

			void ReportQualityTo(Standard_OStream& Ostream, const Mesh2d_SizeMap& theSizeMap) const;

			void ReleaseMemory();

			void SetManualReleaseMemory();

		protected:

			void LaplacianSmoothing(Standard_Real(*Distance)(const Geom_Pnt2d&, const Geom_Pnt2d&, const Mesh2d_SizeMap&), const Mesh2d_SizeMap&, const Standard_Boolean Verbose = Standard_False);

			void AllocateMemory(const Standard_Integer N);
		};
	}
}

#include <Mesh2d_PlaneI.hxx>

#endif // !_Mesh2d_Plane_Header
