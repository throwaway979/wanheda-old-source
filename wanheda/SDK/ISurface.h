#pragma once
#include "..\Utils\Color.h"
#include "..\Utils\Utils.h"
#include "..\Utils\SPoint.h"
#include <d3d9.h>

#define COL2DWORD(x) (D3DCOLOR_ARGB(x.alpha, x.red, x.green, x.blue))

enum EFontFlags {
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

struct Vertex {
	float x, y, z, rhw;
	DWORD color;
};

struct Vertex_t {
	Vector2D	mPosition;
	Vector2D	m_TexCoord;

	Vertex_t( ) {}
	Vertex_t( const Vector2D& pos, const Vector2D& coord = Vector2D( 0, 0 ) )
	{
		mPosition = pos;
		m_TexCoord = coord;
	}
	void Init( const Vector2D& pos, const Vector2D& coord = Vector2D( 0, 0 ) )
	{
		mPosition = pos;
		m_TexCoord = coord;
	}
};

typedef  Vertex_t FontVertex_t;

class ISurface {
public:
	void UnLockCursor( )
	{
		typedef void( __thiscall * Fn )( void* );
		Utils::GetVFunc< Fn >( this, 66 )( this );
	}

	void DrawSetColor( Color col )
	{
		typedef void( __thiscall * Fn )( PVOID, Color );
		return Utils::GetVFunc< Fn >( this, 14 )( this, col );
	}

	void DrawSetColor( int r, int g, int b, int a )
	{
		typedef void( __thiscall * Fn )( PVOID, int, int, int, int );
		Utils::GetVFunc< Fn >( this, 15 )( this, r, g, b, a );
	}

	void TexturedPolygon( int n, std::vector<Vertex_t> vertice, Color color )
	{
		static int texture_id = CreateNewTextureID( true ); // 
		static unsigned char buf[ 4 ] = { 255, 255, 255, 255 };
		DrawSetTextureRGBA( texture_id, buf, 1, 1 ); //
		DrawSetColor( color ); //
		DrawSetTexture( texture_id ); //
		DrawTexturedPolygon( n, vertice.data( ) ); //
	}

	void DrawFilledRect( int x0, int y0, int x1, int y1 )
	{
		typedef void( __thiscall * Fn )( PVOID, int, int, int, int );
		Utils::GetVFunc< Fn >( this, 16 )( this, x0, y0, x1, y1 );
	}

	void DrawOutlinedRect( int x0, int y0, int x1, int y1 )
	{
		typedef void( __thiscall * Fn )( PVOID, int, int, int, int );
		Utils::GetVFunc< Fn >( this, 18 )( this, x0, y0, x1, y1 );
	}

	void DrawLine( int x0, int y0, int x1, int y1 )
	{
		typedef void( __thiscall * Fn )( PVOID, int, int, int, int );
		Utils::GetVFunc< Fn >( this, 19 )( this, x0, y0, x1, y1 );
	}

	void DrawPolyLine( int* x, int* y, int count )
	{
		typedef void( __thiscall * Fn )( PVOID, int*, int*, int );
		Utils::GetVFunc< Fn >( this, 20 )( this, x, y, count );
	}

	void DrawSetTextFont( unsigned long font )
	{
		typedef void( __thiscall * Fn )( PVOID, unsigned long );
		Utils::GetVFunc< Fn >( this, 23 )( this, font );
	}

	void DrawSetTextColor( int r, int g, int b, int a )
	{
		typedef void( __thiscall * Fn )( PVOID, int, int, int, int );
		Utils::GetVFunc< Fn >( this, 25 )( this, r, g, b, a );
	}

	void DrawSetTextColor( Color col )
	{
		typedef void( __thiscall * Fn )( PVOID, Color );
		return Utils::GetVFunc< Fn >( this, 24 )( this, col );
	}

	void DrawSetTextPos( int x, int y )
	{
		typedef void( __thiscall * Fn )( PVOID, int, int );
		Utils::GetVFunc< Fn >( this, 26 )( this, x, y );
	}

	void DrawPrintText( const wchar_t* text, int textLen )
	{
		typedef void( __thiscall * Fn )( PVOID, const wchar_t*, int, int );
		Utils::GetVFunc< Fn >( this, 28 )( this, text, textLen, 0 );
	}

	void DrawSetTexture( int textureID )
	{
		typedef void( __thiscall * Fn )( PVOID, int );
		return Utils::GetVFunc< Fn >( this, 38 )( this, textureID );
	}

	void DrawSetTextureRGBA( int textureID, unsigned char  const* colors, int w, int h )
	{
		typedef void( __thiscall * Fn )( PVOID, int, unsigned char  const*, int, int );
		return Utils::GetVFunc< Fn >( this, 37 )( this, textureID, colors, w, h );
	}

