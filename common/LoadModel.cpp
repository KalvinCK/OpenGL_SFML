#include <vector>
#include <stdio.h>
#include <string.h>
#include <map>
#include <cstring>
#include <iostream>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "LoadModel.hpp"


// bool loadOBJ( const char * path, vector<vec3> & out_vertices, vector<vec2> & out_uvs, vector<vec3> & out_normals )
void loadOBJ( const char * path, ModelTemp & modelObj)
{
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("impossivel abrir o arquivo\n");
		getchar();
		exit(0);
	}

	while( 1 ){
		char lineHeader[128];

		// lê a primeira palavra da linha
		int res = fscanf(file, "%s", lineHeader);

		if (res == EOF)
			break; // EOF = final do arquivo, encerra o laço

		// else : analisa lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				printf("O arquivo não pode ser lido pelo nosso analisador\n");
				fclose(file);
				return exit(0);
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	// Para cada vertice de cada triângulo
	for( unsigned int i=0; i<vertexIndices.size(); i++ )
	{
		// Obetem os indices de seus atributos
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Obtem os atributos graças ao indice
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// coloca os atributos nos buffers
		modelObj.vertices.push_back(vertex);
		modelObj.uvs.push_back(uv);
		modelObj.normals.push_back(normal);
	
	}
	// fechamos o arquivo, nao e mais nescessario.
	fclose(file);

}
// ALGORITMO - indexacao de modelo
//  Para cada vértice de entrada
//	Tente encontrar um vértice semelhante ( = igual para todos os atributos ) entre todos aqueles que já produzimos
//	Se encontrado :
//		Um vértice semelhante já está no VBO, use-o!
//	Se não for encontrado:
//		Nenhum vértice semelhante encontrado, adicione-o ao VBO
struct PackedVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const
	{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
	};
};

bool getSimilarVertexIndex_fast( PackedVertex & packed, map<PackedVertex,unsigned short> & VertexToOutIndex,unsigned short & result)
{
	map<PackedVertex,unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if ( it == VertexToOutIndex.end() ){
		return false;
	}else{
		result = it->second;
		return true;
	}
}
void modelIndexing(ModelTemp & ModelInput, ModelIndexer & ModelIndicesOut)
{
	// map chave -> valor, o valor da chave e constante nao pode ser modificado
	map<PackedVertex,unsigned short> VertexToOutIndex;

	// Para cada vértice de entrada
	for ( unsigned int i=0; i<ModelInput.vertices.size(); i++ )
	{
		PackedVertex packed = {ModelInput.vertices[i], ModelInput.uvs[i], ModelInput.normals[i]};
		
		unsigned short index; // Tente encontrar um vértice semelhante em out_XXXX

		if(getSimilarVertexIndex_fast( packed, VertexToOutIndex, index)) // Um vértice semelhante já está no VBO, use-o!
		{
			ModelIndicesOut.indices.push_back( index );
		}
		else // Caso contrário, ele precisa ser adicionado nos dados de saída.
		{ 
			ModelIndicesOut.indexed_vertices.push_back( ModelInput.vertices[i]);
			ModelIndicesOut.indexed_uvs.push_back( ModelInput.uvs[i]);
			ModelIndicesOut.indexed_normals.push_back( ModelInput.normals[i]);

			unsigned short newindex = (unsigned short)ModelIndicesOut.indexed_vertices.size() - 1;

			ModelIndicesOut.indices.push_back( newindex );

			VertexToOutIndex[ packed ] = newindex;
		}
	}
	
	ModelInput.vertices.clear();
	ModelInput.uvs.clear();
	ModelInput.normals.clear();
}