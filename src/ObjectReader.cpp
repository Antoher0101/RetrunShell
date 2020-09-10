#include "ObjectReader.h"



ObjectReader::ObjectReader(const std::string& objName)
{
	std::string ObjectName;
	
	std::string path = "resource/model/" + objName + ".obj" ;
	try
	{
		std::ifstream objFile(path.c_str(), std::ios_base::in);
		objFile.exceptions(std::ifstream::eofbit);
		if (objFile.is_open())
		{
			std::string strType;
			std::string str;
			while (std::getline(objFile, str))
			{
					// Checking the type of the current line
				sscanf_s(str.c_str(), "%s", strType.c_str(), 10);
				
					// literal 'v' sets vertex coordinates 
				if (!strncmp(strType.c_str(), "v", 2)) {
					sscanf_s(str.c_str(), "%*s %f %f %f", &tmp_x_, &tmp_y_, &tmp_z_);
					vertexData.emplace_back(tmp_x_,tmp_y_,tmp_z_);
				}
					// literal 'vt' sets texture coordinates
				else if (!strncmp(strType.c_str(), "vt", 2)) {
					sscanf_s(str.c_str(), "%*s %f %f %f", &tmp_x_, &tmp_y_, &tmp_z_);
					VTextureData.emplace_back( tmp_x_, tmp_y_, tmp_z_ );
				}
				// literal 'vn' sets normals
				else if (!strncmp(strType.c_str(), "vn", 2)) {
					sscanf_s(str.c_str(), "%*s %f %f %f", &tmp_x_, &tmp_y_, &tmp_z_);
					VNormalData.emplace_back(tmp_x_, tmp_y_, tmp_z_);
				}
				// literal 'vp' sets normals (idk yet for what)
				else if (!strncmp(strType.c_str(), "vp", 2)) {
					continue;
					sscanf_s(str.c_str(), "%*s %f %f %f", &tmp_x_, &tmp_y_, &tmp_z_);
					VNormalData.emplace_back(tmp_x_, tmp_y_, tmp_z_);
				}
				// literal 'f' sets indices of faces for build a triangle 
				else if (!strncmp(strType.c_str(), "f", 1)) {
					
					// VERTICLES//NORMALS ! WITHOUT TEXTURE COORDINATES
				if (str.find("//") != std::string::npos)
				{
					sscanf_s(str.c_str(), "%*s %u//%*u %u//%*u %u//%*u", &iv_, &iv1_, &iv2_);
				}
					// VERTICLES ONLY
				else
				{
					sscanf_s(str.c_str(), "%*s %u %u %u", &iv_, &iv1_, &iv2_);
				}
					VertIndices.emplace_back(iv_ - 1);
					VertIndices.emplace_back(iv1_ - 1);
					VertIndices.emplace_back(iv2_ - 1);
				}
					// Read and write the name of object from file
				else if (!strncmp(strType.c_str(), "o", 1)) {
					this->objectName += str + "\n";
				}
					// Read and write the comment from file 
				else if (!strncmp(strType.c_str(),"#",1)) {
					this->objectInfo += str + "\n";
				}
				else if (!strncmp(strType.c_str(), "s", 1)) {
					continue;
				}
				//std::cout << str << std::endl;
				
				if (objFile.eof())
					break;
			}
		}
		objFile.close();
	}
	/*
	 * Need to fix this shit later
	 */
	catch (std::ios_base::failure&)
	{
		//std::cerr << "Error of reading file \"" + objName + ".obj\"" << std::endl << fail.what() << std::endl;
	}
	
}

std::vector<glm::vec3> ObjectReader::getVertexData()
{
	return vertexData;
}

std::vector<glm::vec3> ObjectReader::getVTextureData()
{
	return VTextureData;
}

std::vector<glm::vec3> ObjectReader::getVNormalData()
{
	return VNormalData;
}

std::vector<unsigned> ObjectReader::getVertIndices()
{
	return VertIndices;
}

std::vector<unsigned> ObjectReader::getNormIndices()
{
	return NormIndices;
}

std::string ObjectReader::getObjectInfo()
{
	return objectInfo;
}

std::string ObjectReader::getObjectName()
{
	return objectName;
}

ObjectReader::~ObjectReader()
{
}
