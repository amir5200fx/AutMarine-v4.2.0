#pragma once
#ifndef _Mesh2d_Cavity_Header
#define _Mesh2d_Cavity_Header

#include <TColMesh2d_HAvlTreeOfEdge.hxx>
#include <TColMesh2d_HAry1dOfEdge.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_Cavity
		{

		private:

			TColMesh2d_HAvlTreeOfEdge theUnCertainty_;

			TColMesh2d_HAvlTreeOfEdge theCertainty_;

		public:

			Mesh2d_Cavity();

			Standard_Boolean IsUnCertaintyEmpty() const;

			Standard_Boolean IsCertaintyEmpty() const;

			//! Throw an exception
			void InsertToUnCertainty(Global_Handle(Mesh2d_Edge) Edge);

			//! Throw an exception
			void InsertToCertainty(Global_Handle(Mesh2d_Edge) Edge);

			//! Throw an exception
			void RemoveFromUnCertainty(Global_Handle(Mesh2d_Edge) Edge);

			//! Throw an exception
			void RemoveFromCertainty(Global_Handle(Mesh2d_Edge) Edge);

			void RemoveFromUnCertaintyIgnoreWarning(Global_Handle(Mesh2d_Edge) Edge);

			void RemoveFromCertaintyIgnoreWarning(Global_Handle(Mesh2d_Edge) Edge);

			void RetrieveUnCertaintyTo(TColMesh2d_HAry1dOfEdge& Edges) const;

			void RetrieveCertaintyTo(TColMesh2d_HAry1dOfEdge& Edges) const;

			void ClearUnCertainty();

			void ClearCertainty();
		};
	}
}

#include <Mesh2d_CavityI.hxx>

#endif // !_Mesh2d_Cavity_Header
