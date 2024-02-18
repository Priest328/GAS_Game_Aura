// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Aura/Public/AuraCharacter_Base.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAuraCharacter_Base() {}
// Cross Module References
	AURA_API UClass* Z_Construct_UClass_AAuraCharacter_Base();
	AURA_API UClass* Z_Construct_UClass_AAuraCharacter_Base_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_ACharacter();
	UPackage* Z_Construct_UPackage__Script_Aura();
// End Cross Module References
	void AAuraCharacter_Base::StaticRegisterNativesAAuraCharacter_Base()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AAuraCharacter_Base);
	UClass* Z_Construct_UClass_AAuraCharacter_Base_NoRegister()
	{
		return AAuraCharacter_Base::StaticClass();
	}
	struct Z_Construct_UClass_AAuraCharacter_Base_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AAuraCharacter_Base_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_ACharacter,
		(UObject* (*)())Z_Construct_UPackage__Script_Aura,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAuraCharacter_Base_Statics::DependentSingletons) < 16);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AAuraCharacter_Base_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "AuraCharacter_Base.h" },
		{ "ModuleRelativePath", "Public/AuraCharacter_Base.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AAuraCharacter_Base_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAuraCharacter_Base>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_AAuraCharacter_Base_Statics::ClassParams = {
		&AAuraCharacter_Base::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAuraCharacter_Base_Statics::Class_MetaDataParams), Z_Construct_UClass_AAuraCharacter_Base_Statics::Class_MetaDataParams)
	};
	UClass* Z_Construct_UClass_AAuraCharacter_Base()
	{
		if (!Z_Registration_Info_UClass_AAuraCharacter_Base.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAuraCharacter_Base.OuterSingleton, Z_Construct_UClass_AAuraCharacter_Base_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_AAuraCharacter_Base.OuterSingleton;
	}
	template<> AURA_API UClass* StaticClass<AAuraCharacter_Base>()
	{
		return AAuraCharacter_Base::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(AAuraCharacter_Base);
	AAuraCharacter_Base::~AAuraCharacter_Base() {}
	struct Z_CompiledInDeferFile_FID_WorkProject_Aura_Source_Aura_Public_AuraCharacter_Base_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_WorkProject_Aura_Source_Aura_Public_AuraCharacter_Base_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_AAuraCharacter_Base, AAuraCharacter_Base::StaticClass, TEXT("AAuraCharacter_Base"), &Z_Registration_Info_UClass_AAuraCharacter_Base, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAuraCharacter_Base), 3817121844U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_WorkProject_Aura_Source_Aura_Public_AuraCharacter_Base_h_2086421533(TEXT("/Script/Aura"),
		Z_CompiledInDeferFile_FID_WorkProject_Aura_Source_Aura_Public_AuraCharacter_Base_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_WorkProject_Aura_Source_Aura_Public_AuraCharacter_Base_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
