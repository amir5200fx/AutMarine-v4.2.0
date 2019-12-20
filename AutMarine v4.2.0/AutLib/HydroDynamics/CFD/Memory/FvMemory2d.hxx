#pragma once
#ifndef _FvMemory2d_Header
#define _FvMemory2d_Header


namespace AutLib
{
	namespace FvLib
	{

		class FvVector;
		class FvMatrix;

		class FvMemory2d
		{

		private:


		public:

			/*Velocity x-component at cell centre (previous time step)*/
			virtual FvVector& xU0() = 0;

			/*Velocity y-component at cell centre (previous time step)*/
			virtual FvVector& xV0() = 0;

			/*Pressure at cell centre (previous time step)*/
			virtual FvVector& xP0() = 0;

			/*Velocity x-component at cell centre*/
			virtual FvVector& xU() = 0;

			/*Velocity y-component at cell centre*/
			virtual FvVector& xV() = 0;

			/*Pressure at cell centre*/
			virtual FvVector& xP() = 0;

			/*Velocity x-component at face centre*/
			virtual FvVector& xUf() = 0;

			/*Velocity y-component at face centre*/
			virtual FvVector& xVf() = 0;

			/*Pressure at face centre*/
			virtual FvVector& xPf() = 0;

			/*Face flux velocity*/
			virtual FvVector& Uf() = 0;

			/*Momentum matrix diagonal*/
			virtual FvVector& Ap() = 0;

			virtual FvVector& xpP() = 0;

			/* Momentum matrix source x-component without pressure*/
			virtual FvVector& Hu() = 0;

			/* Momentum matrix source y-component without pressure*/
			virtual FvVector& Hv() = 0;

			/* Momentum matrix source x-component*/
			virtual FvVector& Bu() = 0;

			/* Momentum matrix source y-component*/
			virtual FvVector& Bv() = 0;

			virtual FvMatrix& Am() = 0;

			virtual FvMatrix& Ac() = 0;
		};
	}
}

#endif // !_FvMemory2d_Header
