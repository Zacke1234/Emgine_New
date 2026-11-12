#include "MeshLoader.h"
#include "fstream"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <Texture.h>
#include <Object.h>
#include "MeshManager.h"
#include <bitset>
#include <cassert>
#include <gl/GL.h>
using namespace std;

// do breakpoints
int n;
MeshLoader::MeshLoader()
{

}

MeshLoader::~MeshLoader()
{

}

// https://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

bool runOnce = false;
bool MeshLoader::ObjParser(std::string fileName, Mesh* INmesh)
{

	if (INmesh == nullptr)
	{
		return false;
	}

	Mesh& mesh = *INmesh;

	std::ifstream file(fileName);
	
	std::string line;
	
	if (!file.is_open() && ignore == false)
	{
		std::cerr <<  "Failed to open file: " << fileName << std::endl;
		return false;
	}
	
	while (std::getline(file, line)){
		std::istringstream iss(line);
		std::string prefix;
		iss >> prefix;
		
		if (prefix == "v")
		{
			
			glm::vec3 position;
			iss >> position.x >> position.y >> position.z;
			
			temp_position.push_back(position);
			mesh.position.push_back(position);
			
			
		}
		if (prefix == "f")
		{
			std::vector<VertRef> ref;


			Face face;
			int vertexIndex = 0;
			std::string newFace;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;

			iss >> newFace;
			ParseFaceIndices(newFace, face, vertexIndex);
			vertexIndex++;
			
			iss >> newFace;
		
			temp_faces.push_back(face);
			mesh.faces.push_back(face);	
			
		}
		if (prefix == "vt") 
		{
			
			glm::vec2 UV;
			iss >> UV.x >> UV.y;

			temp_uvs.push_back(UV);
			mesh.uvs.push_back(UV);
		}

		if (prefix == "vn")
		{
			
			glm::vec3 NORMAL;
			iss >> NORMAL.x >> NORMAL.y >> NORMAL.z;

			temp_normals.push_back(NORMAL);
			mesh.normals.push_back(NORMAL);
		}
		if (prefix == "mtllib") // load in the material from the file onto the mesh
		{
			
			
			std::cout << "Material", "\n";
			

		}
		
	}


	file.close();
	
	
	for (int i = 0; i < mesh.faces.size(); i++)
	{
		Vertex vertices[3];
	
		Face face = mesh.faces[i];

		for (int e = 0; e < 3; e++)
		{
			int index = face.positionIndices[e];
			Vertex& v = vertices[e];

			if (index != -1 && index != 0)
			{
				v.position = mesh.position[index - 1];
				
			}

			if (index == 0)
			{
				v.position = mesh.position[index];
			}

			index = face.normalIndices[e];

			if (index != -1 && index != 0)
			{
				v.normal = mesh.normals[index - 1];



			}
			if (index == 0)
			{
				v.position = mesh.position[index];
			}

			index = face.uvIndices[e];

			if (index != -1 && index != 0)
			{

				v.uv = mesh.uvs[index - 1];

			}
			if (index == 0)
			{
				v.position = mesh.position[index];
			}



		}
		// calculate tangents

		CalculateTangent(vertices[0], vertices[1], vertices[2]);
		CalculateTangent(vertices[1], vertices[0], vertices[2]);
		CalculateTangent(vertices[2], vertices[1], vertices[0]);

		for (int e = 0; e < 3; e++)
		{
			
			Vertex& v = vertices[e];
			

			mesh.data.push_back(v.position.x); // Important
			mesh.data.push_back(v.position.y);
			mesh.data.push_back(v.position.z);
				

			mesh.data.push_back(v.normal.x);
			mesh.data.push_back(v.normal.y);
			mesh.data.push_back(v.normal.z);

   			
			mesh.data.push_back(v.uv.x);
			mesh.data.push_back(v.uv.y);


			// push back tangents

			mesh.data.push_back(v.tangent.x);
			mesh.data.push_back(v.tangent.y);
			mesh.data.push_back(v.tangent.z);

			mesh.data.push_back(v.binormal.x);
			mesh.data.push_back(v.binormal.y);
			mesh.data.push_back(v.binormal.z); // Important
			
			mesh.elements.push_back(mesh.numberVertices);
			temp_elements.push_back(mesh.numberVertices);
			
			
			
			//temp_vertices.push_back(vertices);

			mesh.numberVertices++;
			
		}
		
	}
	
	temp_faces.clear();
	temp_normals.clear();
	temp_position.clear();
	temp_uvs.clear();
	temp_vertices.clear();
	temp_elements.clear();

	return true;
}

