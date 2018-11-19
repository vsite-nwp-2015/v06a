#pragma once

class Brush{
	HBRUSH h;
public:
	Brush(COLORREF color, int hatch = -1) :
	  h(hatch >= 0 ? CreateHatchBrush(hatch, color) : ::CreateSolidBrush(color)) {}
	~Brush() { ::DeleteObject(h); }
	operator HBRUSH() { return h; }
};
