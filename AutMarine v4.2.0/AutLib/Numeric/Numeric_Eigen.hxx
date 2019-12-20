#pragma once
#ifndef _Numeric_Eigen_Header
#define _Numeric_Eigen_Header

#include <TColStd_Ary2dOfReal.hxx>
#include <TColStd_Ary1dOfReal.hxx>

namespace AutLib
{
	namespace NumLib
	{

		class Numeric_Eigen
		{

		public:

			static void CalcEigen(const TColStd_Ary2dOfReal& A, TColStd_Ary1dOfReal& eVals, TColStd_Ary2dOfReal& eVecs, const Standard_Real tol);

			static void CalcGenEigen(const TColStd_Ary2dOfReal& A, const TColStd_Ary2dOfReal& B, TColStd_Ary1dOfReal& eVals, TColStd_Ary2dOfReal& eVecs, const Standard_Real eps);

		private:

			static TColStd_Ary2dOfReal MatMul(const TColStd_Ary2dOfReal& A, const TColStd_Ary2dOfReal& B);

			static TColStd_Ary1dOfReal Diag(const TColStd_Ary2dOfReal& A);

			static TColStd_Ary2dOfReal Iden(const Standard_Integer n);

			static TColStd_Ary2dOfReal tril(const TColStd_Ary2dOfReal& A);

			static TColStd_Ary2dOfReal Transpose(const TColStd_Ary2dOfReal& A);

			static TColStd_Ary2dOfReal Invert_Low_Tri(const TColStd_Ary2dOfReal& l);

			static void Choleski(TColStd_Ary2dOfReal& A);

			static void maxElem(const TColStd_Ary2dOfReal& a, Standard_Real& amax, Standard_Integer& k, Standard_Integer& l);

			static void Rotate(Standard_Integer k, Standard_Integer l, TColStd_Ary2dOfReal& A, TColStd_Ary2dOfReal& P);

			static void sortEigen(TColStd_Ary1dOfReal& eVals, TColStd_Ary2dOfReal& eVecs);

			static void stdForm(const TColStd_Ary2dOfReal& A, const TColStd_Ary2dOfReal& B, TColStd_Ary2dOfReal& H, TColStd_Ary2dOfReal& T);

			template<typename T>
			static inline void swapRows(const Standard_Integer i, const Standard_Integer j, ADT_Ary2d<T>& a)
			{
				Standard_Integer n = a.Size(0);
				ADT_Ary1d<T> temp(n);

				for (Standard_Integer k = 0; k < n; k++)
					temp[k] = a[i][k];
				for (Standard_Integer k = 0; k < n; k++)
					a[i][k] = a[j][k];
				for (Standard_Integer k = 0; k < n; k++)
					a[j][k] = temp[k];
			}

			template<typename T>
			static inline void swapCols(const Standard_Integer i, const Standard_Integer j, ADT_Ary2d<T>& a)
			{
				Standard_Integer n = a.Size(0);
				ADT_Ary1d<T> temp(n);

				for (Standard_Integer k = 0; k < n; k++)
					temp[k] = a[k][i];
				for (Standard_Integer k = 0; k < n; k++)
					a[k][i] = a[k][j];
				for (Standard_Integer k = 0; k < n; k++)
					a[k][j] = temp[k];
			}
		};
	}
}

#include <Numeric_EigenI.hxx>

#endif // !_Numeric_Eigen_Header
