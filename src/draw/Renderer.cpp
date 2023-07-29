#include "draw/Renderer.h"
#include <stdio.h>
#include "Engine.h"
#include "Window.h"
#include "colors/Colors.h"

Renderer::Renderer()
	:renderer(nullptr), fps(30), targetFrameTime(1000 / fps), colorBufferTexture(nullptr), utility(this)
{

}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}


bool Renderer::CreateRenderer()
{
	SDL_Window* window = Engine::GetInstance()->GetWindow()->GetSdlWindow();
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		fprintf(stderr, "Error Creating SDL Renderer. \n");
		return false;
	}

	return true;
}

/* Color buffer is not actually displayed, it will be moved to an SDL_Texture to be displayed.*/
void Renderer::ClearColorBuffer(uint32_t color)
{
	for (int y = 0; y < GetWindowHeight(); y++)
	{
		for (int x = 0; x < GetWindowWidth(); x++)
		{
			colorBuffer[(GetWindowWidth() * y) + x] = color;
		}
	}
}

/* Copy the color buffer into the SDL_Texture to be displayed. */
void Renderer::RenderColorBuffer()
{
	SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer.data(), GetWindowWidth() * sizeof(uint32_t));
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	const char* error = SDL_GetError();
	if (*error) {
		printf("SDL Error: %s\n", error);
		SDL_ClearError();
	}
}

const int Renderer::GetWindowHeight() const
{
	return 	Engine::GetInstance()->GetWindow()->GetHeight();
}

const int Renderer::GetWindowWidth() const
{
	return Engine::GetInstance()->GetWindow()->GetWidth();
}

void Renderer::AddToColorBuffer(int index, uint32_t color)
{
	try 
	{
		colorBuffer.at(index) = color;
	}
	catch (std::out_of_range& e) 
	{
		std::cerr << "Out of Range error: " << e.what() << '\n';
	}
}

void Renderer::Update()
{
	SDL_Delay(targetFrameTime);

	/* ======================= NEEDS TO BE ABSTRACTED FROM HERE ===============================*/
	// Reset to NULL on every update;
// 	triangles_to_render = NULL;
// 
// 	// Add transform manually for testing
// 	mesh.rotation.y += 0.01;
// 	mesh.rotation.z += 0.01;
// 	mesh.rotation.x += 0.01;
// 	// 	mesh.scale.x += 0.002;
// 	// 	mesh.scale.y += 0.002;
// 	//	mesh.translation.x += 0.01;
// 
// 	matrix4_t scale_matrix = make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
// 	matrix4_t translation_matrix = make_translation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
// 	matrix4_t rotation_matrix_x = make_rotation_x(mesh.rotation.x);
// 	matrix4_t rotation_matrix_y = make_rotation_y(mesh.rotation.y);
// 	matrix4_t rotation_matrix_z = make_rotation_z(mesh.rotation.z);
// 
// 	int num_faces = array_length(mesh.faces);
// 	for (int i = 0; i < num_faces; i++)
// 	{
// 		face_t mesh_face = mesh.faces[i];
// 
// 		vec3_t face_verticies[3];
// 		face_verticies[0] = mesh.vertices[mesh_face.a - 1];
// 		face_verticies[1] = mesh.vertices[mesh_face.b - 1];
// 		face_verticies[2] = mesh.vertices[mesh_face.c - 1];
// 		//mesh_face.color = WHITE;
// 
// 		vec4_t transformed_vertices[3];
// 
// 		/* Transform */
// 		for (int j = 0; j < 3; j++)
// 		{
// 			vec4_t transformed_vertex = vec4_from_vec3(face_verticies[j]);
// 
// 			transformed_vertex = mat4_multi_vec4(scale_matrix, transformed_vertex);
// 			transformed_vertex = mat4_multi_vec4(rotation_matrix_x, transformed_vertex);
// 			transformed_vertex = mat4_multi_vec4(rotation_matrix_y, transformed_vertex);
// 			transformed_vertex = mat4_multi_vec4(rotation_matrix_z, transformed_vertex);
// 			transformed_vertex = mat4_multi_vec4(translation_matrix, transformed_vertex);
// 
// 			// Translate vertex away from camera
// 			transformed_vertex.z += camera_zoom;
// 			transformed_vertices[j] = transformed_vertex;
// 		}
// 
// 		bool should_project = true;
// 		if (backface_culling_enabled)
// 		{
// 			should_project = backface_culling(&transformed_vertices);
// 		}
// 
// 		/* Project */
// 		if (should_project)
// 		{
// 			vec2_t projected_points[3];
// 			for (int j = 0; j < 3; j++)
// 			{
// 				// project current vertex
// 				projected_points[j] = project(vec3_from_vec4(transformed_vertices[j]));
// 
// 				//scale and translate projected point to middle of screen.
// 				projected_points[j].x += (window_width / 2);
// 				projected_points[j].y += (window_height / 2);
// 			}
// 
// 			// Calculate depth to render faces in order.
// 			float face_depth = GetFaceDepth(transformed_vertices);
// 
// 			triangle_t projected_triangle =
// 			{
// 				.points =
// 				{
// 					{ projected_points[0].x, projected_points[0].y },
// 					{ projected_points[1].x, projected_points[1].y },
// 					{ projected_points[2].x, projected_points[2].y }
// 				},
// 				.color = mesh_face.color,
// 				.avg_depth = face_depth
// 			};
// 			array_push(triangles_to_render, projected_triangle);
// 		}
// 		// Sort based on average vert depth.
// 		SortTriangleFaces(triangles_to_render);
// 	}
}

void Renderer::Render()
{
	/* ======================= NEEDS TO BE ABSTRACTED FROM HERE ===============================*/
	//draw_grid(LIGHT_SLATE_GRAY);

	// Loop over projected triangle and render them
	//int num_triangles = array_length(triangles_to_render);
// 	for (int i = 0; i < num_triangles; i++)
// 	{
// 		triangle_t triangle = triangles_to_render[i];
// 
// 		if (render_vertices) display_vertices(triangle);
// 		if (render_faces) display_faces(triangle);
// 		if (render_wireframe) display_wireframe(triangle);
// 	}

	// Clear array of triangles every frame
	//array_free(triangles_to_render);
	RenderColorBuffer();
	ClearColorBuffer(SLATE_GRAY);
	SDL_RenderPresent(renderer);
}

void Renderer::Setup()
{
	colorBuffer.resize(GetWindowHeight() * GetWindowWidth());
	CreateRenderer();
	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, GetWindowWidth(), GetWindowHeight());
	//load_cube_mesh_data();
	//load_obj_file_data("./assets/cube.obj");
}
