#include "main.h"
#include "rc.h"

int SizeDialog::IDD() 
{
	return IDD_SIZE;
}

bool SizeDialog::OnInitDialog() 
{
	SetInt(IDC_EDIT1, x);
	SetInt(IDC_EDIT2, y);
	return true;
}

bool SizeDialog::OnOK() 
{
	try {
		x = GetInt(IDC_EDIT1);
		y = GetInt(IDC_EDIT2);
	}
	catch (XCtrl & ex) {
		MessageBox(*this, "Unesene su krivi podaci!! ","Krivi Podaci!", MB_OK);
		MessageBox(*this, "Molim unesite brojeve", "Size", MB_OK);
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc) 
{
	RECT win;
	HBRUSH brush = CreateSolidBrush(c);
	GetClientRect(*this, &win);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, win.right, win.bottom, 0);
	SetWindowExtEx(hdc, x, y, 0);
	for (int i = 0; i < x; i++) {
		for (int j = (i & 1); j < y; j += 2) {
			RECT r = { i, j, i + 1, j + 1 };
			FillRect(hdc, &r, brush);
		}
	}

	DeleteObject(brush);
}

void MainWindow::PromjeniVelicinuEkrana(MainWindow h)
{
	SizeDialog nbr;
	nbr.x = x;
	nbr.y = y;
	if (nbr.DoModal(0, h) == IDOK) {
		x = nbr.x;
		y = nbr.y;
		InvalidateRect(h, NULL, true);

	}
}

void MainWindow::PromjeniBoju(MainWindow h)
{
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = *this;
	cc.lpCustColors = custCols;
	cc.rgbResult = c;
	if (ChooseColor(&cc)) {
		c = cc.rgbResult;
		InvalidateRect(*this, NULL, true);
	}
}

void MainWindow::OnCommand(int id) {
	switch (id) {
	case ID_SIZE:
	{
		PromjeniVelicinuEkrana(*this);
		break;
	}
	case ID_COLOR:
	{
		PromjeniBoju(*this);
		break;
	}
	case ID_EXIT:
		DestroyWindow(*this);
		break;
	}
}



void MainWindow::OnDestroy() {
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP",
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));
	return app.Run();
}
