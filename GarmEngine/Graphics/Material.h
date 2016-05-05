#pragma once
#include <gl/glew.h>
#include <string>
#include <vector>
#include "../Math.h"
namespace garm { namespace graphics {


	class Material {

	};

	//possible way of doing material....maybe later
	/*
	class Texture;

	class MaterialData {
		friend class Material;
		explicit MaterialData(const int& v){			valueType = GL_INT;			value.intValue[0] = v; }
		explicit MaterialData(const float& v){			valueType = GL_FLOAT;		value.floatValue[0] = v; }
		explicit MaterialData(const glm::ivec2& v){		valueType = GL_INT_VEC2;	value.intValue[0] = v[0]; value.intValue[1] = v[1]; }
		explicit MaterialData(const glm::ivec3& v){		valueType = GL_INT_VEC3;	value.intValue[0] = v[0]; value.intValue[1] = v[1]; value.intValue[2] = v[2]; }
		explicit MaterialData(const glm::ivec4& v){		valueType = GL_INT_VEC4;	value.intValue[0] = v[0]; value.intValue[1] = v[1]; value.intValue[2] = v[2];  value.intValue[3] = v[3]; }
		explicit MaterialData(const glm::vec2& v){		valueType = GL_FLOAT_VEC2;	value.floatValue[0] = v[0]; value.floatValue[1] = v[1]; }
		explicit MaterialData(const glm::vec3& v){		valueType = GL_FLOAT_VEC3;	value.floatValue[0] = v[0]; value.floatValue[1] = v[1]; value.floatValue[2] = v[2]; }
		explicit MaterialData(const glm::vec4& v){		valueType = GL_FLOAT_VEC4;	value.floatValue[0] = v[0]; value.floatValue[1] = v[1]; value.floatValue[2] = v[2];  value.floatValue[3] = v[3]; }
		explicit MaterialData(const Texture* v){		valueType = GL_SAMPLER_2D;	value.texturePtr = v; }
		explicit MaterialData(const glm::mat2& v){		valueType = GL_FLOAT_MAT2;	value.floatValue[0] = v[0][0]; value.floatValue[1] = v[0][1]; value.floatValue[2] = v[1][0];  value.floatValue[3] = v[1][1];}
		explicit MaterialData(const bool& v){			valueType = GL_BOOL;		value.boolValue = v;}

		union Type {
			int boolValue;
			int intValue[4];
			float floatValue[4];
			Texture* texturePtr;
		} value;
		GLenum valueType;
		std::string uniformName;
	};

	class Material {
		std::vector<MaterialData> m_materialData;

	public:
		void AddMaterialData(std::string name, const int& v){			m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const float& v){			m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const glm::ivec2& v){	m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const glm::ivec3& v){	m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const glm::ivec4& v){	m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const glm::vec2& v){		m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const glm::vec3& v){		m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const glm::vec4& v){		m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const Texture* v){		m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const glm::mat2& v){		m_materialData.push_back(MaterialData(v)); }
		void AddMaterialData(std::string name, const bool& v){			m_materialData.push_back(MaterialData(v)); }
	};
	*/
} }