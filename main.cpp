#include "main.h"
#include "rc.h"


int SizeDialog::IDD(){
	return IDD_SIZE; 
}

bool SizeDialog::OnInitDialog(){

	return true;
}

bool SizeDialog::OnOK(){
	return true;
}

MainWindow::MainWindow() { x = 25; y = 25; color = RGB(0, 0, 0); }

void MainWindow::OnPaint(HDC hdc){
	HBRUSH brush = CreateSolidBrush(color);
	SetMapMode(hdc, MM_ANISOTROPIC);
	RECT rekt;
	GetClientRect(*this, &rekt);
	SetViewportExtEx(hdc, rekt.right, rekt.bottom, NULL);
	SetWindowExtEx(hdc, x, y, NULL);
	for (int x1 = 0; x1 < x; ++x1){
		for (int y1 = 0 ; y1 < y; y1+=2) {
			RECT rect = { x1, y1, x1 + 1 , y1 + 1};
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
