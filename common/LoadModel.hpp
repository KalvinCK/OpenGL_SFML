#ifndef LOADMODEL_H
#define LOADMODEL_H

typedef struct ModelTemp
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

} ModelTemp;

typedef struct ModelIndexer
{
	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

} ModelIndexer;


void loadOBJ(const char * path, ModelTemp & modelObj);
void modelIndexing(ModelTemp & ModelInput, ModelIndexer & ModelIndicesOut);


#endif // !LOADMODEL_H