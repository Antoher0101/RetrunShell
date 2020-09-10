#pragma once
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class ObjectReader
{
	std::string buff;

	std::vector<glm::vec3> vertexData = {};
	std::vector<glm::vec3> VTextureData = {};
	std::vector<glm::vec3> VNormalData = {};
	std::vector<unsigned> VertIndices = {};
	std::vector<unsigned> NormIndices = {};
	std::string objectInfo;
	std::string objectName;

	float tmp_x_ = 0.f;
	float tmp_y_ = 0.f;
	float tmp_z_ = 0.f;

	unsigned iv_ = 0;
	unsigned iv1_ = 0;
	unsigned iv2_ = 0;
public:
	
	std::vector<glm::vec3> getVertexData();
	std::vector<glm::vec3> getVTextureData();
	std::vector<glm::vec3> getVNormalData();
	
	std::vector<unsigned> getVertIndices();
	std::vector<unsigned> getNormIndices();//

	std::string getObjectInfo();
	std::string getObjectName();
	
	ObjectReader(const std::string& objName);
	~ObjectReader();
};