	int CreateNewTextureID( bool procedural )
	{
		typedef int( __thiscall * Fn )( PVOID, bool );
		return Utils::GetVFunc< Fn >( this, 43 )( this, procedural );
	}

	void DrawTexturedPolygon( int vtxCount, FontVertex_t* vtx, bool bClipVertices = true )
	{
		typedef void( __thiscall * Fn )( PVOID, int, FontVertex_t*, bool );
		return Utils::GetVFunc< Fn >( this, 106 )( this, vtxCount, vtx, bClipVertices );
	}

	unsigned long FontCreate( )
	{
		typedef unsigned int( __thiscall * Fn )( PVOID );
		return Utils::GetVFunc< Fn >( this, 71 )( this );
	}

	void SetFontGlyphSet( unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags )
	{
		typedef void( __thiscall * Fn )( PVOID, unsigned long, const char*, int, int, int, int, int, int, int );
		Utils::GetVFunc< Fn >( this, 72 )( this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0 );
	}

	void ISurface::GetTextSize( DWORD font, const wchar_t* text, int& wide, int& tall )
	{
		typedef void( __thiscall * Fn )( void*, DWORD, const wchar_t*, int&, int& );
		return Utils::GetVFunc<Fn>( this, 79 )( this, font, text, wide, tall );
	}

	void DrawOutlinedCircle( int x, int y, int r, int seg )
	{
		typedef void( __thiscall * Fn )( PVOID, int, int, int, int );
		return Utils::GetVFunc< Fn >( this, 103 )( this, x, y, r, seg );
	}

	void draw_filled_rect_fade( int x0, int y0, int w, int h, size_t alpha0, size_t alpha1, bool horizontal ) {
		using original_fn = void( __thiscall* )( void*, int, int, int, int, size_t, size_t, bool );
		Utils::GetVFunc< original_fn >( this, 123 )( this, x0, y0, x0 + w, y0 + h, alpha0, alpha1, horizontal ); //hopefully this index is correct
	}

	void DrawProgressCircle( int x, int y, float progress, int radius, Color color )
	{
		constexpr int res = 256;
		constexpr float step = M_PI * 2.f / res;
		float amt = res * progress;
		int _x[ 512 ], _y[ 512 ];

		for ( int i = 0; i < amt; i++ ) {
			float theta = i * step;
			float x_off = radius * cos( theta );
			float y_off = radius * sin( theta );
		}

		for ( int i = amt; i > 0; --i ) {
			float theta = i * step;
			float x_off = radius * cos( theta );
			float y_off = radius * sin( theta );
		}

		DrawPolyLine( _x, _y, amt * 2 );
	}

	void SurfaceGetCursorPos( int& x, int& y )
	{
		typedef void( __thiscall * Fn )( PVOID, int&, int& );
		return Utils::GetVFunc< Fn >( this, 66 )( this, x, y );
	}

	void RoundedFilledRect( int x, int y, int width, int height, float radius, Color col ) { // UC https://www.unknowncheats.me/forum/1498179-post4.html
		// TODO: make the quality not hardcoded -green
		// don't you have to give it quality in the formula you wrote? 8 + 4 * ( quality ) ? -dex
		constexpr int quality = 24;

		static Vertex_t verts[ quality ];

		Vector2D add = { 0, 0 };

		for ( int i = 0; i < quality; i++ ) {
			float angle = ( static_cast < float > ( i ) / -quality ) * 6.28f - ( 6.28f / 16.f );

			verts[ i ].mPosition.x = radius + x + add.x + ( radius * sin( angle ) );
			verts[ i ].mPosition.y = height - radius + y + add.y + ( radius * cos( angle ) );

			if ( i == 4 ) {
				add.y = -height + ( radius * 2 );
			}
			else if ( i == 10 ) {
				add.x = width - ( radius * 2 );
			}
			else if ( i == 16 ) {
				add.y = 0;
			}
			else if ( i == 22 ) {
				add.x = 0;
			}
		}
		DrawSetColor( col.red, col.green, col.blue, col.alpha );
		DrawTexturedPolygon( quality, verts );
	}

	void vertical_gradient_rect( int x, int y, int w, int h, Color top, Color bottom ) {
		DrawSetColor( top.red, top.green, top.blue, top.alpha );
		draw_filled_rect_fade( x, y, w, h, 255, 255, false );
		DrawSetColor( bottom.red, bottom.green, bottom.blue, bottom.alpha );
		draw_filled_rect_fade( x, y, w, h, 0, 255, false );
	}

