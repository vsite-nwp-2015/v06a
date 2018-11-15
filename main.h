#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class SizeDialog : public Dialog {
public:
	int x=0, y=0;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
	COLORREF color;
	SizeDialog dlg;
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
