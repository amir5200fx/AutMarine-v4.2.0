#pragma once
#ifndef _Rudder_Header
#define _Rudder_Header

#include <Cad3d_MarineModel.hxx>
#include <Rudder_Parameters.hxx>
#include <Rudder_Section.hxx>

#include <TopoDS_Shape.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Rudder : public Cad3d_MarineModel
		{

		private:

			Rudder_Parameters theParameters_;

			Rudder_Section theSection_;

			TopoDS_Shape myShaft_;

			Standard_Boolean toMakeShaft_;

		public:

			Rudder();

			virtual ~Rudder();

			virtual Global_Handle(Cad3d_Solid) GetSolid() const { return 0; }

			virtual void Make();

			void SetToMakeShaft();

		private:

			void DefaultParameters();

			void CreateMyFaces();

			void CreateMyRudder();

			void MakeClosedRudder();

			void MakeShaft();

			void MakeSolid();
		};
	}
}

#endif // !_Rudder_Header
