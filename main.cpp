#include "main.h"
#include "rc.h"

MainWindow::MainWindow() { x = 8; y = 8; color = RGB(0, 0, 0); }

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
	HBRUSH brush = CreateSolidBrush(color);
	SelectObject(hdc, brush);
	SetMapMode(hdc, MM_ANISOTROPIC);
	RECT rekt;
	GetClientRect(*this, &rekt);
	SetViewportExtEx(hdc, rekt.right, rekt.bottom, NULL);
	SetWindowExtEx(hdc, x, y, NULL);
	for (int y1 = 0; y1 < x; ++y1){
		for (int x1 = (y1 & 1) ; x1 < y; x1+=2) {
			RECT rect = { y1, x1, y1 + 1 , x1 + 1};
			FillRect(hdc, &rect, brush);
		}
	}
	DeleteObject(brush);
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_SIZE:
		{
			SizeDialog sDlg;
			sDlg.x = x;
			sDlg.y = y;
			if (sDlg.DoModal(0, *this) == IDOK) {
				x = sDlg.x;
				y = sDlg.y;
				InvalidateRect(*this, NULL, true);
			}
		}
			break;
		case ID_COLOR:
		{
			COLORREF custCols[16] = { 0 };
			CHOOSECOLOR cc;
			ZeroMemory(&cc, sizeof cc);
			cc.lStructSize = sizeof cc;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			cc.lpCustColors = custCols;
			cc.rgbResult = color;
			if (ChooseColor(&cc))
				color = cc.rgbResult;
		}
		InvalidateRect(*this, NULL, true);
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}
//quit
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
