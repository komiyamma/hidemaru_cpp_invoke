/*
 * Copyright (c) 2021 Akitsugu Komiyama
 * under the MIT License
 */


#include "HmCppInvoke.h"


using namespace std;
using namespace Hidemaru;


THm::TFile::PFNAnalyzeEncoding THm::TFile::Hidemaru_AnalyzeEncoding = NULL;
THm::TFile::PFNLoadFileUnicode THm::TFile::Hidemaru_LoadFileUnicode = NULL;


THm::TFile::TFile()
{
	if (hHideExeHandle) {
		Hidemaru_AnalyzeEncoding = (PFNAnalyzeEncoding)GetProcAddress(hHideExeHandle, "Hidemaru_AnalyzeEncoding");
		Hidemaru_LoadFileUnicode = (PFNLoadFileUnicode)GetProcAddress(hHideExeHandle, "Hidemaru_LoadFileUnicode");
	}
}

Hidemaru::THm::TFile::IEncoding::IEncoding(int hm_encode, int ms_codepage)
{
	this->hm_encode = hm_encode;
	this->ms_codepage = ms_codepage;
}


int THm::TFile::IEncoding::getHmEncode()
{
	return hm_encode;
}

int THm::TFile::IEncoding::getMsCodePage()
{
	return ms_codepage;
}

THm::TFile::IEncoding Hidemaru::THm::TFile::getEncoding(int hm_encode)
{
	const vector<int> to_mscp_list = getEncodingTable();
	if (0 <= hm_encode && hm_encode < (int)to_mscp_list.size()) {
		IEncoding encode = IEncoding(hm_encode, to_mscp_list[hm_encode]);
		return encode;
	}

	IEncoding no_encode = IEncoding(0, 0);
	return no_encode;

}

THm::TFile::IEncoding Hidemaru::THm::TFile::getEncoding(wstring filepath)
{
	if (Hidemaru_AnalyzeEncoding) {
		int hm_encode = Hidemaru_AnalyzeEncoding(filepath.c_str(), 0, 0);
		return getEncoding(hm_encode);
	}

	return getEncoding(0);
}

const vector<int> Hidemaru::THm::TFile::getEncodingTable()
{
	const vector<int> ret = {
		0,      // Unknown
		932,	// encode = 1 ANSI/OEM Japanese; Japanese (Shift-JIS)
		1200,	// encode = 2 Unicode UTF-16, little-endian
		51932,	// encode = 3 EUC
		50221,	// encode = 4 JIS
		65000,	// encode = 5 UTF-7
		65001,	// encode = 6 UTF-8
		1201,	// encode = 7 Unicode UTF-16, big-endian
		1252,	// encode = 8 ���� ANSI Latin 1; Western European (Windows)
		936,	// encode = 9 �ȑ̎������� ANSI/OEM Simplified Chinese (PRC, Singapore); Chinese Simplified (GB2312)
		950,	// encode =10 �ɑ̎������� ANSI/OEM Traditional Chinese (Taiwan; Hong Kong SAR, PRC); Chinese Traditional (Big5)
		949,	// encode =11 �؍��� ANSI/OEM Korean (Unified Hangul Code)
		1361,	// encode =12 �؍��� Korean (Johab)
		1250,	// encode =13 �������[���b�p���� ANSI Central European; Central European (Windows)
		1257,	// encode =14 �o���g�� ANSI Baltic; Baltic (Windows)
		1253,	// encode =15 �M���V���� ANSI Greek; Greek (Windows)
		1251,	// encode =16 �L�������� ANSI Cyrillic; Cyrillic (Windows)
		42,		// encode =17 �V���{��
		1254,	// encode =18 �g���R�� ANSI Turkish; Turkish (Windows)
		1255,	// encode =19 �w�u���C�� ANSI Hebrew; Hebrew (Windows)
		1256,	// encode =20 �A���r�A�� ANSI Arabic; Arabic (Windows)
		874,	// encode =21 �^�C�� ANSI/OEM Thai (same as 28605, ISO 8859-15); Thai (Windows)
		1258,	// encode =22 �x�g�i���� ANSI/OEM Vietnamese; Vietnamese (Windows)
		10001,	// encode =23 x-mac-japanese Japanese (Mac)
		850,	// encode =24 OEM/DOS
		0,		// encode =25 ���̑�
		12000,	// encode =26 Unicode (UTF-32) little-endian
		12001	// encode =27 Unicode (UTF-32) big-endian
	};

	return ret;
}


Hidemaru::THm::TFile::IHidemaruStreamReader::IHidemaruStreamReader(std::wstring filepath, IEncoding encoding)
{
	this->filepath = filepath;
	this->encoding = encoding;
}

THm::TFile::IEncoding THm::TFile::IHidemaruStreamReader::getEncoding()
{
	return this->encoding;
}

wstring THm::TFile::IHidemaruStreamReader::read()
{
	if (Hidemaru_LoadFileUnicode) {
		UINT pcwchOut = 0;
		HGLOBAL hGlobal = Hidemaru_LoadFileUnicode(filepath.c_str(), this->encoding.getHmEncode(), &pcwchOut, NULL, NULL);
		if (hGlobal) {
			wchar_t* pwsz = (wchar_t*)GlobalLock(hGlobal);
			if (pwsz) {
				wstring text(pwsz); // �R�s�[
				GlobalUnlock(hGlobal);
				GlobalFree(hGlobal); // ���͉̂��
				return text;
			}
		}
	}

	return L"";
}

wstring THm::TFile::IHidemaruStreamReader::getFilePath()
{
	return this->filepath;
}

void THm::TFile::IHidemaruStreamReader::close()
{
	this->filepath = L"";
	this->encoding = IEncoding(0, 0);
}

THm::TFile::IHidemaruStreamReader THm::TFile::open(std::wstring filepath, int hm_encode)
{
	if (hm_encode == -1) {
		IEncoding encoding = getEncoding(filepath);
		IHidemaruStreamReader sr = IHidemaruStreamReader(filepath, encoding);
		return sr;
	}
	else {
		IEncoding encoding = getEncoding(hm_encode);
		IHidemaruStreamReader sr = IHidemaruStreamReader(filepath, encoding);
		return sr;
	}

}



