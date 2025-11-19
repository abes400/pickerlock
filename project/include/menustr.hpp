#ifndef MENUSTR_HPP
#define MENUSTR_HPP

namespace MainMenuStr {
    constexpr const char* play = "Play";
    constexpr const char* inst = "Instruction";
    constexpr const char* cred = "Credits";
    constexpr const char* best = "Best: ";
    constexpr const char* byln = "(C) 2025 Abes400 -- Made for 20 Second Game Jam";
}


namespace InstructionsStr {
    constexpr const char* instTxt = "Objective: \n"
                    "You are in a lock picking contest. \n"
                    "You are tasked to pick as many locks as you can in 20 seconds. \n\n\n\n\n\n\n\n"

                    "Instructions: \n"
                    "Press the arrow keys in the order given on screen to pick each lock. \n"
                    "As you successfully break a lock, you will be given the next one. \n"
                    "If you press the wrong button, you'll get disqualified.";
}

namespace CreditsStr {
    constexpr const char* credTxt =
                    "Pickerlock 1.0 \n\n"
                    "---- CREDITS ---- \n"
                    "Concept, Programming and Artwork : Abes400 \n\n"
                    "Sound effects (Probably) Obtained from ZapSplat. \n"
                    "Distributed under MIT License. \n\n"
                    "Made for 20 Seconds GameJam 2025\n";
}

namespace DiffStr {
    constexpr const char* diffTxt ="Select Difficulty to begin:";
    constexpr const char* easy ="Easy";
    constexpr const char* medi ="Medium";
    constexpr const char* hard ="Hard";
}


namespace MiscMenuStr {
    constexpr const char* back = "Back";
}
#endif