#pragma once
#include <gl/glew.h>

namespace garm { namespace graphics{
	class Texture;
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
		static Texture* Diagonal(
			DiagonalTextureTypes type,
			float color1Intesity = 1.0f,
			float color2Intesity = 0.5f,
			float color3Intesity = 0.3f);
		static Texture* Pattern(
			PatternTextureType type,
			float color1Intesity = 1.0f,
			float color2Intesity = 0.5f,
			float color3Intesity = 0.3f);
		static Texture* Faded(
			FadeTextureType type,
			float startIntensity,
			float endIntensity,
			unsigned resolution);
		static Texture* SimpleTexture(
			unsigned type,
			float color1Intesity = 1.0f,
			float color2Intesity = 0.5f,
			float color3Intesity = 0.3f);
	private:
		static Texture* MakeDiagTexture1(GLubyte byteIntesity1, GLubyte byteIntesity2);
		static Texture* MakeDiagTexture2(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static Texture* MakeDiagTexture3(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static Texture* MakeDiagTexture4(GLubyte byteIntesity1, GLubyte byteIntesity2);
		static Texture* MakeDiagTexture5(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static Texture* MakeDiagTexture6(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static Texture* MakeDiagTexture7(GLubyte byteIntesity1, GLubyte byteIntesity2);

		static Texture* MakePatternTexture1(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static Texture* MakePatternTexture2(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);
		static Texture* MakePatternTexture3(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3);

		static Texture* MakeLinearFaded(float startIntensity, float endIntensity, unsigned resolution);
	};

}}