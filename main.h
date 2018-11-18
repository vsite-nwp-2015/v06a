#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class SizeDialog : public Dialog {
private:
	int x;
	int y;
public:
	SizeDialog(int x, int y) 
		: x(x),y(y) {}
	int GetX() const { return x; }
	int GetY() const { return y; }
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
private:
	COLORREF color;
	int x;
	int y;
public:
	MainWindow() 
		: x(0), y(0), color(RGB(0,0,125)){}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
