#pragma once

#include <glad/glad.h>

#include <vector>
#include <iostream>

#include "RenderShaderProgram/RenderShaderProgram.h"
#include "RenderShader/RenderShader.h"
#include "RenderCamera/RenderCamera.h"

// To do: Consider using different data structure for Scene elements

namespace SimpleRender
{
	// Forward declare all classes
	class RenderObject;
	class RenderApplication;
	class RenderCamera;


	class RenderScene
	{
	public:
		RenderScene(SimpleRender::RenderApplication* application);
		void LoadDefaultScene();

		void DrawScene(RenderCamera* camera, GLuint framebuffer);

		/// <summary>
		/// Draw the scene for object selection.
		/// </summary>
		/// <param name="camera"></param>
		/// <param name="framebuffer"></param>
		void DrawIDScene(RenderCamera* camera, GLuint framebuffer);

		/// <summary>
		/// Free allocated memory.
		/// As of now does nothing.
		/// Should implement an interface to release OpenGL IDs of each class.
		/// </summary>
		inline void Dispose()
		{

		}


		inline std::vector<RenderShader*>* GetShadersOfType(enum ShaderType type)
		{
			if(type == ShaderType::Vertex)
				return SceneVertexShaders;
			else if(type == ShaderType::Fragment)
				return SceneFragmentShaders;
			else
				return SceneGeometryShaders;
		}

		
		/// <summary>
		/// Add a render object to the scene, managing its ID
		/// </summary>
		/// <param name="program"></param>
		/// <param name="path"></param>
		void AddObject(RenderShaderProgram*& program, std::string path = "");

		/// <summary>
		/// Delete the specified object. Manage the IDs afterwards.
		/// </summary>
		/// <param name="object"></param>
		void DeleteObject(RenderObject* object);

		/// <summary>
		/// Delete the active object. Equivalent to calling DeleteObject with arg = ActiveObject
		/// </summary>
		void DeleteActiveObject();


		std::vector<RenderObject*>* const SceneObjects = &objects;
		std::vector<RenderCamera*>* const SceneCameras = &cameras;

		std::vector<RenderShader*>* const SceneVertexShaders = &vertexShaders;
		std::vector<RenderShader*>* const SceneFragmentShaders = &fragmentShaders;
		std::vector<RenderShader*>* const SceneGeometryShaders = &geometryShaders;

		std::vector<RenderShaderProgram*>* const SceneShaderPrograms = &shaderPrograms;

		RenderCamera* ActiveCamera = nullptr;
		RenderObject* ActiveObject = nullptr;
		RenderShaderProgram* ActiveShaderProgram = nullptr;
		RenderShader* ActiveShader = nullptr;

		GLuint* SceneFrameBuffer = &framebuffer;
		GLuint* SceneTexture = &screenTexture;


		const RenderApplication* Application = application;

		RenderShaderProgram* const ObjectIDShaderProgram = &objectSelectionShaderProgram;


	private:
		RenderApplication* application;


		std::vector<RenderObject*> objects;
		std::vector<RenderCamera*> cameras;

		std::vector<RenderShader*> vertexShaders;
		std::vector<RenderShader*> fragmentShaders;
		std::vector<RenderShader*> geometryShaders;

		std::vector<RenderShaderProgram*> shaderPrograms;

		GLuint framebuffer = 0;
		GLuint screenTexture = 0;

		RenderShaderProgram objectSelectionShaderProgram;
	};


}