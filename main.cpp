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
		
		if (x <= 0 || y <= 0) throw("Unesite pozitivan broj");
		return true;
	}
	catch (char* str)
	{
		
		SendDlgItemMessage(*this, IDC_EDIT1, EM_SETSEL, 0, -1);
		SetFocus(GetDlgItem(*this, IDC_EDIT1));
		MessageBox(*this, str, "upozorenje", MB_OK| MB_ICONEXCLAMATION);
		
	}
	catch (XCtrl&) {
		SendDlgItemMessage(*this, IDC_EDIT1, EM_SETSEL, 0, -1);
		SetFocus(GetDlgItem(*this, IDC_EDIT1));
		MessageBox(*this, "Nije broj \n"  "Unesite broj", "upozorenje",MB_OK| MB_ICONEXCLAMATION);
	}
	return false;
	
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
	if (ChooseColor(&cc)) {
		
		cur = cc.rgbResult;
		
	}
	InvalidateRect(parent, NULL, true);
	return cur;
}

void MainWindow::OnPaint(HDC hdc) {
	
	RECT rec;
	
	HBRUSH hbrush = CreateSolidBrush(col);
	HGDIOBJ obj=SelectObject(hdc,hbrush);
		   	
	GetClientRect(*this, &rec);
		
		double sirina = static_cast<double>( rec.right)/brojStupac;
		double visina =  static_cast<double>(rec.bottom)/brojRed;
		
		for (int i = 0; i <= brojRed; ++i) {
			for (int j = i%2; j <= brojStupac; j+=2) {
		
				rec.left = sirina * (j - 1);
				rec.top = visina * i;
 				rec.right = sirina * j;
				rec.bottom = visina * (i + 1);
				
				FillRect(hdc, &rec, hbrush);
				
			}
	}
		SelectObject(hdc, obj);
		DeleteObject(hbrush);
}


void MainWindow::OnCommand(int id){
	
	SizeDialog size;
	switch(id){
		
		case ID_SIZE:
			size.x = brojRed;
			size.y = brojStupac;
				if (size.DoModal(0, *this) == IDOK) {
					brojRed = size.x;
					brojStupac = size.y;
				}
						
			InvalidateRect(*this, 0, true);
			break;
		
		case ID_COLOR:
			col = GetColor(*this, col);
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
