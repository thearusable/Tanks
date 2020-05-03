#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <memory>

class HelloTriangleApplication {
public:

	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	const std::vector<const char*> m_ValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

#ifdef NDEBUG
	const bool m_EnableValidationLayers = false;
#else
	const bool m_EnableValidationLayers = true;
#endif

	void run() {
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:

	GLFWwindow* m_Window;
	vk::Instance m_Instance;

	void initWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_Window = glfwCreateWindow(WIDTH, HEIGHT, "Karakan", nullptr, nullptr);
	}

	void initVulkan() {
		createInstance();
	}

	void mainLoop(){
		while (!glfwWindowShouldClose(m_Window)) {
			glfwPollEvents();
		}
	}

	void createInstance() {
		vk::ApplicationInfo appInfo; 
		appInfo.setPApplicationName("Karakan");
		appInfo.setApplicationVersion(VK_MAKE_VERSION(1, 0, 0));
		appInfo.setPEngineName("No Engine");
		appInfo.setEngineVersion(VK_MAKE_VERSION(1, 0, 0));
		appInfo.setApiVersion(VK_API_VERSION_1_2);

		vk::InstanceCreateInfo createInfo;
		createInfo.setPApplicationInfo(&appInfo);

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.setEnabledExtensionCount(glfwExtensionCount);
		createInfo.setPpEnabledExtensionNames(glfwExtensions);
		createInfo.setEnabledLayerCount(0);

		if (vk::createInstance(&createInfo, nullptr, &m_Instance) != vk::Result::eSuccess){
			throw std::runtime_error("Failed to create instance!");
		}

		auto extensions = vk::enumerateInstanceExtensionProperties();

		std::cout << "Available extensions: \n";
		for (const auto& ext : extensions) {
			std::cout << "\t" << ext.extensionName << "\n";
		}

		if (m_EnableValidationLayers && !checkValidationLayers()) {
			throw std::runtime_error("Validation layers requested but not available!");
		}

		if (m_EnableValidationLayers) {
			createInfo.setEnabledLayerCount(static_cast<uint32_t>(m_ValidationLayers.size()));
			createInfo.setPpEnabledLayerNames(m_ValidationLayers.data());
		}
		else {
			createInfo.setEnabledLayerCount(0);
		}
	}

	bool checkValidationLayers() {
		auto availableLayers = vk::enumerateInstanceLayerProperties();

		std::cout << "Available layers: \n";
		for (const auto& ext : availableLayers) {
			std::cout << "\t" << ext.layerName << "\n";
		}

		for (const auto& layerName : m_ValidationLayers) {
			bool isFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					isFound = true;
					break;
				}
			}

			if (!isFound) {
				return false;
			}
		}

		return true;
	}

	void cleanup(){
		glfwDestroyWindow(m_Window);

		glfwTerminate();
	}
};

int main() {
	HelloTriangleApplication app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}