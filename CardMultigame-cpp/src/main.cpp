// REPL entry point — mirrors C# CardMultigame/Program.cs (verbatim behavior + warts).
#include "interface/UiLogicDispatcher.hpp"
#include "technical/StringUtils.hpp"

#include <iostream>
#include <string>

int main()
{
    cardmultigame::interface::UiLogicDispatcher dispatcher;
    std::string builder;

    std::string orders;
    while (true)
    {
        // Console.WriteLine("...\n") — the text line plus a blank line.
        std::cout << "Please, input the command with proper separators\n\n";

        if (!std::getline(std::cin, orders))
        {
            break; // EOF — C# would crash on null.Trim(); exit cleanly instead (transcripts end with EXIT).
        }

        builder += cardmultigame::technical::Trim(orders); // appended every line, NO separator (WART-23)

        if (orders.find("SETUP") != std::string::npos) // substring, case-sensitive (WART-24)
        {
            const std::string actualOrders = builder;
            builder.clear();
            dispatcher.SetupGame(actualOrders);
        }
        else if (orders.find("EXIT") != std::string::npos)
        {
            break; // no state print after EXIT (WART-25 companion)
        }
        else
        {
            dispatcher.DoStuff(orders);
        }

        // Console.Write(state + NewLine + NewLine) — state plus two newlines.
        std::cout << dispatcher.DisplayCurrentState() << "\n\n";
    }

    return 0;
}
