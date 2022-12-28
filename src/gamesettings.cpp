#include "gamesettings.h"

std::string gamesettings_get_fileconfig() {
    std::ifstream gamesettings_file("gamesettings.rcf", std::ios::binary);
    if (gamesettings_file.fail()) {
        std::string defaultValues = "resolution_x = 800\nresolution_y = 600\n";
        printf("Failed to load gamesettings.rcf; Default values will be used.\n");
        return defaultValues;
    }
    // or we can use file_get_contents
    std::string contents;
    gamesettings_file.seekg(0, std::ios::end);
    contents.resize(gamesettings_file.tellg());
    gamesettings_file.seekg(0, std::ios::beg);
    gamesettings_file.read(&contents[0], contents.size());
    gamesettings_file.close();
    return contents;
}

void gamesettings_load_config(GameSettings_ *GameSettings) {
    std::string gamesettings_string = gamesettings_get_fileconfig();
    GameSettings->resolution_x = rcf_fetch_ivalue(gamesettings_string, "resolution_x");
    GameSettings->resolution_y = rcf_fetch_ivalue(gamesettings_string, "resolution_y");
}
