//switch (eMapPrintLogic)
//{
//case Calculate:
//	if (x == VALUE_SCREEN_WIDTH)
//	{
//		if (y != (VALUE_SCREEN_HEIGHT - 1))
//		{
//			strcat(gspMapFrame, "\n");
//		}
//		else {
//			strcat(gspMapFrame, "\n");
//			//TextAttr(0xb0);
//			printf(gspMapFrame);
//			cTextMapFrame[0] = '\0';
//		}
//	}
//	else
//	{
//		if ((((iMapY + y) < 0) || ((iMapX + x) < 0)) || (((iMapY + y) > (VALUE_MAP_HEIGHT - 1)) || ((iMapX + x) > (VALUE_MAP_WIDTH - 1))))
//		{
//			strcat(gspMapFrame, " ");
//			if (x == (VALUE_SCREEN_WIDTH - 1))
//			{
//				if (((iMapY + y + 1) >= 0) && ((iMapX) >= 0))
//				{
//					//TextAttr(0xb0);
//					printf(gspMapFrame);
//					cTextMapFrame[0] = '\0';
//
//				}
//			}
//			else
//			{
//				if (((iMapY + y) >= 0) && ((iMapX + x + 1) >= 0))
//				{
//					//TextAttr(0xb0);
//					printf(gspMapFrame);
//					cTextMapFrame[0] = '\0';
//				}
//			}
//		}
//		else// if (((iMapY + y) >= 0) && ((iMapX + x) >= 0))
//		{
//			MapBlockCalculate(Map, y, x, gspMapFrame);
//		}
//	}
//	break;
//case PrintOut:
//	printf(gspMapFrame);
//	cTextMapFrame[0] = '\0';
//	eMapPrintLogic = Calculate;
//	break;
//default:
//	break;
//
//}