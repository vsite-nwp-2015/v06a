#include "main.h"
#include "rc.h"

int x, y;
COLORREF bground;

int SizeDialog::IDD(){
	return IDD_SIZE; 
}

bool SizeDialog::OnInitDialog(){
	SetInt(IDC_EDIT1, x);
	SetInt(IDC_EDIT2, y);
	return true;
}

bool SizeDialog::OnOK(){
	try{
		x=GetInt(IDC_EDIT1);
		y=GetInt(IDC_EDIT2);
	}
	catch (XCtrl&){
		MessageBox(*this, _T("Only numbers!!"), _T("Try again"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	HBRUSH brush = CreateSolidBrush(bground);
	SetMapMode(hdc, MM_ANISOTROPIC);
	RECT rc;
	GetClientRect(*this, &rc);
	SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
	SetWindowExtEx(hdc, x, y, NULL);
	int j;
	for (int i = 0; i < x; ++i)
		for ((i%2==0? j = 1 : j = 0); j < y; j+=2){
			RECT r = { i, j, i + 1, j + 1 };
			FillRect(hdc, &r, brush);
		}
		DeleteObject(brush);
	
}

COLORREF GetColor(HWND parent, COLORREF cur){
	COLORREF custCols[16] = { 0 };
	CHOOSECOLOR cc;
	ZeroMemory(&cc, sizeof cc);
	cc.lStructSize = sizeof cc;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.hwndOwner = parent;
	cc.lpCustColors = custCols;
	cc.rgbResult = cur;
	if (ChooseColor(&cc))
		cur = cc.rgbResult;
	return cur;
}

void MainWindow::OnCommand(int id){
    
	switch(id){
	case ID_SIZE:
	{
		SizeDialog dlg;
		if (dlg.DoModal(0, *this) == IDOK){
			InvalidateRect(*this, NULL, true);
		}

		break;
	}
	case ID_COLOR:
	{
		bground = GetColor(*this, bground);
		InvalidateRect(*this, NULL, true);

		break;
		}

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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"),(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}
