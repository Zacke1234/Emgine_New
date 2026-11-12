#pragma once
#include "vector"
#include "Message.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <list>
#include "fstream"
#include <vec3.hpp>
#include <string>
#include "Mesh/Mesh.h"
#include "Structs/Face.h"
#include "Structs/Vertex.h"
#include "Structs/VertRef.h"
#include "Enums/E_MeshLoadStage.h"
#include <fbxsdk/fbxsdk.h>


//#include "lib\include\fbxsdk.h"
// $(SolutionDir)Dependencies\lib\libfbxsdk-mt.lib

class MeshLoader
{
public:
	std::string name;
	std::string type;

	std::vector<Vertex> tmp;
	std::vector<unsigned int> temp_elements;
	std::vector<Vertex> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	std::vector<Face> temp_faces;
	std::vector<glm::vec3> temp_position;
	std::string face_result;

	MeshLoadStage stage;

	FbxManager* SdkManager;
	FbxScene* PScene;
	FbxImporter* Importer;
	FbxAnimLayer* CurrentAnimLayer;
	FbxNode* SelectedNode;
	FbxMesh* Pmesh;

	bool ignore = false;

	MeshLoader();
	~MeshLoader();

	virtual bool WriteObjToBinary(std::ofstream& filepathOut, std::string fileString, Mesh* mesh);
	virtual bool ReadObjToBinary(std::string fileString, std::ifstream& fstreamPath, Mesh* mesh);
	bool ObjParser(std::string fileName, Mesh* mesh);
	bool BinParser(std::string fileName, Mesh* mesh);
	void ParseFaceIndices(const std::string& string, Face& face, int vertexIndex);
	void CalculateTangent(Vertex& A, const Vertex&  B, const Vertex& C);
	bool FbxParser(std::string fileName, Mesh* mesh);
	void FbxInit(FbxManager*& pManager, FbxScene*& pScene);
	void GetNormal(FbxNode* pNode, Mesh* myMesh);
	//void SmoothingNormal(FbxManager* pSdkManager, FbxNode* pNode, bool pCompute = false, bool pConvertToSmoothingGroup = false, Mesh* mymesh = NULL);
	void GetUv(FbxNode* pNode, Mesh* myMesh, FbxMesh* pMesh);
	void SaveUvInfo(FbxNode* pNode, Mesh* myMesh, FbxMesh* pMesh);
	void GetBinormal(FbxNode* pNode, Mesh* myMesh);
	void GetTangent(FbxNode* pNode, Mesh* myMesh);

	void GetFaces(FbxNode* pNode, Mesh* myMesh, FbxMesh* mesh);

	bool GetFBXInfo(FbxNode* node, Mesh* mesh);

	void GetFbxMesh(FbxNode* node, std::vector<Mesh>& meshes);
	
	std::string temp_fileName;
};



