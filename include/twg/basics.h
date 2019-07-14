#pragma once

#include <string>

namespace twg
{

	#define TWG_max(a,b) ((a)>(b) ? (a) : (b))
	#define TWG_min(a,b) ((a)<(b) ? (a) : (b))

	typedef int8_t		int8;
	typedef int16_t		int16;
	typedef int32_t		int32; 
	typedef int64_t		int64;
	
	typedef uint8_t		int8u;
	typedef uint16_t	int16u;
	typedef uint32_t	int32u;
	typedef uint64_t	int64u;

	struct Rect;
	enum CycleType : int32u;
	enum KeyType : int32u;
	enum CursorType : int32u;
	enum MessageType : int32u;
	enum MessageReturnType : int32u;

	/** Математическая константа Пи. */
	const double pi = 3.14159265358979323846;

	//-------------------------------------------------------------------------
	/** @class Rect
		Структура, задающая одновременно и размер и положение окна. Окно считается прямоугольником. Прямоугольник можно однозначно задать двумя точками(наклоны не учитываются) - верхней левой вершиной(точка A) и нижней правой вершиной(точка B). Эта структура описывает как раз эти две точки. Позиция окна - точка A. Размер окна B-A. 
	 */
	struct Rect {
		int32 ax, ay, bx, by;

		Rect(int32 ax, int32 ay, int32 bx, int32 by) : 
			ax(ax), ay(ay), bx(bx), by(by) {}
		Rect() : ax(0), ay(0), bx(0), by(0) {}

		/** @return размер окна по горизонтали. */
		int32 x(void) { return bx-ax; }
		/** @return размер окна по вертикали. */
		int32 y(void) { return by-ay; }
	};

	//-------------------------------------------------------------------------
	/** Переводит угол из градусов в радианы. */
	double 	deg2rad(double deg);
	/** Переводит угол из радиан в градусы. */
	double 	rad2deg(double rad);
	/** В зависимости от переменной pos результат будет циклически меняться в промежутке [0, 1]. CycleType задает этот цикл. Более подробно о типах циклов см. \ref CycleType. Используется для рисования градиентов. */
	double 	computeCycle(double pos, CycleType type);

	inline std::string wstr2str(const std::string& str) {
		return std::string(str.begin(), str.end());
	}

	//-------------------------------------------------------------------------
	/** Тип цикла. См \ref computeCycle. */
	enum CycleType : int32u
	{
		CYCLE_NULL, ///< Обрезается на нуле и на единице.
		CYCLE_SIN, ///< y=x на промежутке [0, 1] повторяется как sin.
		CYCLE_TAN ///< y=x на промежутке [0, 1] повторяется как tg.
	};

//=============================================================================
//=============================================================================
//=============================================================================

//-----------------------------------------------------------------------------
inline double deg2rad(double deg) {
	return deg * pi / 180.0;
}

//-----------------------------------------------------------------------------
inline double rad2deg(double rad) {
	return rad * 180.0 / pi;
}

}