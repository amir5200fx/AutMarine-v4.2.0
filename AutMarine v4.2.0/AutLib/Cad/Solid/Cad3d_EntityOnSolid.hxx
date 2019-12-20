#pragma once
#ifndef _Cad3d_EntityOnSolid_Header
#define _Cad3d_EntityOnSolid_Header

#include <Standard_TypeDef.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_EntityOnSolid
		{

		private:

			Standard_Integer theIndex_;

		public:

			virtual ~Cad3d_EntityOnSolid();

			void SetIndex(const Standard_Integer theIndex);

			Standard_Integer Index() const;

			virtual void ExportToPlt(fstream& File) const = 0;

		public:

			Cad3d_EntityOnSolid();

			Cad3d_EntityOnSolid(const Standard_Integer theIndex);
		};
	}
}

#include <Cad3d_EntityOnSolidI.hxx>

#endif // !_Cad3d_EntityOnSolid_Header
