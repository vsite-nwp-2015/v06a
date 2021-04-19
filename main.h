#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class size_dialog : public vsite::nwp::dialog {
public:
	int xDlg;
	int yDlg;

protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
};

class main_window : public vsite::nwp::window {
protected:
	int xWnd = 5;
	int yWnd = 5;
	COLORREF myCol = RGB(255, 255, 0);

	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
};
