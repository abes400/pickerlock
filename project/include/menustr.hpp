#pragma once

namespace MainMenuStr {
    constexpr const char* play = "Play";
    constexpr const char* inst = "Instructions";
    constexpr const char* opts = "Options";
    constexpr const char* cred = "Credits";
    constexpr const char* exit = "Quit Game";
    constexpr const char* byln = "by Flying Map Entertainment - Made for 20 Second Game Jam";
}


namespace InstructionsStr {
    constexpr const char* instTxt = "Objective: \n"
                    "You don't know how and when you decided to do so, \n"
                    "but somehow, you found yourself enrolled in a lock picking contest. \n"
                    "You are tasked to open as many locks as you can. \n\n\n\n\n\n\n\n\n\n"

                    "Instructions: \n"
                    "Press the arrow keys in the order given on screen to open each lock. \n"
                    "As you successfully open a lock, you will be given the next one. \n"
                    "If you press the wrong button, the game ends.";
}

namespace CreditsStr {
    constexpr const char* credTxt =
                    "PICKERLOCK from FLYING MAP ENTERTAINMENT\n"
                    "Version 1.0 - Deluxe Edition - Feb. 01, 2026\n\n\n\n"

                    "- Concept, Programming, and Artwork -\n"
                    "I. K. Bilir (Abes400)\n\n\n\n"

                    "- Music -\n" 
                    "\"Safe At Home\" by Marcelo Fernandez - marcelofernandezmusic.com\n"
                    "\"A Journey Awaits\" by Pierre Bondoerffer - opengameart.org: pbondoer\n\n\n"

                    "Distributed under MIT License.\n"
                    "Initially made for 20 Second Game Jam 2025.\n"
                    "Altered for 20 Million Second Game Jam.";
}

namespace DiffStr {
    constexpr const char* diffTxt = "Endless Mode:\n\n\n\n\n\n\nSelect difficulty to begin:";
    constexpr const char* easy  = "Easy: 3 Tiles";
    constexpr const char* medi  = "Med.: 4 Tiles";
    constexpr const char* hard  = "Hard: 5 Tiles";
    constexpr const char* scrs  = "- Best (Timed) -\nEasy\nMedium\nHard";
    constexpr const char* scrsE = "- Best (Endless) -\nEasy\nMedium\nHard";
    constexpr const char* hscr  = "%04u\n%04u\n%04u"; // "0000\n0000\n0000\0" 15 chars (inc. '\0')

    constexpr const char* endTxt = "Endless Mode";
    constexpr const char* mdDsc1 = "- Given 20 seconds through entire game.\n- Game ends as the time runs out.";
    constexpr const char* mdDsc2 = "- Given 3 to 5 seconds for each lock,\n  depending on difficulty.\n"
                                   "- Time resets as you crack each lock.\n"
                                   "- Game ends as the time runs out.";
}

namespace OptsStr {
    constexpr const char* optsTxt   = "- Options -\n\nMusic\n\nSFX\n\nFullscreen";
    constexpr const char* rsHS      = "Rst Best Scrs";
    constexpr const char* rsInf     = "All high scores reset!";
}


namespace MiscMenuStr {
    constexpr const char* back = "Back";
}