#include "gameinfo.h"

void GameInfo::set_vsync(bool state) {
    if (state) {
        vsync = true;
        glfwSwapInterval(1);
        return;}
    vsync = false;
    glfwSwapInterval(0);
    
}

void GameInfo::set_viewport(int res_x, int res_y) {
    glViewport(0, 0, res_x, res_y);
}

std::string gameinfo_get_fileconfig() {
    std::ifstream settings_file("settings.rcf", std::ios::binary);
    if (settings_file.fail()) {
        std::string defaultValues = "resolution_x = 800\nresolution_y = 600\nvsync = 1\n";
        printf("Failed to load settings.rcf; Default values will be used. Creating settings.rcf;\n");
        std::ofstream file("settings.rcf", std::ios::binary);
        file << defaultValues;
        file.close();
        return defaultValues;
    }
    // or we can use file_get_contents
    std::string contents;
    settings_file.seekg(0, std::ios::end);
    contents.resize(settings_file.tellg());
    settings_file.seekg(0, std::ios::beg);
    settings_file.read(&contents[0], contents.size());
    settings_file.close();
    return contents;
}

void GameInfo::load_config() {
    std::string settings_string = gameinfo_get_fileconfig();
    resolution_x = rcf_fetch_ivalue(settings_string, "resolution_x");
    resolution_y = rcf_fetch_ivalue(settings_string, "resolution_y");
    glfwSetWindowSize(window, resolution_x, resolution_y);
    set_viewport(resolution_x, resolution_y);
    
    vsync = rcf_fetch_bvalue(settings_string, "vsync");
    set_vsync(vsync);
    
}
GameInfo::GameInfo() {
    window = glfwCreateWindow(800, 600, "RCraft", NULL, NULL); // We resize the window in another function. @Refactor Maybe we should do it in this one too.
    glfwMakeContextCurrent(window);
    glad_init();
}

void GameInfo::hide_cursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void GameInfo::show_cursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}


