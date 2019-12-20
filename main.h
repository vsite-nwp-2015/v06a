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
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
	void PromjeniVelicinuEkrana();
	void PromjeniBoju();
public:
	COLORREF c = RGB(240, 40, 240);
	int x = 10;
	int y = 10;

};
