#include "main.h"
#include "rc.h"
COLORREF color = RGB(0, 0, 0);

int x = 10;
int y = 10;
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
	RECT rc;
	HBRUSH brush = CreateSolidBrush(color);
	GetClientRect(*this, &rc);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, rc.right, rc.bottom, 0);
	SetWindowExtEx(hdc, x,y, 0);
	for (int i = 0; i< x; i++) {
		for (int j = (i&1); j < y; j+=2) {
			RECT r = { i, j, i + 1, j + 1 };
			FillRect(hdc, &r, brush);
		}
		
 }
//	InvalidateRect(*this, NULL, true);
}


void MainWindow::OnCommand(int id){
	switch(id){
	case ID_SIZE: {
		SizeDialog size;
		size.x = x;
		size.y = y;
		if (size.DoModal(0, *this) == IDOK) {
			x = size.x;
			y = size.y;
			InvalidateRect(*this, NULL, true);
			
		}
		break;
	}
	case ID_COLOR: {
			COLORREF custCols[16] = { 0 };
			CHOOSECOLOR cc;
			ZeroMemory(&cc, sizeof cc);
			cc.lStructSize = sizeof cc;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			cc.hwndOwner = *this;
			cc.lpCustColors = custCols;
			cc.rgbResult = color;
			if (ChooseColor(&cc)) {
				color = cc.rgbResult;
				InvalidateRect(*this, NULL, true);
			}
		}
		   
		  break;
	
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
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