bool MeshLoader::BinParser(std::string bineFileName, Mesh* mesh)
{
	std::ifstream binFile(bineFileName);
	std::string line;
	if (!binFile.is_open())
	{
		std::cout << "Filename empty" << std::endl;
		return false;
	}

	if (mesh == nullptr)
	{
		std::cout << "mesh is nullptr" << std::endl;
		return false;
	}

	// Parse the Binary file back into the human readable OBJ format and initialise the mesh with that exact data.

	int dataLength = mesh->data.size(); // redo this for the cache loading
	int elementsLength = mesh->elements.size();
	int positionLength = mesh->position.size();
	int normalsLength = mesh->normals.size();
	int uvLength = mesh->uvs.size();
	int facesLength = mesh->faces.size();

	
	for (int i = 0; i < positionLength; i++)
	{


		glm::vec3 positionBinary = mesh->position[i];


		binFile.read((char*)(&positionBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < facesLength; i++)
	{


		Face facesBinary = mesh->faces[i];


		binFile.read((char*)(&facesBinary),
			sizeof(Face));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < uvLength; i++)
	{


		glm::vec2 uvBinary = mesh->uvs[i];


		binFile.read((char*)(&uvBinary),
			sizeof(glm::vec2));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < normalsLength; i++)
	{


		glm::vec3 normalBinary = mesh->normals[i];


		binFile.read((char*)(&normalBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < dataLength; i++)
	{

		float dataBinary = mesh->data[i];

		binFile.read((char*)(&dataBinary),
			sizeof(float));

	}




	mesh->InitialiseMesh();
	return false;
}

static inline std::vector<std::string> SplitString(const std::string& str, char delimeter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimeter))
	{
		tokens.push_back(token);
	
	}
	return tokens;

}

void MeshLoader::ParseFaceIndices(const std::string& string, Face& face, int vertexIndex) 
{
	
	/*auto foundIndex = string.find('/');
	face_result = string.substr  (0, foundIndex);*/

	char del = '/';

	std::string indexString = "";
	int indexCounter = 0;
	n = 0;
	std::vector<std::string> tokens = SplitString(string, del);
	
	for (std::string& token : tokens)
	{
		int index = std::atoi(token.c_str());
		if (indexCounter == 0)
		{
			face.positionIndices[vertexIndex] = index;
		}
		else if (indexCounter == 2)
		{
			face.normalIndices[vertexIndex] = index;
		}
		else if (indexCounter == 1)
		{
			face.uvIndices[vertexIndex] = index;
		}
		indexCounter++;
		n++;
	}
}


void MeshLoader::CalculateTangent(Vertex& A, const Vertex& B, const Vertex& C)
{

	glm::vec3 dpAB = B.position - A.position;

	glm::vec3 dpAC = C.position - A.position;

	glm::vec2 dtAB = B.uv - A.uv;

	glm::vec2 dtAC = C.uv - A.uv;

	float r = 1.0f / (dtAB.x * dtAC.y - dtAB.y * dtAC.x);

	glm::vec3 T = (dpAB * dtAC.y - dpAC * dtAB.y) * r;

	glm::vec3 Bn = (dpAC * dtAB.x - dpAB * dtAC.x) * r;

	glm::vec3 N = (A.normal);

	glm::vec3 X = glm::cross(N, T);

	T = glm::cross(X, N);
	T = glm::normalize(T);
	// get updated bi-tangent
	X = glm::cross(Bn, N);
	Bn = glm::cross(N, X);
	Bn = glm::normalize(Bn);

	A.tangent = T;
	A.binormal = Bn;


}

bool MeshLoader::FbxParser(std::string fileName, Mesh* mesh)
{

	
	
	FbxInit(SdkManager, PScene);

	FbxNode* rootNode;// = PScene->GetRootNode();
	
	const char* charFileName = fileName.c_str();
	if (SdkManager)
	{
		int IFileFormat = -1;
		
		Importer = FbxImporter::Create(SdkManager, "");
		if (!SdkManager->GetIOPluginRegistry()->DetectReaderFileFormat(charFileName, IFileFormat))
		{
			IFileFormat = SdkManager->GetIOPluginRegistry()->FindReaderIDByDescription("FBX binary (*.fbx)");;
		}

		if (Importer->Initialize(charFileName, IFileFormat) == true)
		{
			std::cout << "Importing file: ";
			std::cout << charFileName << std::endl;
			std::cout << "Loading " << std::endl;
		}
		else
		{
			std::cout << "Unable to open file: ";
			std::cout << charFileName << std::endl;
			std::cout << "Error: ";
			std::cout << Importer->GetStatus().GetErrorString();
			
		}
	}
	else
	{
		std::cout << "Unable to parse fbx file";
		return false;
	}

	Importer->Import(PScene);
	Importer->Destroy();

	rootNode = PScene->GetRootNode();

	if (rootNode)
	{
		GetFBXInfo(rootNode, mesh);
	}
	
	return true;
}

void MeshLoader::FbxInit(FbxManager*& pManager, FbxScene*& pScene)
{
	pManager = FbxManager::Create();
	
	if (!pManager)
	{
		FBXSDK_printf("Error: unable to create fbx manager\n");
		exit(1);
	}
	else FBXSDK_printf("AutoDesk FBX SDK version %s\n", pManager->GetVersion());
	
	

	FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(ios);

	FbxString _1Path = FbxGetApplicationDirectory();
	pManager->LoadPluginsDirectory(_1Path.Buffer());

	pScene = FbxScene::Create(pManager, "My Scene");

	
	if (!pScene)
	{
		FBXSDK_printf("Error: Unable to create FBX scene \n");
		exit(1);
	}
}

void MeshLoader::GetNormal(FbxNode* pNode, Mesh* myMesh)
{
	if (!pNode)
		return;

	//get mesh
	FbxMesh* lMesh = pNode->GetMesh();
	if (lMesh)
	{
		//print mesh node name
		printf("current mesh node: %s\n", pNode->GetName());

		//get the normal element
		FbxGeometryElementNormal* lNormalElement = lMesh->GetElementNormal();
		FbxVector4 lNormal;
		
		if (lNormalElement)
		{
			//mapping mode is by control points. The mesh should be smooth and soft.
			//we can get normals by retrieving each control point
			if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
			{
				//Let's get normals of each vertex, since the mapping mode of normal element is by control point
				for (int lVertexIndex = 0; lVertexIndex < lMesh->GetControlPointsCount(); lVertexIndex++)
				{
					int lNormalIndex = 0;
					//reference mode is direct, the normal index is same as vertex index.
					//get normals by the index of control vertex
					if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						lNormalIndex = lVertexIndex;

					//reference mode is index-to-direct, get normals by the index-to-direct
					if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						lNormalIndex = lNormalElement->GetIndexArray().GetAt(lVertexIndex);

					//Got normals of each vertex.
					lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
					printf("normals for vertex[%d]: %f %f %f %f \n", lVertexIndex, lNormal[0], lNormal[1], lNormal[2], lNormal[3]);
					
					myMesh->normals.push_back(glm::vec3(lNormal.mData[0], lNormal.mData[1], lNormal.mData[2]));

					for (int ln = 0; ln < 3; ln++)
					{
						myMesh->data.push_back(lNormal.mData[ln]);
					}
					
					
					
					//add your custom code here, to output normals or get them into a list, such as KArrayTemplate<KFbxVector4>
					//. . .
				}//end for lVertexIndex
			}//end eBY_CONTROL_POINT
			//mapping mode is by polygon-vertex.
			//we can get normals by retrieving polygon-vertex.
			else if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
			{
				int lIndexByPolygonVertex = 0;
				int PolygonCount = lMesh->GetPolygonCount();
				//Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
				for (int lPolygonIndex = 0; lPolygonIndex < lMesh->GetPolygonCount(); lPolygonIndex++)
				{
					//get polygon size, you know how many vertices in current polygon.
					int lPolygonSize = lMesh->GetPolygonSize(lPolygonIndex);
					//retrieve each vertex of current polygon.
					for (int i = 0; i < lPolygonSize; i++)
					{
						int lNormalIndex = 0;
						//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
						if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
							lNormalIndex = lIndexByPolygonVertex;

						//reference mode is index-to-direct, get normals by the index-to-direct
						if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
							lNormalIndex = lNormalElement->GetIndexArray().GetAt(lIndexByPolygonVertex);

						//Got normals of each polygon-vertex.
						lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
						printf("normals for polygon[%d]vertex[%d]: %f %f %f %f \n",
							lPolygonIndex, i, lNormal[0], lNormal[1], lNormal[2], lNormal[3]);

						myMesh->normals.push_back(glm::vec3(lNormal.mData[0], lNormal.mData[1], lNormal.mData[2]));
						for (int ln = 0; ln < 3; ln++)
						{
							myMesh->data.push_back(lNormal.mData[ln]);
						}
						
						
						//add your custom code here, to output normals or get them into a list, such as KArrayTemplate<KFbxVector4>
						//. . .

						lIndexByPolygonVertex++;
					}//end for i //lPolygonSize
				}//end for lPolygonIndex //PolygonCount

			}//end eBY_POLYGON_VERTEX
		}//end if lNormalElement

		for (int b = 0; b < 3; b++)
		{
			myMesh->data.push_back(lNormal.mData[b]);
		}
	}//end if lMesh

	

	//recursively traverse each node in the scene
	int i, lCount = pNode->GetChildCount();
	for (i = 0; i < lCount; i++)
	{
		GetNormal(pNode->GetChild(i), myMesh);
	}
}


void MeshLoader::GetUv(FbxNode* pNode, Mesh* myMesh, FbxMesh* pMesh)
{
	//get all UV set names
	FbxStringList lUVSetNameList;
	pMesh->GetUVSetNames(lUVSetNameList);
	FbxVector2 lUVValue;
	//iterating over all uv sets
	for (int lUVSetIndex = 0; lUVSetIndex < lUVSetNameList.GetCount(); lUVSetIndex++)
	{
		//get lUVSetIndex-th uv set
		const char* lUVSetName = lUVSetNameList.GetStringAt(lUVSetIndex);
		const FbxGeometryElementUV* lUVElement = pMesh->GetElementUV(lUVSetName);

		if (!lUVElement)
			continue;

		// only support mapping mode eBY_POLYGON_VERTEX and eBY_CONTROL_POINT
		if (lUVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
			lUVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
			return;

		//direct array, where holds the actual uv data
		const int lDataCount = lUVElement->GetDirectArray().GetCount();

		//index array, where holds the index referenced to the uv data
		const bool lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
		const int lIndexCount = (lUseIndex) ? lUVElement->GetIndexArray().GetCount() : 0;

		//iterating through the data by polygon
		const int lPolyCount = pMesh->GetPolygonCount();

		if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
			{
				// build the max index array that we need to pass into MakePoly
				const int lPolySize = pMesh->GetPolygonSize(lPolyIndex);
				for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
				{
					

					//FbxGeometryElementNormal* lNormalElement = pMesh->GetElementNormal();

					//get the index of the current vertex in control points array
					int lPolyVertIndex = pMesh->GetPolygonVertex(lPolyIndex, lVertIndex);

					//the UV index depends on the reference mode
					int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyVertIndex) : lPolyVertIndex;

					lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);
					myMesh->uvs.push_back(glm::vec2(lUVValue.mData[0], lUVValue.mData[1]));
					for (int b = 0; b < 2; b++)
					{
						myMesh->data.push_back(lUVValue.mData[b]);
					}
					//User TODO:
					//Print out the value of UV(lUVValue) or log it to a file
					//myMesh->data.push_back(lUVValue.mData[lVertIndex]);
				}
			}
		}
		else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			int lPolyIndexCounter = 0;
			for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
			{
				// build the max index array that we need to pass into MakePoly
				const int lPolySize = pMesh->GetPolygonSize(lPolyIndex);
				for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
				{
					if (lPolyIndexCounter < lIndexCount)
					{
						
						

						//the UV index depends on the reference mode
						int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyIndexCounter) : lPolyIndexCounter;

						lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

						//User TODO:
						//Print out the value of UV(lUVValue) or log it to a file
						myMesh->uvs.push_back(glm::vec2(lUVValue.mData[0], lUVValue.mData[1]));
						for (int b = 0; b < 2; b++)
						{
							myMesh->data.push_back(lUVValue.mData[b]);
						}
						//myMesh->data.push_back();
						lPolyIndexCounter++;
					}
				}
			}
		}
	}
}

