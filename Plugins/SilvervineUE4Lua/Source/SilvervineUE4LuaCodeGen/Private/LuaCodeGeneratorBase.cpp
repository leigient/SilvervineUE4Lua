// SilvervineUE4Lua / devCAT studio
// Copyright 2016 - 2019. Nexon Korea Corporation. All rights reserved.

#include "LuaCodeGeneratorBase.h"


void FSUE4LuaCodeBuilder::AppendCodeGenBanner(const FString& InLineComment)
{
	AppendLine(FString(TEXT("XX SilvervineUE4Lua / devCAT studio")).Replace(TEXT("XX"), *InLineComment));
	AppendLine(FString(TEXT("XX Copyright 2016 - 2019. Nexon Korea Corporation. All rights reserved.")).Replace(TEXT("XX"), *InLineComment));
	AppendLine();
	AppendLine(FString(TEXT("XX AUTOGENERATED XX AUTOGENERATED XX AUTOGENERATED XX AUTOGENERATED XX")).Replace(TEXT("XX"), *InLineComment));
	AppendLine(FString(TEXT("XX AUTOGENERATED XX AUTOGENERATED XX AUTOGENERATED XX AUTOGENERATED XX")).Replace(TEXT("XX"), *InLineComment));
	AppendLine(FString(TEXT("XX AUTOGENERATED                                      AUTOGENERATED XX")).Replace(TEXT("XX"), *InLineComment));
	AppendLine(FString(TEXT("XX AUTOGENERATED         Do NOT edit manually.        AUTOGENERATED XX")).Replace(TEXT("XX"), *InLineComment));
	AppendLine(FString(TEXT("XX AUTOGENERATED                                      AUTOGENERATED XX")).Replace(TEXT("XX"), *InLineComment));
	AppendLine(FString(TEXT("XX AUTOGENERATED XX AUTOGENERATED XX AUTOGENERATED XX AUTOGENERATED XX")).Replace(TEXT("XX"), *InLineComment));
	AppendLine(FString(TEXT("XX AUTOGENERATED XX AUTOGENERATED XX AUTOGENERATED XX AUTOGENERATED XX")).Replace(TEXT("XX"), *InLineComment));
	AppendLine();
	AppendLine();
}

FSUE4LuaCodeGeneratorBase::FSUE4LuaCodeGeneratorBase(const FString& InOutputDirectory)
{
	OutputDirectory = InOutputDirectory;
}

bool FSUE4LuaCodeGeneratorBase::SaveIfChanged(const FString& Path, const FString& NewContents)
{
	FString OriginalHeaderLocal;
	FFileHelper::LoadFileToString(OriginalHeaderLocal, *Path);

	const bool bHasChanged = OriginalHeaderLocal.Len() == 0 || FCString::Strcmp(*OriginalHeaderLocal, *NewContents);
	if (bHasChanged)
	{
		if (!FFileHelper::SaveStringToFile(NewContents, *Path))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to save : '%s'"), *Path);
		}
	}

	return bHasChanged;
}

bool FSUE4LuaCodeGeneratorBase::IsSupportedClass(const FSUE4LuaCodeGenContext& CodeGenContext)
{
	const UClass* Class = CodeGenContext.Class;
	FString ClassName = Class->GetName();

	const bool bDeprecated = Class->HasAnyClassFlags(CLASS_Deprecated);
	if (bDeprecated)
	{
		return false;
	}

	// 인터페이스는 개수도 많지 않고 처리가 복잡하여 익스포트하지 않습니다.
	const bool bInterface = Class->IsChildOf<UInterface>();
	if (bInterface)
	{
		return false;
	}

	// SUE4Lua*Binding 클래스는 제외
	const bool bBindingClass = ClassName.StartsWith(TEXT("SUE4Lua")) && ClassName.EndsWith(TEXT("Binding"));
	if (bBindingClass)
	{
		return false;
	}

	return true;
}

bool FSUE4LuaCodeGeneratorBase::IsUObjectWrapper(const UProperty* Property)
{
	return Property->HasAnyPropertyFlags(CPF_UObjectWrapper) && Property->GetClass()->HasAnyCastFlag(CASTCLASS_UObjectPropertyBase);
}

bool FSUE4LuaCodeGeneratorBase::IsParameter(const UProperty* Param)
{
	return Param->HasAnyPropertyFlags(CPF_Parm);
}

bool FSUE4LuaCodeGeneratorBase::IsReturnParameter(const UProperty* Param)
{
	return Param->HasAnyPropertyFlags(CPF_ReturnParm);
}

bool FSUE4LuaCodeGeneratorBase::IsOutParameter(const UProperty* Param)
{
	const bool bReturn = IsReturnParameter(Param);
	const bool bOut = Param->HasAnyPropertyFlags(CPF_OutParm);
	const bool bConst = Param->HasAnyPropertyFlags(CPF_ConstParm);

	return bOut && !(bReturn || bConst);
}

FString FSUE4LuaCodeGeneratorBase::GetDefaultParameter(const UFunction* Function, const UProperty* Param)
{
	return Function->GetMetaData(FName(*FString::Printf(TEXT("CPP_Default_%s"), *Param->GetName())));
}