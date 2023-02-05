
#include "debug.h"

void show_debug_info(Font &font, GameInfo &ginfo, Camera &player, FPSCounter &fps) {
    int line_gap = 20;

    std::string resolution_info = "Resolution: " + std::to_string(ginfo.resolution_x) + "x" + std::to_string(ginfo.resolution_y);
    font.render_text(resolution_info, glm::vec2(20, ginfo.resolution_y - line_gap), 16, glm::vec3(1.0f, 1.0f, 1.0f));

    std::string player_info = "XYZ: " + std::to_string(player.position.x) + " / ";
    player_info += std::to_string(player.position.y) + " / ";
    player_info += std::to_string(player.position.z);
    font.render_text(player_info, glm::vec2(20, ginfo.resolution_y - line_gap * 2), 16, glm::vec3(1.0f, 1.0f, 1.0f));

    std::string fps_info = "FPS: " + std::to_string(fps.fps);
    font.render_text(fps_info, glm::vec2(20, ginfo.resolution_y - line_gap * 3), 16, glm::vec3(1.0f, 1.0f, 1.0f));

    std::string frametime_info = "Frametime ms: " + std::to_string(fps.frametime * 1000);
    font.render_text(frametime_info, glm::vec2(20, ginfo.resolution_y - line_gap * 4), 16, glm::vec3(1.0f, 1.0f, 1.0f));
}