#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class SizeDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
public:
	int x;
	int y;
};

class MainWindow : public Window {
public:	
	MainWindow() 
	{
		x = 10;
		y = 10;
		color = RGB(0, 0, 0);
	}
protected:
	int x;
	int y;
	COLORREF color;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
