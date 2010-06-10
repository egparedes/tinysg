/*************************************************************************
* TinySG, Copyright (C) 2007, 2008  J.D. Yamokoski
* All rights reserved.
* Email: yamokosk at gmail dot com
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation; either version 2.1 of the License,
* or (at your option) any later version. The text of the GNU Lesser General
* Public License is included with this library in the file LICENSE.TXT.
*
* This library is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the file LICENSE.TXT for
* more details.
*
*************************************************************************/

/*
 * Code taken from the OGRE (Object-oriented Graphics Rendering Engine) Project
 * http://www.ogre3d.org/
 */

#ifndef __Matrix3_H__
#define __Matrix3_H__

#include "MathPrerequisites.h"

#include "Vector3.h"

#include <string>
#include <sstream>

// NB All code adapted from Wild Magic 0.2 Matrix math (free source code)
// http://www.geometrictools.com/

// NOTE.  The (x,y,z) coordinate system is assumed to be right-handed.
// Coordinate axis rotation matrices are of the form
//   RX =    1       0       0
//           0     cos(t) -sin(t)
//           0     sin(t)  cos(t)
// where t > 0 indicates a counterclockwise rotation in the yz-plane
//   RY =  cos(t)    0     sin(t)
//           0       1       0
//        -sin(t)    0     cos(t)
// where t > 0 indicates a counterclockwise rotation in the zx-plane
//   RZ =  cos(t) -sin(t)    0
//         sin(t)  cos(t)    0
//           0       0       1
// where t > 0 indicates a counterclockwise rotation in the xy-plane.

/** A 3x3 matrix which can represent rotations around axes.
	@note
		<b>All the code is adapted from the Wild Magic 0.2 Matrix
		library (http://www.geometrictools.com/).</b>
	@par
		The coordinate system is assumed to be <b>right-handed</b>.
*/
class SOEXPORT Matrix3
{
public:
	/** Default constructor.
		@note
			It does <b>NOT</b> initialize the matrix for efficiency.
	*/
	inline Matrix3 () {};
	inline explicit Matrix3 (const Real arr[3][3])
	{
		memcpy(m,arr,9*sizeof(Real));
	}
	inline Matrix3 (const Matrix3& rkMatrix)
	{
		memcpy(m,rkMatrix.m,9*sizeof(Real));
	}
	Matrix3 (Real fEntry00, Real fEntry01, Real fEntry02,
				Real fEntry10, Real fEntry11, Real fEntry12,
				Real fEntry20, Real fEntry21, Real fEntry22)
	{
		m[0][0] = fEntry00;
		m[0][1] = fEntry01;
		m[0][2] = fEntry02;
		m[1][0] = fEntry10;
		m[1][1] = fEntry11;
		m[1][2] = fEntry12;
		m[2][0] = fEntry20;
		m[2][1] = fEntry21;
		m[2][2] = fEntry22;
	}

