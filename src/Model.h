#pragma once
#include "Shader.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
	std::vector<std::shared_ptr<Texture>> m_LoadedTextures;
	std::vector<Mesh> m_Meshes;
	std::string directory;

	Model(const std::string& path) {
		loadModel(path);
	}
	Model(const char* path) {
		loadModel(std::string(path));
	}
	
	void Draw(Shader& shader);
		
private:

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};