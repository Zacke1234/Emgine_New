#pragma once
enum MeshLoadStage {
	ParsingObj = 0,
	ReadingVertices,
	ReadingFaces,
	ReadingUVs,
	ReadingNormals,
	InitialisingMesh,
	BinaryWriting,
	BinaryParsing,
	MeshLoaded
};

