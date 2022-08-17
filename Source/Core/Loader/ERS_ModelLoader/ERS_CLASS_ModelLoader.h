//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <future>
#include <thread>
#include <chrono>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <FreeImage.h>

//#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Mesh.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_Vertex.h>
#include <ERS_STRUCT_Model.h>

#include <ERS_STRUCT_SystemUtils.h>

#include <ERS_FUNCTION_ModelMetadataDecoderManager.h>

// TESTING STUFF HERE
#include <ERS_CLASS_AssetStreamingManager.h>


#ifdef _WIN32
#include <windows.h>
const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
   DWORD dwType; // Must be 0x1000.
   LPCSTR szName; // Pointer to name (in user addr space).
   DWORD dwThreadID; // Thread ID (-1=caller thread).
   DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)


void SetThreadName(uint32_t dwThreadID, const char* threadName)
{

  // DWORD dwThreadID = ::GetThreadId( static_cast<HANDLE>( t.native_handle() ) );

   THREADNAME_INFO info;
   info.dwType = 0x1000;
   info.szName = threadName;
   info.dwThreadID = dwThreadID;
   info.dwFlags = 0;

   __try
   {
      RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
   }
   __except(EXCEPTION_EXECUTE_HANDLER)
   {
   }
}
void SetThreadName( const char* threadName)
{
    SetThreadName(GetCurrentThreadId(),threadName);
}

void SetThreadName( std::thread* thread, const char* threadName)
{
    DWORD threadId = ::GetThreadId( static_cast<HANDLE>( thread->native_handle() ) );
    SetThreadName(threadId,threadName);
}

#elif defined(__linux__)
#include <sys/prctl.h>
void SetThreadName( const char* threadName)
{
  prctl(PR_SET_NAME,threadName,0,0,0);
}

#else
void SetThreadName(std::thread* thread, const char* threadName)
{
   auto handle = thread->native_handle();
   pthread_setname_np(handle,threadName);
}
#endif




/**
 * @brief Class for loading models (fbx, gltx, etc.) based on the ASSIMP library
 * 
 */
class ERS_CLASS_ModelLoader {


private:



    ERS_STRUCT_SystemUtils* SystemUtils_; /**<System Utils Struct*/

    std::vector<std::shared_ptr<ERS_STRUCT_Model>> WorkItems_; /**<Items For The Worker To Process*/
    std::vector<long> WorkIDs_; /**<Vector Containing IDs*/
    std::vector<bool> FlipTextures_; /**<vector Containing FlipTexture For Work Items*/

    std::vector<std::shared_ptr<ERS_STRUCT_Model>> LoadedModelRefrences_; /**<Used to check if a model has already been loaded*/
    std::vector<std::shared_ptr<ERS_STRUCT_Model>> ModelsToRefrence_; /**<Models that are wating for the refs to be copied*/

    std::vector<std::thread> WorkerThreads_; /**<List of worker threads*/
    std::thread ModelRefrenceThread_; /**<Thread used to copy refrences from fully loaded models*/

    std::mutex BlockThread_; /**<Block Threads From Doing Things*/
    std::mutex BlockRefThread_; /**<Lock the ref thread from modifying non-threadsafe vars*/

    bool ExitThreads_ = false; /**<Set To True To Make Threads Quit*/
    bool EnableReferenceLoading_ = false; /**<Enable Or Disable Re-Using Assets Instead Of Reloading (Massive Performance Improvement When Enabled)*/
    bool ExitRefThread_ = false; /**Make ref matching thread exit*/


    /**
     * @brief Thread used to load model(s) from disk/database
     * 
     */
    void WorkerThread(int WorkerThreadNumber);

    /**
     * @brief Used to match references from models
     * 
     */
    void ReferenceThread();

    /**
     * @brief Load a texture given the id
     * 
     * @param ID 
     * @param FlipTextures 
     * @return ERS_STRUCT_Texture 
     */
    ERS_STRUCT_Texture LoadTexture(long ID, bool FlipTextures = false);

    /**
     * @brief Function Used To Process Subnodes Of SceneFiles.
     * 
     * @param Node 
     * @param Scene 
     */
    void ProcessNode(ERS_STRUCT_Model* Model, aiNode *Node, const aiScene *Scene);

    /**
     * @brief Process Meshes From Model.
     * 
     * @param Model
     * @param Mesh 
     * @param Scene 
     * @return ERS_STRUCT_Mesh 
     */
    ERS_STRUCT_Mesh ProcessMesh(ERS_STRUCT_Model* Model, unsigned long PreallocVertSize, unsigned long PerallocIndSize, aiMesh *Mesh, const aiScene *Scene);


    /**
     * @brief Populates Texture Request Information For The Mesh
     * 
     * @param Mat 
     * @param Mesh 
     */
    void IdentifyMeshTextures(aiMaterial* Mat, ERS_STRUCT_Mesh* Mesh);

    /**
     * @brief Checks if the target model has already been loaded, and returns refrences when completed.
     * 
     * @param AssetID 
     * @return long 
     */
    long CheckIfModelAlreadyLoaded(long AssetID);

    /**
     * @brief Adds the given model to the queue of models with refs waiting to be copied
     * 
     * @param AssetID 
     * @param Model 
     */
    void AddModelToReferenceQueue(long AssetID, std::shared_ptr<ERS_STRUCT_Model> Model);

    /**
     * @brief Creates texture pointers within the model's meshes
     * 
     * @param Model 
     */
    void MatchTextures(ERS_STRUCT_Model* Model);



public:

    std::unique_ptr<ERS_CLASS_AssetStreamingManager> AssetStreamingManager_; /**<Asset Streaming Manager Instance*/


    void ProcessGPU(std::shared_ptr<ERS_STRUCT_Model> Model); /**<Process the GPU stuff for each model*/


    /**
     * @brief Construct a new Model Loader object
     * 
     * @param Logger 
     * @param TextureLoader 
     */
    ERS_CLASS_ModelLoader(ERS_STRUCT_SystemUtils* SystemUtils, int MaxThreadCount = -1);

    /**
     * @brief Destroy the Model Loader object
     * 
     */
    ~ERS_CLASS_ModelLoader();


    /**
     * @brief Load Model From Given File.
     * 
     * @param AssetPath 
     * @param FlipTextures 
     * @return ERS_STRUCT_Model 
     */
    void LoadModel(long AssetID, std::shared_ptr<ERS_STRUCT_Model> Model);


    /**
     * @brief Process models in scene, perform opengl loading operations on models as needed - opengl cannot be done in another thread.
     * 
     * @param ActiveScene 
     */
    void ProcessNewModels(ERS_STRUCT_Scene* ActiveScene);


    /**
     * @brief Add a model to the queue to be loaded.
     * 
     * @param AssetID 
     * @param Model 
     * @param FlipTextures 
     */
    void AddModelToLoadingQueue(long AssetID, std::shared_ptr<ERS_STRUCT_Model> Model);
    void AddModelToLoadingQueue(std::shared_ptr<ERS_STRUCT_Model> Model);



};

