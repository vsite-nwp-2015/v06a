#include <windows.h>
#include <tchar.h>
#include "nwpwin.h"
#include "nwpdlg.h"

class size_dialog : public vsite::nwp::dialog {
private:
	POINT koordinate;
public:
	size_dialog(POINT tocke) :koordinate(tocke) {}
	POINT dohvati_tocke() const {
		return koordinate;
	}
protected:
	int idd() const override;
	bool on_init_dialog() override;
	bool on_ok() override;
};

class main_window : public vsite::nwp::window {
private:
	COLORREF color;
	POINT parametri;
public:
	main_window() :color(RGB(255, 0, 0)), parametri({ 20,20 }) {}
protected:
	void on_paint(HDC hdc) override;
	void on_command(int id) override;
	void on_destroy() override;
	//int brojPoSirini=20;
	//int brojPoVisini=20;
	//COLORREF color = RGB(255, 0, 0);
};

