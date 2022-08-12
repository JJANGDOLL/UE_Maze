// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_CharacterTest.h"
#include "MainCharcater.h"

#include "Global.h"

AGM_CharacterTest::AGM_CharacterTest()
{
//     DefaultPawnClass = AMainCharcater::StaticClass();
    Helpers::GetClass<APawn>(&DefaultPawnClass, "Blueprint'/Game/Characters/BP_MainCharacter.BP_MainCharacter_C'");
}