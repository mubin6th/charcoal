#ifndef LINMATH_H
#define LINMATH_H

#include <math.h>
#include <string.h>

#ifdef LINMATH_NO_INLINE
#define LINMATH_H_FUNC static
#else
#define LINMATH_H_FUNC static inline
#endif

#define LINMATH_H_DEFINE_VEC(n) \
typedef float linmath_vec##n[n]; \
LINMATH_H_FUNC void linmath_vec##n##_add(linmath_vec##n r, linmath_vec##n const a, linmath_vec##n const b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i] + b[i]; \
} \
LINMATH_H_FUNC void linmath_vec##n##_sub(linmath_vec##n r, linmath_vec##n const a, linmath_vec##n const b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i] - b[i]; \
} \
LINMATH_H_FUNC void linmath_vec##n##_scale(linmath_vec##n r, linmath_vec##n const v, float const s) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = v[i] * s; \
} \
LINMATH_H_FUNC float linmath_vec##n##_mul_inner(linmath_vec##n const a, linmath_vec##n const b) \
{ \
	float p = 0.f; \
	int i; \
	for(i=0; i<n; ++i) \
		p += b[i]*a[i]; \
	return p; \
} \
LINMATH_H_FUNC float linmath_vec##n##_len(linmath_vec##n const v) \
{ \
	return sqrtf(linmath_vec##n##_mul_inner(v,v)); \
} \
LINMATH_H_FUNC void linmath_vec##n##_norm(linmath_vec##n r, linmath_vec##n const v) \
{ \
	float k = 1.f / linmath_vec##n##_len(v); \
	linmath_vec##n##_scale(r, v, k); \
} \
LINMATH_H_FUNC void linmath_vec##n##_min(linmath_vec##n r, linmath_vec##n const a, linmath_vec##n const b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i]<b[i] ? a[i] : b[i]; \
} \
LINMATH_H_FUNC void linmath_vec##n##_max(linmath_vec##n r, linmath_vec##n const a, linmath_vec##n const b) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = a[i]>b[i] ? a[i] : b[i]; \
} \
LINMATH_H_FUNC void linmath_vec##n##_dup(linmath_vec##n r, linmath_vec##n const src) \
{ \
	int i; \
	for(i=0; i<n; ++i) \
		r[i] = src[i]; \
}

LINMATH_H_DEFINE_VEC(2)
LINMATH_H_DEFINE_VEC(3)
LINMATH_H_DEFINE_VEC(4)

LINMATH_H_FUNC void linmath_vec3_mul_cross(linmath_vec3 r, linmath_vec3 const a, linmath_vec3 const b)
{
	r[0] = a[1]*b[2] - a[2]*b[1];
	r[1] = a[2]*b[0] - a[0]*b[2];
	r[2] = a[0]*b[1] - a[1]*b[0];
}

LINMATH_H_FUNC void linmath_vec3_reflect(linmath_vec3 r, linmath_vec3 const v, linmath_vec3 const n)
{
	float p = 2.f * linmath_vec3_mul_inner(v, n);
	int i;
	for(i=0;i<3;++i)
		r[i] = v[i] - p*n[i];
}

LINMATH_H_FUNC void linmath_vec4_mul_cross(linmath_vec4 r, linmath_vec4 const a, linmath_vec4 const b)
{
	r[0] = a[1]*b[2] - a[2]*b[1];
	r[1] = a[2]*b[0] - a[0]*b[2];
	r[2] = a[0]*b[1] - a[1]*b[0];
	r[3] = 1.f;
}

LINMATH_H_FUNC void linmath_vec4_reflect(linmath_vec4 r, linmath_vec4 const v, linmath_vec4 const n)
{
	float p  = 2.f*linmath_vec4_mul_inner(v, n);
	int i;
	for(i=0;i<4;++i)
		r[i] = v[i] - p*n[i];
}

