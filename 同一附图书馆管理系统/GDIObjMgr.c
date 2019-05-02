#include<Windows.h>
#include"Global.h"

BOOL GDIObjectCreate()
{

	//hB_AC = CreateSolidBrush(APP_COLOR);
	//hB_ABC = CreateSolidBrush(APP_BK_COLOR);
	//hB_ABDC = CreateSolidBrush(APP_BKD_COLOR);


	FontForm.lfHeight = 0;
	FontForm.lfWidth = 0;
	FontForm.lfEscapement = 0;
	FontForm.lfOrientation = 0;
	FontForm.lfWeight = 0;
	FontForm.lfItalic = 0;
	FontForm.lfUnderline = 0;
	FontForm.lfStrikeOut = 0;
	FontForm.lfCharSet = DEFAULT_CHARSET;
	FontForm.lfOutPrecision = 0;
	FontForm.lfClipPrecision = 0;
	FontForm.lfPitchAndFamily = 0;
	lstrcpy(FontForm.lfFaceName, TEXT("Î¢ÈíÑÅºÚ"));

	return TRUE;
}

BOOL GDIObjectClean()
{
	/*if (hB_AC)
	{
		DeleteObject(hB_AC);
	}
	if (hB_ABC)
	{
		DeleteObject(hB_ABC);
	}
	if (hB_ABDC)
	{
		DeleteObject(hB_ABDC);
	}*/
	return TRUE;
}