void MeshLoader::SaveUvInfo(FbxNode* pNode, Mesh* myMesh, FbxMesh* pMesh)
{
}

void MeshLoader::GetBinormal(FbxNode* pNode, Mesh* myMesh)
{
	FbxMesh* pMesh = pNode->GetMesh();
}

void MeshLoader::GetTangent(FbxNode* pNode, Mesh* myMesh)
{
	FbxMesh* pMesh = pNode->GetMesh();
	for (int i = 0; i < myMesh->faces.size(); i++)
	{
		Vertex vertices[3];

		Face face = myMesh->faces[i];

		for (int e = 0; e < 3; e++)
		{
			int index = face.positionIndices[e];
			Vertex& v = vertices[e];

			if (index != -1)
			{
				v.position = myMesh->position[index - 1];

			}

			

			index = face.normalIndices[e];

			if (index != -1)
			{
				v.normal = myMesh->normals[index - 1];



			}
		

			index = face.uvIndices[e];

			if (index != -1)
			{

				v.uv = myMesh->uvs[index - 1];

			}

		}
		// calculate tangents

		CalculateTangent(vertices[0], vertices[1], vertices[2]);
		CalculateTangent(vertices[1], vertices[0], vertices[2]);
		CalculateTangent(vertices[2], vertices[1], vertices[0]);
		
		for (int e = 0; e < 3; e++)
		{
			Vertex& v = vertices[e];


			//myMesh->data.push_back(v.position.x); // Important
			//myMesh->data.push_back(v.position.y);
			//myMesh->data.push_back(v.position.z);


			//myMesh->data.push_back(v.normal.x);
			//myMesh->data.push_back(v.normal.y);
			//myMesh->data.push_back(v.normal.z);


			//myMesh->data.push_back(v.uv.x);
			//myMesh->data.push_back(v.uv.y);


			//myMesh->data.push_back(v.tangent.x);
			//myMesh->data.push_back(v.tangent.y);
			//myMesh->data.push_back(v.tangent.z);

			//myMesh->data.push_back(v.binormal.x);
			//myMesh->data.push_back(v.binormal.y);
			//myMesh->data.push_back(v.binormal.z); // Important
			

		}
		

	}
}

