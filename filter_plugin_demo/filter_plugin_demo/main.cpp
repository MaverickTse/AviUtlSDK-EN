﻿#include <Windows.h>
#include "../../filter.h" //please set this to AviUtl SDK's filter.h

// About setting multilingual UI //
/*
  The slider and button text are all fixed when you export a FILTER_DLL struct to outside.
  Once exported, you cannot change the UI text except the window title.
  Hence, we need to set individual FILTER_DLL struct for EACH language.
  It is actually copy-and-paste mostly, just need to change the slider name and checkbox/button name pointers.
  The example below gives the UI in Japanese and Traditional Chinese. If the thread's codepage is neither 932(SJIS) or 950(BIG5),
  it exports the English UI.
*/

// Define sliders
#define	TRACK_N	3 //	slider count. This creates 3 sliders
// i18n slider name
char* en_name[] = { "track0", "JP", "CHT" };
char* jp_name[] = { "ゼロ", "日本語", "中国語" };
char* cht_name[] = { "滑竿1", "日文", "中文繁體" };

int		track_default[] = { 0, 0, 0 };	//	default values
int		track_s[] = { -999, -999, -999 };	//	minimum values
int		track_e[] = { +999, +999, +999 };	//	maximum values

// Define checkboxes and buttons
#define	CHECK_N	3														//	total number of check box and button
char	*check_name_en[] = { "check0", "check1", "button1" };				//	label name
char	*check_name_jp[] = { "ハゲ", "ホゲ", "押すな！" };				//	label name:JP
char	*check_name_cht[] = { "中華民國", "中國香港", "支那" };				//	label name:CHT
int		check_default[] = { 0, 0, -1 };				//	for checkbox: 0(unchecked) or 1(checked); for button: must be -1



// Define filter info
FILTER_DLL filter_en = {               // English UI filter info
	FILTER_FLAG_EX_INFORMATION | FILTER_FLAG_PRIORITY_LOWEST,	//	filter flags, use bitwise OR to add more
	//	FILTER_FLAG_ALWAYS_ACTIVE		: フィルタを常にアクティブにします
	//	FILTER_FLAG_CONFIG_POPUP		: 設定をポップアップメニューにします
	//	FILTER_FLAG_CONFIG_CHECK		: 設定をチェックボックスメニューにします
	//	FILTER_FLAG_CONFIG_RADIO		: Only one of the checkboxes can be ticked at one time.
	//	FILTER_FLAG_EX_DATA				: 拡張データを保存出来るようにします。
	//	FILTER_FLAG_PRIORITY_HIGHEST	: Make this plugin highest priority(i.e. always run before other filters)
	//	FILTER_FLAG_PRIORITY_LOWEST		: Make this plugin lowest priority
	//	FILTER_FLAG_WINDOW_THICKFRAME	: user-draggable dialog box
	//	FILTER_FLAG_WINDOW_SIZE			: Custom dialogbox size (size defined in argument 2 and 3)
	//	FILTER_FLAG_DISP_FILTER			: 表示フィルタにします
	//	FILTER_FLAG_EX_INFORMATION		: フィルタの拡張情報を設定できるようにします
	//	FILTER_FLAG_NO_CONFIG			: 設定ウィンドウを表示しないようにします
	//	FILTER_FLAG_AUDIO_FILTER		: オーディオフィルタにします
	//	FILTER_FLAG_RADIO_BUTTON		: チェックボックスをラジオボタンにします
	//	FILTER_FLAG_WINDOW_HSCROLL		: 水平スクロールバーを持つウィンドウを作ります
	//	FILTER_FLAG_WINDOW_VSCROLL		: 垂直スクロールバーを持つウィンドウを作ります
	//	FILTER_FLAG_IMPORT				: インポートメニューを作ります
	//	FILTER_FLAG_EXPORT				: エクスポートメニューを作ります
	0, 0,						//	dialogbox size
	"Filter Demo",			//	Filter plugin name
	TRACK_N,					//	トラックバーの数 (0なら名前初期値等もNULLでよい)
	en_name,					//	slider label names in English
	track_default,				//	トラックバーの初期値郡へのポインタ
	track_s, track_e,			//	トラックバーの数値の下限上限 (NULLなら全て0～256)
	CHECK_N,					//	チェックボックスの数 (0なら名前初期値等もNULLでよい)
	check_name_en,					//	チェックボックスの名前郡へのポインタ
	check_default,				//	チェックボックスの初期値郡へのポインタ
	func_proc,					//	main filter function, use NULL to skip
	func_init,						//	initialization function, use NULL to skip
	func_exit,						//	on-exit function, use NULL to skip
	func_update,						//	invokes when when settings changed. use NULL to skip
	func_WndProc,						//	for capturing dialog's control messages. Essential if you use button or auto uncheck some checkboxes.
	NULL, NULL,					//	Reserved. Do not use.
	NULL,						//  pointer to extra data when FILTER_FLAG_EX_DATA is set
	NULL,						//  extra data size
	"Filter Demo version x.yz by MT",
	//  pointer or c-string for full filter info when FILTER_FLAG_EX_INFORMATION is set.
	func_save_start,						//	invoke just before saving starts. NULL to skip
	func_save_end,						//	invoke just after saving ends. NULL to skip
};

