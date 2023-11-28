#include "RenderMesh.h"
#include <sstream>

#include "RenderShaderProgram/RenderShaderProgram.h"


using namespace SimpleRender;
using namespace std;


RenderMesh::RenderMesh(const aiScene* scene, const aiMesh* mesh,  std::vector<unsigned int> textureIndices)
{
	this->textureIndices = textureIndices;
	InitVertices(mesh);
	InitBuffers();

}

RenderMesh::~RenderMesh()
{
}

void RenderMesh::InitVertices(const aiMesh* mesh)
{
	vertices.reserve(mesh->mNumVertices);

	// Add vertices
	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		RenderVertex vertex;

		auto pos = mesh->mVertices[i];
		auto normal = mesh->mNormals[i];

		
		vertex.position.x = pos.x;
		vertex.position.y = pos.y;
		vertex.position.z = pos.z;

		vertex.normal.x = normal.x;
		vertex.normal.y = normal.y;
		vertex.normal.z = normal.z;

		// Add texture coordinates if exists
		if(mesh->mTextureCoords[0])
		{
			auto coords = mesh->mTextureCoords[0][i];
			vertex.texturePosition.x = coords.x;
			vertex.texturePosition.y = coords.y;
		}
		else
		{
			vertex.texturePosition.x = 0.0f;
			vertex.texturePosition.y = 0.0f;
		}


		vertices.push_back(vertex);

	}

	// Add element indices for element buffer
	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for(unsigned int j = 0; j < face.mNumIndices; j++)
		{
			elementIndices.push_back(face.mIndices[j]);
		}
	}



}

void RenderMesh::InitBuffers()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(BufferType::LEN, buffers);

	// Generate vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[BufferType::VBO]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RenderVertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Generate element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[BufferType::EBO]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elementIndices.size(), &elementIndices[0], GL_STATIC_DRAW);



	glEnableVertexAttribArray(0);		// Enable position
	glEnableVertexAttribArray(1);		// Enable normal
	glEnableVertexAttribArray(2);		// Enable texture coordinate

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(RenderVertex), (void*)(offsetof(RenderVertex, position)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(RenderVertex), (void*)(offsetof(RenderVertex, normal)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(RenderVertex), (void*)(offsetof(RenderVertex, texturePosition)));



	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}



void RenderMesh::Draw(RenderShaderProgram* program, std::vector<RenderTexture*> textureMap)
{
	glUseProgram(program->ID());
	
	// Bind textures
	unsigned int diffNo = 0;
	unsigned int specNo = 0;
	unsigned int globalTexID = 0;

	for(unsigned int& index : textureIndices)
	{

		RenderTexture* texture = textureMap[index];
		unsigned int texNo;

		if(texture->Type() == TextureType::Diffuse)
			texNo = diffNo++;
		else if(texture->Type() == TextureType::Specular)
			texNo = specNo++;


		ostringstream stream;
		stream << "material." << RenderTexture::TextureTypeToString(texture->Type()) << texNo;
		
		string location = stream.str();


		glActiveTexture(GL_TEXTURE0 + globalTexID);
		glUniform1f(glGetUniformLocation(program->ID(), location.c_str()), globalTexID++);
		glBindTexture(GL_TEXTURE_2D, texture->ID());
		

	}

	//cout << glGetError() << endl;
	//char log[512];
	//glGetProgramInfoLog(program->ID(), 512, 0, log);
	//cout << log << endl;

	glBindVertexArray(vertexArray);

	glDrawElements(GL_TRIANGLES, elementIndices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}





