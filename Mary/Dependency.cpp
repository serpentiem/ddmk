


//#include "../Core/Core.h"

#include "../Core/DataTypes.h"
#include "../Core/Memory.ixx"


#include "../Core/File.ixx"


#include "../Core/Memory.ixx"






//export struct FUNC
//{
//	byte8 *  addr;
//	byte8 *  sect0;
//	byte8 *  sect1;
//	byte8 *  sect2;
//	byte8 ** cache;
//};







void Init()
{
	{
		byte8 sect0[] =
		{
			0x66, 0x89, 0x81, 0x66, 0x01, 0x00, 0x00, //mov [rcx+00000166],ax
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1AA3CC), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x1AA3C5), func.addr, 2);
	}
}



















