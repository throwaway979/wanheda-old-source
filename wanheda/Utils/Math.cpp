#include "Math.h"
#include "../SDK/Vector.h"
#include "../SDK/VMatrix.h"
#include "../Utils/SPoint.h"
#include <array>

Math g_Math;

//not taking credit for any of this math

void Math::RotateTriangle( std::array<Vector2D, 3>& points, float rotation )
{
	const auto points_center = ( points.at( 0 ) + points.at( 1 ) + points.at( 2 ) ) / 3;
	for ( auto& point : points )
	{
		point -= points_center;

		const auto temp_x = point.x;
		const auto temp_y = point.y;

		const auto theta = DEG_2_RAD( rotation );
		const auto c = cosf( theta );
		const auto s = sinf( theta );

		point.x = temp_x * c - temp_y * s;
		point.y = temp_x * s + temp_y * c;

		point += points_center;
	}
}

void Math::VectorAngles( const Vector& vecForward, Vector& vecAngles )
{
	Vector vecView;
	if ( vecForward[ 1 ] == 0.f && vecForward[ 0 ] == 0.f )
	{
		vecView[ 0 ] = 0.f;
		vecView[ 1 ] = 0.f;
	}
	else
	{
		vecView[ 1 ] = atan2( vecForward[ 1 ], vecForward[ 0 ] ) * 180.f / 3.14159265358979323846f;

		if ( vecView[ 1 ] < 0.f )
			vecView[ 1 ] += 360.f;

		vecView[ 2 ] = sqrt( vecForward[ 0 ] * vecForward[ 0 ] + vecForward[ 1 ] * vecForward[ 1 ] );

		vecView[ 0 ] = atan2( vecForward[ 2 ], vecView[ 2 ] ) * 180.f / 3.14159265358979323846f;
	}

	vecAngles[ 0 ] = -vecView[ 0 ];
	vecAngles[ 1 ] = vecView[ 1 ];
	vecAngles[ 2 ] = 0.f;
}

void Math::VectorAngles( const Vector & forward, Vector & up, Vector & angles ) {
	Vector left = CrossProduct( up, forward );
	left.NormalizeInPlace( );

	float forwardDist = forward.Length2D( );

	if ( forwardDist > 0.001f ) {
		angles.x = atan2f( -forward.z, forwardDist ) * 180 / M_PI;
		angles.y = atan2f( forward.y, forward.x ) * 180 / M_PI;

		float upZ = ( left.y * forward.x ) - ( left.x * forward.y );
		angles.z = atan2f( left.z, upZ ) * 180 / M_PI;
	}
	else {
		angles.x = atan2f( -forward.z, forwardDist ) * 180 / M_PI;
		angles.y = atan2f( -left.x, left.y ) * 180 / M_PI;
		angles.z = 0;
	}
}

Vector Math::CalcAngle( const Vector & vecSource, const Vector & vecDestination )
{
	Vector qAngles;
	Vector delta = Vector( ( vecSource[ 0 ] - vecDestination[ 0 ] ), ( vecSource[ 1 ] - vecDestination[ 1 ] ), ( vecSource[ 2 ] - vecDestination[ 2 ] ) );
	float hyp = sqrtf( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );
	qAngles[ 0 ] = ( float )( atan( delta[ 2 ] / hyp ) * ( 180.0f / M_PI ) );
	qAngles[ 1 ] = ( float )( atan( delta[ 1 ] / delta[ 0 ] ) * ( 180.0f / M_PI ) );
	qAngles[ 2 ] = 0.f;
	if ( delta[ 0 ] >= 0.f )
		qAngles[ 1 ] += 180.f;

	return qAngles;
}

void Math::VectorTransform( const Vector in1, const matrix3x4_t in2, Vector & out ) {
	out[ 0 ] = DotProduct( in1, Vector( in2[ 0 ][ 0 ], in2[ 0 ][ 1 ], in2[ 0 ][ 2 ] ) ) + in2[ 0 ][ 3 ];
	out[ 1 ] = DotProduct( in1, Vector( in2[ 1 ][ 0 ], in2[ 1 ][ 1 ], in2[ 1 ][ 2 ] ) ) + in2[ 1 ][ 3 ];
	out[ 2 ] = DotProduct( in1, Vector( in2[ 2 ][ 0 ], in2[ 2 ][ 1 ], in2[ 2 ][ 2 ] ) ) + in2[ 2 ][ 3 ];
}

vec_t Math::VectorNormalize( Vector & v )
{
	vec_t l = v.Length( );

	if ( l != 0.0f )
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f; v.z = 1.0f;
	}

	return l;
}

