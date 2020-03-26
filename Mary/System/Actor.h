#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Internal.h"
#include "../Vars.h"

#include "File.h"

#include "../Cosmetics/Color.h"
#include "../Cosmetics/Model.h"

//extern uint32 devilCounter;
//extern bool System_Actor_enableArrayExtension;
//extern bool System_Actor_enableCreateActor;
//extern bool System_Actor_enableUpdateActor;
//extern bool System_Actor_enableDoppelgangerFixes;
//extern bool System_Actor_enableModelFixes;
//extern byte8 * System_Actor_actorBaseAddr[MAX_ACTOR];
// @Todo: Move to Internal.
//typedef void(__fastcall * UpdateModel_t)(byte8 * baseAddr);
//extern byte8 * System_Actor_mainActorBaseAddr;
//extern byte8 * System_Actor_mainCloneBaseAddr;
//
////extern byte8 ** System_Actor_actorBaseAddr;
////extern byte8 ** System_Actor_cloneBaseAddr;
//
//
//extern byte8 * System_Actor_actorBaseAddr[MAX_ACTOR];
//extern byte8 * System_Actor_cloneBaseAddr[MAX_ACTOR];



// @Todo: Add operator[].

//template <typename T, uint32 n>
//struct vector
//{
//	uint32 count;
//	T data[n];
//	void Push(T var)
//	{
//		data[count] = var;
//		count++;
//	}
//	void Clear()
//	{
//		memset(this, 0, sizeof(*this));
//	}
//	void operator+=(T var)
//	{
//		Push(var);
//	}
//	vector()
//	{
//		Clear();
//	}
//};


//extern vector<byte8 *, 128> Actor_actorBaseAddr;








template <typename T, uint32 n>
struct vector
{
	uint32 count;
	T data[n];
	void Push(T var)
	{
		data[count] = var;
		count++;
	}
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
	void operator+=(T var)
	{
		Push(var);
	}
	T & operator[](uint32 index)
	{
		return data[index];
	}
	vector()
	{
		Clear();
	}
};

extern vector<byte8 *, 128> System_Actor_actorBaseAddr;













byte8 * CreateActor
(
	uint8 character,
	uint8 actor
);







//typedef void(* System_Actor_UpdateDevilForm_t)(byte8 *       );
//typedef void(* System_Actor_UpdateFlux_t     )(byte8 *, uint8);
//typedef void(* System_Actor_Relax_t          )(byte8 *       );
//
//extern System_Actor_UpdateDevilForm_t System_Actor_UpdateDevilForm;
//extern System_Actor_UpdateFlux_t      System_Actor_UpdateFlux;
//extern System_Actor_Relax_t           System_Actor_Relax;







//void System_Actor_AdjustConfig(CONFIG & config);





//uint8 System_Actor_GetActorId(byte8 * baseAddr);
//uint8 System_Actor_GetActorCount();
//void System_Actor_ResetDevilModel();
//void System_Actor_UpdateDevilModel(uint8 model);
void System_Actor_Init();
//void System_Actor_ToggleArrayExtension(bool enable);
//void System_Actor_ToggleCreateActorOne(bool enable);
//void System_Actor_ToggleUpdateActor(bool enable);
//void System_Actor_ToggleDoppelgangerFixes(bool enable);
//void System_Actor_ToggleModelFixes(bool enable);
//void System_Actor_ToggleDisableIdleTimer(bool enable);