	// member access, allows use of construct mat[r][c]
	inline Real* operator[] (size_t iRow) const
	{
		return (Real*)m[iRow];
	}
	/*inline operator Real* ()
	{
		return (Real*)m[0];
	}*/
	Vector3 GetColumn (size_t iCol) const;
	void SetColumn(size_t iCol, const Vector3& vec);
	void FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis);

	// assignment and comparison
	inline Matrix3& operator= (const Matrix3& rkMatrix)
	{
		memcpy(m,rkMatrix.m,9*sizeof(Real));
		return *this;
	}
	bool operator== (const Matrix3& rkMatrix) const;
	inline bool operator!= (const Matrix3& rkMatrix) const
	{
		return !operator==(rkMatrix);
	}

	// arithmetic operations
	Matrix3 operator+ (const Matrix3& rkMatrix) const;
	Matrix3 operator- (const Matrix3& rkMatrix) const;
	Matrix3 operator* (const Matrix3& rkMatrix) const;
	Matrix3 operator- () const;

	// matrix * vector [3x3 * 3x1 = 3x1]
	Vector3 operator* (const Vector3& rkVector) const;

	// vector * matrix [1x3 * 3x3 = 1x3]
	SOEXPORT friend Vector3 operator* (const Vector3& rkVector,
		const Matrix3& rkMatrix);

	// matrix * scalar
	Matrix3 operator* (Real fScalar) const;

	// scalar * matrix
	SOEXPORT friend Matrix3 operator* (Real fScalar, const Matrix3& rkMatrix);

	// utilities
	Matrix3 Transpose () const;
	bool Inverse (Matrix3& rkInverse, Real fTolerance = 1e-06) const;
	Matrix3 Inverse (Real fTolerance = 1e-06) const;
	Real Determinant () const;

	// singular value decomposition
	void SingularValueDecomposition (Matrix3& rkL, Vector3& rkS,
		Matrix3& rkR) const;
	void SingularValueComposition (const Matrix3& rkL,
		const Vector3& rkS, const Matrix3& rkR);

	// Gram-Schmidt orthonormalization (applied to columns of rotation matrix)
	void Orthonormalize ();

	// orthogonal Q, diagonal D, upper triangular U stored as (u01,u02,u12)
	void QDUDecomposition (Matrix3& rkQ, Vector3& rkD,
		Vector3& rkU) const;

	Real SpectralNorm () const;

	// matrix must be orthonormal
	void ToAxisAngle (Vector3& rkAxis, Real& rfAngle) const;
	/*inline void ToAxisAngle (Vector3& rkAxis, Degree& rfAngle) const {
		Real r;
		ToAxisAngle ( rkAxis, r );
		rfAngle = r;
	}*/
	void FromAxisAngle (const Vector3& rkAxis, const Real& fRadians);

	// The matrix must be orthonormal.  The decomposition is yaw*pitch*roll
	// where yaw is rotation about the Up vector, pitch is rotation about the
	// Right axis, and roll is rotation about the Direction axis.
	bool ToEulerAnglesXYZ (Real& rfYAngle, Real& rfPAngle, Real& rfRAngle) const;
	bool ToEulerAnglesXZY (Real& rfYAngle, Real& rfPAngle, Real& rfRAngle) const;
	bool ToEulerAnglesYXZ (Real& rfYAngle, Real& rfPAngle, Real& rfRAngle) const;
	bool ToEulerAnglesYZX (Real& rfYAngle, Real& rfPAngle, Real& rfRAngle) const;
	bool ToEulerAnglesZXY (Real& rfYAngle, Real& rfPAngle, Real& rfRAngle) const;
	bool ToEulerAnglesZYX (Real& rfYAngle, Real& rfPAngle, Real& rfRAngle) const;
	void FromEulerAnglesXYZ (const Real& fYAngle, const Real& fPAngle, const Real& fRAngle);
	void FromEulerAnglesXZY (const Real& fYAngle, const Real& fPAngle, const Real& fRAngle);
	void FromEulerAnglesYXZ (const Real& fYAngle, const Real& fPAngle, const Real& fRAngle);
	void FromEulerAnglesYZX (const Real& fYAngle, const Real& fPAngle, const Real& fRAngle);
	void FromEulerAnglesZXY (const Real& fYAngle, const Real& fPAngle, const Real& fRAngle);
	void FromEulerAnglesZYX (const Real& fYAngle, const Real& fPAngle, const Real& fRAngle);
	// eigensolver, matrix must be symmetric
	void EigenSolveSymmetric (Real afEigenvalue[3],
		Vector3 akEigenvector[3]) const;

	static void TensorProduct (const Vector3& rkU, const Vector3& rkV,
		Matrix3& rkProduct);

	/** Determines if this matrix involves a scaling. */
	inline bool hasScale() const
	{
		// check magnitude of column vectors (==local axes)
		Real t = m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0];
		if (!Math::RealEqual(t, 1.0, 1e-04))
			return true;
		t = m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1];
		if (!Math::RealEqual(t, 1.0, 1e-04))
			return true;
		t = m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2];
		if (!Math::RealEqual(t, 1.0, 1e-04))
			return true;

		return false;
	}

	std::string toString() const
	{
		std::stringstream ss;
		ss << m[0][0] << " " << m[0][1] << " " << m[0][2] << " "
		   << m[1][0] << " " << m[1][1] << " " << m[1][2] << " "
		   << m[2][0] << " " << m[2][1] << " " << m[2][2];
		return ss.str();
	}

	static const Real EPSILON;
	static const Matrix3 ZERO;
	static const Matrix3 IDENTITY;

protected:
	// support for eigensolver
	void Tridiagonal (Real afDiag[3], Real afSubDiag[3]);
	bool QLAlgorithm (Real afDiag[3], Real afSubDiag[3]);

	// support for singular value decomposition
	static const Real ms_fSvdEpsilon;
	static const unsigned int ms_iSvdMaxIterations;
	static void Bidiagonalize (Matrix3& kA, Matrix3& kL,
		Matrix3& kR);
	static void GolubKahanStep (Matrix3& kA, Matrix3& kL,
		Matrix3& kR);

	// support for spectral norm
	static Real MaxCubicRoot (Real afCoeff[3]);

	Real m[3][3];

	// for faster access
	friend class Matrix4;
};
#endif