void MeshLoader::GetFaces(FbxNode* pNode, Mesh* myMesh, FbxMesh* mesh)
{
	
	Face face;
	int b = 0;
	int bf = 0;
	std::string indice1 = "";
	std::string total = "";
	if (mesh != NULL) {
		int polygonCount = mesh->GetPolygonCount();
		std::cout << "Mesh: " << pNode->GetName() << " has " << polygonCount << " polygons.\n";

		for (int i = 0; i < polygonCount; i++) {
			int polygonSize = mesh->GetPolygonSize(i);
			std::vector<int> vertexIndices;

			for (int j = 0; j < polygonSize; j++) {
				int vertexIndex = mesh->GetPolygonVertex(i, j);
				vertexIndices.push_back(vertexIndex);

				
			}

			//
			
			
			// Output face vertex indices
			std::cout << "Face " << i << ": ";
			//Face face = {}
			int c = 0;
			for (int idx : vertexIndices) {
				std::cout << idx << " ";
				// Work on this more
				
				
				
				
			}
			total = "";
			for (int k = 0; k <= 3; k++) // remove all the zeroes and fill it in with a different indice value
			{

				indice1 = to_string(vertexIndices[k]);
				if (indice1 == "0")
				{
					k++;
					indice1 = to_string(vertexIndices[k]);
				}
				total += indice1 + '/';
			}


			//face.normalIndices =
			ParseFaceIndices(total, face, b);
			b++;
			if (b == 3)
			{
				myMesh->faces.push_back(face);
				b = 0;
			}
			
			
			std::cout << "\n";
		}
		
	}
	
}

