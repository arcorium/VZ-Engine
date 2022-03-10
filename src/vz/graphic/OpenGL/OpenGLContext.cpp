#include "vzpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace vz
{

    namespace ctx
    {
        OpenGL::OpenGL(GLFWwindow* window)
            : m_window(window)
        {
        }

        void OpenGL::Init()
        {
            // GLFW
            glfwMakeContextCurrent(m_window);

            // GLAD
            VZ_ASSERT(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)), "Failed to instantiate GLAD");
        }

        void OpenGL::SwapBuffers()
        {
            glfwSwapBuffers(m_window);
        }
    }
}