
set(IMGUI_BACKEND_H
	#backends/imgui_impl_allegro5.h
	#backends/imgui_impl_android.h
	#backends/imgui_impl_dx10.h
	#backends/imgui_impl_dx11.h
	#backends/imgui_impl_dx12.h
	#backends/imgui_impl_dx9.h
	backends/imgui_impl_glfw.h
	#backends/imgui_impl_glut.h
	#backends/imgui_impl_marmalade.h
	#backends/imgui_impl_metal.h
	#backends/imgui_impl_opengl2.h
	backends/imgui_impl_opengl3.h
	backends/imgui_impl_opengl3_loader.h
	#backends/imgui_impl_osx.h
	#backends/imgui_impl_sdl.h
	#backends/imgui_impl_sdlrenderer.h
	#backends/imgui_impl_vulkan.h
	#backends/imgui_impl_wgpu.h
	#backends/imgui_impl_win32.h
	)
set(IMGUI_BACKEND_CPP
	#backends/imgui_impl_allegro5.cpp
	#backends/imgui_impl_android.cpp
	#backends/imgui_impl_dx10.cpp
	#backends/imgui_impl_dx11.cpp
	#backends/imgui_impl_dx12.cpp
	#backends/imgui_impl_dx9.cpp
	backends/imgui_impl_glfw.cpp
	#backends/imgui_impl_glut.cpp
	#backends/imgui_impl_marmalade.cpp
	#backends/imgui_impl_opengl2.cpp
	backends/imgui_impl_opengl3.cpp
	#backends/imgui_impl_sdl.cpp
	#backends/imgui_impl_sdlrenderer.cpp
	#backends/imgui_impl_vulkan.cpp
	#backends/imgui_impl_wgpu.cpp
	#backends/imgui_impl_win32.cpp
	)

add_library(ImGui STATIC 
	${IMGUI_BACKEND_H}
	${IMGUI_BACKEND_CPP}
	imconfig.h
	imgui.h
	imgui_internal.h
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_tables.cpp
	imgui_widgets.cpp
	)

target_include_directories(ImGui
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/backends"
	PRIVATE "${CMAKE_SOURCE_DIR}/thirdparty/GLFW3/include"
	)

set_target_properties(ImGui 
	PROPERTIES VERSION 1.85)
