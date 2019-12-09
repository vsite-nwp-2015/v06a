#include "main.h"
#include "rc.h"

int SizeDialog::IDD(){
	return IDD_SIZE; 
}

bool SizeDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, x);
	SetInt(IDC_EDIT2, y);
	return true;
}

bool SizeDialog::OnOK(){

	x = GetInt(IDC_EDIT1);
	y = GetInt(IDC_EDIT2);
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	RECT rect;
	HBRUSH brush = CreateSolidBrush(c);
	GetClientRect(*this, &rect);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, rect.right, rect.bottom, 0);
	SetWindowExtEx(hdc, x, y, 0);
	for (int i = 0; i < x; i++) {
		for (int j = (i&1); j < y; j += 2) {
			RECT rc = { i, j, i + 1, j + 1 };
			FillRect(hdc, &rc, brush);
		}
	}
	DeleteObject(brush);
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_SIZE:
			ChangeRectSize();
			break;
		case ID_COLOR:
			ChangeRectColor();
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void MainWindow::ChangeRectSize() {
	SizeDialog sd;
	sd.x = x;
	sd.y = y;
	if (sd.DoModal(0, *this) == IDOK) {
		x = sd.x;
		y = sd.y;
		InvalidateRect(*this, NULL, true);
	}
}

void MainWindow::ChangeRectColor() {
	COLORREF cr[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = *this;
	cc.lpCustColors = cr;
	cc.rgbResult = c;
	if (ChooseColor(&cc)) {
		c = cc.rgbResult;
		InvalidateRect(*this, NULL, true);
	}
}

void MainWindow::OnDestroy(){
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
