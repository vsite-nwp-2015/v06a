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
	try {
		x = GetInt(IDC_EDIT1);
		y = GetInt(IDC_EDIT2);
	}
	catch (XCtrl&) {
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	HBRUSH br = CreateSolidBrush(boja);
	RECT upplf;
	GetClientRect(*this, &upplf);
	SetMapMode(hdc, MM_ANISOTROPIC);
	SetViewportExtEx(hdc, upplf.right, upplf.bottom, 0);
	SetWindowExtEx(hdc, x, y, 0);
	int i = 0;
	while (i < x) {
		int j = i & 1;
		while (j < y) {
			RECT r = { i, j, i + 1, j + 1 };
			FillRect(hdc, &r, br);
			j += 2;
		}
		++i;
	}
	DeleteObject(br);
	
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_SIZE:
		{
			SizeDialog velicina;
			velicina.x = x;
			velicina.y = y;
			if (velicina.DoModal(0, *this) == IDOK) {
				x = velicina.x;
				y = velicina.y;
				InvalidateRect(*this, NULL, true);
			}
			break;
		}
		case ID_COLOR:
		{	COLORREF boja2[100] = { 0 };
			CHOOSECOLOR odabir_boje;
			ZeroMemory(&odabir_boje, sizeof odabir_boje);
			odabir_boje.rgbResult = boja;
			odabir_boje.lpCustColors = boja2;
			odabir_boje.hwndOwner = *this;
			odabir_boje.lStructSize = sizeof odabir_boje;
			odabir_boje.Flags = CC_FULLOPEN | CC_RGBINIT;
			
			if (ChooseColor(&odabir_boje)) {
				boja = odabir_boje.rgbResult;
				InvalidateRect(*this, NULL, true);
			}
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
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}
