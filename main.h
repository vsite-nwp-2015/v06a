#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class SizeDialog : public Dialog {
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
protected:
	COLORREF color;
	int x; 
	int y;
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
public:
	MainWindow();
};
