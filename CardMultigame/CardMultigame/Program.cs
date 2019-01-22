using Core.Interface;
using System;

namespace CardMultigame
{
    class Program
    {
        static void Main(string[] args)
        {
            var dispatcher = new UiLogicDispatcher();

            while(true)
            {
                Console.WriteLine("Please, input the command with proper separators\n");

                string orders = Console.ReadLine();

                if(orders.Contains("SETUP"))
                {
                    dispatcher.SetupGame(orders);
                }
                else if(orders.Contains("EXIT"))
                {
                    break;
                }
                else
                {
                    dispatcher.DoStuff(orders);
                }
                
                Console.Write(dispatcher.DisplayCurrentState() + System.Environment.NewLine + System.Environment.NewLine);
            }
        }
    }
}