bool MeshLoader::GetFBXInfo(FbxNode* pNode, Mesh* myMesh)
{
	Vertex vertices[3];

	int nodeChildren = pNode->GetChildCount();
	FbxNode* childNode = 0;
	int numVertices = 0;

	for (int e = 0; e < 3; e++)
	{
		//int index = face.positionIndices[e];
		Vertex& v = vertices[e];

	}
	for (int i = 0; i < nodeChildren; i++)
	{
		childNode = pNode->GetChild(i);
		FbxMesh* mesh = childNode->GetMesh();
			
		if (mesh != NULL)
		{
			int numbVerts = mesh->GetControlPointsCount();
			for (int j = 0; j < numbVerts; j++)
			{
				FbxVector4 vert = mesh->GetControlPointAt(j);
				//FbxVector2 vert2 = mesh->GetNormals();
				int* fbx_triangle_vertices = mesh->GetPolygonVertices();
				//FbxGeometryElementNormal* normalElement = mesh->GetElementNormal();

				
				myMesh->data.push_back((float)vert.mData[0]);
				myMesh->data.push_back((float)vert.mData[1]);
				myMesh->data.push_back((float)vert.mData[2]);
				/*myMesh->data.push_back((float)vert.mData[1]);
				myMesh->data.push_back((float)vert.mData[2]);*/

				myMesh->position.push_back(glm::vec3(vert.mData[0], vert.mData[1], vert.mData[2]));
				
				
				
				// etc, remember to push it to the mesh->data



			}

			GetNormal(pNode, myMesh);
			//SmoothingNormal(SdkManager, pNode, false, false);
			GetUv(pNode, myMesh, mesh);

			GetFaces(pNode, myMesh, mesh);

			int* indices = mesh->GetPolygonVertices();
			float numIndices = mesh->GetPolygonVertexCount();
			for (int e = 0; e < numIndices; e++)
			{
				myMesh->elements.push_back(indices[e]);
				
			}
			myMesh->indexCount = numIndices;
			myMesh->numberVertices = numIndices;
		
			GetTangent(pNode, myMesh);

		}
			
	}

	
	
	this->ignore = true;
	//ObjParser(myMesh->name, myMesh);
	return true;
}

