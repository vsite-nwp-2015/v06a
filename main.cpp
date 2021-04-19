#include "main.h"
#include "rc.h"

int size_dialog::idd() const {
	return IDD_SIZE; 
}

bool size_dialog::on_init_dialog(){
	set_int(IDC_EDIT1, xDlg);
	set_int(IDC_EDIT2, yDlg);
	return true;
}

bool size_dialog::on_ok(){
	xDlg = get_int(IDC_EDIT1);
	yDlg = get_int(IDC_EDIT2);
	return true;
}


void main_window::on_paint(HDC hdc){
	RECT rect;
	HBRUSH brush = CreateSolidBrush(myCol);

	SetMapMode(hdc, MM_ANISOTROPIC);
	GetClientRect(*this, &rect);
	SetViewportExtEx(hdc, rect.right, rect.bottom, NULL);
	SetWindowExtEx(hdc, xWnd, yWnd, NULL);

	for (int i = 0; i < xWnd; i++) {
		for (int j = (i & 1); j < yWnd; j += 2) {
			RECT rect = { i, j, i + 1, j + 1 };
			FillRect(hdc, &rect, brush);
		}

	}
	DeleteObject(brush);
}

void main_window::on_command(int id){
	switch(id){
		case ID_SIZE:
		{
			size_dialog sizeDlg;

			sizeDlg.xDlg = xWnd;
			sizeDlg.yDlg = yWnd;

			if (sizeDlg.do_modal(NULL, *this) == IDOK) {
				xWnd = sizeDlg.xDlg;
				yWnd = sizeDlg.yDlg;
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
			cc.rgbResult = myCol;
			cc.hwndOwner = *this;
			if (ChooseColor(&cc))
			{
				myCol = cc.rgbResult;
				InvalidateRect(*this, NULL, true);
			}
		}
			break;

		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void main_window::on_destroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	vsite::nwp::application app;
	main_window wnd;	
	wnd.create(0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, _T("NWP"), (int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)), CW_USEDEFAULT, CW_USEDEFAULT, 500, 500);
	return app.run();
}
