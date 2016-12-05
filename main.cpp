#include "main.h"
#include "resource.h"

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
	catch (XCtrl& e)
	{
		MessageBox(*this, "Upisi broj", "Not a number", MB_OK);
		return false;
	}
	return true;
}


void MainWindow::OnPaint(HDC hdc){
	RECT rc, chessR;
	HBRUSH hbrush = CreateSolidBrush(currentColor);
	GetClientRect(*this, &rc);
	SetMapMode(hdc, bTropic ? MM_ANISOTROPIC : MM_ISOTROPIC);
	SetViewportExtEx(hdc, rc.right, rc.bottom, NULL);
	SetWindowExtEx(hdc, x, y, NULL);

	for (int i = 0; i < y; ++i) {
		for (int j = i&1; j < x; j += 2) {
			chessR = {j, i, j + 1, i + 1};
			FillRect(hdc, &chessR, hbrush);
		}
	}
	DeleteBrush(hbrush);
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_SIZE:
		{
			SizeDialog sD;
			sD.x = x;
			sD.y = y;
			if (sD.DoModal(0, *this) == IDOK) {
				x = sD.x;
				y = sD.y;
				InvalidateRect(*this, NULL, true);
			}
		}
			break;
		case ID_COLOR:
		{
			CHOOSECOLOR cS;
			ZeroMemory(&cS, sizeof(cS));
			cS.lStructSize = sizeof(cS);
			cS.Flags = CC_FULLOPEN | CC_RGBINIT;
			cS.hwndOwner = *this;
			cS.lpCustColors = customColors;
			cS.rgbResult = currentColor;
			if (ChooseColor(&cS))
				currentColor = cS.rgbResult;
			InvalidateRect(*this, NULL, true);
		}
			break;
		case ID_FILE_ANISOTROPIC:
		{
			bTropic = !bTropic;
			CheckMenuItem(GetSubMenu(GetMenu(*this), 0), ID_FILE_ANISOTROPIC, bTropic ? MF_CHECKED : MF_UNCHECKED);
			InvalidateRect(*this, NULL, true);
		}
		break;
		case ID_EXIT: 
			DestroyWindow(*this); 
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
