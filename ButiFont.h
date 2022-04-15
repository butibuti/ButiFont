#ifndef BUTIFONT_H
#define BUTIFONT_H

#pragma once

#ifdef BUTIFONT_EXPORTS
#define BUTIFONT_API __declspec(dllexport)
#else
#define BUTIFONT_API __declspec(dllimport)
#endif

namespace ButiFont {

/// <summary>
/// �������Ƃ̏��
/// </summary>
class FontGlyph
{
public:
	std::uint32_t    Codepoint : 31;
	std::uint32_t    Visible : 1;
	float           AdvanceX;
	/// <summary>
	/// ���W
	/// </summary>
	float           X0, Y0, X1, Y1;
	/// <summary>
	/// UV
	/// </summary>
	float           U0, V0, U1, V1;

};

/// <summary>
/// ����̎w��
/// </summary>
enum class FontLanguage {
	FONTLANG_JAPANESE, FONTLANG_ENG
};

/// <summary>
/// �t�H���g�̎g�p���̎擾
/// </summary>
class IFontInformation {
public:
	virtual const ButiFont::FontGlyph* * FindGlyphs_utf8(const char* arg_srcStr, std::int32_t& arg_ref_glyphSize) const= 0;
	virtual std::int32_t GetSize()const = 0;
};

/// <summary>
/// True Type Font�@�K�i�̃t�H���g�t�@�C���̓ǂݍ���
/// </summary>
/// <param name="arg_filePath">�t�@�C���p�X</param>
/// <param name="size">�t�H���g�𑜓x</param>
/// <param name="arg_lang">�g�p���錾��</param>
/// <param name="arg_output_width">�t�H���g�A�g���X�̉��T�C�Y(�o��)</param>
/// <param name="arg_output_height">�t�H���g�A�g���X�̏c�T�C�Y(�o��)</param>
/// <param name="arg_output_atlasTextureData">�t�H���g�A�g���X�̃s�N�Z���f�[�^(�o��)</param>
/// <param name="arg_output_fontInfo">�t�H���g�̎g�p���(�o��)</param>
/// <returns></returns>
extern BUTIFONT_API void LoadTTF(const char* arg_filePath, const std::int32_t size, ButiFont::FontLanguage arg_lang,  std::int32_t* arg_output_width,  std::int32_t* arg_output_height,unsigned char** arg_output_atlasTextureData, IFontInformation** arg_output_fontInfo);

/// <summary>
/// ButiFont���m�ۂ����������̉��
/// </summary>
/// <param name="arg_release">������郁�����̃A�h���X</param>
/// <returns></returns>
extern BUTIFONT_API void ReleaseMemory(void* arg_release);
}


#endif // !BUTIFONT_H
