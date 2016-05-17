#include "TextureGenerator.h"
#include "Texture.h"
#include <vector>

namespace garm { namespace graphics{

	inline float lerp(float v0, float v1, float t) {
		return v0 + t*(v1 - v0);
	}

	TextureOld* TextureGenerator::MakeDiagTexture1(GLubyte byteIntesity1, GLubyte byteIntesity2){
		GLubyte image[] = {
			byteIntesity1, byteIntesity1, byteIntesity2, byteIntesity2,
			byteIntesity1, byteIntesity2, byteIntesity2, byteIntesity1,
			byteIntesity2, byteIntesity2, byteIntesity1, byteIntesity1,
			byteIntesity2, byteIntesity1, byteIntesity1, byteIntesity2};
		TextureOld* texture = new TextureOld(image, glm::ivec2(4, 4), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakeDiagTexture2(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3){
		GLubyte image[8 * 8] = {
			byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity3,
			byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity3, byteIntesity1,
			byteIntesity3, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity1,
			byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3,
			byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity3,
			byteIntesity2, byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity2,
			byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity2, byteIntesity2,
			byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3
		};
		TextureOld* texture = new TextureOld(image, glm::ivec2(8, 8), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakeDiagTexture3(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3){
		GLubyte image[6 * 6] = {
			byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, 
			byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1,
			byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1,
			byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3,
			byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2,
			byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2,
		};
	
		TextureOld* texture = new TextureOld(image, glm::ivec2(6, 6), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakeDiagTexture4(GLubyte byteIntesity1, GLubyte byteIntesity2){
		GLubyte image[5 * 5] = {
			byteIntesity1, byteIntesity1, byteIntesity2, byteIntesity2, byteIntesity2,
			byteIntesity1, byteIntesity2, byteIntesity2, byteIntesity2, byteIntesity1,
			byteIntesity2, byteIntesity2, byteIntesity2, byteIntesity1, byteIntesity1,
			byteIntesity2, byteIntesity2, byteIntesity1, byteIntesity1, byteIntesity2,
			byteIntesity2, byteIntesity1, byteIntesity1, byteIntesity2, byteIntesity2,
		};
	
		TextureOld* texture = new TextureOld(image, glm::ivec2(5, 5), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakeDiagTexture5(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3){
		GLubyte image[5 * 5] = {
			byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity3,
			byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity3, byteIntesity1,
			byteIntesity3, byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1,
			byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3,
			byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2,
		};
	
		TextureOld* texture = new TextureOld(image, glm::ivec2(5, 5), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakeDiagTexture6(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3){
		GLubyte image[6 * 6] = {
			byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3,
			byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1,
			byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1,
			byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3,
			byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2,
			byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2,
		};
	
		TextureOld* texture = new TextureOld(image, glm::ivec2(6, 6), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakeDiagTexture7(GLubyte byteIntesity1, GLubyte byteIntesity2){
		GLubyte image[3 * 3] = {
			byteIntesity2, byteIntesity2, byteIntesity1,
			byteIntesity2, byteIntesity1, byteIntesity2,
			byteIntesity1, byteIntesity2, byteIntesity2,
		};
	
		TextureOld* texture = new TextureOld(image, glm::ivec2(3, 3), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakePatternTexture1(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3){
		GLubyte image[6 * 6] = {
			byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity2, byteIntesity3, byteIntesity1,
			byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity3, byteIntesity3,
			byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity1, byteIntesity1,
			byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity3,
			byteIntesity2, byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3,
			byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity1, byteIntesity1
		};
	
		TextureOld* texture = new TextureOld(image, glm::ivec2(6, 6), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakePatternTexture2(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3){
		GLubyte image[6 * 6] = {
			byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3,
			byteIntesity1, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity1,
			byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity1, byteIntesity1,
			byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3,
			byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity1, byteIntesity1,
			byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity1
		};
	
		TextureOld* texture = new TextureOld(image, glm::ivec2(6, 6), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakePatternTexture3(GLubyte byteIntesity1, GLubyte byteIntesity2, GLubyte byteIntesity3){
		GLubyte image[8 * 8] = {
			byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1,
			byteIntesity3, byteIntesity1, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity1, byteIntesity3,
			byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity3, byteIntesity2,
			byteIntesity2, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity2,			
			byteIntesity2, byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity2,
			byteIntesity2, byteIntesity3, byteIntesity1, byteIntesity3, byteIntesity3, byteIntesity1, byteIntesity3, byteIntesity2,
			byteIntesity3, byteIntesity1, byteIntesity3, byteIntesity1, byteIntesity1, byteIntesity3, byteIntesity1, byteIntesity3,
			byteIntesity1, byteIntesity3, byteIntesity2, byteIntesity2, byteIntesity2, byteIntesity2, byteIntesity3, byteIntesity1,
		};
	
		TextureOld* texture = new TextureOld(image, glm::ivec2(8, 8), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::MakeLinearFaded(float startIntensity, float endIntensity, unsigned resolution){
		std::vector<GLubyte> image(resolution);
		for (unsigned i = 0; i < resolution; i++) {
			image[i] = lerp(startIntensity, endIntensity,  i / (float)resolution) * 255;
		}
		TextureOld* texture = new TextureOld(image.data(),  glm::ivec2(1, resolution), 1);
		return texture;
	}
	
	TextureOld* TextureGenerator::Diagonal(
		DiagonalTextureTypes type,
		float color1Intesity /*= 1.0f*/,
		float color2Intesity /*= 0.5f*/,
		float color3Intesity /*= 0.3f*/){
	
		GLubyte byteIntesity1 = (GLubyte)(color1Intesity * 255);
		GLubyte byteIntesity2 = (GLubyte)(color2Intesity * 255);
		GLubyte byteIntesity3 = (GLubyte)(color3Intesity * 255);
	
		switch (type) {
		case DIAG_TEXT_1: return MakeDiagTexture1(byteIntesity1, byteIntesity2);
		case DIAG_TEXT_2: return MakeDiagTexture2(byteIntesity1, byteIntesity2, byteIntesity3);
		case DIAG_TEXT_3: return MakeDiagTexture3(byteIntesity1, byteIntesity2, byteIntesity3);
		case DIAG_TEXT_4: return MakeDiagTexture4(byteIntesity1, byteIntesity2);
		case DIAG_TEXT_5: return MakeDiagTexture5(byteIntesity1, byteIntesity2, byteIntesity3);
		case DIAG_TEXT_6: return MakeDiagTexture6(byteIntesity1, byteIntesity2, byteIntesity3);
		case DIAG_TEXT_7: return MakeDiagTexture7(byteIntesity1, byteIntesity2);
		default: return nullptr;	/// \todo throw exeption or return default texture
		};
	}
	
	
	
	TextureOld* TextureGenerator::Pattern(
		PatternTextureType type,
		float color1Intesity /*= 1.0f*/,
		float color2Intesity /*= 0.5f*/,
		float color3Intesity /*= 0.3f*/){
	
		GLubyte byteIntesity1 = (GLubyte)(color1Intesity * 255);
		GLubyte byteIntesity2 = (GLubyte)(color2Intesity * 255);
		GLubyte byteIntesity3 = (GLubyte)(color3Intesity * 255);
	
		switch (type) {
		case PATT_TEXT_1: return MakePatternTexture1(byteIntesity1, byteIntesity2, byteIntesity3);
		case PATT_TEXT_2: return MakePatternTexture2(byteIntesity1, byteIntesity2, byteIntesity3);
		case PATT_TEXT_3: return MakePatternTexture3(byteIntesity1, byteIntesity2, byteIntesity3);
		default: return nullptr;	/// \todo throw exeption or return default texture
		};
	}
	
	TextureOld* TextureGenerator::Faded(
		FadeTextureType type,
		float startIntensity,
		float endIntensity,
		unsigned resolution){
	
		switch (type) {
		case FADE_TEXT_LINEAR: return MakeLinearFaded(startIntensity, endIntensity, resolution);
	
		default: return nullptr;
		}
	}
	
	TextureOld* TextureGenerator::SimpleTexture(
		unsigned type,
		float color1Intesity,
		float color2Intesity,
		float color3Intesity){
	
		GLubyte byteIntesity1 = (GLubyte)(color1Intesity * 255);
		GLubyte byteIntesity2 = (GLubyte)(color2Intesity * 255);
		GLubyte byteIntesity3 = (GLubyte)(color3Intesity * 255);
	
		switch (type) {
		case DIAG_TEXT_1: return MakeDiagTexture1(byteIntesity1, byteIntesity2);
		case DIAG_TEXT_2: return MakeDiagTexture2(byteIntesity1, byteIntesity2, byteIntesity3);
		case DIAG_TEXT_3: return MakeDiagTexture3(byteIntesity1, byteIntesity2, byteIntesity3);
		case DIAG_TEXT_4: return MakeDiagTexture4(byteIntesity1, byteIntesity2);
		case DIAG_TEXT_5: return MakeDiagTexture5(byteIntesity1, byteIntesity2, byteIntesity3);
		case DIAG_TEXT_6: return MakeDiagTexture6(byteIntesity1, byteIntesity2, byteIntesity3);
		case DIAG_TEXT_7: return MakeDiagTexture7(byteIntesity1, byteIntesity2);
		case PATT_TEXT_1: return MakePatternTexture1(byteIntesity1, byteIntesity2, byteIntesity3);
		case PATT_TEXT_2: return MakePatternTexture2(byteIntesity1, byteIntesity2, byteIntesity3);
		case PATT_TEXT_3: return MakePatternTexture3(byteIntesity1, byteIntesity2, byteIntesity3);
	
		default: return nullptr;
		}
	}

} }