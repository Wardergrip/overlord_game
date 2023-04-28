#include "stdafx.h"
#include "PxMeshLoader.h"

//CONVEX MESH
//***********
PxConvexMesh* PxConvexMeshLoader::LoadContent(const ContentLoadInfo& loadInfo)
{
	auto inputStream = PxDefaultFileInputData(loadInfo.assetFullPath.string().c_str());
	return PxGetPhysics().createConvexMesh(inputStream);
}

//TRIANGLE MESH
//*************
PxTriangleMesh* PxTriangleMeshLoader::LoadContent(const ContentLoadInfo& loadInfo)
{
	auto inputStream = PxDefaultFileInputData(loadInfo.assetFullPath.string().c_str());
	return PxGetPhysics().createTriangleMesh(inputStream);
}