FILTER_DLL filter_jp = {               // Japanese UI filter info
	FILTER_FLAG_EX_INFORMATION | FILTER_FLAG_PRIORITY_LOWEST,	//	filter flags, use bitwise OR to add more
	//	FILTER_FLAG_ALWAYS_ACTIVE		: フィルタを常にアクティブにします
	//	FILTER_FLAG_CONFIG_POPUP		: 設定をポップアップメニューにします
	//	FILTER_FLAG_CONFIG_CHECK		: 設定をチェックボックスメニューにします
	//	FILTER_FLAG_CONFIG_RADIO		: Only one of the checkboxes can be ticked at one time.
	//	FILTER_FLAG_EX_DATA				: 拡張データを保存出来るようにします。
	//	FILTER_FLAG_PRIORITY_HIGHEST	: Make this plugin highest priority(i.e. always run before other filters)
	//	FILTER_FLAG_PRIORITY_LOWEST		: Make this plugin lowest priority
	//	FILTER_FLAG_WINDOW_THICKFRAME	: user-draggable dialog box
	//	FILTER_FLAG_WINDOW_SIZE			: Custom dialogbox size (size defined in argument 2 and 3)
	//	FILTER_FLAG_DISP_FILTER			: 表示フィルタにします
	//	FILTER_FLAG_EX_INFORMATION		: フィルタの拡張情報を設定できるようにします
	//	FILTER_FLAG_NO_CONFIG			: 設定ウィンドウを表示しないようにします
	//	FILTER_FLAG_AUDIO_FILTER		: オーディオフィルタにします
	//	FILTER_FLAG_RADIO_BUTTON		: チェックボックスをラジオボタンにします
	//	FILTER_FLAG_WINDOW_HSCROLL		: 水平スクロールバーを持つウィンドウを作ります
	//	FILTER_FLAG_WINDOW_VSCROLL		: 垂直スクロールバーを持つウィンドウを作ります
	//	FILTER_FLAG_IMPORT				: インポートメニューを作ります
	//	FILTER_FLAG_EXPORT				: エクスポートメニューを作ります
	0, 0,						//	dialogbox size
	"フィルター見本",			//	Filter plugin name
	TRACK_N,					//	トラックバーの数 (0なら名前初期値等もNULLでよい)
	jp_name,					//	slider label names in Japanese
	track_default,				//	トラックバーの初期値郡へのポインタ
	track_s, track_e,			//	トラックバーの数値の下限上限 (NULLなら全て0～256)
	CHECK_N,					//	チェックボックスの数 (0なら名前初期値等もNULLでよい)
	check_name_jp,					//	チェックボックスの名前郡へのポインタ
	check_default,				//	チェックボックスの初期値郡へのポインタ
	func_proc,					//	main filter function, use NULL to skip
	func_init,						//	initialization function, use NULL to skip
	func_exit,						//	on-exit function, use NULL to skip
	func_update,						//	invokes when when settings changed. use NULL to skip
	func_WndProc,						//	for capturing dialog's control messages. Essential if you use button or auto uncheck some checkboxes.
	NULL, NULL,					//	Reserved. Do not use.
	NULL,						//  pointer to extra data when FILTER_FLAG_EX_DATA is set
	NULL,						//  extra data size
	"フィルター見本 version x.yz by MT",
	//  pointer or c-string for full filter info when FILTER_FLAG_EX_INFORMATION is set.
	func_save_start,						//	invoke just before saving starts. NULL to skip
	func_save_end,						//	invoke just after saving ends. NULL to skip
};


