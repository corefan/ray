CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

ADD_SUBDIRECTORY(unzip)
ADD_SUBDIRECTORY(zlib)
ADD_SUBDIRECTORY(libjpeg)
ADD_SUBDIRECTORY(libpng)
ADD_SUBDIRECTORY(libiconv)
ADD_SUBDIRECTORY(libvorbis)
ADD_SUBDIRECTORY(libogg)
ADD_SUBDIRECTORY(tinyxml)
ADD_SUBDIRECTORY(freetype)
ADD_SUBDIRECTORY(UVAtlas)
ADD_SUBDIRECTORY(DirectX)
ADD_SUBDIRECTORY(DirectXMesh)
ADD_SUBDIRECTORY(HLSLCrossCompiler)

SET_TARGET_ATTRIBUTE(libjpeg "contrib")
SET_TARGET_ATTRIBUTE(libpng "contrib")
SET_TARGET_ATTRIBUTE(libiconv "contrib")
SET_TARGET_ATTRIBUTE(libvorbis "contrib")
SET_TARGET_ATTRIBUTE(libogg "contrib")
SET_TARGET_ATTRIBUTE(unzip "contrib")
SET_TARGET_ATTRIBUTE(zlib "contrib")
SET_TARGET_ATTRIBUTE(tinyxml "contrib")
SET_TARGET_ATTRIBUTE(freetype "contrib")
SET_TARGET_ATTRIBUTE(libHLSLcc "contrib")
SET_TARGET_ATTRIBUTE(UVAtlas "contrib")
SET_TARGET_ATTRIBUTE(DirectXMesh "contrib")

IF(BUILD_OPENGL_ES2 OR BUILD_OPENGL_ES3)
	ADD_SUBDIRECTORY(glsl-optimizer)
	SET_TARGET_ATTRIBUTE(glsl_optimizer "contrib")
	SET_TARGET_ATTRIBUTE(glcpp-library "contrib")
	SET_TARGET_ATTRIBUTE(mesa "contrib")
ENDIF()

IF(BUILD_PHYSIC)
	ADD_SUBDIRECTORY(bullet)
	SET_TARGET_ATTRIBUTE(BulletCollision "contrib")
	SET_TARGET_ATTRIBUTE(BulletDynamics "contrib")
	SET_TARGET_ATTRIBUTE(BulletSoftBody "contrib")
	SET_TARGET_ATTRIBUTE(LinearMath "contrib")
	IF(BUILD_MULTITHREADING)
		SET_TARGET_ATTRIBUTE(MiniCL "contrib")
		SET_TARGET_ATTRIBUTE(BulletSoftBodySolvers_OpenCL_Mini "contrib")
		SET_TARGET_ATTRIBUTE(BulletMultiThreaded "contrib")
	ENDIF()
	IF(BUILD_NVIDIA_OPENCL_DEMOS)
		SET_TARGET_ATTRIBUTE(BulletSoftBodySolvers_OpenCL_NVidia "contrib")
	ENDIF()
ENDIF()

ADD_SUBDIRECTORY(glew)
SET_TARGET_ATTRIBUTE(glew "contrib")

IF(BUILD_PLATFORM_ANDROID)
  ADD_SUBDIRECTORY(android_native_app_glue)
  SET_TARGET_ATTRIBUTE(AndroidNativeAppGlue "contrib")
ELSE()
	ADD_SUBDIRECTORY(glfw)
	SET_TARGET_ATTRIBUTE(glfw "contrib")

	IF(BUILD_OPENGL_ES2 OR BUILD_OPENGL_ES3)
		ADD_SUBDIRECTORY(gles)
	ENDIF()

	IF(BUILD_VULKAN)
		ADD_SUBDIRECTORY(glslang)
		SET_TARGET_ATTRIBUTE(glslang "contrib")
		SET_TARGET_ATTRIBUTE(OGLCompiler "contrib")
		SET_TARGET_ATTRIBUTE(OSDependent "contrib")
		SET_TARGET_ATTRIBUTE(SPIRV "contrib")
		SET_TARGET_ATTRIBUTE(HLSL "contrib")
	ENDIF()
ENDIF()

IF(BUILD_GUI EQUAL 1 OR BUILD_GUI EQUAL 3)
	ADD_SUBDIRECTORY(imgui)
	SET_TARGET_ATTRIBUTE(imgui "contrib")
ENDIF()

IF(BUILD_GUI EQUAL 2 OR BUILD_GUI EQUAL 3)
	ADD_SUBDIRECTORY(MyGUIEngine)
	SET_TARGET_ATTRIBUTE(MyGUIEngine "contrib")
ENDIF()

IF(BUILD_SOUND)
	ADD_SUBDIRECTORY(openal)
	IF(BUILD_PLATFORM_WINDOWS)
		SET_TARGET_ATTRIBUTE(OpenAL32 "contrib")
	ELSE()
		SET_TARGET_ATTRIBUTE(openal "contrib")
	ENDIF()
	SET_TARGET_ATTRIBUTE(common "contrib")
ENDIF()