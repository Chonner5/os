/*********************************************************************
 *                                                                    *
 *                SEGGER Microcontroller GmbH & Co. KG                *
 *        Solutions for real time microcontroller applications        *
 *                                                                    *
 **********************************************************************
 *                                                                    *
 * C-file generated by:                                               *
 *                                                                    *
 *        GUI_Builder for emWin version 5.28                          *
 *        Compiled Jan 30 2015, 16:41:06                              *
 *        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
 *                                                                    *
 **********************************************************************
 *                                                                    *
 *        Internet: www.segger.com  Support: support@segger.com       *
 *                                                                    *
 **********************************************************************
 */

// USER START (Optionally insert additional includes)
#include <stdlib.h>
#include <string.h>
//#include <math.h>
#include <adc.h>
#include "DIALOG.h"
#include "GRAPH.h"
#include "malloc.h"
#include "touch.h"

#include "graphyt.h"
#include "setting.h"
#include "all_value.h"
#include "timer.h"
//
// Recommended memory to run the sample with adequate performance
//
#define RECOMMENDED_MEMORY (1024L * 20)
// USER END

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */

// USER START (Optionally insert additional static data)

static GUI_CONST_STORAGE GUI_LOGPALETTE Pal = {
	2, // number of entries
	1, // Has transparency
	&Colors[0]};

static GUI_CONST_STORAGE unsigned char acEnlarge[] = {
	_______X, X_______,
	______XX, XX______,
	_____XXX, XXX_____,
	_______X, X_______,
	__X____X, X____X__,
	_XX_____, _____XX_,
	XXXXX___, ___XXXXX,
	XXXXX___, ___XXXXX,
	_XX_____, _____XX_,
	__X____X, X____X__,
	_______X, X_______,
	_____XXX, XXX_____,
	______XX, XX______,
	_______X, X_______};

static GUI_CONST_STORAGE unsigned char acShrink[] = {
	_______X, X_______,
	_______X, X_______,
	_____XXX, XXX_____,
	______XX, XX______,
	__X____X, X____X__,
	__XX____, ____XX__,
	XXXXX___, ___XXXXX,
	XXXXX___, ___XXXXX,
	__XX____, ____XX__,
	__X____X, X____X__,
	______XX, XX______,
	_____XXX, XXX_____,
	_______X, X_______,
	_______X, X_______};

static GUI_CONST_STORAGE GUI_BITMAP _bmEnlarge = {
	16,		   // XSize
	14,		   // YSize
	2,		   // BytesPerLine
	1,		   // BitsPerPixel
	acEnlarge, // Pointer to picture data (indices)
	&Pal	   // Pointer to palette
};

static GUI_CONST_STORAGE GUI_BITMAP _bmShrink = {
	16,		  // XSize
	14,		  // YSize
	2,		  // BytesPerLine
	1,		  // BitsPerPixel
	acShrink, // Pointer to picture data (indices)
	&Pal	  // Pointer to palette
};

// USER END