FILTER_DLL filter_cht = {               // Chinese Traditional UI filter info
	FILTER_FLAG_EX_INFORMATION | FILTER_FLAG_PRIORITY_LOWEST,	//	filter flags, use bitwise OR to add more
	//	FILTER_FLAG_ALWAYS_ACTIVE		: フィルタを常にアクティブにします
	//	FILTER_FLAG_CONFIG_POPUP		: 設定をポップアップメニューにします
	//	FILTER_FLAG_CONFIG_CHECK		: 設定をチェックボックスメニューにします
	//	FILTER_FLAG_CONFIG_RADIO		: Only one of the checkboxes can be ticked at one time.
	//	FILTER_FLAG_EX_DATA				: 拡張データを保存出来るようにします。
	//	FILTER_FLAG_PRIORITY_HIGHEST	: Make this plugin highest priority(i.e. always run before other filters)
	//	FILTER_FLAG_PRIORITY_LOWEST		: Make this plugin lowest priority
	//	FILTER_FLAG_WINDOW_THICKFRAME	: user-draggable dialog box
	//	FILTER_FLAG_WINDOW_SIZE			: Custom dialogbox size (size defined in argument 2 and 3)
	//	FILTER_FLAG_DISP_FILTER			: 表示フィルタにします
	//	FILTER_FLAG_EX_INFORMATION		: フィルタの拡張情報を設定できるようにします
	//	FILTER_FLAG_NO_CONFIG			: 設定ウィンドウを表示しないようにします
	//	FILTER_FLAG_AUDIO_FILTER		: オーディオフィルタにします
	//	FILTER_FLAG_RADIO_BUTTON		: チェックボックスをラジオボタンにします
	//	FILTER_FLAG_WINDOW_HSCROLL		: 水平スクロールバーを持つウィンドウを作ります
	//	FILTER_FLAG_WINDOW_VSCROLL		: 垂直スクロールバーを持つウィンドウを作ります
	//	FILTER_FLAG_IMPORT				: インポートメニューを作ります
	//	FILTER_FLAG_EXPORT				: エクスポートメニューを作ります
	0, 0,						//	dialogbox size
	"濾鏡示範",			//	Filter plugin name
	TRACK_N,					//	トラックバーの数 (0なら名前初期値等もNULLでよい)
	cht_name,					//	slider label names in Japanese
	track_default,				//	トラックバーの初期値郡へのポインタ
	track_s, track_e,			//	トラックバーの数値の下限上限 (NULLなら全て0～256)
	CHECK_N,					//	チェックボックスの数 (0なら名前初期値等もNULLでよい)
	check_name_cht,					//	チェックボックスの名前郡へのポインタ
	check_default,				//	チェックボックスの初期値郡へのポインタ
	func_proc,					//	main filter function, use NULL to skip
	func_init,						//	initialization function, use NULL to skip
	func_exit,						//	on-exit function, use NULL to skip
	func_update,						//	invokes when when settings changed. use NULL to skip
	func_WndProc,						//	for capturing dialog's control messages. Essential if you use button or auto uncheck some checkboxes.
	NULL, NULL,					//	Reserved. Do not use.
	NULL,						//  pointer to extra data when FILTER_FLAG_EX_DATA is set
	NULL,						//  extra data size
	"濾鏡示範 version x.yz by MT",
	//  pointer or c-string for full filter info when FILTER_FLAG_EX_INFORMATION is set.
	func_save_start,						//	invoke just before saving starts. NULL to skip
	func_save_end,						//	invoke just after saving ends. NULL to skip
};


// Export the above filter table
EXTERN_C  __declspec(dllexport) FILTER_DLL*  GetFilterTable(void)
{
	FILTER_DLL* UITable = nullptr;
	LPCPINFOEX cpinfo = new CPINFOEX{ 0 };
	if (GetCPInfoEx(CP_THREAD_ACP, 0, cpinfo)) // try to get AviUtl's current codepage
	{
		if (cpinfo->CodePage == 932) // 932 is Japanese S-JIS; 950 is BIG5 Chinese
		{
			UITable = &filter_jp;
		}
		else if (cpinfo->CodePage == 950)
		{
			UITable = &filter_cht;
		}
		else // default to English to avoid scrambled text
		{
			UITable = &filter_en;
		}
	}
	else // if something wrong with CP retrival, use English UI
	{
		UITable = &filter_en;
	}
	delete cpinfo;

	return UITable;
}

/**************************************************************************************/
/* IMPORTANT NOTE */
/* The original SDK sample code use the following:

EXTERN_C FILTER_DLL __declspec(dllexport) * __stdcall GetFilterTable( void )
{
return &filter;
}

but MSVC seems to have problem parsing this and you will need an extra .def file
for proper export.
If the FILTER_DLL struct fails to export, the plugin will not show up in AviUtl's
"Filter+" menu.
*/
/**************************************************************************************/

