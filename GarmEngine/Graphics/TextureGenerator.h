#pragma once
#include <gl/glew.h>

namespace garm { namespace graphics{
	class TextureOld;
	enum DiagonalTextureTypes : unsigned {
		DIAG_TEXT_1 = 1,
		DIAG_TEXT_2,
		DIAG_TEXT_3,
		DIAG_TEXT_4,
		DIAG_TEXT_5,
		DIAG_TEXT_6,
		DIAG_TEXT_7,
		DIAG_TEXT_LAST
	};

	enum PatternTextureType {
		PATT_TEXT_1 = DIAG_TEXT_LAST,
		PATT_TEXT_2,
		PATT_TEXT_3,
		PATT_TEXT_LAST
	};

	enum FadeTextureType {
		FADE_TEXT_LINEAR = PATT_TEXT_LAST,
		FADE_TEXT_LAST
	};

	class TextureGenerator {
	public:
		static TextureOld* Diagonal(
			DiagonalTextureTypes type,
			float color1Intesity = 1.0f,
			float color2Intesity = 0.5f,
			float color3Intesity = 0.3f);
		static TextureOld* Pattern(
			PatternTextureType type,
			float color1Intesity = 1.0f,
			float color2Intesity = 0.5f,
			float color3Intesity = 0.3f);
		static TextureOld* Faded(
			FadeTextureType type,
			float startIntensity,
			float endIntensity,
			unsigned resolution);
		static TextureOld* SimpleTexture(
			unsigned type,
			float color1Intesity = 1.0f,
			float color2Intesity = 0.5f,
			float color3Intesity = 0.3f);
	private:
		static TextureOld* MakeDiagTexture1(GLubyte byteIntesity1, GLubyte byteIntesity2);
		static TextureOld* MakeDiagTexture2(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static TextureOld* MakeDiagTexture3(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static TextureOld* MakeDiagTexture4(GLubyte byteIntesity1, GLubyte byteIntesity2);
		static TextureOld* MakeDiagTexture5(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static TextureOld* MakeDiagTexture6(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static TextureOld* MakeDiagTexture7(GLubyte byteIntesity1, GLubyte byteIntesity2);

		static TextureOld* MakePatternTexture1(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static TextureOld* MakePatternTexture2(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static TextureOld* MakePatternTexture3(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);

		static TextureOld* MakeLinearFaded(float startIntensity, float endIntensity, unsigned resolution);
	};

}}