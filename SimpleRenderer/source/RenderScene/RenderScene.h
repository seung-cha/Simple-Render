#pragma once

#include <glad/glad.h>

#include <vector>
#include <iostream>

#include <memory>

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
	class RenderCubemap;
	class RenderDeferredRender;


	class RenderScene
	{
	public:
		RenderScene(SimpleRender::RenderApplication* application);
		~RenderScene();
		void LoadDefaultScene();

		void DrawScene(RenderCamera* const& camera, const GLuint& framebuffer);

		/// <summary>
		/// Draw the scene with selected shader program, instead of each object's program.
		/// </summary>
		/// <param name="camera"></param>
		/// <param name="framebuffer"></param>
		/// <param name="shaderProgram"></param>
		void DrawScene(RenderCamera* const& camera, const GLuint& framebuffer, RenderShaderProgram* const& shaderProgram);


		/// <summary>
		/// Draw the scene for Gbuffer
		/// </summary>
		/// <param name="camera"></param>
		/// <param name="framebuffer"></param>
		void DrawGBufferScene(RenderCamera* const& camera, const GLuint& framebuffer);

		/// <summary>
		/// Draw the scene for object selection.
		/// </summary>
		/// <param name="camera"></param>
		/// <param name="framebuffer"></param>
		void DrawIDScene(RenderCamera* const& camera, const GLuint& framebuffer);

		/// <summary>
		/// Free allocated memory.
		/// As of now does nothing.
		/// Should implement an interface to release OpenGL IDs of each class.
		/// </summary>
		void Dispose()
		{

		}


		inline std::vector<std::unique_ptr<RenderShader>>* GetShadersOfType(enum ShaderType type)
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
		/// <returns>true if successfully added object</returns>
		bool AddObject(RenderShaderProgram* const& program, const std::string& path);
		void AddDefaultObject(RenderShaderProgram* const& program);


		/// <summary>
		/// Delete the specified object. Manage the IDs afterwards.
		/// </summary>
		/// <param name="object"></param>
		void DeleteObject(RenderObject* const object);

		/// <summary>
		/// Delete the active object. Equivalent to calling DeleteObject with arg = ActiveObject
		/// </summary>
		void DeleteActiveObject();


		/// <summary>
		/// Update the deferred render class.
		/// This is really just deleting the current one
		/// and then assigning a new one.
		/// </summary>
		void UpdateDeferredRender();


		std::vector<std::unique_ptr<RenderObject>>* const SceneObjects = &objects;

		std::vector<std::unique_ptr<RenderShader>>* const SceneVertexShaders = &vertexShaders;
		std::vector<std::unique_ptr<RenderShader>>* const SceneFragmentShaders = &fragmentShaders;
		std::vector<std::unique_ptr<RenderShader>>* const SceneGeometryShaders = &geometryShaders;

		std::vector<std::unique_ptr<RenderShaderProgram>>* const SceneShaderPrograms = &shaderPrograms;


		RenderObject* ActiveObject = nullptr;
		RenderShaderProgram* ActiveShaderProgram = nullptr;
		RenderShader* ActiveShader = nullptr;



		RenderApplication*& Application = application;


		const std::unique_ptr<RenderShaderProgram>& ObjectIDShaderProgram = objectSelectionShaderProgram;
		const std::unique_ptr<RenderShaderProgram>& GBufferShaderProgram = gbufferShaderProgram;
		const std::unique_ptr<RenderDeferredRender>& DeferredRender = deferredRender;
		const std::unique_ptr<RenderCubemap>& Cubemap = cubemap;

	private:
		RenderApplication* application;


		std::vector<std::unique_ptr<RenderObject>> objects;

		std::vector<std::unique_ptr<RenderShader>> vertexShaders;
		std::vector<std::unique_ptr<RenderShader>> fragmentShaders;
		std::vector<std::unique_ptr<RenderShader>> geometryShaders;

		std::vector<std::unique_ptr<RenderShaderProgram>> shaderPrograms;


		std::unique_ptr<RenderShaderProgram> objectSelectionShaderProgram;
		std::unique_ptr<RenderShader> selectionVert, selectionFrag;
		std::unique_ptr<RenderShaderProgram> gbufferShaderProgram;
		std::unique_ptr<RenderShader> gBufferVert, gBufferFrag;
		std::unique_ptr<RenderCubemap> cubemap;
		std::unique_ptr<RenderDeferredRender> deferredRender;
	};


}