/*********************************************************************
 *
 *       _aDialogCreate
 */
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{FRAMEWIN_CreateIndirect, "Oscilloscope", 0, 0, 0, 400, 272, FRAMEWIN_CF_ACTIVE},
	{GRAPH_CreateIndirect, 0, GUI_ID_GRAPH0, 0, 0, 400, 200},	 //
	{TEXT_CreateIndirect, "Spacing X:", 0, 5, 210, 50, 20},		 //
	{TEXT_CreateIndirect, "Spacing Y:", 0, 5, 230, 50, 20},		 //
	{SLIDER_CreateIndirect, 0, GUI_ID_SLIDER0, 55, 210, 60, 16}, //
	{SLIDER_CreateIndirect, 0, GUI_ID_SLIDER1, 55, 230, 60, 16}, //
	// {CHECKBOX_CreateIndirect, 0, GUI_ID_CHECK5, 180, 210, 50, 0},  //
	// {CHECKBOX_CreateIndirect, 0, GUI_ID_CHECK6, 180, 230, 50, 0},  //
	// {CHECKBOX_CreateIndirect, 0, GUI_ID_CHECK2, 290, 210, 50, 0},  //
	// {CHECKBOX_CreateIndirect, 0, GUI_ID_CHECK3, 230, 210, 50, 0},  //
	// {CHECKBOX_CreateIndirect, 0, GUI_ID_CHECK4, 230, 230, 50, 0},  //
	{BUTTON_CreateIndirect, "", GUI_ID_BUTTON0, 355, 230, 36, 18}, //全屏按钮405
	//{CHECKBOX_CreateIndirect, 0, GUI_ID_CHECK1, 290, 230, 40, 0},  // 405
	
	{BUTTON_CreateIndirect, "| ->", GUI_ID_BUTTON2, 170, 220, 36, 18},
	{BUTTON_CreateIndirect, "<- |", GUI_ID_BUTTON3, 125, 220, 36, 18},
	{BUTTON_CreateIndirect, "-- Up", GUI_ID_BUTTON4, 220, 205, 40, 18},
	{BUTTON_CreateIndirect, "-- Dn", GUI_ID_BUTTON5, 220, 230, 40, 18},

};

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

// USER START (Optionally insert additional static code)

void test_line_X_init(void)
{

	//竖线A的值
	test_lineplace[0][0].x = Xline_A_palce;
	test_lineplace[0][0].y = 2;
	test_lineplace[0][1].x = Xline_A_palce;
	test_lineplace[0][1].y = 300;

	//竖线B的值
	test_lineplace[1][0].x = Xline_B_palce;
	test_lineplace[1][0].y = 2;
	test_lineplace[1][1].x = Xline_B_palce;
	test_lineplace[1][1].y = 300;
	peroid_test = (Xline_B_palce - Xline_A_palce) * (1000000 / mysample_time[dropdown_flag]) / X_step;
}


void test_line_Y_init(void)
{

	//竖线A的值
	test_Y_lineplace[0][0].x = 1;
	test_Y_lineplace[0][0].y = Yline_A_palce;
	test_Y_lineplace[0][1].x =350;
	test_Y_lineplace[0][1].y =  Yline_A_palce;

	//竖线B的值
	test_Y_lineplace[1][0].x = 1;
	test_Y_lineplace[1][0].y = Yline_B_palce;
	test_Y_lineplace[1][1].x =350;
	test_Y_lineplace[1][1].y =  Yline_B_palce;
	voltage_test=(Yline_B_palce-Yline_A_palce)*(15+Y_step);
}

// USER END
static void _InitPoints(int NumPoints)
{
	int i;
	int t;
	Close_ADC(); //数据储存时必须关掉ADC
	_NumPoints = NumPoints;

	for (i = 0; i <= NumPoints - 1; i++)
	{
		_aPoint[0][i].x = (int)(i * X_step);
		t=(int)((float)(ADC_ConvertedValue[i] * 3300 / 4095));
		_aPoint[0][i].y = t/(15 + Y_step) + 20; //数据传输处  这里的15+Y_step是缩小倍数 +20是上移动20


		if (i == 0)
		{
			signal_max = (int)(float)(ADC_ConvertedValue[i] * 3300 / 4095);
		}

		//提取最大值
		if (i > 0 && (signal_max < (int)(float)(ADC_ConvertedValue[i] * 3300 / 4095))) //不能加等于如果加等于号会在信号最后一个最大值
		{
			signal_max = (int)(float)(ADC_ConvertedValue[i] * 3300 / 4095);

			//下面是同步触发的可以不要
			if (signal_max > (int)(float)(ADC_ConvertedValue[i - 1] * 3300 / 4095))
			{
				start_x = i;
			}
		}
		// _aPoint[0][i].x = (int)(100 - r * cos(Rad));
		// _aPoint[0][i].y = (int)(100 + r * sin(Rad) * Deg / 360);
		// _aPoint[1][i].x = (int)(i*3);
		// _aPoint[1][i].y = (int)(100);
		// _aPoint[2][i].x = (int)(i*2);
		// _aPoint[2][i].y = (int)(50);
		// if(i==NumPoints- 1){
		//   Open_ADC();
		// }
	}
}

