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

MainWindow::MainWindow() { x = 256; y = 256; }

void MainWindow::OnPaint(HDC hdc){
	for (int x1 = 0; x1 < x; x1++){
		for (int y1 = 0; y1 < y; y1++)

	}
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
			COLORREF myCol = RGB(255, 0, 0);
			COLORREF custCols[16] = { 0 };
			CHOOSECOLOR cc;
			ZeroMemory(&cc, sizeof cc);
			cc.lStructSize = sizeof cc;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;
			cc.lpCustColors = custCols;
			cc.rgbResult = myCol;
			if (ChooseColor(&cc))
				myCol = cc.rgbResult;
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
