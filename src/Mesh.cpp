#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<Texture>> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int roughnessNr = 1;
	unsigned int aoNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++ ) {
		std::string number;
		std::string name = textures[i]->GetType();

		if (name == "diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "specular")
			number = std::to_string(specularNr++);
		else if (name == "normal")
			number = std::to_string(normalNr++);
		else if (name == "roughness")
			number = std::to_string(roughnessNr++);
		else if (name == "ao")
			number = std::to_string(aoNr++);

		shader.SetInt((name + number).c_str(), i);
		textures[i]->Bind(i);
	}

	m_VAO->Bind();
	Renderer renderer;
	renderer.Draw(*m_VAO, shader, static_cast<GLint>(indices.size()), *m_EBO);
	m_VAO->Unbind();
}

void Mesh::setupMesh()
{
	m_VAO = std::make_unique<VertexArray>();
	m_VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(Vertex));
	m_EBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());

	VertexBufferLayout layout;

	layout.Push<float>(3, 0); // Position
	layout.Push<float>(3, 0); // Normal
	layout.Push<float>(2, 0); // TexCoords

	m_VAO->AddBuffer(*m_VBO, layout);
}
