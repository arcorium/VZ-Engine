#pragma once
#include "Context.h"

// dummy struct
struct GLFWwindow;

namespace vz
{
    /**
     * \brief OpenGL graphics context implementation
     */
    namespace ctx
    {

        class OpenGL : public Context
        {
        public:
            OpenGL(GLFWwindow* window);

            void Init() override;
            void SwapBuffers() override;

        private:
            GLFWwindow* m_window;
        };
    }
}
