// VGSDK - Copyright (C) 2012, Alexandre Di Pino.
// Distributed under the terms of the GNU Library General Public License (LGPL)
// as published by the Free Software Foundation.
// Author Alexandre Di Pino


#include "vgQt/vgQt.hpp"
#include <map>
#include <string>


namespace
{


static std::map<std::string, std::map<int, int> > color_foreground;
static std::map<std::string, std::map<int, int> > color_background;

void constructTheme()
{
	std::map<int, int> BespinFor;

	BespinFor[1] = 0x1E9AE0;
	BespinFor[10] = 0xFFAA00;
	BespinFor[11] = 0xF8F8F8;
	BespinFor[13] = 0xFF3A83;
	BespinFor[14] = 0xFFB454;
	BespinFor[15] = 0x1E9AE0;
	BespinFor[16] = 0xFFAA00;
	BespinFor[17] = 0x1E9AE0;
	BespinFor[18] = 0x1E9AE0;
	BespinFor[2] = 0x1E9AE0;
	BespinFor[3] = 0x1E9AE0;
	BespinFor[4] = 0xFF3A83;
	BespinFor[5] = 0xF6F080;
	BespinFor[6] = 0x55E439;
	BespinFor[7] = 0x55E439;
	BespinFor[9] = 0xFFAA00;

	color_foreground["Bespin"] = BespinFor;

	std::map<int, int> BespinBack;

	BespinBack[1] = 0x2A211C;
	BespinBack[10] = 0x2A211C;
	BespinBack[11] = 0x2A211C;
	BespinBack[13] = 0x2A211C;
	BespinBack[14] = 0x2A211C;
	BespinBack[15] = 0x2A211C;
	BespinBack[16] = 0x2A211C;
	BespinBack[17] = 0x2A211C;
	BespinBack[18] = 0x2A211C;
	BespinBack[2] = 0x2A211C;
	BespinBack[3] = 0x2A211C;
	BespinBack[4] = 0x2A211C;
	BespinBack[5] = 0x2A211C;
	BespinBack[6] = 0x2A211C;
	BespinBack[7] = 0x2A211C;
	BespinBack[9] = 0x2A211C;

	color_background["Bespin"] = BespinBack;

	std::map<int, int> BlackboardFor;

	BlackboardFor[1] = 0xAEAEAE;
	BlackboardFor[10] = 0xFBDE2D;
	BlackboardFor[11] = 0xF8F8F8;
	BlackboardFor[13] = 0xD8FA3C;
	BlackboardFor[14] = 0x61CE3C;
	BlackboardFor[15] = 0xAEAEAE;
	BlackboardFor[16] = 0xFBDE2D;
	BlackboardFor[17] = 0xAEAEAE;
	BlackboardFor[18] = 0xAEAEAE;
	BlackboardFor[2] = 0xAEAEAE;
	BlackboardFor[3] = 0xAEAEAE;
	BlackboardFor[4] = 0xD8FA3C;
	BlackboardFor[5] = 0xFBDE2D;
	BlackboardFor[6] = 0x61CE3C;
	BlackboardFor[7] = 0x61CE3C;
	BlackboardFor[9] = 0xFBDE2D;

	color_foreground["Blackboard"] = BlackboardFor;

	std::map<int, int> BlackboardBack;

	BlackboardBack[1] = 0x0C1021;
	BlackboardBack[10] = 0x0C1021;
	BlackboardBack[11] = 0x0C1021;
	BlackboardBack[13] = 0x0C1021;
	BlackboardBack[14] = 0x0C1021;
	BlackboardBack[15] = 0x0C1021;
	BlackboardBack[16] = 0x0C1021;
	BlackboardBack[17] = 0x0C1021;
	BlackboardBack[18] = 0x0C1021;
	BlackboardBack[2] = 0x0C1021;
	BlackboardBack[3] = 0x0C1021;
	BlackboardBack[4] = 0x0C1021;
	BlackboardBack[5] = 0x0C1021;
	BlackboardBack[6] = 0x0C1021;
	BlackboardBack[7] = 0x0C1021;
	BlackboardBack[9] = 0x0C1021;

	color_background["Blackboard"] = BlackboardBack;

	std::map<int, int> ChocoFor;

	ChocoFor[1] = 0x679D47;
	ChocoFor[10] = 0xB3935C;
	ChocoFor[11] = 0xC3BE98;
	ChocoFor[13] = 0xDA5659;
	ChocoFor[14] = 0xE9C062;
	ChocoFor[15] = 0x679D47;
	ChocoFor[16] = 0xB3935C;
	ChocoFor[17] = 0x679D47;
	ChocoFor[18] = 0x679D47;
	ChocoFor[2] = 0x679D47;
	ChocoFor[3] = 0x679D47;
	ChocoFor[4] = 0xDA5659;
	ChocoFor[5] = 0xF1E694;
	ChocoFor[6] = 0x7CA563;
	ChocoFor[7] = 0x7CA563;
	ChocoFor[9] = 0x8996A8;

	color_foreground["Choco"] = ChocoFor;

	std::map<int, int> ChocoBack;

	ChocoBack[1] = 0x1A0F0B;
	ChocoBack[10] = 0x1A0F0B;
	ChocoBack[11] = 0x1A0F0B;
	ChocoBack[13] = 0x1A0F0B;
	ChocoBack[14] = 0x1A0F0B;
	ChocoBack[15] = 0x1A0F0B;
	ChocoBack[16] = 0x1A0F0B;
	ChocoBack[17] = 0x1A0F0B;
	ChocoBack[18] = 0x1A0F0B;
	ChocoBack[2] = 0x1A0F0B;
	ChocoBack[3] = 0x1A0F0B;
	ChocoBack[4] = 0x1A0F0B;
	ChocoBack[5] = 0x1A0F0B;
	ChocoBack[6] = 0x1A0F0B;
	ChocoBack[7] = 0x1A0F0B;
	ChocoBack[9] = 0x1A0F0B;

	color_background["Choco"] = ChocoBack;

	std::map<int, int> DeepBlackFor;

	DeepBlackFor[1] = 0x00FF00;
	DeepBlackFor[10] = 0xFFCC00;
	DeepBlackFor[11] = 0xFFFFFF;
	DeepBlackFor[13] = 0xFFFFFF;
	DeepBlackFor[14] = 0xFFFFFF;
	DeepBlackFor[15] = 0x00FF00;
	DeepBlackFor[16] = 0x00FFFF;
	DeepBlackFor[17] = 0x00FF00;
	DeepBlackFor[18] = 0x00FF00;
	DeepBlackFor[2] = 0x00FF00;
	DeepBlackFor[3] = 0x00FF00;
	DeepBlackFor[4] = 0xFF8000;
	DeepBlackFor[5] = 0xFF6600;
	DeepBlackFor[6] = 0xFFFF00;
	DeepBlackFor[7] = 0xFF8080;
	DeepBlackFor[9] = 0xC0C0C0;

	color_foreground["DeepBlack"] = DeepBlackFor;

	std::map<int, int> DeepBlackBack;

	DeepBlackBack[1] = 0x000000;
	DeepBlackBack[10] = 0x000000;
	DeepBlackBack[11] = 0x000000;
	DeepBlackBack[13] = 0x000000;
	DeepBlackBack[14] = 0x000000;
	DeepBlackBack[15] = 0x000000;
	DeepBlackBack[16] = 0x000000;
	DeepBlackBack[17] = 0x000000;
	DeepBlackBack[18] = 0x000000;
	DeepBlackBack[2] = 0x000000;
	DeepBlackBack[3] = 0x000000;
	DeepBlackBack[4] = 0x000000;
	DeepBlackBack[5] = 0x000000;
	DeepBlackBack[6] = 0x000000;
	DeepBlackBack[7] = 0x000000;
	DeepBlackBack[9] = 0x000000;

	color_background["DeepBlack"] = DeepBlackBack;

	std::map<int, int> defaultThemeFor;

	defaultThemeFor[1] = 0x008000;
	defaultThemeFor[10] = 0x000080;
	defaultThemeFor[11] = 0x000000;
	defaultThemeFor[13] = 0x000000;
	defaultThemeFor[14] = 0x000000;
	defaultThemeFor[15] = 0x008080;
	defaultThemeFor[16] = 0x8000FF;
	defaultThemeFor[17] = 0x008080;
	defaultThemeFor[18] = 0x008080;
	defaultThemeFor[2] = 0x008000;
	defaultThemeFor[3] = 0x008080;
	defaultThemeFor[4] = 0xFF8000;
	defaultThemeFor[5] = 0x0000FF;
	defaultThemeFor[6] = 0x808080;
	defaultThemeFor[7] = 0x808080;
	defaultThemeFor[9] = 0x804000;

	color_foreground["defaultTheme"] = defaultThemeFor;

	std::map<int, int> defaultThemeBack;

	defaultThemeBack[1] = 0xFFFFFF;
	defaultThemeBack[10] = 0xFFFFFF;
	defaultThemeBack[11] = 0xFFFFFF;
	defaultThemeBack[13] = 0xFFFFFF;
	defaultThemeBack[14] = 0xFFFFFF;
	defaultThemeBack[15] = 0xFFFFFF;
	defaultThemeBack[16] = 0xFFFFFF;
	defaultThemeBack[17] = 0xFFFFFF;
	defaultThemeBack[18] = 0xFFFFFF;
	defaultThemeBack[2] = 0xFFFFFF;
	defaultThemeBack[3] = 0xFFFFFF;
	defaultThemeBack[4] = 0xFFFFFF;
	defaultThemeBack[5] = 0xFFFFFF;
	defaultThemeBack[6] = 0xFFFFFF;
	defaultThemeBack[7] = 0xFFFFFF;
	defaultThemeBack[9] = 0xFFFFFF;

	color_background["defaultTheme"] = defaultThemeBack;

	std::map<int, int> HelloKittyFor;

	HelloKittyFor[1] = 0x008000;
	HelloKittyFor[10] = 0x000080;
	HelloKittyFor[11] = 0x000000;
	HelloKittyFor[13] = 0x000000;
	HelloKittyFor[14] = 0x000000;
	HelloKittyFor[15] = 0x008080;
	HelloKittyFor[16] = 0x8000FF;
	HelloKittyFor[17] = 0x008080;
	HelloKittyFor[18] = 0x008080;
	HelloKittyFor[2] = 0x008000;
	HelloKittyFor[3] = 0x008080;
	HelloKittyFor[4] = 0xFF8000;
	HelloKittyFor[5] = 0x0000FF;
	HelloKittyFor[6] = 0x808080;
	HelloKittyFor[7] = 0x808080;
	HelloKittyFor[9] = 0x804000;

	color_foreground["HelloKitty"] = HelloKittyFor;

	std::map<int, int> HelloKittyBack;

	HelloKittyBack[1] = 0xFFB0FF;
	HelloKittyBack[10] = 0xFFB0FF;
	HelloKittyBack[11] = 0xFFB0FF;
	HelloKittyBack[13] = 0xFFB0FF;
	HelloKittyBack[14] = 0xFFB0FF;
	HelloKittyBack[15] = 0xFFB0FF;
	HelloKittyBack[16] = 0xFFB0FF;
	HelloKittyBack[17] = 0xFFB0FF;
	HelloKittyBack[18] = 0xFFB0FF;
	HelloKittyBack[2] = 0xFFB0FF;
	HelloKittyBack[3] = 0xFFB0FF;
	HelloKittyBack[4] = 0xFFB0FF;
	HelloKittyBack[5] = 0xFFB0FF;
	HelloKittyBack[6] = 0xFFB0FF;
	HelloKittyBack[7] = 0xFFB0FF;
	HelloKittyBack[9] = 0xFFB0FF;

	color_background["HelloKitty"] = HelloKittyBack;

	std::map<int, int> HotFudgeSundaeFor;

	HotFudgeSundaeFor[1] = 0x255C08;
	HotFudgeSundaeFor[10] = 0xD6C479;
	HotFudgeSundaeFor[11] = 0xB7975D;
	HotFudgeSundaeFor[13] = 0xBCBB80;
	HotFudgeSundaeFor[14] = 0x0088CE;
	HotFudgeSundaeFor[15] = 0x255C08;
	HotFudgeSundaeFor[16] = 0xcfba28;
	HotFudgeSundaeFor[17] = 0x255C08;
	HotFudgeSundaeFor[18] = 0xff00ff;
	HotFudgeSundaeFor[2] = 0x255C08;
	HotFudgeSundaeFor[3] = 0x255C08;
	HotFudgeSundaeFor[4] = 0xAFA7D6;
	HotFudgeSundaeFor[5] = 0x42A658;
	HotFudgeSundaeFor[6] = 0xBCBB80;
	HotFudgeSundaeFor[7] = 0xBCBB80;
	HotFudgeSundaeFor[9] = 0xC11418;

	color_foreground["HotFudgeSundae"] = HotFudgeSundaeFor;

	std::map<int, int> HotFudgeSundaeBack;

	HotFudgeSundaeBack[1] = 0x2b0f01;
	HotFudgeSundaeBack[10] = 0x2b0f01;
	HotFudgeSundaeBack[11] = 0x2b0f01;
	HotFudgeSundaeBack[13] = 0x2b0f01;
	HotFudgeSundaeBack[14] = 0x2b0f01;
	HotFudgeSundaeBack[15] = 0x2b0f01;
	HotFudgeSundaeBack[16] = 0x2b0f01;
	HotFudgeSundaeBack[17] = 0x2b0f01;
	HotFudgeSundaeBack[18] = 0x2b0f01;
	HotFudgeSundaeBack[2] = 0x2b0f01;
	HotFudgeSundaeBack[3] = 0x2b0f01;
	HotFudgeSundaeBack[4] = 0x2b0f01;
	HotFudgeSundaeBack[5] = 0x2b0f01;
	HotFudgeSundaeBack[6] = 0x2b0f01;
	HotFudgeSundaeBack[7] = 0x2b0f01;
	HotFudgeSundaeBack[9] = 0x2b0f01;

	color_background["HotFudgeSundae"] = HotFudgeSundaeBack;

	std::map<int, int> khakiFor;

	khakiFor[1] = 0x87875f;
	khakiFor[10] = 0x00005f;
	khakiFor[11] = 0x5f5f00;
	khakiFor[13] = 0x005f5f;
	khakiFor[14] = 0x0087af;
	khakiFor[15] = 0x87875f;
	khakiFor[16] = 0x5f005f;
	khakiFor[17] = 0x87875f;
	khakiFor[18] = 0xd700d7;
	khakiFor[2] = 0x87875f;
	khakiFor[3] = 0x87875f;
	khakiFor[4] = 0x005f00;
	khakiFor[5] = 0x87005f;
	khakiFor[6] = 0x005f5f;
	khakiFor[7] = 0x005f5f;
	khakiFor[9] = 0x5f0000;

	color_foreground["khaki"] = khakiFor;

	std::map<int, int> khakiBack;

	khakiBack[1] = 0xd7d7af;
	khakiBack[10] = 0xd7d7af;
	khakiBack[11] = 0xd7d7af;
	khakiBack[13] = 0xd7d7af;
	khakiBack[14] = 0xd7d7af;
	khakiBack[15] = 0xd7d7af;
	khakiBack[16] = 0xd7d7af;
	khakiBack[17] = 0xd7d7af;
	khakiBack[18] = 0xd7d7af;
	khakiBack[2] = 0xd7d7af;
	khakiBack[3] = 0xd7d7af;
	khakiBack[4] = 0xd7d7af;
	khakiBack[5] = 0xd7d7af;
	khakiBack[6] = 0xd7d7af;
	khakiBack[7] = 0xd7d7af;
	khakiBack[9] = 0xd7d7af;

	color_background["khaki"] = khakiBack;

	std::map<int, int> MonoIndustrialFor;

	MonoIndustrialFor[1] = 0x666C68;
	MonoIndustrialFor[10] = 0xA8B3AB;
	MonoIndustrialFor[11] = 0xFFFFFF;
	MonoIndustrialFor[13] = 0xE98800;
	MonoIndustrialFor[14] = 0xFFFFFF;
	MonoIndustrialFor[15] = 0x666C68;
	MonoIndustrialFor[16] = 0xA39E64;
	MonoIndustrialFor[17] = 0x666C68;
	MonoIndustrialFor[18] = 0x666C68;
	MonoIndustrialFor[2] = 0x666C68;
	MonoIndustrialFor[3] = 0x666C68;
	MonoIndustrialFor[4] = 0xE98800;
	MonoIndustrialFor[5] = 0xC23B00;
	MonoIndustrialFor[6] = 0xFFFFFF;
	MonoIndustrialFor[7] = 0xFFFFFF;
	MonoIndustrialFor[9] = 0xA39E64;

	color_foreground["MonoIndustrial"] = MonoIndustrialFor;

	std::map<int, int> MonoIndustrialBack;

	MonoIndustrialBack[1] = 0x222C28;
	MonoIndustrialBack[10] = 0x222C28;
	MonoIndustrialBack[11] = 0x222C28;
	MonoIndustrialBack[13] = 0x222C28;
	MonoIndustrialBack[14] = 0x222C28;
	MonoIndustrialBack[15] = 0x222C28;
	MonoIndustrialBack[16] = 0x222C28;
	MonoIndustrialBack[17] = 0x222C28;
	MonoIndustrialBack[18] = 0x222C28;
	MonoIndustrialBack[2] = 0x222C28;
	MonoIndustrialBack[3] = 0x222C28;
	MonoIndustrialBack[4] = 0x222C28;
	MonoIndustrialBack[5] = 0x222C28;
	MonoIndustrialBack[6] = 0x222C28;
	MonoIndustrialBack[7] = 0x222C28;
	MonoIndustrialBack[9] = 0x222C28;

	color_background["MonoIndustrial"] = MonoIndustrialBack;

	std::map<int, int> MonokaiFor;

	MonokaiFor[1] = 0x75715E;
	MonokaiFor[10] = 0xF92672;
	MonokaiFor[11] = 0xF8F8F2;
	MonokaiFor[13] = 0xAE81FF;
	MonokaiFor[14] = 0xE6DB74;
	MonokaiFor[15] = 0x75715E;
	MonokaiFor[16] = 0xF92672;
	MonokaiFor[17] = 0x75715E;
	MonokaiFor[18] = 0x75715E;
	MonokaiFor[2] = 0x75715E;
	MonokaiFor[3] = 0x75715E;
	MonokaiFor[4] = 0xAE81FF;
	MonokaiFor[5] = 0x66D9EF;
	MonokaiFor[6] = 0xE6DB74;
	MonokaiFor[7] = 0xE6DB74;
	MonokaiFor[9] = 0xF92672;

	color_foreground["Monokai"] = MonokaiFor;

	std::map<int, int> MonokaiBack;

	MonokaiBack[1] = 0x272822;
	MonokaiBack[10] = 0x272822;
	MonokaiBack[11] = 0x272822;
	MonokaiBack[13] = 0x272822;
	MonokaiBack[14] = 0x272822;
	MonokaiBack[15] = 0x272822;
	MonokaiBack[16] = 0x272822;
	MonokaiBack[17] = 0x272822;
	MonokaiBack[18] = 0x272822;
	MonokaiBack[2] = 0x272822;
	MonokaiBack[3] = 0x272822;
	MonokaiBack[4] = 0x272822;
	MonokaiBack[5] = 0x272822;
	MonokaiBack[6] = 0x272822;
	MonokaiBack[7] = 0x272822;
	MonokaiBack[9] = 0x272822;

	color_background["Monokai"] = MonokaiBack;

	std::map<int, int> MossyLawnFor;

	MossyLawnFor[1] = 0x2a390e;
	MossyLawnFor[10] = 0xffee88;
	MossyLawnFor[11] = 0xf2c476;
	MossyLawnFor[13] = 0xffdc87;
	MossyLawnFor[14] = 0xafcf90;
	MossyLawnFor[15] = 0x2a390e;
	MossyLawnFor[16] = 0xefc53d;
	MossyLawnFor[17] = 0x2a390e;
	MossyLawnFor[18] = 0x981f0e;
	MossyLawnFor[2] = 0x2a390e;
	MossyLawnFor[3] = 0x2a390e;
	MossyLawnFor[4] = 0xffdc87;
	MossyLawnFor[5] = 0xcbe248;
	MossyLawnFor[6] = 0xffdc87;
	MossyLawnFor[7] = 0xffdc87;
	MossyLawnFor[9] = 0xa32129;

	color_foreground["MossyLawn"] = MossyLawnFor;

	std::map<int, int> MossyLawnBack;

	MossyLawnBack[1] = 0x6c7d51;
	MossyLawnBack[10] = 0x6c7d51;
	MossyLawnBack[11] = 0x6c7d51;
	MossyLawnBack[13] = 0x6c7d51;
	MossyLawnBack[14] = 0x6c7d51;
	MossyLawnBack[15] = 0x6c7d51;
	MossyLawnBack[16] = 0x6c7d51;
	MossyLawnBack[17] = 0x6c7d51;
	MossyLawnBack[18] = 0xfdd64a;
	MossyLawnBack[2] = 0x6c7d51;
	MossyLawnBack[3] = 0x6c7d51;
	MossyLawnBack[4] = 0x6c7d51;
	MossyLawnBack[5] = 0x6c7d51;
	MossyLawnBack[6] = 0x6c7d51;
	MossyLawnBack[7] = 0x6c7d51;
	MossyLawnBack[9] = 0x6c7d51;

	color_background["MossyLawn"] = MossyLawnBack;

	std::map<int, int> NavajoFor;

	NavajoFor[1] = 0x181880;
	NavajoFor[10] = 0x010101;
	NavajoFor[11] = 0x000000;
	NavajoFor[13] = 0xC00058;
	NavajoFor[14] = 0xC00058;
	NavajoFor[15] = 0x181880;
	NavajoFor[16] = 0x1E8B47;
	NavajoFor[17] = 0x181880;
	NavajoFor[18] = 0xBCBCBC;
	NavajoFor[2] = 0x181880;
	NavajoFor[3] = 0x181880;
	NavajoFor[4] = 0xC00058;
	NavajoFor[5] = 0x804040;
	NavajoFor[6] = 0xC00058;
	NavajoFor[7] = 0xC00058;
	NavajoFor[9] = 0x870087;

	color_foreground["Navajo"] = NavajoFor;

	std::map<int, int> NavajoBack;

	NavajoBack[1] = 0xBA9C80;
	NavajoBack[10] = 0xBA9C80;
	NavajoBack[11] = 0xBA9C80;
	NavajoBack[13] = 0xBA9C80;
	NavajoBack[14] = 0xBA9C80;
	NavajoBack[15] = 0xBA9C80;
	NavajoBack[16] = 0xBA9C80;
	NavajoBack[17] = 0xBA9C80;
	NavajoBack[18] = 0x5F0000;
	NavajoBack[2] = 0xBA9C80;
	NavajoBack[3] = 0xBA9C80;
	NavajoBack[4] = 0xBA9C80;
	NavajoBack[5] = 0xBA9C80;
	NavajoBack[6] = 0xBA9C80;
	NavajoBack[7] = 0xBA9C80;
	NavajoBack[9] = 0xBA9C80;

	color_background["Navajo"] = NavajoBack;

	std::map<int, int> ObsidianFor;

	ObsidianFor[1] = 0x66747B;
	ObsidianFor[10] = 0xE8E2B7;
	ObsidianFor[11] = 0xE0E2E4;
	ObsidianFor[13] = 0xE0E2E4;
	ObsidianFor[14] = 0xD39745;
	ObsidianFor[15] = 0x6C788C;
	ObsidianFor[16] = 0x678CB1;
	ObsidianFor[17] = 0x6C788C;
	ObsidianFor[18] = 0x6C788C;
	ObsidianFor[2] = 0x66747B;
	ObsidianFor[3] = 0x6C788C;
	ObsidianFor[4] = 0xFFCD22;
	ObsidianFor[5] = 0x93C763;
	ObsidianFor[6] = 0xEC7600;
	ObsidianFor[7] = 0xFF8409;
	ObsidianFor[9] = 0xA082BD;

	color_foreground["Obsidian"] = ObsidianFor;

	std::map<int, int> ObsidianBack;

	ObsidianBack[1] = 0x293134;
	ObsidianBack[10] = 0x293134;
	ObsidianBack[11] = 0x293134;
	ObsidianBack[13] = 0x293134;
	ObsidianBack[14] = 0x293134;
	ObsidianBack[15] = 0x293134;
	ObsidianBack[16] = 0x293134;
	ObsidianBack[17] = 0x293134;
	ObsidianBack[18] = 0x293134;
	ObsidianBack[2] = 0x293134;
	ObsidianBack[3] = 0x293134;
	ObsidianBack[4] = 0x293134;
	ObsidianBack[5] = 0x293134;
	ObsidianBack[6] = 0x293134;
	ObsidianBack[7] = 0x293134;
	ObsidianBack[9] = 0x293134;

	color_background["Obsidian"] = ObsidianBack;

	std::map<int, int> PlasticCodeWrapFor;

	PlasticCodeWrapFor[1] = 0x1E9AE0;
	PlasticCodeWrapFor[10] = 0xFFAA00;
	PlasticCodeWrapFor[11] = 0xF8F8F8;
	PlasticCodeWrapFor[13] = 0xFF3A83;
	PlasticCodeWrapFor[14] = 0xFFB454;
	PlasticCodeWrapFor[15] = 0x1E9AE0;
	PlasticCodeWrapFor[16] = 0xFFAA00;
	PlasticCodeWrapFor[17] = 0x1E9AE0;
	PlasticCodeWrapFor[18] = 0x1E9AE0;
	PlasticCodeWrapFor[2] = 0x1E9AE0;
	PlasticCodeWrapFor[3] = 0x1E9AE0;
	PlasticCodeWrapFor[4] = 0xFF3A83;
	PlasticCodeWrapFor[5] = 0xF6F080;
	PlasticCodeWrapFor[6] = 0x55E439;
	PlasticCodeWrapFor[7] = 0x55E439;
	PlasticCodeWrapFor[9] = 0xFFAA00;

	color_foreground["PlasticCodeWrap"] = PlasticCodeWrapFor;

	std::map<int, int> PlasticCodeWrapBack;

	PlasticCodeWrapBack[1] = 0x0B161D;
	PlasticCodeWrapBack[10] = 0x0B161D;
	PlasticCodeWrapBack[11] = 0x0B161D;
	PlasticCodeWrapBack[13] = 0x0B161D;
	PlasticCodeWrapBack[14] = 0x0B161D;
	PlasticCodeWrapBack[15] = 0x0B161D;
	PlasticCodeWrapBack[16] = 0x0B161D;
	PlasticCodeWrapBack[17] = 0x0B161D;
	PlasticCodeWrapBack[18] = 0x0B161D;
	PlasticCodeWrapBack[2] = 0x0B161D;
	PlasticCodeWrapBack[3] = 0x0B161D;
	PlasticCodeWrapBack[4] = 0x0B161D;
	PlasticCodeWrapBack[5] = 0x0B161D;
	PlasticCodeWrapBack[6] = 0x0B161D;
	PlasticCodeWrapBack[7] = 0x0B161D;
	PlasticCodeWrapBack[9] = 0x0B161D;

	color_background["PlasticCodeWrap"] = PlasticCodeWrapBack;

	std::map<int, int> RubyBlueFor;

	RubyBlueFor[1] = 0xFFFFFF;
	RubyBlueFor[10] = 0xFFFFFF;
	RubyBlueFor[11] = 0xFFFFFF;
	RubyBlueFor[13] = 0xFFFFFF;
	RubyBlueFor[14] = 0xFFFFFF;
	RubyBlueFor[15] = 0xFFFFFF;
	RubyBlueFor[16] = 0xFFFFFF;
	RubyBlueFor[17] = 0xFFFFFF;
	RubyBlueFor[18] = 0xFFFFFF;
	RubyBlueFor[2] = 0xFFFFFF;
	RubyBlueFor[3] = 0xFFFFFF;
	RubyBlueFor[4] = 0xFFFFFF;
	RubyBlueFor[5] = 0xFFFFFF;
	RubyBlueFor[6] = 0xFFFFFF;
	RubyBlueFor[7] = 0xFFFFFF;
	RubyBlueFor[9] = 0xFFFFFF;

	color_foreground["RubyBlue"] = RubyBlueFor;

	std::map<int, int> RubyBlueBack;

	RubyBlueBack[1] = 0x112435;
	RubyBlueBack[10] = 0x112435;
	RubyBlueBack[11] = 0x112435;
	RubyBlueBack[13] = 0x112435;
	RubyBlueBack[14] = 0x112435;
	RubyBlueBack[15] = 0x112435;
	RubyBlueBack[16] = 0x112435;
	RubyBlueBack[17] = 0x112435;
	RubyBlueBack[18] = 0x112435;
	RubyBlueBack[2] = 0x112435;
	RubyBlueBack[3] = 0x112435;
	RubyBlueBack[4] = 0x112435;
	RubyBlueBack[5] = 0x112435;
	RubyBlueBack[6] = 0x112435;
	RubyBlueBack[7] = 0x112435;
	RubyBlueBack[9] = 0x112435;

	color_background["RubyBlue"] = RubyBlueBack;

	std::map<int, int> SolarizedlightFor;

	SolarizedlightFor[1] = 0x93A1A1;
	SolarizedlightFor[10] = 0x586E75;
	SolarizedlightFor[11] = 0x657B83;
	SolarizedlightFor[13] = 0x2AA198;
	SolarizedlightFor[14] = 0x268BD2;
	SolarizedlightFor[15] = 0x93A1A1;
	SolarizedlightFor[16] = 0xB58900;
	SolarizedlightFor[17] = 0x93A1A1;
	SolarizedlightFor[18] = 0xD33682;
	SolarizedlightFor[2] = 0x93A1A1;
	SolarizedlightFor[3] = 0x93A1A1;
	SolarizedlightFor[4] = 0x2AA198;
	SolarizedlightFor[5] = 0x859900;
	SolarizedlightFor[6] = 0x2AA198;
	SolarizedlightFor[7] = 0x2AA198;
	SolarizedlightFor[9] = 0xDC322F;

	color_foreground["Solarizedlight"] = SolarizedlightFor;

	std::map<int, int> SolarizedlightBack;

	SolarizedlightBack[1] = 0xFDF6E3;
	SolarizedlightBack[10] = 0xFDF6E3;
	SolarizedlightBack[11] = 0xFDF6E3;
	SolarizedlightBack[13] = 0xFDF6E3;
	SolarizedlightBack[14] = 0xFDF6E3;
	SolarizedlightBack[15] = 0xFDF6E3;
	SolarizedlightBack[16] = 0xFDF6E3;
	SolarizedlightBack[17] = 0xFDF6E3;
	SolarizedlightBack[18] = 0xFDF6E3;
	SolarizedlightBack[2] = 0xFDF6E3;
	SolarizedlightBack[3] = 0xFDF6E3;
	SolarizedlightBack[4] = 0xFDF6E3;
	SolarizedlightBack[5] = 0xFDF6E3;
	SolarizedlightBack[6] = 0xFDF6E3;
	SolarizedlightBack[7] = 0xFDF6E3;
	SolarizedlightBack[9] = 0xFDF6E3;

	color_background["Solarizedlight"] = SolarizedlightBack;

	std::map<int, int> SolarizedFor;

	SolarizedFor[1] = 0x586E75;
	SolarizedFor[10] = 0x93A1A1;
	SolarizedFor[11] = 0x839496;
	SolarizedFor[13] = 0x2AA198;
	SolarizedFor[14] = 0x268BD2;
	SolarizedFor[15] = 0x586E75;
	SolarizedFor[16] = 0xB58900;
	SolarizedFor[17] = 0x586E75;
	SolarizedFor[18] = 0xD33682;
	SolarizedFor[2] = 0x586E75;
	SolarizedFor[3] = 0x586E75;
	SolarizedFor[4] = 0x2AA198;
	SolarizedFor[5] = 0x859900;
	SolarizedFor[6] = 0x2AA198;
	SolarizedFor[7] = 0x2AA198;
	SolarizedFor[9] = 0xDC322F;

	color_foreground["Solarized"] = SolarizedFor;

	std::map<int, int> SolarizedBack;

	SolarizedBack[1] = 0x002B36;
	SolarizedBack[10] = 0x002B36;
	SolarizedBack[11] = 0x002B36;
	SolarizedBack[13] = 0x002B36;
	SolarizedBack[14] = 0x002B36;
	SolarizedBack[15] = 0x002B36;
	SolarizedBack[16] = 0x002B36;
	SolarizedBack[17] = 0x002B36;
	SolarizedBack[18] = 0x002B36;
	SolarizedBack[2] = 0x002B36;
	SolarizedBack[3] = 0x002B36;
	SolarizedBack[4] = 0x002B36;
	SolarizedBack[5] = 0x002B36;
	SolarizedBack[6] = 0x002B36;
	SolarizedBack[7] = 0x002B36;
	SolarizedBack[9] = 0x002B36;

	color_background["Solarized"] = SolarizedBack;

	std::map<int, int> TwilightFor;

	TwilightFor[1] = 0x5F5A60;
	TwilightFor[10] = 0xCDA869;
	TwilightFor[11] = 0xF8F8F8;
	TwilightFor[13] = 0xCF6A4C;
	TwilightFor[14] = 0xE9C062;
	TwilightFor[15] = 0x5F5A60;
	TwilightFor[16] = 0xCDA869;
	TwilightFor[17] = 0x5F5A60;
	TwilightFor[18] = 0x5F5A60;
	TwilightFor[2] = 0x5F5A60;
	TwilightFor[3] = 0x5F5A60;
	TwilightFor[4] = 0xCF6A4C;
	TwilightFor[5] = 0xF9EE98;
	TwilightFor[6] = 0x8F9D6A;
	TwilightFor[7] = 0x8F9D6A;
	TwilightFor[9] = 0x8996A8;

	color_foreground["Twilight"] = TwilightFor;

	std::map<int, int> TwilightBack;

	TwilightBack[1] = 0x141414;
	TwilightBack[10] = 0x141414;
	TwilightBack[11] = 0x141414;
	TwilightBack[13] = 0x141414;
	TwilightBack[14] = 0x141414;
	TwilightBack[15] = 0x141414;
	TwilightBack[16] = 0x141414;
	TwilightBack[17] = 0x141414;
	TwilightBack[18] = 0x141414;
	TwilightBack[2] = 0x141414;
	TwilightBack[3] = 0x141414;
	TwilightBack[4] = 0x141414;
	TwilightBack[5] = 0x141414;
	TwilightBack[6] = 0x141414;
	TwilightBack[7] = 0x141414;
	TwilightBack[9] = 0x141414;

	color_background["Twilight"] = TwilightBack;

	std::map<int, int> VibrantInkFor;

	VibrantInkFor[1] = 0x9933CC;
	VibrantInkFor[10] = 0xFFCC00;
	VibrantInkFor[11] = 0xFFFFFF;
	VibrantInkFor[13] = 0xFFFFFF;
	VibrantInkFor[14] = 0xFFFFFF;
	VibrantInkFor[15] = 0x9933CC;
	VibrantInkFor[16] = 0x66FF00;
	VibrantInkFor[17] = 0x9933CC;
	VibrantInkFor[18] = 0x9933CC;
	VibrantInkFor[2] = 0x9933CC;
	VibrantInkFor[3] = 0x9933CC;
	VibrantInkFor[4] = 0xFF8000;
	VibrantInkFor[5] = 0xFF6600;
	VibrantInkFor[6] = 0x66FF00;
	VibrantInkFor[7] = 0x66FF00;
	VibrantInkFor[9] = 0xEDF8F9;

	color_foreground["VibrantInk"] = VibrantInkFor;

	std::map<int, int> VibrantInkBack;

	VibrantInkBack[1] = 0x000000;
	VibrantInkBack[10] = 0x000000;
	VibrantInkBack[11] = 0x000000;
	VibrantInkBack[13] = 0x000000;
	VibrantInkBack[14] = 0x000000;
	VibrantInkBack[15] = 0x000000;
	VibrantInkBack[16] = 0x000000;
	VibrantInkBack[17] = 0x000000;
	VibrantInkBack[18] = 0x000000;
	VibrantInkBack[2] = 0x000000;
	VibrantInkBack[3] = 0x000000;
	VibrantInkBack[4] = 0x000000;
	VibrantInkBack[5] = 0x000000;
	VibrantInkBack[6] = 0x000000;
	VibrantInkBack[7] = 0x000000;
	VibrantInkBack[9] = 0x000000;

	color_background["VibrantInk"] = VibrantInkBack;

	std::map<int, int> vimDarkBlueFor;

	vimDarkBlueFor[1] = 0x80A0FF;
	vimDarkBlueFor[10] = 0xFFFFFF;
	vimDarkBlueFor[11] = 0xFFFFFF;
	vimDarkBlueFor[13] = 0x00FFFF;
	vimDarkBlueFor[14] = 0x80FFFF;
	vimDarkBlueFor[15] = 0x80A0FF;
	vimDarkBlueFor[16] = 0x00FF00;
	vimDarkBlueFor[17] = 0x80A0FF;
	vimDarkBlueFor[18] = 0x80A0FF;
	vimDarkBlueFor[2] = 0x80A0FF;
	vimDarkBlueFor[3] = 0x80A0FF;
	vimDarkBlueFor[4] = 0xFFFFFF;
	vimDarkBlueFor[5] = 0xFFFF00;
	vimDarkBlueFor[6] = 0xFFA0A0;
	vimDarkBlueFor[7] = 0xFFA0A0;
	vimDarkBlueFor[9] = 0xFFFFFF;

	color_foreground["vimDarkBlue"] = vimDarkBlueFor;

	std::map<int, int> vimDarkBlueBack;

	vimDarkBlueBack[1] = 0x000040;
	vimDarkBlueBack[10] = 0x000040;
	vimDarkBlueBack[11] = 0x000040;
	vimDarkBlueBack[13] = 0x000040;
	vimDarkBlueBack[14] = 0x000040;
	vimDarkBlueBack[15] = 0x000040;
	vimDarkBlueBack[16] = 0x000040;
	vimDarkBlueBack[17] = 0x000040;
	vimDarkBlueBack[18] = 0x000040;
	vimDarkBlueBack[2] = 0x000040;
	vimDarkBlueBack[3] = 0x000040;
	vimDarkBlueBack[4] = 0x000040;
	vimDarkBlueBack[5] = 0x000040;
	vimDarkBlueBack[6] = 0x000040;
	vimDarkBlueBack[7] = 0x000040;
	vimDarkBlueBack[9] = 0x000040;

	color_background["vimDarkBlue"] = vimDarkBlueBack;

	std::map<int, int> ZenburnFor;

	ZenburnFor[1] = 0x7F9F7F;
	ZenburnFor[10] = 0x9F9D6D;
	ZenburnFor[11] = 0xDCDCCC;
	ZenburnFor[13] = 0xCC9393;
	ZenburnFor[14] = 0xC89191;
	ZenburnFor[15] = 0x7F9F7F;
	ZenburnFor[16] = 0xCEDF99;
	ZenburnFor[17] = 0x7F9F7F;
	ZenburnFor[18] = 0x7F9F7F;
	ZenburnFor[2] = 0x7F9F7F;
	ZenburnFor[3] = 0x7F9F7F;
	ZenburnFor[4] = 0x8CD0D3;
	ZenburnFor[5] = 0xDFC47D;
	ZenburnFor[6] = 0xCC9393;
	ZenburnFor[7] = 0xDCA3A3;
	ZenburnFor[9] = 0xFFCFAF;

	color_foreground["Zenburn"] = ZenburnFor;

	std::map<int, int> ZenburnBack;

	ZenburnBack[1] = 0x3F3F3F;
	ZenburnBack[10] = 0x3F3F3F;
	ZenburnBack[11] = 0x3F3F3F;
	ZenburnBack[13] = 0x3F3F3F;
	ZenburnBack[14] = 0x3F3F3F;
	ZenburnBack[15] = 0x3F3F3F;
	ZenburnBack[16] = 0x3F3F3F;
	ZenburnBack[17] = 0x3F3F3F;
	ZenburnBack[18] = 0x3F3F3F;
	ZenburnBack[2] = 0x3F3F3F;
	ZenburnBack[3] = 0x3F3F3F;
	ZenburnBack[4] = 0x3F3F3F;
	ZenburnBack[5] = 0x3F3F3F;
	ZenburnBack[6] = 0x3F3F3F;
	ZenburnBack[7] = 0x3F3F3F;
	ZenburnBack[9] = 0x3F3F3F;

	color_background["Zenburn"] = ZenburnBack;

}


}

namespace vgQt
{
	const std::map<int, int>&	getThemeForeground(const std::string& name)
	{
		if (color_foreground.size() == 0)
		{
			constructTheme();
		}
		return color_foreground[name];
	}

	const std::map<int, int>&	getThemeBackground(const std::string& name)
	{
		if (color_background.size() == 0)
		{
			constructTheme();
		}
		return color_background[name];
	}
}