void Math::AngleVectors( const Vector & angles, Vector * forward )
{
	Assert( s_bMathlibInitialized );
	Assert( forward );

	float	sp, sy, cp, cy;

	sy = sin( DEG2RAD( angles[ 1 ] ) );
	cy = cos( DEG2RAD( angles[ 1 ] ) );

	sp = sin( DEG2RAD( angles[ 0 ] ) );
	cp = cos( DEG2RAD( angles[ 0 ] ) );

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

void Math::NormalizeAngles( Vector & angles )
{
	for ( auto i = 0; i < 3; i++ ) {
		while ( angles[ i ] < -180.0f ) angles[ i ] += 360.0f;
		while ( angles[ i ] > 180.0f ) angles[ i ] -= 360.0f;
	}
}
Vector Math::NormalizeAngle( Vector angle )
{
	while ( angle.x < -180.0f ) angle.x += 360.0f;
	while ( angle.x > 180.0f ) angle.x -= 360.0f;

	while ( angle.y < -180.0f ) angle.y += 360.0f;
	while ( angle.y > 180.0f ) angle.y -= 360.0f;

	while ( angle.z < -180.0f ) angle.z += 360.0f;
	while ( angle.z > 180.0f ) angle.z -= 360.0f;

	return angle;
}
float Math::NormalizeYaw( float yaw )
{
	if ( yaw > 180 )
		yaw -= ( round( yaw / 360 ) * 360.f );
	else if ( yaw < -180 )
		yaw += ( round( yaw / 360 ) * -360.f );

	return yaw;
}

void sin_cos( float radian, float* sin, float* cos )
{
	*sin = std::sin( radian );
	*cos = std::cos( radian );
}

void Math::AngleVectors( const Vector & angles, Vector * forward, Vector * right, Vector * up )
{
	float sp, sy, sr, cp, cy, cr;

	sin_cos( GRD_TO_BOG( angles.x ), &sp, &cp );
	sin_cos( GRD_TO_BOG( angles.y ), &sy, &cy );
	sin_cos( GRD_TO_BOG( angles.z ), &sr, &cr );

	if ( forward != nullptr )
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if ( right != nullptr )
	{
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if ( up != nullptr )
	{
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

float Math::YawDistance(float firstangle, float secondangle)
{
	if (firstangle == secondangle)
		return 0.f;

	bool oppositeSides = false;

	if (firstangle > 0 && secondangle < 0)
		oppositeSides = true;
	else if (firstangle < 0 && secondangle > 0)
		oppositeSides = true;

	if (!oppositeSides)
		return fabs(firstangle - secondangle);

	bool past90 = false;

	if (firstangle > 90 && secondangle < -90)
	{
		firstangle -= (firstangle - 90);
		secondangle += (secondangle + 90);
	}
	else if (firstangle < -90 && secondangle > 90)
	{
		firstangle += (firstangle + 90);
		secondangle -= (secondangle - 90);
	}

	float oneTwo;

	oneTwo = fabs(firstangle - secondangle);

	return oneTwo;
}

void Math::RandomSeed( int seed )
{
	static auto random_seed = reinterpret_cast< void( * )( int ) >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomSeed" ) );

	random_seed( seed );
}

float Math::RandomFloat( float min, float max )
{
	static auto random_float = reinterpret_cast< float( * )( float, float ) >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomFloat" ) );

	return random_float( min, max );
}
Vector Math::ClampAngle( Vector angle )
{
	while ( angle.y > 180 ) angle.y -= 360;
	while ( angle.y < -180 ) angle.y += 360;

	if ( angle.x > 89.0f ) angle.x = 89.0f;
	if ( angle.x < -89.0f ) angle.x = -89.0f;

	angle.z = 0.f;

	return angle;
}
void Math::ClampAngles( Vector & angles ) {
	if ( angles.y > 180.0f )
		angles.y = 180.0f;
	else if ( angles.y < -180.0f )
		angles.y = -180.0f;

	if ( angles.x > 89.0f )
		angles.x = 89.0f;
	else if ( angles.x < -89.0f )
		angles.x = -89.0f;

	angles.z = 0;
}

bool Math::Clamp( Vector & angles )
{
	Vector a = angles;
	NormalizeAngles( a );
	ClampAngles( a );

	if ( isnan( a.x ) || isinf( a.x ) ||
		isnan( a.y ) || isinf( a.y ) ||
		isnan( a.z ) || isinf( a.z ) ) {
		return false;
	}
	else {
		angles = a;
		return true;
	}
}

float Math::GRD_TO_BOG( float GRD ) {
	return ( M_PI / 180 ) * GRD;
}

float Math::Distance( Vector2D point1, Vector2D point2 )
{
	float diffY = point1.y - point2.y;
	float diffX = point1.x - point2.x;
	return sqrt( ( diffY * diffY ) + ( diffX * diffX ) );
}

void Math::AngleMatrix( const Vector & angles, matrix3x4_t & matrix )
{
	float sr, sp, sy, cr, cp, cy;

	sin_cos( DEG2RAD( angles[ 1 ] ), &sy, &cy );
	sin_cos( DEG2RAD( angles[ 0 ] ), &sp, &cp );
	sin_cos( DEG2RAD( angles[ 2 ] ), &sr, &cr );

	// matrix = (YAW * PITCH) * ROLL
	matrix[ 0 ][ 0 ] = cp * cy;
	matrix[ 1 ][ 0 ] = cp * sy;
	matrix[ 2 ][ 0 ] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;
	matrix[ 0 ][ 1 ] = sp * srcy - crsy;
	matrix[ 1 ][ 1 ] = sp * srsy + crcy;
	matrix[ 2 ][ 1 ] = sr * cp;

	matrix[ 0 ][ 2 ] = ( sp * crcy + srsy );
	matrix[ 1 ][ 2 ] = ( sp * crsy - srcy );
	matrix[ 2 ][ 2 ] = cr * cp;

	matrix[ 0 ][ 3 ] = 0.0f;
	matrix[ 1 ][ 3 ] = 0.0f;
	matrix[ 2 ][ 3 ] = 0.0f;
}

void Math::MatrixSetColumn( const Vector & in, int column, matrix3x4_t & out )
{
	out[ 0 ][ column ] = in.x;
	out[ 1 ][ column ] = in.y;
	out[ 2 ][ column ] = in.z;
}

void Math::AngleMatrix( const Vector & angles, const Vector & position, matrix3x4_t & matrix )
{
	AngleMatrix( angles, matrix );
	MatrixSetColumn( position, 3, matrix );
}