typedef linmath_vec4 linmath_mat4x4[4];
LINMATH_H_FUNC void linmath_mat4x4_identity(linmath_mat4x4 M)
{
	int i, j;
	for(i=0; i<4; ++i)
		for(j=0; j<4; ++j)
			M[i][j] = i==j ? 1.f : 0.f;
}
LINMATH_H_FUNC void linmath_mat4x4_dup(linmath_mat4x4 M, linmath_mat4x4 const N)
{
	int i;
	for(i=0; i<4; ++i)
		linmath_vec4_dup(M[i], N[i]);
}
LINMATH_H_FUNC void linmath_mat4x4_row(linmath_vec4 r, linmath_mat4x4 const M, int i)
{
	int k;
	for(k=0; k<4; ++k)
		r[k] = M[k][i];
}
LINMATH_H_FUNC void linmath_mat4x4_col(linmath_vec4 r, linmath_mat4x4 const M, int i)
{
	int k;
	for(k=0; k<4; ++k)
		r[k] = M[i][k];
}
LINMATH_H_FUNC void linmath_mat4x4_transpose(linmath_mat4x4 M, linmath_mat4x4 const N)
{
    // Note: if M and N are the same, the user has to
    // explicitly make a copy of M and set it to N.
	int i, j;
	for(j=0; j<4; ++j)
		for(i=0; i<4; ++i)
			M[i][j] = N[j][i];
}
LINMATH_H_FUNC void linmath_mat4x4_add(linmath_mat4x4 M, linmath_mat4x4 const a, linmath_mat4x4 const b)
{
	int i;
	for(i=0; i<4; ++i)
		linmath_vec4_add(M[i], a[i], b[i]);
}
LINMATH_H_FUNC void linmath_mat4x4_sub(linmath_mat4x4 M, linmath_mat4x4 const a, linmath_mat4x4 const b)
{
	int i;
	for(i=0; i<4; ++i)
		linmath_vec4_sub(M[i], a[i], b[i]);
}
LINMATH_H_FUNC void linmath_mat4x4_scale(linmath_mat4x4 M, linmath_mat4x4 const a, float k)
{
	int i;
	for(i=0; i<4; ++i)
		linmath_vec4_scale(M[i], a[i], k);
}
LINMATH_H_FUNC void linmath_mat4x4_scale_aniso(linmath_mat4x4 M, linmath_mat4x4 const a, float x, float y, float z)
{
	linmath_vec4_scale(M[0], a[0], x);
	linmath_vec4_scale(M[1], a[1], y);
	linmath_vec4_scale(M[2], a[2], z);
	linmath_vec4_dup(M[3], a[3]);
}
LINMATH_H_FUNC void linmath_mat4x4_mul(linmath_mat4x4 M, linmath_mat4x4 const a, linmath_mat4x4 const b)
{
	linmath_mat4x4 temp;
	int k, r, c;
	for(c=0; c<4; ++c) for(r=0; r<4; ++r) {
		temp[c][r] = 0.f;
		for(k=0; k<4; ++k)
			temp[c][r] += a[k][r] * b[c][k];
	}
	linmath_mat4x4_dup(M, temp);
}
LINMATH_H_FUNC void linmath_mat4x4_mul_linmath_vec4(linmath_vec4 r, linmath_mat4x4 const M, linmath_vec4 const v)
{
	int i, j;
	for(j=0; j<4; ++j) {
		r[j] = 0.f;
		for(i=0; i<4; ++i)
			r[j] += M[i][j] * v[i];
	}
}
LINMATH_H_FUNC void linmath_mat4x4_translate(linmath_mat4x4 T, float x, float y, float z)
{
	linmath_mat4x4_identity(T);
	T[3][0] = x;
	T[3][1] = y;
	T[3][2] = z;
}
LINMATH_H_FUNC void linmath_mat4x4_translate_in_place(linmath_mat4x4 M, float x, float y, float z)
{
	linmath_vec4 t = {x, y, z, 0};
	linmath_vec4 r;
	int i;
	for (i = 0; i < 4; ++i) {
		linmath_mat4x4_row(r, M, i);
		M[3][i] += linmath_vec4_mul_inner(r, t);
	}
}
LINMATH_H_FUNC void linmath_mat4x4_from_linmath_vec3_mul_outer(linmath_mat4x4 M, linmath_vec3 const a, linmath_vec3 const b)
{
	int i, j;
	for(i=0; i<4; ++i) for(j=0; j<4; ++j)
		M[i][j] = i<3 && j<3 ? a[i] * b[j] : 0.f;
}
LINMATH_H_FUNC void linmath_mat4x4_rotate(linmath_mat4x4 R, linmath_mat4x4 const M, float x, float y, float z, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	linmath_vec3 u = {x, y, z};

	if(linmath_vec3_len(u) > 1e-4) {
		linmath_vec3_norm(u, u);
		linmath_mat4x4 T;
		linmath_mat4x4_from_linmath_vec3_mul_outer(T, u, u);

		linmath_mat4x4 S = {
			{    0,  u[2], -u[1], 0},
			{-u[2],     0,  u[0], 0},
			{ u[1], -u[0],     0, 0},
			{    0,     0,     0, 0}
		};
		linmath_mat4x4_scale(S, S, s);

		linmath_mat4x4 C;
		linmath_mat4x4_identity(C);
		linmath_mat4x4_sub(C, C, T);

		linmath_mat4x4_scale(C, C, c);

		linmath_mat4x4_add(T, T, C);
		linmath_mat4x4_add(T, T, S);

		T[3][3] = 1.f;
		linmath_mat4x4_mul(R, M, T);
	} else {
		linmath_mat4x4_dup(R, M);
	}
}
LINMATH_H_FUNC void linmath_mat4x4_rotate_X(linmath_mat4x4 Q, linmath_mat4x4 const M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	linmath_mat4x4 R = {
		{1.f, 0.f, 0.f, 0.f},
		{0.f,   c,   s, 0.f},
		{0.f,  -s,   c, 0.f},
		{0.f, 0.f, 0.f, 1.f}
	};
	linmath_mat4x4_mul(Q, M, R);
}
LINMATH_H_FUNC void linmath_mat4x4_rotate_Y(linmath_mat4x4 Q, linmath_mat4x4 const M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	linmath_mat4x4 R = {
		{   c, 0.f,  -s, 0.f},
		{ 0.f, 1.f, 0.f, 0.f},
		{   s, 0.f,   c, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	linmath_mat4x4_mul(Q, M, R);
}
LINMATH_H_FUNC void linmath_mat4x4_rotate_Z(linmath_mat4x4 Q, linmath_mat4x4 const M, float angle)
{
	float s = sinf(angle);
	float c = cosf(angle);
	linmath_mat4x4 R = {
		{   c,   s, 0.f, 0.f},
		{  -s,   c, 0.f, 0.f},
		{ 0.f, 0.f, 1.f, 0.f},
		{ 0.f, 0.f, 0.f, 1.f}
	};
	linmath_mat4x4_mul(Q, M, R);
}
LINMATH_H_FUNC void linmath_mat4x4_invert(linmath_mat4x4 T, linmath_mat4x4 const M)
{
	float s[6];
	float c[6];
	s[0] = M[0][0]*M[1][1] - M[1][0]*M[0][1];
	s[1] = M[0][0]*M[1][2] - M[1][0]*M[0][2];
	s[2] = M[0][0]*M[1][3] - M[1][0]*M[0][3];
	s[3] = M[0][1]*M[1][2] - M[1][1]*M[0][2];
	s[4] = M[0][1]*M[1][3] - M[1][1]*M[0][3];
	s[5] = M[0][2]*M[1][3] - M[1][2]*M[0][3];

	c[0] = M[2][0]*M[3][1] - M[3][0]*M[2][1];
	c[1] = M[2][0]*M[3][2] - M[3][0]*M[2][2];
	c[2] = M[2][0]*M[3][3] - M[3][0]*M[2][3];
	c[3] = M[2][1]*M[3][2] - M[3][1]*M[2][2];
	c[4] = M[2][1]*M[3][3] - M[3][1]*M[2][3];
	c[5] = M[2][2]*M[3][3] - M[3][2]*M[2][3];
	
	/* Assumes it is invertible */
	float idet = 1.0f/( s[0]*c[5]-s[1]*c[4]+s[2]*c[3]+s[3]*c[2]-s[4]*c[1]+s[5]*c[0] );
	
	T[0][0] = ( M[1][1] * c[5] - M[1][2] * c[4] + M[1][3] * c[3]) * idet;
	T[0][1] = (-M[0][1] * c[5] + M[0][2] * c[4] - M[0][3] * c[3]) * idet;
	T[0][2] = ( M[3][1] * s[5] - M[3][2] * s[4] + M[3][3] * s[3]) * idet;
	T[0][3] = (-M[2][1] * s[5] + M[2][2] * s[4] - M[2][3] * s[3]) * idet;

	T[1][0] = (-M[1][0] * c[5] + M[1][2] * c[2] - M[1][3] * c[1]) * idet;
	T[1][1] = ( M[0][0] * c[5] - M[0][2] * c[2] + M[0][3] * c[1]) * idet;
	T[1][2] = (-M[3][0] * s[5] + M[3][2] * s[2] - M[3][3] * s[1]) * idet;
	T[1][3] = ( M[2][0] * s[5] - M[2][2] * s[2] + M[2][3] * s[1]) * idet;

	T[2][0] = ( M[1][0] * c[4] - M[1][1] * c[2] + M[1][3] * c[0]) * idet;
	T[2][1] = (-M[0][0] * c[4] + M[0][1] * c[2] - M[0][3] * c[0]) * idet;
	T[2][2] = ( M[3][0] * s[4] - M[3][1] * s[2] + M[3][3] * s[0]) * idet;
	T[2][3] = (-M[2][0] * s[4] + M[2][1] * s[2] - M[2][3] * s[0]) * idet;

	T[3][0] = (-M[1][0] * c[3] + M[1][1] * c[1] - M[1][2] * c[0]) * idet;
	T[3][1] = ( M[0][0] * c[3] - M[0][1] * c[1] + M[0][2] * c[0]) * idet;
	T[3][2] = (-M[3][0] * s[3] + M[3][1] * s[1] - M[3][2] * s[0]) * idet;
	T[3][3] = ( M[2][0] * s[3] - M[2][1] * s[1] + M[2][2] * s[0]) * idet;
}
LINMATH_H_FUNC void linmath_mat4x4_orthonormalize(linmath_mat4x4 R, linmath_mat4x4 const M)
{
	linmath_mat4x4_dup(R, M);
	float s = 1.f;
	linmath_vec3 h;

	linmath_vec3_norm(R[2], R[2]);
	
	s = linmath_vec3_mul_inner(R[1], R[2]);
	linmath_vec3_scale(h, R[2], s);
	linmath_vec3_sub(R[1], R[1], h);
	linmath_vec3_norm(R[1], R[1]);

	s = linmath_vec3_mul_inner(R[0], R[2]);
	linmath_vec3_scale(h, R[2], s);
	linmath_vec3_sub(R[0], R[0], h);

	s = linmath_vec3_mul_inner(R[0], R[1]);
	linmath_vec3_scale(h, R[1], s);
	linmath_vec3_sub(R[0], R[0], h);
	linmath_vec3_norm(R[0], R[0]);
}

LINMATH_H_FUNC void linmath_mat4x4_frustum(linmath_mat4x4 M, float l, float r, float b, float t, float n, float f)
{
	M[0][0] = 2.f*n/(r-l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;
	
	M[1][1] = 2.f*n/(t-b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][0] = (r+l)/(r-l);
	M[2][1] = (t+b)/(t-b);
	M[2][2] = -(f+n)/(f-n);
	M[2][3] = -1.f;
	
	M[3][2] = -2.f*(f*n)/(f-n);
	M[3][0] = M[3][1] = M[3][3] = 0.f;
}
LINMATH_H_FUNC void linmath_mat4x4_ortho(linmath_mat4x4 M, float l, float r, float b, float t, float n, float f)
{
	M[0][0] = 2.f/(r-l);
	M[0][1] = M[0][2] = M[0][3] = 0.f;

	M[1][1] = 2.f/(t-b);
	M[1][0] = M[1][2] = M[1][3] = 0.f;

	M[2][2] = -2.f/(f-n);
	M[2][0] = M[2][1] = M[2][3] = 0.f;
	
	M[3][0] = -(r+l)/(r-l);
	M[3][1] = -(t+b)/(t-b);
	M[3][2] = -(f+n)/(f-n);
	M[3][3] = 1.f;
}
LINMATH_H_FUNC void linmath_mat4x4_perspective(linmath_mat4x4 m, float y_fov, float aspect, float n, float f)
{
	/* NOTE: Degrees are an unhandy unit to work with.
	 * linmath.h uses radians for everything! */
	float const a = 1.f / tanf(y_fov / 2.f);

	m[0][0] = a / aspect;
	m[0][1] = 0.f;
	m[0][2] = 0.f;
	m[0][3] = 0.f;

	m[1][0] = 0.f;
	m[1][1] = a;
	m[1][2] = 0.f;
	m[1][3] = 0.f;

	m[2][0] = 0.f;
	m[2][1] = 0.f;
	m[2][2] = -((f + n) / (f - n));
	m[2][3] = -1.f;

	m[3][0] = 0.f;
	m[3][1] = 0.f;
	m[3][2] = -((2.f * f * n) / (f - n));
	m[3][3] = 0.f;
}
LINMATH_H_FUNC void linmath_mat4x4_look_at(linmath_mat4x4 m, linmath_vec3 const eye, linmath_vec3 const center, linmath_vec3 const up)
{
	/* Adapted from Android's OpenGL Matrix.java.                        */
	/* See the OpenGL GLUT documentation for gluLookAt for a description */
	/* of the algorithm. We implement it in a straightforward way:       */

	/* TODO: The negation of of can be spared by swapping the order of
	 *       operands in the following cross products in the right way. */
	linmath_vec3 f;
	linmath_vec3_sub(f, center, eye);	
	linmath_vec3_norm(f, f);	
	
	linmath_vec3 s;
	linmath_vec3_mul_cross(s, f, up);
	linmath_vec3_norm(s, s);

	linmath_vec3 t;
	linmath_vec3_mul_cross(t, s, f);

	m[0][0] =  s[0];
	m[0][1] =  t[0];
	m[0][2] = -f[0];
	m[0][3] =   0.f;

	m[1][0] =  s[1];
	m[1][1] =  t[1];
	m[1][2] = -f[1];
	m[1][3] =   0.f;

	m[2][0] =  s[2];
	m[2][1] =  t[2];
	m[2][2] = -f[2];
	m[2][3] =   0.f;

	m[3][0] =  0.f;
	m[3][1] =  0.f;
	m[3][2] =  0.f;
	m[3][3] =  1.f;

	linmath_mat4x4_translate_in_place(m, -eye[0], -eye[1], -eye[2]);
}

typedef float quat[4];
#define quat_add linmath_vec4_add
#define quat_sub linmath_vec4_sub
#define quat_norm linmath_vec4_norm
#define quat_scale linmath_vec4_scale
#define quat_mul_inner linmath_vec4_mul_inner

LINMATH_H_FUNC void quat_identity(quat q)
{
	q[0] = q[1] = q[2] = 0.f;
	q[3] = 1.f;
}
LINMATH_H_FUNC void quat_mul(quat r, quat const p, quat const q)
{
	linmath_vec3 w, tmp;

	linmath_vec3_mul_cross(tmp, p, q);
	linmath_vec3_scale(w, p, q[3]);
	linmath_vec3_add(tmp, tmp, w);
	linmath_vec3_scale(w, q, p[3]);
	linmath_vec3_add(tmp, tmp, w);

	linmath_vec3_dup(r, tmp);
	r[3] = p[3]*q[3] - linmath_vec3_mul_inner(p, q);
}
LINMATH_H_FUNC void quat_conj(quat r, quat const q)
{
	int i;
	for(i=0; i<3; ++i)
		r[i] = -q[i];
	r[3] = q[3];
}
LINMATH_H_FUNC void quat_rotate(quat r, float angle, linmath_vec3 const axis) {
    linmath_vec3 axis_norm;
    linmath_vec3_norm(axis_norm, axis);
    float s = sinf(angle / 2);
    float c = cosf(angle / 2);
    linmath_vec3_scale(r, axis_norm, s);
    r[3] = c;
}
LINMATH_H_FUNC void quat_mul_linmath_vec3(linmath_vec3 r, quat const q, linmath_vec3 const v)
{
/*
 * Method by Fabian 'ryg' Giessen (of Farbrausch)
t = 2 * cross(q.xyz, v)
v' = v + q.w * t + cross(q.xyz, t)
 */
	linmath_vec3 t;
	linmath_vec3 q_xyz = {q[0], q[1], q[2]};
	linmath_vec3 u = {q[0], q[1], q[2]};

	linmath_vec3_mul_cross(t, q_xyz, v);
	linmath_vec3_scale(t, t, 2);

	linmath_vec3_mul_cross(u, q_xyz, t);
	linmath_vec3_scale(t, t, q[3]);

	linmath_vec3_add(r, v, t);
	linmath_vec3_add(r, r, u);
}
LINMATH_H_FUNC void linmath_mat4x4_from_quat(linmath_mat4x4 M, quat const q)
{
	float a = q[3];
	float b = q[0];
	float c = q[1];
	float d = q[2];
	float a2 = a*a;
	float b2 = b*b;
	float c2 = c*c;
	float d2 = d*d;
	
	M[0][0] = a2 + b2 - c2 - d2;
	M[0][1] = 2.f*(b*c + a*d);
	M[0][2] = 2.f*(b*d - a*c);
	M[0][3] = 0.f;

	M[1][0] = 2*(b*c - a*d);
	M[1][1] = a2 - b2 + c2 - d2;
	M[1][2] = 2.f*(c*d + a*b);
	M[1][3] = 0.f;

	M[2][0] = 2.f*(b*d + a*c);
	M[2][1] = 2.f*(c*d - a*b);
	M[2][2] = a2 - b2 - c2 + d2;
	M[2][3] = 0.f;

	M[3][0] = M[3][1] = M[3][2] = 0.f;
	M[3][3] = 1.f;
}

LINMATH_H_FUNC void linmath_mat4x4o_mul_quat(linmath_mat4x4 R, linmath_mat4x4 const M, quat const q)
{
/*  XXX: The way this is written only works for orthogonal matrices. */
/* TODO: Take care of non-orthogonal case. */
	quat_mul_linmath_vec3(R[0], q, M[0]);
	quat_mul_linmath_vec3(R[1], q, M[1]);
	quat_mul_linmath_vec3(R[2], q, M[2]);

	R[3][0] = R[3][1] = R[3][2] = 0.f;
	R[0][3] = M[0][3];
	R[1][3] = M[1][3];
	R[2][3] = M[2][3];
	R[3][3] = M[3][3];  // typically 1.0, but here we make it general
}
LINMATH_H_FUNC void quat_from_linmath_mat4x4(quat q, linmath_mat4x4 const M)
{
	float r=0.f;
	int i;

	int perm[] = { 0, 1, 2, 0, 1 };
	int *p = perm;

	for(i = 0; i<3; i++) {
		float m = M[i][i];
		if( m < r )
			continue;
		m = r;
		p = &perm[i];
	}

	r = sqrtf(1.f + M[p[0]][p[0]] - M[p[1]][p[1]] - M[p[2]][p[2]] );

	if(r < 1e-6) {
		q[0] = 1.f;
		q[1] = q[2] = q[3] = 0.f;
		return;
	}

	q[0] = r/2.f;
	q[1] = (M[p[0]][p[1]] - M[p[1]][p[0]])/(2.f*r);
	q[2] = (M[p[2]][p[0]] - M[p[0]][p[2]])/(2.f*r);
	q[3] = (M[p[2]][p[1]] - M[p[1]][p[2]])/(2.f*r);
}

LINMATH_H_FUNC void linmath_mat4x4_arcball(linmath_mat4x4 R, linmath_mat4x4 const M, linmath_vec2 const _a, linmath_vec2 const _b, float s)
{
	linmath_vec2 a; memcpy(a, _a, sizeof(a));
	linmath_vec2 b; memcpy(b, _b, sizeof(b));
	
	float z_a = 0.;
	float z_b = 0.;

	if(linmath_vec2_len(a) < 1.) {
		z_a = sqrtf(1. - linmath_vec2_mul_inner(a, a));
	} else {
		linmath_vec2_norm(a, a);
	}

	if(linmath_vec2_len(b) < 1.) {
		z_b = sqrtf(1. - linmath_vec2_mul_inner(b, b));
	} else {
		linmath_vec2_norm(b, b);
	}
	
	linmath_vec3 a_ = {a[0], a[1], z_a};
	linmath_vec3 b_ = {b[0], b[1], z_b};

	linmath_vec3 c_;
	linmath_vec3_mul_cross(c_, a_, b_);

	float const angle = acos(linmath_vec3_mul_inner(a_, b_)) * s;
	linmath_mat4x4_rotate(R, M, c_[0], c_[1], c_[2], angle);
}
#endif
