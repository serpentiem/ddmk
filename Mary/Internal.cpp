#include "Internal.h"

func_897B0_t  func_897B0  = 0;
func_89450_t  func_89450  = 0;
func_89270_t  func_89270  = 0;
func_8B470_t  func_8B470  = 0;
func_89960_t  func_89960  = 0;
func_89DE0_t  func_89DE0  = 0;
func_8BC60_t  func_8BC60  = 0;
func_305D80_t func_305D80 = 0;
func_8A000_t  func_8A000  = 0;
func_2C9F40_t func_2C9F40 = 0;
func_2CA1D0_t func_2CA1D0 = 0;
func_2CA2F0_t func_2CA2F0 = 0;
func_1EF040_t func_1EF040 = 0;
func_1DE820_t func_1DE820 = 0;
func_1DF240_t func_1DF240 = 0;
func_1F92C0_t func_1F92C0 = 0;
func_1F97F0_t func_1F97F0 = 0;


func_2EE3D0_t func_2EE3D0 = 0;
func_1FAF40_t func_1FAF40 = 0;

func_1EEF80_t func_1EEF80 = 0;



void Internal_Init()
{
	LogFunction();
	{
		auto func = CreateFunction((appBaseAddr + 0x897B0));
		func_897B0 = (func_897B0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89450));
		func_89450 = (func_89450_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89270));
		func_89270 = (func_89270_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8B470));
		func_8B470 = (func_8B470_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89960));
		func_89960 = (func_89960_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89DE0), 0, true, false);
		func_89DE0 = (func_89DE0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8BC60));
		func_8BC60 = (func_8BC60_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x305D80));
		func_305D80 = (func_305D80_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8A000));
		func_8A000 = (func_8A000_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2C9F40), 0, true, false);
		func_2C9F40 = (func_2C9F40_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2CA1D0));
		func_2CA1D0 = (func_2CA1D0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2CA2F0), 0, true, true, 0, 0, 0, 0, 1);
		func_2CA2F0 = (func_2CA2F0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1EF040));
		func_1EF040 = (func_1EF040_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1DE820), 0, true, false);
		func_1DE820 = (func_1DE820_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1DF240));
		func_1DF240 = (func_1DF240_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1F92C0));
		func_1F92C0 = (func_1F92C0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1F97F0));
		func_1F97F0 = (func_1F97F0_t)func.addr;
	}



	{
		auto func = CreateFunction((appBaseAddr + 0x2EE3D0));
		func_2EE3D0 = (func_2EE3D0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1FAF40));
		func_1FAF40 = (func_1FAF40_t)func.addr;
	}



	{
		auto func = CreateFunction((appBaseAddr + 0x1EEF80));
		func_1EEF80 = (func_1EEF80_t)func.addr;
	}








}
