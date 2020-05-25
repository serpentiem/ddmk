#include "Internal.h"

func_897B0_t func_897B0 = 0;
func_89450_t func_89450 = 0;
func_89270_t func_89270 = 0;
func_8B470_t func_8B470 = 0;
func_89960_t func_89960 = 0;
func_89DE0_t func_89DE0 = 0;
func_8BC60_t func_8BC60 = 0;
func_305D80_t func_305D80 = 0;
func_8A000_t func_8A000 = 0;
func_2C9F40_t func_2C9F40 = 0;
func_2CA1D0_t func_2CA1D0 = 0;
func_2CA2F0_t func_2CA2F0 = 0;
func_1EF040_t func_1EF040 = 0;
func_2EE3D0_t func_2EE3D0 = 0;
func_1FAF40_t func_1FAF40 = 0;
func_1EEF80_t func_1EEF80 = 0;
func_2EE060_t func_2EE060 = 0;
func_1DE820_t func_1DE820 = 0;
func_217B90_t func_217B90 = 0;
func_226F10_t func_226F10 = 0;
func_219660_t func_219660 = 0;
func_223CB0_t func_223CB0 = 0;
func_212BE0_t func_212BE0 = 0;
func_225D70_t func_225D70 = 0;
func_219260_t func_219260 = 0;
func_220970_t func_220970 = 0;
func_1DFC20_t func_1DFC20 = 0;
func_2310B0_t func_2310B0 = 0;
func_22EC90_t func_22EC90 = 0;
func_227870_t func_227870 = 0;
func_22A1E0_t func_22A1E0 = 0;
func_228CF0_t func_228CF0 = 0;
func_22B0C0_t func_22B0C0 = 0;
func_2306B0_t func_2306B0 = 0;
func_22C4A0_t func_22C4A0 = 0;
func_2300A0_t func_2300A0 = 0;
func_22BA30_t func_22BA30 = 0;
func_231A30_t func_231A30 = 0;
func_22D960_t func_22D960 = 0;
func_2298E0_t func_2298E0 = 0;
func_22CF00_t func_22CF00 = 0;
func_280120_t func_280120 = 0;
func_280160_t func_280160 = 0;
func_1EB0E0_t func_1EB0E0 = 0;
func_1F92C0_t func_1F92C0 = 0;
func_1F97F0_t func_1F97F0 = 0;
func_23E560_t func_23E560 = 0;
func_8AC80_t func_8AC80 = 0;
func_89E30_t func_89E30 = 0;
func_1B9FA0_t func_1B9FA0 = 0;
func_223AC0_t func_223AC0 = 0;
func_223F50_t func_223F50 = 0;
func_223BE0_t func_223BE0 = 0;
func_1EFB90_t func_1EFB90 = 0;
func_1E0800_t func_1E0800 = 0;
func_211100_t func_211100 = 0;
func_1F01F0_t func_1F01F0 = 0;
func_5A290_t func_5A290 = 0;

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
	{
		auto func = CreateFunction((appBaseAddr + 0x2EE060));
		func_2EE060 = (func_2EE060_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1DE820), 0, true, false);
		func_1DE820 = (func_1DE820_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x217B90));
		func_217B90 = (func_217B90_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x226F10));
		func_226F10 = (func_226F10_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x219660));
		func_219660 = (func_219660_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x223CB0));
		func_223CB0 = (func_223CB0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x212BE0));
		func_212BE0 = (func_212BE0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x225D70));
		func_225D70 = (func_225D70_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x219260));
		func_219260 = (func_219260_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x220970));
		func_220970 = (func_220970_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1DFC20));
		func_1DFC20 = (func_1DFC20_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2310B0), 0, true, false);
		func_2310B0 = (func_2310B0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22EC90), 0, true, false);
		func_22EC90 = (func_22EC90_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x227870), 0, true, false);
		func_227870 = (func_227870_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22A1E0), 0, true, false);
		func_22A1E0 = (func_22A1E0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x228CF0), 0, true, false);
		func_228CF0 = (func_228CF0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22B0C0), 0, true, false);
		func_22B0C0 = (func_22B0C0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2306B0), 0, true, false);
		func_2306B0 = (func_2306B0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22C4A0), 0, true, false);
		func_22C4A0 = (func_22C4A0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2300A0), 0, true, false);
		func_2300A0 = (func_2300A0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22BA30), 0, true, false);
		func_22BA30 = (func_22BA30_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x231A30), 0, true, false);
		func_231A30 = (func_231A30_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22D960), 0, true, false);
		func_22D960 = (func_22D960_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2298E0), 0, true, false);
		func_2298E0 = (func_2298E0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x22CF00), 0, true, false);
		func_22CF00 = (func_22CF00_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x280120));
		func_280120 = (func_280120_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x280160));
		func_280160 = (func_280160_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1EB0E0));
		func_1EB0E0 = (func_1EB0E0_t)func.addr;
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
		auto func = CreateFunction((appBaseAddr + 0x23E560));
		func_23E560 = (func_23E560_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x8AC80), 0, true, true, 0, 0, 0, 0, 1);
		func_8AC80 = (func_8AC80_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x89E30));
		func_89E30 = (func_89E30_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1B9FA0));
		func_1B9FA0 = (func_1B9FA0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x223AC0));
		func_223AC0 = (func_223AC0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x223F50));
		func_223F50 = (func_223F50_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x223BE0));
		func_223BE0 = (func_223BE0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1EFB90));
		func_1EFB90 = (func_1EFB90_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1E0800));
		func_1E0800 = (func_1E0800_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x211100));
		func_211100 = (func_211100_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x1F01F0));
		func_1F01F0 = (func_1F01F0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x5A290), 0, true, true, 0, 0, 0, 0, 2);
		func_5A290 = (func_5A290_t)func.addr;
	}
}
