#pragma once
#ifndef _FvMemory_LaspackAllocate_Header
#define _FvMemory_LaspackAllocate_Header

#include <Global_Macros.hxx>
#include <FvMemory2d.hxx>
#include <FvVector_Laspack.hxx>
#include <FvMatrix_Laspack.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMemory_LaspackAllocate : public FvMemory2d
		{

		private:

			FvVector_Laspack thexU0_;
			FvVector_Laspack thexV0_;
			FvVector_Laspack thexP0_;

			FvVector_Laspack thexU_;
			FvVector_Laspack thexV_;
			FvVector_Laspack thexP_;

			FvVector_Laspack thexUf_;
			FvVector_Laspack thexVf_;
			FvVector_Laspack thexPf_;

			FvVector_Laspack theUf_;

			FvVector_Laspack theAp_;

			FvVector_Laspack thexpP_;

			FvVector_Laspack theHu_;
			FvVector_Laspack theHv_;

			FvVector_Laspack theBu_;
			FvVector_Laspack theBv_;

			FvMatrix_Laspack theAm_;
			FvMatrix_Laspack theAc_;

		public:

			FvMemory_LaspackAllocate();

			/*Velocity x-component at cell centre (previous time step)*/
			virtual FvVector& xU0();

			/*Velocity y-component at cell centre (previous time step)*/
			virtual FvVector& xV0();

			/*Pressure at cell centre (previous time step)*/
			virtual FvVector& xP0();

			/*Velocity x-component at cell centre*/
			virtual FvVector& xU();

			/*Velocity y-component at cell centre*/
			virtual FvVector& xV();

			/*Pressure at cell centre*/
			virtual FvVector& xP();

			/*Velocity x-component at face centre*/
			virtual FvVector& xUf();

			/*Velocity y-component at face centre*/
			virtual FvVector& xVf();

			/*Pressure at face centre*/
			virtual FvVector& xPf();

			/*Face flux velocity*/
			virtual FvVector& Uf();

			/*Momentum matrix diagonal*/
			virtual FvVector& Ap();

			virtual FvVector& xpP();

			/* Momentum matrix source x-component without pressure*/
			virtual FvVector& Hu();

			/* Momentum matrix source y-component without pressure*/
			virtual FvVector& Hv();

			/* Momentum matrix source x-component*/
			virtual FvVector& Bu();

			/* Momentum matrix source y-component*/
			virtual FvVector& Bv();

			virtual FvMatrix& Am();

			virtual FvMatrix& Ac();
		};
	}
}

#include <FvMemory_LaspackAllocateI.hxx>

#endif // !_FvMemory_LaspackAllocate_Header
