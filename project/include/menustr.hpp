#pragma once

namespace MainMenuStr {
    constexpr const char* play = "Play";
    constexpr const char* inst = "Instructions";
    constexpr const char* opts = "Options";
    constexpr const char* cred = "Credits";
    constexpr const char* byln = "by Flying Map Entertainment - Made for 20 Second Game Jam";
}


namespace InstructionsStr {
    constexpr const char* instTxt = "Objective: \n"
                    "You are in a lock picking contest. \n"
                    "Your task to open as many locks as you can in 20 seconds. \n\n\n\n\n\n\n\n"

                    "Instructions: \n"
                    "Press the arrow keys in the order given on screen to open each lock. \n"
                    "As you successfully open a lock, you will be given the next one. \n"
                    "If you press the wrong button, you'll get disqualified.";
}

namespace CreditsStr {
    constexpr const char* credTxt =
                    "PICKERLOCK from FLYING MAP ENTERTAINMENT\n"
                    "Version 1.0 - Browser Edition - Dec. 12, 2025\n\n"

                    "Concept, Programming, and Artwork : Abes400\n\n"

                    "- Music -\n" 
                    "\"Safe At Home\" by Marcelo Fernandez - marcelofernandezmusic.com\n"
                    "\"A Journey Awaits\" by Pierre Bondoerffer - opengameart.org: pbondoer\n\n"

                    "Distributed under MIT License.\n"
                    "Written in C++ using Raylib.\n"
                    "Made for 20 Second Game Jam 2025.\n\n"
                    "Download the DELUXE EDITION for ENDLESS MODE & Fullscreen support!";
}

namespace DiffStr {
    constexpr const char* diffTxt = "Select Difficulty to begin:";
    constexpr const char* easy = "Easy: 3 Tiles";
    constexpr const char* medi = "Med.: 4 Tiles";
    constexpr const char* hard = "Hard: 5 Tiles";
    constexpr const char* scrs = "- HIGH SCORES -\nEasy\nMedium\nHard";
    constexpr const char* hscr = "%04d\n%04d\n%04d"; // "0000\n0000\n0000\0" 15 chars (inc. '\0')
}

namespace OptsStr {
    constexpr const char* optsTxt   = "- Options -\n\n\nMusic\n\n\nSFX";
    constexpr const char* enbl      = "Enabled";
    constexpr const char* dsbl      = "Disabled";
}


namespace MiscMenuStr {
    constexpr const char* back = "Back";
}