static int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO *pDrawItemInfo)
{
	switch (pDrawItemInfo->Cmd)
	{
	case WIDGET_ITEM_DRAW:
		GUI_DrawRect(pDrawItemInfo->x0 - 3, pDrawItemInfo->y0 - 3, pDrawItemInfo->x0 + 3, pDrawItemInfo->y0 + 3);
		break;
	}
	return 0;
}

static void _UserDraw(WM_HWIN hWin, int Stage)
{
	if (Stage == GRAPH_DRAW_LAST)
	{
		char acText[] = "mv";
		GUI_RECT Rect;
		GUI_RECT RectInvalid;
		int FontSizeY;

		GUI_SetFont(&GUI_Font13_ASCII);
		FontSizeY = GUI_GetFontSizeY();
		WM_GetInsideRect(&Rect);
		WM_GetInvalidRect(hWin, &RectInvalid);
		Rect.x1 = Rect.x0 + FontSizeY;
		GUI_SetColor(GUI_RED);
		GUI_DispStringInRectEx(acText, &Rect, GUI_TA_HCENTER, strlen(acText), GUI_ROTATE_CCW);
	}
}

static void _ForEach(WM_HWIN hWin, void *pData)
{
	int Id;
	int FullScreenMode;

	FullScreenMode = *(int *)pData;
	Id = WM_GetId(hWin);
	if ((Id == GUI_ID_GRAPH0) || (Id == GUI_ID_BUTTON0) || (Id == GUI_ID_VSCROLL) || (Id == GUI_ID_HSCROLL))
	{
		return;
	}
	if (FullScreenMode)
	{
		WM_HideWindow(hWin);
	}
	else
	{
		WM_ShowWindow(hWin);
	}
}

static void _ToggleFullScreenMode(WM_HWIN hDlg)
{
	static int FullScreenMode;
	static GUI_RECT Rect;
	static unsigned ScalePos;
	WM_HWIN hGraph;
	WM_HWIN hButton;

	hGraph = WM_GetDialogItem(hDlg, GUI_ID_GRAPH0);
	hButton = WM_GetDialogItem(hDlg, GUI_ID_BUTTON0);
	FullScreenMode ^= 1;
	if (FullScreenMode)
	{
		//
		// Enter the full screen mode
		//
		WM_HWIN hClient;
		GUI_RECT RectInside;

		hClient = WM_GetClientWindow(hDlg);
		BUTTON_SetBitmapEx(hButton, BUTTON_BI_PRESSED, &_bmShrink, 10, 2);
		BUTTON_SetBitmapEx(hButton, BUTTON_BI_UNPRESSED, &_bmShrink, 10, 2);
		WM_MoveWindow(hButton, 0, 11);
		FRAMEWIN_SetTitleVis(hDlg, 0);
		WM_GetInsideRectEx(hClient, &RectInside);
		WM_GetWindowRectEx(hGraph, &Rect);
		WM_ForEachDesc(hClient, _ForEach, &FullScreenMode); // Hide all descendants
		WM_SetWindowPos(hGraph, WM_GetWindowOrgX(hClient), WM_GetWindowOrgX(hClient), RectInside.x1, RectInside.y1);
		ScalePos = GRAPH_SCALE_SetPos(_hScaleH, RectInside.y1 - 105);
	}
	else
	{
		//
		// Return to normal mode
		//
		BUTTON_SetBitmapEx(hButton, BUTTON_BI_PRESSED, &_bmEnlarge, 10, 2);
		BUTTON_SetBitmapEx(hButton, BUTTON_BI_UNPRESSED, &_bmEnlarge, 10, 2);
		WM_MoveWindow(hButton, 0, -11);
		WM_ForEachDesc(WM_GetClientWindow(hDlg), _ForEach, &FullScreenMode); // Show all descendants
		WM_SetWindowPos(hGraph, Rect.x0, Rect.y0, Rect.x1 - Rect.x0 + 1, Rect.y1 - Rect.y0 + 1);
		FRAMEWIN_SetTitleVis(hDlg, 1);
		GRAPH_SCALE_SetPos(_hScaleH, ScalePos);
	}
}
/*********************************************************************
 *
 *       _cbDialog
 */
