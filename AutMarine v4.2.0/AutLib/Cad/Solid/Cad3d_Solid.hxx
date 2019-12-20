#pragma once
#ifndef _Cad3d_Solid_Header
#define _Cad3d_Solid_Header

#include <Entity_Box3d.hxx>
#include <Cad3d_EntitiesOnSolid.hxx>
#include <Cad3d_OutterBoundaryOnSolid.hxx>
#include <Cad3d_InnerBoundariesOnSolid.hxx>
#include <TColCad3d_HAry1dOfEntityOnSolid.hxx>
#include <TColCad3d_HAry1dOfPointOnSolid.hxx>
#include <TColCad3d_HAry1dOfPairedOnSolid.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box3d;
	}

	namespace CadLib
	{

		class Cad3d_Solid
		{

		protected:

			Standard_Integer theIndex_;

			Standard_String theName_;

			Global_Handle(Cad3d_EntitiesOnSolid) theVertices_;
			Global_Handle(Cad3d_EntitiesOnSolid) thePairedEdges_;
			Global_Handle(Cad3d_EntitiesOnSolid) theSurfaces_;

			Standard_Real theTolerance_;

			Cad3d_OutterBoundaryOnSolid theOutterShell_;

			Cad3d_InnerBoundariesOnSolid theInnerShells_;

			M_GEO Entity_Box3d theBoundingBox_;

		public:

			Cad3d_Solid();

			~Cad3d_Solid();

			//Throw an exception
			M_GEO Entity_Box3d BoundingBox(const Standard_Real Offset = 0.0) const;

			Global_Handle(Cad3d_EntitiesOnSolid) Vertices() const;

			Global_Handle(Cad3d_EntitiesOnSolid) PairedEdges() const;

			Global_Handle(Cad3d_EntitiesOnSolid) Surfaces() const;

			Standard_Integer NbVertices() const;

			Standard_Integer NbPairedEdges() const;

			Standard_Integer NbSurfaces() const;

			Standard_Integer NbHoles() const;

			Standard_Integer NbFreeEdges() const;

			Standard_Boolean HasFreeEdge() const;

			Standard_String Name() const;

			void Make(const TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces, const Standard_Real Tolerance = 1.0E-6);

			void SetName(const Standard_String Name);

			void RetrieveVerticesTo(TColCad3d_HAry1dOfEntityOnSolid& theVertices) const;

			void RetrieveVerticesTo(TColCad3d_HAry1dOfPointOnSolid& theVertices) const;

			void RetrievePairedEdgesTo(TColCad3d_HAry1dOfEntityOnSolid& theEdges) const;

			void RetrieveFreeEdgesTo(TColCad3d_HAry1dOfEntityOnSolid& theFreeEdges) const;

			void RetrieveFreeEdgesTo(TColCad3d_HAry1dOfPairedOnSolid& theFreeEdges) const;

			void RetrieveSurfacesTo(TColCad3d_HAry1dOfEntityOnSolid& theSurfaces) const;

			void RetrieveSurfacesTo(TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces) const;

			void SplitByShells();

			void Clear();

			void ExportToPlt(fstream& File) const;

			void ExportPointsToPlt(fstream& File) const;

			void ExportPlanesToPlt(fstream& File) const;

			void ExportParametricCurvesToPlt(fstream& File) const;

			void ExportParametricWiresToPlt(fstream& File) const;

			void ExportCurvesToPlt(fstream& File) const;

			void ExportFreeEdgesToPlt(fstream& File) const;

			void ExportSurfacesToPlt(fstream& File) const;

			void ExportNormalsToPlt(fstream& File, const Standard_Real theCoeff = 0.01) const;

			void ExportShellsToPlt(fstream& File) const;

			void ExportBlockSurfacesToPlt(fstream& File) const;

			void ExportTopologyToPlt(fstream& File) const;

			void Report(Standard_OStream& Ostream = cout) const;

			Global_Handle(Cad3d_Solid) Copy() const;

		protected:

			Standard_Boolean CreateShells(const TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces);
		};
	}
}

#include <Cad3d_SolidI.hxx>

#endif // !_Cad3d_Solid_Header
