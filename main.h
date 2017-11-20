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
	int x, y;
};

class MainWindow : public Window {
protected:
	void OnPaint(HDC hdc);
	void OnCommand(int id);
	void OnDestroy();

};
