
#include "debug.h"

void show_debug_info(TextManager &TextManager, GameInfo &ginfo, Camera &player, FPSCounter &fps) {
    int line_gap = 20;

    std::string resolution_info = "Resolution: " + std::to_string(ginfo.resolution_x) + "x" + std::to_string(ginfo.resolution_y);
    TextManager.render(resolution_info, glm::vec2(20, ginfo.resolution_y - line_gap), 16);

    std::string player_info = "XYZ: " + std::to_string(player.position.x) + " / ";
    player_info += std::to_string(player.position.y) + " / ";
    player_info += std::to_string(player.position.z);
    TextManager.render(player_info, glm::vec2(20, ginfo.resolution_y - line_gap * 2), 16);

    std::string fps_info = "FPS: " + std::to_string(fps.fps);
    TextManager.render(fps_info, glm::vec2(20, ginfo.resolution_y - line_gap * 3), 16);

    std::string frametime_info = "Frametime ms: " + std::to_string(fps.frametime * 1000);
    TextManager.render(frametime_info, glm::vec2(20, ginfo.resolution_y - line_gap * 4), 16);
}
