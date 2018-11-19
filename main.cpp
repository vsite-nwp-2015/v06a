#include "main.h"
#include "rc.h"

int SizeDialog::IDD(){
	return IDD_SIZE; 
}

bool SizeDialog::OnInitDialog(){
	SetInt(IDC_EDIT1,paramsXY.x);
	SetInt(IDC_EDIT2,paramsXY.y);
	return true;
}

bool SizeDialog::OnOK(){
	try {
		paramsXY.x = GetInt(IDC_EDIT1);
		paramsXY.y = GetInt(IDC_EDIT2);
		if (paramsXY.x < 0 || paramsXY.y < 0) {
			MessageBox(*this, "The value must be greater than zero!", "Size", MB_OK);
			return false;
		}
	} catch (XCtrl&) {
		MessageBox(*this, "Wrong entry!", "Size", MB_OK);
		return false;
	}
	return true;
}

RECT CreateRect(int i, int j) {
	return { i, j, i + 1, j + 1 };
}

void MainWindow::OnPaint(HDC hdc){
	HBRUSH brush = CreateSolidBrush(color);
	RECT rc;
	GetClientRect(*this, &rc);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
	SetWindowExtEx(hdc, params.x, params.y, NULL);
	
	for (int i = 0; i < params.x; ++i) {
		for (int j = (i & 1); j < params.y; j += 2) {
			FillRect(hdc, &CreateRect(i, j), brush);
		}
	}

	DeleteObject(brush);
}

COLORREF GetColor(HWND parent, COLORREF cur) {
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

POINT GetParameters(const SizeDialog& sizeDialog) {
	return sizeDialog.GetParamsXY();
}

void OpenSizeDialog(POINT& params, const HWND parent) {
	SizeDialog sizeDialog(params);
	if (sizeDialog.DoModal(0, parent) == IDOK) {
		params = GetParameters(sizeDialog);
		InvalidateRect(parent, 0, true);
	}
}

void MainWindow::OnCommand(int id){
	switch(id){
	case ID_SIZE:
		OpenSizeDialog(params, *this);
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
