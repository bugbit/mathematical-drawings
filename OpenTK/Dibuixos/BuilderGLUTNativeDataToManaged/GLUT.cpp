#include "stdafx.h"
#include "GLUT.h"

GLUT::GLUT()
{
}

void GLUT::CreateAndWriteFonts()
{
	System::IO::StreamWriter^ pWriter = nullptr;

	try
	{
		auto pFonts = gcnew GLUT::SFG_Fonts();

		CreateFontsBitMap(pFonts);

		auto pXmlSerializer = gcnew System::Xml::Serialization::XmlSerializer(GLUT::SFG_Fonts::typeid);
		pWriter = gcnew System::IO::StreamWriter(L"fgFonts.xml");

		pXmlSerializer->Serialize(pWriter, pFonts);
	}
	finally
	{
		if (pWriter != nullptr)
			delete pWriter;
	}
}

GLUT::SFG_Font^ GLUT::CreateFont(::SFG_Font *f)
{
	auto pFont = gcnew SFG_Font();

	pFont->Name = gcnew System::String(f->Name);
	pFont->Quantity = f->Quantity;
	pFont->Height = f->Height;

	auto pCars = gcnew array<array<System::Byte>^>(256);
	::GLubyte ** ptr = (::GLubyte **)f->Characters;

	for (int i = 0; i < 256; i++, ptr++)
	{
		unsigned char *pCarn = *ptr;
		int w = *pCarn;
		int l = 1 + ((w / 8) + ((w % 8) > 0 ? 1 : 0))*pFont->Height;
		auto pCar = gcnew array<System::Byte>(l);
		pin_ptr<System::Byte> pinPtrArray = &pCar[0];

		memcpy_s(pinPtrArray, l, pCarn, l);
		pCars[i] = pCar;
	}
	pFont->Characters = pCars;

	pFont->xorig = f->xorig;
	pFont->yorig = f->yorig; /* Relative origin of the character */

	return pFont;
}