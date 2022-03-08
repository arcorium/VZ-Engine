#include "vzpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>

#include "vz/Application.h"

namespace vz
{

    Input* Input::m_instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        // Get keycode state
        GLFWwindow* window = static_cast<GLFWwindow*>(vz::Application::Get().GetWindow()->Get());
        auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        // Get keycode state

        GLFWwindow* window = static_cast<GLFWwindow*>(vz::Application::Get().GetWindow()->Get());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(vz::Application::Get().GetWindow()->Get());

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { FLOAT(x), FLOAT(y)};
    }
}
