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
		CreateFontStrokeMonoRoman(pFonts);
		CreateFontStrokeRoman(pFonts);

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

GLUT::SFG_StrokeFont^ GLUT::CreateFont(::SFG_StrokeFont *f)
{
	auto pFont = gcnew SFG_StrokeFont();
	auto l = f->Quantity;
	auto ptr = f->Characters;
	auto pCars = gcnew array<SFG_StrokeChar^>(l);

	for (int i = 0; i < l; i++, ptr++)
	{
		auto pCar = gcnew SFG_StrokeChar();

		if (*ptr != NULL)
		{
			auto l2 = (*ptr)->Number;
			auto pStrips = gcnew array<SFG_StrokeStrip^>(l2);
			auto ptr2 = (*ptr)->Strips;

			for (int j = 0; j < l2; j++, ptr2++)
			{
				auto pStrip = gcnew SFG_StrokeStrip();
				auto l3 = ptr2->Number;
				auto pVexs = gcnew array<SFG_StrokeVertex ^>(l3);
				auto ptr3 = ptr2->Vertices;

				for (int k = 0; k < l3; k++, ptr3++)
				{
					auto pVex = gcnew SFG_StrokeVertex();

					pVex->X = ptr3->X;
					pVex->Y = ptr3->Y;
					pVexs[k] = pVex;
				}
				pStrip->Number = ptr2->Number;
				pStrip->Vertices = pVexs;
				pStrips[j] = pStrip;
			}

			pCar->Right = (*ptr)->Right;
			pCar->Number = l;
			pCar->Strips = pStrips;
		}
		pCars[i] = pCar;
	}
	pFont->Name = gcnew System::String(f->Name);
	pFont->Quantity = f->Quantity;
	pFont->Height = f->Height;
	pFont->Characters = pCars;

	return pFont;
}