BOOL func_proc(FILTER *fp, FILTER_PROC_INFO *fpip) // This is the main image manipulation function
{
	//TODO
	MessageBoxExW(NULL, L"func_proc invoked!", L"DEMO", MB_OK | MB_ICONINFORMATION, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK));
	// image data at: fpip->ycp_edit
	// scratch area, same size as ycp_edit, at: fpip->ycp_temp
	// max image dimension (depends on AviUtl setting): fpip->max_w fpip->max_h [READ-ONLY]
	// View port(output) dimension (changeable): fpip->w, fpip->h 
	// a long list of utility function can be accessed under fp->exfunc->
	// default pixel format in ycp_edit is PIXEL_YC (see filter.h for details)
	// The idea of "stride" or "step" is not used when accessing ycp_edit data.
	// ycp_edit is a continous arrangement of pixels with a maximum of fpip->max_w*fpip->max_h pixels
	// size of ycp_edit and ycp_temp is therefore fpip->max_w*fpip->max_h*sizeof(PIXEL_YC)

	// The principle idea is to make change on fpip->ycp_edit, then return TRUE when done.

	return TRUE; //TRUE to update frame image. FALSE to skip refresh.
}
BOOL func_init(FILTER *fp)
{
	//TODO
	MessageBoxExW(NULL, L"func_init invoked!\nfunc_initを呼び出した！", L"DEMO", MB_OK | MB_ICONINFORMATION, MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN));

	return TRUE;
}
BOOL func_exit(FILTER *fp)
{
	//DO NOT PUT MessageBox here, crash the application!
	//MessageBox(NULL, "func_exit invoked!", "DEMO", MB_OK | MB_ICONINFORMATION);
	return TRUE;
}
BOOL func_update(FILTER *fp, int status)
{
	//TODO
	switch (status)
	{
	case FILTER_UPDATE_STATUS_TRACK:
		MessageBox(NULL, "func_update FILTER_UPDATE_STATUS_TRACK", "DEMO", MB_OK | MB_ICONINFORMATION);
		break;
	case FILTER_UPDATE_STATUS_TRACK+1:
		MessageBox(NULL, "func_update FILTER_UPDATE_STATUS_TRACK+1", "DEMO", MB_OK | MB_ICONINFORMATION);
		break;
	case FILTER_UPDATE_STATUS_TRACK+2:
		MessageBox(NULL, "func_update FILTER_UPDATE_STATUS_TRACK+2", "DEMO", MB_OK | MB_ICONINFORMATION);
		break;
	case FILTER_UPDATE_STATUS_CHECK:
		MessageBox(NULL, "func_update FILTER_UPDATE_STATUS_CHECK", "DEMO", MB_OK | MB_ICONINFORMATION);
		break;
	case FILTER_UPDATE_STATUS_CHECK+1:
		MessageBox(NULL, "func_update FILTER_UPDATE_STATUS_CHECK+1", "DEMO", MB_OK | MB_ICONINFORMATION);
		break;
	case FILTER_UPDATE_STATUS_CHECK+2: // no effect since our 3rd checkbox is a button.
		MessageBox(NULL, "func_update FILTER_UPDATE_STATUS_CHECK+2", "DEMO", MB_OK | MB_ICONINFORMATION);
		break;
	default:
		MessageBox(NULL, "func_update invoked!", "DEMO", MB_OK | MB_ICONINFORMATION);
	}
	
	return FALSE;
}
BOOL func_WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, void *editp, FILTER *fp)
// This is used for capturing mouse click, button states, and getting mouse coordinates
{
	//
	switch (message)
	{
	case WM_FILTER_MAIN_MOUSE_DOWN:
		break;
	case WM_FILTER_MAIN_MOUSE_MOVE:
		break;
	case WM_COMMAND: // This is for capturing dialog control's message, i.e. button-click
		switch (wparam)
		{
		case MID_FILTER_BUTTON+2: // This ID is the COMBINED order of checkbox and button.
			// so MID_FILTER_BUTTON = checkbox1
			// MID_FILTER_BUTTON+1 = checkbox2
			// MID_FILTER_BUTTON+2 = button1
			// but since the checkboxes are not buttons, the first two MID_FILTER_BUTTON have no effect.
			MessageBoxExW(NULL, L"This should show some Chinese text\n你好嗎?", L"BUTTON-CLICK", MB_OK | MB_ICONINFORMATION, MAKELANGID(LANG_CHINESE_TRADITIONAL, SUBLANG_CHINESE_HONGKONG));
			break;
		default:
			return FALSE;

		}
	}
	return FALSE;
}
BOOL func_save_start(FILTER *fp, int s, int e, void *editp)
{
	//
	MessageBox(NULL, "func_save_start invoked!", "DEMO", MB_OK | MB_ICONINFORMATION);
	return FALSE;
}
BOOL func_save_end(FILTER *fp, void *editp)
{
	//
	MessageBox(NULL, "func_save_end invoked!", "DEMO", MB_OK | MB_ICONINFORMATION);
	return FALSE;
}