static void _cbDialog(WM_MESSAGE *pMsg)
{
	int NCode;
	int Id;
	// int Value;
	int i;

	// int     j;
	WM_HWIN hDlg;
	WM_HWIN hItem;

	hDlg = pMsg->hWin;
	switch (pMsg->MsgId)
	{
	// case WM_PAINT:
	case WM_INIT_DIALOG:
		hItem = WM_GetDialogItem(hDlg, GUI_ID_GRAPH0);
		//GRAPH_SetAutoScrollbar(hItem,30,1);
		_InitPoints(300);

		test_line_X_init();
		test_line_Y_init();
		//
		// Add graphs  A线
		//
		//测量线，这里的思路是添加一个数据，这个数据是自己加的，只有两个坐标刚好是一条直线
		test_line[0] = GRAPH_DATA_XY_Create(GUI_BLUE, 2, test_lineplace[0], 2);
		GRAPH_DATA_XY_SetPenSize(test_line[0], 3);
		GRAPH_AttachData(hItem, test_line[0]);
		//X  B线
		test_line[1] = GRAPH_DATA_XY_Create(GUI_BLUE, 2, test_lineplace[1], 2);
		GRAPH_DATA_XY_SetPenSize(test_line[1], 3);
		GRAPH_AttachData(hItem, test_line[1]);


		//Y	 A线
		test_Y_line[0] = GRAPH_DATA_XY_Create(GUI_BLUE, 2, test_Y_lineplace[0], 2);
		GRAPH_DATA_XY_SetPenSize(test_Y_line[0], 3);
		GRAPH_AttachData(hItem, test_Y_line[0]);
		//Y  B线
		test_Y_line[1] = GRAPH_DATA_XY_Create(GUI_BLUE, 2, test_Y_lineplace[1], 2);
		GRAPH_DATA_XY_SetPenSize(test_Y_line[1], 3);
		GRAPH_AttachData(hItem, test_Y_line[1]);


		for (i = 0; i < 2; i++)
		{
			_ahDataXY[i] = GRAPH_DATA_XY_Create(GUI_YELLOW, _NumPoints, _aPoint[i], _NumPoints);
			GRAPH_DATA_XY_SetLineStyle(_ahDataXY[i], _aLStyle[i]);
			GRAPH_DATA_XY_SetPenSize(_ahDataXY[i], 3);
			GRAPH_AttachData(hItem, _ahDataXY[i]);
			GRAPH_DATA_XY_SetOwnerDraw(_ahDataXY[i], _OwnerDraw);
		}
		GRAPH_SetBorder(hItem, 40, 0, 0, 0);
		//
		// Set graph attributes
		//
		GRAPH_SetGridDistY(hItem, 20);
		GRAPH_SetGridVis(hItem, 1);
		GRAPH_SetUserDraw(hItem, _UserDraw);
		//
		// Create and add vertical scale
		//
		_hScaleV = GRAPH_SCALE_Create(40, GUI_TA_RIGHT, GRAPH_SCALE_CF_VERTICAL, 20);
		GRAPH_SCALE_SetOff(_hScaleV, 20);
		GRAPH_SCALE_SetFactor(_hScaleV, 20);
		GRAPH_SCALE_SetTextColor(_hScaleV, GUI_RED);
		GRAPH_AttachScale(hItem, _hScaleV);
		//
		// Create and add horizontal scale
		//
		_hScaleH = GRAPH_SCALE_Create(190, GUI_TA_HCENTER, GRAPH_SCALE_CF_HORIZONTAL, 50);
		// GRAPH_SCALE_SetFactor(_hScaleH, 0.02f);
		GRAPH_SCALE_SetTextColor(_hScaleH, GUI_DARKGREEN);
		GRAPH_AttachScale(hItem, _hScaleH);
		//
		// Init check boxes
		//
		hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK2);
		CHECKBOX_SetText(hItem, "Single");
		CHECKBOX_SetState(hItem, 0);
		
		hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK1);
		CHECKBOX_SetText(hItem, "Grid");
		CHECKBOX_SetState(hItem, 1);
		hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK3);
		CHECKBOX_SetText(hItem, "HScroll");
		hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK4);
		CHECKBOX_SetText(hItem, "VScroll");
		hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK5);
		CHECKBOX_SetText(hItem, "Lines");
		CHECKBOX_SetState(hItem, 1);
		hItem = WM_GetDialogItem(hDlg, GUI_ID_CHECK6);
		CHECKBOX_SetText(hItem, "Points");
		CHECKBOX_SetState(hItem, 0);
		
		//X轴放大缩小
		hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER0);
		SLIDER_SetRange(hItem, 1, 10);
		SLIDER_SetValue(hItem, 2);
		SLIDER_SetNumTicks(hItem, 6);

		//Y轴放大缩小
		hItem = WM_GetDialogItem(hDlg, GUI_ID_SLIDER1);
		SLIDER_SetRange(hItem, 0, 10);
		SLIDER_SetValue(hItem, 5);
		SLIDER_SetNumTicks(hItem, 6);
		//
		
		//全屏按钮
		hItem = WM_GetDialogItem(hDlg, GUI_ID_BUTTON0);
		BUTTON_SetBitmapEx(hItem, BUTTON_BI_PRESSED, &_bmEnlarge, 10, 2);
		BUTTON_SetBitmapEx(hItem, BUTTON_BI_UNPRESSED, &_bmEnlarge, 10, 2);
		WM_SetStayOnTop(hItem, 1);
		break;

	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc); // Id of widget
		NCode = pMsg->Data.v;		  // Notification code
		switch (Id)
		{
		case GUI_ID_BUTTON0:
			switch (NCode)
			{
				case WM_NOTIFICATION_CLICKED:
					break;
				case WM_NOTIFICATION_RELEASED:
					_ToggleFullScreenMode(hDlg);
					break;
			}
			break;
		case GUI_ID_BUTTON2:
			switch (NCode)
			{
				case WM_NOTIFICATION_CLICKED:
					break;
				case WM_NOTIFICATION_RELEASED:
					switch (chose_A_B)
					{
						case 0:
							Xline_A_palce += drop1_step_value;
							break;
						case 1:
							Xline_B_palce += drop1_step_value;
							break;
						case 2:
							Xline_A_palce += drop1_step_value;
							Xline_B_palce += drop1_step_value;
							break;
						default:
							break;
					}
					break;
			}
			break;
		case GUI_ID_BUTTON3:
			switch (NCode)
			{
				case WM_NOTIFICATION_CLICKED:
					break;
				case WM_NOTIFICATION_RELEASED:
					switch (chose_A_B)
					{
						case 0:
							Xline_A_palce -= drop1_step_value;
							break;
						case 1:
							Xline_B_palce -= drop1_step_value;
							break;
						case 2:
							Xline_A_palce -= drop1_step_value;
							Xline_B_palce -= drop1_step_value;
							break;
						default:
							break;
					}
					break;
			}
			break;
		case GUI_ID_BUTTON4:
			switch (NCode)
			{
				case WM_NOTIFICATION_CLICKED:
					break;
				case WM_NOTIFICATION_RELEASED:
					switch (chose_A_B)
					{
					case 0:
						Yline_A_palce += drop1_step_value;
						break;
					case 1:
						Yline_B_palce += drop1_step_value;
						break;
					case 2:
						Yline_A_palce += drop1_step_value;
						Yline_B_palce += drop1_step_value;
						break;
					default:
						break;
					}
					break;
			}
			break;
		case GUI_ID_BUTTON5:
			switch (NCode)
			{
				case WM_NOTIFICATION_CLICKED:
					break;
				case WM_NOTIFICATION_RELEASED:
					switch (chose_A_B)
					{
					case 0:
						Yline_A_palce=Yline_A_palce - drop1_step_value;
						break;
					case 1:
						Yline_B_palce=Yline_B_palce - drop1_step_value;
						break;
					case 2:
						Yline_A_palce=Yline_A_palce - drop1_step_value;
						Yline_B_palce=Yline_B_palce - drop1_step_value;
						break;
					default:
						break;
					}
				break;
			}

		case GUI_ID_SLIDER0:
			switch (NCode)
			{
			case WM_NOTIFICATION_VALUE_CHANGED:
				X_step = SLIDER_GetValue(pMsg->hWinSrc);
				break;
			}
			break;
		case GUI_ID_SLIDER1:
			switch (NCode)
			{
			case WM_NOTIFICATION_VALUE_CHANGED:
				Y_step = SLIDER_GetValue(pMsg->hWinSrc);
				break;
			}
			break;
		
		default:
			break;
		}
		
	default:
		WM_DefaultProc(pMsg);
	}
}
//图形显示demo
static void _cbBkWindow(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void myGraphyt_demo(void)
{

	// WM_HWIN ClientWin;
	//  int Graph_xSize;
	int i, t, n, a;
	// int dataxsize;	        //示波器数据区X,Y大小

	WM_SetCallback(WM_HBKWIN, _cbBkWindow); //设置背景窗口回调函数
	hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, 0, 0, 0);
	
	setting_demo();
	
	// test_line_X_init();
	//_aPoint=mymalloc(SRAMIN,dataxsize*4);	//申请内存
	GUI_Exec();
	while (1)
	{
	
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetColor(GUI_BLACK);

		GUI_DispDecAt(mysample_time[dropdown_flag], 405, 30, 8);
		GUI_DispStringAt("Hz", 460, 30);
		GUI_DispStringAt("X_step:", 405, 45);
		GUI_DispDecAt(X_step, 460, 45, 2);
		GUI_DispStringAt("Y_step:", 405, 55);
		GUI_DispDecAt(Y_step, 460, 55, 2);
		GUI_DispStringAt("1div:", 405, 75);
		GUI_GotoXY(405, 90);
		GUI_DispFloat((1000000 / mysample_time[dropdown_flag] * 50) / X_step, 5);
		GUI_DispStringAt("us", 460, 90);

		GUI_DispStringAt("max", 405, 105);
		GUI_DispStringAt("mv", 460, 105);
		GUI_DispDecAt(signal_max, 430, 105, 4);
		
		GUI_DispStringAt("peroid", 405, 120);
		GUI_GotoXY(405, 130);
		GUI_DispFloat(peroid_test, 4);
		GUI_DispStringAt("us", 460, 130);

		
		GUI_DispStringAt("V", 405, 150);
		GUI_GotoXY(405, 160);
		GUI_DispFloat(voltage_test, 4);
		GUI_DispStringAt("mv", 460, 160);


		//刷新测量线数据
		test_line_X_init();
		test_line_Y_init();

		//刷新波形
		if (Single_flag == 0)      //判断Single是否开启
		{

			_InitPoints(300);		//刷新波形，关闭ADC
			GRAPH_DATA_XY_Clear(_ahDataXY[0]);//清除波形数据
			for (n = 0; n <= 300 - 1; n++)
			{
				GRAPH_DATA_XY_AddPoint(_ahDataXY[0], &_aPoint[0][n]);//重绘波形
				if (n == 300 - 1)//当显示完数据
				{
					GUI_Delay(30);//延迟30ms，避免屏幕闪烁
					Open_ADC();//重新打开ADC刷新数据
				}
			}
			// if(tp_dev.x[4]>100){
			//   GUI_SetColor(0x0040f0);
			//   GUI_DrawVLine(tp_dev.x[4],30,200);
			// }
		}


		//设置竖直测量线是可见
		for (i = 0; i < 2; i++)
		{
			GRAPH_DATA_XY_SetLineVis(test_line[i], line_X_flag);
		}


		//设置横向测量线是可见
		for (i = 0; i < 2; i++)
		{
			GRAPH_DATA_XY_SetLineVis(test_Y_line[i], line_Y_flag);
		}



		//设置线是否可见
		for (i = 0; i < 2; i++)
		{
			GRAPH_DATA_XY_SetLineVis(_ahDataXY[i], Lines);
		}

		//设置点是否可见
		for (a = 0; a < 2; a++)
		{
			GRAPH_DATA_XY_SetPointVis(_ahDataXY[a], Points);
		}

		//设置网格是否可见
		GRAPH_SetGridVis(WM_GetDialogItem(hWin, GUI_ID_GRAPH0), Grid_flag);


		
		// //设置横向滑条是否可见
		// if (Hscroll==1)
		// {
		// 	GRAPH_SetVSizeX(WM_GetDialogItem(hWin, GUI_ID_GRAPH0), 500);
		// }
		// else
		// {
		// 	GRAPH_SetVSizeX(WM_GetDialogItem(hWin, GUI_ID_GRAPH0), 0);
		// }

		// //设置竖向滑条是否可见
		// if (Vscroll==1)
		// {
		// 	GRAPH_SetVSizeX(WM_GetDialogItem(hWin, GUI_ID_GRAPH0), 300);
		// }
		// else
		// {
		// 	GRAPH_SetVSizeX(WM_GetDialogItem(hWin, GUI_ID_GRAPH0), 0);
		// }

		//用按键改变测量线的位置
		if (BUTTON_IsPressed(WM_GetDialogItem(hWin, GUI_ID_BUTTON2)) == 1 || BUTTON_IsPressed(WM_GetDialogItem(hWin, GUI_ID_BUTTON3)) == 1)
		{
			
			GRAPH_DATA_XY_Clear(test_line[0]);
			GRAPH_DATA_XY_Clear(test_line[1]);
			for (t = 0; t < 2; t++)
			{
				GRAPH_DATA_XY_AddPoint(test_line[0], &test_lineplace[0][t]);
				GRAPH_DATA_XY_AddPoint(test_line[1], &test_lineplace[1][t]);
			}
		}
		//更新测量线Y的位置
		if (BUTTON_IsPressed(WM_GetDialogItem(hWin, GUI_ID_BUTTON4)) == 1 || BUTTON_IsPressed(WM_GetDialogItem(hWin, GUI_ID_BUTTON5)) == 1)
		{
			
			GRAPH_DATA_XY_Clear(test_Y_line[0]);
			GRAPH_DATA_XY_Clear(test_Y_line[1]);
			for (t = 0; t < 2; t++)
			{
				GRAPH_DATA_XY_AddPoint(test_Y_line[0], &test_Y_lineplace[0][t]);
				GRAPH_DATA_XY_AddPoint(test_Y_line[1], &test_Y_lineplace[1][t]);
			}
		}

		GUI_Delay(5); //不能少。如果没有就会死循环，这个延迟里有供系统跳出来的函数
	}
}

/*************************** End of file ****************************/
