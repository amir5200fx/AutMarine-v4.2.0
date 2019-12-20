#pragma once
#ifndef _Mesh3d_Cavity_Header
#define _Mesh3d_Cavity_Header

#include <TColMesh3d_HAvlTreeOfFacet.hxx>
#include <TColMesh3d_HAry1dOfFacet.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_Cavity
		{

		private:

			TColMesh3d_HAvlTreeOfFacet theUnCertainty_;

			TColMesh3d_HAvlTreeOfFacet theCertainty_;

		public:

			Mesh3d_Cavity();

			Standard_Boolean IsUnCertaintyEmpty() const;

			Standard_Boolean IsCertaintyEmpty() const;

			//! Throw an exception
			void InsertToUnCertainty(Global_Handle(Mesh3d_Facet) Facet);

			//! Throw an exception
			void InsertToCertainty(Global_Handle(Mesh3d_Facet) Facet);

			//! Throw an exception
			void RemoveFromUnCertainty(Global_Handle(Mesh3d_Facet) Facet);

			//! Throw an exception
			void RemoveFromCertainty(Global_Handle(Mesh3d_Facet) Facet);

			void RemoveFromUnCertaintyIgnoreWarning(Global_Handle(Mesh3d_Facet) Facet);

			void RemoveFromCertaintyIgnoreWarning(Global_Handle(Mesh3d_Facet) Facet);

			void RetrieveUnCertaintyTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void RetrieveCertaintyTo(TColMesh3d_HAry1dOfFacet& Facets) const;

			void ClearUnCertainty();

			void ClearCertainty();
		};
	}
}

#include <Mesh3d_CavityI.hxx>

#endif // !_Mesh3d_Cavity_Header