void MeshLoader::GetFbxMesh(FbxNode* node, std::vector<Mesh>& meshes)
{
	//assert(node);

	////if (FbxMesh * fbx_mesh)

	//FbxGeometryConverter gc{ SdkManager };

	//Mesh m;
}

bool MeshLoader::ReadObjToBinary(std::string objPath, std::ifstream& objReadFile, Mesh* mesh) // read
{
	ObjParser(objPath, mesh);
	int dataLength = mesh->data.size();
	int elementsLength = mesh->elements.size();
	int positionLength = mesh->position.size();
	int normalsLength = mesh->normals.size();
	int uvLength = mesh->uvs.size();
	int facesLength = mesh->faces.size();
	int verticesLength = mesh->vertices.size();
	

	if (!objReadFile.is_open())
	{
		cerr << "Error: Failed to open for parsing" << endl;
		return false;
	}
	for (int i = 0; i < positionLength; i++)
	{


		glm::vec3 positionBinary = mesh->position[i];


		objReadFile.read((char*)(&positionBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < facesLength; i++)
	{


		Face facesBinary = mesh->faces[i];


		objReadFile.read((char*)(&facesBinary),
			sizeof(Face));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < uvLength; i++)
	{


		glm::vec2 uvBinary = mesh->uvs[i];


		objReadFile.read((char*)(&uvBinary),
			sizeof(glm::vec2));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < normalsLength; i++)
	{


		glm::vec3 normalBinary = mesh->normals[i];


		objReadFile.read((char*)(&normalBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < dataLength; i++)
	{

		float dataBinary = mesh->data[i];

		objReadFile.read((char*)(&dataBinary),
			sizeof(float));

	}

	
	

	for (int i = 0; i < elementsLength; i++)
	{


		unsigned int elementsBinary = mesh->elements[i];

		
		objReadFile.read((char*)(&elementsBinary),
			sizeof(unsigned int));
		//std::cout << elementsBinary << endl;
	}

	
	
	
	//mesh->InitialiseMesh();

	
	

	objReadFile.close();
	
	return true;
}

bool MeshLoader::WriteObjToBinary(std::ofstream& binaryOutputFile, 
	std::string ObjFilePath, Mesh* mesh) // write
{
	
	

	int dataLength = mesh->data.size();
	int elementsLength = mesh->elements.size();

	int positionLength = mesh->position.size();
	int normalsLength = mesh->normals.size();
	int uvLength = mesh->uvs.size();

	int facesLength = mesh->faces.size();

	if (!binaryOutputFile.is_open())
	{
		cerr << "Error: Failed to open for parsing" << endl;
		return false;
	}
	for (int i = 0; i < positionLength; i++)
	{


		glm::vec3 positionBinary = mesh->position[i];


		binaryOutputFile.write((const char*)(&positionBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < facesLength; i++)
	{


		Face facesBinary = mesh->faces[i];


		binaryOutputFile.write((const char*)(&facesBinary),
			sizeof(Face));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < uvLength; i++)
	{


		glm::vec2 uvBinary = mesh->uvs[i];


		binaryOutputFile.write((const char*)(&uvBinary),
			sizeof(glm::vec2));
		//std::cout << elementsBinary << endl;
	}
	for (int i = 0; i < normalsLength; i++)
	{


		glm::vec3 normalBinary = mesh->normals[i];


		binaryOutputFile.write((const char*)(&normalBinary),
			sizeof(glm::vec3));
		//std::cout << elementsBinary << endl;
	}

	for (int i = 0; i < dataLength; i++)
	{
		
		float dataBinary = mesh->data[i];
		

		binaryOutputFile.write((const char*)(&dataBinary),
			sizeof(float));
		


	}
	
	for (int i = 0; i < elementsLength; i++)
	{

		
		unsigned int elementsBinary = mesh->elements[i];

		binaryOutputFile.write((const char*)(&elementsBinary),
			sizeof(unsigned int));


	}

	
	//std::cout << reinterpret_cast<char*>(&TEST) << std::endl;
	
	binaryOutputFile.close();
	return true;
	
}