	void horizontal_gradient_rect( int x, int y, int w, int h, Color left, Color right ) {
		DrawSetColor( left.red, left.green, left.blue, left.alpha );
		draw_filled_rect_fade( x, y, w, h, 255, 255, true );
		DrawSetColor( right.red, right.green, right.blue, right.alpha );
		draw_filled_rect_fade( x, y, w, h, 0, 255, true );
	}

	void FilledRect( int x, int y, int w, int h, Color color )
	{
		DrawSetColor( color.red, color.green, color.blue, color.alpha );
		DrawFilledRect( x, y, x + w, y + h );
	}

	void FilledGradientRect( int x, int y, int w, int h, Color color1, Color color2 )
	{
		FilledRect( x, y, w, h, color1 );
		BYTE First = color2.red;
		BYTE Second = color2.green;
		BYTE Third = color2.blue;
		for ( int i = 0; i < h; i++ )
		{
			float fi = i, fh = h;
			float a = fi / fh;
			DWORD ia = a * 255;
			FilledRect( x, y + i, w, 1, Color( First, Second, Third, ia ) );
		}
	}

	void OutlinedRect( int x, int y, int w, int h, Color color )
	{
		DrawSetColor( color.red, color.green, color.blue, color.alpha );
		DrawOutlinedRect( x, y, x + w, y + h );
	}

	void Circle( int x, int y, int r, int s, Color col ) {
		float Step = M_PI * 2.0 / s;
		for ( float a = 0; a < ( M_PI * 2.0 ); a += Step )
		{
			float x1 = r * cos( a ) + x;
			float y1 = r * sin( a ) + y;
			float x2 = r * cos( a + Step ) + x;
			float y2 = r * sin( a + Step ) + y;
			DrawSetColor( col.red, col.green, col.blue, col.alpha );
			DrawLine( x1, y1, x2, y2 );
		}
	}

	void OutlinedVecRect( int x, int y, int x2, int y2, Color color )
	{
		DrawSetColor( color.red, color.green, color.blue, color.alpha );
		DrawLine( x, y, x2, y );
		DrawLine( x2, y, x2, y2 );
		DrawLine( x2, y2, x, y2 );
		DrawLine( x, y2, x, y );
	}

	void Line( int x, int y, int x2, int y2, Color color )
	{
		DrawSetColor( color.red, color.green, color.blue, color.alpha );
		DrawLine( x, y, x2, y2 );
	}

	void DrawT( int X, int Y, Color Color, int Font, bool Center, const char* _Input, ... )
	{
		/*want to draw text? sucks for you*/
		/*actually i'm not that mean, so here you go, have fun memory leaking*/
		
		/*stock stickrpg*/
		int apple = 0;
		char Buffer[ 2048 ] = { '\0' };
		va_list Args;

		va_start( Args, _Input );
		vsprintf_s( Buffer, _Input, Args );
		va_end( Args );

		size_t Size = strlen( Buffer ) + 1;
		wchar_t* WideBuffer = new wchar_t[ Size ]; //laxol's gonna be mad!!

		mbstowcs_s( 0, WideBuffer, Size, Buffer, Size - 1 );

		int Width = 0, Height = 0;

		if ( Center )
			GetTextSize( Font, WideBuffer, Width, Height );

		DrawSetTextColor( Color.red, Color.green, Color.blue, Color.alpha );
		DrawSetTextFont( Font );
		DrawSetTextPos( X - ( Width / 2 ), Y );
		DrawPrintText( WideBuffer, wcslen( WideBuffer ) );
	}

	void DrawTUni( int x, int y, Color color, DWORD font, const wchar_t* text )
	{
		DrawSetTextFont( font );
		DrawSetTextColor( color );
		DrawSetTextPos( x, y );
		DrawPrintText( text, wcslen( text ) );
	}

	RECT GetTextSizeRect( DWORD font, const char* text ) // ayyware or something
	{
		size_t origsize = strlen( text ) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t wcstring[ newsize ];
		mbstowcs_s( &convertedChars, wcstring, origsize, text, _TRUNCATE );

		RECT rect; int x, y;
		GetTextSize( font, wcstring, x, y );
		rect.left = x; rect.bottom = y;
		rect.right = x;
		return rect;
	}

	Vector2D GetMousePosition( ) // bolbi ware
	{
		POINT mousePosition;
		GetCursorPos( &mousePosition );
		ScreenToClient( FindWindow( 0, "Counter-Strike: Global Offensive" ), &mousePosition );
		return { static_cast< float >( mousePosition.x ), static_cast< float >( mousePosition.y ) };
	}

	bool MouseInRegion( int x, int y, int x2, int y2 ) {
		if ( GetMousePosition( ).x > x && GetMousePosition( ).y > y && GetMousePosition( ).x < x2 + x && GetMousePosition( ).y < y2 + y )
			return true;
		return false;
	}
};

extern ISurface* g_pSurface;
