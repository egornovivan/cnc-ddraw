//---------------------------------------------------------------------------

#include <vcl.h>
#include <IniFiles.hpp>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("ConfigFormUnit.cpp", ConfigForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;

		auto *ini = new TIniFile(".\\ddraw.ini");
		auto theme = ini->ReadString("ddraw", "configtheme", "Windows10");

		TStyleManager::TrySetStyle(
			theme == "Cobalt XEMedia" ? "Cobalt XEMedia" : "Windows10");

		delete ini;

		Application->CreateForm(__classid(TConfigForm), &ConfigForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
