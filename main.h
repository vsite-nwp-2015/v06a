#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class SizeDialog : public Dialog {
public: 
	int x, y;
protected:
	int IDD();
	bool OnInitDialog();
	bool OnOK();
};

class MainWindow : public Window {
public:
	int x, y;
	bool bTropic;
	COLORREF currentColor, customColors[16] = { 0 };
	MainWindow()
	{
		bTropic = true;
		currentColor = RGB(123, 145, 134);
		x = 5;
		y = 5;
	}
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();
};
