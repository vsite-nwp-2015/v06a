#include "main.h"
#include "rc.h"

int size_dialog::idd() const {
	return IDD_SIZE;
}

bool size_dialog::on_init_dialog() {
	set_int(IDC_EDIT1, koordinate.x);
	set_int(IDC_EDIT2, koordinate.y);
	return true;
}

bool size_dialog::on_ok() {
	try {
		koordinate.x = get_int(IDC_EDIT1);
		koordinate.y = get_int(IDC_EDIT2);

	}
	catch (std::exception& e) {
		return false;

	}

	return true;
}


void main_window::on_paint(HDC hdc) {

	RECT rec;
	HBRUSH cetka = CreateSolidBrush(color);
	GetClientRect(*this, &rec);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, rec.right, rec.bottom, NULL);
	SetWindowExtEx(hdc, parametri.x, parametri.y, NULL);

	for (int i = 0; i < parametri.x; ++i) {
		for (int j = i % 2; j < parametri.y; j += 2) {
			RECT rec2 = { j, i, j + 1, i + 1 };
			//Rectangle(hdc, j, i, j + 1, i + 1);
			FillRect(hdc, &rec2, cetka);
		}
	}
	DeleteObject(cetka);
}

void OpenSizeDialog(POINT& tocke, const HWND parent) {
	size_dialog dijalog(tocke);
	if (dijalog.do_modal(0, parent) == IDOK) {
		tocke = dijalog.dohvati_tocke();
		InvalidateRect(parent, 0, true);
	}
}
COLORREF GetColor(HWND parent, COLORREF cur) {

	COLORREF custom_colors[16]{ 0 };
	CHOOSECOLOR cc{ sizeof(CHOOSECOLOR), parent, 0, cur, custom_colors, CC_FULLOPEN | CC_RGBINIT };
	if (ChooseColor(&cc))
		cur = cc.rgbResult;
	return cur;

}




void main_window::on_command(int id) {
	switch (id) {
	case ID_SIZE:
		OpenSizeDialog(parametri, *this);
		break;
	case ID_COLOR:
		color = GetColor(*this, color);
		InvalidateRect(*this, NULL, true);
		break;
	case ID_EXIT:
		DestroyWindow(*this);
		break;
	}
}

void main_window::on_destroy() {
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window wnd;
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.run();
}