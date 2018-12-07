#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class SizeDialog : public Dialog {

public:
	int x , y ;
	
public: 
	SizeDialog() {}
	
	SizeDialog(int x, int y)
{
	this->x = x;
	this->y = y;
}
protected:
	
	int IDD();
	bool OnInitDialog();
	bool OnOK();
	
};

class MainWindow : public Window {
protected:
	int brojRed=5, brojStupac=5;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	COLORREF col=RGB(0,0,255);
	
};
