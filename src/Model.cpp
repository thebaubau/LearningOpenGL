#include "Model.h"

void Model::Draw(Shader& shader)
{
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
        m_Meshes[i].Draw(shader);
}

void Model::loadModel(std::string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('\\'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(processMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process material

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        // Diffuse
        std::vector<std::shared_ptr<Texture>> diffuseMaps = loadMaterialTextures(material,
            aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Specular
        std::vector<std::shared_ptr<Texture>> specularMaps = loadMaterialTextures(material,
            aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        // Normal
        std::vector<std::shared_ptr<Texture>> normalMaps = loadMaterialTextures(material,
            aiTextureType_HEIGHT, "normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        // Roughness (often stored as shininess in Assimp)
        std::vector<std::shared_ptr<Texture>> roughnessMaps = loadMaterialTextures(material,
            aiTextureType_SHININESS, "roughness");
        textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());

        // Ambient
        std::vector<std::shared_ptr<Texture>> ambientMaps = loadMaterialTextures(material,
            aiTextureType_AMBIENT, "ao");
        textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<std::shared_ptr<Texture>> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string texturePath = directory + '\\' + str.C_Str();
        bool skip = false;

        for (unsigned int j = 0; j < m_LoadedTextures.size(); j++)
        {
            if (std::strcmp(m_LoadedTextures[j]->GetFilePath().c_str(), texturePath.c_str()) == 0)
            {
                textures.emplace_back(m_LoadedTextures[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {   
            auto texture = std::make_shared<Texture>(texturePath, typeName);
            m_LoadedTextures.emplace_back(texture);
            textures.push_back(m_LoadedTextures.back());
        }
    }

    return textures;
}
